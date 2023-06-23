/* 
 * AtomElementPropertyFunctions.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


double MolProp::getAtomicWeight(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::getAtomicWeight(getType(atom), getIsotope(atom));
}

std::size_t MolProp::getIUPACGroup(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::getIUPACGroup(getType(atom));
}

std::size_t MolProp::getPeriod(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::getPeriod(getType(atom));
}

double MolProp::getVdWRadius(const Chem::Atom& atom)
{
    return Internal::getVdWRadius(atom);
}

double MolProp::getCovalentRadius(const Chem::Atom& atom, std::size_t order)
{
    return Chem::AtomDictionary::getCovalentRadius(getType(atom), order);
}

double MolProp::getAllredRochowElectronegativity(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::getAllredRochowElectronegativity(getType(atom));
}

std::size_t MolProp::getElementValenceElectronCount(const Chem::Atom& atom)
{
	return Chem::AtomDictionary::getNumValenceElectrons(getType(atom));
}

const std::string& MolProp::getElementName(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::getName(getType(atom), getIsotope(atom));
}

bool MolProp::isChemicalElement(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isChemicalElement(getType(atom));
}

bool MolProp::isMainGroupElement(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isMainGroupElement(getType(atom));
}

bool MolProp::isMetal(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isMetal(getType(atom));
}

bool MolProp::isTransitionMetal(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isTransitionMetal(getType(atom));
}

bool MolProp::isNonMetal(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isNonMetal(getType(atom));
}

bool MolProp::isSemiMetal(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isSemiMetal(getType(atom));
}

bool MolProp::isHalogen(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isHalogen(getType(atom));
}

bool MolProp::isNobleGas(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::isNobleGas(getType(atom));
}

