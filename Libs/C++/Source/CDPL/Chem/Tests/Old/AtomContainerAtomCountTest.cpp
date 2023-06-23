/* 
 * AtomContainerAtomCountTest.cpp 
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
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"


BOOST_AUTO_TEST_CASE(AtomContainerAtomCountTest)
{
    using namespace CDPL;
    using namespace Chem;

    Molecule mol1;

    BOOST_CHECK(mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumAtoms() == 0);
    BOOST_CHECK(mol1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol1.addAtom();
    mol1.addAtom();
    mol1.addAtom();

    BOOST_CHECK(mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

//-----

    BOOST_CHECK(mol1.getNumAtoms() == 3);
    BOOST_CHECK(mol1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 3);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol1.addAtom(mol1.getAtom(0));

    BOOST_CHECK(mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumAtoms() == 4);
    BOOST_CHECK(mol1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 4);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol1.removeAtom(2);

    BOOST_CHECK(mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumAtoms() == 3);
    BOOST_CHECK(mol1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 3);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol1.removeAtom(mol1.getAtomsBegin());

    BOOST_CHECK(mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getNumAtoms() == 2);
    BOOST_CHECK(mol1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    Fragment frag1(mol1);
    Molecule mol2;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 0);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol2 = mol1;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());
    
    mol2 = mol1;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol2.clear();

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 0);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol2 = frag1;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());
    
    mol2 = frag1;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 2);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol2 += mol1;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 4);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 4);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol2 += frag1;

    BOOST_CHECK(mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol2.getNumAtoms() == 6);
    BOOST_CHECK(mol2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 6);

    BOOST_CHECK(!mol2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

//-----

    BOOST_CHECK(frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(!frag1.addAtom(mol1.getAtom(0)));

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag1.removeAtom(0);

    BOOST_CHECK(frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 1);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag1.removeAtom(frag1.getAtomsBegin());

    BOOST_CHECK(frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 0);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag1 += mol1;

    BOOST_CHECK(frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag1 = mol1;

    BOOST_CHECK(frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag1 = mol1;

    BOOST_CHECK(frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag1.getNumAtoms() == 2);
    BOOST_CHECK(frag1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    Fragment frag2;

    BOOST_CHECK(frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumAtoms() == 0);
    BOOST_CHECK(frag2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag2 = frag1;

    BOOST_CHECK(frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumAtoms() == 2);
    BOOST_CHECK(frag2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag2 = frag1;

    BOOST_CHECK(frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumAtoms() == 2);
    BOOST_CHECK(frag2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    frag2.clear();

    BOOST_CHECK(frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(frag2.getNumAtoms() == 0);
    BOOST_CHECK(frag2.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!frag2.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

//-----

    mol1.addAtom();
    mol1.addAtom();

    BOOST_CHECK(mol1.getAtom(0).getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 4);

    BOOST_CHECK(mol1.getAtom(0).getNumAtoms() == 0);
    BOOST_CHECK(mol1.getAtom(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

    BOOST_CHECK(!mol1.getAtom(0).getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol1.addBond(0, 1);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getAtom(0).getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getAtom(0).getNumAtoms() == 1);
    BOOST_CHECK(mol1.getAtom(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);

    BOOST_CHECK(!mol1.getAtom(0).getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    mol1.addBond(0, 2);

    BOOST_CHECK(!mol1.getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getAtom(0).getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

    BOOST_CHECK(mol1.getAtom(0).getNumAtoms() == 2);
    BOOST_CHECK(mol1.getAtom(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

    BOOST_CHECK(!mol1.getAtom(0).getProperty(AtomContainerProperty::ATOM_COUNT, false, false).isEmpty());

//-----

    BOOST_CHECK(mol1.getBond(0).getNumAtoms() == 2);
    BOOST_CHECK(mol1.getBond(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);
}

