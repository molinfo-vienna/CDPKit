/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentTree.cpp 
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

#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/FragmentList.hpp"

#include "FragmentTree.hpp"
#include "FragmentTreeNode.hpp"


namespace
{

	const std::size_t MAX_TREE_NODE_CACHE_SIZE  = 200;
	const double      NO_CLASH_MIN_ATOM_SPACING = 0.25;
}


using namespace CDPL;


ConfGen::FragmentTree::FragmentTree(std::size_t max_conf_data_cache_size):
	confDataCache(max_conf_data_cache_size),
	nodeCache(boost::bind(&FragmentTree::createTreeNode, this), TreeNodeCache::DefaultDestructor(), MAX_TREE_NODE_CACHE_SIZE), 
	molGraph(0)
{
	nodeCache.setCleanupFunction(boost::bind(&FragmentTreeNode::clearConformers, _1));

	rootNode = nodeCache.getRaw();
}

ConfGen::FragmentTree::~FragmentTree() {}


const Chem::MolecularGraph* ConfGen::FragmentTree::getMolecularGraph() const
{
	return molGraph;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::getRoot() const
{
	return rootNode;
}

void ConfGen::FragmentTree::setAbortCallback(const CallbackFunction& func)
{
	abortCallback = func;
}

const ConfGen::CallbackFunction& ConfGen::FragmentTree::getAbortCallback() const
{
	return abortCallback;
}

void ConfGen::FragmentTree::setTimeoutCallback(const CallbackFunction& func)
{
	timeoutCallback = func;
}

const ConfGen::CallbackFunction& ConfGen::FragmentTree::getTimeoutCallback() const
{
	return timeoutCallback;
}

std::size_t ConfGen::FragmentTree::getNumFragments() const
{
	return fragToNodeMap.size();
}

const Chem::Fragment* ConfGen::FragmentTree::getFragment(std::size_t idx) const
{
	return fragToNodeMap[idx].first.get();
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::getFragmentNode(std::size_t idx) const
{
	return fragToNodeMap[idx].second;
}

void ConfGen::FragmentTree::buildTree(const Chem::FragmentList& frags, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	molGraph = &molgraph;

	nodeCache.putAll();
	fragToNodeMap.clear();

	if (frags.isEmpty()) {
		rootNode = allocTreeNode();

		rootNode->setChildren(0, 0);
		rootNode->setSplitBond(0);
		rootNode->setSplitBondAtoms(0, 0);
		rootNode->atomIndices.clear();
		rootNode->atomMask.resize(molgraph.getNumAtoms());
		rootNode->atomMask.reset();
		rootNode->coreAtomMask = rootNode->atomMask;
		return;
	}

	leafNodes.clear();

	for (FragmentList::BaseType::ConstElementIterator it = frags.FragmentList::BaseType::getElementsBegin(),
			 end = frags.FragmentList::BaseType::getElementsEnd(); it != end; ++it) {

		const Fragment::SharedPointer& frag = *it;
		FragmentTreeNode* node = allocTreeNode();

		node->setChildren(0, 0);
		node->setSplitBond(0);
		node->setSplitBondAtoms(0, 0);
		node->initFragmentData(*frag, molgraph);

		leafNodes.push_back(node);
		fragToNodeMap.push_back(std::make_pair(frag, node));
	}

	while (leafNodes.size() > 1) {
		bool found_pair = false;

		for (TreeNodeList::iterator it1 = leafNodes.begin(), end = leafNodes.end(); it1 != end; ++it1) {
			FragmentTreeNode* node1 = *it1;
			
			for (TreeNodeList::iterator it2 = it1 + 1; it2 != end; ++it2) {
				FragmentTreeNode* node2 = *it2;
				const Chem::Bond* bond = findConnectingBond(node1, node2);

				if (!bond) 
					continue;
				
				FragmentTreeNode* node = createParentNode(node1, node2, bond);
				
				found_pair = true;
				*it1 = node;
				leafNodes.erase(it2);
				break;
			}

			if (found_pair)
				break;
		}

		if (!found_pair)
			break;
	}

	rootNode = leafNodes.front();

	for (TreeNodeList::iterator it = leafNodes.begin() + 1, end = leafNodes.end(); it != end; ++it) 
		rootNode = createParentNode(rootNode, *it, 0);
}

void ConfGen::FragmentTree::initAtomClashRadiusTable()
{
	std::size_t num_atoms = molGraph->getNumAtoms();

	clashRadiusTable.resize(num_atoms);
	
	for (std::size_t i = 0; i < num_atoms; i++) {
		double radius = Chem::AtomDictionary::getCovalentRadius(getType(molGraph->getAtom(i)), 1);

		if (radius <= 0.0)
			clashRadiusTable[i] = 0.5;
		else
			clashRadiusTable[i] = radius + NO_CLASH_MIN_ATOM_SPACING * 0.5;
	}
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::createParentNode(FragmentTreeNode* node1, FragmentTreeNode* node2, 
																   const Chem::Bond* bond)
{
	FragmentTreeNode* node = allocTreeNode();

	node1->setParent(node);
	node2->setParent(node);

	FragmentTreeNode* left_child = node1;
	FragmentTreeNode* right_child = node2;

	if (left_child->getAtomIndices().size() > right_child->getAtomIndices().size())
		std::swap(left_child, right_child);

	node->setChildren(left_child, right_child);
	node->initFragmentData();
	node->setSplitBond(bond);

	if (!bond)
		node->setSplitBondAtoms(0, 0);

	else {
		if (left_child->getCoreAtomMask().test(molGraph->getAtomIndex(bond->getBegin())))
			node->setSplitBondAtoms(&bond->getBegin(), &bond->getEnd());
		else
			node->setSplitBondAtoms(&bond->getEnd(), &bond->getBegin());
	}

	return node;
}

const Chem::Bond* ConfGen::FragmentTree::findConnectingBond(FragmentTreeNode* node1, FragmentTreeNode* node2)
{
	const Util::BitSet& node1_atom_mask = node1->getAtomMask();
	const Util::BitSet& node2_atom_mask = node2->getAtomMask();

	for (BondList::iterator it = splitBonds.begin(), end = splitBonds.end(); it != end; ++it) {
		const Chem::Bond* bond = *it;

		std::size_t atom1_idx = molGraph->getAtomIndex(bond->getBegin());
		std::size_t atom2_idx = molGraph->getAtomIndex(bond->getEnd());

		if (node1_atom_mask.test(atom1_idx) && node1_atom_mask.test(atom2_idx) &&
			node2_atom_mask.test(atom1_idx) && node2_atom_mask.test(atom2_idx)) {

			splitBonds.erase(it);
			return bond;
		}
	}

	return 0;
}

ConfGen::ConformerData::SharedPointer ConfGen::FragmentTree::allocConformerData()
{
	ConformerData::SharedPointer conf_data = confDataCache.get();

	conf_data->resize(molGraph->getNumAtoms());
	conf_data->setEnergy(0.0);

	return conf_data;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::allocTreeNode()
{
	FragmentTreeNode* node = nodeCache.getRaw();

	node->setParent(0);
	node->clearConformers();
	node->getMMFF94Parameters().clear();
	node->clearTorsionDrivingData();

	return node;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::createTreeNode()
{
	return new FragmentTreeNode(*this);
}

bool ConfGen::FragmentTree::aborted() const
{
	if (abortCallback)
		return abortCallback();

	return false;
}

bool ConfGen::FragmentTree::timedout() const
{
	if (timeoutCallback)
		return timeoutCallback();

	return false;
}

const ConfGen::FragmentTree::DoubleArray& ConfGen::FragmentTree::getAtomClashRadiusTable() const
{
	return clashRadiusTable;
}
