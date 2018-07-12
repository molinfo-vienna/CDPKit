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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MOL2MoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Util/FileDataReader.hpp"

#include "OptimolLogReader.hpp"
#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MMFF94AtomTyperTest)
{
	using namespace CDPL;

	Chem::BasicMolecule mol;
	Util::FileDataReader<Chem::MOL2MoleculeReader> mol_reader(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94_hypervalent.mol2"));

	TestUtils::OptimolLogReader log_reader(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94_opti.log"));
	TestUtils::OptimolLogReader::SymbolicAtomTypeArray sym_types;
	TestUtils::OptimolLogReader::NumericAtomTypeArray num_types;

	ForceField::MMFF94AtomTyper atom_typer;
	Util::UIArray perc_num_types;
	Util::SArray perc_sym_types;
	std::size_t mol_idx = 0;

	while (mol_reader.read(mol)) {
		TestUtils::setupMMFF94TestSuiteMolecule(mol);
		ForceField::perceiveMMFF94AromaticRings(mol, false);

		const std::string& mol_name = getName(mol);

		BOOST_CHECK(log_reader.getSymbolicAtomTypes(mol_name, sym_types));
		BOOST_CHECK_EQUAL(sym_types.size(), mol.getNumAtoms());

		BOOST_CHECK(log_reader.getNumericAtomTypes(mol_name, num_types));
		BOOST_CHECK_EQUAL(num_types.size(), mol.getNumAtoms());

		atom_typer.perceiveTypes(mol, perc_sym_types, perc_num_types, true);

		for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
			const std::string& correct_type = sym_types[i];
			const std::string& perceived_type = perc_sym_types[i];

			BOOST_CHECK_MESSAGE(perceived_type == correct_type, "Symbolic atom type mismatch for atom #" << i << " (" << getMOL2Name(mol.getAtom(i)) << 
								") of molecule #" << mol_idx << " (" << mol_name << "): " << perceived_type << " != " << correct_type);
		}
			
		for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
			unsigned int correct_type = num_types[i];
			unsigned int perceived_type = perc_num_types[i];

			BOOST_CHECK_MESSAGE(perceived_type == correct_type, "Numeric atom type mismatch for atom #" << i << " (" << getMOL2Name(mol.getAtom(i)) << 
								") of molecule #" << mol_idx << " (" << mol_name << "): " << perceived_type << " != " << correct_type);
		}
			
		mol_idx++;
		mol.clear();
	}
}
