/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeHydrogenManipulationFunctionsTest.cpp 
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

#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


namespace
{

	void checkExplicitHCount(const CDPL::Chem::Molecule& mol, std::size_t exp_h_count, std::size_t exp_non_h_count)
	{
		using namespace CDPL;
		using namespace Chem;

		std::size_t h_count = 0;

		for (Molecule::ConstAtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) 
			if (getType(*it) == AtomType::H)
				h_count++;

		BOOST_CHECK(h_count == exp_h_count);
		BOOST_CHECK(mol.getNumAtoms() - h_count == exp_non_h_count);

		for (Molecule::ConstBondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) 
			if (getType(it->getBegin()) == AtomType::H || getType(it->getEnd()) == AtomType::H)
				BOOST_CHECK(getOrder(*it) == 1);
	}
}


BOOST_AUTO_TEST_CASE(MoleculeMakeHydrogenCompleteAndDepleteFunctionTest)
{
	using namespace CDPL;
	using namespace Chem;

	BasicMolecule mol;

	Atom& atom1 = mol.addAtom();
	Atom& atom2 = mol.addAtom();

	setType(atom1, AtomType::C);
	setType(atom2, AtomType::H);

	Atom& atom3 = mol.addAtom();
	atom3.copyProperties(atom1);

	mol.addAtom().copyProperties(atom2);

	setOrder(mol.addBond(0, 1), 1);

	Bond& bond1 = mol.addBond(0, 2);

	setOrder(bond1, 1);

	checkExplicitHCount(mol, 2, 2);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 8, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 6, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	Bond& bond2 = mol.addBond(0, 1);

	setOrder(bond2, 1);

	checkExplicitHCount(mol, 0, 2);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 6, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	setOrder(bond2, 2);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 4, 2);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 2);

	mol.clear();

	checkExplicitHCount(mol, 0, 0);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	checkExplicitHCount(mol, 0, 0);

	makeHydrogenDeplete(mol);

	checkExplicitHCount(mol, 0, 0);
}

BOOST_AUTO_TEST_CASE(MoleculeMakeOrdinaryHydrogenDepleteFunctionTest)
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

	checkExplicitHCount(mol, 2, 2);

	calcImplicitHydrogenCounts(mol, true);
	makeHydrogenComplete(mol);

	BOOST_CHECK(mol.getNumBonds() == 8);
	BOOST_CHECK(mol.getNumAtoms() == 10);

 	makeOrdinaryHydrogenDeplete(mol, 0);

 	BOOST_CHECK(mol.getNumBonds() == 1);
 	BOOST_CHECK(mol.getNumAtoms() == 3);

	checkExplicitHCount(mol, 1, 2);

	Atom& atom3 = mol.addAtom();

	setType(atom3, AtomType::H);
	setIsotope(atom3, 2);

	setOrder(mol.addBond(0, mol.getAtomIndex(atom3)), 1);

	BOOST_CHECK(mol.getNumBonds() == 2);
	BOOST_CHECK(mol.getNumAtoms() == 4);

	checkExplicitHCount(mol, 2, 2);

	calcImplicitHydrogenCounts(mol, true);
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
}
