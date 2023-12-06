/* 
 * CIPRule4c.cpp 
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


#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPRule4c.hpp"


using namespace CDPL;


int Chem::CIPRule4c::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    unsigned int ord_a = ordinal(getBondLabel(a));
    unsigned int ord_b = ordinal(getBondLabel(b));

    int cmp = (ord_a > ord_b ? 1 : ord_a < ord_b ? -1 : 0);

    if (cmp != 0)
        return cmp;
    
    ord_a = ordinal(a.getEnd().getAuxDescriptor());
    ord_b = ordinal(b.getEnd().getAuxDescriptor());

    return (ord_a > ord_b ? 1 : ord_a < ord_b ? -1 : 0);
}

unsigned int Chem::CIPRule4c::ordinal(unsigned int descr)
{
    switch (descr) {

        case CIPDescriptor::m:
        case CIPDescriptor::r:
            return 2;

        case CIPDescriptor::s:
        case CIPDescriptor::p:
            return 1;

        default:
            return 0;
    }
}
