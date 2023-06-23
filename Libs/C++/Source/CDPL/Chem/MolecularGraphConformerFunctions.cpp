/* 
 * MolecularGraphConformerFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


void Chem::setConformation(MolecularGraph& molgraph, std::size_t conf_idx, const Math::Vector3DArray& coords, double energy)
{
    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++)
        (*get3DCoordinatesArray(molgraph.getAtom(i)))[conf_idx] = coords[i];

    (*getConformerEnergies(molgraph))[conf_idx] = energy;
}

void Chem::addConformation(MolecularGraph& molgraph, const Math::Vector3DArray& coords, double energy)
{
    std::size_t i = 0;
    
    for (MolecularGraph::AtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it, i++) {
        Atom& atom = *it;
        Math::Vector3DArray::SharedPointer coords_array;

        if (!has3DCoordinatesArray(atom)) {
            coords_array.reset(new Math::Vector3DArray());

            set3DCoordinatesArray(atom, coords_array);

        } else
            coords_array = get3DCoordinatesArray(atom);
        
        coords_array->addElement(coords[i]);
    }

    Util::DArray::SharedPointer energy_array;

    if (!hasConformerEnergies(molgraph)) {
        energy_array.reset(new Util::DArray());

        setConformerEnergies(molgraph, energy_array);

    } else
        energy_array = getConformerEnergies(molgraph);

    energy_array->addElement(energy);
}

double Chem::getConformationEnergy(const MolecularGraph& molgraph, std::size_t conf_idx)
{
    return (*getConformerEnergies(molgraph))[conf_idx];
}
