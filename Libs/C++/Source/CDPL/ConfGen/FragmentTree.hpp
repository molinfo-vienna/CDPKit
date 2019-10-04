/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentTree.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::FragmentTree.
 */

#ifndef CDPL_CONFGEN_FRAGMENTTREE_HPP
#define CDPL_CONFGEN_FRAGMENTTREE_HPP

#include <vector>
#include <cstddef>

#include <boost/unordered_map.hpp>

#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class FragmentTreeNode;

		class FragmentTree
		{

			friend class FragmentTreeNode;


		public:
			FragmentTree(std::size_t max_conf_data_cache_size);

			~FragmentTree();

			void build(const Chem::MolecularGraph& molgraph, const Util::BitSet& split_bond_mask);

			template <typename NodeOrderFunc>
			void build(const Chem::MolecularGraph& molgraph, const Util::BitSet& split_bond_mask, 
					   const NodeOrderFunc& node_order_func);

			FragmentTreeNode* getRoot() const;

		private:
			typedef Util::ObjectPool<ConformerData> ConformerDataCache;
			
			void generateLeafNodes(const Chem::MolecularGraph& molgraph, const Util::BitSet& split_bond_mask);
			void buildupTree(const Chem::MolecularGraph& molgraph);

			FragmentTreeNode* createParentNode(FragmentTreeNode* node1, FragmentTreeNode* node2, 
											   const Chem::MolecularGraph& molgraph, const Chem::Bond* bond);

			const Chem::Bond* findConnectingBond(const Chem::MolecularGraph& molgraph, FragmentTreeNode* node1, 
												 FragmentTreeNode* node2);

			void orderLeafNodes();
			bool compareLeafNodeOrder(FragmentTreeNode* node1, FragmentTreeNode* node2);

			ConformerData::SharedPointer allocConformerData();

			FragmentTreeNode* allocTreeNode(const Chem::MolecularGraph& molgraph);
			FragmentTreeNode* createTreeNode();

			typedef std::vector<const Chem::Bond*> BondList;
			typedef Util::ObjectStack<FragmentTreeNode> TreeNodeCache;
			typedef std::vector<FragmentTreeNode*> TreeNodeList;
			typedef boost::unordered_map<FragmentTreeNode*, std::size_t> TreeNodeOrderMap;

			ConformerDataCache         confDataCache;
			TreeNodeCache              nodeCache;
			FragmentTreeNode*          rootNode;
			Chem::FragmentList         fragments;
			BondList                   splitBonds;
			TreeNodeList               leafNodes;
			TreeNodeOrderMap           leafNodeOrders;
		};
    }
}


// Implementation

template <typename NodeOrderFunc>
void CDPL::ConfGen::FragmentTree::build(const CDPL::Chem::MolecularGraph& molgraph, const CDPL::Util::BitSet& split_bond_mask, 
										const NodeOrderFunc& node_order_func)
{
	generateLeafNodes(molgraph, split_bond_mask);

	leafNodeOrders.clear();

	for (TreeNodeList::const_iterator it = leafNodes.begin(), end = leafNodes.end(); it != end; ++it) {
		const FragmentTreeNode* node = *it;

		leafNodeOrders.insert(TreeNodeOrderMap::value_type(node, node_order_func(*node)));
	}

	orderLeafNodes();
	buildupTree(molgraph);
}

#endif // CDPL_CONFGEN_FRAGMENTTREE_HPP
