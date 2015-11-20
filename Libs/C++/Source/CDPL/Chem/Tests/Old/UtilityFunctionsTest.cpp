/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctionsTest.cpp 
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

#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomTypes.hpp"
#include "CDPL/Chem/AtomPropertyFlags.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"


namespace
{

	void checkExplicitHCount(const CDPL::Chem::MolecularGraph& molgraph, std::size_t exp_h_count, std::size_t exp_non_h_count)
	{
		using namespace CDPL;
		using namespace Chem;

		std::size_t h_count = 0;

		for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) 
			if (it->getProperty<unsigned int>(AtomProperty::TYPE) == AtomType::H)
				h_count++;

		BOOST_CHECK(h_count == exp_h_count);
		BOOST_CHECK(molgraph.getNumAtoms() - h_count == exp_non_h_count);

		for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) 
			if (it->getBegin().getProperty<unsigned int>(AtomProperty::TYPE) == AtomType::H 
				|| it->getEnd().getProperty<unsigned int>(AtomProperty::TYPE) == AtomType::H)
				BOOST_CHECK(it->getProperty<std::size_t>(BondProperty::ORDER) == 1);
	}
}


BOOST_AUTO_TEST_CASE(UtilityFunctionsTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Util;

	Molecule mol;

	Atom* atom1 = &mol.addAtom();
	Atom* atom2 = &mol.addAtom();

	atom1->setProperty(AtomProperty::SYMBOL, std::string("C"));
	atom2->setProperty(AtomProperty::TYPE, AtomType::H);

	Atom* atom3 = &mol.addAtom(*atom1);

	mol.addAtom(*atom2);

	mol.addBond(0, 1).setProperty(BondProperty::ORDER, std::size_t(1));

	Bond* bond1 = &mol.addBond(0, 2);

	bond1->setProperty(BondProperty::ORDER, std::size_t(1));

	checkExplicitHCount(mol, 2, 2);

	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 8, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 6, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	Bond* bond2 = &mol.addBond(0, 1);

	bond2->setProperty(BondProperty::ORDER, std::size_t(1));

	checkExplicitHCount(mol, 0, 2);

	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 6, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	bond2->setProperty(BondProperty::ORDER, std::size_t(2));

	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 4, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	mol.clear();

	checkExplicitHCount(mol, 0, 0);

	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 0, 0);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 0);

//##########

	mol.clear();

	atom1 = &mol.addAtom();
	atom2 = &mol.addAtom();

	atom1->setProperty(AtomProperty::SYMBOL, std::string("C"));
	atom2->setProperty(AtomProperty::TYPE, AtomType::H);

	mol.addAtom(*atom1);
	mol.addAtom(*atom2);

	mol.addBond(0, 1).setProperty(BondProperty::ORDER, std::size_t(1));
	mol.addBond(0, 2).setProperty(BondProperty::ORDER, std::size_t(1));

	checkExplicitHCount(mol, 2, 2);

	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 8);
	BOOST_CHECK(mol.getNumAtoms() == 10);

	checkExplicitHCount(mol, 8, 2);

	Fragment frag1(mol);

	BOOST_CHECK(frag1.getNumBonds() == 8);
	BOOST_CHECK(frag1.getNumAtoms() == 10);

	checkExplicitHCount(frag1, 8, 2);

	makeHydrogenDeplete(frag1);

	checkExplicitHCount(frag1, 0, 2);

	BOOST_CHECK(frag1.getNumBonds() == 1);
	BOOST_CHECK(frag1.getNumAtoms() == 2);

//##########

	mol.clear();

	atom1 = &mol.addAtom();
	atom2 = &mol.addAtom();

	atom1->setProperty(AtomProperty::SYMBOL, std::string("C"));
	atom2->setProperty(AtomProperty::TYPE, AtomType::H);

	mol.addAtom(*atom1);
	mol.addAtom(*atom2);

	mol.addBond(0, 1).setProperty(BondProperty::ORDER, std::size_t(1));
	mol.addBond(0, 2).setProperty(BondProperty::ORDER, std::size_t(1));

	checkExplicitHCount(mol, 2, 2);

	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 8);
	BOOST_CHECK(mol.getNumAtoms() == 10);

 	makeOrdinaryHydrogenDeplete(mol, 0);

 	BOOST_CHECK(mol.getNumBonds() == 1);
 	BOOST_CHECK(mol.getNumAtoms() == 3);

	checkExplicitHCount(mol, 1, 2);

	atom3 = &mol.addAtom();

	atom3->setProperty(AtomProperty::TYPE, AtomType::H);
	atom3->setProperty(AtomProperty::ISOTOPE, std::size_t(2));

	mol.addBond(0, mol.getAtomIndex(*atom3)).setProperty(BondProperty::ORDER, std::size_t(1));

	BOOST_CHECK(mol.getNumBonds() == 2);
	BOOST_CHECK(mol.getNumAtoms() == 4);

	checkExplicitHCount(mol, 2, 2);

	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 8);
	BOOST_CHECK(mol.getNumAtoms() == 10);

	makeOrdinaryHydrogenDeplete(mol, AtomPropertyFlag::ISOTOPE);

	BOOST_CHECK(mol.getNumBonds() == 2);
	BOOST_CHECK(mol.getNumAtoms() == 4);

	checkExplicitHCount(mol, 2, 2);

	makeOrdinaryHydrogenDeplete(mol, 0);

	BOOST_CHECK(mol.getNumBonds() == 1);
	BOOST_CHECK(mol.getNumAtoms() == 3);

	checkExplicitHCount(mol, 1, 2);

//##########

	mol.clear();

	atom1 = &mol.addAtom();
	atom2 = &mol.addAtom();

	atom1->setProperty(AtomProperty::SYMBOL, std::string("C"));
	atom2->setProperty(AtomProperty::TYPE, AtomType::H);

	mol.addAtom(*atom1);
	mol.addAtom(*atom2);

	mol.addBond(0, 1).setProperty(BondProperty::ORDER, std::size_t(1));
	mol.addBond(0, 2).setProperty(BondProperty::ORDER, std::size_t(1));

	atom3 = &mol.addAtom();

	atom3->setProperty(AtomProperty::TYPE, AtomType::H);
	atom2->setProperty(AtomProperty::ISOTOPE, std::size_t(2));

	checkExplicitHCount(mol, 3, 2);

	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 9);
	BOOST_CHECK(mol.getNumAtoms() == 12);

	checkExplicitHCount(mol, 10, 2);

	frag1 = mol;

	BOOST_CHECK(frag1.getNumBonds() == 9);
	BOOST_CHECK(frag1.getNumAtoms() == 12);

	checkExplicitHCount(frag1, 10, 2);

	makeOrdinaryHydrogenDeplete(frag1, 0);

 	BOOST_CHECK(frag1.getNumBonds() == 1);
 	BOOST_CHECK(frag1.getNumAtoms() == 4);

	checkExplicitHCount(frag1, 2, 2);

	frag1 = mol;

	BOOST_CHECK(frag1.getNumBonds() == 9);
	BOOST_CHECK(frag1.getNumAtoms() == 12);

	checkExplicitHCount(frag1, 10, 2);

	makeOrdinaryHydrogenDeplete(frag1, AtomPropertyFlag::ISOTOPE);

 	BOOST_CHECK(frag1.getNumBonds() == 2);
 	BOOST_CHECK(frag1.getNumAtoms() == 5);

	checkExplicitHCount(frag1, 3, 2);

	frag1 = mol;

	BOOST_CHECK(frag1.getNumBonds() == 9);
	BOOST_CHECK(frag1.getNumAtoms() == 12);

	checkExplicitHCount(frag1, 10, 2);

	while (frag1.getNumBonds() > 0)
		frag1.removeBond(0);

	BOOST_CHECK(frag1.getNumBonds() == 0);
 	BOOST_CHECK(frag1.getNumAtoms() == 12);

	makeOrdinaryHydrogenDeplete(frag1, 0);

 	BOOST_CHECK(frag1.getNumBonds() == 0);
 	BOOST_CHECK(frag1.getNumAtoms() == 12);

	checkExplicitHCount(frag1, 10, 2);

//##########

	BitSet bs1(std::string("101010101010101010101010"));
	std::string bs_string;

	foldBitSet(bs1, 0);
	to_string(bs1, bs_string);
	BOOST_CHECK(bs_string == "101010101010101010101010");

	foldBitSet(bs1, 1);
	to_string(bs1, bs_string);
	BOOST_CHECK(bs_string == "101010101010");

	foldBitSet(bs1, 1);
	to_string(bs1, bs_string);
	BOOST_CHECK(bs_string == "101010");

	BitSet bs2(std::string("101010101010010101010101"));

	foldBitSet(bs2, 0);
	to_string(bs2, bs_string);
	BOOST_CHECK(bs_string == "101010101010010101010101");

	foldBitSet(bs2, 1);
	to_string(bs2, bs_string);
	BOOST_CHECK(bs_string == "111111111111");

	foldBitSet(bs2, 1);
	to_string(bs2, bs_string);
	BOOST_CHECK(bs_string == "111111");

	BitSet bs3(std::string("010101010101010101010"));

	foldBitSet(bs3, 0);
	to_string(bs3, bs_string);
	BOOST_CHECK(bs_string == "010101010101010101010");

	foldBitSet(bs3, 1);
	to_string(bs3, bs_string);
	BOOST_CHECK(bs_string == "1010101010");

	foldBitSet(bs3, 1);
	to_string(bs3, bs_string);
	BOOST_CHECK(bs_string == "11111");

	BitSet bs4(std::string("111111111100000000000000"));	

	foldBitSet(bs4, 2);
	to_string(bs4, bs_string);
	BOOST_CHECK(bs_string == "111111");

	foldBitSet(bs4, 0);
	to_string(bs4, bs_string);
	BOOST_CHECK(bs_string == "111111");

	foldBitSet(bs4, 1);
	to_string(bs4, bs_string);
	BOOST_CHECK(bs_string == "111");

	foldBitSet(bs4, 1);
	to_string(bs4, bs_string);
	BOOST_CHECK(bs_string == "1");

	foldBitSet(bs4, 1);
	to_string(bs4, bs_string);
	BOOST_CHECK(bs_string == "");

	BitSet bs5;	

	foldBitSet(bs5, 0);
	to_string(bs5, bs_string);
	BOOST_CHECK(bs_string == "");

	foldBitSet(bs5, 1);
	to_string(bs5, bs_string);
	BOOST_CHECK(bs_string == "");

	foldBitSet(bs5, 50);
	to_string(bs5, bs_string);
	BOOST_CHECK(bs_string == "");

	BitSet bs6(std::string("000000000000000000000000"));

	foldBitSet(bs6, 0);
	to_string(bs6, bs_string);
	BOOST_CHECK(bs_string == "000000000000000000000000");

	foldBitSet(bs6, 1);
	to_string(bs6, bs_string);
	BOOST_CHECK(bs_string == "000000000000");

	foldBitSet(bs6, 2);
	to_string(bs6, bs_string);
	BOOST_CHECK(bs_string == "000");
}
