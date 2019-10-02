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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "FragmentTree.hpp"
#include "FragmentTreeNode.hpp"


namespace
{

	const std::size_t MAX_TREE_NODE_CACHE_SIZE = 100;
}


using namespace CDPL;


ConfGen::FragmentTree::FragmentTree():
	nodeCache(&createTreeNode, TreeNodeCache::DefaultDestructor(), MAX_TREE_NODE_CACHE_SIZE), rootNode(0)
{}

ConfGen::FragmentTree::~FragmentTree() {}

void ConfGen::FragmentTree::build(const Chem::MolecularGraph& molgraph, const Util::BitSet& split_bond_mask)
{
	generateLeafNodes(molgraph, split_bond_mask);
	buildupTree(molgraph);
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::getRoot() const
{
	return rootNode;
}

void ConfGen::FragmentTree::generateLeafNodes(const Chem::MolecularGraph& molgraph, const Util::BitSet& split_bond_mask)
{
	rootNode = 0;

	leafNodes.clear();
	nodeCache.putAll();
	splitBonds.clear();

	for (Util::BitSet::size_type i = split_bond_mask.find_first(); i != Util::BitSet::npos; i = split_bond_mask.find_next(i))
		splitBonds.push_back(&molgraph.getBond(i));

	splitIntoFragments(molgraph, fragments, split_bond_mask, false);

	for (Chem::FragmentList::ConstElementIterator it = fragments.getElementsBegin(), end = fragments.getElementsEnd(); it != end; ++it) {
		const Chem::Fragment& frag = *it;
		FragmentTreeNode* node = nodeCache.getRaw();

		node->initFragmentData(frag, molgraph);
		node->setFragment(&frag);
		node->setRootFragment(&molgraph);
		node->setParent(0);
		node->setChildren(0, 0);
		node->setSplitBond(0);
		node->setSplitBondAtoms(0, 0);
		node->setTorsionReferenceAtoms(0, 0);
		node->getConformers().clear();
		node->getTorsionAngles().clear();
		node->getMMFF94InteractionData().clear();

		leafNodes.push_back(node);
	}
}

void ConfGen::FragmentTree::buildupTree(const Chem::MolecularGraph& molgraph)
{
	if (leafNodes.empty())
		return;

	while (leafNodes.size() > 1) {
		bool found_pair = false;

		for (TreeNodeList::iterator it1 = leafNodes.begin(), end = leafNodes.end(); it1 != end; ) {
			FragmentTreeNode* node1 = *it1;
			
			for (TreeNodeList::iterator it2 = ++it1; it2 != end; ++it2) {
				FragmentTreeNode* node2 = *it2;
				const Chem::Bond* bond = findConnectingBond(molgraph, node1, node2);

				if (!bond)
					continue;

				FragmentTreeNode* node = nodeCache.getRaw();
	
				node1->setParent(node);
				node2->setParent(node);
	
				if (node1->getAtomIndices().size() <=  node2->getAtomIndices().size())
					node->setChildren(node1, node2);
				else
					node->setChildren(node2, node1);

				node->initFragmentData();
				node->setParent(0);
				node->setFragment(0);
				node->setRootFragment(&molgraph);
				node->setSplitBond(bond);
				node->setSplitBondAtoms(0, 0);
				node->setTorsionReferenceAtoms(0, 0);
				node->getConformers().clear();
				node->getTorsionAngles().clear();
				node->getMMFF94InteractionData().clear();

				*it2 = node;
				leafNodes.erase(it1);

				found_pair = true;
				break;
			}

			if (found_pair)
				break;
		}

		if (!found_pair)
			break;
	}

	rootNode = leafNodes.front();
}

const Chem::Bond* ConfGen::FragmentTree::findConnectingBond(const Chem::MolecularGraph& molgraph, FragmentTreeNode* node1, 
															FragmentTreeNode* node2)
{
	const Util::BitSet& node1_atom_mask = node1->getAtomMask();
	const Util::BitSet& node2_atom_mask = node2->getAtomMask();

	for (BondList::iterator it = splitBonds.begin(), end = splitBonds.end(); it != end; ++it) {
		const Chem::Bond* bond = *it;

		std::size_t atom1_idx = molgraph.getAtomIndex(bond->getBegin());
		std::size_t atom2_idx = molgraph.getAtomIndex(bond->getEnd());

		if (node1_atom_mask.test(atom1_idx) && node1_atom_mask.test(atom2_idx) &&
			node2_atom_mask.test(atom1_idx) && node2_atom_mask.test(atom2_idx)) {

			splitBonds.erase(it);
			return bond;
		}
	}

	return 0;
}

void ConfGen::FragmentTree::orderLeafNodes()
{
	std::sort(leafNodes.begin(), leafNodes.end(), boost::bind(&FragmentTree::compareLeafNodeOrder, this, _1, _2));
}

bool ConfGen::FragmentTree::compareLeafNodeOrder(FragmentTreeNode* node1, FragmentTreeNode* node2)
{
	return (leafNodeOrders[node1] < leafNodeOrders[node2]);
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTree::createTreeNode()
{
	return new FragmentTreeNode();
}
