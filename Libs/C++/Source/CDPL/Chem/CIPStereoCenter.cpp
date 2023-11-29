/* 
 * CIPStereoCenter.cpp 
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

/*
 * Copyright (c) 2020 John Mayfield
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPStereoCenter.hpp"


using namespace CDPL;


unsigned int Chem::CIPStereoCenter::label(CIPDigraph::Node& node, CIPDigraph& digraph, CIPSequenceRule& comp)
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
                       [](const CIPDigraph::Edge* e) -> bool { return isInternalEdge(*e, f, f2); }),
        edges.end());
}

void Chem::CIPStereoCenter::removeDuplicatedEdges(CIPDigraph::EdgeList& edges)
{
    edges.erase(
        std::remove_if(edges.begin(), edges.end(),
                       [](const CIPDigraph::Edge* e) -> bool { return e->getEnd().isDuplicate(); }),
        edges.end());
}
