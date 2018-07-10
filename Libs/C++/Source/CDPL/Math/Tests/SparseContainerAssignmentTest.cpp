/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SparseContainerAssignmentTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/SparseContainerAssignment.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename M, typename T, std::size_t N>
	void checkValues(typename M::SizeType num_elem, typename M::SizeType size1, typename M::SizeType size2, M& mtx, T values[][N])
	{
		BOOST_CHECK_EQUAL(mtx.getNumElements(), num_elem);
		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), values[i][j]);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), values[i][j]);
			}
		}
	}

	template <typename M, typename T>
	void checkValues(typename M::SizeType num_elem, typename M::SizeType size1, typename M::SizeType size2, M& mtx, const T& value)
	{
		BOOST_CHECK_EQUAL(mtx.getNumElements(), num_elem);
		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), value);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), value);
			}
		}
	}

	template <typename T1, typename T2>
	struct DirectAssignment
	{

		static void apply(T1& t1, const T2& t2) {
			t1 = t2;
		}
	};

	template <typename T1, typename T2>
	struct AdditionAssignment
	{

		static void apply(T1& t1, const T2& t2) {
			t1 += t2;
		}
	};
}


BOOST_AUTO_TEST_CASE(SparseContainerAssignScalarFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	SparseMatrix<double> m1;

	checkValues(0, 0, 0, m1, 0.0);

	// -------

	sparseContainerAssignScalar<AdditionAssignment>(m1, 4.25);

	checkValues(0, 0, 0, m1, 0.0);

	// -------

	m1.resize(0, 6);

	checkValues(0, 0, 6, m1, 0.0);

	sparseContainerAssignScalar<AdditionAssignment>(m1, 1.11);

	checkValues(0, 0, 6, m1, 0.0);

	// -------

	m1.resize(5, 0);

	checkValues(0, 5, 0, m1, 0.0);

	sparseContainerAssignScalar<DirectAssignment>(m1, -2.11);

	checkValues(0, 5, 0, m1, 0.0);

	// -------

	m1.resize(7, 3);

	checkValues(0, 7, 3, m1, -2.11);

	sparseContainerAssignScalar<AdditionAssignment>(m1, 1.12);

	checkValues(0, 7, 3, m1, -2.11 + 1.12);

	sparseContainerAssignScalar<AdditionAssignment>(m1, 1.22);

	checkValues(0, 7, 3, m1, -2.11 + 1.12 + 1.22);

	// -------

	m1.resize(7, 6);

	sparseContainerAssignScalar<DirectAssignment>(m1, -4.0);

	checkValues(0, 7, 6, m1, -4.0);

	// -------

	m1.resize(7, 3);

	checkValues(0, 7, 3, m1, -4.0);

	double values[7][3];

	typedef SparseMatrix<double>::SizeType SizeType;

	for (SizeType i = 0; i < 7; i++) {
		for (SizeType j = 0; j < 3; j++) {
			values[i][j] = double(i * 7 + j);
			m1(i, j) = values[i][j];
		}
	}

	checkValues(21, 7, 3, m1, values);

	sparseContainerAssignScalar<AdditionAssignment>(m1, -2.12);

	for (std::size_t i = 0; i < 7; i++) {
		for (std::size_t j = 0; j < 3; j++) {
			values[i][j] += -2.12;
		}
	}

	checkValues(21, 7, 3, m1, values);

	sparseContainerAssignScalar<DirectAssignment>(m1, 4.123);

	checkValues(21, 7, 3, m1, 4.123);

	// -------

	sparseContainerAssignScalar<DirectAssignment>(m1, int(-2));

	checkValues(21, 7, 3, m1, double(int(-2)));

	// -------

	m1.resize(3, 3, false);

	sparseContainerAssignScalar<DirectAssignment>(m1, 4.123);

	checkValues(9, 3, 3, m1, 4.123);
	
	m1.resize(7, 3, false);

	checkValues(9, 7, 3, m1, 4.123);
}
