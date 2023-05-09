/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomColorTableTest.cpp 
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

#include "CDPL/Vis/AtomColorTable.hpp"
#include "CDPL/Chem/AtomType.hpp"


BOOST_AUTO_TEST_CASE(AtomColorTableTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace AtomColorTable;

	BOOST_CHECK(ELEMENT_COLORS_2D.getSize() == 28);

	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::C ) == Vis::Color( 40.0 / 255.0,  40.0 / 255.0,  40.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::O ) == Vis::Color(240.0 / 255.0,   0.0        ,   0.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::H ) == Vis::Color(100.0 / 255.0, 100.0 / 255.0, 100.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::N ) == Vis::Color(143.0 / 255.0, 143.0 / 255.0, 255.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::S ) == Vis::Color(255.0 / 255.0, 200.0 / 255.0,  50.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Cl) == Vis::Color(  0.0        ,   1.0        ,   0.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::B ) == Vis::Color(  0.0        ,   1.0        ,   0.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::P ) == Vis::Color(255.0 / 255.0, 165.0 / 255.0,   0.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Fe) == Vis::Color(255.0 / 255.0, 165.0 / 255.0,   0.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Ba) == Vis::Color(255.0 / 255.0, 165.0 / 255.0,   0.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Na) == Vis::Color(  0.0        ,   0.0        ,   1.0        ));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Mg) == Vis::Color( 34.0 / 255.0, 139.0 / 255.0,  34.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Zn) == Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Cu) == Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Ni) == Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Br) == Vis::Color(165.0 / 255.0,  42.0 / 255.0,  42.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Ca) == Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Mn) == Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Al) == Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Ti) == Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Cr) == Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Ag) == Vis::Color(128.0 / 255.0, 128.0 / 255.0, 144.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::F ) == Vis::Color(218.0 / 255.0, 165.0 / 255.0,  32.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Si) == Vis::Color(218.0 / 255.0, 165.0 / 255.0,  32.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Au) == Vis::Color(218.0 / 255.0, 165.0 / 255.0,  32.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::I ) == Vis::Color(160.0 / 255.0,  32.0 / 255.0, 240.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::Li) == Vis::Color(178.0 / 255.0,  34.0 / 255.0,  34.0 / 255.0));
	BOOST_CHECK(ELEMENT_COLORS_2D.getValue(Chem::AtomType::He) == Vis::Color(255.0 / 255.0, 192.0 / 255.0, 203.0 / 255.0));
}
