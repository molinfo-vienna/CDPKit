/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomAtomTypeFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Chem/AtomTypeFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


unsigned int Chem::getType(const Atom& atom)
{
    return atom.getPropertyOrDefault<unsigned int>(AtomProperty::TYPE, AtomType::UNKNOWN);
}

void Chem::setType(Atom& atom, unsigned int type)
{
    atom.setProperty(AtomProperty::TYPE, type);
}

void Chem::clearType(Atom& atom)
{
    atom.removeProperty(AtomProperty::TYPE);
}

bool Chem::hasType(const Atom& atom)
{
    return atom.isPropertySet(AtomProperty::TYPE);
}

unsigned int Chem::getTypeForSymbol(const Atom& atom)
{
    return getAtomType(getSymbol(atom));
}

unsigned int Chem::getGenericType(const Atom& atom)
{
    unsigned int atom_type = getType(atom);

    if (atom_type == AtomType::UNKNOWN || (atom_type > AtomType::MAX_ATOMIC_NO && atom_type <= AtomType::MAX_TYPE))
		return atom_type; 

    if (atom_type > AtomType::MAX_TYPE)
		return AtomType::UNKNOWN; 

    if (isHalogen(atom_type))
		return AtomType::X;

    if (isMetal(atom_type))
		return AtomType::M;

    if (atom_type == AtomType::C)
		return AtomType::A;
    
    if (atom_type == AtomType::H)
		return AtomType::QH;

    return AtomType::Q; 
}

