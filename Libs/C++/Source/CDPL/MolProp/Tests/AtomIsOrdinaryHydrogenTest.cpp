/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * IsOrdinaryHydrogenTest.cpp 
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

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


BOOST_AUTO_TEST_CASE(AtomIsOrdinaryHydrogenFunctionTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace MolProp;

	BasicMolecule mol;

	Atom& atom1 = mol.addAtom();
	Atom& atom2 = mol.addAtom();
	Bond& bond = mol.addBond(0, 1);

	setOrder(bond, 1);
	calcImplicitHydrogenCounts(mol, false);
	
//------

	setType(atom1, AtomType::H);

	BOOST_CHECK(isOrdinaryHydrogen(atom1, mol));

	setIsotope(atom1, 1);

	BOOST_CHECK(!isOrdinaryHydrogen(atom1, mol, AtomPropertyFlag::ISOTOPE));

	setType(atom1, AtomType::X);

	BOOST_CHECK(!isOrdinaryHydrogen(atom1, mol));

	setType(atom1, AtomType::UNKNOWN);

	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));

	setType(atom2, AtomType::H);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));

	setType(atom2, AtomType::Cl);

	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));

	setType(atom2, AtomType::H);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));
	
	setFormalCharge(atom2, -1);

	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));
	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT));

	setFormalCharge(atom2, 1);

	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));
	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT));

	setFormalCharge(atom2, 0);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE));
	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT));

	//------

	setOrder(bond, 2);

	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT));

	setOrder(bond, 1);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT));

	set2DStereoFlag(bond, BondStereoFlag::UP);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT));
	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::CONFIGURATION));

	set2DStereoFlag(bond, BondStereoFlag::PLAIN);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::CONFIGURATION));

	set2DStereoFlag(bond, BondStereoFlag::PLAIN);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::CONFIGURATION));

	//------

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::ATOM_MAPPING_ID));

	setAtomMappingID(atom1, 0);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::ATOM_MAPPING_ID));

	setAtomMappingID(atom1, 1);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::ATOM_MAPPING_ID));

	setAtomMappingID(atom2, 0);

	BOOST_CHECK(isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::ATOM_MAPPING_ID));

	setAtomMappingID(atom2, 1);

	BOOST_CHECK(!isOrdinaryHydrogen(atom2, mol, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT | AtomPropertyFlag::ATOM_MAPPING_ID));
}
