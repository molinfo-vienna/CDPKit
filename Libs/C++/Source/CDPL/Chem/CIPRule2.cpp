/* 
 * CIPRule2.cpp 
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


#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"

#include "CIPRule2.hpp"


using namespace CDPL;


int Chem::CIPRule2::compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b)
{
    auto atom_a = a.getEnd().getAtom();
    auto atom_b = b.getEnd().getAtom();

    auto atom_a_iso = (a.getEnd().isDuplicate() ? 0 : atom_a ? getIsotope(*atom_a) : 0);
    auto atom_b_iso = (b.getEnd().isDuplicate() ? 0 : atom_b ? getIsotope(*atom_b) : 0);

    if (atom_a_iso == 0 && atom_b_iso == 0)
      return 0;
    
    auto atomic_no_a = (atom_a ? getType(*atom_a) : AtomType::H);
    auto atomic_no_b = (atom_b ? getType(*atom_b) : AtomType::H);

    double atom_a_wt = AtomDictionary::getAtomicWeight(atomic_no_a, atom_a_iso);
    double atom_b_wt = AtomDictionary::getAtomicWeight(atomic_no_b, atom_b_iso);

    return (atom_a_wt > atom_b_wt ? 1 : atom_a_wt < atom_b_wt ? -1 : 0);
}
