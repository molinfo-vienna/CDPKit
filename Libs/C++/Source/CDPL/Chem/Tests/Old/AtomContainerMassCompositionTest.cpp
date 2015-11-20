/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerMassCompositionTest.cpp 
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
#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomTypes.hpp"
#include "CDPL/Chem/MassComposition.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(AtomContainerMassCompositionTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

//-----

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<MassComposition>(AtomContainerProperty::MASS_COMPOSITION).getSize() == 0);

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

//-----

	std::ifstream ifs(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs);

	BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

	const MassComposition* mass_comp = &mol.getProperty<MassComposition>(AtomContainerProperty::MASS_COMPOSITION);

	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::H], 0.00752, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::C], 0.76130, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::N], 0.05222, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::O], 0.17896, 0.1);
	BOOST_CHECK_SMALL((*mass_comp)[AtomType::B], 0.0000001);

	BOOST_CHECK(mass_comp->getSize() == 4);

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

//-----

	mol.getAtom(0).setProperty(AtomProperty::TYPE, AtomType::N);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

	mass_comp = &mol.getProperty<MassComposition>(AtomContainerProperty::MASS_COMPOSITION);

	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::H], 0.00746, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::C], 0.71122, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::N], 0.10368, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::O], 0.17764, 0.1);
	BOOST_CHECK_SMALL((*mass_comp)[AtomType::Li], 0.0000001);

	BOOST_CHECK(mass_comp->getSize() == 4);

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

//-----

	mol.getAtom(1).setProperty(AtomProperty::TYPE, AtomType::MAX_ATOMIC_NO + 1);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

	mass_comp = &mol.getProperty<MassComposition>(AtomContainerProperty::MASS_COMPOSITION);

	BOOST_CHECK_SMALL((*mass_comp)[AtomType::UNKNOWN], 0.00001);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::H], 0.00781, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::C], 0.69779, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::N], 0.10850, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::O], 0.18590, 0.1);
	BOOST_CHECK_SMALL((*mass_comp)[AtomType::F], 0.0000001);

	BOOST_CHECK(mass_comp->getSize() == 5);

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

//-----

	mol.getAtom(2).setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

	mass_comp = &mol.getProperty<MassComposition>(AtomContainerProperty::MASS_COMPOSITION);

	BOOST_CHECK_SMALL((*mass_comp)[AtomType::UNKNOWN], 0.00001);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::H], 0.00819, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::C], 0.68304, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::N], 0.11379, 0.1);
	BOOST_CHECK_CLOSE((*mass_comp)[AtomType::O], 0.19497, 0.1);
	BOOST_CHECK_SMALL((*mass_comp)[AtomType::I], 0.0000001);

	BOOST_CHECK(mass_comp->getSize() == 5);

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
		it->setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

	BOOST_CHECK(mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

	mass_comp = &mol.getProperty<MassComposition>(AtomContainerProperty::MASS_COMPOSITION);

	BOOST_CHECK(std::isnan((*mass_comp)[AtomType::UNKNOWN]));
	BOOST_CHECK_SMALL((*mass_comp)[AtomType::C], 0.000001);

	BOOST_CHECK(mass_comp->getSize() == 1);

	BOOST_CHECK(!mol.getProperty(AtomContainerProperty::MASS_COMPOSITION, false, false).isEmpty());

//-----
	
	TestUtils::checkDependency(mol, AtomContainerProperty::MASS_COMPOSITION, mol, AtomContainerProperty::ATOM_COUNT);

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
		TestUtils::checkDependency(mol, AtomContainerProperty::MASS_COMPOSITION, *it, AtomProperty::ATOMIC_WEIGHT);
		TestUtils::checkDependency(mol, AtomContainerProperty::MASS_COMPOSITION, *it, AtomProperty::TYPE);
	}
}
