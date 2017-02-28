/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AromaticSubstructure.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Chem/AromaticSubstructure.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"

#include "AromaticityPerception.hpp"


using namespace CDPL;


namespace
{

	const std::size_t MAX_NUM_UNIQUE_RING_SYSTEMS = 300000;
}


Chem::AromaticSubstructure::AromaticSubstructure(const MolecularGraph& molgraph)
{
	perceive(molgraph);
}

void Chem::AromaticSubstructure::perceive(const MolecularGraph& molgraph)
{
	clear();

	if (molgraph.getNumAtoms() == 0 || molgraph.getNumBonds() == 0)
		return;

	init(molgraph);
	findAromaticSubstructure();
	freeMemory();
}

void Chem::AromaticSubstructure::freeMemory()
{
	ringDescrListTable.clear();
	uniqueRingSet.clear();
}

void Chem::AromaticSubstructure::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	const FragmentList::BaseType& sssr = *getSSSR(molgraph);

	std::size_t num_bonds = molgraph.getNumBonds();

	if (!aromBondMask.empty()) {
		aromBondMask.clear();
		ringBondMask.clear();
	}

	aromBondMask.resize(num_bonds);
	ringBondMask.resize(num_bonds);

	freeMemory();

	ringDescrListTable.reserve(sssr.getSize());
	ringDescrListTable.push_back(RingDescriptorListTable::value_type(RingDescriptorList(), 0));

	RingDescriptorList& first_rdlist = ringDescrListTable.front().first;
	FragmentList::BaseType::ConstElementIterator sssr_end = sssr.getElementsEnd();

	for (FragmentList::BaseType::ConstElementIterator it = sssr.getElementsBegin(); it != sssr_end; ++it) {
		const Fragment::SharedPointer& ring_ptr = *it;
		std::size_t num_ring_bonds = ring_ptr->getNumBonds();

		if (num_ring_bonds == 0 || num_ring_bonds != ring_ptr->getNumAtoms()) // sanity check
			continue;

		if (isNotAromatic(molgraph, *ring_ptr))
			continue;

		RingDescriptor::SharedPointer ring_descr_ptr(new RingDescriptor(ring_ptr, molgraph));
		const Util::BitSet& bond_mask = ring_descr_ptr->getBondMask();

		if (!uniqueRingSet.insert(bond_mask).second) // already seen this ring (should never happen)? 
			continue;

		ringBondMask |= bond_mask;

		first_rdlist.push_back(ring_descr_ptr);
	}
}

void Chem::AromaticSubstructure::findAromaticSubstructure()
{
	finished = false;

	do {
		RingDescriptorListTable::reverse_iterator rdlist_tab_end = ringDescrListTable.rend();
		
		while (true) {
			bool changes = false;

			for (RingDescriptorListTable::reverse_iterator it = ringDescrListTable.rbegin(); !finished && it != rdlist_tab_end; ++it)
				changes |= findAromaticRings(*it);

			if (finished)
				break;

			if (!changes)
				break;
		}

		if (!finished) {
			fuseRings();
			
			if (uniqueRingSet.size() > MAX_NUM_UNIQUE_RING_SYSTEMS) 
				break;
		}

	} while (!finished);

	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!aromBondMask.test(molGraph->getBondIndex(bond)))
			continue;

		addBond(bond);
	}
}

bool Chem::AromaticSubstructure::findAromaticRings(RingDescriptorListTable::value_type& rdlist_tab_entry)
{
	bool changes = false;

	RingDescriptorList& rdlist = rdlist_tab_entry.first;

	RingDescriptorList::iterator rings_end = rdlist.end();
	RingDescriptorList::iterator rings_beg = rdlist.begin();
	RingDescriptorList::iterator arom_rings_end = rings_beg + rdlist_tab_entry.second;

	while (true) {
		RingDescriptorList::iterator next_arom_rings_end = std::partition(arom_rings_end, rings_end, 
																		  boost::bind(&AromaticSubstructure::isAromatic, 
																					  this, _1));
		if (aromBondMask == ringBondMask) {
			finished = true; // ok, all ring bonds are aromatic -> nothing left to do
			return true;
		}

		if (next_arom_rings_end == arom_rings_end)
			break;

		arom_rings_end = next_arom_rings_end;
		changes = true;
	}

	rdlist_tab_entry.second = arom_rings_end - rings_beg;

	return changes;
}

void Chem::AromaticSubstructure::fuseRings()
{
	ringDescrListTable.push_back(RingDescriptorListTable::value_type(RingDescriptorList(), 0));

	const RingDescriptorListTable::value_type& last_rdlist_entry = *(ringDescrListTable.end() - 2);
	const RingDescriptorListTable::value_type& first_rdlist_entry = ringDescrListTable.front();
	RingDescriptorListTable::value_type& next_rdlist_entry = ringDescrListTable.back();

	const RingDescriptorList& first_rdlist = first_rdlist_entry.first;
	const RingDescriptorList& last_rdlist = last_rdlist_entry.first;
	RingDescriptorList& next_rdlist = next_rdlist_entry.first;

	for (RingDescriptorList::const_iterator it1 = first_rdlist.begin() , end1 = first_rdlist.end(); it1 != end1; ++it1) {
		const RingDescriptor& ring_descr1 = **it1;

		for (RingDescriptorList::const_iterator it2 = last_rdlist.begin(), end2 = last_rdlist.end(); it2 != end2; ++it2) {
			const RingDescriptor& ring_descr2 = **it2;
			
			if (&ring_descr1 == &ring_descr2)
				continue;

			fuseRings(ring_descr1, ring_descr2, next_rdlist);
		}
	}

	finished = next_rdlist.empty();
}

void Chem::AromaticSubstructure::fuseRings(const RingDescriptor& ring_descr1, const RingDescriptor& ring_descr2, 
										   RingDescriptorList& rdlist)
{
	tmpBondMask = ring_descr1.getBondMask();
	tmpBondMask &= ring_descr2.getBondMask();

	if (tmpBondMask.none()) // any bonds in common?
		return;

	if (ring_descr2.containsSubRing(ring_descr1)) // is ring2 already the product of a fusion with ring1? 
		return;

	const Fragment& ring1 = ring_descr1.getRing();

	std::size_t num_ring1_bonds = ring1.getNumBonds();
	std::size_t num_term_atoms = 0;

	const Atom* atom = 0;

	for (std::size_t i = 0; i < num_ring1_bonds; i++) {  // check if the fusion bonds form a single chain!
		if (!tmpBondMask.test(molGraph->getBondIndex(ring1.getBond(i))))
			continue;

		atom = &ring1.getAtom(i);

		if (!tmpBondMask.test(molGraph->getBondIndex(ring1.getBond((i + 1) % num_ring1_bonds))))
			num_term_atoms++;

		if (!tmpBondMask.test(molGraph->getBondIndex(ring1.getBond((i + num_ring1_bonds - 1) % num_ring1_bonds))))
			num_term_atoms++;

		if (num_term_atoms > 2)
			return;
	}

	tmpBondMask = ring_descr1.getBondMask();
	tmpBondMask ^= ring_descr2.getBondMask();

	if (!uniqueRingSet.insert(tmpBondMask).second) // already seen this ring?
		return;

	Fragment::SharedPointer ring_ptr(new Fragment());
	Fragment& ring = *ring_ptr;

	ring.addAtom(*atom);

	while (true) {
		Atom::ConstBondIterator bonds_end = atom->getBondsEnd();
		Atom::ConstBondIterator it = atom->getBondsBegin();

		for ( ; it != bonds_end; ++it) {
			const Bond& bond = *it;

			if (!ring.containsBond(bond) && molGraph->containsBond(bond) && 
				tmpBondMask.test(molGraph->getBondIndex(bond))) {
				
				ring.addBond(bond);
				atom = &bond.getNeighbor(*atom);
				break;
			}
		}

		if (it == bonds_end)
			break;
	}

	rdlist.push_back(RingDescriptor::SharedPointer(new RingDescriptor(ring_ptr, tmpBondMask, ring_descr1, ring_descr2)));
}

bool Chem::AromaticSubstructure::isAromatic(const RingDescriptor::SharedPointer& ring_descr)
{
	if (!Chem::isAromatic(*molGraph, ring_descr->getRing(), aromBondMask))
		return false;

	aromBondMask |= ring_descr->getBondMask();
	return true;
}


Chem::AromaticSubstructure::RingDescriptor::RingDescriptor(const Fragment::SharedPointer& ring_ptr, const MolecularGraph& molgraph): 
	ringPtr(ring_ptr), subRing1(0), subRing2(0), bondMask(molgraph.getNumBonds()), aromatic(false) 
{
	std::for_each(ringPtr->getBondsBegin(), ringPtr->getBondsEnd(),
				  boost::bind(&Util::BitSet::set, boost::ref(bondMask),
							  boost::bind(&BondContainer::getBondIndex, boost::ref(molgraph), _1), true));
}

Chem::AromaticSubstructure::RingDescriptor::RingDescriptor(const Fragment::SharedPointer& ring_ptr, Util::BitSet& bond_mask,
														   const RingDescriptor& sub_ring1, const RingDescriptor& sub_ring2):
	ringPtr(ring_ptr), subRing1(&sub_ring1), subRing2(&sub_ring2), aromatic(false) 
{
	bondMask.swap(bond_mask);
}

const Chem::Fragment& Chem::AromaticSubstructure::RingDescriptor::getRing() const
{
	return *ringPtr;
}

const Util::BitSet& Chem::AromaticSubstructure::RingDescriptor::getBondMask() const
{
	return bondMask;
}

bool Chem::AromaticSubstructure::RingDescriptor::containsSubRing(const RingDescriptor& ring_descr) const
{
	if (this == &ring_descr)
		return true;

	if (subRing1 && subRing1->containsSubRing(ring_descr))
		return true;

	if (subRing2 && subRing2->containsSubRing(ring_descr))
		return true;

	return false;
}
