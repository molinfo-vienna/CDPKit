/* 
 * CIPRule1a.cpp 
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


#include "CDPL/Chem/AtomType.hpp"

#include "CIPRule1a.hpp"


using namespace CDPL;


namespace
{

    bool isChemElement(unsigned int atom_type)
    {
        return (atom_type >= Chem::AtomType::H && atom_type <= Chem::AtomType::MAX_ATOMIC_NO);
    }
}

    
int Chem::CIPRule1a::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    auto atomic_no_num_a = a.getEnd().getAtomicNoNumerator();
    auto atomic_no_den_a = a.getEnd().getAtomicNoDenominator();

    if (atomic_no_den_a == 1 && !isChemElement(atomic_no_num_a))
        return CIPSequenceRule::COMP_TO_WILDCARD;

    auto atomic_no_num_b = b.getEnd().getAtomicNoNumerator();
    auto atomic_no_den_b = b.getEnd().getAtomicNoDenominator();

    if (atomic_no_den_b == 1 && !isChemElement(atomic_no_num_b))
        return CIPSequenceRule::COMP_TO_WILDCARD;
    
    double fr_atomic_no_a = double(atomic_no_num_a) / atomic_no_den_a;
    double fr_atomic_no_b = double(atomic_no_num_b) / atomic_no_den_b;

    return (fr_atomic_no_a < fr_atomic_no_b ? -1 : fr_atomic_no_a > fr_atomic_no_b ? 1 : 0);
}
