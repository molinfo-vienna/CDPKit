/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorFunctionsTest.cpp 
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


#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Math/Vector.hpp"


BOOST_AUTO_TEST_CASE(VectorFunctionsTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 3> v1;

	v1(0) = 1.0;
	v1(1) = 0.0;
	v1(2) = 0.0;

	Vector<float> v2(3);

	v2(0) = 0.0f;
	v2(1) = 1.0f;
	v2(2) = 0.0f;

	CVector<double, 3> res;

	cross_prod(v1, v2, res);

	BOOST_CHECK_SMALL(res(0), 0.00001);
	BOOST_CHECK_SMALL(res(1), 0.00001);
	BOOST_CHECK_CLOSE(res(2), 1.0, 0.00001);

	res = cross_prod(v2, v1);

	BOOST_CHECK_SMALL(res(0), 0.00001);
	BOOST_CHECK_SMALL(res(1), 0.00001);
	BOOST_CHECK_CLOSE(res(2), -1.0, 0.00001);

	v2(1) = 0.0f;

	cross_prod(v2, v1, res);

	BOOST_CHECK_SMALL(res(0), 0.00001);
	BOOST_CHECK_SMALL(res(1), 0.00001);
	BOOST_CHECK_SMALL(res(2), 0.00001);
	
	v1(0) = -2.0;
	v1(1) = 3.0;
	v1(2) = 4.0;

	normalize(v1, res);

	BOOST_CHECK_CLOSE(res(0), -2.0 / std::sqrt(29), 0.00001);
	BOOST_CHECK_CLOSE(res(1), 3.0 / std::sqrt(29), 0.00001);
	BOOST_CHECK_CLOSE(res(2), 4.0 / std::sqrt(29), 0.00001);

	v1(0) = 0.0;
	v1(1) = 4.0;
	v1(2) = 9.0;

	res = normalize(v1, res);

	BOOST_CHECK_SMALL(res(0), 0.00001);
	BOOST_CHECK_CLOSE(res(1), 4.0 / std::sqrt(97), 0.00001);
	BOOST_CHECK_CLOSE(res(2), 9.0 / std::sqrt(97), 0.00001);

//-----

	BOOST_CHECK(DVector() == DVector());
	BOOST_CHECK(!(DVector() != DVector()));

	v2(0) = 0.0f;
	v2(1) = 4.0f;
	v2(2) = 9.0f;

	BOOST_CHECK(v1 == v2);
	BOOST_CHECK(!(v1 != v2));

	v2.resize(4);

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK(v1 != v2);

	v2.resize(3);

	BOOST_CHECK(v1 == v2);
	BOOST_CHECK(!(v1 != v2));

	v2(0) = 1.0f;

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK(v1 != v2);

	BOOST_CHECK(v1 == v1);
	BOOST_CHECK(!(v1 != v1));
}

