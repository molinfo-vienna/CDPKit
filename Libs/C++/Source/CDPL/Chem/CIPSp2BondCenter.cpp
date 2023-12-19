/* 
 * CIPSp2BondCenter.cpp 
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


#include <utility>
#include <algorithm>

#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPSp2BondCenter.hpp"
#include "CIPSequenceRule.hpp"


using namespace CDPL;


unsigned int Chem::CIPSp2BondCenter::label(CIPSequenceRule& comp)
{
    const Atom* const* foci = getFocusAtoms();
    const Atom* focus1 = foci[0];
    const Atom* focus2 = foci[1];

    CIPDigraph& digraph = getDigraph();
    CIPDigraph::Node* root1 = digraph.getRoot();
                
    if (!root1)
        root1 = &digraph.init(*focus1);
    else
        digraph.changeRoot(*root1);

    const CIPDigraph::Edge* internal = findInternalEdge(root1->getEdges(), focus1, focus2);

    if (!internal)
        return CIPDescriptor::UNDEF;
                    
    root1->getEdges(edges1, internal);

    CIPSortingResult sort_res1 = comp.sort(*root1, edges1);

    if (!sort_res1.isUnique())
        return CIPDescriptor::NONE;

    CIPDigraph::Node& root2 = internal->getOther(*root1);
                    
    digraph.changeRoot(root2);
                
    root2.getEdges(edges2, internal);

    CIPSortingResult sort_res2 = comp.sort(root2, edges2);
                
    if (!sort_res2.isUnique())
        return CIPDescriptor::NONE;

    const Atom* const* carriers = getCarrierAtoms();
    unsigned int config = getConfig();

    // swap
    if (edges1.size() > 1 && carriers[0] == edges1[1]->getEnd().getAtom())
        config ^= 0x3;
    // swap
    if (edges2.size() > 1 && carriers[1] == edges2[1]->getEnd().getAtom())
        config ^= 0x3;

    if (config == TOGETHER) {
        if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
            return CIPDescriptor::seqCis;

        return CIPDescriptor::Z;
    }

    if (config == OPPOSITE) {
        if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
            return CIPDescriptor::seqTrans;

        return CIPDescriptor::E;
    }

    return CIPDescriptor::NS;
}

unsigned int Chem::CIPSp2BondCenter::label(CIPDigraph::Node& root1, CIPDigraph& digraph, CIPSequenceRule& comp)
{
    const Atom* const* foci = getFocusAtoms();
    const Atom* focus1 = foci[0];
    const Atom* focus2 = foci[1];

    const CIPDigraph::Edge* internal = findInternalEdge(root1.getEdges(), focus1, focus2);

    if (!internal)
        return CIPDescriptor::UNDEF;
                
    CIPDigraph::Node& root2 = internal->getOther(root1);
             
    root1.getEdges(edges1, internal);
    root2.getEdges(edges2, internal);
              
    const Atom* carriers[2] = { getCarrierAtoms()[0], getCarrierAtoms()[1] };
    unsigned int config = getConfig();

    if (root1.getAtom() == focus2)
        std::swap(carriers[1], carriers[0]);

    digraph.changeRoot(root1);
                
    CIPSortingResult sort_res1 = comp.sort(root1, edges1);
                
    if (!sort_res1.isUnique())
        return CIPDescriptor::NONE;
                
    // swap
    if (edges1.size() > 1 && carriers[0] == edges1[1]->getEnd().getAtom())
        config ^= 0x3;
                
    digraph.changeRoot(root2);

    CIPSortingResult sort_res2 = comp.sort(root2, edges2);
                
    if (!sort_res2.isUnique())
        return CIPDescriptor::NONE;
                
    // swap
    if (edges2.size() > 1 && carriers[1] == edges2[1]->getEnd().getAtom())
        config ^= 0x3;

    if (config == TOGETHER) {
        if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
            return CIPDescriptor::seqCis;

        return CIPDescriptor::Z;

    } else if (config == OPPOSITE) {
        if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
            return CIPDescriptor::seqTrans;

        return CIPDescriptor::E;
    }
                
    return CIPDescriptor::UNDEF;
}
