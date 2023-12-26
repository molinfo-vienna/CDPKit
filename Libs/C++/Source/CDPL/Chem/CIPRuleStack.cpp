/* 
 * CIPRuleStack.cpp 
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


#include "CIPRuleStack.hpp"
#include "CIPRule1a.hpp"
#include "CIPRule1b.hpp"
#include "CIPRule2.hpp"
#include "CIPRule3.hpp"
#include "CIPRule4a.hpp"
#include "CIPRule4b.hpp"
#include "CIPRule4c.hpp"
#include "CIPRule5.hpp"
#include "CIPRule6.hpp"


using namespace CDPL;


Chem::CIPRuleStack::CIPRuleStack():
    fullStack(true)
{
    rules.push_back(new CIPRule1a());
    rules.push_back(new CIPRule1b());
    rules.push_back(new CIPRule2());
    rules.push_back(new CIPRule3());
    rules.push_back(new CIPRule4a());
    rules.push_back(new CIPRule4b());
    rules.push_back(new CIPRule4c());
    rules.push_back(new CIPRule5());
    rules.push_back(new CIPRule6());

    for (std::size_t i = 0, num_rules = rules.size(); i < num_rules; i++)
        rules[i].setSorter(CIPSorter(rules.c_array(), i + 1));

    setSorter(rules.back().getSorter());
}

void Chem::CIPRuleStack::enableFullStack(bool full_stack)
{
    fullStack = full_stack;

    if (full_stack)
        setSorter(rules.back().getSorter());
    else
        setSorter(rules[2].getSorter());
}

int Chem::CIPRuleStack::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    // Try using each rules. The rules will expand the search exhaustively
    // to all child ligands
    for (std::size_t i = 0, num_rules = (fullStack ? std::size_t(rules.size()) : std::size_t(3)); i < num_rules; i++) {
        // compare expands exhaustively across the whole graph
        int value = rules[i].recursiveCompare(a, b);
        
        if (value != 0)
            return value;
    }
    
    return 0;
}

int Chem::CIPRuleStack::getComparison(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b, bool deep)
{
    // Try using each rules. The rules will expand the search exhaustively
    // to all child ligands
    for (std::size_t i = 0, num_rules = (fullStack ? std::size_t(rules.size()) : std::size_t(3)); i < num_rules; i++) {
        // compare expands exhaustively across the whole graph
        int value = rules[i].recursiveCompare(a, b);

        if (value != 0)
            return value;
    }

    return 0;
}
