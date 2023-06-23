/* 
 * AtomMarkReachableAtomsFunction.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


void Chem::markReachableAtoms(const Atom& atom, const MolecularGraph& molgraph, Util::BitSet& atom_mask, bool reset)
{
    std::size_t num_atoms = molgraph.getNumAtoms();

    if (atom_mask.size() < num_atoms)
        atom_mask.resize(num_atoms);

    if (reset)
        atom_mask.reset();

    atom_mask.set(molgraph.getAtomIndex(atom));

    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        const Atom& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;

        if (!molgraph.containsBond(*b_it))
            continue;

        std::size_t atom_idx = molgraph.getAtomIndex(nbr_atom);

        if (atom_mask.test(atom_idx))
            continue;

        atom_mask.set(atom_idx);

        markReachableAtoms(nbr_atom, molgraph, atom_mask, false);
    }
}

