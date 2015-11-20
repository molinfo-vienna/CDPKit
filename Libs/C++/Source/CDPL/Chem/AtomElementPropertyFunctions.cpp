/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomElementPropertyFunctions.cpp 
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
#include "CDPL/Chem/AtomTypeFunctions.hpp"


using namespace CDPL; 


double Chem::getAtomicWeight(const Atom& atom)
{
    return getAtomicWeight(getType(atom), getIsotope(atom));
}

std::size_t Chem::getIUPACGroup(const Atom& atom)
{
    return getIUPACGroup(getType(atom));
}

double Chem::getVdWRadius(const Atom& atom)
{
    return getVdWRadius(getType(atom));
}

double Chem::getCovalentRadius(const Atom& atom, std::size_t order)
{
    return getCovalentRadius(getType(atom), order);
}

double Chem::getAllredRochowElectronegativity(const Atom& atom)
{
    return getAllredRochowElectronegativity(getType(atom));
}

std::size_t Chem::getElementValenceElectronCount(const Atom& atom)
{
	return getNumValenceElectrons(getType(atom));
}

const std::string& Chem::getElementName(const Atom& atom)
{
    return getElementName(getType(atom), getIsotope(atom));
}

bool Chem::isChemicalElement(const Atom& atom)
{
    return isChemicalElement(getType(atom));
}

bool Chem::isMainGroupElement(const Atom& atom)
{
    return isMainGroupElement(getType(atom));
}

bool Chem::isMetal(const Atom& atom)
{
    return isMetal(getType(atom));
}

bool Chem::isTransitionMetal(const Atom& atom)
{
    return isTransitionMetal(getType(atom));
}

bool Chem::isNonMetal(const Atom& atom)
{
    return isNonMetal(getType(atom));
}

bool Chem::isSemiMetal(const Atom& atom)
{
    return isSemiMetal(getType(atom));
}

bool Chem::isHalogen(const Atom& atom)
{
    return isHalogen(getType(atom));
}

bool Chem::isNobleGas(const Atom& atom)
{
    return isNobleGas(getType(atom));
}

