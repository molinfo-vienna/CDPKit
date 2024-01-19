/* 
 * MMFF94OutOfPlaneBendingInteractionParameterizer.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

 
#include "StaticInit.hpp"

#include <iterator>
#include <string>
#include <cstddef>

#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

    const unsigned int FALLBACK_ATOM_TYPE = 1;
}


ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::MMFF94OutOfPlaneBendingInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
                                                                                                             MMFF94OutOfPlaneBendingInteractionList& ia_list,
                                                                                                             bool strict):
    filterFunc(), atomTypeFunc(&getMMFF94NumericType), paramTable(MMFF94OutOfPlaneBendingParameterTable::get(true)),
    typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get())
{
    parameterize(molgraph, ia_list, strict);
}

ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::MMFF94OutOfPlaneBendingInteractionParameterizer():
    filterFunc(), atomTypeFunc(&getMMFF94NumericType), paramTable(MMFF94OutOfPlaneBendingParameterTable::get(true)),
    typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get()) 
{}


void ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setFilterFunction(const InteractionFilterFunction4& func)
{
    filterFunc = func;
} 

void ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
    atomTypeFunc = func;
}  

void ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setOutOfPlaneBendingParameterTable(const MMFF94OutOfPlaneBendingParameterTable::SharedPointer& table)
{
    paramTable = table;
}

void ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map)
{
    paramTypeMap = map;
}

void ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
    typePropTable = table;
}

void ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, MMFF94OutOfPlaneBendingInteractionList& ia_list,
                                                                               bool strict)
{
    using namespace Chem;

    typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;

    ia_list.clear();

    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
        const Atom& ctr_atom = molgraph.getAtom(i);
        unsigned int ctr_atom_type = atomTypeFunc(ctr_atom);
        const AtomTypePropEntry& ctr_prop_entry = typePropTable->getEntry(ctr_atom_type);

        if (!ctr_prop_entry) {
            if (!strict) 
                continue;

            throw ParameterizationFailed("MMFF94OutOfPlaneBendingInteractionParameterizer: could not find MMFF94 atom type properties for atom #" + 
                                         std::to_string(i));
        }
        
        if (ctr_prop_entry.getNumNeighbors() != 3) // only 3-valent atoms are considered
            continue;

        nbrAtoms.clear();
        getConnectedAtoms(ctr_atom, molgraph, std::back_inserter(nbrAtoms));

        if (nbrAtoms.size() != 3)                  // sanity check 
            continue;

        if (filterFunc && !filterFunc(*nbrAtoms[0], ctr_atom, *nbrAtoms[1], *nbrAtoms[2]))
            continue;

        double force_const;
        std::size_t nbr_atom_idcs[3];

        try {
            force_const = getForceConstant(molgraph, ctr_atom_type, i, nbrAtoms, strict);

        } catch (const ParameterizationFailed& e) {
            if (strict)
                throw e;

            unsigned int nbr_atom_types[3] = { FALLBACK_ATOM_TYPE, FALLBACK_ATOM_TYPE, FALLBACK_ATOM_TYPE };

            force_const = getForceConstant(molgraph, ctr_atom_type, i, nbr_atom_types, nbrAtoms);
        }

        for (std::size_t j = 0; j < 3; j++)
            nbr_atom_idcs[j] = molgraph.getAtomIndex(*nbrAtoms[j]);
        
        ia_list.addElement(MMFF94OutOfPlaneBendingInteraction(nbr_atom_idcs[0], i, nbr_atom_idcs[1], nbr_atom_idcs[2], force_const));
        ia_list.addElement(MMFF94OutOfPlaneBendingInteraction(nbr_atom_idcs[2], i, nbr_atom_idcs[0], nbr_atom_idcs[1], force_const));
        ia_list.addElement(MMFF94OutOfPlaneBendingInteraction(nbr_atom_idcs[1], i, nbr_atom_idcs[2], nbr_atom_idcs[0], force_const));
    } 
}

double ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::getForceConstant(const Chem::MolecularGraph& molgraph, unsigned int ctr_atom_type, 
                                                                                     std::size_t ctr_atom_idx, const AtomList& nbr_atoms, bool strict) const
{
    unsigned int nbr_atom_types[3];

    for (std::size_t i = 0; i < 3; i++) {
         nbr_atom_types[i] = atomTypeFunc(*nbr_atoms[i]);

         if (!strict && nbr_atom_types[i] == 0)
             nbr_atom_types[i] = FALLBACK_ATOM_TYPE;
    }

    return getForceConstant(molgraph, ctr_atom_type, ctr_atom_idx, nbr_atom_types, nbr_atoms);
}

double ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::getForceConstant(const Chem::MolecularGraph& molgraph, unsigned int ctr_atom_type, 
                                                                                     std::size_t ctr_atom_idx, unsigned int nbr_atom_types[3], const AtomList& nbr_atoms) const
{
    typedef MMFF94OutOfPlaneBendingParameterTable::Entry ParamEntry;

    const unsigned int* nbr_atom_param_types[3];

    for (std::size_t i = 0; i < 3; i++) {
        nbr_atom_param_types[i] = paramTypeMap->getEntry(nbr_atom_types[i]).getParameterTypes();

        if (!nbr_atom_param_types[i])
            throw ParameterizationFailed("MMFF94OutOfPlaneBendingInteractionParameterizer: could not find MMFF94 parameter atom type equivalence list for atom #" + 
                                         std::to_string(molgraph.getAtomIndex(*nbr_atoms[i])));
    }

    for (std::size_t i = 0; i < MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES; i++) {
        const ParamEntry& param_entry = paramTable->getEntry(nbr_atom_param_types[0][i], ctr_atom_type, nbr_atom_param_types[1][i], nbr_atom_param_types[2][i]);

        if (!param_entry)
            continue;

        return param_entry.getForceConstant();
    }

    throw ParameterizationFailed("MMFF94OutOfPlaneBendingInteractionParameterizer: could not find MMFF94 parameters for out-of-plane bending interaction centered at atom #" + 
                                 std::to_string(ctr_atom_idx));
    return 0.0;
}
