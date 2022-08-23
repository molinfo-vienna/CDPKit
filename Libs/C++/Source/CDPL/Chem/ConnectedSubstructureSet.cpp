/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConnectedSubstructureSet.cpp
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

#include <algorithm>
#include <iterator>
#include <set>

#include "CDPL/Chem/ConnectedSubstructureSet.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


namespace
{

	const std::size_t MAX_SUBSTRUCT_DESCR_CACHE_SIZE = 5000;
}


using namespace CDPL;


Chem::ConnectedSubstructureSet::ConnectedSubstructureSet(): 
	substructDescrCache(MAX_SUBSTRUCT_DESCR_CACHE_SIZE), currSubstructSize(0), molGraph(0) 
{}

Chem::ConnectedSubstructureSet::ConnectedSubstructureSet(const MolecularGraph& molgraph): 
	substructDescrCache(MAX_SUBSTRUCT_DESCR_CACHE_SIZE), currSubstructSize(0), molGraph(&molgraph) 
{
	bondMask.resize(molgraph.getNumBonds());
}

void Chem::ConnectedSubstructureSet::reset(const MolecularGraph& molgraph)
{
	bondMask.resize(molgraph.getNumBonds());

	if (molGraph)
		reset();
	else
		currSubstructSize = 0;

	molGraph = &molgraph;
}

void Chem::ConnectedSubstructureSet::findSubstructures(std::size_t size)
{
	if (!molGraph)
		return;

	growSubstructDescriptors(size);
	createSubstructFragments();
}

std::size_t Chem::ConnectedSubstructureSet::getSubstructureSize() const
{
	return currSubstructSize;
}

void Chem::ConnectedSubstructureSet::reset()
{
	currSubstructSize = 0;

	bondMask.reset();
	foundSubstructDescriptors.clear();
}

void Chem::ConnectedSubstructureSet::growSubstructDescriptors(std::size_t size)
{
	if (size < currSubstructSize) 
		reset();

	typedef std::set<SubstructDescriptorPtr, SubstructDescriptorLessCmpFunc> UniqueSubstructDescriptorList;

	UniqueSubstructDescriptorList grown_substruct_descrs;
	
	for ( ; currSubstructSize < size; currSubstructSize++) {
		if (currSubstructSize == 0) {
			std::size_t i = 0;
			MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

			for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it, i++) {
				const Bond& bond = *it;
			
				if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
					continue;

				foundSubstructDescriptors.push_back(allocSubstructDescriptor(bond));
				bondMask.set(i);
			}

			continue;
		}

		SubstructDescriptorList::const_iterator descr_list_end = foundSubstructDescriptors.end();

		for (SubstructDescriptorList::const_iterator it = foundSubstructDescriptors.begin(); it != descr_list_end; ++it) {
			const SubstructDescriptorPtr& substruct_descr = *it; 

			while (substruct_descr->grow(bondMask)) {
				UniqueSubstructDescriptorList::iterator lb = grown_substruct_descrs.lower_bound(substruct_descr);

				if (lb == grown_substruct_descrs.end() || grown_substruct_descrs.key_comp()(substruct_descr, *lb)) {
					SubstructDescriptorPtr new_substruct_descr = substructDescrCache.get();

					new_substruct_descr->copy(*substruct_descr);
					grown_substruct_descrs.insert(lb, new_substruct_descr);
				} 

				substruct_descr->ungrow();
			}
		}

		foundSubstructDescriptors.clear();
		foundSubstructDescriptors.insert(foundSubstructDescriptors.end(), 
										 grown_substruct_descrs.begin(), grown_substruct_descrs.end());

		grown_substruct_descrs.clear();
	}
}

void Chem::ConnectedSubstructureSet::createSubstructFragments()
{
	SubstructDescriptorList::const_iterator frags_end = foundSubstructDescriptors.end();

	for (SubstructDescriptorList::const_iterator it = foundSubstructDescriptors.begin(); it != frags_end; ++it)
		addElement((*it)->createFragment());
}

Chem::ConnectedSubstructureSet::SubstructDescriptorPtr Chem::ConnectedSubstructureSet::allocSubstructDescriptor(const Bond& bond)
{
	SubstructDescriptorPtr substruct_descr = substructDescrCache.get();

	substruct_descr->init(molGraph, bond);

	return substruct_descr;
}


void Chem::ConnectedSubstructureSet::SubstructDescriptor::init(const MolecularGraph* molgraph, const Bond& bond) 
{
	molGraph = molgraph;

	bondMask.resize(molgraph->getNumBonds());
	bondMask.reset();
	bondMask.set(molgraph->getBondIndex(bond));

	unsatAListIdx = 0;
	nbrBListIdx = 0;

	unsatAtoms.clear();
	atomBondCounts.clear();

	startAtom = &bond.getBegin();

	if (Internal::getExplicitBondCount(*startAtom, *molgraph) > 1) {
		unsatAtoms.push_back(startAtom);
		atomBondCounts.push_back(1);
	}

	const Atom* atom2 = &bond.getEnd();

	if (Internal::getExplicitBondCount(*atom2, *molgraph) > 1) {
		unsatAtoms.push_back(atom2);
		atomBondCounts.push_back(1);
	}
}

bool Chem::ConnectedSubstructureSet::SubstructDescriptor::grow(const Util::BitSet& molgraph_bond_mask)
{
	std::size_t num_unsat_atoms = unsatAtoms.size();

	for ( ; unsatAListIdx < num_unsat_atoms; unsatAListIdx++) {
		const Atom* atom = unsatAtoms[unsatAListIdx];
		std::size_t num_bonds = atom->getNumBonds();

		for ( ; nbrBListIdx < num_bonds; nbrBListIdx++) {
			const Bond& bond = atom->getBond(nbrBListIdx);
			
			if (!molGraph->containsBond(bond))
				continue;

			lastBondIdx = molGraph->getBondIndex(bond);

			if (!molgraph_bond_mask.test(lastBondIdx) || bondMask.test(lastBondIdx))
				continue;
			
			bondMask.set(lastBondIdx);

			const Atom& nbr_atom = atom->getAtom(nbrBListIdx);

			if (Internal::getExplicitBondCount(nbr_atom, *molGraph) > 1) {
				unsatAtoms.push_back(&nbr_atom);
				atomBondCounts.push_back(1);

				addedAtom = true;

			} else
				addedAtom = false;

			if (++atomBondCounts[unsatAListIdx] == Internal::getExplicitBondCount(*atom, *molGraph))
				nbrBListIdx = num_bonds;
			else 
				nbrBListIdx++;
		 
			return true;
		}
		
		nbrBListIdx = 0;
	}

	return false;
}

void Chem::ConnectedSubstructureSet::SubstructDescriptor::ungrow()
{
	bondMask.reset(lastBondIdx);

	if (addedAtom) {
		unsatAtoms.pop_back();
		atomBondCounts.pop_back();
	}

	atomBondCounts[unsatAListIdx]--;
}

Chem::Fragment::SharedPointer Chem::ConnectedSubstructureSet::SubstructDescriptor::createFragment() const
{  
	Fragment::SharedPointer frag_ptr(new Fragment());
	Fragment& frag = *frag_ptr;

	AtomList atoms;
	AtomList next_atoms;

	next_atoms.push_back(startAtom);

	for (std::size_t num_atoms = 1; num_atoms > 0; num_atoms = next_atoms.size()) {
		atoms.swap(next_atoms);
		next_atoms.clear();

		AtomList::const_iterator atoms_end = atoms.end(); 

		for (AtomList::const_iterator it1 = atoms.begin(); it1 != atoms_end; ++it1) {
			const Atom* atom = *it1;

			Atom::ConstBondIterator bonds_end = atom->getBondsEnd();

			for (Atom::ConstBondIterator it2 = atom->getBondsBegin(); it2 != bonds_end; ++it2) {
				const Bond& bond = *it2;

				if (!molGraph->containsBond(bond))
					continue;

				if (bondMask.test(molGraph->getBondIndex(bond)) && !frag.containsBond(bond)) {
					const Atom& nbr_atom = bond.getNeighbor(*atom);
					bool nbr_visited = frag.containsAtom(nbr_atom);

					frag.addBond(bond);

					if (nbr_visited)
						continue;

					next_atoms.push_back(&nbr_atom);
				}
			}
		}
	}

	return frag_ptr;
}

void Chem::ConnectedSubstructureSet::SubstructDescriptor::copy(const SubstructDescriptor& descr)
{
	unsatAListIdx = 0;
	nbrBListIdx = 0;

	molGraph = descr.molGraph;
	bondMask = descr.bondMask;
	startAtom = descr.startAtom;

	if (descr.atomBondCounts[descr.unsatAListIdx] < Internal::getExplicitBondCount(*descr.unsatAtoms[descr.unsatAListIdx], *molGraph)) {
		unsatAtoms = descr.unsatAtoms;
		atomBondCounts = descr.atomBondCounts;

	} else {
		unsatAtoms.clear();
		atomBondCounts.clear();

		std::copy(descr.unsatAtoms.begin(), descr.unsatAtoms.begin() + descr.unsatAListIdx, 
				  std::back_inserter(unsatAtoms));

		std::copy(descr.atomBondCounts.begin(), descr.atomBondCounts.begin() + descr.unsatAListIdx, 
				  std::back_inserter(atomBondCounts));

		std::copy(descr.unsatAtoms.begin() + descr.unsatAListIdx + 1, descr.unsatAtoms.end(), 
				  std::back_inserter(unsatAtoms));

		std::copy(descr.atomBondCounts.begin() + descr.unsatAListIdx + 1, descr.atomBondCounts.end(), 
				  std::back_inserter(atomBondCounts));
	}
}

bool Chem::ConnectedSubstructureSet::SubstructDescriptor::operator<(const SubstructDescriptor& descr) const
{
	return (bondMask < descr.bondMask);
}


bool Chem::ConnectedSubstructureSet::SubstructDescriptorLessCmpFunc::operator()(const SubstructDescriptorPtr& descr1, 
																				const SubstructDescriptorPtr& descr2) const
{
	return (*descr1 < *descr2);
}
