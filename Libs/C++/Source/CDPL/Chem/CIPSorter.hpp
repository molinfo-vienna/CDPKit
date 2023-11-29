/* 
 * CIPSorter.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::CIPSorter.
 */

#ifndef CDPL_CHEM_CIPSORTER_HPP
#define CDPL_CHEM_CIPSORTER_HPP

#include <cstddef>
#include <vector>

#include "CIPSortingResult.hpp"
#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        class CIPSequenceRule;
        
        /**
         * A simple insertion sort implementation for ligands. The number of ligands is not likely to
         * be very larger as such doing a merge sort would have little benefit.
         */
        class CIPSorter
        {

          public:
            typedef std::vector<std::vector<const CIPDigraph::Edge*> > GroupList;
          
            CIPSorter(CIPSequenceRule* rule):
                rules(&rule), numRules(1), rule(rule)
            {}

            CIPSorter(CIPSequenceRule* const* rules, std::size_t num_rules):
                rules(rules), numRules(1), rule(0)
            {}

            CIPSequenceRule* const* getRules() const
            {
                return rules;
            }

            std::size_t getNumRules() const
            {
                return numRules;
            }

            CIPSortingResult prioritise(const CIPDigraph::Node& node, CIPDigraph::EdgeList& edges) const
            {
                return prioritise(node, edges, true);
            }

            CIPSortingResult prioritise(const CIPDigraph::Node& node, CIPDigraph::EdgeList& edges, bool deep) const;
         
            int compareLigands(const CIPDigraph::Node& node, CIPDigraph::Edge& a, CIPDigraph::Edge& b, bool deep) const;
            
            void getGroups(const CIPDigraph::EdgeList& edges, GroupList& groups) const;

            std::size_t getNumGroups(const CIPDigraph::EdgeList& edges) const;

          private:
            CIPSequenceRule* const* rules;
            std::size_t             numRules;
            CIPSequenceRule*        rule;
        }
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPSORTER_HPP
