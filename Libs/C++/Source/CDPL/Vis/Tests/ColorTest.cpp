/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ColorTest.cpp 
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

#include "CDPL/Vis/Color.hpp"


BOOST_AUTO_TEST_CASE(ColorTest)
{
	using namespace CDPL;
	using namespace Vis;

	Color c1;

	BOOST_CHECK(c1.getRed() == 0.0);
	BOOST_CHECK(c1.getGreen() == 0.0);
	BOOST_CHECK(c1.getBlue() == 0.0);
	BOOST_CHECK(c1.getAlpha() == 0.0);

	Color c2(-3.0, 2.0, -0.7, 4.0);

	BOOST_CHECK(c2.getRed() == 0.0);
	BOOST_CHECK(c2.getGreen() == 1.0);
	BOOST_CHECK(c2.getBlue() == 0.0);
	BOOST_CHECK(c2.getAlpha() == 1.0);

	Color c3(2.0, -1.4, 2.0, -1.1);

	BOOST_CHECK(c3.getRed() == 1.0);
	BOOST_CHECK(c3.getGreen() == 0.0);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	Color c4(0.3, 0.4, 1.0, 0.1);

	BOOST_CHECK(c4.getRed() == 0.3);
	BOOST_CHECK(c4.getGreen() == 0.4);
	BOOST_CHECK(c4.getBlue() == 1.0);
	BOOST_CHECK(c4.getAlpha() == 0.1);

	Color c5(0.3, 0.4, 0.9);

	BOOST_CHECK(c5.getRed() == 0.3);
	BOOST_CHECK(c5.getGreen() == 0.4);
	BOOST_CHECK(c5.getBlue() == 0.9);
	BOOST_CHECK(c5.getAlpha() == 1.0);

//-----

	c3.setRed(2.0);

	BOOST_CHECK(c3.getRed() == 1.0);
	BOOST_CHECK(c3.getGreen() == 0.0);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setRed(-1.3);

	BOOST_CHECK(c3.getRed() == 0.0);
	BOOST_CHECK(c3.getGreen() == 0.0);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setRed(0.31);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.0);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

//-----

	c3.setGreen(2.0);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 1.0);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setGreen(-1.3);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.0);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setGreen(0.5);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

//-----

	c3.setBlue(2.0);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 1.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setBlue(-1.3);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 0.0);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setBlue(0.6);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 0.6);
	BOOST_CHECK(c3.getAlpha() == 0.0);

//-----

	c3.setAlpha(2.0);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 0.6);
	BOOST_CHECK(c3.getAlpha() == 1.0);

	c3.setAlpha(-1.3);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 0.6);
	BOOST_CHECK(c3.getAlpha() == 0.0);

	c3.setAlpha(0.7);

	BOOST_CHECK(c3.getRed() == 0.31);
	BOOST_CHECK(c3.getGreen() == 0.5);
	BOOST_CHECK(c3.getBlue() == 0.6);
	BOOST_CHECK(c3.getAlpha() == 0.7);

//-----

	Color c6;

	c6.setRGBA(-3.0, 2.0, -0.7, 4.0);

	BOOST_CHECK(c6.getRed() == 0.0);
	BOOST_CHECK(c6.getGreen() == 1.0);
	BOOST_CHECK(c6.getBlue() == 0.0);
	BOOST_CHECK(c6.getAlpha() == 1.0);

	c6.setRGBA(2.0, -1.4, 2.0, -1.1);

	BOOST_CHECK(c6.getRed() == 1.0);
	BOOST_CHECK(c6.getGreen() == 0.0);
	BOOST_CHECK(c6.getBlue() == 1.0);
	BOOST_CHECK(c6.getAlpha() == 0.0);

	c6.setRGBA(0.3, 0.4, 1.0, 0.1);

	BOOST_CHECK(c6.getRed() == 0.3);
	BOOST_CHECK(c6.getGreen() == 0.4);
	BOOST_CHECK(c6.getBlue() == 1.0);
	BOOST_CHECK(c6.getAlpha() == 0.1);

	c6.setRGBA(0.32, 0.42, 1.2);

	BOOST_CHECK(c6.getRed() == 0.32);
	BOOST_CHECK(c6.getGreen() == 0.42);
	BOOST_CHECK(c6.getBlue() == 1.0);
	BOOST_CHECK(c6.getAlpha() == 1.0);

//----

	BOOST_CHECK(c3 != c5); 
	BOOST_CHECK(!(c3 == c5)); 

	c3.setRed(0.3);

	BOOST_CHECK(c3 != c5); 
	BOOST_CHECK(!(c3 == c5)); 

	c3.setGreen(0.4);
		
	BOOST_CHECK(c3 != c5); 
	BOOST_CHECK(!(c3 == c5)); 

	c3.setBlue(0.9);
		
	BOOST_CHECK(c3 != c5); 
	BOOST_CHECK(!(c3 == c5)); 

	c3.setAlpha(1.0);

	BOOST_CHECK(c3 == c5); 
	BOOST_CHECK(!(c3 != c5)); 

	BOOST_CHECK(c3 == c3);
	BOOST_CHECK(!(c3 != c3));

//----

	c3 = c1;

	BOOST_CHECK(c3 == c1);
	BOOST_CHECK(!(c3 != c1));

	BOOST_CHECK(c3 != c5);
	BOOST_CHECK(!(c3 == c5));

	BOOST_CHECK(c1 != c5);
	BOOST_CHECK(!(c1 == c5));
}

