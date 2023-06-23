/* 
 * AtomTypeMatchExpression.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include "StaticInit.hpp"

#include "CDPL/Chem/AtomTypeMatchExpression.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


Chem::AtomTypeMatchExpression::AtomTypeMatchExpression(unsigned int atom_type, bool not_match): 
    atomType(atom_type), notMatch(not_match) {}

bool Chem::AtomTypeMatchExpression::operator()(const Atom&, const MolecularGraph&, 
                                               const Atom& target_atom, const MolecularGraph&, 
                                               const Base::Any&) const
{
    return (notMatch ? !atomTypesMatch(atomType, getType(target_atom)) : atomTypesMatch(atomType, getType(target_atom)));
}
