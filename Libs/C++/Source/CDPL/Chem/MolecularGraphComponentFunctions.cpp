/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphComponentFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ComponentSet.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


namespace
{

	void visitAtom(const Chem::Atom& atom, Util::BitSet& vis_atoms, const Chem::MolecularGraph& molgraph)
	{
		using namespace Chem;

		vis_atoms.set(molgraph.getAtomIndex(atom));

		Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
		Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
			const Bond& bond = *b_it;

			if (!molgraph.containsBond(bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			if (!vis_atoms.test(molgraph.getAtomIndex(nbr_atom)))
				visitAtom(nbr_atom, vis_atoms, molgraph);
		}
	}
}


Chem::FragmentList::SharedPointer Chem::perceiveComponents(const MolecularGraph& molgraph)
{
	FragmentList::SharedPointer comps_ptr(new ComponentSet(molgraph));

	return comps_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveComponents(MolecularGraph& molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Variant prev_comps = molgraph.getProperty(MolecularGraphProperty::COMPONENTS, false);
	
		if (!prev_comps.isEmpty())
			return prev_comps.getData<FragmentList::SharedPointer>();
	}

	FragmentList::SharedPointer comps_ptr(new ComponentSet(molgraph));

	molgraph.setProperty(MolecularGraphProperty::COMPONENTS, comps_ptr);

	return comps_ptr;
}

std::size_t Chem::getComponentCount(const MolecularGraph& molgraph)
{
	Util::BitSet vis_atoms(molgraph.getNumAtoms());

	std::size_t count = 0;
	std::size_t i = 0;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();
	
	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it, i++) {
		const Atom& atom = *it;

		if (!vis_atoms.test(i)) {
			count++;
			visitAtom(atom, vis_atoms, molgraph);
		}
	}

	return count;
}
