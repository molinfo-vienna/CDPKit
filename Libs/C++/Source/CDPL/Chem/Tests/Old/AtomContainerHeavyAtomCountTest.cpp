/* 
 * AtomContainerHeavyAtomCountTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(AtomContainerHeavyAtomCountTest)
{
    using namespace CDPL;
    using namespace Chem;

    Molecule mol;

//-----

    BOOST_CHECK(mol.getProperty(AtomContainerProperty::HEAVY_ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::HEAVY_ATOM_COUNT) == 0);

    BOOST_CHECK(!mol.getProperty(AtomContainerProperty::HEAVY_ATOM_COUNT, false, false).isEmpty());

//-----

    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

    BOOST_CHECK(ifs);

    BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

//-----

    BOOST_CHECK(mol.getProperty(AtomContainerProperty::HEAVY_ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::HEAVY_ATOM_COUNT) == 21);

    BOOST_CHECK(!mol.getProperty(AtomContainerProperty::HEAVY_ATOM_COUNT, false, false).isEmpty());

    TestUtils::checkDependency(mol, AtomContainerProperty::HEAVY_ATOM_COUNT, mol, AtomContainerProperty::ATOM_COUNT);

//-----

    Fragment frag(mol);

    BOOST_CHECK(frag.getProperty(AtomContainerProperty::HEAVY_ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag.getProperty<std::size_t>(AtomContainerProperty::HEAVY_ATOM_COUNT) == 21);

    BOOST_CHECK(!frag.getProperty(AtomContainerProperty::HEAVY_ATOM_COUNT, false, false).isEmpty());

    TestUtils::checkDependency(frag, AtomContainerProperty::HEAVY_ATOM_COUNT, frag, AtomContainerProperty::ATOM_COUNT);

//-----

    for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
        TestUtils::checkDependency(mol, AtomContainerProperty::HEAVY_ATOM_COUNT, *it, AtomProperty::TYPE);
}
