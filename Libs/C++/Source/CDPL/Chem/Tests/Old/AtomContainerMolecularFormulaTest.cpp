/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerMolecularFormulaTest.cpp 
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


#include <string>
#include <cstdlib>
#include <fstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomTypes.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(AtomContainerMolecularFormulaTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

//-----

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MOLECULAR_FORMULA) == "");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

//-----

	std::ifstream ifs(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs);

	BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MOLECULAR_FORMULA) == "C17H2NO3");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

//-----

	mol.getAtom(0).setProperty(AtomProperty::TYPE, AtomType::N);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MOLECULAR_FORMULA) == "C16H2N2O3");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

//-----

	mol.getAtom(1).setProperty(AtomProperty::TYPE, AtomType::MAX_ATOMIC_NO + 1);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MOLECULAR_FORMULA) == "C15H2N2O3?");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

//-----

	mol.getAtom(2).setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MOLECULAR_FORMULA) == "C14H2N2O3?2");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MOLECULAR_FORMULA, false, false).isEmpty());

//-----

	TestUtils::checkDependency(mol, AtomContainerProperty::MOLECULAR_FORMULA, mol, AtomContainerProperty::ATOM_COUNT);

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
		TestUtils::checkDependency(mol, AtomContainerProperty::MOLECULAR_FORMULA, *it, AtomProperty::TYPE);
}
