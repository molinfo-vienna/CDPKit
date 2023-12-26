/* 
 * CIPRule4b.cpp 
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


#include <cstddef>
#include <algorithm>

#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CIPRule4b.hpp"
#include "CIPPairList.hpp"


using namespace CDPL;


struct Chem::CIPRule4b::RefResetter
{

    ~RefResetter() {
        rule->refDescriptor = CIPDescriptor::UNDEF;
    }

    CIPRule4b* rule;
};


Chem::CIPRule4b::CIPRule4b():
    pairListCache(50), nodeListCache(100), edgeListCache(50), refDescriptor(CIPDescriptor::UNDEF)
{
    pairListCache.setInitFunction([](CIPPairList& l) { l.clear(); });
    nodeListCache.setInitFunction([](NodeList& l) { l.clear(); });
    edgeListCache.setInitFunction([](EdgeList& l) { l.clear(); });
}

void Chem::CIPRule4b::newPairLists(PairListList& plists)
{
    plists.clear();

    for (auto descriptor : descrList) {
        auto plist = pairListCache.get();

        plist->add(descriptor);

        plists.push_back(plist);
    }
}

bool Chem::CIPRule4b::getReference(const NodeList& nodes)
{
    using namespace CIPDescriptor;
    
    std::size_t right = 0;
    std::size_t left  = 0;

    for (auto node : nodes) {
        switch (node->getAuxDescriptor()) {

            case R:
            case M:
            case seqCis:
                right++;
                break;

            case S:
            case P:
            case seqTrans:
                left++;
                break;
        }
    }

    if (right + left == 0)
        return false;

    if (right > left) {
        descrList.push_back(R);
        return true;
    }

    if (right < left) {
        descrList.push_back(S);
        return true;
    }

    descrList.push_back(R);
    descrList.push_back(S);
    return true;
}

void Chem::CIPRule4b::getReferenceDescriptors(CIPDigraph::Node& node)
{
    nodeListCache.putAll();
    descrList.clear();

    initialLevel(node);
    
    while (!nodeLists.empty()) {
        for (auto nodes : nodeLists) {
            if (getReference(*nodes))
                return;
        }
        
        getNextLevel();
    }
}

void Chem::CIPRule4b::initialLevel(CIPDigraph::Node& node)
{
    auto list = nodeListCache.get();

    list->push_back(&node);

    nodeLists.clear();
    nodeLists.push_back(list);
}

void Chem::CIPRule4b::getNextLevel()
{
    nextNodeLists.clear();
  
    CIPSorter& sorter = getSorter();
    
    for (auto prev : nodeLists) {
        edgeGroups.clear();
        edgeListCache.putAll();

        auto edges = edgeListCache.get();
        std::size_t num_grps = 0;
        
        for (auto node : *prev) {
            node->getNonTerminalOutEdges(*edges);
            sort(*node, *edges);

            bool init = edgeGroups.empty();
            auto curr_num_grps = sorter.getGroups(*edges, edgeGroups,
                                                  [this]() -> EdgeList* {
                                                      return this->edgeListCache.get();
                                                  });
            if (init)
                num_grps = curr_num_grps;
            else if (curr_num_grps != num_grps)
                throw Base::SizeError("CIPRule4b: invalid number of equiv. edge groups");
        }

        for (std::size_t i = 0; i < num_grps; i++) {
            auto nl = nodeListCache.get();
            
            for (std::size_t j = i; j < edgeGroups.size(); j += num_grps)
                addNodes(*nl, *edgeGroups[j]);

            if (!nl->empty())
                nextNodeLists.push_back(nl);
            else
                nodeListCache.put(); 
        }
    }
    
    nextNodeLists.swap(nodeLists);
}

void Chem::CIPRule4b::addNodes(NodeList& nodes, const EdgeList& eq_edges) const
{
    for (auto edge : eq_edges)
      nodes.push_back(&edge->getEnd());
}

void Chem::CIPRule4b::fillPairs(CIPDigraph::Node& beg, CIPPairList& plist)
{
    RefResetter ref_res{this};
    auto& sorter = getSorter();
    
    refDescriptor = plist.getRefDescriptor();
    
    nodeQueue1.clear();
    nodeQueue1.push_back(&beg);
    
    while (!nodeQueue1.empty()) {
        auto node = nodeQueue1.front(); nodeQueue1.pop_front();

        plist.add(node->getAuxDescriptor());
        
        auto& edges = node->getEdges();

        sorter.prioritise(*node, edges);

        for (auto edge : edges)
            if (edge->isBeg(*node) && !edge->getEnd().isTerminal())
                nodeQueue1.push_back(&edge->getEnd());
    }
}
            
int Chem::CIPRule4b::comparePairs(CIPDigraph::Node& a, CIPDigraph::Node& b, unsigned int ref_a, unsigned int ref_b)
{
    RefResetter ref_res{this};
    auto& sorter = getSorter();
    
    nodeQueue1.clear();
    nodeQueue1.push_back(&a);

    nodeQueue2.clear();
    nodeQueue2.push_back(&b);

    while (!nodeQueue1.empty() && !nodeQueue2.empty()) {
        auto a_node = nodeQueue1.front(); nodeQueue1.pop_front();
        auto b_node = nodeQueue2.front(); nodeQueue2.pop_front();
        auto des_a = CIPPairList::ref(a_node->getAuxDescriptor());
        auto des_b = CIPPairList::ref(b_node->getAuxDescriptor());

        if (des_a == ref_a && des_b != ref_b)
            return +1;

        if (des_a != ref_a && des_b == ref_b)
            return -1;

        auto& a_edges = a_node->getEdges();

        refDescriptor = ref_a;
        sorter.prioritise(*a_node, a_edges);

        for (auto edge : a_edges)
            if (edge->isBeg(*a_node) && !edge->getEnd().isTerminal())
                nodeQueue1.push_back(&edge->getEnd());

        auto& b_edges = b_node->getEdges();

        refDescriptor = ref_b;
        sorter.prioritise(*b_node, b_edges);

        for (auto edge : b_edges)
            if (edge->isBeg(*b_node) && !edge->getEnd().isTerminal())
                nodeQueue2.push_back(&edge->getEnd());
    }
    
    return 0;
}

int Chem::CIPRule4b::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    if (a.getBeg().getDigraph().getCurrRoot() != &a.getBeg() ||
        b.getBeg().getDigraph().getCurrRoot() != &b.getBeg()) {

        if (refDescriptor == CIPDescriptor::UNDEF)
            return 0;

        auto a_desc = a.getEnd().getAuxDescriptor();
        auto b_desc = b.getEnd().getAuxDescriptor();

        if (a_desc != CIPDescriptor::UNDEF && b_desc != CIPDescriptor::UNDEF) {
            bool a_like = (CIPPairList::ref(refDescriptor) == CIPPairList::ref(a_desc));
            bool b_like = (CIPPairList::ref(refDescriptor) == CIPPairList::ref(b_desc));

            if (a_like && !b_like)
                return +1;
            
            if (b_like && !a_like)
                return -1;
        }
        
        return 0;
    }
    
    pairListCache.putAll();
    
    getReferenceDescriptors(a.getEnd());
    newPairLists(pairLists1);

    getReferenceDescriptors(b.getEnd());
    newPairLists(pairLists2);

    if (pairLists1.empty() != pairLists2.empty())
        throw Base::OperationFailed("CIPRule4b: compared ligands should be topologically equivalent");

    if (pairLists1.size() == 1)
        return comparePairs(a.getEnd(), b.getEnd(),
                            pairLists1[0]->getRefDescriptor(),
                            pairLists2[0]->getRefDescriptor());
    
    if (pairLists1.size() > 1) {
        for (auto plist : pairLists1)
            fillPairs(a.getEnd(), *plist);
        
        for (auto plist : pairLists2)
            fillPairs(b.getEnd(), *plist);

        auto cmp_func = [](const CIPPairList* pl1, const CIPPairList* pl2) -> bool {
                            return (pl1->compareTo(*pl2) > 0);
                        };

        std::sort(pairLists1.begin(), pairLists1.end(), cmp_func);
        std::sort(pairLists2.begin(), pairLists2.end(), cmp_func);

        for (std::size_t i = 0, num_plists = pairLists1.size(); i < num_plists; i++) {
            int cmp = pairLists1[i]->compareTo(*pairLists2[i]);

            if (cmp != 0)
                return cmp;
        }
    }

    return 0;
}
