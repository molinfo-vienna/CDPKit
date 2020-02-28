/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(AtomContainerTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

	BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);

	BOOST_CHECK(static_cast<AtomContainer&>(mol).getAtomsBegin() == static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsEnd() - static_cast<AtomContainer&>(mol).getAtomsBegin()) == 0);

//-----

	Atom& atom1 = mol.addAtom();

	BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);

	BOOST_CHECK(static_cast<AtomContainer&>(mol).getAtomsBegin() != static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsEnd() - static_cast<AtomContainer&>(mol).getAtomsBegin()) == 1);

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsBegin() + 1) == static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK(&*static_cast<AtomContainer&>(mol).getAtomsBegin() == &atom1);

//-----

	Atom& atom2 = mol.addAtom();

	BOOST_CHECK(mol.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);

	BOOST_CHECK(static_cast<AtomContainer&>(mol).getAtomsBegin() != static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsEnd() - static_cast<AtomContainer&>(mol).getAtomsBegin()) == 2);

	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsBegin() + 1) != static_cast<AtomContainer&>(mol).getAtomsEnd());
	BOOST_CHECK((static_cast<AtomContainer&>(mol).getAtomsBegin() + 2) == static_cast<AtomContainer&>(mol).getAtomsEnd());

	BOOST_CHECK(&*static_cast<AtomContainer&>(mol).getAtomsBegin() == &atom1);
	BOOST_CHECK(&*(static_cast<AtomContainer&>(mol).getAtomsBegin() + 1) == &atom2);
}

