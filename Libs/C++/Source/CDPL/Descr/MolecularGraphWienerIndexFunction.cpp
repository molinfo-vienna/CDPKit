/* 
 * MolecularGraphWienerIndexFunction.cpp 
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

#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


std::size_t Descr::calcWienerIndex(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    Util::BitSet h_mask(molgraph.getNumAtoms());
    createAtomTypeMask(molgraph, h_mask, AtomType::H);

    MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

    const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);
    std::size_t index = 0;

    for (MolecularGraph::ConstAtomIterator it1 = molgraph.getAtomsBegin(); it1 != atoms_end; ) {
        std::size_t atom1_idx = molgraph.getAtomIndex(*it1);

        if (h_mask.test(atom1_idx))
            continue;

        for (MolecularGraph::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
            std::size_t atom2_idx = molgraph.getAtomIndex(*it2);

            if (h_mask.test(atom2_idx))
                continue;

            index += dist_mtx(atom1_idx, atom2_idx);
        }
    }

    return index;
}
