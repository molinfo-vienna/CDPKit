/* 
 * CIPRule1b.cpp 
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


#include "CIPRule1b.hpp"


using namespace CDPL;


namespace
{

    /**
     * Flag indicates whether to match the problematic
     * IUPAC 2013 recommendations for Rule 1B.
     */
    constexpr bool IUPAC_2013 = false;
}


int Chem::CIPRule1b::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    if (IUPAC_2013)
        return (a.getEnd().getDistance() < b.getEnd().getDistance() ? 1 :
                a.getEnd().getDistance() > b.getEnd().getDistance() ? -1 : 0);

    if (a.getEnd().isSet(CIPDigraph::Node::RING_DUPLICATE) && b.getEnd().isSet(CIPDigraph::Node::RING_DUPLICATE))
        return (a.getEnd().getDistance() < b.getEnd().getDistance() ? 1 :
                a.getEnd().getDistance() > b.getEnd().getDistance() ? -1 : 0);

    if (a.getEnd().isSet(CIPDigraph::Node::RING_DUPLICATE) && !b.getEnd().isSet(CIPDigraph::Node::RING_DUPLICATE))
        return +1;

    if (!a.getEnd().isSet(CIPDigraph::Node::RING_DUPLICATE) && b.getEnd().isSet(CIPDigraph::Node::RING_DUPLICATE))
        return -1;

    return 0;
}
