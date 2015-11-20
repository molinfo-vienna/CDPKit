/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTest.cpp 
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


#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(AtomTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	Molecule mol;

	mol.addAtom();
	mol.addAtom();
	mol.addAtom();
	mol.addAtom();
	mol.addAtom();

	mol.addBond(0, 1);
	mol.addBond(2, 0);
	mol.addBond(0, 3);

//-----

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(4)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(4)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(4).getNumAtoms() == 0);
	BOOST_CHECK(mol.getAtom(4).getNumBonds() == 0);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(4)).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(4)).getBond(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(4)).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(4)).getBond(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(4)).getAtom(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(4)).getAtom(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(4)).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(4)).getAtom(1), IndexError);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(4)).getAtomsBegin() == const_cast<const Atom&>(mol.getAtom(4)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(4)).getAtomsBegin() == const_cast<Atom&>(mol.getAtom(4)).getAtomsEnd());

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(4)).getBondsBegin() == const_cast<const Atom&>(mol.getAtom(4)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(4)).getBondsBegin() == const_cast<Atom&>(mol.getAtom(4)).getBondsEnd());

	BOOST_CHECK(!mol.getAtom(4).containsAtom(mol.getAtom(4)));
	BOOST_CHECK(!mol.getAtom(4).containsBond(mol.getBond(0)));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(4)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(4)).getBondToAtom(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(4)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(4)).findBondToAtom(mol.getAtom(4)) == 0);

	BOOST_CHECK(mol.getAtom(4).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(4).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);		
	BOOST_CHECK(mol.getAtom(4).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);		

//-----

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(0).getNumAtoms() == 3);
	BOOST_CHECK(mol.getAtom(0).getNumBonds() == 3);

	
	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBond(0) == &mol.getBond(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBond(0) == &mol.getBond(0));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBond(1) == &mol.getBond(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBond(1) == &mol.getBond(1));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBond(2) == &mol.getBond(2));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBond(2) == &mol.getBond(2));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBond(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBond(3), IndexError);


	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getAtom(0) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getAtom(0) == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getAtom(1) == &mol.getAtom(2));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getAtom(1) == &mol.getAtom(2));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getAtom(2) == &mol.getAtom(3));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getAtom(2) == &mol.getAtom(3));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getAtom(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getAtom(3), IndexError);


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin()) == &mol.getAtom(1));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin()) == &mol.getAtom(1));

	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin() + 1) == &mol.getAtom(2));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin() + 1) == &mol.getAtom(2));

	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin() + 2) == &mol.getAtom(3));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin() + 2) == &mol.getAtom(3));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin() + 3 == const_cast<const Atom&>(mol.getAtom(0)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin() + 3 == const_cast<Atom&>(mol.getAtom(0)).getAtomsEnd());


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin()) == &mol.getBond(0));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin()) == &mol.getBond(0));

	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin() + 1) == &mol.getBond(1));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin() + 1) == &mol.getBond(1));

	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin() + 2) == &mol.getBond(2));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin() + 2) == &mol.getBond(2));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin() + 3 == const_cast<const Atom&>(mol.getAtom(0)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin() + 3 == const_cast<Atom&>(mol.getAtom(0)).getBondsEnd());


	BOOST_CHECK(!mol.getAtom(0).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(!mol.getAtom(0).containsAtom(mol.getAtom(4)));

	BOOST_CHECK(mol.getAtom(0).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(mol.getAtom(0).containsBond(mol.getBond(0)));

	BOOST_CHECK(mol.getAtom(0).containsAtom(mol.getAtom(2)));
	BOOST_CHECK(mol.getAtom(0).containsBond(mol.getBond(1)));

	BOOST_CHECK(mol.getAtom(0).containsAtom(mol.getAtom(3)));
	BOOST_CHECK(mol.getAtom(0).containsBond(mol.getBond(2)));


	BOOST_CHECK_THROW(mol.getAtom(0).getAtomIndex(mol.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(0).getAtomIndex(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(mol.getAtom(0).getAtomIndex(mol.getAtom(1)) == 0);
	BOOST_CHECK(mol.getAtom(0).getBondIndex(mol.getBond(0)) == 0);

	BOOST_CHECK(mol.getAtom(0).getAtomIndex(mol.getAtom(2)) == 1);
	BOOST_CHECK(mol.getAtom(0).getBondIndex(mol.getBond(1)) == 1);

	BOOST_CHECK(mol.getAtom(0).getAtomIndex(mol.getAtom(3)) == 2);
	BOOST_CHECK(mol.getAtom(0).getBondIndex(mol.getBond(2)) == 2);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(0)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(1)) == &mol.getBond(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(1)) == &mol.getBond(0));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(2)) == &mol.getBond(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(2)) == &mol.getBond(1));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(3)) == &mol.getBond(2));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(3)) == &mol.getBond(2));


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(0)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(0)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(4)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(1)) == &mol.getBond(0));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(1)) == &mol.getBond(0));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(2)) == &mol.getBond(1));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(2)) == &mol.getBond(1));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(3)) == &mol.getBond(2));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(3)) == &mol.getBond(2));


	BOOST_CHECK(mol.getAtom(0).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 3);		
	BOOST_CHECK(mol.getAtom(0).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 3);		

//-----

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(1)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(1)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol.getAtom(1).getNumBonds() == 1);

	
	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(1)).getBond(0) == &mol.getBond(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(1)).getBond(0) == &mol.getBond(0));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(1)).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(1)).getBond(1), IndexError);


	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(1)).getAtom(0) == &mol.getAtom(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(1)).getAtom(0) == &mol.getAtom(0));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(1)).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(1)).getAtom(1), IndexError);


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(1)).getAtomsBegin()) == &mol.getAtom(0));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(1)).getAtomsBegin()) == &mol.getAtom(0));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).getAtomsBegin() + 1 == const_cast<const Atom&>(mol.getAtom(1)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).getAtomsBegin() + 1 == const_cast<Atom&>(mol.getAtom(1)).getAtomsEnd());


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(1)).getBondsBegin()) == &mol.getBond(0));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(1)).getBondsBegin()) == &mol.getBond(0));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).getBondsBegin() + 1 == const_cast<const Atom&>(mol.getAtom(1)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).getBondsBegin() + 1 == const_cast<Atom&>(mol.getAtom(1)).getBondsEnd());


	BOOST_CHECK(!mol.getAtom(1).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(!mol.getAtom(1).containsAtom(mol.getAtom(4)));

	BOOST_CHECK(mol.getAtom(1).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(mol.getAtom(1).containsBond(mol.getBond(0)));

	BOOST_CHECK(!mol.getAtom(1).containsAtom(mol.getAtom(2)));
	BOOST_CHECK(!mol.getAtom(1).containsBond(mol.getBond(1)));

	BOOST_CHECK(!mol.getAtom(1).containsAtom(mol.getAtom(3)));
	BOOST_CHECK(!mol.getAtom(1).containsBond(mol.getBond(2)));


	BOOST_CHECK_THROW(mol.getAtom(1).getAtomIndex(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(1).getAtomIndex(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(mol.getAtom(1).getAtomIndex(mol.getAtom(0)) == 0);
	BOOST_CHECK(mol.getAtom(1).getBondIndex(mol.getBond(0)) == 0);

	BOOST_CHECK_THROW(mol.getAtom(1).getAtomIndex(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(1).getBondIndex(mol.getBond(1)), ItemNotFound);

	BOOST_CHECK_THROW(mol.getAtom(1).getAtomIndex(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(1).getBondIndex(mol.getBond(2)), ItemNotFound);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(1)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(3)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(0)) == &mol.getBond(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(1)).getBondToAtom(mol.getAtom(0)) == &mol.getBond(0));


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(1)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(1)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(2)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(2)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(3)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(3)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(4)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(0)) == &mol.getBond(0));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(1)).findBondToAtom(mol.getAtom(0)) == &mol.getBond(0));


	BOOST_CHECK(mol.getAtom(1).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(1).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);		
	BOOST_CHECK(mol.getAtom(1).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 1);		

//-----

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(2)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(2)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol.getAtom(2).getNumBonds() == 1);

	
	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(2)).getBond(0) == &mol.getBond(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(2)).getBond(0) == &mol.getBond(1));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBond(1), IndexError);


	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(2)).getAtom(0) == &mol.getAtom(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(2)).getAtom(0) == &mol.getAtom(0));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getAtom(1), IndexError);


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(2)).getAtomsBegin()) == &mol.getAtom(0));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(2)).getAtomsBegin()) == &mol.getAtom(0));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).getAtomsBegin() + 1 == const_cast<const Atom&>(mol.getAtom(2)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).getAtomsBegin() + 1 == const_cast<Atom&>(mol.getAtom(2)).getAtomsEnd());


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(2)).getBondsBegin()) == &mol.getBond(1));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(2)).getBondsBegin()) == &mol.getBond(1));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).getBondsBegin() + 1 == const_cast<const Atom&>(mol.getAtom(2)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).getBondsBegin() + 1 == const_cast<Atom&>(mol.getAtom(2)).getBondsEnd());


	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(2)));
	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(4)));

	BOOST_CHECK(mol.getAtom(2).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(mol.getAtom(2).containsBond(mol.getBond(1)));

	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(!mol.getAtom(2).containsBond(mol.getBond(0)));

	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(3)));
	BOOST_CHECK(!mol.getAtom(2).containsBond(mol.getBond(2)));


	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(mol.getAtom(2).getAtomIndex(mol.getAtom(0)) == 0);
	BOOST_CHECK(mol.getAtom(2).getBondIndex(mol.getBond(1)) == 0);

	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(2).getBondIndex(mol.getBond(0)), ItemNotFound);

	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(2).getBondIndex(mol.getBond(2)), ItemNotFound);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(1)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(3)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(0)) == &mol.getBond(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(0)) == &mol.getBond(1));


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(1)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(1)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(2)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(2)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(3)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(3)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(4)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(0)) == &mol.getBond(1));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(0)) == &mol.getBond(1));


	BOOST_CHECK(mol.getAtom(2).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(2).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);		
	BOOST_CHECK(mol.getAtom(2).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 1);		

//-----

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(3)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(3)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol.getAtom(3).getNumBonds() == 1);

	
	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(3)).getBond(0) == &mol.getBond(2));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(3)).getBond(0) == &mol.getBond(2));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(3)).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(3)).getBond(1), IndexError);


	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(3)).getAtom(0) == &mol.getAtom(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(3)).getAtom(0) == &mol.getAtom(0));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(3)).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(3)).getAtom(1), IndexError);


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(3)).getAtomsBegin()) == &mol.getAtom(0));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(3)).getAtomsBegin()) == &mol.getAtom(0));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).getAtomsBegin() + 1 == const_cast<const Atom&>(mol.getAtom(3)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).getAtomsBegin() + 1 == const_cast<Atom&>(mol.getAtom(3)).getAtomsEnd());


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(3)).getBondsBegin()) == &mol.getBond(2));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(3)).getBondsBegin()) == &mol.getBond(2));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).getBondsBegin() + 1 == const_cast<const Atom&>(mol.getAtom(3)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).getBondsBegin() + 1 == const_cast<Atom&>(mol.getAtom(3)).getBondsEnd());


	BOOST_CHECK(!mol.getAtom(3).containsAtom(mol.getAtom(3)));
	BOOST_CHECK(!mol.getAtom(3).containsAtom(mol.getAtom(4)));

	BOOST_CHECK(mol.getAtom(3).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(mol.getAtom(3).containsBond(mol.getBond(2)));

	BOOST_CHECK(!mol.getAtom(3).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(!mol.getAtom(3).containsBond(mol.getBond(0)));

	BOOST_CHECK(!mol.getAtom(3).containsAtom(mol.getAtom(3)));
	BOOST_CHECK(!mol.getAtom(3).containsBond(mol.getBond(1)));


	BOOST_CHECK_THROW(mol.getAtom(3).getAtomIndex(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(3).getAtomIndex(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(mol.getAtom(3).getAtomIndex(mol.getAtom(0)) == 0);
	BOOST_CHECK(mol.getAtom(3).getBondIndex(mol.getBond(2)) == 0);

	BOOST_CHECK_THROW(mol.getAtom(3).getAtomIndex(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(3).getBondIndex(mol.getBond(0)), ItemNotFound);

	BOOST_CHECK_THROW(mol.getAtom(3).getAtomIndex(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(3).getBondIndex(mol.getBond(1)), ItemNotFound);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(1)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(3)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(0)) == &mol.getBond(2));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(3)).getBondToAtom(mol.getAtom(0)) == &mol.getBond(2));


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(1)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(1)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(2)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(2)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(3)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(3)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(4)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(0)) == &mol.getBond(2));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(3)).findBondToAtom(mol.getAtom(0)) == &mol.getBond(2));


	BOOST_CHECK(mol.getAtom(3).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(3).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 1);		
	BOOST_CHECK(mol.getAtom(3).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 1);		

//-----

	mol.removeBond(1);

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(0).getNumAtoms() == 2);
	BOOST_CHECK(mol.getAtom(0).getNumBonds() == 2);

	
	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBond(0) == &mol.getBond(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBond(0) == &mol.getBond(0));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBond(1) == &mol.getBond(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBond(1) == &mol.getBond(1));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBond(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBond(2), IndexError);


	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getAtom(0) == &mol.getAtom(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getAtom(0) == &mol.getAtom(1));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getAtom(1) == &mol.getAtom(3));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getAtom(1) == &mol.getAtom(3));

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getAtom(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getAtom(2), IndexError);


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin()) == &mol.getAtom(1));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin()) == &mol.getAtom(1));

	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin() + 1) == &mol.getAtom(3));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin() + 1) == &mol.getAtom(3));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).getAtomsBegin() + 2 == const_cast<const Atom&>(mol.getAtom(0)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).getAtomsBegin() + 2 == const_cast<Atom&>(mol.getAtom(0)).getAtomsEnd());


	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin()) == &mol.getBond(0));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin()) == &mol.getBond(0));

	BOOST_CHECK(&*(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin() + 1) == &mol.getBond(1));
	BOOST_CHECK(&*(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin() + 1) == &mol.getBond(1));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).getBondsBegin() + 2 == const_cast<const Atom&>(mol.getAtom(0)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).getBondsBegin() + 2 == const_cast<Atom&>(mol.getAtom(0)).getBondsEnd());


	BOOST_CHECK(!mol.getAtom(0).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(!mol.getAtom(0).containsAtom(mol.getAtom(4)));

	BOOST_CHECK(mol.getAtom(0).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(mol.getAtom(0).containsBond(mol.getBond(0)));

	BOOST_CHECK(!mol.getAtom(0).containsAtom(mol.getAtom(2)));
	BOOST_CHECK(mol.getAtom(0).containsBond(mol.getBond(1)));

	BOOST_CHECK(mol.getAtom(0).containsAtom(mol.getAtom(3)));


	BOOST_CHECK_THROW(mol.getAtom(0).getAtomIndex(mol.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(0).getAtomIndex(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK(mol.getAtom(0).getAtomIndex(mol.getAtom(1)) == 0);
	BOOST_CHECK(mol.getAtom(0).getBondIndex(mol.getBond(0)) == 0);

	BOOST_CHECK_THROW(mol.getAtom(0).getAtomIndex(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK(mol.getAtom(0).getBondIndex(mol.getBond(1)) == 1);

	BOOST_CHECK(mol.getAtom(0).getAtomIndex(mol.getAtom(3)) == 1);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(0)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(1)) == &mol.getBond(0));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(1)) == &mol.getBond(0));

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(3)) == &mol.getBond(1));
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(0)).getBondToAtom(mol.getAtom(3)) == &mol.getBond(1));


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(0)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(0)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(2)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(2)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(4)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(1)) == &mol.getBond(0));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(1)) == &mol.getBond(0));

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(3)) == &mol.getBond(1));
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(0)).findBondToAtom(mol.getAtom(3)) == &mol.getBond(1));


	BOOST_CHECK(mol.getAtom(0).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(0).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 2);		
	BOOST_CHECK(mol.getAtom(0).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 2);		

//-----

	BOOST_CHECK(&const_cast<const Atom&>(mol.getAtom(2)).getMolecule() == &mol);
	BOOST_CHECK(&const_cast<Atom&>(mol.getAtom(2)).getMolecule() == &mol);

	BOOST_CHECK(mol.getAtom(2).getNumAtoms() == 0);
	BOOST_CHECK(mol.getAtom(2).getNumBonds() == 0);

	
	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBond(0), IndexError);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getAtom(0), IndexError);


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).getAtomsBegin() == const_cast<const Atom&>(mol.getAtom(2)).getAtomsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).getAtomsBegin() == const_cast<Atom&>(mol.getAtom(2)).getAtomsEnd());


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).getBondsBegin() == const_cast<const Atom&>(mol.getAtom(2)).getBondsEnd());
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).getBondsBegin() == const_cast<Atom&>(mol.getAtom(2)).getBondsEnd());


	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(2)));
	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(4)));

	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(0)));
	BOOST_CHECK(!mol.getAtom(2).containsBond(mol.getBond(1)));

	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(1)));
	BOOST_CHECK(!mol.getAtom(2).containsBond(mol.getBond(0)));

	BOOST_CHECK(!mol.getAtom(2).containsAtom(mol.getAtom(3)));


	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(4)), ItemNotFound);

	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(2).getBondIndex(mol.getBond(1)), ItemNotFound);

	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(mol.getAtom(2).getBondIndex(mol.getBond(0)), ItemNotFound);

	BOOST_CHECK_THROW(mol.getAtom(2).getAtomIndex(mol.getAtom(3)), ItemNotFound);


	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(0)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(1)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(2)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(2)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(3)), ItemNotFound);

	BOOST_CHECK_THROW(const_cast<const Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(const_cast<Atom&>(mol.getAtom(2)).getBondToAtom(mol.getAtom(4)), ItemNotFound);


	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(0)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(0)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(1)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(1)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(2)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(2)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(3)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(3)) == 0);

	BOOST_CHECK(const_cast<const Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(4)) == 0);
	BOOST_CHECK(const_cast<Atom&>(mol.getAtom(2)).findBondToAtom(mol.getAtom(4)) == 0);


	BOOST_CHECK(mol.getAtom(2).getProperty<std::string>(AtomProperty::SYMBOL) == "");		
	BOOST_CHECK(mol.getAtom(2).getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 0);		
	BOOST_CHECK(mol.getAtom(2).getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 0);

//-----

	mol.clear();

	mol.addAtom();
	mol.addAtom();
	mol.addAtom();
	mol.addAtom();

	mol.addBond(0, 1);
	mol.addBond(2, 0);
	mol.addBond(0, 3);
	mol.addBond(0, 0);

	BOOST_CHECK(mol.getNumAtoms() == 4);
	BOOST_CHECK(mol.getNumBonds() == 4);

	for (std::size_t i = 0; i < mol.getAtom(0).getNumAtoms(); i++) {
		BOOST_CHECK(mol.getAtom(0).containsAtom(mol.getAtom(0).getAtom(i)));
		BOOST_CHECK(mol.getAtom(0).getAtomIndex(mol.getAtom(0).getAtom(i)) == i);

		BOOST_CHECK(mol.getAtom(0).findBondToAtom(mol.getAtom(0).getAtom(i)) == &mol.getAtom(0).getBond(i));
		BOOST_CHECK(&mol.getAtom(0).getBondToAtom(mol.getAtom(0).getAtom(i)) == &mol.getAtom(0).getBond(i));

		BOOST_CHECK(mol.getAtom(0).containsBond(mol.getAtom(0).getBond(i)));
		BOOST_CHECK(mol.getAtom(0).getBondIndex(mol.getAtom(0).getBond(i)) == i);
	}
}
