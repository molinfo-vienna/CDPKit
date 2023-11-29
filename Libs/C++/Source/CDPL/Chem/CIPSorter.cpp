/* 
 * CIPSorter.cpp 
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


#include <utility>

#include "CIPSorter.hpp"
#include "CIPSequenceRule.hpp"


using namespace CDPL;


Chem::CIPSortingResult Chem::CIPSorter::prioritise(const CIPDigraph::Node& node, CIPDigraph::EdgeList& edges, bool deep) const
{
    bool unique = true;
    bool found_wc = false;
    std::size_t num_pseudo_asym = 0;

outer:
    for (std::size_t i = 0, num_edges = edges.size(); i < num_edges; i++) {
        for (long j = i; j > 0; j--) {
            int cmp = compareLigands(node, *edges[j - 1], *edges[j], deep);

            if (cmp == SequenceRule::COMP_TO_WILDCARD) {
                unique = false;
                found_wc = true;
                break outer;
            }

            // -2/+2 means we used Rule 5 (or more) and the ligands are mirror images
            if (cmp < -1 || cmp > 1)
                num_pseudo_asym++;

            if (cmp < 0) {
                std::swap(edges[j], edges[j - 1]);

            } else {
                if (cmp == 0)
                    unique = false;
                break;
            }
        }
    }

    return CIPSortingResult(unique, found_wc, num_pseudo_asym == 1);
}

int Chem::CIPSorter::compareLigands(const CIPDigraph::Node& node, CIPDigraph::Edge& a, CIPDigraph::Edge& b, bool deep) const
{
    // ensure 'up' edges are moved to the front
    if (!a.isBeg(node) && b.isBeg(node))
        return +1;

    if (a.isBeg(node) && !b.isBeg(node))
        return -1;

    for (std::size_t i = 0; i < numRules; i++) {
        int cmp = rules[i]->getComparison(a, b, deep);

        if (cmp != 0)
            return cmp;
    }

    return 0;
}

void Chem::CIPSorter::getGroups(const CIPDigraph::EdgeList& edges, GroupList& groups) const
{
    // would be nice to have this integrated whilst sorting - may provide a small speed increase
    // but as most of our lists are small we take use ugly sort then group approach
    groups.clear();
    CIPDigraph::Edge* prev = 0;

    for (auto edge : edges) {
        if (!prev || compareLigands(prev->getBeg(), *prev, *edge, true) != 0)
            groups.resize(groups.size() + 1);

        prev = edge;
        groups.back().push_back(edge);
    }
}

std::size_t Chem::CIPSorter::getNumGroups(const CIPDigraph::EdgeList& edges) const
{
    // would be nice to have this integrated whilst sorting - may provide a small speed increase
    // but as most of our lists are small we take use ugly sort then group approach
    std::size_t num_grps = 0;
    CIPDigraph::Edge* prev = 0;

    for (auto edge : edges) {
        if (!prev || compareLigands(prev->getBeg(), *prev, *edge, true) != 0)
            num_grps++;

        prev = edge;
    }

    return num_grps;
}
