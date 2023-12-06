/* 
 * CIPSequenceRule.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::CIPSequenceRule.
 */

#ifndef CDPL_CHEM_CIPSEQUENCERULE_HPP
#define CDPL_CHEM_CIPSEQUENCERULE_HPP

#include <cstddef>
#include <deque>

#include "CDPL/Util/ObjectStack.hpp"

#include "CIPSorter.hpp"
#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * An abstract comparator that provides construction of the CIPSorter
         * wrapper allowing subclasses to focus on the actual comparison of ligands.
         * 
         * Note there is some special semantics on the return value of the comparison.
         * Possible values are -3 (COMP_TO_WILDCARD), -2 (LESS using rule5),
         * -1 (LESS), 0 (EQ), +1 (MORE), +2 (MORE using rule5). We need these
         * to indicate back up to the caller that this is either undefined
         * stereochemistry or it is defined by pseudo-asymmetric (super-imposable
         * mirror image R=>r, S=>s, etc).
         */
        class CIPSequenceRule
        {

          public:
            /**
             * Sentinel value returned if a comparison was made to a wildcard (any atom).
             * Since these have undefined ranking we need to indicate back up the call
             * stack that this centre is undefined. 
             */
            static constexpr int COMP_TO_WILDCARD = -3;

            CIPSequenceRule(): edgeQueueCache(100), sorter(this) {}

            virtual ~CIPSequenceRule() {}
            
            unsigned int getBondLabel(const CIPDigraph::Edge& edge) const;

            virtual std::size_t getNumSubRules() const
            {
                return 1;
            }

            virtual bool isPseudoAsymmetric() const
            {
                return false;
            }

            virtual int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b) = 0;
            
            int recursiveCompare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);

            int getComparison(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
            {
                return getComparison(a, b, true);
            }

            virtual int getComparison(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b, bool deep)
            {
                return (deep ? recursiveCompare(a, b) : compare(a, b));
            }

            void setSorter(const CIPSorter& sorter)
            {
                this->sorter = sorter;
            }

            CIPSorter& getSorter()
            {
                return sorter;
            }

            CIPSortingResult sort(const CIPDigraph::Node& node, CIPDigraph::EdgeList& edges, bool deep)
            {
                return sorter.prioritise(node, edges, deep);
            }

            CIPSortingResult sort(const CIPDigraph::Node& node, CIPDigraph::EdgeList& edges)
            {
                return sort(node, edges, true);
            }

          private:
            static bool areUpEdges(const CIPDigraph::Node& a_node, const CIPDigraph::Node& b_node,
                                   const CIPDigraph::Edge& a_edge, const CIPDigraph::Edge& b_edge);

            typedef std::deque<const CIPDigraph::Edge*> EdgeQueue;
            typedef Util::ObjectStack<EdgeQueue>        EdgeQueueCache;

            EdgeQueueCache edgeQueueCache;
            CIPSorter      sorter;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPSEQUENCERULE_HPP
