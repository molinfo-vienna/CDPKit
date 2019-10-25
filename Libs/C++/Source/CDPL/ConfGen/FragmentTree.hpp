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

#include <utility>
#include <vector>
#include <cstddef>

#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL 
{
	
	namespace Chem
	{

		class FragmentList;
	}

    namespace ConfGen 
    {

		class FragmentTreeNode;

		class FragmentTree
		{

			friend class FragmentTreeNode;

		public:
			FragmentTree(std::size_t max_conf_data_cache_size);

			~FragmentTree();
				
			template <typename BondIter>
			void build(const Chem::FragmentList& frags, const Chem::MolecularGraph& molgraph,
					   const BondIter& bonds_beg, const BondIter& bonds_end);

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			const Chem::MolecularGraph* getMolecularGraph() const;

			FragmentTreeNode* getRoot() const;

			std::size_t getNumFragments() const;

			const Chem::Fragment* getFragment(std::size_t idx) const;

			FragmentTreeNode* getFragmentNode(std::size_t idx) const;

		private:
			typedef std::vector<double> DoubleArray;

			void generateLeafNodes(const Chem::FragmentList& frags, const Chem::MolecularGraph& molgraph);

			void buildupTree();

			void initAtomClashRadiusTable();

			FragmentTreeNode* createParentNode(FragmentTreeNode* node1, FragmentTreeNode* node2, 
											   const Chem::Bond* bond);

			const Chem::Bond* findConnectingBond(FragmentTreeNode* node1, FragmentTreeNode* node2);

			ConformerData::SharedPointer allocConformerData();

			FragmentTreeNode* allocTreeNode();
			FragmentTreeNode* createTreeNode();

			bool aborted() const;
			bool timedout() const;

			const DoubleArray& getAtomClashRadiusTable() const;

			typedef Util::ObjectPool<ConformerData> ConformerDataCache;
			typedef std::vector<const Chem::Bond*> BondList;
			typedef Util::ObjectStack<FragmentTreeNode> TreeNodeCache;
			typedef std::vector<FragmentTreeNode*> TreeNodeList;
			typedef std::vector<std::pair<Chem::Fragment::SharedPointer, FragmentTreeNode*> > FragmentToNodeMap;

			ConformerDataCache          confDataCache;
			TreeNodeCache               nodeCache;
			const Chem::MolecularGraph* molGraph;
			FragmentTreeNode*           rootNode;
			BondList                    splitBonds;
			TreeNodeList                leafNodes;
			FragmentToNodeMap           fragToNodeMap;
			CallbackFunction            abortCallback;
			CallbackFunction            timeoutCallback;
			DoubleArray                 clashRadiusTable;
		};
    }
}


// Implementation

template <typename BondIter>
void CDPL::ConfGen::FragmentTree::build(const Chem::FragmentList& frags, const Chem::MolecularGraph& molgraph,
										const BondIter& bonds_beg, const BondIter& bonds_end)
{
	splitBonds.clear();
	splitBonds.insert(splitBonds.end(), bonds_beg, bonds_end);

	generateLeafNodes(frags, molgraph);
	buildupTree();
	initAtomClashRadiusTable();
}

#endif // CDPL_CONFGEN_FRAGMENTTREE_HPP
