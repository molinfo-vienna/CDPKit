/* 
 * CIPStereoCenter.cpp 
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

#include "CIPStereoCenter.hpp"


using namespace CDPL;


unsigned int Chem::CIPStereoCenter::label(CIPDigraph::Node& node, CIPSequenceRule& comp)
{
    return CIPDescriptor::UNDEF;
}

Chem::CIPDigraph::Edge* Chem::CIPStereoCenter::findInternalEdge(const CIPDigraph::EdgeList& edges, const Atom* f1, const Atom* f2)
{
    for (auto edge : edges) {
        if (edge->getBeg().isDuplicate() || edge->getEnd().isDuplicate())
            continue;
                    
        if (isInternalEdge(*edge, f1, f2))
            return edge;
    }

    return 0;
}

bool Chem::CIPStereoCenter::isInternalEdge(const CIPDigraph::Edge& edge, const Atom* f1, const Atom* f2)
{
    const Atom* beg_atom = edge.getBeg().getAtom();
    const Atom* end_atom = edge.getEnd().getAtom();

    if (f1 == beg_atom && f2 == end_atom)
        return true;

    if (f1 == end_atom && f2 == beg_atom)
        return true;

    return false;
}

void Chem::CIPStereoCenter::removeInternalEdges(CIPDigraph::EdgeList& edges, const Atom* f1, const Atom* f2)
{
    edges.erase(
        std::remove_if(edges.begin(), edges.end(),
                       [f1, f2](const CIPDigraph::Edge* e) -> bool { return isInternalEdge(*e, f1, f2); }),
        edges.end());
}

void Chem::CIPStereoCenter::removeDuplicatedEdges(CIPDigraph::EdgeList& edges)
{
    edges.erase(
        std::remove_if(edges.begin(), edges.end(),
                       [](const CIPDigraph::Edge* e) -> bool { return e->getEnd().isDuplicate(); }),
        edges.end());
}
