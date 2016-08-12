/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomSymbolFunctions.cpp 
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
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"


using namespace CDPL; 


const std::string& Chem::getSymbol(const Atom& atom)
{
	static const std::string DEF_SYMBOL = AtomDictionary::getSymbol(AtomType::UNKNOWN);

	return atom.getPropertyOrDefault<std::string>(AtomProperty::SYMBOL, DEF_SYMBOL);
}

void Chem::setSymbol(Atom& atom, const std::string& symbol)
{
	atom.setProperty(AtomProperty::SYMBOL, symbol);
}

void Chem::clearSymbol(Atom& atom)
{
	atom.removeProperty(AtomProperty::SYMBOL);
}

bool Chem::hasSymbol(const Atom& atom)
{
	return atom.isPropertySet(AtomProperty::SYMBOL);
}

const std::string& Chem::getSymbolForType(const Atom& atom)
{
	return AtomDictionary::getSymbol(getType(atom), getIsotope(atom));
}

