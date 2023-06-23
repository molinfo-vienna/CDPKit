/* 
 * BondContainerBondCountTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"


BOOST_AUTO_TEST_CASE(BondContainerBondCountTest)
{
    using namespace CDPL;
    using namespace Chem;

    Molecule mol1;

    BOOST_CHECK(mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumBonds() == 0);
    BOOST_CHECK(mol1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

    BOOST_CHECK(!mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol1.addAtom();
    mol1.addAtom();
    mol1.addAtom();
    mol1.addAtom();

    BOOST_CHECK(!mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol1.addBond(0, 1);
    mol1.addBond(1, 2);
    mol1.addBond(2, 3);

    BOOST_CHECK(mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

//-----

    BOOST_CHECK(mol1.getNumBonds() == 3);
    BOOST_CHECK(mol1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 3);

    BOOST_CHECK(!mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol1.addBond(0, 3, mol1.getBond(0));

    BOOST_CHECK(mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumBonds() == 4);
    BOOST_CHECK(mol1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 4);

    BOOST_CHECK(!mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    Molecule mol3(mol1);

    mol1.removeBond(2);

    BOOST_CHECK(mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumBonds() == 3);
    BOOST_CHECK(mol1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 3);

    BOOST_CHECK(!mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol1.removeBond(mol1.getBondsBegin());

    BOOST_CHECK(mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumBonds() == 2);
    BOOST_CHECK(mol1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    Fragment frag1(mol1);
    Molecule mol2;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 0);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol2 = mol1;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());
    
    mol2 = mol1;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol2.clear();

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 0);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol2 = frag1;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());
    
    mol2 = frag1;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol2 += mol1;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 4);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 4);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol2 += frag1;

    BOOST_CHECK(mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumBonds() == 6);
    BOOST_CHECK(mol2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 6);

    BOOST_CHECK(!mol2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

//-----

    BOOST_CHECK(frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumBonds() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(!frag1.addBond(mol1.getBond(0)));

    BOOST_CHECK(!frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumBonds() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    frag1.removeBond(0);

    BOOST_CHECK(frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumBonds() == 1);
    BOOST_CHECK(frag1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 1);

    BOOST_CHECK(!frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    frag1 += mol1;

    BOOST_CHECK(frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumBonds() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    frag1 = mol1;

    BOOST_CHECK(frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumBonds() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    Fragment frag2;

    BOOST_CHECK(frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumBonds() == 0);
    BOOST_CHECK(frag2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

    BOOST_CHECK(!frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    frag2 = frag1;

    BOOST_CHECK(frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumBonds() == 2);
    BOOST_CHECK(frag2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    frag2 = frag1;

    BOOST_CHECK(frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumBonds() == 2);
    BOOST_CHECK(frag2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    frag2.clear();

    BOOST_CHECK(frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumBonds() == 0);
    BOOST_CHECK(frag2.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

    BOOST_CHECK(!frag2.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

//-----

    BOOST_CHECK(mol3.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol3.getNumBonds() == 4);
    BOOST_CHECK(mol3.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 4);

    BOOST_CHECK(!mol3.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol3.getAtom(0).getNumBonds() == 2);
    BOOST_CHECK(mol3.getAtom(0).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol3.addAtom();

    BOOST_CHECK(!mol3.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(!mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());
    
    mol3.addBond(0, 2);

    BOOST_CHECK(mol3.getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol3.getAtom(0).getNumBonds() == 3);
    BOOST_CHECK(mol3.getAtom(0).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 3);

    BOOST_CHECK(!mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    mol3.removeBond(--mol3.getBondsEnd());

    BOOST_CHECK(mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol3.getAtom(0).getNumBonds() == 2);
    BOOST_CHECK(mol3.getAtom(0).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);

    BOOST_CHECK(!mol3.getAtom(0).getProperty(BondContainerProperty::BOND_COUNT, false, false).isEmpty());
}

