/* 
 * ExtendedConnectivityCalculator.cpp
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

#include <algorithm>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"

#include "ExtendedConnectivityCalculator.hpp"


using namespace CDPL;


void ConfGen::ExtendedConnectivityCalculator::calculate(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    std::size_t num_atoms = molgraph.getNumAtoms();

    hAtomMask.resize(num_atoms);
    hAtomMask.reset();

    createAtomTypeMask(molgraph, hAtomMask, AtomType::H, false);

    ecArray.assign(num_atoms, 1);

    std::size_t last_num_classes = 0;

    while (true) {
        tmpECArray.assign(num_atoms, 0);

        for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
            const Bond& bond = *it;
            std::size_t atom1_idx = molgraph.getAtomIndex(bond.getBegin());

            if (hAtomMask.test(atom1_idx))
                continue;

            std::size_t atom2_idx = molgraph.getAtomIndex(bond.getEnd());
    
            if (hAtomMask.test(atom2_idx))
                continue;

            tmpECArray[atom1_idx] += ecArray[atom2_idx];
            tmpECArray[atom2_idx] += ecArray[atom1_idx];
        }

        ecArray = tmpECArray;

        std::sort(tmpECArray.begin(), tmpECArray.end());

        std::size_t num_classes = 0;
        std::size_t curr_ec = 0;

        for (std::size_t i = 0; i < num_atoms; i++) {
            if (num_classes == 0 || curr_ec != tmpECArray[i]) {
                curr_ec = tmpECArray[i];
                num_classes++;
            }
        }

        if (num_classes <= last_num_classes) 
            break;

        last_num_classes = num_classes;
    }
}
