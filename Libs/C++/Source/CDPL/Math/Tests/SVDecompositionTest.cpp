/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SVDecompositionTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
//#include "CDPL/Math/IO.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(SVDecomposeFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	typedef Matrix<double>::SizeType SizeType1;

	Matrix<double> a1(0, 0);
	Vector<double> w1(2, 0.0);
	Matrix<double> v1(2, 2, 0.0);

	BOOST_CHECK(svDecompose(a1, w1, v1));

	a1.resize(6, 0);

	BOOST_CHECK(svDecompose(a1, w1, v1));

	a1.resize(0, 6);

	BOOST_CHECK_THROW(svDecompose(a1, w1, v1), Base::SizeError);

	w1.resize(6);

	BOOST_CHECK_THROW(svDecompose(a1, w1, v1), Base::SizeError);

	v1.resize(1, 6);

	BOOST_CHECK_THROW(svDecompose(a1, w1, v1), Base::SizeError);

	v1.resize(6, 3);

	BOOST_CHECK_THROW(svDecompose(a1, w1, v1), Base::SizeError);

	v1.resize(6, 6);

	BOOST_CHECK(svDecompose(a1, w1, v1));

	// ---------

	a1.resize(6, 6, true, 0.0);

	BOOST_CHECK(svDecompose(a1, w1, v1));

	BOOST_CHECK(a1 == IdentityMatrix<double>(6, 6));
	BOOST_CHECK(w1 == ZeroVector<double>(6));
	BOOST_CHECK(v1 == IdentityMatrix<double>(6, 6));

	// ---------

	a1 = IdentityMatrix<double>(6, 6);

	BOOST_CHECK(svDecompose(a1, w1, v1));

	BOOST_CHECK(a1 == -IdentityMatrix<double>(6, 6));
	BOOST_CHECK(w1 == ScalarVector<double>(6, 1.0));
	BOOST_CHECK(v1 == -IdentityMatrix<double>(6, 6));

	// ---------

	a1.resize(20, 18, false);

	for (SizeType1 i = 0; i < a1.getSize1(); i++) 
		for (SizeType1 j = 0; j < a1.getSize2(); j++)
			a1(i, j) = i * a1.getSize2() + j - 20.20;

	a1(8, 8) = 0.0;
	a1(4, 1) = 0.0;
	a1(0, 7) = 0.0;
	a1(11, 11) = 1.0;

	w1.resize(18);
	v1.resize(18, 18, false);

	Matrix<double> u1(a1);

	BOOST_CHECK(svDecompose(u1, w1, v1, 4));
	
	BOOST_CHECK(equals(a1, u1 * diag(w1) * trans(v1), 10e-10));

	// ---------

	a1.resize(18, 18, false);

	for (SizeType1 i = 0; i < a1.getSize1(); i++) 
		for (SizeType1 j = 0; j < a1.getSize2(); j++)
			a1(i, j) = i * a1.getSize2() + j * 0.2;

	a1(5, 6) = 0.0;
	a1(1, 1) = 0.0;
	a1(17, 12) = 0.0;
	a1(8, 8) = 1.0;

	u1 = a1;

	BOOST_CHECK(svDecompose(u1, w1, v1, 5));
	
	BOOST_CHECK(equals(a1, u1 * diag(w1) * trans(v1), 10e-10));

	// ---------

	a1.resize(15, 18, false);

	for (SizeType1 i = 0; i < a1.getSize1(); i++) 
		for (SizeType1 j = 0; j < a1.getSize2(); j++)
			a1(i, j) = 1000.2 - i * a1.getSize2() + j * 0.2;

	a1(14, 17) = 0.0;
	a1(8, 5) = 0.0;
	a1(5, 5) = 0.0;
	a1(2, 2) = 1.0;

	u1 = a1;

	BOOST_CHECK(svDecompose(u1, w1, v1, 4));
	
	BOOST_CHECK(equals(a1, u1 * diag(w1) * trans(v1), 10e-10));
}

BOOST_AUTO_TEST_CASE(SVSubstituteFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	typedef Matrix<double>::SizeType SizeType1;
	typedef Vector<double>::SizeType SizeType2;

	Matrix<double> a1(100, 100);
	Vector<double> x1(a1.getSize2());

	for (SizeType1 i = 0; i < a1.getSize1(); i++) 
		for (SizeType1 j = 0; j < a1.getSize2(); j++)
			a1(i, j) = -1000.2 + i * a1.getSize2() - j * 20.1232;

	for (SizeType2 i = 0; i < x1.getSize(); i++) 
		x1(i) = 10 + i / -2.1232;

	Vector<double> b1(a1 * x1);	
	Matrix<double> u1(a1);
	Vector<double> w1(a1.getSize2(), 0.0);
	Matrix<double> v1(a1.getSize2(), a1.getSize2(), 0.0);

	Vector<double> x1_sol(x1.getSize());

	BOOST_CHECK(svDecompose(u1, w1, v1, 4));

	BOOST_CHECK_NO_THROW(svSubstitute(u1, w1, v1, b1, x1_sol));

	// BOOST_MESSAGE("x1 = " << x1);
	// BOOST_MESSAGE("x1_sol = " << x1_sol);

	BOOST_CHECK(equals(x1, x1_sol, 10e-13));

	// ----------------

	Matrix<double> x2(a1.getSize2(), 5);

	for (SizeType1 i = 0; i < x2.getSize1(); i++) 
		for (SizeType1 j = 0; j < x2.getSize2(); j++)
			x2(i, j) = 10 + i / -2.1232 + j * 2.2;

	Matrix<double> b2(a1 * x2);
	Matrix<double> u2(a1);
	Vector<double> w2(a1.getSize2(), 0.0);
	Matrix<double> v2(a1.getSize2(), a1.getSize2(), 0.0);
	Matrix<double> x2_sol(x2.getSize1(), x2.getSize2());

	BOOST_CHECK(svDecompose(u2, w2, v2, 4));

	BOOST_CHECK_NO_THROW(svSubstitute(u2, w2, v2, b2, x2_sol));

	BOOST_CHECK(equals(x2, x2_sol, 10e-13));
}
