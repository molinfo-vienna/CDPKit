/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BrushTest.cpp 
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

#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Color.hpp"


BOOST_AUTO_TEST_CASE(BrushTest)
{
	using namespace CDPL;
	using namespace Vis;

	Brush b1;

	BOOST_CHECK(b1.getStyle() == Brush::NO_PATTERN);
	BOOST_CHECK(b1.getColor() == Color::BLACK);

	Brush b2(Brush::CROSS_PATTERN);

	BOOST_CHECK(b2.getStyle() == Brush::CROSS_PATTERN);
	BOOST_CHECK(b2.getColor() == Color::BLACK);

	Brush b3(Color::RED);

	BOOST_CHECK(b3.getStyle() == Brush::SOLID_PATTERN);
	BOOST_CHECK(b3.getColor() == Color::RED);

	Brush b4(Color::GREEN, Brush::H_PATTERN);

	BOOST_CHECK(b4.getStyle() == Brush::H_PATTERN);
	BOOST_CHECK(b4.getColor() == Color::GREEN);

//-----

	BOOST_CHECK(b1 != b4);
	BOOST_CHECK(!(b1 == b4));

	b1.setStyle(Brush::H_PATTERN);

	BOOST_CHECK(b1.getStyle() == Brush::H_PATTERN);
	BOOST_CHECK(b1.getColor() == Color::BLACK);

	BOOST_CHECK(b1 != b4);
	BOOST_CHECK(!(b1 == b4));

	b1.setColor(Color::GREEN);

	BOOST_CHECK(b1.getStyle() == Brush::H_PATTERN);
	BOOST_CHECK(b1.getColor() == Color::GREEN);

	BOOST_CHECK(b1 == b4);
	BOOST_CHECK(!(b1 != b4));

//-----

	BOOST_CHECK(b2 == b2);
	BOOST_CHECK(!(b2 != b2));

	b1 = b2;

	BOOST_CHECK(b1 != b4);
	BOOST_CHECK(!(b1 == b4));

	BOOST_CHECK(b1 == b2);
	BOOST_CHECK(!(b1 != b2));

	BOOST_CHECK(b2 != b4);
	BOOST_CHECK(!(b2 == b4));
}

