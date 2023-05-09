/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"


BOOST_AUTO_TEST_CASE(MolecularGraphTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

	BOOST_CHECK(static_cast<AtomContainer&>(mol).getAtomsBegin() == static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsEnd() - static_cast<AtomContainer&>(mol).getAtomsBegin()) == 0);

	BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

//-----

	Atom& atom1 = mol.addAtom();

	atom1.setProperty(AtomProperty::SYMBOL, std::string("C"));

	BOOST_CHECK(static_cast<AtomContainer&>(mol).getAtomsBegin() != static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsEnd() - static_cast<AtomContainer&>(mol).getAtomsBegin()) == 1);

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsBegin() + 1) == static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK(&*static_cast<AtomContainer&>(mol).getAtomsBegin() == &atom1);

	BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);

	BOOST_CHECK(mol.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_ATOM_COUNT) == 5);
	BOOST_CHECK(mol.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_BOND_COUNT) == 4);

//-----

	Atom& atom2 = mol.addAtom();

	atom2.setProperty(AtomProperty::SYMBOL, std::string("O"));

	BOOST_CHECK(static_cast<AtomContainer&>(mol).getAtomsBegin() != static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsEnd() - static_cast<AtomContainer&>(mol).getAtomsBegin()) == 2);

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsBegin() + 1) != static_cast<AtomContainer&>(mol).getAtomsEnd());
	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsBegin() + 2) == static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK(&*static_cast<AtomContainer&>(mol).getAtomsBegin() == &atom1);
	BOOST_CHECK(&*(static_cast<AtomContainer&>(mol).getAtomsBegin() + 1) == &atom2);

	BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

	BOOST_CHECK(mol.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_ATOM_COUNT) == 8);
	BOOST_CHECK(mol.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_BOND_COUNT) == 6);

//-----

	BOOST_CHECK(static_cast<MolecularGraph&>(mol).getBondsBegin() == static_cast<MolecularGraph&>(mol).getBondsEnd());

	BOOST_CHECK((static_cast<MolecularGraph&>(mol).getBondsEnd() - static_cast<MolecularGraph&>(mol).getBondsBegin()) == 0);

	BOOST_CHECK(mol.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

//-----

	Bond& bond1 = mol.addBond(0, 1);

	bond1.setProperty(BondProperty::ORDER, std::size_t(2));

	BOOST_CHECK(static_cast<MolecularGraph&>(mol).getBondsBegin() != static_cast<MolecularGraph&>(mol).getBondsEnd());

	BOOST_CHECK((static_cast<MolecularGraph&>(mol).getBondsEnd() - static_cast<MolecularGraph&>(mol).getBondsBegin()) == 1);

	BOOST_CHECK((static_cast<MolecularGraph&>(mol).getBondsBegin() + 1) == static_cast<MolecularGraph&>(mol).getBondsEnd());

	BOOST_CHECK(&*static_cast<MolecularGraph&>(mol).getBondsBegin() == &bond1);

	BOOST_CHECK(mol.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 1);

	BOOST_CHECK(mol.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_ATOM_COUNT) == 4);
	BOOST_CHECK(mol.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_BOND_COUNT) == 3);
}
