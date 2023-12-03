/* 
 * CIPTetrahedralCenter.cpp 
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


#include <algorithm>

#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPTetrahedralCenter.hpp"
#include "CIPSequenceRule.hpp"


using namespace CDPL;


unsigned int Chem::CIPTetrahedralCenter::label(CIPSequenceRule& comp)
{
    CIPDigraph& digraph = getDigraph();
    CIPDigraph::Node* root = digraph.getRoot();
                
    if (!root)
        return label(digraph.init(*getFocus()), comp);

    digraph.changeRoot(*root);

    return label(*root, comp);
}

unsigned int Chem::CIPTetrahedralCenter::label(CIPDigraph::Node& node, CIPDigraph& digraph, CIPSequenceRule& comp)
{
    digraph.changeRoot(node);
                
    return label(node, comp);
}

unsigned int Chem::CIPTetrahedralCenter::label(CIPDigraph::Node& node, CIPSequenceRule& comp)
{
    node.getEdges(edges);

    // something not right!?! bad creation
    if (edges.size() < 3)
        return CIPDescriptor::NONE;

    if (edges.size() > 4)
        return CIPDescriptor::NONE;

    CIPSortingResult sort_res = comp.sort(node, edges);
                
    if (sort_res.wasWildcardFound())
        return CIPDescriptor::NS;

    bool is_unique = sort_res.isUnique();
                
    if (!is_unique && edges.size() == 4) {
        if (comp.getNumSubRules() == 3)
            return CIPDescriptor::UNDEF;
                    
        std::size_t num_grps = comp.getSorter().getNumGroups(edges);
                    
        if (num_grps == 2) {
            // a a' b b' and a a' a'' b
            node.getDigraph().setRule6Ref(edges[1]->getEnd().getAtom());
                        
            sort_res = comp.sort(node, edges);

            node.getDigraph().setRule6Ref(0);
                        
        } else if (num_grps == 1) {
            // S4 symmetric case
            node.getDigraph().setRule6Ref(edges[0]->getEnd().getAtom());
            comp.sort(node, edges);
                        
            const CIPDigraph::Edge* nbrs1[4];

            std::copy(edges.begin(), edges.end(), nbrs1);

            node.getDigraph().setRule6Ref(edges[1]->getEnd().getAtom());

            sort_res = comp.sort(node, edges);

            const CIPDigraph::Edge* nbrs2[4];
                        
            std::copy(edges.begin(), edges.end(), nbrs2);

            if (parity4(nbrs1, nbrs2) == 1)
                return CIPDescriptor::NONE;
                        
            node.getDigraph().setRule6Ref(0);
        }

        if (!sort_res.isUnique())
            return CIPDescriptor::NONE;
                    
    } else if (!is_unique)
        return CIPDescriptor::NONE;

    const Atom* ordered[4];
    std::size_t idx = 0;

    for (auto edge : edges) {
        if (edge->getEnd().isSet(CIPDigraph::Node::BOND_DUPLICATE) ||
            edge->getEnd().isSet(CIPDigraph::Node::IMPL_HYDROGEN))
            continue;
                
        ordered[idx++] = edge->getEnd().getAtom();
    }
                
    if (idx < 4)
        ordered[idx] = getFocus();

    unsigned int parity = parity4(ordered, getCarrierAtoms());

    if (parity == 0)
        return CIPDescriptor::UNDEF;

    unsigned int config = getConfig();
                
    if (parity == 1)
        config ^= 0x3;

    if (config == LEFT) {
        if (sort_res.isPseudoAsymmetric())
            return CIPDescriptor::s;
                   
        return CIPDescriptor::S;

    } else if (config == RIGHT) {
        if (sort_res.isPseudoAsymmetric())
            return CIPDescriptor::r;

        return CIPDescriptor::R;
    }

    return CIPDescriptor::UNDEF;
}
