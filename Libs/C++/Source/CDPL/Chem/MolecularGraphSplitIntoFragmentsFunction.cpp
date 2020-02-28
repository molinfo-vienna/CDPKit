/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphSplitIntoFragmentsFunction.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


namespace
{

    void visitAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& frag, 
				   const Util::BitSet& split_bond_mask, Util::BitSet& vis_atom_mask)
    {
		using namespace Chem;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Bond& bond = *b_it;

			if (!molgraph.containsBond(bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			if (!frag.containsBond(bond))
				frag.addBond(bond);

			if (split_bond_mask.test(molgraph.getBondIndex(bond)))
				continue;

			std::size_t nbr_atom_idx = molgraph.getAtomIndex(nbr_atom);

			if (!vis_atom_mask.test(nbr_atom_idx)) { 
				vis_atom_mask.set(nbr_atom_idx);
				visitAtom(nbr_atom, molgraph, frag, split_bond_mask, vis_atom_mask);
			}
		}
    }
}


void Chem::splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list, 
							  const Util::BitSet& split_bond_mask, bool append)
{
    if (!append)
		frag_list.clear();

    std::size_t num_atoms = molgraph.getNumAtoms();
    Util::BitSet vis_atom_mask(num_atoms);

    for (std::size_t i = 0; i < num_atoms; i++) {
		if (!vis_atom_mask.test(i)) {
			Fragment::SharedPointer frag_ptr(new Fragment());
			const Atom& atom = molgraph.getAtom(i);

			frag_ptr->addAtom(atom);

			vis_atom_mask.set(i);
			visitAtom(atom, molgraph, *frag_ptr, split_bond_mask, vis_atom_mask);
			
			frag_list.addElement(frag_ptr);
		}
    }
}
