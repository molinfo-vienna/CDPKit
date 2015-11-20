/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomVdwRadiusTest.cpp 
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
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomTypeDB.hpp"
#include "CDPL/Chem/AtomTypes.hpp"


BOOST_AUTO_TEST_CASE(AtomVdwRadiusTest)
{
	using namespace CDPL;
	using namespace Chem;
   
	Molecule mol;
	Atom& atom = mol.addAtom();

	BOOST_CHECK(atom.getProperty(AtomProperty::VDW_RADIUS, false, false).isEmpty());

	BOOST_CHECK_SMALL(atom.getProperty<double>(AtomProperty::VDW_RADIUS), 0.0000001);

	BOOST_CHECK(!atom.getProperty(AtomProperty::VDW_RADIUS, false, false).isEmpty());

//-----

	for (unsigned int atom_type = 0; atom_type < AtomType::MAX_TYPE + 10; atom_type++) {
		atom.setProperty(AtomProperty::TYPE, atom_type);

		BOOST_CHECK(atom.getProperty(AtomProperty::VDW_RADIUS, false, false).isEmpty());

		BOOST_CHECK_CLOSE(atom.getProperty<double>(AtomProperty::VDW_RADIUS), AtomTypeDB::getVdWRadius(atom_type), 0.0001);

		BOOST_CHECK(!atom.getProperty(AtomProperty::VDW_RADIUS, false, false).isEmpty());
	}
}

