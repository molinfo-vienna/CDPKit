/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94ChargeCalculatorTest.cpp 
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


#include <cstddef>
#include <cmath>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/ForceField/MMFF94ChargeCalculator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"


BOOST_AUTO_TEST_CASE(MMFF94ChargeCalculatorTest)
{
	using namespace CDPL;
	using namespace Testing;

	OptimolLogReader::AtomChargeArray part_charges;
	OptimolLogReader::AtomChargeArray form_charges;

	ForceField::MMFF94ChargeCalculator charge_calc;
	Util::DArray calc_charges;

	for (std::size_t mol_idx = 0; mol_idx <	MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol =	*MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
		const std::string& mol_name = getName(mol);

		BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getPartialAtomCharges(mol_name, part_charges));
		BOOST_CHECK_EQUAL(part_charges.size(), mol.getNumAtoms());

		BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getFormalAtomCharges(mol_name, form_charges));
		BOOST_CHECK_EQUAL(form_charges.size(), mol.getNumAtoms());

		charge_calc.calculate(mol, calc_charges, true);

		for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
			double correct_charge = form_charges[i];
			double calc_charge = charge_calc.getFormalCharges()[i];

			BOOST_CHECK_MESSAGE(std::abs(calc_charge - correct_charge) <= 0.0005, "Formal charge mismatch for atom #" << i << "(" << getMOL2Name(mol.getAtom(i)) <<
								") of molecule #" << mol_idx << " (" << mol_name << "): " << calc_charge << " != " << correct_charge);
		}
		
		for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
			double correct_charge = part_charges[i];
			double calc_charge = calc_charges[i];
		
			BOOST_CHECK_MESSAGE(std::abs(calc_charge - correct_charge) <= 0.0006, "Partial charge mismatch for atom #" << i << "(" << getMOL2Name(mol.getAtom(i)) <<
								") of molecule #" << mol_idx << " (" << mol_name << "): " << calc_charge << " != " << correct_charge);
		}
	}
}
