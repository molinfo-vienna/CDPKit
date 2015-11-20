/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTypeFunctionsTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/AtomTypeFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


BOOST_AUTO_TEST_CASE(AtomTypeFunctionsTest)
{
	using namespace CDPL;
	using namespace Chem;

	BOOST_CHECK(getAtomTypeSymbol(AtomType::H, 0) == "H");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::H, 1) == "H");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::H, 2) == "D");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::H, 3) == "T");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::H, 4) == "H");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::Cl, 4) == "Cl");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::MAX_TYPE + 1, 0) == "");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::MAX_TYPE + 1, 300) == "");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::UNKNOWN, 0) == "");
	BOOST_CHECK(getAtomTypeSymbol(AtomType::UNKNOWN, 400) == "");
	BOOST_CHECK(getAtomTypeSymbol(0) == "");

//-----

	BOOST_CHECK(getElementName(AtomType::H, 0) == "Hydrogen");
	BOOST_CHECK(getElementName(AtomType::H, 1) == "Hydrogen");
	BOOST_CHECK(getElementName(AtomType::H, 2) == "Deuterium");
	BOOST_CHECK(getElementName(AtomType::H, 3) == "Tritium");
	BOOST_CHECK(getElementName(AtomType::H, 4) == "Hydrogen");
	BOOST_CHECK(getElementName(AtomType::Cl, 4) == "Chlorine");
	BOOST_CHECK(getElementName(AtomType::Fe, 4) == "Iron");
	BOOST_CHECK(getElementName(AtomType::MAX_TYPE + 1, 0) == "");
	BOOST_CHECK(getElementName(AtomType::MAX_TYPE + 1, 1) == "");
	BOOST_CHECK(getElementName(AtomType::UNKNOWN, 1) == "");
	BOOST_CHECK(getElementName(AtomType::UNKNOWN, 0) == "");
	BOOST_CHECK(getElementName(AtomType::UNKNOWN, 1) == "");
	BOOST_CHECK(getElementName(0) == "");

//-----

	BOOST_CHECK(getAtomType("H") == AtomType::H);
	BOOST_CHECK(getAtomType("D") == AtomType::H);
	BOOST_CHECK(getAtomType("T") == AtomType::H);
	BOOST_CHECK(getAtomType("Mt") == AtomType::Mt);
	BOOST_CHECK(getAtomType("*") == AtomType::ANY);
	BOOST_CHECK(getAtomType("MH") == AtomType::MH);
	BOOST_CHECK(getAtomType("") == AtomType::UNKNOWN);
	BOOST_CHECK(getAtomType("h") == AtomType::UNKNOWN);
	BOOST_CHECK(getAtomType("fe") == AtomType::UNKNOWN);
	BOOST_CHECK(getAtomType(" ") == AtomType::UNKNOWN);
	BOOST_CHECK(getAtomType("-") == AtomType::UNKNOWN);

//-----

	BOOST_CHECK(getMostAbundantIsotope(AtomType::H) == 1);
	BOOST_CHECK(getMostAbundantIsotope(AtomType::C) == 12);
	BOOST_CHECK(getMostAbundantIsotope(AtomType::Cl) == 35);
	BOOST_CHECK(getMostAbundantIsotope(AtomType::UNKNOWN) == 0);
	BOOST_CHECK(getMostAbundantIsotope(AtomType::MAX_TYPE + 1) == 0);
	BOOST_CHECK(getMostAbundantIsotope(AtomType::ANY) == 0);
	BOOST_CHECK(getMostAbundantIsotope(0) == 0);

//-----

	BOOST_CHECK(getIUPACGroup(AtomType::H) == 1);
	BOOST_CHECK(getIUPACGroup(AtomType::Be) == 2);
	BOOST_CHECK(getIUPACGroup(AtomType::Sc) == 3);
	BOOST_CHECK(getIUPACGroup(AtomType::Ti) == 4);
	BOOST_CHECK(getIUPACGroup(AtomType::V) == 5);
	BOOST_CHECK(getIUPACGroup(AtomType::Cr) == 6);
	BOOST_CHECK(getIUPACGroup(AtomType::Mn) == 7);
	BOOST_CHECK(getIUPACGroup(AtomType::Fe) == 8);
	BOOST_CHECK(getIUPACGroup(AtomType::Co) == 9);
	BOOST_CHECK(getIUPACGroup(AtomType::Ni) == 10);
	BOOST_CHECK(getIUPACGroup(AtomType::Cu) == 11);
	BOOST_CHECK(getIUPACGroup(AtomType::Zn) == 12);
	BOOST_CHECK(getIUPACGroup(AtomType::Ga) == 13);
	BOOST_CHECK(getIUPACGroup(AtomType::Ge) == 14);
	BOOST_CHECK(getIUPACGroup(AtomType::As) == 15);
	BOOST_CHECK(getIUPACGroup(AtomType::Se) == 16);
	BOOST_CHECK(getIUPACGroup(AtomType::Br) == 17);
	BOOST_CHECK(getIUPACGroup(AtomType::He) == 18);
	BOOST_CHECK(getIUPACGroup(AtomType::UNKNOWN) == 0);
	BOOST_CHECK(getIUPACGroup(AtomType::MAX_TYPE + 1) == 0);
	BOOST_CHECK(getIUPACGroup(AtomType::ANY) == 0);
	BOOST_CHECK(getIUPACGroup(0) == 0);

//-----

	BOOST_CHECK(getNumValenceElectrons(AtomType::H) == 1);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Be) == 2);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Sc) == 3);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Ti) == 4);
	BOOST_CHECK(getNumValenceElectrons(AtomType::V) == 5);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Cr) == 6);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Mn) == 7);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Fe) == 8);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Co) == 9);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Ni) == 10);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Cu) == 11);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Zn) == 12);
	BOOST_CHECK(getNumValenceElectrons(AtomType::B) == 3);
	BOOST_CHECK(getNumValenceElectrons(AtomType::C) == 4);
	BOOST_CHECK(getNumValenceElectrons(AtomType::P) == 5);
	BOOST_CHECK(getNumValenceElectrons(AtomType::O) == 6);
	BOOST_CHECK(getNumValenceElectrons(AtomType::Br) == 7);
	BOOST_CHECK(getNumValenceElectrons(AtomType::He) == 8);
	BOOST_CHECK(getNumValenceElectrons(AtomType::UNKNOWN) == 0);
	BOOST_CHECK(getNumValenceElectrons(AtomType::MAX_TYPE + 1) == 0);
	BOOST_CHECK(getNumValenceElectrons(AtomType::ANY) == 0);
	BOOST_CHECK(getNumValenceElectrons(0) == 0);

//-----

	BOOST_CHECK(getAtomicWeight(AtomType::H, 0) == 1.00794);
	BOOST_CHECK(getAtomicWeight(AtomType::H, 1) == 1.0078503);
	BOOST_CHECK(getAtomicWeight(AtomType::H, 2) == 2.01410178);
	BOOST_CHECK(getAtomicWeight(AtomType::H, 3) == 3.0);
	BOOST_CHECK(getAtomicWeight(AtomType::C, 0) == 12.0107);
	BOOST_CHECK(getAtomicWeight(AtomType::C, 12) == 12.0);
	BOOST_CHECK(getAtomicWeight(AtomType::C, 13) == 13.00335483);
	BOOST_CHECK(getAtomicWeight(AtomType::UNKNOWN, 0) == 0.0);
	BOOST_CHECK(getAtomicWeight(AtomType::UNKNOWN, 1) == 1.0);
	BOOST_CHECK(getAtomicWeight(AtomType::ANY, 0) == 0.0);
	BOOST_CHECK(getAtomicWeight(AtomType::ANY, 3) == 3.0);
	BOOST_CHECK(getAtomicWeight(AtomType::MAX_TYPE + 1, 0) == 0.0);
	BOOST_CHECK(getAtomicWeight(AtomType::MAX_TYPE + 1, 9) == 9.0);

//-----

	BOOST_CHECK(getVdWRadius(AtomType::H) == 1.2);
	BOOST_CHECK(getVdWRadius(AtomType::C) == 1.7);
	BOOST_CHECK(getVdWRadius(AtomType::N) == 1.55);
	BOOST_CHECK(getVdWRadius(AtomType::O) == 1.52);
	BOOST_CHECK(getVdWRadius(AtomType::Kr) == 2.02);
	BOOST_CHECK(getVdWRadius(AtomType::UNKNOWN) == 0.0);
	BOOST_CHECK(getVdWRadius(AtomType::MAX_TYPE + 1) == 0.0);
	BOOST_CHECK(getVdWRadius(0) == 0.0);

//-----

	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::H) == 2.2);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::C) == 2.5);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::N) == 3.1);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::O) == 3.5);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::F) == 4.1);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::Cl) == 2.8);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::Li) == 1.0);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::UNKNOWN) == 0.0);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::Q) == 0.0);
	BOOST_CHECK(getAllredRochowElectronegativity(AtomType::MAX_TYPE + 1) == 0.0);
	BOOST_CHECK(getAllredRochowElectronegativity(0) == 0.0);

//-----

	BOOST_CHECK(getValenceStates(AtomType::H)[0] == 1);
	BOOST_CHECK(getValenceStates(AtomType::H)[1] == -1);

	BOOST_CHECK(getValenceStates(AtomType::Bi)[0] == 3);
	BOOST_CHECK(getValenceStates(AtomType::Bi)[1] == 2);
	BOOST_CHECK(getValenceStates(AtomType::Bi)[2] == 4);
	BOOST_CHECK(getValenceStates(AtomType::Bi)[3] == 5);
	BOOST_CHECK(getValenceStates(AtomType::Bi)[4] == -1);

	BOOST_CHECK(getValenceStates(AtomType::C)[0] == 4);
	BOOST_CHECK(getValenceStates(AtomType::C)[1] == 2);
	BOOST_CHECK(getValenceStates(AtomType::C)[2] == -1);

	BOOST_CHECK(getValenceStates(AtomType::UNKNOWN)[0] == -1);
	BOOST_CHECK(getValenceStates(AtomType::X)[0] == -1);
	BOOST_CHECK(getValenceStates(AtomType::MAX_TYPE + 1)[0] == -1);
	BOOST_CHECK(getValenceStates(0)[0] == -1);

//-----

	BOOST_CHECK(isChemicalElement(AtomType::H));
	BOOST_CHECK(isChemicalElement(AtomType::Mt));
	BOOST_CHECK(isChemicalElement(AtomType::Pt));
	BOOST_CHECK(!isChemicalElement(AtomType::UNKNOWN));
	BOOST_CHECK(!isChemicalElement(AtomType::XH));
	BOOST_CHECK(!isChemicalElement(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isChemicalElement(0));

//-----

	BOOST_CHECK(isMainGroupElement(AtomType::H));
	BOOST_CHECK(isMainGroupElement(AtomType::He));
	BOOST_CHECK(isMainGroupElement(AtomType::Li));
	BOOST_CHECK(!isMainGroupElement(AtomType::Mo));
	BOOST_CHECK(!isMainGroupElement(AtomType::Ti));
	BOOST_CHECK(!isMainGroupElement(AtomType::M));
	BOOST_CHECK(!isMainGroupElement(AtomType::X));
	BOOST_CHECK(!isMainGroupElement(AtomType::UNKNOWN));
	BOOST_CHECK(!isMainGroupElement(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isMainGroupElement(0));

//-----

	BOOST_CHECK(!isTransitionMetal(AtomType::H));
	BOOST_CHECK(!isTransitionMetal(AtomType::He));
	BOOST_CHECK(!isTransitionMetal(AtomType::Li));
	BOOST_CHECK(isTransitionMetal(AtomType::Pr));
	BOOST_CHECK(isTransitionMetal(AtomType::Mo));
	BOOST_CHECK(isTransitionMetal(AtomType::Ti));
	BOOST_CHECK(isTransitionMetal(AtomType::Hg));
	BOOST_CHECK(!isTransitionMetal(AtomType::Q));
	BOOST_CHECK(!isTransitionMetal(AtomType::MH));
	BOOST_CHECK(!isTransitionMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!isTransitionMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isTransitionMetal(0));

//-----

	BOOST_CHECK(!isMetal(AtomType::H));
	BOOST_CHECK(!isMetal(AtomType::He));
	BOOST_CHECK(isMetal(AtomType::Li));
	BOOST_CHECK(isMetal(AtomType::Pr));
	BOOST_CHECK(isMetal(AtomType::Mo));
	BOOST_CHECK(isMetal(AtomType::Ti));
	BOOST_CHECK(isMetal(AtomType::Hg));
	BOOST_CHECK(isMetal(AtomType::Si));
	BOOST_CHECK(isMetal(AtomType::Ge));
	BOOST_CHECK(isMetal(AtomType::At));
	BOOST_CHECK(!isMetal(AtomType::Q));
	BOOST_CHECK(!isMetal(AtomType::MH));
	BOOST_CHECK(!isMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!isMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isMetal(0));

//-----

	BOOST_CHECK(!isSemiMetal(AtomType::H));
	BOOST_CHECK(!isSemiMetal(AtomType::He));
	BOOST_CHECK(!isSemiMetal(AtomType::Li));
	BOOST_CHECK(!isSemiMetal(AtomType::Pr));
	BOOST_CHECK(!isSemiMetal(AtomType::Mo));
	BOOST_CHECK(!isSemiMetal(AtomType::Ti));
	BOOST_CHECK(!isSemiMetal(AtomType::Hg));
	BOOST_CHECK(isSemiMetal(AtomType::B));
	BOOST_CHECK(isSemiMetal(AtomType::Si));
	BOOST_CHECK(isSemiMetal(AtomType::Ge));
	BOOST_CHECK(isSemiMetal(AtomType::As));
	BOOST_CHECK(isSemiMetal(AtomType::Se));
	BOOST_CHECK(isSemiMetal(AtomType::Sb));
	BOOST_CHECK(isSemiMetal(AtomType::Te));
	BOOST_CHECK(isSemiMetal(AtomType::Po));
	BOOST_CHECK(isSemiMetal(AtomType::At));
	BOOST_CHECK(!isSemiMetal(AtomType::Q));
	BOOST_CHECK(!isSemiMetal(AtomType::MH));
	BOOST_CHECK(!isSemiMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!isSemiMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isSemiMetal(0));

//-----

	BOOST_CHECK(isNonMetal(AtomType::H));
	BOOST_CHECK(isNonMetal(AtomType::He));
	BOOST_CHECK(!isNonMetal(AtomType::Li));
	BOOST_CHECK(!isNonMetal(AtomType::Pr));
	BOOST_CHECK(!isNonMetal(AtomType::Mo));
	BOOST_CHECK(!isNonMetal(AtomType::Ti));
	BOOST_CHECK(!isNonMetal(AtomType::Hg));
	BOOST_CHECK(isNonMetal(AtomType::Si));
	BOOST_CHECK(isNonMetal(AtomType::Ge));
	BOOST_CHECK(isNonMetal(AtomType::At));
	BOOST_CHECK(!isNonMetal(AtomType::Q));
	BOOST_CHECK(!isNonMetal(AtomType::MH));
	BOOST_CHECK(!isNonMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!isNonMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isNonMetal(0));

//-----

	BOOST_CHECK(isHalogen(AtomType::F));
	BOOST_CHECK(isHalogen(AtomType::Cl));
	BOOST_CHECK(isHalogen(AtomType::Br));
	BOOST_CHECK(isHalogen(AtomType::I));
	BOOST_CHECK(isHalogen(AtomType::At));
	BOOST_CHECK(!isHalogen(AtomType::H));
	BOOST_CHECK(!isHalogen(AtomType::He));
	BOOST_CHECK(!isHalogen(AtomType::Li));
	BOOST_CHECK(!isHalogen(AtomType::Pr));
	BOOST_CHECK(!isHalogen(AtomType::Mo));
	BOOST_CHECK(!isHalogen(AtomType::Ti));
	BOOST_CHECK(!isHalogen(AtomType::Hg));
	BOOST_CHECK(!isHalogen(AtomType::Si));
	BOOST_CHECK(!isHalogen(AtomType::Ge));
	BOOST_CHECK(isHalogen(AtomType::At));
	BOOST_CHECK(!isHalogen(AtomType::Q));
	BOOST_CHECK(!isHalogen(AtomType::MH));
	BOOST_CHECK(!isHalogen(AtomType::UNKNOWN));
	BOOST_CHECK(!isHalogen(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isHalogen(0));

//-----

	BOOST_CHECK(!isNobleGas(AtomType::F));
	BOOST_CHECK(!isNobleGas(AtomType::Cl));
	BOOST_CHECK(!isNobleGas(AtomType::Br));
	BOOST_CHECK(!isNobleGas(AtomType::I));
	BOOST_CHECK(!isNobleGas(AtomType::At));
	BOOST_CHECK(!isNobleGas(AtomType::H));
	BOOST_CHECK(isNobleGas(AtomType::He));
	BOOST_CHECK(isNobleGas(AtomType::Xe));
	BOOST_CHECK(isNobleGas(AtomType::Kr));
	BOOST_CHECK(isNobleGas(AtomType::Ne));
	BOOST_CHECK(!isNobleGas(AtomType::Li));
	BOOST_CHECK(!isNobleGas(AtomType::Pr));
	BOOST_CHECK(!isNobleGas(AtomType::Mo));
	BOOST_CHECK(!isNobleGas(AtomType::Ti));
	BOOST_CHECK(!isNobleGas(AtomType::Hg));
	BOOST_CHECK(!isNobleGas(AtomType::Si));
	BOOST_CHECK(!isNobleGas(AtomType::Ge));
	BOOST_CHECK(!isNobleGas(AtomType::At));
	BOOST_CHECK(!isNobleGas(AtomType::Q));
	BOOST_CHECK(!isNobleGas(AtomType::MH));
	BOOST_CHECK(!isNobleGas(AtomType::UNKNOWN));
	BOOST_CHECK(!isNobleGas(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!isNobleGas(0));
}
