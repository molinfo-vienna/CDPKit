/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SmallestSetOfSmallestRings.cpp 
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

#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/RangeGenerator.hpp"


using namespace CDPL;


Chem::SmallestSetOfSmallestRings::SmallestSetOfSmallestRings(const MolecularGraph& molgraph)
{
	perceive(molgraph);
}

void Chem::SmallestSetOfSmallestRings::perceive(const MolecularGraph& molgraph)
{
	clear();

	if (molgraph.getNumAtoms() < 3 || molgraph.getNumBonds() < 3)
		return;

	init(molgraph);
	findSSSR();
	createRingFragments();
}

void Chem::SmallestSetOfSmallestRings::init(const MolecularGraph& molgraph)
{
	sssr.clear();
	procRings.clear();
	evenRings.clear();
	linDepTestMtx.clear();
	freeMessages.clear();
	freeMessages.reserve(allocMessages.size());

	std::transform(allocMessages.begin(), allocMessages.end(), std::back_inserter(freeMessages),
				   boost::bind(&PathMessage::SharedPointer::get, _1));

	testRing = allocMessage();
	linDepTestRing = allocMessage();

	cycleSubstruct.perceive(molgraph);

	std::size_t num_atoms = cycleSubstruct.getNumAtoms();
	std::size_t num_bonds = cycleSubstruct.getNumBonds();

	sssrSize = num_bonds + getComponentCount(cycleSubstruct) - num_atoms;

	nodes.clear();
	nodes.reserve(num_atoms);

	std::generate_n(std::back_inserter(nodes), num_atoms, Internal::RangeGenerator<std::size_t>());

	std::size_t bond_idx = 0;
	
	for (Fragment::ConstBondIterator it = cycleSubstruct.getBondsBegin(), end = cycleSubstruct.getBondsEnd(); it != end; ++it, bond_idx++) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		std::size_t atom1_idx = cycleSubstruct.getAtomIndex(atom1);
		std::size_t atom2_idx = cycleSubstruct.getAtomIndex(atom2);

		TNode::connect(this, &nodes[atom1_idx], &nodes[atom2_idx], bond_idx, num_atoms, num_bonds);
	}
}

void Chem::SmallestSetOfSmallestRings::findSSSR()
{
	std::size_t num_nodes = nodes.size();

	while (!sssrComplete()) {
		bool new_messages = false;
		
		for (std::size_t i = 0; i < num_nodes; i++)
			new_messages |= nodes[i].send(this);

		if (!new_messages) 
			throw Base::CalculationFailed("SmallestSetOfSmallestRings: SSSR incomplete");

		for (std::size_t i = 0; i < num_nodes; i++)
			if (nodes[i].receive(this))
				return;
		
		processEvenRings();
	}
}

void Chem::SmallestSetOfSmallestRings::createRingFragments()
{
	MessageList::const_iterator sssr_end = sssr.end();

	for (MessageList::const_iterator it = sssr.begin(); it != sssr_end; ++it)
		addElement((*it)->createRing(cycleSubstruct));
}

bool Chem::SmallestSetOfSmallestRings::sssrComplete() const
{
	return (sssr.size() >= sssrSize);
}

Chem::SmallestSetOfSmallestRings::PathMessage* Chem::SmallestSetOfSmallestRings::allocMessage()
{
	if (freeMessages.empty()) {
		PathMessage::SharedPointer msg_ptr(new PathMessage());
		
		allocMessages.push_back(msg_ptr);

		return msg_ptr.get();
	}

	PathMessage* msg = freeMessages.back();
	freeMessages.pop_back();

	return msg;
}

Chem::SmallestSetOfSmallestRings::PathMessage* Chem::SmallestSetOfSmallestRings::allocMessage(std::size_t first_atom_idx, std::size_t first_bond_idx, 
																							  std::size_t max_num_atoms, std::size_t max_num_bonds)
{
	if (freeMessages.empty()) {
		PathMessage::SharedPointer msg_ptr(new PathMessage(first_atom_idx, first_bond_idx, max_num_atoms, max_num_bonds));
		
		allocMessages.push_back(msg_ptr);

		return msg_ptr.get();
	}

	PathMessage* msg = freeMessages.back();

	msg->init(first_atom_idx, first_bond_idx, max_num_atoms, max_num_bonds);

	freeMessages.pop_back();

	return msg;
}

void Chem::SmallestSetOfSmallestRings::freeMessage(PathMessage* msg)
{
	freeMessages.push_back(msg);
}

bool Chem::SmallestSetOfSmallestRings::processCollision(const PathMessage* msg1, const PathMessage* msg2, bool odd)
{
	if (!testRing->join(msg1, msg2))
		return false;
	
	if (!procRings.insert(testRing).second) 
		return false;

	if (odd)
		processRing(testRing);
	else
		evenRings.push_back(testRing);		

	testRing = allocMessage();
	
	return sssrComplete();
}

void Chem::SmallestSetOfSmallestRings::processEvenRings()
{
	MessageList::iterator ev_rings_end = evenRings.end();

	for (MessageList::iterator it = evenRings.begin(); it != ev_rings_end && !sssrComplete(); ++it)
		processRing(*it);

	evenRings.clear();
}

void Chem::SmallestSetOfSmallestRings::processRing(PathMessage* ring)
{
	TestMatrixRowCmpFunc search_func;

	MessageList::iterator mtx_end = linDepTestMtx.end();
	MessageList::iterator lb = std::lower_bound(linDepTestMtx.begin(), mtx_end, ring, search_func);

	if (lb != mtx_end && !search_func(ring, *lb)) {
		linDepTestRing->copy(ring);

		while (true) {
			*linDepTestRing ^= **lb;
			lb = std::lower_bound(lb, mtx_end, linDepTestRing, search_func);

			if (lb != mtx_end && !search_func(linDepTestRing, *lb)) 
				continue;
			
			if (lb == mtx_end && linDepTestRing->getMaxBondIndex() == 0) 
				return;
			
			linDepTestMtx.insert(lb, linDepTestRing);
			linDepTestRing = allocMessage();
			break;
		}

	} else 
		linDepTestMtx.insert(lb, ring);

	sssr.push_back(ring);
}


bool Chem::SmallestSetOfSmallestRings::TNode::send(Controller* controller)
{
	std::size_t num_nbr_nodes = nbrNodes.size();
	std::size_t num_messages = sendBuffer.size();
	bool new_messages = false;
	
	for (std::size_t i = 0; i < num_messages; i++) {
		PathMessage* msg = sendBuffer[i];

		for (std::size_t j = 0; j < num_nbr_nodes; j++) {
			std::size_t bond_idx = bondIndices[j]; 

			if (msg->containsAtom(nbrNodes[j]->index) | msg->containsBond(bond_idx)) // check path collisions
				continue;

			PathMessage* new_msg = controller->allocMessage();		

			new_msg->copy(msg);
			new_msg->push(index, bond_idx);

			new_messages = true;
			nbrNodes[j]->receiveBuffer.push_back(new_msg);
		}

		controller->freeMessage(msg);
	}

	sendBuffer.clear();

	return new_messages;
}

bool Chem::SmallestSetOfSmallestRings::TNode::receive(Controller* controller)
{
	MessageBuffer::iterator rcv_buf_beg = receiveBuffer.begin();
	MessageBuffer::iterator rcv_buf_end = receiveBuffer.end();

	for (MessageBuffer::iterator it = rcv_buf_beg; it != rcv_buf_end; ) {
		PathMessage* msg1 = *it;
		std::size_t first_atom_idx = msg1->getFirstAtomIndex();
		std::size_t first_bond_idx = msg1->getFirstBondIndex();

		for (MessageBuffer::iterator it2 = ++it; it2 != rcv_buf_end; ++it2) {
			PathMessage* msg2 = *it2;

			if (first_atom_idx == msg2->getFirstAtomIndex()) {		 // node collision
				if (first_bond_idx == msg2->getFirstBondIndex())     // edge collision
					continue;

				if (controller->processCollision(msg1, msg2, false))				
					return true;

			} else if (first_bond_idx == msg2->getFirstBondIndex()) { // inverse edge collision
				if (controller->processCollision(msg1, msg2, true))				
					return true; 
			}                                                        // no collision
		}
	}

	sendBuffer.swap(receiveBuffer);
	receiveBuffer.clear();

	return false;
}

std::size_t Chem::SmallestSetOfSmallestRings::TNode::getIndex() const
{
	return index;
}

void Chem::SmallestSetOfSmallestRings::TNode::connect(Controller* controller, TNode* node1, TNode* node2, 
													  std::size_t bond_idx, std::size_t max_num_atoms,
													  std::size_t max_num_bonds)
{
	node1->nbrNodes.push_back(node2);
	node2->nbrNodes.push_back(node1);

	node1->bondIndices.push_back(bond_idx);
	node2->bondIndices.push_back(bond_idx);

	node1->sendBuffer.push_back(controller->allocMessage(node2->index, bond_idx, max_num_atoms, max_num_bonds));	
	node2->sendBuffer.push_back(controller->allocMessage(node1->index, bond_idx, max_num_atoms, max_num_bonds));	
}


Chem::SmallestSetOfSmallestRings::PathMessage::PathMessage(std::size_t first_atom_idx, std::size_t first_bond_idx,
														   std::size_t max_num_atoms, std::size_t max_num_bonds)
{
	init(first_atom_idx, first_bond_idx, max_num_atoms, max_num_bonds);
} 

void Chem::SmallestSetOfSmallestRings::PathMessage::init(std::size_t first_atom_idx, std::size_t first_bond_idx,
														 std::size_t max_num_atoms, std::size_t max_num_bonds)
{
	atomPath.resize(max_num_atoms);
	atomPath.reset();
	atomPath.set(first_atom_idx);

	bondPath.resize(max_num_bonds);
	bondPath.reset();
	bondPath.set(first_bond_idx);

	firstAtomIdx = first_atom_idx;
	firstBondIdx = first_bond_idx;
	maxBondIdx = first_bond_idx + 1;
}

void Chem::SmallestSetOfSmallestRings::PathMessage::push(std::size_t atom_idx, std::size_t bond_idx)
{
	atomPath.set(atom_idx);
	bondPath.set(bond_idx);

	maxBondIdx = std::max(maxBondIdx, bond_idx + 1);
}

void Chem::SmallestSetOfSmallestRings::PathMessage::copy(const PathMessage* msg)
{
	atomPath = msg->atomPath;
	bondPath = msg->bondPath;
	firstAtomIdx = msg->firstAtomIdx;
	firstBondIdx = msg->firstBondIdx;
	maxBondIdx = msg->maxBondIdx;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::join(const PathMessage* msg1, const PathMessage* msg2)
{
	bondPath = msg1->bondPath;
	bondPath &= msg2->bondPath;

	bondPath.reset(msg1->firstBondIdx);

	if (bondPath.any())   // messages contain common bonds other than the first
		return false;

	atomPath = msg1->atomPath;
	atomPath &= msg2->atomPath;

	atomPath.reset(msg1->firstAtomIdx);
	atomPath.reset(msg2->firstAtomIdx);

	if (atomPath.any())   // messages contain common atoms other than the origin atoms
		return false;

	bondPath = msg1->bondPath;
	bondPath |= msg2->bondPath;

	maxBondIdx = std::max(msg1->maxBondIdx, msg2->maxBondIdx);
	firstAtomIdx = msg1->firstAtomIdx;
		
	return true;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::containsAtom(std::size_t atom_idx)
{
	return atomPath.test(atom_idx);
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::containsBond(std::size_t bond_idx)
{
	return bondPath.test(bond_idx);
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getFirstAtomIndex() const
{
	return firstAtomIdx;
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getFirstBondIndex() const
{
	return firstBondIdx;
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getMaxBondIndex() const
{
	return maxBondIdx;
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getNumBonds() const
{
	return bondPath.count();
}

Chem::Fragment::SharedPointer Chem::SmallestSetOfSmallestRings::PathMessage::createRing(const MolecularGraph& molgraph) const
{
	Fragment::SharedPointer ring_ptr(new Fragment());
	Fragment& ring = *ring_ptr;

	const Atom* atom = &molgraph.getAtom(firstAtomIdx);

	ring.addAtom(*atom);

	while (true) {
		Atom::ConstBondIterator bonds_end = atom->getBondsEnd();
		Atom::ConstBondIterator it = atom->getBondsBegin();

		for ( ; it != bonds_end; ++it) {
			const Bond& bond = *it;

			if (!molgraph.containsBond(bond))
				continue;
			
			if (!ring.containsBond(bond) && bondPath.test(molgraph.getBondIndex(bond))) {
				ring.addBond(bond);
				atom = &bond.getNeighbor(*atom);
				break;
			}
		}

		if (it == bonds_end)
			break;
	}

	return ring_ptr;
}

Chem::SmallestSetOfSmallestRings::PathMessage& Chem::SmallestSetOfSmallestRings::PathMessage::operator^=(const PathMessage& msg)
{
	bondPath ^= msg.bondPath;

	for (maxBondIdx = bondPath.size(); maxBondIdx > 0 && !bondPath.test(maxBondIdx - 1); maxBondIdx--);

	return *this;
}


bool Chem::SmallestSetOfSmallestRings::TestMatrixRowCmpFunc::operator()(const PathMessage* msg1, const PathMessage* msg2) const
{
	return (msg1->getMaxBondIndex() > msg2->getMaxBondIndex());
}


bool Chem::SmallestSetOfSmallestRings::PathMessage::LessCmpFunc::operator()(const PathMessage* msg1, const PathMessage* msg2) const
{
	return (msg1->bondPath < msg2->bondPath);
}
