/* 
 * CIPRuleStack.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPRuleStack.
 */

#ifndef CDPL_CHEM_CIPRULESTACK_HPP
#define CDPL_CHEM_CIPRULESTACK_HPP

#include <boost/ptr_container/ptr_vector.hpp>

#include "CIPSequenceRule.hpp"


namespace CDPL
{

    namespace Chem
    {

        class CIPRuleStack : public CIPSequenceRule
        {

          public:
            CIPRuleStack();

            void enableFullStack(bool full_stack);

            std::size_t getNumSubRules() const
            {
                return (fullStack ? std::size_t(rules.size()) : std::size_t(3));
            }

            int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);

            int getComparison(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b, bool deep);

          private:
            typedef boost::ptr_vector<CIPSequenceRule> RuleStack;

            RuleStack rules;
            bool      fullStack;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPRULESTACK_HPP
