/* 
 * CIPRule5.cpp 
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


#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPRule5.hpp"


using namespace CDPL;


Chem::CIPRule5::CIPRule5():
    refDescriptor(CIPDescriptor::UNDEF)
{}
    
int Chem::CIPRule5::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
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

    listRA.clear();
    listRA.add(CIPDescriptor::R);

    listRB.clear();
    listRB.add(CIPDescriptor::R);

    listSA.clear();
    listSA.add(CIPDescriptor::S);

    listSB.clear();
    listSB.add(CIPDescriptor::S);
   
    fillPairs(a.getEnd(), listRA);
    fillPairs(a.getEnd(), listSA);
    fillPairs(b.getEnd(), listRB);
    fillPairs(b.getEnd(), listSB);

    int cmp_R = listRA.compareTo(listRB);
    int cmp_S = listSA.compareTo(listSB);

    // -2/+2 for psuedo-asymetric
    // -1/+1 if not (e.g. the R > R and S > S lists)
    if (cmp_R < 0)
        return cmp_S < 0 ? -1 : -2;

    if (cmp_R > 0)
        return cmp_S > 0 ? +1 : +2;

    return 0;
}

void Chem::CIPRule5::fillPairs(CIPDigraph::Node& beg, CIPPairList& plist)
{
    struct RefResetter
    {
        
        ~RefResetter() {
            rule->refDescriptor = CIPDescriptor::UNDEF;
        }
        
        CIPRule5* rule;

    } ref_res{this};
    
    refDescriptor = plist.getRefDescriptor();

    nodeQueue.clear();
    nodeQueue.push_back(&beg);

    auto& sorter = getSorter();
    
    while (!nodeQueue.empty()) {
        auto node = nodeQueue.front(); nodeQueue.pop_front();
        
        plist.add(node->getAuxDescriptor());

        auto& edges = node->getEdges();

        sorter.prioritise(*node, edges);
      
        for (auto edge : edges) {
            if (edge->isBeg(*node) && !edge->getEnd().isTerminal())
                nodeQueue.push_back(&edge->getEnd());
        }
    }
}
