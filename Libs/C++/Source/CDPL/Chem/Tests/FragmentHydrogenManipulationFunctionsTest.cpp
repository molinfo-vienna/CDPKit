/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentHydrogenManipulationFunctionsTest.cpp 
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

#include "CDPL/Chem/FragmentFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


namespace
{

	void checkExplicitHCount(const CDPL::Chem::Fragment& frag, std::size_t exp_h_count, std::size_t exp_non_h_count)
	{
		using namespace CDPL;
		using namespace Chem;

		std::size_t h_count = 0;

		for (Fragment::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) 
			if (getType(*it) == AtomType::H)
				h_count++;

		BOOST_CHECK(h_count == exp_h_count);
		BOOST_CHECK(frag.getNumAtoms() - h_count == exp_non_h_count);

		for (Fragment::ConstBondIterator it = frag.getBondsBegin(), end = frag.getBondsEnd(); it != end; ++it) 
			if (getType(it->getBegin()) == AtomType::H || getType(it->getEnd()) == AtomType::H)
				BOOST_CHECK(getOrder(*it) == 1);
	}
}


BOOST_AUTO_TEST_CASE(FragmentMakeHydrogenDepleteFunctionTest)
{
	using namespace CDPL;
	using namespace Chem;

	BasicMolecule mol;

	Atom& atom1 = mol.addAtom();
	Atom& atom2 = mol.addAtom();

	setType(atom1, AtomType::C);
	setType(atom2, AtomType::H);

	mol.addAtom().copyProperties(atom1);
	mol.addAtom().copyProperties(atom2);

	setOrder(mol.addBond(0, 1), 1);
	setOrder(mol.addBond(0, 2), 1);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 8);
	BOOST_CHECK(mol.getNumAtoms() == 10);

	Fragment frag1(mol);

	BOOST_CHECK(frag1.getNumBonds() == 8);
	BOOST_CHECK(frag1.getNumAtoms() == 10);

	checkExplicitHCount(frag1, 8, 2);

	makeHydrogenDeplete(frag1);

	checkExplicitHCount(frag1, 0, 2);

	BOOST_CHECK(frag1.getNumBonds() == 1);
	BOOST_CHECK(frag1.getNumAtoms() == 2);
}

BOOST_AUTO_TEST_CASE(FragmentMakeOrdinaryHydrogenDepleteFunctionTest)
{
	using namespace CDPL;
	using namespace Chem;

	BasicMolecule mol;

	Atom& atom1 = mol.addAtom();
	Atom& atom2 = mol.addAtom();

	setType(atom1, AtomType::C);
	setType(atom2, AtomType::H);

	mol.addAtom().copyProperties(atom1);
	mol.addAtom().copyProperties(atom2);

	setOrder(mol.addBond(0, 1), 1);
	setOrder(mol.addBond(0, 2), 1);

	Atom& atom3 = mol.addAtom();

	setType(atom3, AtomType::H);
	setIsotope(atom2, 2);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 9);
	BOOST_CHECK(mol.getNumAtoms() == 12);

	Fragment frag1(mol);

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
}
