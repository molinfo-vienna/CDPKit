/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PointArray2DTest.cpp 
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

#include "CDPL/Vis/PointArray2D.hpp"


BOOST_AUTO_TEST_CASE(PointArray2DTest)
{
	using namespace CDPL;
	using namespace Vis;

	Math::Vector2D test_points[10] = {
		 Math::vec(0.1, -0.2),
		 Math::vec(10.1, 0.0),
		 Math::vec(-3.1, -13.4),
		 Math::vec(4.1,  10.0),
		 Math::vec(0.0,  12.2),
		 Math::vec(4.1,  10.0),
		 Math::vec(10.1, 0.0),
		 Math::vec(-3.1, -13.4),
		 Math::vec(0.1, -0.2),
		 Math::vec(0.0,  12.2)
	};

	PointArray2D pa;

//-----

	pa.insertElements(pa.getElementsBegin(), &test_points[0], &test_points[0] + 10);

	BOOST_CHECK(pa.getSize() == 10);	

	Math::Vector2D t = Math::vec(-2.0, 3.36);

	pa.translate(t);

	std::size_t i = 0;

	for (PointArray2D::ConstElementIterator it = pa.getElementsBegin(), end = pa.getElementsEnd(); it != end; ++it, i++) {

		BOOST_CHECK_CLOSE(test_points[i](0) - 2.0, (*it)(0), 0.00001);
		BOOST_CHECK_CLOSE(test_points[i](1) + 3.36, (*it)(1), 0.00001);
	}
}

