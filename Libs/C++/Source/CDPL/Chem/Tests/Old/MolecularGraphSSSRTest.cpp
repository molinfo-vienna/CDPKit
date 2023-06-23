/* 
 * MolecularGraphSSSRTest.cpp 
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


BOOST_AUTO_TEST_CASE(MolecularGraphSSSRTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace std::placeholders;
	
	Molecule mol;

//-----

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::SSSR, false, false).isEmpty());

	BOOST_CHECK(mol.getProperty<FragmentList>(MolecularGraphProperty::SSSR).getSize() == 0);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::SSSR, false, false).isEmpty());

//-----

	std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Fullerene2.jme").c_str());

	BOOST_CHECK(ifs);

	BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::SSSR, false, false).isEmpty());

	const FragmentList& sssr = mol.getProperty<FragmentList>(MolecularGraphProperty::SSSR);

	BOOST_CHECK(sssr.getSize() == 31);

	BOOST_CHECK(std::count_if(sssr.getElementsBegin(), sssr.getElementsEnd(), 
							  std::bind(std::equal_to<std::size_t>(), 5, std::bind(&Fragment::getNumBonds, _1))) == 12);
	BOOST_CHECK(std::count_if(sssr.getElementsBegin(), sssr.getElementsEnd(), 
							  std::bind(std::equal_to<std::size_t>(), 6, std::bind(&Fragment::getNumBonds, _1))) == 19);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::SSSR, false, false).isEmpty());

//-----

	TestUtils::checkDependency(mol, MolecularGraphProperty::SSSR, mol, AtomContainerProperty::ATOM_COUNT);
	TestUtils::checkDependency(mol, MolecularGraphProperty::SSSR, mol, BondContainerProperty::BOND_COUNT);

//-----

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
		TestUtils::checkDependency(mol, MolecularGraphProperty::SSSR, *it, BondContainerProperty::BOND_COUNT);

//-----

	mol.getProperty<FragmentList>(MolecularGraphProperty::SSSR);

	BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::SSSR, false, false).isEmpty());

	mol.addAtom();

	BOOST_CHECK(mol.getProperty(MolecularGraphProperty::SSSR, false, false).isEmpty());
}
