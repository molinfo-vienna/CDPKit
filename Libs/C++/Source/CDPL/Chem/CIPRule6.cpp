/* 
 * CIPRule6.cpp 
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


#include "CIPRule6.hpp"


using namespace CDPL;


int Chem::CIPRule6::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    auto& digraph = a.getBeg().getDigraph();
    auto ref = digraph.getRule6Ref();

    if (!ref)
      return 0;

    auto a_atom = a.getEnd().getAtom();
    auto b_atom = b.getEnd().getAtom();

    // note: we had to go through rule 5 (pseudoasymmetric) to get here
    // so the return type is -2/+2
    
    if (ref == a_atom && ref != b_atom)
        return +2; // a is ref (has priority)

    if (ref != a_atom && ref == b_atom)
        return -2; // b is ref (has priority)

    return 0;
}
