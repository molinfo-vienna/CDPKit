/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomRadicalTypeFunctions.cpp 
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
#include "CDPL/Chem/RadicalType.hpp"


using namespace CDPL; 


unsigned int Chem::getRadicalType(const Atom& atom)
{
    return atom.getPropertyOrDefault<unsigned int>(AtomProperty::RADICAL_TYPE, RadicalType::NOT_RADICALIC);
}

void Chem::setRadicalType(Atom& atom, unsigned int type)
{
    atom.setProperty(AtomProperty::RADICAL_TYPE, type);
}

void Chem::clearRadicalType(Atom& atom)
{
    atom.removeProperty(AtomProperty::RADICAL_TYPE);
}

bool Chem::hasRadicalType(const Atom& atom)
{
    return atom.isPropertySet(AtomProperty::RADICAL_TYPE);
}
