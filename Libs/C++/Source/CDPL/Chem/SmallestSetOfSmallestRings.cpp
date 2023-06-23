/* 
 * SmallestSetOfSmallestRings.cpp 
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

#include <algorithm>
#include <functional>

#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/RangeGenerator.hpp"


namespace
{

	const std::size_t MAX_MESSAGE_CACHE_SIZE = 100000;
}


using namespace CDPL;


Chem::SmallestSetOfSmallestRings::SmallestSetOfSmallestRings():
	msgCache(MAX_MESSAGE_CACHE_SIZE)
{
	testRing = allocMessage();
	linDepTestRing = allocMessage();
}

Chem::SmallestSetOfSmallestRings::SmallestSetOfSmallestRings(const MolecularGraph& molgraph):
	msgCache(MAX_MESSAGE_CACHE_SIZE)
{
	testRing = allocMessage();
	linDepTestRing = allocMessage();

	perceive(molgraph);
}

void Chem::SmallestSetOfSmallestRings::perceive(const MolecularGraph& molgraph)
{
	clear();

	cyclicSubstruct.perceive(molgraph);
	visAtomMask.resize(cyclicSubstruct.getNumAtoms());
	visAtomMask.reset();

	std::size_t i = 0;
	std::size_t comp_count = 0;
	Fragment::ConstAtomIterator atoms_end = cyclicSubstruct.getAtomsEnd();

	for (Fragment::ConstAtomIterator it = cyclicSubstruct.getAtomsBegin(); it != atoms_end; ++it, i++) {
		if (!visAtomMask.test(i)) {
			component.clear();

			const Atom& atom = *it;

			component.addAtom(atom);

			visitComponentAtom(atom);

			sssrSize = component.getNumBonds() + 1 - component.getNumAtoms();
			comp_count++;

			if (sssrSize == 1) {
				const Atom* r_atom = &atom;
				Fragment::SharedPointer ring_ptr(new Fragment());
				Fragment& ring = *ring_ptr;

				while (true) {
					ring.addAtom(*r_atom);

					Atom::ConstBondIterator nb_it = r_atom->getBondsBegin();
					Atom::ConstBondIterator nb_end = r_atom->getBondsEnd();

					for (; nb_it != nb_end; ++nb_it) {
						const Bond& bond = *nb_it;

						if (!component.containsBond(bond))
							continue;
			
						if (!ring.containsBond(bond)) {
							ring.addBond(bond);
							r_atom = &bond.getNeighbor(*r_atom);
							break;
						}
					}

					if (nb_it == nb_end)
						break;
				}

				addElement(ring_ptr);
				continue;
			}

			init();
			findSSSR();
			createRingFragments();
		}
	}

	using namespace std::placeholders;
	
	if (comp_count > 1)
		std::sort(this->BaseType::getElementsBegin(), this->BaseType::getElementsEnd(), 
				  std::bind(std::less<std::size_t>(), std::bind(&Fragment::getNumAtoms, _1),
							std::bind(&Fragment::getNumAtoms, _2)));
}

void Chem::SmallestSetOfSmallestRings::visitComponentAtom(const Atom& atom)
{
	visAtomMask.set(cyclicSubstruct.getAtomIndex(atom));

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (!cyclicSubstruct.containsBond(bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!cyclicSubstruct.containsAtom(nbr_atom))
			continue;

		if (!component.containsBond(bond))
			component.addBond(bond);

		if (!visAtomMask.test(cyclicSubstruct.getAtomIndex(nbr_atom))) 
			visitComponentAtom(nbr_atom);
	}
}

void Chem::SmallestSetOfSmallestRings::init()
{
	sssr.clear();
	procRings.clear();
	evenRings.clear();
	linDepTestMtx.clear();

	std::size_t num_atoms = component.getNumAtoms();
	std::size_t num_bonds = component.getNumBonds();

	nodes.clear();
	nodes.reserve(num_atoms);

	std::generate_n(std::back_inserter(nodes), num_atoms, Internal::RangeGenerator<std::size_t>());

	std::size_t bond_idx = 0;

	for (Fragment::ConstBondIterator it = component.getBondsBegin(), end = component.getBondsEnd(); it != end; ++it, bond_idx++) {
		const Bond& bond = *it;

		TNode& node1 = nodes[component.getAtomIndex(bond.getBegin())];
		TNode& node2 = nodes[component.getAtomIndex(bond.getEnd())];

		TNode::connect(&node1, &node2, bond_idx);
	}

	for (NodeArray::iterator it = nodes.begin(), end = nodes.end(); it != end; ++it) 
		it->initMessages(this, num_atoms, num_bonds);
}

void Chem::SmallestSetOfSmallestRings::findSSSR()
{
	std::size_t num_nodes = nodes.size();

	for (bool first_cycle = true; !sssrComplete(); first_cycle = false) {
		if (!first_cycle) {
			bool new_messages = false;
		
			for (std::size_t i = 0; i < num_nodes; i++)
				new_messages |= nodes[i].send(this);

			if (!new_messages) 
				throw Base::CalculationFailed("SmallestSetOfSmallestRings: could not complete SSSR");
		}

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
		addElement(createRing(component, *it));
}

Chem::Fragment::SharedPointer Chem::SmallestSetOfSmallestRings::createRing(const MolecularGraph& molgraph, const MessagePtr& msg)
{
	Fragment::SharedPointer ring_ptr(new Fragment());
	Fragment& ring = *ring_ptr;
	const Atom* atom = &molgraph.getAtom(msg->getFirstAtomIndex());

	ring_ptr->addAtom(*atom);

	const Util::BitSet& bond_mask = msg->getBondMask();

	while (true) {
		Atom::ConstBondIterator bonds_end = atom->getBondsEnd();
		Atom::ConstBondIterator it = atom->getBondsBegin();

		for ( ; it != bonds_end; ++it) {
			const Bond& bond = *it;

			if (!molgraph.containsBond(bond))
				continue;
			
			if (!ring.containsBond(bond) && bond_mask.test(molgraph.getBondIndex(bond))) {
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

bool Chem::SmallestSetOfSmallestRings::sssrComplete() const
{
	return (sssr.size() >= sssrSize);
}

Chem::SmallestSetOfSmallestRings::MessagePtr Chem::SmallestSetOfSmallestRings::allocMessage()
{
	return msgCache.get();
}

Chem::SmallestSetOfSmallestRings::MessagePtr Chem::SmallestSetOfSmallestRings::allocMessage(std::size_t first_atom_idx, std::size_t first_bond_idx, 
																							std::size_t max_num_atoms, std::size_t max_num_bonds)
{
	MessagePtr msg = msgCache.get();

	msg->init(first_atom_idx, first_bond_idx, max_num_atoms, max_num_bonds);

	return msg;
}

bool Chem::SmallestSetOfSmallestRings::processCollision(const MessagePtr& msg1, const MessagePtr& msg2, std::size_t coll_atom_idx, bool odd)
{
	if (!testRing->join(msg1, msg2))
		return false;
	
	testRing->addAtom(coll_atom_idx);

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

void Chem::SmallestSetOfSmallestRings::processRing(const MessagePtr& ring)
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


bool Chem::SmallestSetOfSmallestRings::TNode::send(Controller* ctrl)
{
	std::size_t num_nbr_nodes = nbrNodes.size();
	std::size_t num_messages = sendBuffer.size();
	bool new_messages = false;
	
	for (std::size_t i = 0; i < num_messages; i++) {
		const MessagePtr& msg = sendBuffer[i];

		for (std::size_t j = 0; j < num_nbr_nodes; j++) {
			std::size_t bond_idx = bondIndices[j]; 

			if (msg->containsAtom(nbrNodes[j]->index) || msg->containsBond(bond_idx)) // check path collisions
				continue;

			MessagePtr new_msg = ctrl->allocMessage();		

			new_msg->copy(msg);
			new_msg->addAtom(index);
			new_msg->addBond(bond_idx);

			new_messages = true;
			nbrNodes[j]->receiveBuffer.push_back(new_msg);
		}
	}

	sendBuffer.clear();

	return new_messages;
}

bool Chem::SmallestSetOfSmallestRings::TNode::receive(Controller* ctrl)
{
	MessageList::iterator rcv_buf_beg = receiveBuffer.begin();
	MessageList::iterator rcv_buf_end = receiveBuffer.end();

	std::for_each(rcv_buf_beg, rcv_buf_end, std::bind(&PathMessage::clearFlags, std::placeholders::_1));

	for (MessageList::iterator it = rcv_buf_beg; it != rcv_buf_end; ) {
		MessagePtr& msg1 = *it;
		std::size_t first_atom_idx = msg1->getFirstAtomIndex();
		std::size_t first_bond_idx = msg1->getFirstBondIndex();

		for (MessageList::iterator it2 = ++it; it2 != rcv_buf_end; ++it2) {
			MessagePtr& msg2 = *it2;

			if (first_atom_idx == msg2->getFirstAtomIndex()) {		 // node collision
				if (first_bond_idx == msg2->getFirstBondIndex()) {   // edge collision 
					msg1->setRemoveFlag();
					msg2->setRemoveFlag();

					if (!msg1->getEdgeCollisionFlag() && !msg2->getEdgeCollisionFlag())
						msg1->setEdgeCollisionFlag();

					continue;
				}

				if (ctrl->processCollision(msg1, msg2, index, false))				
					return true;

			} else if (first_bond_idx == msg2->getFirstBondIndex()) { // inverse edge collision
				if (ctrl->processCollision(msg1, msg2, index, true))				
					return true; 
			}                                                         // no collision
		}
	}

	sendBuffer.clear();

	for (MessageList::iterator it = rcv_buf_beg; it != rcv_buf_end; ++it) {
		MessagePtr& msg = *it;

		if (msg->getRemoveFlag() && !msg->getEdgeCollisionFlag()) 
			continue;
		
		sendBuffer.push_back(msg);
	}

	receiveBuffer.clear();

	return false;
}

std::size_t Chem::SmallestSetOfSmallestRings::TNode::getIndex() const
{
	return index;
}

std::size_t Chem::SmallestSetOfSmallestRings::TNode::getNumNeighbors() const
{
	return nbrNodes.size();
}

void Chem::SmallestSetOfSmallestRings::TNode::initMessages(Controller* ctrl, std::size_t max_num_atoms, std::size_t max_num_bonds)
{
	for (std::size_t i = 0, num_nbrs = nbrNodes.size(); i < num_nbrs; i++) {
		TNode* nbr_node = nbrNodes[i];

		receiveBuffer.push_back(ctrl->allocMessage(nbr_node->index, bondIndices[i], max_num_atoms, max_num_bonds));
	}
}

void Chem::SmallestSetOfSmallestRings::TNode::connect(TNode* node1, TNode* node2, std::size_t bond_idx)
{
	node1->nbrNodes.push_back(node2);
	node2->nbrNodes.push_back(node1);

	node1->bondIndices.push_back(bond_idx);
	node2->bondIndices.push_back(bond_idx);
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

void Chem::SmallestSetOfSmallestRings::PathMessage::addAtom(std::size_t atom_idx)
{
	atomPath.set(atom_idx);
}

void Chem::SmallestSetOfSmallestRings::PathMessage::addBond(std::size_t bond_idx)
{
	bondPath.set(bond_idx);

	maxBondIdx = std::max(maxBondIdx, bond_idx + 1);
}

void Chem::SmallestSetOfSmallestRings::PathMessage::copy(const MessagePtr& msg)
{
	atomPath = msg->atomPath;
	bondPath = msg->bondPath;
	firstAtomIdx = msg->firstAtomIdx;
	firstBondIdx = msg->firstBondIdx;
	maxBondIdx = msg->maxBondIdx;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::join(const MessagePtr& msg1, const MessagePtr& msg2)
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

	atomPath = msg1->atomPath;
	atomPath |= msg2->atomPath;

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

const Util::BitSet& Chem::SmallestSetOfSmallestRings::PathMessage::getAtomMask() const
{
	return atomPath;
}

const Util::BitSet& Chem::SmallestSetOfSmallestRings::PathMessage::getBondMask() const
{
	return bondPath;
}

void Chem::SmallestSetOfSmallestRings::PathMessage::clearFlags()
{
	removeFlag = false;
	edgeCollFlag = false;
}

void Chem::SmallestSetOfSmallestRings::PathMessage::setRemoveFlag()
{
	removeFlag = true;
}

void Chem::SmallestSetOfSmallestRings::PathMessage::setEdgeCollisionFlag()
{
	edgeCollFlag = true;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::getRemoveFlag() const
{
	return removeFlag;
}

bool Chem::SmallestSetOfSmallestRings::PathMessage::getEdgeCollisionFlag() const
{
	return edgeCollFlag;
}

Chem::SmallestSetOfSmallestRings::PathMessage& Chem::SmallestSetOfSmallestRings::PathMessage::operator^=(const PathMessage& msg)
{
	bondPath ^= msg.bondPath;

	for (maxBondIdx = bondPath.size(); maxBondIdx > 0 && !bondPath.test(maxBondIdx - 1); maxBondIdx--);

	return *this;
}


bool Chem::SmallestSetOfSmallestRings::TestMatrixRowCmpFunc::operator()(const MessagePtr& msg1, const MessagePtr& msg2) const
{
	return (msg1->getMaxBondIndex() > msg2->getMaxBondIndex());
}


bool Chem::SmallestSetOfSmallestRings::PathMessage::LessCmpFunc::operator()(const MessagePtr& msg1, const MessagePtr& msg2) const
{
	return (msg1->bondPath < msg2->bondPath);
}
