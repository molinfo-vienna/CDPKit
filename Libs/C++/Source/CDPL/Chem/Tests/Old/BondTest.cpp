/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/BondProperties.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(BondTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	Molecule mol;

	mol.addAtom();
	mol.addAtom();
	mol.addAtom();
	mol.addAtom();

	mol.addBond(0, 1);
	mol.addBond(1, 3);

//-----

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getMolecule() == &mol);

	BOOST_CHECK(mol.getBond(0).getNumAtoms() == 2);

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getBegin() == &mol.getAtom(0));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getBegin() == &mol.getAtom(0));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getEnd() == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getEnd() == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getAtom(0) == &mol.getAtom(0));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getAtom(0) == &mol.getAtom(0));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getAtom(1) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getAtom(1) == &mol.getAtom(1));

	BOOST_CHECK_THROW(const_cast<const Bond&>(mol.getBond(0)).getAtom(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Bond&>(mol.getBond(0)).getAtom(2), IndexError);

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getNeighbor(mol.getAtom(0)) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getNeighbor(mol.getAtom(0)) == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(0)).getNeighbor(mol.getAtom(1)) == &mol.getAtom(0));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(0)).getNeighbor(mol.getAtom(1)) == &mol.getAtom(0));

	BOOST_CHECK_THROW(const_cast<const Bond&>(mol.getBond(0)).getNeighbor(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Bond&>(mol.getBond(0)).getNeighbor(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK(mol.getBond(0).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(mol.getBond(0).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(!mol.getBond(0).containsAtom(mol.getAtom(2)));

	BOOST_CHECK(mol.getBond(0).containsAtom(mol.getBond(0).getBegin()));
	BOOST_CHECK(mol.getBond(0).containsAtom(mol.getBond(0).getEnd()));

	BOOST_CHECK(mol.getBond(0).getAtomIndex(mol.getAtom(0)) == 0);
	BOOST_CHECK(mol.getBond(0).getAtomIndex(mol.getAtom(1)) == 1);
	BOOST_CHECK_THROW(mol.getBond(0).getAtomIndex(mol.getAtom(2)), ItemNotFound);
	
	BOOST_CHECK(mol.getBond(0).getAtomIndex(mol.getBond(0).getBegin()) == 0);
	BOOST_CHECK(mol.getBond(0).getAtomIndex(mol.getBond(0).getEnd()) == 1);

//-----

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getMolecule() == &mol);

	BOOST_CHECK(mol.getBond(1).getNumAtoms() == 2);

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getBegin() == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getBegin() == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getEnd() == &mol.getAtom(3));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getEnd() == &mol.getAtom(3));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getAtom(0) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getAtom(0) == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getAtom(1) == &mol.getAtom(3));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getAtom(1) == &mol.getAtom(3));

	BOOST_CHECK_THROW(const_cast<const Bond&>(mol.getBond(1)).getAtom(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Bond&>(mol.getBond(1)).getAtom(2), IndexError);

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getNeighbor(mol.getAtom(3)) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getNeighbor(mol.getAtom(3)) == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Bond&>(mol.getBond(1)).getNeighbor(mol.getAtom(3)) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Bond&>(mol.getBond(1)).getNeighbor(mol.getAtom(3)) == &mol.getAtom(1));

	BOOST_CHECK_THROW(const_cast<const Bond&>(mol.getBond(1)).getNeighbor(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Bond&>(mol.getBond(1)).getNeighbor(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK(mol.getBond(1).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(mol.getBond(1).containsAtom(mol.getAtom(3)));
	BOOST_CHECK(!mol.getBond(1).containsAtom(mol.getAtom(2)));

	BOOST_CHECK(mol.getBond(1).containsAtom(mol.getBond(1).getBegin()));
	BOOST_CHECK(mol.getBond(1).containsAtom(mol.getBond(1).getEnd()));

	BOOST_CHECK(mol.getBond(1).getAtomIndex(mol.getAtom(1)) == 0);
	BOOST_CHECK(mol.getBond(1).getAtomIndex(mol.getAtom(3)) == 1);
	BOOST_CHECK_THROW(mol.getBond(1).getAtomIndex(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK(mol.getBond(1).getAtomIndex(mol.getBond(1).getBegin()) == 0);
	BOOST_CHECK(mol.getBond(1).getAtomIndex(mol.getBond(1).getEnd()) == 1);

//-----

	BOOST_CHECK(mol.getBond(0).getProperty<FragmentList>(BondProperty::RINGS).getSize() == 0);
	BOOST_CHECK(mol.getBond(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);				
}
