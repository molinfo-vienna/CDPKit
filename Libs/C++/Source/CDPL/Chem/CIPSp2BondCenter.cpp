/* 
 * CIPSp2BondCenter.cpp 
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


#include <utility>
#include <algorithm>

#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPSp2BondCenter.hpp"
#include "CIPSequenceRule.hpp"


using namespace CDPL;


unsigned int Chem::CIPSp2BondCenter::label(CIPSequenceRule& comp)
{
    auto foci = getFocusAtoms();
    auto focus1 = foci[0];
    auto focus2 = foci[1];

    auto& digraph = getDigraph();
    auto root1 = digraph.getRoot();
                
    if (!root1)
        root1 = &digraph.init(*focus1);
    else
        digraph.changeRoot(*root1);

    auto internal = findInternalEdge(root1->getEdges(), focus1, focus2);

    if (!internal)
        return CIPDescriptor::UNDEF;
                    
    root1->getEdges(edges1, internal);

    auto sort_res1 = comp.sort(*root1, edges1);

    if (!sort_res1.isUnique())
        return CIPDescriptor::NONE;

    auto& root2 = internal->getOther(*root1);
                    
    digraph.changeRoot(root2);
                
    root2.getEdges(edges2, internal);

    auto sort_res2 = comp.sort(root2, edges2);
                
    if (!sort_res2.isUnique())
        return CIPDescriptor::NONE;

    auto config = getConfig();

    if (config == UNSPEC)
        return CIPDescriptor::NS;

    auto carriers = getCarrierAtoms();
    
    // swap
    if (edges1.size() > 1 && carriers[0] == edges1[1]->getEnd().getAtom())
        config ^= (OPPOSITE | TOGETHER);
    // swap
    if (edges2.size() > 1 && carriers[1] == edges2[1]->getEnd().getAtom())
        config ^= (OPPOSITE | TOGETHER);

    if (config == TOGETHER) {
        if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
            return CIPDescriptor::seqCis;

        return CIPDescriptor::Z;
    }

    if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
        return CIPDescriptor::seqTrans;

    return CIPDescriptor::E;
}

unsigned int Chem::CIPSp2BondCenter::label(CIPDigraph::Node& root1, CIPSequenceRule& comp)
{
    auto foci = getFocusAtoms();
    auto focus1 = foci[0];
    auto focus2 = foci[1];

    auto internal = findInternalEdge(root1.getEdges(), focus1, focus2);

    if (!internal)
        return CIPDescriptor::UNDEF;
                
    auto& root2 = internal->getOther(root1);
             
    root1.getEdges(edges1, internal);
    root2.getEdges(edges2, internal);

    removeInternalEdges(edges1, focus1, focus2);
    removeInternalEdges(edges2, focus1, focus2);
    
    const Atom* carriers[2] = { getCarrierAtoms()[0], getCarrierAtoms()[1] };
    auto config = getConfig();

    if (root1.getAtom() == focus2)
        std::swap(carriers[1], carriers[0]);

    auto& digraph = getDigraph();
    
    digraph.changeRoot(root1);
                
    auto sort_res1 = comp.sort(root1, edges1);
                
    if (!sort_res1.isUnique())
        return CIPDescriptor::NONE;
                
    // swap
    if (edges1.size() > 1 && carriers[0] == edges1[1]->getEnd().getAtom() && config != UNSPEC)
        config ^= (OPPOSITE | TOGETHER);
                
    digraph.changeRoot(root2);

    auto sort_res2 = comp.sort(root2, edges2);
                
    if (!sort_res2.isUnique())
        return CIPDescriptor::NONE;

    if (config == UNSPEC)
        return CIPDescriptor::NS;
                    
    // swap
    if (edges2.size() > 1 && carriers[1] == edges2[1]->getEnd().getAtom())
        config ^= (OPPOSITE | TOGETHER);

    if (config == TOGETHER) {
        if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
            return CIPDescriptor::seqCis;

        return CIPDescriptor::Z;
    }

    if (sort_res1.isPseudoAsymmetric() != sort_res2.isPseudoAsymmetric())
        return CIPDescriptor::seqTrans;

    return CIPDescriptor::E;
}
