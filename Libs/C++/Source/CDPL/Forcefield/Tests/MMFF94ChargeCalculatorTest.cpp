/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AtomTyperTest.cpp 
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


#include <cstdlib>
#include <cmath>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Forcefield/MMFF94ChargeCalculator.hpp"
#include "CDPL/Forcefield/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MOL2MoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Util/FileDataReader.hpp"

#include "OptimolLogReader.hpp"
#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MMFF94ChargeCalculatorTest)
{
	using namespace CDPL;

	Chem::BasicMolecule mol;
	Util::FileDataReader<Chem::MOL2MoleculeReader> mol_reader(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94_hypervalent.mol2"));

	TestUtils::OptimolLogReader log_reader(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94_opti.log"));
	TestUtils::OptimolLogReader::AtomChargeArray part_charges;
	TestUtils::OptimolLogReader::AtomChargeArray form_charges;

	Forcefield::MMFF94ChargeCalculator charge_calc;
	Util::DArray calc_charges;
	std::size_t mol_idx = 0;

	while (mol_reader.read(mol)) {
		TestUtils::setupMMFF94TestSuiteMolecule(mol);
		Forcefield::perceiveMMFF94AromaticRings(mol, false);
		Forcefield::assignMMFF94AtomTypes(mol, true, false);
		Forcefield::assignMMFF94BondTypeIndices(mol, false);

		const std::string& mol_name = getName(mol);

		BOOST_CHECK(log_reader.getPartialAtomCharges(mol_name, part_charges));
		BOOST_CHECK_EQUAL(part_charges.size(), mol.getNumAtoms());

		BOOST_CHECK(log_reader.getFormalAtomCharges(mol_name, form_charges));
		BOOST_CHECK_EQUAL(form_charges.size(), mol.getNumAtoms());

		charge_calc.calculate(mol, calc_charges);

		for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
			double correct_charge = form_charges[i];
			double calc_charge = charge_calc.getFormalCharges()[i];

			if (std::abs(calc_charge - correct_charge) > 0.0005) {
				const Chem::Atom& atom = mol.getAtom(i);

				BOOST_MESSAGE("!! Formal charge mismatch for atom #" << i << " (" << getMOL2Name(atom) <<
							  ") of molecule #" << mol_idx << " (" << mol_name << "):");
				BOOST_CHECK_EQUAL(calc_charge, correct_charge);
			}
		}
		
		for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
			double correct_charge = part_charges[i];
			double calc_charge = calc_charges[i];

			if (std::abs(calc_charge - correct_charge) > 0.0006) {
				const Chem::Atom& atom = mol.getAtom(i);

				BOOST_MESSAGE("!! Partial charge mismatch for atom #" << i << " (" << getMOL2Name(atom) <<
							  ") of molecule #" << mol_idx << " (" << mol_name << "):");
				BOOST_CHECK_EQUAL(calc_charge, correct_charge);
			}
		}

		mol_idx++;
		mol.clear();
	}
}
