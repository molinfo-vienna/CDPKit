/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HierarchyViewModel.cpp 
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

#include "CDPL/Biomol/HierarchyViewModel.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


std::size_t Biomol::HierarchyViewModel::getNumChains() const
{
	initChainList();

	return chains.size();
}

const Biomol::HierarchyViewChain& Biomol::HierarchyViewModel::getChain(std::size_t idx) const
{
	initChainList();

	if (idx >= chains.size())
		throw Base::IndexError("HierarchyViewModel: chain index out of bounds");

	return *chains[idx];
}

bool Biomol::HierarchyViewModel::hasChainWithID(const std::string& id) const
{
	initChainList();

	return (idToChainMap.find(id) != idToChainMap.end());
}

const Biomol::HierarchyViewChain& Biomol::HierarchyViewModel::getChainByID(const std::string& id) const
{
	initChainList();

	IDToChainMap::const_iterator it = idToChainMap.find(id);

	if (it != idToChainMap.end())
		return *it->second;

	throw Base::ItemNotFound("HierarchyViewModel: chain with specified ID not found");
}

Biomol::HierarchyViewModel::ConstChainIterator Biomol::HierarchyViewModel::getChainsBegin() const
{
	initChainList();

	return ConstChainIterator(chains.begin());
}

Biomol::HierarchyViewModel::ConstChainIterator Biomol::HierarchyViewModel::getChainsEnd() const
{
	initChainList();

	return ConstChainIterator(chains.end());
}

void Biomol::HierarchyViewModel::initChainList() const
{
    std::lock_guard<std::mutex> lock(getMutex());

    if (!initChains)
		return;

	using namespace Chem;

	std::size_t model_no = getModelNumber(*this);

	for (Fragment::ConstAtomIterator a_it = getAtomsBegin(), a_end = getAtomsEnd(); a_it != a_end; ++a_it) {
		const Atom& atom = *a_it;
		const std::string& chain_id = getChainID(atom);

		IDToChainMap::iterator c_it = idToChainMap.find(chain_id);

		if (c_it != idToChainMap.end()) {
			c_it->second->addAtom(atom);
			continue;
		}

		ChainPtr chain_ptr(new HierarchyViewChain());

		chain_ptr->addAtom(atom);

		setModelNumber(*chain_ptr, model_no);
		setChainID(*chain_ptr, chain_id);

		chains.push_back(chain_ptr);
		idToChainMap.insert(IDToChainMap::value_type(chain_id, chain_ptr));
	}

	for (ChainList::iterator m_it = chains.begin(), m_end = chains.end(); m_it != m_end; ++m_it) {
		HierarchyViewChain& chain = **m_it;

		for (std::size_t i = 0, num_atoms = chain.getNumAtoms(); i < num_atoms; i++) {
			const Atom& atom = chain.getAtom(i);
			Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

			for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
				const Bond& bond = *b_it;

				if (chain.containsBond(bond))
					continue;

				if (!chain.containsAtom(*a_it))
					continue;

				if (!containsBond(bond))
					continue;

				chain.addBond(bond);
			}
		}
	}

    initChains = false;
}
