/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerMassCompositionStringTest.cpp 
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
#include <locale>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomTypes.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(AtomContainerMassCompositionStringTest)
{
	using namespace CDPL;
	using namespace Chem;

	std::locale::global(std::locale::classic());

	Molecule mol;

//-----

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == "");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

	std::ifstream ifs(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs);

	BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == 
				"H: 0.752% C: 76.130% N: 5.222% O: 17.896%");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

	mol.getAtom(0).setProperty(AtomProperty::TYPE, AtomType::N);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == 
				"H: 0.746% C: 71.122% N: 10.368% O: 17.764%");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

	mol.getAtom(1).setProperty(AtomProperty::TYPE, AtomType::MAX_ATOMIC_NO + 1);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == 
				"?: 0.000% H: 0.781% C: 69.779% N: 10.850% O: 18.590%");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

	mol.getAtom(2).setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == 
				"?: 0.000% H: 0.819% C: 68.304% N: 11.379% O: 19.497%");

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
		it->setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == 
				"?: nan%" ||
				mol.getProperty<std::string>(AtomContainerProperty::MASS_COMPOSITION_STRING) == 
				"?: -nan%" );

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

	TestUtils::checkDependency(mol, AtomContainerProperty::MASS_COMPOSITION_STRING, mol,
							   AtomContainerProperty::MASS_COMPOSITION);
}
