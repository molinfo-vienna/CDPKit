/* 
 * CIPRule1a.cpp 
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


#include "CIPRule1a.hpp"


using namespace CDPL;


int Chem::CIPRule1a::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    unsigned int anum = a.getEnd().getAtomicNoNumerator();
    unsigned short aden = a.getEnd().getAtomicNoDenominator();
    unsigned int bnum = b.getEnd().getAtomicNoNumerator();
    unsigned short bden = b.getEnd().getAtomicNoDenominator();
    
    if (anum == 0 || bnum == 0)
        return CIPSequenceRule::COMP_TO_WILDCARD;

    if (aden == 1 && bden == 1)
        return (anum < bnum ? -1 : anum > bnum ? 1 : 0);

    double fr_anum = double(anum) / aden;
    double fr_bnum = double(bnum) / bden;

    return (fr_anum < fr_bnum ? -1 : fr_anum > fr_bnum ? 1 : 0);
}
