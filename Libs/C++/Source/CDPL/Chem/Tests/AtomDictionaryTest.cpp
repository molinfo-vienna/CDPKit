/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDictionaryTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"


BOOST_AUTO_TEST_CASE(AtomDictionaryTest) // TODO
{
	using namespace CDPL;
	using namespace Chem;

	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::H, 0) == "H");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::H, 1) == "H");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::H, 2) == "D");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::H, 3) == "T");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::H, 4) == "");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::Cl, 4) == "");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::MAX_TYPE + 1, 0) == "");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::MAX_TYPE + 1, 300) == "");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::UNKNOWN, 0) == "");
	BOOST_CHECK(AtomDictionary::getSymbol(AtomType::UNKNOWN, 400) == "");
	BOOST_CHECK(AtomDictionary::getSymbol(0) == "");

//-----

	BOOST_CHECK(AtomDictionary::getName(AtomType::H, 0) == "Hydrogen");
	BOOST_CHECK(AtomDictionary::getName(AtomType::H, 1) == "Hydrogen");
	BOOST_CHECK(AtomDictionary::getName(AtomType::H, 2) == "Deuterium");
	BOOST_CHECK(AtomDictionary::getName(AtomType::H, 3) == "Tritium");
	BOOST_CHECK(AtomDictionary::getName(AtomType::H, 4) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::Cl, 4) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::Fe, 4) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::MAX_TYPE + 1, 0) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::MAX_TYPE + 1, 1) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::UNKNOWN, 1) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::UNKNOWN, 0) == "");
	BOOST_CHECK(AtomDictionary::getName(AtomType::UNKNOWN, 1) == "");
	BOOST_CHECK(AtomDictionary::getName(0) == "");

//-----

	BOOST_CHECK(AtomDictionary::getType("H") == AtomType::H);
	BOOST_CHECK(AtomDictionary::getType("D") == AtomType::H);
	BOOST_CHECK(AtomDictionary::getType("T") == AtomType::H);
	BOOST_CHECK(AtomDictionary::getType("Mt") == AtomType::Mt);
	BOOST_CHECK(AtomDictionary::getType("*") == AtomType::ANY);
	BOOST_CHECK(AtomDictionary::getType("MH") == AtomType::MH);
	BOOST_CHECK(AtomDictionary::getType("") == AtomType::UNKNOWN);
	BOOST_CHECK(AtomDictionary::getType("h", false) == AtomType::H);
	BOOST_CHECK(AtomDictionary::getType("fe", true) == AtomType::UNKNOWN);
	BOOST_CHECK(AtomDictionary::getType("fe", false) == AtomType::Fe);
	BOOST_CHECK(AtomDictionary::getType(" ") == AtomType::UNKNOWN);
	BOOST_CHECK(AtomDictionary::getType("-") == AtomType::UNKNOWN);

//-----

	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(AtomType::H) == 1);
	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(AtomType::C) == 12);
	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(AtomType::Cl) == 35);
	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(AtomType::UNKNOWN) == 0);
	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(AtomType::MAX_TYPE + 1) == 0);
	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(AtomType::ANY) == 0);
	BOOST_CHECK(AtomDictionary::getMostAbundantIsotope(0) == 0);

//-----

	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::H) == 1);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Be) == 2);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Sc) == 3);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Ti) == 4);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::V) == 5);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Cr) == 6);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Mn) == 7);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Fe) == 8);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Co) == 9);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Ni) == 10);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Cu) == 11);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Zn) == 12);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Ga) == 13);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Ge) == 14);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::As) == 15);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Se) == 16);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::Br) == 17);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::He) == 18);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::UNKNOWN) == 0);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::MAX_TYPE + 1) == 0);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(AtomType::ANY) == 0);
	BOOST_CHECK(AtomDictionary::getIUPACGroup(0) == 0);

//-----

	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::H) == 1);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Be) == 2);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Sc) == 3);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Ti) == 4);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::V) == 5);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Cr) == 6);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Mn) == 7);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Fe) == 8);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Co) == 9);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Ni) == 10);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Cu) == 11);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Zn) == 12);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::B) == 3);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::C) == 4);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::P) == 5);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::O) == 6);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::Br) == 7);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::He) == 8);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::UNKNOWN) == 0);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::MAX_TYPE + 1) == 0);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(AtomType::ANY) == 0);
	BOOST_CHECK(AtomDictionary::getNumValenceElectrons(0) == 0);

//-----

	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::H, 0) == 1.00794);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::H, 1) == 1.0078503);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::H, 2) == 2.01410178);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::H, 3) == 3.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::C, 0) == 12.0107);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::C, 12) == 12.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::C, 13) == 13.00335483);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::UNKNOWN, 0) == 0.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::UNKNOWN, 1) == 1.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::ANY, 0) == 0.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::ANY, 3) == 3.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::MAX_TYPE + 1, 0) == 0.0);
	BOOST_CHECK(AtomDictionary::getAtomicWeight(AtomType::MAX_TYPE + 1, 9) == 9.0);

//-----

	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::H) == 1.2);
	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::C) == 1.7);
	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::N) == 1.55);
	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::O) == 1.52);
	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::Kr) == 2.02);
	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::UNKNOWN) == 0.0);
	BOOST_CHECK(AtomDictionary::getVdWRadius(AtomType::MAX_TYPE + 1) == 0.0);
	BOOST_CHECK(AtomDictionary::getVdWRadius(0) == 0.0);

//-----

	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::H) == 2.2);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::C) == 2.5);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::N) == 3.1);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::O) == 3.5);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::F) == 4.1);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::Cl) == 2.8);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::Li) == 1.0);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::UNKNOWN) == 0.0);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::Q) == 0.0);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(AtomType::MAX_TYPE + 1) == 0.0);
	BOOST_CHECK(AtomDictionary::getAllredRochowElectronegativity(0) == 0.0);

//-----

	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::H)[0] == 1);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::H).getSize() == 1);

	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::Bi)[0] == 3);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::Bi)[1] == 2);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::Bi)[2] == 4);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::Bi)[3] == 5);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::Bi).getSize() == 4);

	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::C)[0] == 4);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::C)[1] == 2);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::C).getSize() == 2);

	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::UNKNOWN).getSize() == 0);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::X).getSize() == 0);
	BOOST_CHECK(AtomDictionary::getValenceStates(AtomType::MAX_TYPE + 1).getSize() == 0);
	BOOST_CHECK(AtomDictionary::getValenceStates(0).getSize() == 0);

//-----

	BOOST_CHECK(AtomDictionary::isChemicalElement(AtomType::H));
	BOOST_CHECK(AtomDictionary::isChemicalElement(AtomType::Mt));
	BOOST_CHECK(AtomDictionary::isChemicalElement(AtomType::Pt));
	BOOST_CHECK(!AtomDictionary::isChemicalElement(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isChemicalElement(AtomType::XH));
	BOOST_CHECK(!AtomDictionary::isChemicalElement(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isChemicalElement(0));

//-----

	BOOST_CHECK(AtomDictionary::isMainGroupElement(AtomType::H));
	BOOST_CHECK(AtomDictionary::isMainGroupElement(AtomType::He));
	BOOST_CHECK(AtomDictionary::isMainGroupElement(AtomType::Li));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(AtomType::Mo));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(AtomType::Ti));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(AtomType::M));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(AtomType::X));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isMainGroupElement(0));

//-----

	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::H));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::He));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::Li));
	BOOST_CHECK(AtomDictionary::isTransitionMetal(AtomType::Pr));
	BOOST_CHECK(AtomDictionary::isTransitionMetal(AtomType::Mo));
	BOOST_CHECK(AtomDictionary::isTransitionMetal(AtomType::Ti));
	BOOST_CHECK(AtomDictionary::isTransitionMetal(AtomType::Hg));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::Q));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::MH));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isTransitionMetal(0));

//-----

	BOOST_CHECK(!AtomDictionary::isMetal(AtomType::H));
	BOOST_CHECK(!AtomDictionary::isMetal(AtomType::He));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Li));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Pr));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Mo));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Ti));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Hg));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Si));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::Ge));
	BOOST_CHECK(AtomDictionary::isMetal(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isMetal(AtomType::Q));
	BOOST_CHECK(!AtomDictionary::isMetal(AtomType::MH));
	BOOST_CHECK(!AtomDictionary::isMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isMetal(0));

//-----

	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::H));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::He));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::Li));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::Pr));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::Mo));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::Ti));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::Hg));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::B));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::Si));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::Ge));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::As));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::Se));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::Sb));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::Te));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::Po));
	BOOST_CHECK(AtomDictionary::isSemiMetal(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::Q));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::MH));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isSemiMetal(0));

//-----

	BOOST_CHECK(AtomDictionary::isNonMetal(AtomType::H));
	BOOST_CHECK(AtomDictionary::isNonMetal(AtomType::He));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::Li));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::Pr));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::Mo));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::Ti));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::Hg));
	BOOST_CHECK(AtomDictionary::isNonMetal(AtomType::Si));
	BOOST_CHECK(AtomDictionary::isNonMetal(AtomType::Ge));
	BOOST_CHECK(AtomDictionary::isNonMetal(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::Q));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::MH));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isNonMetal(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isNonMetal(0));

//-----

	BOOST_CHECK(AtomDictionary::isHalogen(AtomType::F));
	BOOST_CHECK(AtomDictionary::isHalogen(AtomType::Cl));
	BOOST_CHECK(AtomDictionary::isHalogen(AtomType::Br));
	BOOST_CHECK(AtomDictionary::isHalogen(AtomType::I));
	BOOST_CHECK(AtomDictionary::isHalogen(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::H));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::He));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Li));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Pr));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Mo));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Ti));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Hg));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Si));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Ge));
	BOOST_CHECK(AtomDictionary::isHalogen(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::Q));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::MH));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isHalogen(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isHalogen(0));

//-----

	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::F));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Cl));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Br));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::I));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::H));
	BOOST_CHECK(AtomDictionary::isNobleGas(AtomType::He));
	BOOST_CHECK(AtomDictionary::isNobleGas(AtomType::Xe));
	BOOST_CHECK(AtomDictionary::isNobleGas(AtomType::Kr));
	BOOST_CHECK(AtomDictionary::isNobleGas(AtomType::Ne));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Li));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Pr));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Mo));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Ti));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Hg));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Si));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Ge));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::At));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::Q));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::MH));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::UNKNOWN));
	BOOST_CHECK(!AtomDictionary::isNobleGas(AtomType::MAX_TYPE + 1));
	BOOST_CHECK(!AtomDictionary::isNobleGas(0));
}
