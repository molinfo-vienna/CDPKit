/* 
 * CIPRule4b.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * Code based on a Java implementation of the CIP sequence rules by John Mayfield
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
 * \brief Definition of the class CDPL::Chem::CIPRule4b.
 */

#ifndef CDPL_CHEM_CIPRULE4b_HPP
#define CDPL_CHEM_CIPRULE4b_HPP

#include <vector>
#include <deque>

#include "CDPL/Util/ObjectStack.hpp"

#include "CIPSequenceRule.hpp"
#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        class CIPPairList;
        
        /**
         * CIP Sequence Rule 4b
         *
         * This rule defines that like descriptor pairs have
         * priority over unlike descriptor pairs.
         */
        class CIPRule4b : public CIPSequenceRule
        {

          public:
            CIPRule4b();

            int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);

          private:
            struct RefResetter;
            
            typedef CIPDigraph::NodeList NodeList;
            typedef CIPDigraph::EdgeList EdgeList;
            typedef CIPSorter::GroupList EdgeGroupList;
            typedef std::vector<CIPPairList*> PairListList;
            
            void newPairLists(PairListList& plists);

            bool getReference(const NodeList& nodes);

            void getReferenceDescriptors(CIPDigraph::Node& node);

            void initialLevel(CIPDigraph::Node& node);
            void getNextLevel();
            
            void addNodes(NodeList& nodes, const EdgeList& eq_edges) const;

            void fillPairs(CIPDigraph::Node& beg, CIPPairList& plist);
            
            int comparePairs(CIPDigraph::Node& a, CIPDigraph::Node& b,
                             unsigned int ref_a, unsigned int ref_b);

            typedef std::vector<unsigned int> DescriptorList;
            typedef std::vector<NodeList*> NodeListList;
            typedef std::deque<CIPDigraph::Node*> NodeQueue;
            typedef Util::ObjectStack<CIPPairList> PairListCache;
            typedef Util::ObjectStack<NodeList> NodeListCache;
            typedef Util::ObjectStack<EdgeList> EdgeListCache;
            
            PairListCache  pairListCache;
            NodeListCache  nodeListCache;
            EdgeListCache  edgeListCache;
            unsigned int   refDescriptor;
            PairListList   pairLists1;
            PairListList   pairLists2;
            DescriptorList descrList;
            NodeListList   nodeLists;
            NodeListList   nextNodeLists;
            EdgeGroupList  edgeGroups;
            NodeQueue      nodeQueue1;
            NodeQueue      nodeQueue2;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPRULE4b_HPP
