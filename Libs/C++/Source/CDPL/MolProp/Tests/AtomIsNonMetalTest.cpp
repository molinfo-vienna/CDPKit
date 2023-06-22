/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomIsNonMetalTest.cpp 
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

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


BOOST_AUTO_TEST_CASE(AtomIsNonMetalFunctionTest)
{
	using namespace CDPL;
	using namespace MolProp;
	using namespace Chem;
   
	BasicMolecule mol;
	Atom& atom = mol.addAtom();

	for (unsigned int atom_type = 0; atom_type < AtomType::MAX_TYPE + 10; atom_type++) {
		setType(atom, atom_type);

		BOOST_CHECK(isNonMetal(atom) == AtomDictionary::isNonMetal(atom_type));
	}
}
