/* 
 * CIPSorter.hpp 
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
            typedef std::vector<CIPDigraph::EdgeList*> GroupList;
        
            CIPSorter(CIPSequenceRule* const* rules, std::size_t num_rules):
                rules(rules), numRules(num_rules)
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
         
            int compareLigands(const CIPDigraph::Node& node, const CIPDigraph::Edge& a, const CIPDigraph::Edge& b, bool deep) const;

            template <typename T>
            std::size_t getGroups(const CIPDigraph::EdgeList& edges, GroupList& groups, const T& new_grp) const
            {
                // would be nice to have this integrated whilst sorting - may provide a small speed increase
                // but as most of our lists are small we take use ugly sort then group approach
                CIPDigraph::Edge* prev     = 0;
                std::size_t       num_grps = 0;

                for (auto edge : edges) {
                    if (!prev || compareLigands(prev->getBeg(), *prev, *edge, true) != 0) {
                        groups.push_back(new_grp());
                        num_grps++;
                    }

                    prev = edge;
                    groups.back()->push_back(edge);
                }

                return num_grps;
            }

            std::size_t getNumGroups(const CIPDigraph::EdgeList& edges) const;

          private:
            CIPSequenceRule* const* rules;
            std::size_t             numRules;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPSORTER_HPP
