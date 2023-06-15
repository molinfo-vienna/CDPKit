/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphRingsTest.cpp 
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


#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <functional>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"

#include "TestUtils.hpp"


namespace
{

	void checkRingCount(const CDPL::Chem::FragmentList& frag_list, std::size_t size, std::size_t count)
	{
		using namespace CDPL;
		using namespace Chem;

		BOOST_CHECK(std::size_t(std::count_if(frag_list.getElementsBegin(), frag_list.getElementsEnd(), 
											  std::bind(std::equal_to<std::size_t>(), size, 
														std::bind(&Fragment::getNumBonds, std::placeholders::_1)))) == count);
	}
}


BOOST_AUTO_TEST_CASE(MolecularGraphRingsTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

//-----

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::RINGS, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<FragmentList>(MolecularGraphProperty::RINGS).getSize() == 0);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::RINGS, false, false).isEmpty());

//-----

	std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs);

	BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::RINGS, false, false).isEmpty());

	const FragmentList& rings = mol.getProperty<FragmentList>(MolecularGraphProperty::RINGS);

	BOOST_CHECK(rings.getSize() == 24);

	checkRingCount(rings, 5, 1);
	checkRingCount(rings, 6, 4);
	checkRingCount(rings, 8, 1);
	checkRingCount(rings, 9, 3);
	checkRingCount(rings, 10, 3);
	checkRingCount(rings, 11, 3);
	checkRingCount(rings, 12, 1);
	checkRingCount(rings, 13, 4);
	checkRingCount(rings, 14, 1);
	checkRingCount(rings, 15, 1);
	checkRingCount(rings, 17, 2);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::RINGS, false, false).isEmpty());

//-----

	TestUtils::checkDependency(mol, MolecularGraphProperty::RINGS, mol, AtomContainerProperty::ATOM_COUNT);
	TestUtils::checkDependency(mol, MolecularGraphProperty::RINGS, mol, BondContainerProperty::BOND_COUNT);

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
		TestUtils::checkDependency(mol, MolecularGraphProperty::RINGS, *it, BondContainerProperty::BOND_COUNT);

//-----

	mol.getProperty<FragmentList>(MolecularGraphProperty::RINGS);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::RINGS, false, false).isEmpty());

	mol.addAtom();

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::RINGS, false, false).isEmpty());
}
