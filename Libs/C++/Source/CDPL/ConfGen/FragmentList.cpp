/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentList.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/ConfGen/FragmentList.hpp"
#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

using namespace CDPL;


ConfGen::FragmentList::FragmentList(const Chem::MolecularGraph& molgraph)
{
	generate(molgraph);
}

void ConfGen::FragmentList::generate(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	clear();

	if (molgraph.getNumAtoms() == 0)
		return;

	visAtomMask.resize(molgraph.getNumAtoms());
	visAtomMask.reset();

	splitBondMask.resize(molgraph.getNumBonds());
	splitBondMask.reset();

	molGraph = &molgraph;

	std::size_t i = 0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it, i++) {
		const Bond& bond = *it;
		
		if (isFragmentLinkBond(bond, molgraph))
			splitBondMask.set(i);
	}

	i = 0;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it, i++)
		if (!visAtomMask.test(i)) {
			Fragment::SharedPointer frag_ptr(new Fragment());

			const Atom& atom = *it;

			frag_ptr->addAtom(atom);

			visAtomMask.set(i);
			visitAtom(atom, *frag_ptr);
			
			addElement(frag_ptr);
		}
}

void ConfGen::FragmentList::visitAtom(const Chem::Atom& atom, Chem::Fragment& frag)
{
	using namespace Chem;

	Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (!molGraph->containsBond(bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		if (!frag.containsBond(bond))
			frag.addBond(bond);

		if (splitBondMask.test(molGraph->getBondIndex(bond)))
			continue;

		std::size_t nbr_atom_idx = molGraph->getAtomIndex(nbr_atom);

		if (!visAtomMask.test(nbr_atom_idx)) { 
			visAtomMask.set(nbr_atom_idx);
			visitAtom(nbr_atom, frag);
		}
	}
}
