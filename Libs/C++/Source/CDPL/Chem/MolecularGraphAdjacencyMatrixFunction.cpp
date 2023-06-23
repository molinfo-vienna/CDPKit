/* 
 * MolecularGraphAdjacencyMatrixFunction.cpp 
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
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


void Chem::buildAdjacencyMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx)
{
    std::size_t num_atoms = molgraph.getNumAtoms();

    mtx.resize(num_atoms, num_atoms);
    mtx.clear();

    MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;
        const Atom& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        const Atom& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        std::size_t atom1_idx = molgraph.getAtomIndex(atom1);
        std::size_t atom2_idx = molgraph.getAtomIndex(atom2);

        mtx(atom1_idx, atom2_idx) = 1;
        mtx(atom2_idx, atom1_idx) = 1;
    }
}
