/* 
 * DefaultMultiConfMoleculeInputProcessor.cpp 
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

#include "CDPL/Chem/DefaultMultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL;


constexpr unsigned int Chem::DefaultMultiConfMoleculeInputProcessor::DEF_ATOM_PROPERTY_FLAGS;
constexpr unsigned int Chem::DefaultMultiConfMoleculeInputProcessor::DEF_BOND_PROPERTY_FLAGS;


Chem::DefaultMultiConfMoleculeInputProcessor::DefaultMultiConfMoleculeInputProcessor(bool comp_names, unsigned int atom_flags, unsigned int bond_flags):
    compareNames(comp_names), atomFlags(atom_flags), bondFlags(bond_flags) {}

bool Chem::DefaultMultiConfMoleculeInputProcessor::init(MolecularGraph& tgt_molgraph) const 
{
    if (!hasCoordinates(tgt_molgraph, 3))
        return false;

    if ((atomFlags & AtomPropertyFlag::CONFIGURATION) || (bondFlags & BondPropertyFlag::CONFIGURATION)) {
        perceiveComponents(tgt_molgraph, true);
        perceiveSSSR(tgt_molgraph, true);
        setRingFlags(tgt_molgraph, true);
        calcImplicitHydrogenCounts(tgt_molgraph, true);
        perceiveHybridizationStates(tgt_molgraph, true);
        setAromaticityFlags(tgt_molgraph, true);
        calcCIPPriorities(tgt_molgraph, true);

        if (atomFlags & AtomPropertyFlag::CONFIGURATION) {
            perceiveAtomStereoCenters(tgt_molgraph, true);
            calcAtomStereoDescriptors(tgt_molgraph, false); 
        }

        if (bondFlags & BondPropertyFlag::CONFIGURATION) {
            perceiveBondStereoCenters(tgt_molgraph, true);
            calcBondStereoDescriptors(tgt_molgraph, false); 
        }
    }

    for (MolecularGraph::AtomIterator it = tgt_molgraph.getAtomsBegin(), end = tgt_molgraph.getAtomsEnd(); it != end; ++it) {
        Atom& atom = *it;
        Math::Vector3DArray::SharedPointer coords_array(new Math::Vector3DArray());
        
        set3DCoordinatesArray(atom, coords_array);
        
        coords_array->addElement(get3DCoordinates(atom));
    }

    return true;
}

bool Chem::DefaultMultiConfMoleculeInputProcessor::isConformation(MolecularGraph& tgt_molgraph,
                                                                  MolecularGraph& conf_molgraph) const
{
    if (tgt_molgraph.getNumAtoms() != conf_molgraph.getNumAtoms())
        return false;

    if (tgt_molgraph.getNumBonds() != conf_molgraph.getNumBonds())
        return false;

    if (compareNames && (getName(tgt_molgraph) != getName(conf_molgraph)))
        return false;

    if (!hasCoordinates(conf_molgraph, 3))
        return false;

    if (atomFlags) {
        for (MolecularGraph::ConstAtomIterator tgt_it = tgt_molgraph.getAtomsBegin(), 
                 conf_it = conf_molgraph.getAtomsBegin(), tgt_end = tgt_molgraph.getAtomsEnd();
             tgt_it != tgt_end; ++tgt_it, ++conf_it) {

            const Atom& tgt_atom = *tgt_it;
            const Atom& conf_atom = *conf_it;

            if ((atomFlags & AtomPropertyFlag::TYPE) && getType(tgt_atom) != getType(conf_atom))
                return false;

            if ((atomFlags & AtomPropertyFlag::FORMAL_CHARGE) && getFormalCharge(tgt_atom) != getFormalCharge(conf_atom))
                return false;

            if ((atomFlags & AtomPropertyFlag::ISOTOPE) && getIsotope(tgt_atom) != getIsotope(conf_atom))
                return false;
        }
    }

    for (MolecularGraph::ConstBondIterator tgt_it = tgt_molgraph.getBondsBegin(), 
             conf_it = conf_molgraph.getBondsBegin(), tgt_end = tgt_molgraph.getBondsEnd();
         tgt_it != tgt_end; ++tgt_it, ++conf_it) {
        
        const Bond& tgt_bond = *tgt_it;
        const Bond& conf_bond = *conf_it;

        if (tgt_molgraph.getAtomIndex(tgt_bond.getBegin()) != conf_molgraph.getAtomIndex(conf_bond.getBegin()))
            return false;

        if (tgt_molgraph.getAtomIndex(tgt_bond.getEnd()) != conf_molgraph.getAtomIndex(conf_bond.getEnd()))
            return false;

        if ((bondFlags & BondPropertyFlag::ORDER) && getOrder(tgt_bond) != getOrder(conf_bond))
            return false;
    }

    if ((atomFlags & AtomPropertyFlag::CONFIGURATION) || (bondFlags & BondPropertyFlag::CONFIGURATION)) {
        Math::Vector3DArray coords;
        
        get3DCoordinates(conf_molgraph, coords);

        if (atomFlags & AtomPropertyFlag::CONFIGURATION) {
            for (auto& atom : tgt_molgraph.getAtoms()) {
                auto& descr = getStereoDescriptor(atom);
                auto config = descr.getConfiguration();
                
                if (config != AtomConfiguration::R && config != AtomConfiguration::S)
                    continue;

                if (calcConfiguration(atom, tgt_molgraph, descr, coords) != config)
                    return false;
            }
        }

        if (bondFlags & BondPropertyFlag::CONFIGURATION) {
            for (auto& bond : tgt_molgraph.getBonds()) {
                auto& descr = getStereoDescriptor(bond);
                auto config = descr.getConfiguration();
                
                if (config != BondConfiguration::CIS && config != BondConfiguration::TRANS)
                    continue;

                if (calcConfiguration(bond, tgt_molgraph, descr, coords) != config)
                    return false;
            }
        }
    }
    
    return true;
}

bool Chem::DefaultMultiConfMoleculeInputProcessor::addConformation(MolecularGraph& tgt_molgraph,
                                                                   MolecularGraph& conf_molgraph) const
{
    if (!isConformation(tgt_molgraph, conf_molgraph))
        return false;

    for (MolecularGraph::AtomIterator tgt_it = tgt_molgraph.getAtomsBegin(), 
             conf_it = conf_molgraph.getAtomsBegin(), tgt_end = tgt_molgraph.getAtomsEnd();
         tgt_it != tgt_end; ++tgt_it, ++conf_it) {

        Atom& tgt_atom = *tgt_it;
        Atom& conf_atom = *conf_it;

        get3DCoordinatesArray(tgt_atom)->addElement(get3DCoordinates(conf_atom));
    }

    return true;
}
