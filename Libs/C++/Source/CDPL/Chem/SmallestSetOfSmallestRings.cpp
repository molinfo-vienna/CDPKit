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
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Util/RangeGenerator.hpp"


using namespace CDPL;


Chem::SmallestSetOfSmallestRings::SmallestSetOfSmallestRings(const MolecularGraph& molgraph)
{
	perceive(molgraph);
}

void Chem::SmallestSetOfSmallestRings::perceive(const MolecularGraph& molgraph)
{
	clear();

	if (molgraph.getNumAtoms() == 0 || molgraph.getNumBonds() == 0)
		return;

	init(molgraph);
	findSSSR();
	createRingFragments();
}

void Chem::SmallestSetOfSmallestRings::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	long nullity = calcCyclomaticNumber(molgraph);

	sssr.clear();

	procRings.clear();
	evenRings.clear();
	linDepTestMtx.clear();
	freeMessages.clear();
	freeMessages.reserve(allocMessages.size());

	std::transform(allocMessages.begin(), allocMessages.end(), std::back_inserter(freeMessages),
				   std::mem_fun_ref(&PathMessage::SharedPointer::get));

	testRing = allocMessage();
	linDepTestRing = allocMessage();

	std::size_t num_atoms = molgraph.getNumAtoms();
	std::size_t num_bonds = molgraph.getNumBonds();

	nodes.clear();
	nodes.reserve(num_atoms);

	std::generate_n(std::back_inserter(nodes), num_atoms, Util::RangeGenerator<std::size_t>());

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom1) || !molgraph.containsAtom(atom2)) {
			nullity--;
			continue;
		}

		std::size_t atom1_idx = molgraph.getAtomIndex(atom1);
		std::size_t atom2_idx = molgraph.getAtomIndex(atom2);

		if (atom1_idx == atom2_idx) {
			nullity--;
			continue;
		}

		TNode::connect(this, &nodes[atom1_idx], &nodes[atom2_idx], molgraph.getBondIndex(bond), num_bonds);
	}

	assert(nullity >= 0);

	sssrSize = std::size_t(nullity);
}

void Chem::SmallestSetOfSmallestRings::findSSSR()
{
	MolecularGraph::ConstAtomIterator atoms_beg = molGraph->getAtomsBegin();
	MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();

	while (!sssrComplete()) {
		for (MolecularGraph::ConstAtomIterator a_it = atoms_beg; a_it != atoms_end; ++a_it)
			nodes[molGraph->getAtomIndex(*a_it)].send(this);

		for (MolecularGraph::ConstAtomIterator a_it = atoms_beg; a_it != atoms_end; ++a_it)
			if (nodes[molGraph->getAtomIndex(*a_it)].receive(this))
				return;

		processEvenRings();
	}
}

void Chem::SmallestSetOfSmallestRings::createRingFragments()
{
	MessageList::const_iterator sssr_end = sssr.end();

	for (MessageList::const_iterator it = sssr.begin(); it != sssr_end; ++it)
		addElement((*it)->createRing(molGraph));
}

inline bool Chem::SmallestSetOfSmallestRings::sssrComplete() const
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

Chem::SmallestSetOfSmallestRings::PathMessage* Chem::SmallestSetOfSmallestRings::allocMessage(const TNode* first_node, std::size_t first_bnd_idx, 
																							  std::size_t max_num_bonds)
{
	if (freeMessages.empty()) {
		PathMessage::SharedPointer msg_ptr(new PathMessage(first_node, first_bnd_idx, max_num_bonds));
		
		allocMessages.push_back(msg_ptr);

		return msg_ptr.get();
	}

	PathMessage* msg = freeMessages.back();

	msg->init(first_node, first_bnd_idx, max_num_bonds);

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


void Chem::SmallestSetOfSmallestRings::TNode::send(Controller* controller)
{
	std::size_t num_nbr_nodes = nbrNodes.size();
	std::size_t num_messages = sendBuffer.size();

	if (num_nbr_nodes == 1) {
		if (num_messages > 0) 
			controller->freeMessage(sendBuffer.front());

	} else {
		for (std::size_t i = 0; i < num_messages; i++) {
			PathMessage* msg = sendBuffer[i];
	
			for (std::size_t j = 0; j < num_nbr_nodes; j++) {
				TNode* nbr_node = nbrNodes[j];

				if (nbr_node == msg->getLastNode() || nbr_node == msg->getFirstNode()) // check message return to sender cases
					continue;

				std::size_t bond_idx = bondIndices[j]; 

				if (msg->containsBond(bond_idx)) // check bond path collision
					continue;

				PathMessage* new_msg = controller->allocMessage();		

				new_msg->copy(msg);
				new_msg->push(this, bond_idx);
		
				nbr_node->receiveBuffer.push_back(new_msg);
			}

			controller->freeMessage(msg);
		}
	}

	sendBuffer.clear();
}

bool Chem::SmallestSetOfSmallestRings::TNode::receive(Controller* controller)
{
	mergeBuffer.clear();

	MessageBuffer::iterator rcv_buf_end = receiveBuffer.end();

	for (MessageBuffer::iterator it = receiveBuffer.begin(); it != rcv_buf_end; ++it) {
		PathMessage* msg1 = *it;

		if (msg1->collided()) {
			controller->freeMessage(msg1);
			continue;
		}

		const TNode* first_node = msg1->getFirstNode();

		std::size_t first_bnd_idx = msg1->getFirstBondIndex();

		for (MessageBuffer::iterator it2 = it + 1; it2 != rcv_buf_end; ++it2) {
			PathMessage* msg2 = *it2;

			if (!msg2->collided() && first_node == msg2->getFirstNode() 
				&& first_bnd_idx == msg2->getFirstBondIndex()) 		// direct edge collision

				msg2->setCollisionFlag();
		}

		mergeBuffer.push_back(msg1);
	}

	receiveBuffer.clear();

	MessageBuffer::iterator mrg_buf_end = mergeBuffer.end();

	for (MessageBuffer::iterator it = mergeBuffer.begin(); it != mrg_buf_end; ) {
		PathMessage* msg1 = *it;
		const TNode* first_node = msg1->getFirstNode();
		std::size_t first_bnd_idx = msg1->getFirstBondIndex();

		for (MessageBuffer::iterator it2 = ++it; it2 != mrg_buf_end; ++it2) {
			PathMessage* msg2 = *it2;

			if (first_node == msg2->getFirstNode()) {				 // node collision
				if (controller->processCollision(msg1, msg2, false))				
					return true;

			} else if (first_bnd_idx == msg2->getFirstBondIndex()) {  // inverse edge collision
				if (controller->processCollision(msg1, msg2, true))				
					return true; 

			} else
				continue;

			msg1->setCollisionFlag();
			msg2->setCollisionFlag();
		}

		if (msg1->collided())
			controller->freeMessage(msg1);
		else
			sendBuffer.push_back(msg1);
	}

	return false;
}

std::size_t Chem::SmallestSetOfSmallestRings::TNode::getIndex() const
{
	return index;
}

void Chem::SmallestSetOfSmallestRings::TNode::connect(Controller* controller, TNode* node1, TNode* node2, 
													  std::size_t bond_idx, std::size_t max_num_bonds)
{
	node1->nbrNodes.push_back(node2);
	node2->nbrNodes.push_back(node1);

	node1->bondIndices.push_back(bond_idx);
	node2->bondIndices.push_back(bond_idx);

	node1->sendBuffer.push_back(controller->allocMessage(node2, bond_idx, max_num_bonds));	
	node2->sendBuffer.push_back(controller->allocMessage(node1, bond_idx, max_num_bonds));	
}


Chem::SmallestSetOfSmallestRings::PathMessage::PathMessage(const TNode* first_node, std::size_t first_bnd_idx, std::size_t max_num_bonds) 
{
	init(first_node, first_bnd_idx, max_num_bonds);
} 

void Chem::SmallestSetOfSmallestRings::PathMessage::init(const TNode* first_node, std::size_t first_bnd_idx, std::size_t max_num_bonds)
{
	bondPath.resize(max_num_bonds);
	bondPath.reset();
	bondPath.set(first_bnd_idx);

	firstBondIdx = first_bnd_idx;
	maxBondIdx = first_bnd_idx + 1;
	firstNode = first_node;
	lastNode = first_node;
	collFlag = false;
}

void Chem::SmallestSetOfSmallestRings::PathMessage::push(const TNode* last_node, std::size_t idx)
{
	lastNode = last_node;

	bondPath.set(idx);

	maxBondIdx = std::max(maxBondIdx, idx + 1);

	collFlag = false;
}

void Chem::SmallestSetOfSmallestRings::PathMessage::copy(const PathMessage* msg)
{
	bondPath = msg->bondPath;

	firstBondIdx = msg->firstBondIdx;
	maxBondIdx = msg->maxBondIdx;

	firstNode = msg->firstNode;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::join(const PathMessage* msg1, const PathMessage* msg2)
{
	bondPath = msg1->bondPath;

	bondPath.reset(msg1->firstBondIdx);
	bondPath &= msg2->bondPath;

	if (bondPath.any())  // messages contain common bonds other than the first
		return false;

	bondPath = msg1->bondPath;

	bondPath |= msg2->bondPath;

	firstNode = msg1->firstNode;

	maxBondIdx = std::max(msg1->maxBondIdx, msg2->maxBondIdx);

	return true;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::containsBond(std::size_t bond_idx)
{
	return bondPath.test(bond_idx);
}

void Chem::SmallestSetOfSmallestRings::PathMessage::setCollisionFlag()
{
	collFlag = true;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::collided() const
{
	return collFlag;
}

const Chem::SmallestSetOfSmallestRings::TNode* Chem::SmallestSetOfSmallestRings::PathMessage::getFirstNode() const
{
	return firstNode;
}

const Chem::SmallestSetOfSmallestRings::TNode* Chem::SmallestSetOfSmallestRings::PathMessage::getLastNode() const
{
	return lastNode;
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getFirstBondIndex() const
{
	return firstBondIdx;
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getMaxBondIndex() const
{
	return maxBondIdx;
}

std::size_t Chem::SmallestSetOfSmallestRings::PathMessage::getSize() const
{
	return bondPath.count();
}

Chem::Fragment::SharedPointer Chem::SmallestSetOfSmallestRings::PathMessage::createRing(const MolecularGraph* molgraph) const
{
	Fragment::SharedPointer ring_ptr(new Fragment());
	Fragment& ring = *ring_ptr;

	const Atom* atom = &molgraph->getAtom(firstNode->getIndex());

	ring.addAtom(*atom);

	while (true) {
		Atom::ConstBondIterator bonds_end = atom->getBondsEnd();
		Atom::ConstBondIterator it = atom->getBondsBegin();

		for ( ; it != bonds_end; ++it) {
			const Bond& bond = *it;

			if (!molgraph->containsBond(bond))
				continue;

			if (!ring.containsBond(bond) && bondPath.test(molgraph->getBondIndex(bond))) {
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


inline bool Chem::SmallestSetOfSmallestRings::TestMatrixRowCmpFunc::operator()(const PathMessage* msg1, const PathMessage* msg2) const
{
	return (msg1->getMaxBondIndex() > msg2->getMaxBondIndex());
}


inline bool Chem::SmallestSetOfSmallestRings::PathMessage::LessCmpFunc::operator()(const PathMessage* msg1, const PathMessage* msg2) const
{
	return (msg1->bondPath < msg2->bondPath);
}
