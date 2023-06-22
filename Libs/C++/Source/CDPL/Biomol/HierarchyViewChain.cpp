/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HierarchyViewChain.cpp 
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

#include "CDPL/Biomol/HierarchyViewChain.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


std::size_t Biomol::HierarchyViewChain::getNumFragments() const
{
    initFragmentList();

    return fragments.size();
}

const Biomol::HierarchyViewFragment& Biomol::HierarchyViewChain::getFragment(std::size_t idx) const
{
    initFragmentList();

    if (idx >= fragments.size())
		throw Base::IndexError("HierarchyViewChain: fragment index out of bounds");

    return *fragments[idx];
}

Biomol::HierarchyViewChain::ConstFragmentIterator Biomol::HierarchyViewChain::getFragmentsBegin() const
{
    initFragmentList();

    return ConstFragmentIterator(fragments.begin());
}

Biomol::HierarchyViewChain::ConstFragmentIterator Biomol::HierarchyViewChain::getFragmentsEnd() const
{
    initFragmentList();

    return ConstFragmentIterator(fragments.end());
}

Biomol::HierarchyViewChain::ConstFragmentIterator Biomol::HierarchyViewChain::begin() const
{
    initFragmentList();

    return ConstFragmentIterator(fragments.begin());
}

Biomol::HierarchyViewChain::ConstFragmentIterator Biomol::HierarchyViewChain::end() const
{
    initFragmentList();

    return ConstFragmentIterator(fragments.end());
}

void Biomol::HierarchyViewChain::initFragmentList() const
{
    std::lock_guard<std::mutex> lock(getMutex());

    if (!initFragments)
		return;

    using namespace Chem;

    Util::BitSet vis_atoms(getNumAtoms());
    std::size_t i = 0;

	const std::string& chain_id = getChainID(*this);
	std::size_t model_no = getModelNumber(*this);

    for (Fragment::ConstAtomIterator it = getAtomsBegin(), atoms_end = getAtomsEnd(); it != atoms_end; ++it, i++)
		if (!vis_atoms.test(i)) {
			FragmentPtr frag_ptr(new HierarchyViewFragment());

			setModelNumber(*frag_ptr, model_no);
			setChainID(*frag_ptr, chain_id);

			const Atom& atom = *it;
	    
			frag_ptr->addAtom(atom);
	    
			visitAtom(atom, *frag_ptr, vis_atoms);
	    
			fragments.push_back(frag_ptr);
		}

    initFragments = false;
}

void Biomol::HierarchyViewChain::visitAtom(const Chem::Atom& atom, HierarchyViewFragment& frag, Util::BitSet& vis_atoms) const
{
    using namespace Chem;

	vis_atoms.set(getAtomIndex(atom));

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (!containsBond(bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!containsAtom(nbr_atom))
			continue;

		if (!frag.containsBond(bond))
			frag.addBond(bond);

		if (!vis_atoms.test(getAtomIndex(nbr_atom))) 
		    visitAtom(nbr_atom, frag, vis_atoms);
	}
}
