/* 
 * CIPSequenceRule.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * The code in this file is a C++11 port of Java code written by John Mayfield
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


#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CIPSequenceRule.hpp"


using namespace CDPL;


unsigned int Chem::CIPSequenceRule::getBondLabel(const CIPDigraph::Edge& edge) const
{
    const Bond* bond = edge.getBond();
                
    if (!bond)
        return CIPDescriptor::UNDEF;
                
    return edge.getAuxDescriptor();
}

int Chem::CIPSequenceRule::recursiveCompare(CIPDigraph::Edge& a, CIPDigraph::Edge& b)
{
    int cmp = compare(a, b);
                
    if (cmp != 0)
        return cmp;

    struct Sentinel
    {
        
        ~Sentinel() {
            rule->edgeQueueCache.put();
        }
        
        CIPSequenceRule* rule;
    };
    
    EdgeQueue& edge_queue1 = *edgeQueueCache.getRaw();
    Sentinel sentinel1{this};

    EdgeQueue& edge_queue2 = *edgeQueueCache.getRaw();
    Sentinel sentinel2{this};
    
    edge_queue1.clear();
    edge_queue1.push_back(&a);

    edge_queue2.clear();
    edge_queue2.push_back(&b);

    while (!edge_queue1.empty() && !edge_queue2.empty()) {
        CIPDigraph::Edge* curr_a = edge_queue1.front(); edge_queue1.pop_front();
        CIPDigraph::Edge* curr_b = edge_queue2.front(); edge_queue2.pop_front();
        CIPDigraph::Node& a_node = curr_a->getEnd();
        CIPDigraph::Node& b_node = curr_b->getEnd();
        CIPDigraph::EdgeList& as = a_node.getEdges();
        CIPDigraph::EdgeList& bs = b_node.getEdges();

        // shallow sort first
        if (sort(a_node, as, false).wasWildcardFound())
            return COMP_TO_WILDCARD;
                    
        if (sort(b_node, bs, false).wasWildcardFound())
            return COMP_TO_WILDCARD;

        int size_diff = (as.size() < bs.size() ? -1 : as.size() > bs.size() ? 1 : 0);

        for (auto a_it = as.begin(), b_it = bs.begin(); a_it != as.end() && b_it != bs.end(); ++a_it, ++b_it) {
            CIPDigraph::Edge* a_edge = *a_it;
            CIPDigraph::Edge* b_edge = *b_it;

            if (areUpEdges(a_node, b_node, *a_edge, *b_edge))
                continue;
                            
            cmp = compare(*a_edge, *b_edge);
                            
            if (cmp != 0)
                return cmp;
        }

        if (size_diff != 0)
            return size_diff;

        if (sort(a_node, as).wasWildcardFound())
            return COMP_TO_WILDCARD;
                    
        if (sort(b_node, bs).wasWildcardFound())
            return COMP_TO_WILDCARD;

        for (auto a_it = as.begin(), b_it = bs.begin(); a_it != as.end() && b_it != bs.end(); ++a_it, ++b_it) {
            CIPDigraph::Edge* a_edge = *a_it;
            CIPDigraph::Edge* b_edge = *b_it;

            if (areUpEdges(a_node, b_node, *a_edge, *b_edge))
                continue;
                            
            cmp = compare(*a_edge, *b_edge);
                            
            if (cmp != 0)
                return cmp;

            edge_queue1.push_back(a_edge);
            edge_queue2.push_back(b_edge);
        }
    }
                
    return 0;
}

bool Chem::CIPSequenceRule::areUpEdges(const CIPDigraph::Node& a_node, const CIPDigraph::Node& b_node,
                                       const CIPDigraph::Edge& a_edge, const CIPDigraph::Edge& b_edge)
{
    // step over 'up' edges
    if (a_edge.isEnd(a_node)) {
        // if b is 'down' something's not right!
        if (!b_edge.isEnd(b_node))
            throw Base::ItemNotFound("CIPSequenceRule: digraph node not a member of edge");

        return true;
    }
                
    return false;
}
