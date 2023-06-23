/* 
 * AtomBondMappingTest.cpp 
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

#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Molecule.hpp"


BOOST_AUTO_TEST_CASE(AtomBondMappingTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol;

	Atom* lap1 = &mol.addAtom();
	Atom* rap1 = &mol.addAtom();

	Bond* lbp1 = &mol.addBond(0, 1);
	Bond* rbp1 = &mol.addBond(1, 0);

//-----

	AtomBondMapping m1;

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getAtomMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getAtomMapping().getSize() == 0);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getBondMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getBondMapping().getSize() == 0);

//-----

	m1.getAtomMapping().insertEntry(lap1, rap1);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getAtomMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getAtomMapping().getSize() == 1);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getBondMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getBondMapping().getSize() == 0);

//-----

	m1.getBondMapping().insertEntry(lbp1, rbp1);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getAtomMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getAtomMapping().getSize() == 1);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getBondMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getBondMapping().getSize() == 1);

//-----

	AtomBondMapping m2;

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m2).getAtomMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m2).getAtomMapping().getSize() == 0);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m2).getBondMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m2).getBondMapping().getSize() == 0);

	BOOST_CHECK(m2 != m1);
	BOOST_CHECK(m2 == m2);

	m2 = m1;

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m2).getAtomMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m2).getAtomMapping().getSize() == 1);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m2).getBondMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m2).getBondMapping().getSize() == 1);

	BOOST_CHECK(m2 == m1);
	BOOST_CHECK(m2 == m2);

//-----

	m1.clear();

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getAtomMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getAtomMapping().getSize() == 0);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m1).getBondMapping().getSize() == 0);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m1).getBondMapping().getSize() == 0);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m2).getAtomMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m2).getAtomMapping().getSize() == 1);

	BOOST_CHECK(const_cast<const AtomBondMapping&>(m2).getBondMapping().getSize() == 1);
	BOOST_CHECK(const_cast<AtomBondMapping&>(m2).getBondMapping().getSize() == 1);

	BOOST_CHECK(m2 != m1);
	BOOST_CHECK(m2 == m2);
	BOOST_CHECK(m1 == m1);
}

