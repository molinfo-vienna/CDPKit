/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TPSACalculatorTest.cpp 
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


#include <cstddef>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/TPSACalculator.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


namespace
{

    struct TestDataEntry
    {

	std::string smiles;
	double      tpsa;
    };

    TestDataEntry testData[] = {
        { "CC(C)NCC(COC1=CC=C(C=C1)CCOC)O", 50.7 },
		{ "C1C(=O)NC2=C(C=C(C=C2)Cl)C(=N1)C3=CC=CC=C3", 41.5 },
		{ "CN1C(=O)CN=C(C2=C1C=CC(=C2)Cl)C3=CC=CC=C3", 32.7 },
		{ "CC(C)NCC(COC1=CC=CC=C1OCC=C)O", 50.7 },
		{ "CC1=CC(=O)N(N1C)C2=CC=CC=C2", 23.55 },                         // changed, aromaticity perception
		{ "C1=CC=C(C=C1)C2=NC(C(=O)NC3=C2C=C(C=C3)Cl)O", 61.7 },
		{ "CC(C)NCC(COC1=CC=CC=C1CC=C)O", 41.49 },                        // error in paper, typo
		{ "CC(C)NCC(COC1=CC=C(C=C1)NC(=O)C)O", 70.6 },
		{ "CC(C)NCC(COC1=CC=CC2=C1C=CN2)O", 57.3 },
		{ "C1CC1N2C=C(C(=O)C3=CC(=C(C=C32)N4CCNCC4)F)C(=O)O", 72.88 },    // changed, aromaticity perception 
		{ "CC1NC2=CC(=C(C=C2C(=O)N1C3=CC=CC=C3C)S(=O)(=O)N)Cl", 100.88 }, // error in paper, sulfur was not counted 
		{ "C1CC(CCC1CN)C(=O)O", 63.3 },
		{ "CC(C)NCC(COC1=CC=C(C=C1)CC(=O)N)O", 84.6 },
		{ "CCN1CCCC1CNC(=O)C2=C(C=CC(=C2)S(=O)(=O)N)OC", 110.11 },        // error in paper, sulfur was not counted 
		{ "C(C(C(C(C(CO)O)O)O)O)O", 121.4 },
		{ "C(=O)(O)P(=O)(O)O", 104.64 },                                  // error in paper, phosphor was not counted 
		{ "OC(=O)C1=CC(=CC=C1O)N=NC1=CC=C(C=C1)S(=O)(=O)NC1=NC=CC=C1", 149.69 },  // error in paper, sulfur was not counted 
		{ "OC(=O)C1=CC(=CC=C1O)N=NC1=CC=C(O)C(=C1)C(O)=O", 139.8 },  
		{ "C(C1C(C(C(C(O1)OC2C(OC(C2O)(CO)O)CO)O)O)O)O", 189.53 },        // changed, different form in paper
		{ "C(C1C(C(C(C(O1)OCC2C(C(C(C(O2)OC3(C(C(C(O3)CO)O)O)CO)O)O)O)O)O)O)O", 268.7 }
    };
}

BOOST_AUTO_TEST_CASE(TPSACalculatorTest)
{
    using namespace CDPL;
    using namespace Chem;

    TPSACalculator calculator;
    BasicMolecule mol;

    for (std::size_t i = 0; i < sizeof(testData) / sizeof(TestDataEntry); i++) {
		mol.clear();
		parseSMILES(testData[i].smiles, mol);

		perceiveComponents(mol, false);
		perceiveSSSR(mol, false);
		setRingFlags(mol, false);
		calcImplicitHydrogenCounts(mol, false);
		perceiveHybridizationStates(mol, false);
		setAromaticityFlags(mol, false);

		BOOST_CHECK_CLOSE(calculator.calculate(mol), testData[i].tpsa, 0.1);
    }
}

