/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixFunctionsTest.cpp 
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

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/AffineTransform.hpp"


BOOST_AUTO_TEST_CASE(MatrixFunctionsTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(AffineTransform4D() == AffineTransform4D());
	BOOST_CHECK(!(AffineTransform4D() != AffineTransform4D()));

	BOOST_CHECK(AffineTransform4D() == IdentityMatrix<double>(4));
	BOOST_CHECK(!(AffineTransform4D() != IdentityMatrix<double>(4)));

	BOOST_CHECK(AffineTransform4D() != AffineTransform3D());
	BOOST_CHECK(!(AffineTransform4D() == AffineTransform3D()));

	BOOST_CHECK(ZeroMatrix<double>(4, 4) == ZeroMatrix<double>(4, 4));
	BOOST_CHECK(ZeroMatrix<double>(4, 3) == ZeroMatrix<double>(4, 3));
	BOOST_CHECK(ZeroMatrix<double>(3, 4) == ZeroMatrix<double>(3, 4));

	BOOST_CHECK(ZeroMatrix<double>(3, 4) != ZeroMatrix<double>(4, 4));
	BOOST_CHECK(ZeroMatrix<double>(4, 3) != ZeroMatrix<double>(4, 4));

	BOOST_CHECK(ZeroMatrix<double>(5, 4) != ZeroMatrix<double>(4, 4));
	BOOST_CHECK(ZeroMatrix<double>(4, 5) != ZeroMatrix<double>(4, 4));

	BOOST_CHECK(ZeroMatrix<double>(5, 3) != ZeroMatrix<double>(4, 4));
	BOOST_CHECK(ZeroMatrix<double>(3, 5) != ZeroMatrix<double>(4, 4));

//-----

	BOOST_CHECK(DMatrix() == DMatrix());
	BOOST_CHECK(!(DMatrix() != DMatrix()));

//-----

	DMatrix m1 = ZeroMatrix<double>(3, 4);
	DMatrix m2 = ZeroMatrix<double>(3, 4);

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(0, 0) = 2.2;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(0, 0) = 2.2;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(0, 2) = 0.2;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(0, 2) = 0.2;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(0, 1) = 3.3;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(0, 1) = 3.3;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(0, 3) = 5.0;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(0, 3) = 5.0;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(2, 0) = -0.2;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(2, 0) = -0.2;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(1, 0) = 0.29;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(1, 0) = 0.29;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));

	m1(2, 2) = -5.29;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(2, 2) = 5.29;

	BOOST_CHECK(m1 != m2);
	BOOST_CHECK(!(m1 == m2));

	m2(2, 2) = -5.29;

	BOOST_CHECK(m1 == m2);
	BOOST_CHECK(!(m1 != m2));
}

