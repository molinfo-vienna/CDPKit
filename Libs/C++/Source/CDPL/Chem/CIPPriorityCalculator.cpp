/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CIPPriorityCalculator.cpp 
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

#include "CDPL/Chem/CIPPriorityCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


namespace
{

	const std::size_t MAX_NODE_CACHE_SIZE = 1000;
}


using namespace CDPL;


Chem::CIPPriorityCalculator::CIPPriorityCalculator(): 
	nodeCache(MAX_NODE_CACHE_SIZE), implHCountFunc(&getImplicitHydrogenCount)
{}

Chem::CIPPriorityCalculator::CIPPriorityCalculator(const MolecularGraph& molgraph, Util::STArray& priorities):
	nodeCache(MAX_NODE_CACHE_SIZE), implHCountFunc(&getImplicitHydrogenCount)
{
	calculate(molgraph, priorities);
}

void Chem::CIPPriorityCalculator::setImplicitHydrogenCountFunction(const ImplicitHydrogenCountFunction& func)
{
	implHCountFunc = func;
}

const Chem::CIPPriorityCalculator::ImplicitHydrogenCountFunction& 
Chem::CIPPriorityCalculator::getImplicitHydrogenCountFunction()
{
	return implHCountFunc;
}

void Chem::CIPPriorityCalculator::calculate(const MolecularGraph& molgraph, Util::STArray& priorities)
{
	init(molgraph, priorities);
	determinePriorities(priorities);	
}

void Chem::CIPPriorityCalculator::init(const MolecularGraph& molgraph, Util::STArray& priorities)
{
	nodeCache.putAll();

	std::size_t num_atoms = molgraph.getNumAtoms();

	atomNodes.clear();
	atomNodes.reserve(num_atoms * 2);

	expAtomNodes.clear();
	expAtomNodes.reserve(num_atoms);

	priorities.clear();
	priorities.reserve(num_atoms);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;

		std::size_t atom_type = getType(atom) % 1024;
		std::size_t isotope = getIsotope(atom) % 1024;
		std::size_t impl_h_count = implHCountFunc(atom);

		AtomNode* atom_node = allocNode(atom_type * 1024 + isotope);

		if (impl_h_count > 0) {
			AtomNode* h_node = allocNode(AtomType::H * 1024);

			for (std::size_t i = 0; i < impl_h_count; i++)
				atom_node->addNbrNode(h_node);

			h_node->addNbrNode(atom_node);

			atomNodes.push_back(h_node);
		}

		expAtomNodes.push_back(atom_node);
		atomNodes.push_back(atom_node);
	}

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		AtomNode* atom_node1 = expAtomNodes[molgraph.getAtomIndex(bond.getBegin())];
		AtomNode* atom_node2 = expAtomNodes[molgraph.getAtomIndex(bond.getEnd())];

		std::size_t bond_order = getOrder(bond);

		for (std::size_t i = 0; i < bond_order; i++) {
			atom_node1->addNbrNode(atom_node2);
			atom_node2->addNbrNode(atom_node1);
		}
	}
}

void Chem::CIPPriorityCalculator::determinePriorities(Util::STArray& priorities)
{
	AtomNode::LessCmpFunc node_cmp_func;

	NodeList::iterator nodes_begin = atomNodes.begin();
	NodeList::iterator nodes_end = atomNodes.end();

	std::size_t max_priority = 1;

	while (true) {
		std::for_each(nodes_begin, nodes_end, std::mem_fun(&AtomNode::updateNbrList));
		std::sort(nodes_begin, nodes_end, node_cmp_func);

		std::size_t priority = 1;

		for (NodeList::iterator it = nodes_begin; it != nodes_end; priority++) {
			NodeList::iterator ub = std::upper_bound(it, nodes_end, *it, node_cmp_func);

			std::for_each(it, ub, std::bind2nd(std::mem_fun(&AtomNode::setNewPriority), priority));
			it = ub;
		}

		std::for_each(nodes_begin, nodes_end, std::mem_fun(&AtomNode::updatePriority));

		if (priority <= max_priority)
			break;
		
		max_priority = priority;
	}

	std::for_each(expAtomNodes.begin(), expAtomNodes.end(), boost::bind(&Util::STArray::addElement, 
																		boost::ref(priorities),
																		boost::bind(&AtomNode::getPriority, _1)));
}

Chem::CIPPriorityCalculator::AtomNode* Chem::CIPPriorityCalculator::allocNode(std::size_t p)
{
	AtomNode* node = nodeCache.getRaw();

	node->clear();
	node->setPriority(p);

	return node;
}


void Chem::CIPPriorityCalculator::AtomNode::clear()
{
	nbrNodes.clear();
}

void Chem::CIPPriorityCalculator::AtomNode::addNbrNode(AtomNode* nbr_node)
{
	nbrNodes.push_back(nbr_node);
}

void Chem::CIPPriorityCalculator::AtomNode::setNewPriority(std::size_t p)
{
	newPriority = p;
}

void Chem::CIPPriorityCalculator::AtomNode::updatePriority()
{
	priority = newPriority;
}

void Chem::CIPPriorityCalculator::AtomNode::updateNbrList()
{
	std::sort(nbrNodes.begin(), nbrNodes.end(), PriorityGreaterCmpFunc()); 
}

std::size_t Chem::CIPPriorityCalculator::AtomNode::getPriority() const
{
	return priority;
}

void Chem::CIPPriorityCalculator::AtomNode::setPriority(std::size_t p)
{
	priority = p;
}


bool Chem::CIPPriorityCalculator::AtomNode::LessCmpFunc::operator()(const AtomNode* node1, 
																		   const AtomNode* node2) const
{
	if (node1->priority == node2->priority)
		return std::lexicographical_compare(node1->nbrNodes.begin(), node1->nbrNodes.end(),
											node2->nbrNodes.begin(), node2->nbrNodes.end(),
											PriorityLessCmpFunc());

	return (node1->priority < node2->priority);
}


bool Chem::CIPPriorityCalculator::AtomNode::PriorityLessCmpFunc::operator()(const AtomNode* node1, 
																				   const AtomNode* node2) const
{
	return (node1->priority < node2->priority);
}

bool Chem::CIPPriorityCalculator::AtomNode::PriorityGreaterCmpFunc::operator()(const AtomNode* node1, 
																					  const AtomNode* node2) const
{
	return (node1->priority > node2->priority);
}

