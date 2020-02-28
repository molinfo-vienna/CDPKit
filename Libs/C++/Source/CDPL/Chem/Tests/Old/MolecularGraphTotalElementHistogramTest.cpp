/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphTotalElementHistogramTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomTypes.hpp"
#include "CDPL/Chem/ElementHistogram.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MolecularGraphTotalElementHistogramTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

//-----

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

	const ElementHistogram* histogram = &mol.getProperty<ElementHistogram>(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM);

	BOOST_CHECK(histogram->getSize() == 0);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

//-----

	std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs);

	BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

	histogram = &mol.getProperty<ElementHistogram>(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM);

	BOOST_CHECK((*histogram)[AtomType::H] == 19);
	BOOST_CHECK((*histogram)[AtomType::C] == 17);
	BOOST_CHECK((*histogram)[AtomType::N] == 1);
	BOOST_CHECK((*histogram)[AtomType::O] == 3);
	BOOST_CHECK((*histogram)[AtomType::S] == 0);

	BOOST_CHECK(histogram->getSize() == 4);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

//-----

	mol.getAtom(0).setProperty(AtomProperty::TYPE, AtomType::N);

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

	histogram = &mol.getProperty<ElementHistogram>(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM);

	BOOST_CHECK((*histogram)[AtomType::H] == 19);
	BOOST_CHECK((*histogram)[AtomType::C] == 16);
	BOOST_CHECK((*histogram)[AtomType::N] == 2);
	BOOST_CHECK((*histogram)[AtomType::O] == 3);
	BOOST_CHECK((*histogram)[AtomType::S] == 0);

	BOOST_CHECK(histogram->getSize() == 4);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

//-----

	mol.getAtom(1).setProperty(AtomProperty::TYPE, AtomType::MAX_ATOMIC_NO + 1);

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

	histogram = &mol.getProperty<ElementHistogram>(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM);

	BOOST_CHECK((*histogram)[AtomType::UNKNOWN] == 1);
	BOOST_CHECK((*histogram)[AtomType::H] == 19);
	BOOST_CHECK((*histogram)[AtomType::C] == 15);
	BOOST_CHECK((*histogram)[AtomType::N] == 2);
	BOOST_CHECK((*histogram)[AtomType::O] == 3);
	BOOST_CHECK((*histogram)[AtomType::S] == 0);

	BOOST_CHECK(histogram->getSize() == 5);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

//-----

	mol.getAtom(2).setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

	histogram = &mol.getProperty<ElementHistogram>(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM);

	BOOST_CHECK((*histogram)[AtomType::UNKNOWN] == 2);
	BOOST_CHECK((*histogram)[AtomType::H] == 18);
	BOOST_CHECK((*histogram)[AtomType::C] == 14);
	BOOST_CHECK((*histogram)[AtomType::N] == 2);
	BOOST_CHECK((*histogram)[AtomType::O] == 3);
	BOOST_CHECK((*histogram)[AtomType::S] == 0);

	BOOST_CHECK(histogram->getSize() == 5);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, false, false).isEmpty());

//-----

	TestUtils::checkDependency(mol, MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, mol, AtomContainerProperty::ATOM_COUNT);
	TestUtils::checkDependency(mol, MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, mol, MolecularGraphProperty::IMPLICIT_H_COUNT);

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
		TestUtils::checkDependency(mol, MolecularGraphProperty::TOTAL_ELEMENT_HISTOGRAM, *it, AtomProperty::TYPE);
}
