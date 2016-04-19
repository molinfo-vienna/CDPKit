/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicMoleculeTest.cpp 
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

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/LookupKey.hpp"


namespace
{

	void checkAtomIndices(const CDPL::Chem::BasicMolecule& mol)
	{
		for (std::size_t i = 0; i < mol.getNumAtoms(); i++)
			BOOST_CHECK(mol.getAtomIndex(mol.getAtom(i)) == i);
	}

	void checkBondIndices(const CDPL::Chem::BasicMolecule& mol)
	{
		for (std::size_t i = 0; i < mol.getNumBonds(); i++)
			BOOST_CHECK(mol.getBondIndex(mol.getBond(i)) == i);
	}
}


BOOST_AUTO_TEST_CASE(BasicMoleculeTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	LookupKey prop_key1 = LookupKey::create("key1"); 
	LookupKey prop_key2 = LookupKey::create("key2"); 
	LookupKey prop_key3 = LookupKey::create("key3"); 

//-----	

	BasicMolecule mol1;

	BOOST_CHECK(mol1.getNumAtoms() == 0);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol1.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	Molecule::SharedPointer mol1_clone_ptr = mol1.clone();
	BasicMolecule& mol1_clone = static_cast<BasicMolecule&>(*mol1_clone_ptr);

	BOOST_CHECK(&mol1 != mol1_clone_ptr.get());

	BOOST_CHECK(mol1_clone.getNumAtoms() == 0);
	BOOST_CHECK(mol1_clone.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1_clone).getAtomsBegin() == const_cast<const BasicMolecule&>(mol1_clone).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1_clone).getAtomsBegin() == const_cast<BasicMolecule&>(mol1_clone).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1_clone).getBondsBegin() == const_cast<const BasicMolecule&>(mol1_clone).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1_clone).getBondsBegin() == const_cast<BasicMolecule&>(mol1_clone).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1_clone).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1_clone).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1_clone).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1_clone).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1_clone).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1_clone).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1_clone).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1_clone).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol1_clone.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol1_clone.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol1_clone.removeAtom(mol1_clone.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1_clone.removeAtom(mol1_clone.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol1_clone.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1_clone.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1_clone.removeBond(mol1_clone.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1_clone.removeBond(mol1_clone.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol1_clone.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicAtom& mol1_atom1 = mol1.addAtom();

	mol1_atom1.setProperty(prop_key2, std::string("C"));

	BOOST_CHECK(mol1.getNumAtoms() == 1);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 1), RangeError);

	BOOST_CHECK(mol1.containsAtom(mol1_atom1));

//-----	

	BasicAtom& mol1_atom2 = mol1.addAtom();

	mol1_atom2.setProperty(prop_key2, std::string("H"));

	BasicAtom& mol1_atom3 = mol1.addAtom();	

	mol1_atom3 = mol1_atom2;

	BasicAtom& mol1_atom4 = mol1.addAtom();
	mol1_atom4.setProperty(prop_key2, std::string("O"));

	BasicAtom& mol1_atom5 = (mol1.addAtom() = mol1_atom3);

	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(1), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 1), RangeError);


	BOOST_CHECK(mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(mol1.containsAtom(mol1_atom3));

//-----	

	BOOST_CHECK_THROW(mol1.addBond(0, 5), IndexError);
	BOOST_CHECK_THROW(mol1.addBond(5, 0), IndexError);
	BOOST_CHECK_THROW(mol1.addBond(7, 8), IndexError);

	BasicBond& mol1_bond1 = mol1.addBond(0, 1);
	mol1_bond1.setProperty(prop_key3, std::size_t(1));

	BOOST_CHECK(&mol1_bond1.getBegin() == &mol1_atom1);
	BOOST_CHECK(&mol1_bond1.getEnd() == &mol1_atom2);

	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 1);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 1 == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 1 == const_cast<BasicMolecule&>(mol1).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getBondsBegin() == &mol1_bond1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getBondsBegin() == &mol1_bond1);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(5), IndexError);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(0) == &mol1_bond1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(0) == &mol1_bond1);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(1), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 1), RangeError);


	BOOST_CHECK(mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(mol1.containsAtom(mol1_atom3));

	BOOST_CHECK(mol1.containsBond(mol1_bond1));

//-----	

	BOOST_CHECK_THROW(mol1.addBond(0, 5), IndexError);
	BOOST_CHECK_THROW(mol1.addBond(5, 0), IndexError);
	BOOST_CHECK_THROW(mol1.addBond(7, 8), IndexError);

	BasicBond& mol1_bond2 = (mol1.addBond(2, 0) = mol1_bond1);

	BasicBond& mol1_bond3 = mol1.addBond(0, 3);
	mol1_bond3.setProperty(prop_key3, std::size_t(1));;

	BasicBond& mol1_bond4 = (mol1.addBond(4, 0) = mol1_bond2);

	BOOST_CHECK(&mol1_bond1.getBegin() == &mol1_atom1);
	BOOST_CHECK(&mol1_bond1.getEnd() == &mol1_atom2);

	BOOST_CHECK(&mol1_bond2.getBegin() == &mol1_atom3);
	BOOST_CHECK(&mol1_bond2.getEnd() == &mol1_atom1);

	BOOST_CHECK(&mol1_bond3.getBegin() == &mol1_atom1);
	BOOST_CHECK(&mol1_bond3.getEnd() == &mol1_atom4);

	BOOST_CHECK(&mol1_bond4.getBegin() == &mol1_atom5);
	BOOST_CHECK(&mol1_bond4.getEnd() == &mol1_atom1);


	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 4);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol1).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getBondsBegin() == &mol1_bond1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getBondsBegin() == &mol1_bond1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 1) == &mol1_bond2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 1) == &mol1_bond2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 2) == &mol1_bond3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 2) == &mol1_bond3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 3) == &mol1_bond4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 3) == &mol1_bond4);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(5), IndexError);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(0) == &mol1_bond1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(0) == &mol1_bond1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(1) == &mol1_bond2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(1) == &mol1_bond2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(2) == &mol1_bond3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(2) == &mol1_bond3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(3) == &mol1_bond4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(3) == &mol1_bond4);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(mol1.containsAtom(mol1_atom3));

	BOOST_CHECK(mol1.containsBond(mol1_bond4));
	BOOST_CHECK(mol1.containsBond(mol1_bond3));
	BOOST_CHECK(mol1.containsBond(mol1_bond2));
	BOOST_CHECK(mol1.containsBond(mol1_bond1));

//-----	

	mol1.setProperty(prop_key1, std::string("BasicMolecule 1"));

	BOOST_CHECK(mol1.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

	mol1_clone_ptr = mol1.clone();
	BasicMolecule& mol1_clone2 = static_cast<BasicMolecule&>(*mol1_clone_ptr);

	BOOST_CHECK(&mol1 != mol1_clone_ptr.get());

	BOOST_CHECK(mol1_clone2.getNumAtoms() == 5);
	BOOST_CHECK(mol1_clone2.getNumBonds() == 4);

	checkAtomIndices(mol1_clone2);
	checkBondIndices(mol1_clone2);

	BOOST_CHECK(&mol1_clone2.getBond(0).getBegin() == &mol1_clone2.getAtom(0));
	BOOST_CHECK(&mol1_clone2.getBond(0).getEnd() == &mol1_clone2.getAtom(1));

	BOOST_CHECK(&mol1_clone2.getBond(1).getBegin() == &mol1_clone2.getAtom(2));
	BOOST_CHECK(&mol1_clone2.getBond(1).getEnd() == &mol1_clone2.getAtom(0));

	BOOST_CHECK(&mol1_clone2.getBond(2).getBegin() == &mol1_clone2.getAtom(0));
	BOOST_CHECK(&mol1_clone2.getBond(2).getEnd() == &mol1_clone2.getAtom(3));

	BOOST_CHECK(&mol1_clone2.getBond(3).getBegin() == &mol1_clone2.getAtom(4));
	BOOST_CHECK(&mol1_clone2.getBond(3).getEnd() == &mol1_clone2.getAtom(0));


	BOOST_CHECK_THROW(mol1_clone2.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol1_clone2.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1_clone2).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol1_clone2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1_clone2).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol1_clone2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1_clone2).getAtomsBegin() == &mol1_clone2.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1_clone2).getAtomsBegin() == &mol1_clone2.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getAtomsBegin() + 1) == &mol1_clone2.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getAtomsBegin() + 1) == &mol1_clone2.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getAtomsBegin() + 2) == &mol1_clone2.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getAtomsBegin() + 2) == &mol1_clone2.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getAtomsBegin() + 3) == &mol1_clone2.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getAtomsBegin() + 3) == &mol1_clone2.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getAtomsBegin() + 4) == &mol1_clone2.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getAtomsBegin() + 4) == &mol1_clone2.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1_clone2).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol1_clone2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1_clone2).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol1_clone2).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1_clone2).getBondsBegin() == &mol1_clone2.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1_clone2).getBondsBegin() == &mol1_clone2.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getBondsBegin() + 1) == &mol1_clone2.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getBondsBegin() + 1) == &mol1_clone2.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getBondsBegin() + 2) == &mol1_clone2.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getBondsBegin() + 2) == &mol1_clone2.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1_clone2).getBondsBegin() + 3) == &mol1_clone2.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1_clone2).getBondsBegin() + 3) == &mol1_clone2.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1_clone2).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1_clone2).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1_clone2).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1_clone2).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol1_clone2.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol1_clone2.removeAtom(mol1_clone2.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol1_clone2.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol1_clone2.removeBond(mol1_clone2.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol1_clone2.containsAtom(mol1_clone2.getAtom(0)));

	BOOST_CHECK(!mol1_clone2.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol1_clone2.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol1_clone2.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol1_clone2.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol1_clone2.containsAtom(mol1_atom5));

	BOOST_CHECK(mol1_clone2.containsBond(mol1_clone2.getBond(1)));

	BOOST_CHECK(!mol1_clone2.containsBond(mol1_bond1));
	BOOST_CHECK(!mol1_clone2.containsBond(mol1_bond2));
	BOOST_CHECK(!mol1_clone2.containsBond(mol1_bond3));
	BOOST_CHECK(!mol1_clone2.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol1_clone2.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol1_clone2.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol1_clone2.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol1_clone2.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol1_clone2.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol1_clone2.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol1_clone2.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol1_clone2.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol1_clone2.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol1_clone2.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol1_clone2.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol1_clone2.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol1_clone2.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol1_clone2.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol1_clone2.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol1_clone2.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol1_clone2.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol1_clone2.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol1_clone2.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol1_clone2.getAtom(0).findBondToAtom(mol1_clone2.getAtom(0)) == 0);
	BOOST_CHECK(mol1_clone2.getAtom(0).findBondToAtom(mol1_clone2.getAtom(1)) != 0);
	BOOST_CHECK(mol1_clone2.getAtom(0).findBondToAtom(mol1_clone2.getAtom(2)) != 0);
	BOOST_CHECK(mol1_clone2.getAtom(0).findBondToAtom(mol1_clone2.getAtom(3)) != 0);
	BOOST_CHECK(mol1_clone2.getAtom(0).findBondToAtom(mol1_clone2.getAtom(4)) != 0);

	BOOST_CHECK(mol1_clone2.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	BOOST_CHECK(mol1_atom1.getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol1_atom2.getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol1_atom3.getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol1_atom4.getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol1_atom5.getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol1_bond1.getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol1_bond2.getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol1_bond3.getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol1_bond4.getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol1_atom1.getNumAtoms() == 4);
	BOOST_CHECK(mol1_atom1.getNumBonds() == 4);
	
	BOOST_CHECK(mol1_atom2.getNumAtoms() == 1);
	BOOST_CHECK(mol1_atom2.getNumBonds() == 1);
	
	BOOST_CHECK(mol1_atom3.getNumAtoms() == 1);
	BOOST_CHECK(mol1_atom3.getNumBonds() == 1);
	
	BOOST_CHECK(mol1_atom4.getNumAtoms() == 1);
	BOOST_CHECK(mol1_atom4.getNumBonds() == 1);
	
	BOOST_CHECK(mol1_atom5.getNumAtoms() == 1);
	BOOST_CHECK(mol1_atom5.getNumBonds() == 1);
	
	BOOST_CHECK(mol1_atom1.findBondToAtom(mol1_atom1) == 0);
	BOOST_CHECK(mol1_atom1.findBondToAtom(mol1_atom2) != 0);
	BOOST_CHECK(mol1_atom1.findBondToAtom(mol1_atom3) != 0);
	BOOST_CHECK(mol1_atom1.findBondToAtom(mol1_atom4) != 0);
	BOOST_CHECK(mol1_atom1.findBondToAtom(mol1_atom5) != 0);

//-----	

	BasicMolecule mol2(mol1);

	BOOST_CHECK(&mol2.getBond(0).getBegin() == &mol2.getAtom(0));
	BOOST_CHECK(&mol2.getBond(0).getEnd() == &mol2.getAtom(1));

	BOOST_CHECK(&mol2.getBond(1).getBegin() == &mol2.getAtom(2));
	BOOST_CHECK(&mol2.getBond(1).getEnd() == &mol2.getAtom(0));

	BOOST_CHECK(&mol2.getBond(2).getBegin() == &mol2.getAtom(0));
	BOOST_CHECK(&mol2.getBond(2).getEnd() == &mol2.getAtom(3));

	BOOST_CHECK(&mol2.getBond(3).getBegin() == &mol2.getAtom(4));
	BOOST_CHECK(&mol2.getBond(3).getEnd() == &mol2.getAtom(0));


	BOOST_CHECK(mol2.getNumAtoms() == 5);
	BOOST_CHECK(mol2.getNumBonds() == 4);

	checkAtomIndices(mol2);
	checkBondIndices(mol2);

	BOOST_CHECK_THROW(mol2.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol2.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getAtomsBegin() == &mol2.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getAtomsBegin() == &mol2.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 4) == &mol2.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 4) == &mol2.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol2).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getBondsBegin() == &mol2.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 1) == &mol2.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 1) == &mol2.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 2) == &mol2.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 2) == &mol2.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 3) == &mol2.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 3) == &mol2.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol2.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol2.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol2.containsAtom(mol2.getAtom(0)));

	BOOST_CHECK(!mol2.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom5));

	BOOST_CHECK(mol2.containsBond(mol2.getBond(1)));

	BOOST_CHECK(!mol2.containsBond(mol1_bond1));
	BOOST_CHECK(!mol2.containsBond(mol1_bond2));
	BOOST_CHECK(!mol2.containsBond(mol1_bond3));
	BOOST_CHECK(!mol2.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol2.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol2.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol2.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol2.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol2.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol2.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol2.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol2.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol2.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(0)) == 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(1)) != 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(2)) != 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(3)) != 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(4)) != 0);

	BOOST_CHECK(mol2.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	BasicMolecule mol2_1(static_cast<const BasicMolecule&>(mol1));

	BOOST_CHECK(&mol2_1.getBond(0).getBegin() == &mol2_1.getAtom(0));
	BOOST_CHECK(&mol2_1.getBond(0).getEnd() == &mol2_1.getAtom(1));

	BOOST_CHECK(&mol2_1.getBond(1).getBegin() == &mol2_1.getAtom(2));
	BOOST_CHECK(&mol2_1.getBond(1).getEnd() == &mol2_1.getAtom(0));

	BOOST_CHECK(&mol2_1.getBond(2).getBegin() == &mol2_1.getAtom(0));
	BOOST_CHECK(&mol2_1.getBond(2).getEnd() == &mol2_1.getAtom(3));

	BOOST_CHECK(&mol2_1.getBond(3).getBegin() == &mol2_1.getAtom(4));
	BOOST_CHECK(&mol2_1.getBond(3).getEnd() == &mol2_1.getAtom(0));


	BOOST_CHECK(mol2_1.getNumAtoms() == 5);
	BOOST_CHECK(mol2_1.getNumBonds() == 4);

	checkAtomIndices(mol2_1);
	checkBondIndices(mol2_1);

	BOOST_CHECK_THROW(mol2_1.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol2_1.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2_1).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol2_1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2_1).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol2_1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2_1).getAtomsBegin() == &mol2_1.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2_1).getAtomsBegin() == &mol2_1.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getAtomsBegin() + 1) == &mol2_1.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getAtomsBegin() + 1) == &mol2_1.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getAtomsBegin() + 2) == &mol2_1.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getAtomsBegin() + 2) == &mol2_1.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getAtomsBegin() + 3) == &mol2_1.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getAtomsBegin() + 3) == &mol2_1.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getAtomsBegin() + 4) == &mol2_1.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getAtomsBegin() + 4) == &mol2_1.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2_1).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol2_1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2_1).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol2_1).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2_1).getBondsBegin() == &mol2_1.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2_1).getBondsBegin() == &mol2_1.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getBondsBegin() + 1) == &mol2_1.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getBondsBegin() + 1) == &mol2_1.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getBondsBegin() + 2) == &mol2_1.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getBondsBegin() + 2) == &mol2_1.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2_1).getBondsBegin() + 3) == &mol2_1.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2_1).getBondsBegin() + 3) == &mol2_1.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2_1).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2_1).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2_1).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2_1).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol2_1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol2_1.removeAtom(mol2_1.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol2_1.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol2_1.removeBond(mol2_1.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol2_1.containsAtom(mol2_1.getAtom(0)));

	BOOST_CHECK(!mol2_1.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol2_1.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol2_1.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol2_1.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol2_1.containsAtom(mol1_atom5));

	BOOST_CHECK(mol2_1.containsBond(mol2_1.getBond(1)));

	BOOST_CHECK(!mol2_1.containsBond(mol1_bond1));
	BOOST_CHECK(!mol2_1.containsBond(mol1_bond2));
	BOOST_CHECK(!mol2_1.containsBond(mol1_bond3));
	BOOST_CHECK(!mol2_1.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol2_1.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol2_1.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol2_1.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol2_1.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol2_1.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol2_1.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2_1.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2_1.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2_1.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol2_1.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol2_1.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol2_1.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol2_1.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol2_1.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol2_1.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol2_1.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol2_1.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol2_1.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol2_1.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol2_1.getAtom(0).findBondToAtom(mol2_1.getAtom(0)) == 0);
	BOOST_CHECK(mol2_1.getAtom(0).findBondToAtom(mol2_1.getAtom(1)) != 0);
	BOOST_CHECK(mol2_1.getAtom(0).findBondToAtom(mol2_1.getAtom(2)) != 0);
	BOOST_CHECK(mol2_1.getAtom(0).findBondToAtom(mol2_1.getAtom(3)) != 0);
	BOOST_CHECK(mol2_1.getAtom(0).findBondToAtom(mol2_1.getAtom(4)) != 0);

	BOOST_CHECK(mol2_1.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	BasicMolecule mol3;

	BOOST_CHECK(&(mol3 = mol1) == &mol3);

	BOOST_CHECK(&mol3.getBond(0).getBegin() == &mol3.getAtom(0));
	BOOST_CHECK(&mol3.getBond(0).getEnd() == &mol3.getAtom(1));

	BOOST_CHECK(&mol3.getBond(1).getBegin() == &mol3.getAtom(2));
	BOOST_CHECK(&mol3.getBond(1).getEnd() == &mol3.getAtom(0));

	BOOST_CHECK(&mol3.getBond(2).getBegin() == &mol3.getAtom(0));
	BOOST_CHECK(&mol3.getBond(2).getEnd() == &mol3.getAtom(3));

	BOOST_CHECK(&mol3.getBond(3).getBegin() == &mol3.getAtom(4));
	BOOST_CHECK(&mol3.getBond(3).getEnd() == &mol3.getAtom(0));


	BOOST_CHECK(mol3.getNumAtoms() == 5);
	BOOST_CHECK(mol3.getNumBonds() == 4);

	checkAtomIndices(mol3);
	checkBondIndices(mol3);

	BOOST_CHECK_THROW(mol3.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol3.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol3).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol3).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol3).getAtomsBegin() == &mol3.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol3).getAtomsBegin() == &mol3.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 1) == &mol3.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 1) == &mol3.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 2) == &mol3.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 2) == &mol3.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 3) == &mol3.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 3) == &mol3.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 4) == &mol3.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 4) == &mol3.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol3).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol3).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol3).getBondsBegin() == &mol3.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol3).getBondsBegin() == &mol3.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 1) == &mol3.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 1) == &mol3.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 2) == &mol3.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 2) == &mol3.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 3) == &mol3.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 3) == &mol3.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol3.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol3.removeAtom(mol3.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol3.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol3.removeBond(mol3.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol3.containsAtom(mol3.getAtom(0)));

	BOOST_CHECK(!mol3.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom5));

	BOOST_CHECK(mol3.containsBond(mol3.getBond(1)));

	BOOST_CHECK(!mol3.containsBond(mol1_bond1));
	BOOST_CHECK(!mol3.containsBond(mol1_bond2));
	BOOST_CHECK(!mol3.containsBond(mol1_bond3));
	BOOST_CHECK(!mol3.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol3.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol3.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol3.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol3.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol3.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol3.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol3.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol3.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol3.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol3.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol3.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol3.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(0)) == 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(1)) != 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(2)) != 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(3)) != 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(4)) != 0);

	BOOST_CHECK(mol3.getNumProperties() == 1);

	BOOST_CHECK(mol3.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	mol3.clear();

	BOOST_CHECK(mol3.getNumAtoms() == 0);
	BOOST_CHECK(mol3.getNumBonds() == 0);
	BOOST_CHECK(mol3.getNumProperties() == 0);

	mol3.copy(mol1);

	BOOST_CHECK(&mol3.getBond(0).getBegin() == &mol3.getAtom(0));
	BOOST_CHECK(&mol3.getBond(0).getEnd() == &mol3.getAtom(1));

	BOOST_CHECK(&mol3.getBond(1).getBegin() == &mol3.getAtom(2));
	BOOST_CHECK(&mol3.getBond(1).getEnd() == &mol3.getAtom(0));

	BOOST_CHECK(&mol3.getBond(2).getBegin() == &mol3.getAtom(0));
	BOOST_CHECK(&mol3.getBond(2).getEnd() == &mol3.getAtom(3));

	BOOST_CHECK(&mol3.getBond(3).getBegin() == &mol3.getAtom(4));
	BOOST_CHECK(&mol3.getBond(3).getEnd() == &mol3.getAtom(0));


	BOOST_CHECK(mol3.getNumAtoms() == 5);
	BOOST_CHECK(mol3.getNumBonds() == 4);

	checkAtomIndices(mol3);
	checkBondIndices(mol3);

	BOOST_CHECK_THROW(mol3.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol3.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol3).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol3).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol3).getAtomsBegin() == &mol3.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol3).getAtomsBegin() == &mol3.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 1) == &mol3.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 1) == &mol3.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 2) == &mol3.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 2) == &mol3.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 3) == &mol3.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 3) == &mol3.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() + 4) == &mol3.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getAtomsBegin() + 4) == &mol3.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol3).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol3).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol3).getBondsBegin() == &mol3.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol3).getBondsBegin() == &mol3.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 1) == &mol3.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 1) == &mol3.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 2) == &mol3.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 2) == &mol3.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol3).getBondsBegin() + 3) == &mol3.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol3).getBondsBegin() + 3) == &mol3.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol3.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol3.removeAtom(mol3.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol3.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol3.removeBond(mol3.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol3.containsAtom(mol3.getAtom(0)));

	BOOST_CHECK(!mol3.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol3.containsAtom(mol1_atom5));

	BOOST_CHECK(mol3.containsBond(mol3.getBond(1)));

	BOOST_CHECK(!mol3.containsBond(mol1_bond1));
	BOOST_CHECK(!mol3.containsBond(mol1_bond2));
	BOOST_CHECK(!mol3.containsBond(mol1_bond3));
	BOOST_CHECK(!mol3.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol3.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol3.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol3.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol3.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol3.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol3.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol3.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol3.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol3.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol3.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol3.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol3.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol3.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(0)) == 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(1)) != 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(2)) != 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(3)) != 0);
	BOOST_CHECK(mol3.getAtom(0).findBondToAtom(mol3.getAtom(4)) != 0);

	BOOST_CHECK(mol3.getNumProperties() == 1);

	BOOST_CHECK(mol3.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	BasicMolecule mol4;

	BOOST_CHECK(&(mol4 += mol1) == &mol4);
	
	BOOST_CHECK(&mol4.getBond(0).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(0).getEnd() == &mol4.getAtom(1));

	BOOST_CHECK(&mol4.getBond(1).getBegin() == &mol4.getAtom(2));
	BOOST_CHECK(&mol4.getBond(1).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(2).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(2).getEnd() == &mol4.getAtom(3));

	BOOST_CHECK(&mol4.getBond(3).getBegin() == &mol4.getAtom(4));
	BOOST_CHECK(&mol4.getBond(3).getEnd() == &mol4.getAtom(0));


	BOOST_CHECK(mol4.getNumAtoms() == 5);
	BOOST_CHECK(mol4.getNumBonds() == 4);

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK_THROW(mol4.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol4.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol4).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol4).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol4).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol4).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol4.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol4.removeAtom(mol4.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol4.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol4.removeBond(mol4.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol4.containsAtom(mol4.getAtom(0)));

	BOOST_CHECK(!mol4.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom5));

	BOOST_CHECK(mol4.containsBond(mol4.getBond(1)));

	BOOST_CHECK(!mol4.containsBond(mol1_bond1));
	BOOST_CHECK(!mol4.containsBond(mol1_bond2));
	BOOST_CHECK(!mol4.containsBond(mol1_bond3));
	BOOST_CHECK(!mol4.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol4.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol4.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol4.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol4.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol4.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol4.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol4.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(0)) == 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(1)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(2)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(3)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(4)) != 0);

	BOOST_CHECK(mol4.getNumProperties() == 0);

	BOOST_CHECK_THROW(mol4.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	
	
	mol4.clear();

	BOOST_CHECK(mol4.getNumAtoms() == 0);
	BOOST_CHECK(mol4.getNumBonds() == 0);
	BOOST_CHECK(mol4.getNumProperties() == 0);

	mol4.append(mol1);
	
	BOOST_CHECK(&mol4.getBond(0).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(0).getEnd() == &mol4.getAtom(1));

	BOOST_CHECK(&mol4.getBond(1).getBegin() == &mol4.getAtom(2));
	BOOST_CHECK(&mol4.getBond(1).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(2).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(2).getEnd() == &mol4.getAtom(3));

	BOOST_CHECK(&mol4.getBond(3).getBegin() == &mol4.getAtom(4));
	BOOST_CHECK(&mol4.getBond(3).getEnd() == &mol4.getAtom(0));


	BOOST_CHECK(mol4.getNumAtoms() == 5);
	BOOST_CHECK(mol4.getNumBonds() == 4);

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK_THROW(mol4.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol4.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol4).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol4).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol4).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol4).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol4.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol4.removeAtom(mol4.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol4.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol4.removeBond(mol4.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol4.containsAtom(mol4.getAtom(0)));

	BOOST_CHECK(!mol4.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol4.containsAtom(mol1_atom5));

	BOOST_CHECK(mol4.containsBond(mol4.getBond(1)));

	BOOST_CHECK(!mol4.containsBond(mol1_bond1));
	BOOST_CHECK(!mol4.containsBond(mol1_bond2));
	BOOST_CHECK(!mol4.containsBond(mol1_bond3));
	BOOST_CHECK(!mol4.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol4.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol4.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol4.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol4.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol4.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol4.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol4.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(0)) == 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(1)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(2)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(3)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(4)) != 0);

	BOOST_CHECK(mol4.getNumProperties() == 0);

	BOOST_CHECK_THROW(mol4.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	mol4.setProperty(prop_key1, std::string("BasicMolecule 4"));

	mol4.append(BasicMolecule());

	BOOST_CHECK(&mol4.getBond(0).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(0).getEnd() == &mol4.getAtom(1));

	BOOST_CHECK(&mol4.getBond(1).getBegin() == &mol4.getAtom(2));
	BOOST_CHECK(&mol4.getBond(1).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(2).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(2).getEnd() == &mol4.getAtom(3));

	BOOST_CHECK(&mol4.getBond(3).getBegin() == &mol4.getAtom(4));
	BOOST_CHECK(&mol4.getBond(3).getEnd() == &mol4.getAtom(0));


	BOOST_CHECK(mol4.getNumAtoms() == 5);
	BOOST_CHECK(mol4.getNumBonds() == 4);

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK(mol4.getProperty<std::string>(prop_key1) == "BasicMolecule 4");

	mol4.append(Fragment());

	BOOST_CHECK(&mol4.getBond(0).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(0).getEnd() == &mol4.getAtom(1));

	BOOST_CHECK(&mol4.getBond(1).getBegin() == &mol4.getAtom(2));
	BOOST_CHECK(&mol4.getBond(1).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(2).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(2).getEnd() == &mol4.getAtom(3));

	BOOST_CHECK(&mol4.getBond(3).getBegin() == &mol4.getAtom(4));
	BOOST_CHECK(&mol4.getBond(3).getEnd() == &mol4.getAtom(0));


	BOOST_CHECK(mol4.getNumAtoms() == 5);
	BOOST_CHECK(mol4.getNumBonds() == 4);

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK(mol4.getProperty<std::string>(prop_key1) == "BasicMolecule 4");

//-----	

	BasicMolecule mol5 = BasicMolecule();

	BOOST_CHECK(mol5.getNumAtoms() == 0);
	BOOST_CHECK(mol5.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol5.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol5.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol5.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol5.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	mol5.append(static_cast<const BasicMolecule&>(mol1));

	BOOST_CHECK(&mol5.getBond(0).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(0).getEnd() == &mol5.getAtom(1));

	BOOST_CHECK(&mol5.getBond(1).getBegin() == &mol5.getAtom(2));
	BOOST_CHECK(&mol5.getBond(1).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(2).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(2).getEnd() == &mol5.getAtom(3));

	BOOST_CHECK(&mol5.getBond(3).getBegin() == &mol5.getAtom(4));
	BOOST_CHECK(&mol5.getBond(3).getEnd() == &mol5.getAtom(0));


	BOOST_CHECK(mol5.getNumAtoms() == 5);
	BOOST_CHECK(mol5.getNumBonds() == 4);

	checkAtomIndices(mol5);
	checkBondIndices(mol5);

	BOOST_CHECK_THROW(mol5.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol5.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol5.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol5.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol5.containsAtom(mol5.getAtom(0)));

	BOOST_CHECK(!mol5.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom5));

	BOOST_CHECK(mol5.containsBond(mol5.getBond(1)));

	BOOST_CHECK(!mol5.containsBond(mol1_bond1));
	BOOST_CHECK(!mol5.containsBond(mol1_bond2));
	BOOST_CHECK(!mol5.containsBond(mol1_bond3));
	BOOST_CHECK(!mol5.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol5.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol5.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol5.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol5.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol5.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol5.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol5.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(0)) == 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(1)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(2)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(3)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(4)) != 0);

	BOOST_CHECK(mol5.getNumProperties() == 0);

	BOOST_CHECK_THROW(mol5.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicMolecule mol6;

	BOOST_CHECK(&(mol6 = BasicMolecule()) == &mol6);

	BOOST_CHECK(mol6.getNumAtoms() == 0);
	BOOST_CHECK(mol6.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol6).getAtomsBegin() == const_cast<const BasicMolecule&>(mol6).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol6).getAtomsBegin() == const_cast<BasicMolecule&>(mol6).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol6).getBondsBegin() == const_cast<const BasicMolecule&>(mol6).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol6).getBondsBegin() == const_cast<BasicMolecule&>(mol6).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol6).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol6).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol6).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol6).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol6).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol6).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol6).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol6).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol6.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol6.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol6.removeAtom(mol6.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol6.removeAtom(mol6.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol6.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol6.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol6.removeBond(mol6.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol6.removeBond(mol6.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol6.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicMolecule mol7;

	BOOST_CHECK(&(mol7 += BasicMolecule()) == &mol7);

	BOOST_CHECK(mol7.getNumAtoms() == 0);
	BOOST_CHECK(mol7.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol7).getAtomsBegin() == const_cast<const BasicMolecule&>(mol7).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol7).getAtomsBegin() == const_cast<BasicMolecule&>(mol7).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol7).getBondsBegin() == const_cast<const BasicMolecule&>(mol7).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol7).getBondsBegin() == const_cast<BasicMolecule&>(mol7).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol7).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol7).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol7).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol7).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol7).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol7).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol7).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol7).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol7.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol7.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol7.removeAtom(mol7.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol7.removeAtom(mol7.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol7.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol7.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol7.removeBond(mol7.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol7.removeBond(mol7.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol7.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BOOST_CHECK(&(mol2 += BasicMolecule()) == &mol2);

	BOOST_CHECK(&mol2.getBond(0).getBegin() == &mol2.getAtom(0));
	BOOST_CHECK(&mol2.getBond(0).getEnd() == &mol2.getAtom(1));

	BOOST_CHECK(&mol2.getBond(1).getBegin() == &mol2.getAtom(2));
	BOOST_CHECK(&mol2.getBond(1).getEnd() == &mol2.getAtom(0));

	BOOST_CHECK(&mol2.getBond(2).getBegin() == &mol2.getAtom(0));
	BOOST_CHECK(&mol2.getBond(2).getEnd() == &mol2.getAtom(3));

	BOOST_CHECK(&mol2.getBond(3).getBegin() == &mol2.getAtom(4));
	BOOST_CHECK(&mol2.getBond(3).getEnd() == &mol2.getAtom(0));


	BOOST_CHECK(mol2.getNumAtoms() == 5);
	BOOST_CHECK(mol2.getNumBonds() == 4);

	checkAtomIndices(mol2);
	checkBondIndices(mol2);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getAtomsBegin() == &mol2.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getAtomsBegin() == &mol2.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 4) == &mol2.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 4) == &mol2.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol2).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getBondsBegin() == &mol2.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 1) == &mol2.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 1) == &mol2.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 2) == &mol2.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 2) == &mol2.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 3) == &mol2.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 3) == &mol2.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol2.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol2.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol2.containsAtom(mol2.getAtom(0)));

	BOOST_CHECK(!mol2.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol2.containsAtom(mol1_atom5));

	BOOST_CHECK(mol2.containsBond(mol2.getBond(1)));

	BOOST_CHECK(!mol2.containsBond(mol1_bond1));
	BOOST_CHECK(!mol2.containsBond(mol1_bond2));
	BOOST_CHECK(!mol2.containsBond(mol1_bond3));
	BOOST_CHECK(!mol2.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol2.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol2.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol2.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol2.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol2.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol2.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol2.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol2.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol2.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol2.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol2.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(0)) == 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(1)) != 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(2)) != 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(3)) != 0);
	BOOST_CHECK(mol2.getAtom(0).findBondToAtom(mol2.getAtom(4)) != 0);

	BOOST_CHECK(mol2.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	BOOST_CHECK(&(mol3 = BasicMolecule()) == &mol3);

	BOOST_CHECK(mol3.getNumAtoms() == 0);
	BOOST_CHECK(mol3.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() == const_cast<const BasicMolecule&>(mol3).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getAtomsBegin() == const_cast<BasicMolecule&>(mol3).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getBondsBegin() == const_cast<const BasicMolecule&>(mol3).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getBondsBegin() == const_cast<BasicMolecule&>(mol3).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol3.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol3.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol3.removeAtom(mol3.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol3.removeAtom(mol3.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol3.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol3.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol3.removeBond(mol3.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol3.removeBond(mol3.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol3.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(mol3.getNumProperties() == 0);

//-----	

	BOOST_CHECK(&(mol3 += mol3) == &mol3);

	BOOST_CHECK(mol3.getNumAtoms() == 0);
	BOOST_CHECK(mol3.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getAtomsBegin() == const_cast<const BasicMolecule&>(mol3).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getAtomsBegin() == const_cast<BasicMolecule&>(mol3).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol3).getBondsBegin() == const_cast<const BasicMolecule&>(mol3).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol3).getBondsBegin() == const_cast<BasicMolecule&>(mol3).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol3).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol3).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol3.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol3.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol3.removeAtom(mol3.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol3.removeAtom(mol3.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol3.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol3.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol3.removeBond(mol3.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol3.removeBond(mol3.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol3.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BOOST_CHECK(&(mol4 += mol4) == &mol4);
		
	BOOST_CHECK(&mol4.getBond(0).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(0).getEnd() == &mol4.getAtom(1));

	BOOST_CHECK(&mol4.getBond(1).getBegin() == &mol4.getAtom(2));
	BOOST_CHECK(&mol4.getBond(1).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(2).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(2).getEnd() == &mol4.getAtom(3));

	BOOST_CHECK(&mol4.getBond(3).getBegin() == &mol4.getAtom(4));
	BOOST_CHECK(&mol4.getBond(3).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(4).getBegin() == &mol4.getAtom(5));
	BOOST_CHECK(&mol4.getBond(4).getEnd() == &mol4.getAtom(6));

	BOOST_CHECK(&mol4.getBond(5).getBegin() == &mol4.getAtom(7));
	BOOST_CHECK(&mol4.getBond(5).getEnd() == &mol4.getAtom(5));

	BOOST_CHECK(&mol4.getBond(6).getBegin() == &mol4.getAtom(5));
	BOOST_CHECK(&mol4.getBond(6).getEnd() == &mol4.getAtom(8));

	BOOST_CHECK(&mol4.getBond(7).getBegin() == &mol4.getAtom(9));
	BOOST_CHECK(&mol4.getBond(7).getEnd() == &mol4.getAtom(5));

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK_THROW(mol4.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol4.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(mol4.getNumAtoms() == 10);
	BOOST_CHECK(mol4.getNumBonds() == 8);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 10 == const_cast<const BasicMolecule&>(mol4).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 10 == const_cast<BasicMolecule&>(mol4).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 8 == const_cast<const BasicMolecule&>(mol4).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 8 == const_cast<BasicMolecule&>(mol4).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getAtom(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getAtom(10), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getBond(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getBond(8), IndexError);


	BOOST_CHECK_THROW(mol4.removeAtom(10), IndexError);

	BOOST_CHECK_THROW(mol4.removeAtom(mol4.getAtomsBegin() + 10), RangeError);


	BOOST_CHECK_THROW(mol4.removeBond(8), IndexError);

	BOOST_CHECK_THROW(mol4.removeBond(mol4.getBondsBegin() + 8), RangeError);


	BOOST_CHECK(mol4.containsAtom(mol4.getAtom(0)));

	BOOST_CHECK(!mol4.containsAtom(mol1_atom1));

	BOOST_CHECK(mol4.containsBond(mol4.getBond(1)));

	BOOST_CHECK(!mol4.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol4.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol4.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol4.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol4.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol4.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol4.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol4.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(0)) == 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(1)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(2)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(3)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(4)) != 0);

	BOOST_CHECK(mol4.getProperty<std::string>(prop_key1) == "BasicMolecule 4");

//-----	

	mol4.copy(BasicMolecule());

	BOOST_CHECK(mol4.getNumAtoms() == 0);
	BOOST_CHECK(mol4.getNumBonds() == 0);
	BOOST_CHECK(mol4.getNumProperties() == 0);
	
	mol4.copy(static_cast<const Molecule&>(mol1));

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK(mol4.getNumAtoms() == 5);
	BOOST_CHECK(mol4.getNumBonds() == 4);
	BOOST_CHECK(mol4.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

	mol4.setProperty(prop_key1, std::string("BasicMolecule 4"));
	mol4.append(mol4);

	BOOST_CHECK(&mol4.getBond(0).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(0).getEnd() == &mol4.getAtom(1));

	BOOST_CHECK(&mol4.getBond(1).getBegin() == &mol4.getAtom(2));
	BOOST_CHECK(&mol4.getBond(1).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(2).getBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&mol4.getBond(2).getEnd() == &mol4.getAtom(3));

	BOOST_CHECK(&mol4.getBond(3).getBegin() == &mol4.getAtom(4));
	BOOST_CHECK(&mol4.getBond(3).getEnd() == &mol4.getAtom(0));

	BOOST_CHECK(&mol4.getBond(4).getBegin() == &mol4.getAtom(5));
	BOOST_CHECK(&mol4.getBond(4).getEnd() == &mol4.getAtom(6));

	BOOST_CHECK(&mol4.getBond(5).getBegin() == &mol4.getAtom(7));
	BOOST_CHECK(&mol4.getBond(5).getEnd() == &mol4.getAtom(5));

	BOOST_CHECK(&mol4.getBond(6).getBegin() == &mol4.getAtom(5));
	BOOST_CHECK(&mol4.getBond(6).getEnd() == &mol4.getAtom(8));

	BOOST_CHECK(&mol4.getBond(7).getBegin() == &mol4.getAtom(9));
	BOOST_CHECK(&mol4.getBond(7).getEnd() == &mol4.getAtom(5));

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK_THROW(mol4.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol4.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(mol4.getNumAtoms() == 10);
	BOOST_CHECK(mol4.getNumBonds() == 8);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 10 == const_cast<const BasicMolecule&>(mol4).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 10 == const_cast<BasicMolecule&>(mol4).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getAtomsBegin() == &mol4.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 1) == &mol4.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 2) == &mol4.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 3) == &mol4.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getAtomsBegin() + 4) == &mol4.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 8 == const_cast<const BasicMolecule&>(mol4).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 8 == const_cast<BasicMolecule&>(mol4).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol4).getBondsBegin() == &mol4.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 1) == &mol4.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 2) == &mol4.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol4).getBondsBegin() + 3) == &mol4.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getAtom(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getAtom(10), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol4).getBond(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol4).getBond(8), IndexError);


	BOOST_CHECK_THROW(mol4.removeAtom(10), IndexError);

	BOOST_CHECK_THROW(mol4.removeAtom(mol4.getAtomsBegin() + 10), RangeError);


	BOOST_CHECK_THROW(mol4.removeBond(8), IndexError);

	BOOST_CHECK_THROW(mol4.removeBond(mol4.getBondsBegin() + 8), RangeError);


	BOOST_CHECK(mol4.containsAtom(mol4.getAtom(0)));

	BOOST_CHECK(!mol4.containsAtom(mol1_atom1));

	BOOST_CHECK(mol4.containsBond(mol4.getBond(1)));

	BOOST_CHECK(!mol4.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol4.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol4.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol4.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol4.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol4.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol4.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol4.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol4.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol4.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol4.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(0)) == 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(1)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(2)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(3)) != 0);
	BOOST_CHECK(mol4.getAtom(0).findBondToAtom(mol4.getAtom(4)) != 0);

	BOOST_CHECK(mol4.getProperty<std::string>(prop_key1) == "BasicMolecule 4");

//-----	

	mol4.copy(Fragment());

	BOOST_CHECK(mol4.getNumAtoms() == 0);
	BOOST_CHECK(mol4.getNumBonds() == 0);
	BOOST_CHECK(mol4.getNumProperties() == 0);

	mol4.copy(mol1);

	checkAtomIndices(mol4);
	checkBondIndices(mol4);

	BOOST_CHECK(mol4.getNumAtoms() == 5);
	BOOST_CHECK(mol4.getNumBonds() == 4);
	BOOST_CHECK(mol4.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

	mol4.setProperty(prop_key1, std::string("BasicMolecule 4"));

//-----	

	BOOST_CHECK(&(mol5 = mol1) == &mol5);

	mol5.setProperty(prop_key1, std::string("BasicMolecule 5"));

	BOOST_CHECK(&(mol5 += mol2) == &mol5);

	BOOST_CHECK(&mol5.getBond(0).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(0).getEnd() == &mol5.getAtom(1));

	BOOST_CHECK(&mol5.getBond(1).getBegin() == &mol5.getAtom(2));
	BOOST_CHECK(&mol5.getBond(1).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(2).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(2).getEnd() == &mol5.getAtom(3));

	BOOST_CHECK(&mol5.getBond(3).getBegin() == &mol5.getAtom(4));
	BOOST_CHECK(&mol5.getBond(3).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(4).getBegin() == &mol5.getAtom(5));
	BOOST_CHECK(&mol5.getBond(4).getEnd() == &mol5.getAtom(6));

	BOOST_CHECK(&mol5.getBond(5).getBegin() == &mol5.getAtom(7));
	BOOST_CHECK(&mol5.getBond(5).getEnd() == &mol5.getAtom(5));

	BOOST_CHECK(&mol5.getBond(6).getBegin() == &mol5.getAtom(5));
	BOOST_CHECK(&mol5.getBond(6).getEnd() == &mol5.getAtom(8));

	BOOST_CHECK(&mol5.getBond(7).getBegin() == &mol5.getAtom(9));
	BOOST_CHECK(&mol5.getBond(7).getEnd() == &mol5.getAtom(5));


	BOOST_CHECK(mol5.getNumAtoms() == 10);
	BOOST_CHECK(mol5.getNumBonds() == 8);

	checkAtomIndices(mol5);
	checkBondIndices(mol5);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 10 == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 10 == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 8 == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 8 == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(10), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(8), IndexError);


	BOOST_CHECK_THROW(mol5.removeAtom(10), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 10), RangeError);


	BOOST_CHECK_THROW(mol5.removeBond(8), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 8), RangeError);


	BOOST_CHECK(mol5.containsAtom(mol5.getAtom(0)));

	BOOST_CHECK(!mol5.containsAtom(mol1_atom1));

	BOOST_CHECK(mol5.containsBond(mol5.getBond(1)));

	BOOST_CHECK(!mol5.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol5.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol5.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol5.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol5.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol5.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol5.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol5.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(0)) == 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(1)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(2)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(3)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(4)) != 0);

	BOOST_CHECK(mol5.getProperty<std::string>(prop_key1) == "BasicMolecule 5");

//-----	

	BOOST_CHECK(&(mol5 = mol5) == &mol5);

	BOOST_CHECK(&mol5.getBond(0).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(0).getEnd() == &mol5.getAtom(1));

	BOOST_CHECK(&mol5.getBond(1).getBegin() == &mol5.getAtom(2));
	BOOST_CHECK(&mol5.getBond(1).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(2).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(2).getEnd() == &mol5.getAtom(3));

	BOOST_CHECK(&mol5.getBond(3).getBegin() == &mol5.getAtom(4));
	BOOST_CHECK(&mol5.getBond(3).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(4).getBegin() == &mol5.getAtom(5));
	BOOST_CHECK(&mol5.getBond(4).getEnd() == &mol5.getAtom(6));

	BOOST_CHECK(&mol5.getBond(5).getBegin() == &mol5.getAtom(7));
	BOOST_CHECK(&mol5.getBond(5).getEnd() == &mol5.getAtom(5));

	BOOST_CHECK(&mol5.getBond(6).getBegin() == &mol5.getAtom(5));
	BOOST_CHECK(&mol5.getBond(6).getEnd() == &mol5.getAtom(8));

	BOOST_CHECK(&mol5.getBond(7).getBegin() == &mol5.getAtom(9));
	BOOST_CHECK(&mol5.getBond(7).getEnd() == &mol5.getAtom(5));


	BOOST_CHECK(mol5.getNumAtoms() == 10);
	BOOST_CHECK(mol5.getNumBonds() == 8);

	checkAtomIndices(mol5);
	checkBondIndices(mol5);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 10 == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 10 == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 8 == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 8 == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(10), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(8), IndexError);


	BOOST_CHECK_THROW(mol5.removeAtom(10), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 10), RangeError);


	BOOST_CHECK_THROW(mol5.removeBond(8), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 8), RangeError);


	BOOST_CHECK(mol5.containsAtom(mol5.getAtom(0)));

	BOOST_CHECK(!mol5.containsAtom(mol1_atom1));

	BOOST_CHECK(mol5.containsBond(mol5.getBond(1)));

	BOOST_CHECK(!mol5.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol5.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol5.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol5.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol5.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol5.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol5.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol5.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(0)) == 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(1)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(2)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(3)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(4)) != 0);

	BOOST_CHECK(mol5.getProperty<std::string>(prop_key1) == "BasicMolecule 5");

//-----	

	BOOST_CHECK(&(mol5 = mol2) == &mol5);

	BOOST_CHECK(&mol5.getBond(0).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(0).getEnd() == &mol5.getAtom(1));

	BOOST_CHECK(&mol5.getBond(1).getBegin() == &mol5.getAtom(2));
	BOOST_CHECK(&mol5.getBond(1).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(2).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(2).getEnd() == &mol5.getAtom(3));

	BOOST_CHECK(&mol5.getBond(3).getBegin() == &mol5.getAtom(4));
	BOOST_CHECK(&mol5.getBond(3).getEnd() == &mol5.getAtom(0));


	BOOST_CHECK(mol5.getNumAtoms() == 5);
	BOOST_CHECK(mol5.getNumBonds() == 4);

	checkAtomIndices(mol5);
	checkBondIndices(mol5);

	BOOST_CHECK_THROW(mol5.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol5.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol5.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol5.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol5.containsAtom(mol5.getAtom(0)));

	BOOST_CHECK(!mol5.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom5));

	BOOST_CHECK(mol5.containsBond(mol5.getBond(1)));

	BOOST_CHECK(!mol5.containsBond(mol1_bond1));
	BOOST_CHECK(!mol5.containsBond(mol1_bond2));
	BOOST_CHECK(!mol5.containsBond(mol1_bond3));
	BOOST_CHECK(!mol5.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol5.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol5.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol5.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol5.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol5.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol5.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol5.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(0)) == 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(1)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(2)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(3)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(4)) != 0);

	BOOST_CHECK(mol5.getNumProperties() == 1);

	BOOST_CHECK(mol5.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	mol5.copy(mol5);

	BOOST_CHECK(&mol5.getBond(0).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(0).getEnd() == &mol5.getAtom(1));

	BOOST_CHECK(&mol5.getBond(1).getBegin() == &mol5.getAtom(2));
	BOOST_CHECK(&mol5.getBond(1).getEnd() == &mol5.getAtom(0));

	BOOST_CHECK(&mol5.getBond(2).getBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&mol5.getBond(2).getEnd() == &mol5.getAtom(3));

	BOOST_CHECK(&mol5.getBond(3).getBegin() == &mol5.getAtom(4));
	BOOST_CHECK(&mol5.getBond(3).getEnd() == &mol5.getAtom(0));


	BOOST_CHECK(mol5.getNumAtoms() == 5);
	BOOST_CHECK(mol5.getNumBonds() == 4);

	checkAtomIndices(mol5);
	checkBondIndices(mol5);

	BOOST_CHECK_THROW(mol5.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol5.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getAtomsBegin() == &mol5.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 1) == &mol5.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 2) == &mol5.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 3) == &mol5.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getAtomsBegin() + 4) == &mol5.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol5).getBondsBegin() == &mol5.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 1) == &mol5.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 2) == &mol5.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol5).getBondsBegin() + 3) == &mol5.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol5.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol5.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol5.containsAtom(mol5.getAtom(0)));

	BOOST_CHECK(!mol5.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol5.containsAtom(mol1_atom5));

	BOOST_CHECK(mol5.containsBond(mol5.getBond(1)));

	BOOST_CHECK(!mol5.containsBond(mol1_bond1));
	BOOST_CHECK(!mol5.containsBond(mol1_bond2));
	BOOST_CHECK(!mol5.containsBond(mol1_bond3));
	BOOST_CHECK(!mol5.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol5.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol5.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol5.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol5.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol5.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol5.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol5.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol5.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol5.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol5.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(0)) == 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(1)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(2)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(3)) != 0);
	BOOST_CHECK(mol5.getAtom(0).findBondToAtom(mol5.getAtom(4)) != 0);

	BOOST_CHECK(mol5.getNumProperties() == 1);

	BOOST_CHECK(mol5.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	mol5.clear();

	BOOST_CHECK(mol5.getNumAtoms() == 0);
	BOOST_CHECK(mol5.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getAtomsBegin() == const_cast<const BasicMolecule&>(mol5).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getAtomsBegin() == const_cast<BasicMolecule&>(mol5).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol5).getBondsBegin() == const_cast<const BasicMolecule&>(mol5).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol5).getBondsBegin() == const_cast<BasicMolecule&>(mol5).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol5).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol5).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol5.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol5.removeAtom(mol5.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol5.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol5.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol5.removeBond(mol5.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol5.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(mol5.getNumProperties() == 0);

//-----	

	Fragment frag(mol1);

	BOOST_CHECK(frag.getNumAtoms() == 5);
	BOOST_CHECK(frag.getNumBonds() == 4);

	frag.setProperty(prop_key1, std::string("Fragment"));

	BOOST_CHECK(frag.getProperty<std::string>(prop_key1) == "Fragment");

	frag.addAtom(frag.getAtom(0));
	frag.addAtom(frag.getAtom(3));

	frag.addBond(frag.getBond(2));
	frag.addBond(frag.getBond(1));

//-----	

	Fragment empty_frag;

	BasicMolecule mol8(empty_frag);

	BOOST_CHECK(mol8.getNumAtoms() == 0);
	BOOST_CHECK(mol8.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol8).getAtomsBegin() == const_cast<const BasicMolecule&>(mol8).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol8).getAtomsBegin() == const_cast<BasicMolecule&>(mol8).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol8).getBondsBegin() == const_cast<const BasicMolecule&>(mol8).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol8).getBondsBegin() == const_cast<BasicMolecule&>(mol8).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol8).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol8).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol8).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol8).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol8).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol8).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol8).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol8).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol8.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol8.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol8.removeAtom(mol8.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol8.removeAtom(mol8.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol8.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol8.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol8.removeBond(mol8.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol8.removeBond(mol8.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol8.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicMolecule mol9(frag);

	BOOST_CHECK(&mol9.getBond(0).getBegin() == &mol9.getAtom(0));
	BOOST_CHECK(&mol9.getBond(0).getEnd() == &mol9.getAtom(1));

	BOOST_CHECK(&mol9.getBond(1).getBegin() == &mol9.getAtom(2));
	BOOST_CHECK(&mol9.getBond(1).getEnd() == &mol9.getAtom(0));

	BOOST_CHECK(&mol9.getBond(2).getBegin() == &mol9.getAtom(0));
	BOOST_CHECK(&mol9.getBond(2).getEnd() == &mol9.getAtom(3));

	BOOST_CHECK(&mol9.getBond(3).getBegin() == &mol9.getAtom(4));
	BOOST_CHECK(&mol9.getBond(3).getEnd() == &mol9.getAtom(0));


	BOOST_CHECK(mol9.getNumAtoms() == 5);
	BOOST_CHECK(mol9.getNumBonds() == 4);

	checkAtomIndices(mol9);
	checkBondIndices(mol9);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol9).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol9).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol9).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol9).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol9).getAtomsBegin() == &mol9.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol9).getAtomsBegin() == &mol9.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getAtomsBegin() + 1) == &mol9.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getAtomsBegin() + 1) == &mol9.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getAtomsBegin() + 2) == &mol9.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getAtomsBegin() + 2) == &mol9.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getAtomsBegin() + 3) == &mol9.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getAtomsBegin() + 3) == &mol9.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getAtomsBegin() + 4) == &mol9.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getAtomsBegin() + 4) == &mol9.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol9).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol9).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol9).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol9).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol9).getBondsBegin() == &mol9.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol9).getBondsBegin() == &mol9.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getBondsBegin() + 1) == &mol9.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getBondsBegin() + 1) == &mol9.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getBondsBegin() + 2) == &mol9.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getBondsBegin() + 2) == &mol9.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol9).getBondsBegin() + 3) == &mol9.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol9).getBondsBegin() + 3) == &mol9.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol9).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol9).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol9).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol9).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol9.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol9.removeAtom(mol9.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol9.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol9.removeBond(mol9.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol9.containsAtom(mol9.getAtom(0)));

	BOOST_CHECK(!mol9.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol9.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol9.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol9.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol9.containsAtom(mol1_atom5));

	BOOST_CHECK(mol9.containsBond(mol9.getBond(1)));

	BOOST_CHECK(!mol9.containsBond(mol1_bond1));
	BOOST_CHECK(!mol9.containsBond(mol1_bond2));
	BOOST_CHECK(!mol9.containsBond(mol1_bond3));
	BOOST_CHECK(!mol9.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol9.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol9.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol9.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol9.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol9.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol9.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol9.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol9.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol9.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol9.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol9.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol9.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol9.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol9.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol9.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol9.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol9.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol9.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol9.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol9.getAtom(0).findBondToAtom(mol9.getAtom(0)) == 0);
	BOOST_CHECK(mol9.getAtom(0).findBondToAtom(mol9.getAtom(1)) != 0);
	BOOST_CHECK(mol9.getAtom(0).findBondToAtom(mol9.getAtom(2)) != 0);
	BOOST_CHECK(mol9.getAtom(0).findBondToAtom(mol9.getAtom(3)) != 0);
	BOOST_CHECK(mol9.getAtom(0).findBondToAtom(mol9.getAtom(4)) != 0);

	BOOST_CHECK(mol9.getNumProperties() == 1);

	BOOST_CHECK(mol9.getProperty<std::string>(prop_key1) == "Fragment");

//-----	

	BasicMolecule mol10;

	BOOST_CHECK(&(mol10 = frag) == &mol10);

	BOOST_CHECK(&mol10.getBond(0).getBegin() == &mol10.getAtom(0));
	BOOST_CHECK(&mol10.getBond(0).getEnd() == &mol10.getAtom(1));

	BOOST_CHECK(&mol10.getBond(1).getBegin() == &mol10.getAtom(2));
	BOOST_CHECK(&mol10.getBond(1).getEnd() == &mol10.getAtom(0));

	BOOST_CHECK(&mol10.getBond(2).getBegin() == &mol10.getAtom(0));
	BOOST_CHECK(&mol10.getBond(2).getEnd() == &mol10.getAtom(3));

	BOOST_CHECK(&mol10.getBond(3).getBegin() == &mol10.getAtom(4));
	BOOST_CHECK(&mol10.getBond(3).getEnd() == &mol10.getAtom(0));


	BOOST_CHECK(mol10.getNumAtoms() == 5);
	BOOST_CHECK(mol10.getNumBonds() == 4);

	checkAtomIndices(mol10);
	checkBondIndices(mol10);

	BOOST_CHECK_THROW(mol10.getAtomIndex(mol1_atom1), ItemNotFound);
	BOOST_CHECK_THROW(mol10.getBondIndex(mol1_bond2), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol10).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol10).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol10).getAtomsBegin() == &mol10.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol10).getAtomsBegin() == &mol10.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 1) == &mol10.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 1) == &mol10.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 2) == &mol10.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 2) == &mol10.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 3) == &mol10.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 3) == &mol10.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 4) == &mol10.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 4) == &mol10.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol10).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol10).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol10).getBondsBegin() == &mol10.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol10).getBondsBegin() == &mol10.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 1) == &mol10.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 1) == &mol10.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 2) == &mol10.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 2) == &mol10.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 3) == &mol10.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 3) == &mol10.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol10.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol10.removeAtom(mol10.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol10.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol10.removeBond(mol10.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol10.containsAtom(mol10.getAtom(0)));

	BOOST_CHECK(!mol10.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom5));

	BOOST_CHECK(mol10.containsBond(mol10.getBond(1)));

	BOOST_CHECK(!mol10.containsBond(mol1_bond1));
	BOOST_CHECK(!mol10.containsBond(mol1_bond2));
	BOOST_CHECK(!mol10.containsBond(mol1_bond3));
	BOOST_CHECK(!mol10.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol10.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol10.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol10.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol10.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol10.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol10.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol10.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol10.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol10.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol10.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol10.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol10.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(0)) == 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(1)) != 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(2)) != 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(3)) != 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(4)) != 0);

	BOOST_CHECK(mol10.getNumProperties() == 1);

	BOOST_CHECK(mol10.getProperty<std::string>(prop_key1) == "Fragment");
	
//-----	

	BasicMolecule mol11;

	BOOST_CHECK(&(mol11 += frag) == &mol11);

	BOOST_CHECK(&mol11.getBond(0).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(0).getEnd() == &mol11.getAtom(1));

	BOOST_CHECK(&mol11.getBond(1).getBegin() == &mol11.getAtom(2));
	BOOST_CHECK(&mol11.getBond(1).getEnd() == &mol11.getAtom(0));

	BOOST_CHECK(&mol11.getBond(2).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(2).getEnd() == &mol11.getAtom(3));

	BOOST_CHECK(&mol11.getBond(3).getBegin() == &mol11.getAtom(4));
	BOOST_CHECK(&mol11.getBond(3).getEnd() == &mol11.getAtom(0));


	BOOST_CHECK(mol11.getNumAtoms() == 5);
	BOOST_CHECK(mol11.getNumBonds() == 4);

	checkAtomIndices(mol11);
	checkBondIndices(mol11);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol11).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol11).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol11).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol11).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol11.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol11.removeAtom(mol11.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol11.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol11.removeBond(mol11.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol11.containsAtom(mol11.getAtom(0)));

	BOOST_CHECK(!mol11.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol11.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol11.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol11.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol11.containsAtom(mol1_atom5));

	BOOST_CHECK(mol11.containsBond(mol11.getBond(1)));

	BOOST_CHECK(!mol11.containsBond(mol1_bond1));
	BOOST_CHECK(!mol11.containsBond(mol1_bond2));
	BOOST_CHECK(!mol11.containsBond(mol1_bond3));
	BOOST_CHECK(!mol11.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol11.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol11.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol11.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol11.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol11.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol11.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol11.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(0)) == 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(1)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(2)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(3)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(4)) != 0);

	BOOST_CHECK(mol11.getNumProperties() == 0);

	BOOST_CHECK_THROW(mol11.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicMolecule mol12;

	BOOST_CHECK(&(mol12 = Fragment()) == &mol12);

	BOOST_CHECK(mol12.getNumAtoms() == 0);
	BOOST_CHECK(mol12.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol12).getAtomsBegin() == const_cast<const BasicMolecule&>(mol12).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol12).getAtomsBegin() == const_cast<BasicMolecule&>(mol12).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol12).getBondsBegin() == const_cast<const BasicMolecule&>(mol12).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol12).getBondsBegin() == const_cast<BasicMolecule&>(mol12).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol12).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol12).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol12).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol12).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol12).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol12).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol12).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol12).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol12.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol12.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol12.removeAtom(mol12.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol12.removeAtom(mol12.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol12.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol12.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol12.removeBond(mol12.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol12.removeBond(mol12.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol12.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(mol12.getNumProperties() == 0);	

//-----	

	BasicMolecule mol13;

	BOOST_CHECK(&(mol13 += Fragment()) == &mol13);

	BOOST_CHECK(mol13.getNumAtoms() == 0);
	BOOST_CHECK(mol13.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol13).getAtomsBegin() == const_cast<const BasicMolecule&>(mol13).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol13).getAtomsBegin() == const_cast<BasicMolecule&>(mol13).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol13).getBondsBegin() == const_cast<const BasicMolecule&>(mol13).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol13).getBondsBegin() == const_cast<BasicMolecule&>(mol13).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol13).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol13).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol13).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol13).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol13).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol13).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol13).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol13).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol13.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol13.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol13.removeAtom(mol13.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol13.removeAtom(mol13.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol13.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol13.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol13.removeBond(mol13.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol13.removeBond(mol13.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol13.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(mol13.getNumProperties() == 0);	

//-----	

	mol11.setProperty(prop_key1, std::string("BasicMolecule 11"));

	mol11.append(frag);

	BOOST_CHECK(&mol11.getBond(0).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(0).getEnd() == &mol11.getAtom(1));

	BOOST_CHECK(&mol11.getBond(1).getBegin() == &mol11.getAtom(2));
	BOOST_CHECK(&mol11.getBond(1).getEnd() == &mol11.getAtom(0));

	BOOST_CHECK(&mol11.getBond(2).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(2).getEnd() == &mol11.getAtom(3));

	BOOST_CHECK(&mol11.getBond(3).getBegin() == &mol11.getAtom(4));
	BOOST_CHECK(&mol11.getBond(3).getEnd() == &mol11.getAtom(0));

	BOOST_CHECK(&mol11.getBond(4).getBegin() == &mol11.getAtom(5));
	BOOST_CHECK(&mol11.getBond(4).getEnd() == &mol11.getAtom(6));

	BOOST_CHECK(&mol11.getBond(5).getBegin() == &mol11.getAtom(7));
	BOOST_CHECK(&mol11.getBond(5).getEnd() == &mol11.getAtom(5));

	BOOST_CHECK(&mol11.getBond(6).getBegin() == &mol11.getAtom(5));
	BOOST_CHECK(&mol11.getBond(6).getEnd() == &mol11.getAtom(8));

	BOOST_CHECK(&mol11.getBond(7).getBegin() == &mol11.getAtom(9));
	BOOST_CHECK(&mol11.getBond(7).getEnd() == &mol11.getAtom(5));


	BOOST_CHECK(mol11.getNumAtoms() == 10);
	BOOST_CHECK(mol11.getNumBonds() == 8);

	checkAtomIndices(mol11);
	checkBondIndices(mol11);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 10 == const_cast<const BasicMolecule&>(mol11).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 10 == const_cast<BasicMolecule&>(mol11).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 8 == const_cast<const BasicMolecule&>(mol11).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 8 == const_cast<BasicMolecule&>(mol11).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getAtom(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getAtom(10), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getBond(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getBond(8), IndexError);


	BOOST_CHECK_THROW(mol11.removeAtom(10), IndexError);

	BOOST_CHECK_THROW(mol11.removeAtom(mol11.getAtomsBegin() + 10), RangeError);


	BOOST_CHECK_THROW(mol11.removeBond(8), IndexError);

	BOOST_CHECK_THROW(mol11.removeBond(mol11.getBondsBegin() + 8), RangeError);


	BOOST_CHECK(mol11.containsAtom(mol11.getAtom(0)));

	BOOST_CHECK(!mol11.containsAtom(mol1_atom1));

	BOOST_CHECK(mol11.containsBond(mol11.getBond(1)));

	BOOST_CHECK(!mol11.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol11.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol11.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol11.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol11.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol11.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol11.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol11.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(0)) == 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(1)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(2)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(3)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(4)) != 0);

	BOOST_CHECK(mol11.getNumProperties() == 1);

	BOOST_CHECK(mol11.getProperty<std::string>(prop_key1) == "BasicMolecule 11");

//-----	

	mol10.setProperty(prop_key1, std::string("BasicMolecule 10"));

	BOOST_CHECK(&(mol10 += Fragment()) == &mol10);

	BOOST_CHECK(&mol10.getBond(0).getBegin() == &mol10.getAtom(0));
	BOOST_CHECK(&mol10.getBond(0).getEnd() == &mol10.getAtom(1));

	BOOST_CHECK(&mol10.getBond(1).getBegin() == &mol10.getAtom(2));
	BOOST_CHECK(&mol10.getBond(1).getEnd() == &mol10.getAtom(0));

	BOOST_CHECK(&mol10.getBond(2).getBegin() == &mol10.getAtom(0));
	BOOST_CHECK(&mol10.getBond(2).getEnd() == &mol10.getAtom(3));

	BOOST_CHECK(&mol10.getBond(3).getBegin() == &mol10.getAtom(4));
	BOOST_CHECK(&mol10.getBond(3).getEnd() == &mol10.getAtom(0));


	BOOST_CHECK(mol10.getNumAtoms() == 5);
	BOOST_CHECK(mol10.getNumBonds() == 4);

	checkAtomIndices(mol10);
	checkBondIndices(mol10);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol10).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol10).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol10).getAtomsBegin() == &mol10.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol10).getAtomsBegin() == &mol10.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 1) == &mol10.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 1) == &mol10.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 2) == &mol10.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 2) == &mol10.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 3) == &mol10.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 3) == &mol10.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() + 4) == &mol10.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getAtomsBegin() + 4) == &mol10.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol10).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol10).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol10).getBondsBegin() == &mol10.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol10).getBondsBegin() == &mol10.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 1) == &mol10.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 1) == &mol10.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 2) == &mol10.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 2) == &mol10.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol10).getBondsBegin() + 3) == &mol10.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol10).getBondsBegin() + 3) == &mol10.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol10.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol10.removeAtom(mol10.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol10.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol10.removeBond(mol10.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol10.containsAtom(mol10.getAtom(0)));

	BOOST_CHECK(!mol10.containsAtom(mol1_atom1));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom2));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom3));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol10.containsAtom(mol1_atom5));

	BOOST_CHECK(mol10.containsBond(mol10.getBond(1)));

	BOOST_CHECK(!mol10.containsBond(mol1_bond1));
	BOOST_CHECK(!mol10.containsBond(mol1_bond2));
	BOOST_CHECK(!mol10.containsBond(mol1_bond3));
	BOOST_CHECK(!mol10.containsBond(mol1_bond4));
	
	BOOST_CHECK(mol10.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol10.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol10.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol10.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol10.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol10.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol10.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol10.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol10.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol10.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol10.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol10.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol10.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(0)) == 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(1)) != 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(2)) != 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(3)) != 0);
	BOOST_CHECK(mol10.getAtom(0).findBondToAtom(mol10.getAtom(4)) != 0);

	BOOST_CHECK(mol10.getProperty<std::string>(prop_key1) == "BasicMolecule 10");

//-----	

	BOOST_CHECK(&(mol10 = Fragment()) == &mol10);

	BOOST_CHECK(mol10.getNumAtoms() == 0);
	BOOST_CHECK(mol10.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol10).getAtomsBegin() == const_cast<const BasicMolecule&>(mol10).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol10).getAtomsBegin() == const_cast<BasicMolecule&>(mol10).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol10).getBondsBegin() == const_cast<const BasicMolecule&>(mol10).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol10).getBondsBegin() == const_cast<BasicMolecule&>(mol10).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol10).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol10).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol10.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol10.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol10.removeAtom(mol10.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol10.removeAtom(mol10.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol10.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol10.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol10.removeBond(mol10.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol10.removeBond(mol10.getBondsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol10.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(mol10.getNumProperties() == 0);	

//-----	

	BOOST_CHECK(&(mol11 = frag) == &mol11);

	BOOST_CHECK(&mol11.getBond(0).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(0).getEnd() == &mol11.getAtom(1));

	BOOST_CHECK(&mol11.getBond(1).getBegin() == &mol11.getAtom(2));
	BOOST_CHECK(&mol11.getBond(1).getEnd() == &mol11.getAtom(0));

	BOOST_CHECK(&mol11.getBond(2).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(2).getEnd() == &mol11.getAtom(3));

	BOOST_CHECK(&mol11.getBond(3).getBegin() == &mol11.getAtom(4));
	BOOST_CHECK(&mol11.getBond(3).getEnd() == &mol11.getAtom(0));


	BOOST_CHECK(mol11.getNumAtoms() == 5);
	BOOST_CHECK(mol11.getNumBonds() == 4);

	checkAtomIndices(mol11);
	checkBondIndices(mol11);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol11).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol11).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol11).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol11).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol11.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol11.removeAtom(mol11.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol11.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol11.removeBond(mol11.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol11.containsAtom(mol11.getAtom(0)));

	BOOST_CHECK(!mol11.containsAtom(mol1_atom1));

	BOOST_CHECK(mol11.containsBond(mol11.getBond(1)));

	BOOST_CHECK(!mol11.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol11.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol11.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol11.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol11.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol11.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol11.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol11.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(0)) == 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(1)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(2)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(3)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(4)) != 0);

	BOOST_CHECK(mol11.getNumProperties() == 1);

	BOOST_CHECK(mol11.getProperty<std::string>(prop_key1) == "Fragment");

//-----	

	mol11.clear();
	mol11.setProperty(prop_key1, std::string("BasicMolecule 11"));

	mol11.copy(frag);

	BOOST_CHECK(&mol11.getBond(0).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(0).getEnd() == &mol11.getAtom(1));

	BOOST_CHECK(&mol11.getBond(1).getBegin() == &mol11.getAtom(2));
	BOOST_CHECK(&mol11.getBond(1).getEnd() == &mol11.getAtom(0));

	BOOST_CHECK(&mol11.getBond(2).getBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&mol11.getBond(2).getEnd() == &mol11.getAtom(3));

	BOOST_CHECK(&mol11.getBond(3).getBegin() == &mol11.getAtom(4));
	BOOST_CHECK(&mol11.getBond(3).getEnd() == &mol11.getAtom(0));


	BOOST_CHECK(mol11.getNumAtoms() == 5);
	BOOST_CHECK(mol11.getNumBonds() == 4);

	checkAtomIndices(mol11);
	checkBondIndices(mol11);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol11).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol11).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getAtomsBegin() == &mol11.getAtom(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 1) == &mol11.getAtom(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 2) == &mol11.getAtom(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 3) == &mol11.getAtom(3));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getAtomsBegin() + 4) == &mol11.getAtom(4));


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 4 == const_cast<const BasicMolecule&>(mol11).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 4 == const_cast<BasicMolecule&>(mol11).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol11).getBondsBegin() == &mol11.getBond(0));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 1) == &mol11.getBond(1));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 2) == &mol11.getBond(2));

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol11).getBondsBegin() + 3) == &mol11.getBond(3));


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getAtom(5), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol11).getBond(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol11).getBond(4), IndexError);


	BOOST_CHECK_THROW(mol11.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol11.removeAtom(mol11.getAtomsBegin() + 5), RangeError);


	BOOST_CHECK_THROW(mol11.removeBond(4), IndexError);

	BOOST_CHECK_THROW(mol11.removeBond(mol11.getBondsBegin() + 4), RangeError);


	BOOST_CHECK(mol11.containsAtom(mol11.getAtom(0)));

	BOOST_CHECK(!mol11.containsAtom(mol1_atom1));

	BOOST_CHECK(mol11.containsBond(mol11.getBond(1)));

	BOOST_CHECK(!mol11.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol11.getAtom(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(mol11.getAtom(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(mol11.getAtom(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(mol11.getAtom(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(mol11.getBond(0).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(1).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(2).getProperty<std::size_t>(prop_key3) == 1);
	BOOST_CHECK(mol11.getBond(3).getProperty<std::size_t>(prop_key3) == 1);

	BOOST_CHECK(mol11.getAtom(0).getNumAtoms() == 4);
	BOOST_CHECK(mol11.getAtom(0).getNumBonds() == 4);
	
	BOOST_CHECK(mol11.getAtom(1).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(1).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(2).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(2).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(3).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(3).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(4).getNumAtoms() == 1);
	BOOST_CHECK(mol11.getAtom(4).getNumBonds() == 1);
	
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(0)) == 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(1)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(2)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(3)) != 0);
	BOOST_CHECK(mol11.getAtom(0).findBondToAtom(mol11.getAtom(4)) != 0);

	BOOST_CHECK(mol11.getNumProperties() == 1);

	BOOST_CHECK(mol11.getProperty<std::string>(prop_key1) == "Fragment");

//-----	

	mol1.removeBond(2);

	BOOST_CHECK(&mol1_bond1.getBegin() == &mol1_atom1);
	BOOST_CHECK(&mol1_bond1.getEnd() == &mol1_atom2);

	BOOST_CHECK(&mol1_bond2.getBegin() == &mol1_atom3);
	BOOST_CHECK(&mol1_bond2.getEnd() == &mol1_atom1);

	BOOST_CHECK(&mol1_bond4.getBegin() == &mol1_atom5);
	BOOST_CHECK(&mol1_bond4.getEnd() == &mol1_atom1);


	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 3);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK_THROW(mol1.getAtomIndex(mol11.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol1.getBondIndex(mol11.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol1.getBondIndex(mol1_bond3), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 4) == &mol1_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 3 == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 3 == const_cast<BasicMolecule&>(mol1).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getBondsBegin() == &mol1_bond1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getBondsBegin() == &mol1_bond1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 1) == &mol1_bond2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 1) == &mol1_bond2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getBondsBegin() + 2) == &mol1_bond4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getBondsBegin() + 2) == &mol1_bond4);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(2) == &mol1_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(3) == &mol1_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(4) == &mol1_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(5), IndexError);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(0) == &mol1_bond1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(0) == &mol1_bond1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(1) == &mol1_bond2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(1) == &mol1_bond2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getBond(2) == &mol1_bond4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getBond(2) == &mol1_bond4);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(3), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 5), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd()), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(3), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 4), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd()), RangeError);


	BOOST_CHECK(mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(mol1.containsAtom(mol1_atom3));

	BOOST_CHECK(mol1.containsBond(mol1_bond4));
	BOOST_CHECK(!mol1.containsBond(mol1_bond3));
	BOOST_CHECK(mol1.containsBond(mol1_bond2));
	BOOST_CHECK(mol1.containsBond(mol1_bond1));
	
//-----	

	mol1.removeAtom(0);

	BOOST_CHECK(mol1.getNumAtoms() == 4);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK_THROW(mol1.getAtomIndex(mol11.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol1.getBondIndex(mol11.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(mol1.getBondIndex(mol1_bond3), ItemNotFound);
	BOOST_CHECK_THROW(mol1.getAtomIndex(mol1_atom1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 4 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 4 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom2);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 3) == &mol1_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(2) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(2) == &mol1_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(3) == &mol1_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(3) == &mol1_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(4), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(4), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 4), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd()), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd() + 1), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd() + 1), RangeError);


	BOOST_CHECK(!mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(mol1.containsAtom(mol1_atom3));

	BOOST_CHECK(!mol1.containsBond(mol1_bond4));
	BOOST_CHECK(!mol1.containsBond(mol1_bond3));
	BOOST_CHECK(!mol1.containsBond(mol1_bond2));
	BOOST_CHECK(!mol1.containsBond(mol1_bond1));

//-----	

	mol1.removeAtom(1);

	BOOST_CHECK(mol1.getNumAtoms() == 3);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 3 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 3 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom2);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2) == &mol1_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(2) == &mol1_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(2) == &mol1_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(3), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(3), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 3), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd()), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd() + 1), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd() + 1), RangeError);


	BOOST_CHECK(!mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(!mol1.containsAtom(mol1_atom3));

	BOOST_CHECK(!mol1.containsBond(mol1_bond4));
	BOOST_CHECK(!mol1.containsBond(mol1_bond3));
	BOOST_CHECK(!mol1.containsBond(mol1_bond2));
	BOOST_CHECK(!mol1.containsBond(mol1_bond1));

//-----	

	mol1.removeAtom(2);

	BOOST_CHECK(mol1.getNumAtoms() == 2);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 2 == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 2 == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom2);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol1).getAtomsBegin() == &mol1_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol1).getAtomsBegin() + 1) == &mol1_atom4);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(0) == &mol1_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(0) == &mol1_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol1).getAtom(1) == &mol1_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol1).getAtom(1) == &mol1_atom4);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(2), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(2), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);


	BOOST_CHECK_THROW(mol1.removeAtom(3), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 2), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd()), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsEnd() + 1), RangeError);


	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsEnd() + 1), RangeError);


	BOOST_CHECK(!mol1.containsAtom(mol1_atom1));
	BOOST_CHECK(mol1.containsAtom(mol1_atom2));
	BOOST_CHECK(mol1.containsAtom(mol1_atom4));
	BOOST_CHECK(!mol1.containsAtom(mol1_atom5));
	BOOST_CHECK(!mol1.containsAtom(mol1_atom3));

	BOOST_CHECK(!mol1.containsBond(mol1_bond4));
	BOOST_CHECK(!mol1.containsBond(mol1_bond3));
	BOOST_CHECK(!mol1.containsBond(mol1_bond2));
	BOOST_CHECK(!mol1.containsBond(mol1_bond1));
	
	BOOST_CHECK(mol1.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----

	BasicAtom& mol2_atom1 = mol2.getAtom(0);
	BasicAtom& mol2_atom2 = mol2.getAtom(1);
	BasicAtom& mol2_atom3 = mol2.getAtom(2);
	BasicAtom& mol2_atom4 = mol2.getAtom(3);
	BasicAtom& mol2_atom5 = mol2.getAtom(4);

	BasicBond& mol2_bond1 = mol2.getBond(0);
	BasicBond& mol2_bond2 = mol2.getBond(1);
	BasicBond& mol2_bond3 = mol2.getBond(2);
	BasicBond& mol2_bond4 = mol2.getBond(3);

	mol2.removeBond(mol2.getBondsBegin() + 2);

	BOOST_CHECK(&mol2_bond1.getBegin() == &mol2_atom1);
	BOOST_CHECK(&mol2_bond1.getEnd() == &mol2_atom2);

	BOOST_CHECK(&mol2_bond2.getBegin() == &mol2_atom3);
	BOOST_CHECK(&mol2_bond2.getEnd() == &mol2_atom1);

	BOOST_CHECK(&mol2_bond4.getBegin() == &mol2_atom5);
	BOOST_CHECK(&mol2_bond4.getEnd() == &mol2_atom1);


	BOOST_CHECK(mol2.getNumAtoms() == 5);
	BOOST_CHECK(mol2.getNumBonds() == 3);

	checkAtomIndices(mol2);
	checkBondIndices(mol2);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 5 == const_cast<const BasicMolecule&>(mol2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 5 == const_cast<BasicMolecule&>(mol2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 4) == &mol2_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 4) == &mol2_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 3 == const_cast<const BasicMolecule&>(mol2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 3 == const_cast<BasicMolecule&>(mol2).getBondsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getBondsBegin() == &mol2_bond1);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getBondsBegin() == &mol2_bond1);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 1) == &mol2_bond2);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 1) == &mol2_bond2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getBondsBegin() + 2) == &mol2_bond4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getBondsBegin() + 2) == &mol2_bond4);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(0) == &mol2_atom1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(0) == &mol2_atom1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(1) == &mol2_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(1) == &mol2_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(2) == &mol2_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(2) == &mol2_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(3) == &mol2_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(3) == &mol2_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(4) == &mol2_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(4) == &mol2_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getAtom(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getAtom(5), IndexError);


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getBond(0) == &mol2_bond1);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getBond(0) == &mol2_bond1);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getBond(1) == &mol2_bond2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getBond(1) == &mol2_bond2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getBond(2) == &mol2_bond4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getBond(2) == &mol2_bond4);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getBond(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getBond(3), IndexError);


	BOOST_CHECK_THROW(mol2.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsBegin() + 5), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd()), RangeError);


	BOOST_CHECK_THROW(mol2.removeBond(3), IndexError);

	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsBegin() + 4), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd()), RangeError);


	BOOST_CHECK(mol2.containsAtom(mol2_atom1));
	BOOST_CHECK(mol2.containsAtom(mol2_atom2));
	BOOST_CHECK(mol2.containsAtom(mol2_atom4));
	BOOST_CHECK(mol2.containsAtom(mol2_atom5));
	BOOST_CHECK(mol2.containsAtom(mol2_atom3));

	BOOST_CHECK(mol2.containsBond(mol2_bond4));
	BOOST_CHECK(!mol2.containsBond(mol2_bond3));
	BOOST_CHECK(mol2.containsBond(mol2_bond2));
	BOOST_CHECK(mol2.containsBond(mol2_bond1));

//-----

	BasicMolecule::AtomIterator a_it = mol2.removeAtom(mol2.getAtomsBegin());

	BOOST_CHECK(a_it == mol2.getAtomsBegin());

	BOOST_CHECK(mol2.getNumAtoms() == 4);
	BOOST_CHECK(mol2.getNumBonds() == 0);

	checkAtomIndices(mol2);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 4 == const_cast<const BasicMolecule&>(mol2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 4 == const_cast<BasicMolecule&>(mol2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom2);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom3);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom3);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 3) == &mol2_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getBondsBegin() == const_cast<const BasicMolecule&>(mol2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getBondsBegin() == const_cast<BasicMolecule&>(mol2).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(0) == &mol2_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(0) == &mol2_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(1) == &mol2_atom3);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(1) == &mol2_atom3);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(2) == &mol2_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(2) == &mol2_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(3) == &mol2_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(3) == &mol2_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getAtom(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getAtom(4), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getBond(0), IndexError);


	BOOST_CHECK_THROW(mol2.removeAtom(4), IndexError);

	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsBegin() + 4), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd()), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd() + 1), RangeError);


	BOOST_CHECK_THROW(mol2.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol2.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd()), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd() + 1), RangeError);


	BOOST_CHECK(!mol2.containsAtom(mol2_atom1));
	BOOST_CHECK(mol2.containsAtom(mol2_atom2));
	BOOST_CHECK(mol2.containsAtom(mol2_atom4));
	BOOST_CHECK(mol2.containsAtom(mol2_atom5));
	BOOST_CHECK(mol2.containsAtom(mol2_atom3));

	BOOST_CHECK(!mol2.containsBond(mol2_bond4));
	BOOST_CHECK(!mol2.containsBond(mol2_bond3));
	BOOST_CHECK(!mol2.containsBond(mol2_bond2));
	BOOST_CHECK(!mol2.containsBond(mol2_bond1));
	
//-----	

	a_it = mol2.removeAtom(++mol2.getAtomsBegin());

	BOOST_CHECK(a_it == ++mol2.getAtomsBegin());

	BOOST_CHECK(mol2.getNumAtoms() == 3);
	BOOST_CHECK(mol2.getNumBonds() == 0);

	checkAtomIndices(mol2);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 3 == const_cast<const BasicMolecule&>(mol2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 3 == const_cast<BasicMolecule&>(mol2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom2);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom4);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2_atom5);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 2) == &mol2_atom5);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getBondsBegin() == const_cast<const BasicMolecule&>(mol2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getBondsBegin() == const_cast<BasicMolecule&>(mol2).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(0) == &mol2_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(0) == &mol2_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(1) == &mol2_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(1) == &mol2_atom4);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(2) == &mol2_atom5);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(2) == &mol2_atom5);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getAtom(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getAtom(3), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getBond(0), IndexError);


	BOOST_CHECK_THROW(mol2.removeAtom(3), IndexError);

	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsBegin() + 3), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd()), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd() + 1), RangeError);


	BOOST_CHECK_THROW(mol2.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol2.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd()), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd() + 1), RangeError);


	BOOST_CHECK(!mol2.containsAtom(mol2_atom1));
	BOOST_CHECK(mol2.containsAtom(mol2_atom2));
	BOOST_CHECK(mol2.containsAtom(mol2_atom4));
	BOOST_CHECK(mol2.containsAtom(mol2_atom5));
	BOOST_CHECK(!mol2.containsAtom(mol2_atom3));

	BOOST_CHECK(!mol2.containsBond(mol2_bond4));
	BOOST_CHECK(!mol2.containsBond(mol2_bond3));
	BOOST_CHECK(!mol2.containsBond(mol2_bond2));
	BOOST_CHECK(!mol2.containsBond(mol2_bond1));
	
//-----	

	a_it = mol2.removeAtom(--mol2.getAtomsEnd());

	BOOST_CHECK(a_it == mol2.getAtomsEnd());

	BOOST_CHECK(mol2.getNumAtoms() == 2);
	BOOST_CHECK(mol2.getNumBonds() == 0);

	checkAtomIndices(mol2);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 2 == const_cast<const BasicMolecule&>(mol2).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 2 == const_cast<BasicMolecule&>(mol2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<const BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom2);
	BOOST_CHECK(&*const_cast<BasicMolecule&>(mol2).getAtomsBegin() == &mol2_atom2);

	BOOST_CHECK(&*(const_cast<const BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom4);
	BOOST_CHECK(&*(const_cast<BasicMolecule&>(mol2).getAtomsBegin() + 1) == &mol2_atom4);


	BOOST_CHECK(const_cast<const BasicMolecule&>(mol2).getBondsBegin() == const_cast<const BasicMolecule&>(mol2).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol2).getBondsBegin() == const_cast<BasicMolecule&>(mol2).getBondsEnd());


	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(0) == &mol2_atom2);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(0) == &mol2_atom2);

	BOOST_CHECK(&const_cast<const BasicMolecule&>(mol2).getAtom(1) == &mol2_atom4);
	BOOST_CHECK(&const_cast<BasicMolecule&>(mol2).getAtom(1) == &mol2_atom4);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getAtom(2), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getAtom(2), IndexError);


	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol2).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol2).getBond(0), IndexError);


	BOOST_CHECK_THROW(mol2.removeAtom(3), IndexError);

	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsBegin() + 2), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd()), RangeError);
	BOOST_CHECK_THROW(mol2.removeAtom(mol2.getAtomsEnd() + 1), RangeError);


	BOOST_CHECK_THROW(mol2.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol2.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd()), RangeError);
	BOOST_CHECK_THROW(mol2.removeBond(mol2.getBondsEnd() + 1), RangeError);


	BOOST_CHECK(!mol2.containsAtom(mol2_atom1));
	BOOST_CHECK(mol2.containsAtom(mol2_atom2));
	BOOST_CHECK(mol2.containsAtom(mol2_atom4));
	BOOST_CHECK(!mol2.containsAtom(mol2_atom5));
	BOOST_CHECK(!mol2.containsAtom(mol2_atom3));

	BOOST_CHECK(!mol2.containsBond(mol2_bond4));
	BOOST_CHECK(!mol2.containsBond(mol2_bond3));
	BOOST_CHECK(!mol2.containsBond(mol2_bond2));
	BOOST_CHECK(!mol2.containsBond(mol2_bond1));

	BOOST_CHECK(mol2.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	mol1.removeAtom(0);
	
	a_it = mol1.removeAtom(mol1.getAtomsBegin());

	BOOST_CHECK(a_it == mol1.getAtomsBegin());

	BOOST_CHECK(mol1.getNumAtoms() == 0);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getAtomsBegin() == const_cast<const BasicMolecule&>(mol1).getAtomsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getAtomsBegin() == const_cast<BasicMolecule&>(mol1).getAtomsEnd());

	BOOST_CHECK(const_cast<const BasicMolecule&>(mol1).getBondsBegin() == const_cast<const BasicMolecule&>(mol1).getBondsEnd());
	BOOST_CHECK(const_cast<BasicMolecule&>(mol1).getBondsBegin() == const_cast<BasicMolecule&>(mol1).getBondsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getAtom(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getAtom(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicMolecule&>(mol1).getBond(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicMolecule&>(mol1).getBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeAtom(mol1.getAtomsBegin() + 1), RangeError);

	BOOST_CHECK_THROW(mol1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(mol1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin()), RangeError);
	BOOST_CHECK_THROW(mol1.removeBond(mol1.getBondsBegin() + 1), RangeError);

	BOOST_CHECK(mol1.getProperty<std::string>(prop_key1) == "BasicMolecule 1");

//-----	

	BOOST_CHECK(mol1.addAtom().getNumProperties() == 0);
	BOOST_CHECK(mol1.addAtom().getNumProperties() == 0);
	BOOST_CHECK(mol1.addAtom().getNumProperties() == 0);
	BOOST_CHECK(mol1.addAtom().getNumProperties() == 0);
	BOOST_CHECK(mol1.addAtom().getNumProperties() == 0);

	BOOST_CHECK(mol1.getAtom(0).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(1).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(2).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(3).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(4).getNumBonds() == 0);

	BOOST_CHECK(mol1.getAtom(0).getNumAtoms() == 0);
	BOOST_CHECK(mol1.getAtom(1).getNumAtoms() == 0);
	BOOST_CHECK(mol1.getAtom(2).getNumAtoms() == 0);
	BOOST_CHECK(mol1.getAtom(3).getNumAtoms() == 0);
	BOOST_CHECK(mol1.getAtom(4).getNumAtoms() == 0);

	BOOST_CHECK(mol1.addBond(0, 1).getNumProperties() == 0);
	BOOST_CHECK(mol1.addBond(0, 2).getNumProperties() == 0);
	BOOST_CHECK(mol1.addBond(0, 3).getNumProperties() == 0);
	BOOST_CHECK(mol1.addBond(4, 0).getNumProperties() == 0);

	BOOST_CHECK(mol1.getAtom(0).getNumBonds() == 4);
	BOOST_CHECK(mol1.getAtom(1).getNumBonds() == 1);
	BOOST_CHECK(mol1.getAtom(2).getNumBonds() == 1);
	BOOST_CHECK(mol1.getAtom(3).getNumBonds() == 1);
	BOOST_CHECK(mol1.getAtom(4).getNumBonds() == 1);

	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 4);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

//-----	

	BasicMolecule::BondIterator b_it = mol1.removeBond(--mol1.getBondsEnd());

	BOOST_CHECK(b_it == mol1.getBondsEnd());

	b_it = mol1.removeBond(mol1.getBondsBegin());

	BOOST_CHECK(b_it == mol1.getBondsBegin());

	b_it = mol1.removeBond(++mol1.getBondsBegin());

	BOOST_CHECK(b_it == ++mol1.getBondsBegin());

	b_it = mol1.removeBond(mol1.getBondsBegin());

	BOOST_CHECK(b_it == mol1.getBondsEnd());
	BOOST_CHECK(b_it == mol1.getBondsBegin());

	BOOST_CHECK(mol1.getAtom(0).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(1).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(2).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(3).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(4).getNumBonds() == 0);

	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);

//-----	

	mol1.addBond(0, 1);
	mol1.addBond(0, 2);
	mol1.addBond(0, 3);
	mol1.addBond(4, 0);

	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 4);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK(mol1.getAtom(0).getNumBonds() == 4);
	BOOST_CHECK(mol1.getAtom(1).getNumBonds() == 1);
	BOOST_CHECK(mol1.getAtom(2).getNumBonds() == 1);
	BOOST_CHECK(mol1.getAtom(3).getNumBonds() == 1);
	BOOST_CHECK(mol1.getAtom(4).getNumBonds() == 1);

//-----	

	mol1.removeBond(3);
	mol1.removeBond(0);
	mol1.removeBond(1);
	mol1.removeBond(0);

	BOOST_CHECK(mol1.getAtom(0).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(1).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(2).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(3).getNumBonds() == 0);
	BOOST_CHECK(mol1.getAtom(4).getNumBonds() == 0);

	BOOST_CHECK(mol1.getNumAtoms() == 5);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);

//-----	

	mol1.clear();

	BOOST_CHECK(mol1.getNumAtoms() == 0);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();

	mol1.addBond(0, 1);

	BOOST_CHECK(&mol1.addBond(0, 1) == &mol1.getBond(0));

	mol1.addBond(1, 2);
	mol1.addBond(2, 3);

	BOOST_CHECK(mol1.getNumAtoms() == 4);
	BOOST_CHECK(mol1.getNumBonds() == 3);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK(mol1.getAtomsEnd() - mol1.getAtomsBegin() == 4);
	BOOST_CHECK(mol1.getBondsEnd() - mol1.getBondsBegin() == 3);


	b_it = mol1.removeBond(mol1.getBondsBegin());

	BOOST_CHECK(b_it == mol1.getBondsBegin());

	b_it = mol1.removeBond(mol1.getBondsBegin() + 1);

	BOOST_CHECK(b_it == mol1.getBondsBegin() + 1);

	b_it = mol1.removeBond(--mol1.getBondsEnd());

	BOOST_CHECK(b_it == mol1.getBondsEnd());


	BOOST_CHECK(mol1.getNumAtoms() == 4);
	BOOST_CHECK(mol1.getNumBonds() == 0);

	checkAtomIndices(mol1);


	a_it = mol1.removeAtom(mol1.getAtomsBegin());

	BOOST_CHECK(a_it == mol1.getAtomsBegin());

	a_it = mol1.removeAtom(mol1.getAtomsBegin() + 1);

	BOOST_CHECK(a_it == mol1.getAtomsBegin() + 1);

	a_it = mol1.removeAtom(--mol1.getAtomsEnd());

	BOOST_CHECK(a_it == mol1.getAtomsEnd());

	a_it = mol1.removeAtom(mol1.getAtomsBegin());

	BOOST_CHECK(a_it == mol1.getAtomsEnd());

	BOOST_CHECK(mol1.getNumAtoms() == 0);
	BOOST_CHECK(mol1.getNumBonds() == 0);

//-----	

	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();

	mol1.addBond(0, 1);
	mol1.addBond(1, 2);
	mol1.addBond(2, 3);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK(mol1.getNumAtoms() == 4);
	BOOST_CHECK(mol1.getNumBonds() == 3);

	BOOST_CHECK(&(frag = mol1) == &frag);

	checkAtomIndices(mol1);
	checkBondIndices(mol1);

	BOOST_CHECK(frag.getNumAtoms() == 4);
	BOOST_CHECK(frag.getNumBonds() == 3);
	
	BOOST_CHECK(&(mol2 = mol1) == &mol2);

	checkAtomIndices(mol2);
	checkBondIndices(mol2);

	BOOST_CHECK(mol2.getNumAtoms() == 4);
	BOOST_CHECK(mol2.getNumBonds() == 3);

	BOOST_CHECK(&(frag += mol2) == &frag);

	BOOST_CHECK(frag.getNumAtoms() == 8);
	BOOST_CHECK(frag.getNumBonds() == 6);

	BOOST_CHECK(&frag.getAtom(0).getMolecule() == &mol1);
	BOOST_CHECK(&frag.getAtom(4).getMolecule() == &mol2);
	BOOST_CHECK(&frag.getBond(0).getMolecule() == &mol1);
	BOOST_CHECK(&frag.getBond(3).getMolecule() == &mol2);

	BOOST_CHECK(&(mol3 = frag) == &mol3);

	checkAtomIndices(mol3);
	checkBondIndices(mol3);

	BOOST_CHECK(mol3.getNumAtoms() == 8);
	BOOST_CHECK(mol3.getNumBonds() == 6);

	BasicMolecule mol14(frag);

	checkAtomIndices(mol14);
	checkBondIndices(mol14);

	BOOST_CHECK(mol14.getNumAtoms() == 8);
	BOOST_CHECK(mol14.getNumBonds() == 6);
	BOOST_CHECK_THROW(mol14.getProperty<std::string>(prop_key1), ItemNotFound);

	mol14 += frag;

	checkAtomIndices(mol14);
	checkBondIndices(mol14);

	BOOST_CHECK(mol14.getNumAtoms() == 16);
	BOOST_CHECK(mol14.getNumBonds() == 12);
	BOOST_CHECK_THROW(mol14.getProperty<std::string>(prop_key1), ItemNotFound);
}
