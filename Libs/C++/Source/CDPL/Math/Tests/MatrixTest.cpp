/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixTest.cpp 
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
#include <boost/random/linear_congruential.hpp>

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename M>
	void checkIdentityMatrix(typename M::SizeType size1, typename M::SizeType size2, M& mtx)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		typedef typename M::ValueType ValueType;

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				if (i == j) {
					BOOST_CHECK_EQUAL(mtx(i, j), ValueType(1));
					BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), ValueType(1));
				} else {
					BOOST_CHECK_EQUAL(mtx(i, j), ValueType());
					BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), ValueType());
				}
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);
	
		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}

	template <typename M, typename T, std::size_t N>
	void checkValues4(typename M::SizeType size1, typename M::SizeType size2, M& mtx, T values[][N])
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());
	
		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), values[i][j]);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), values[i][j]);
				
				BOOST_CHECK_EQUAL(mtx.getData()[i][j], values[i][j]);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData()[i][j], values[i][j]);
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);
	
		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}

	template <typename M, typename T>
	void checkValues4(typename M::SizeType size1, typename M::SizeType size2, M& mtx, const T& value)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), value);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), value);

				BOOST_CHECK_EQUAL(mtx.getData()[i][j], value);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData()[i][j], value);
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}

	template <typename M, typename T, std::size_t N>
	void checkValues3(typename M::SizeType size1, typename M::SizeType size2, M& mtx, T values[][N])
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		BOOST_CHECK_EQUAL(mtx.getData().getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getData().getSize2(), size2);
		BOOST_CHECK(!mtx.getData().isEmpty());

		BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData().getSize1(), size1);
		BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData().getSize2(), size2);
		BOOST_CHECK(!const_cast<const M&>(mtx).getData().isEmpty());

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), values[i][j]);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), values[i][j]);
				
				BOOST_CHECK_EQUAL(mtx.getData()(i, j), values[i][j]);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData()(i, j), values[i][j]);
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(size1, size2), Base::IndexError);
	}

	template <typename M, typename T>
	void checkValues3(typename M::SizeType size1, typename M::SizeType size2, M& mtx, const T& value)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		BOOST_CHECK_EQUAL(mtx.getData().getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getData().getSize2(), size2);
		BOOST_CHECK(!mtx.getData().isEmpty());

		BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData().getSize1(), size1);
		BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData().getSize2(), size2);
		BOOST_CHECK(!const_cast<const M&>(mtx).getData().isEmpty());

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), value);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), value);

				BOOST_CHECK_EQUAL(mtx.getData()(i, j), value);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData()(i, j), value);
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(size1, size2), Base::IndexError);
	}

	template <typename M, typename T, std::size_t N>
	void checkValues2(typename M::SizeType size1, typename M::SizeType size2, M& mtx, T values[][N])
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), values[i][j]);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), values[i][j]);
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}

	template <typename M, typename T>
	void checkValues2(typename M::SizeType size1, typename M::SizeType size2, M& mtx, const T& value)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		for (typename M::SizeType i = 0; i < size1; i++) {
			for (typename M::SizeType j = 0; j < size2; j++) {
				BOOST_CHECK_EQUAL(mtx(i, j), value);
				BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), value);
			}
		}

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}

	template <typename M, typename T, std::size_t N>
	void checkValues1(typename M::SizeType size1, typename M::SizeType size2, M& mtx, T values[][N])
	{
		checkValues2(size1, size2, mtx, values);

		BOOST_CHECK(!mtx.getData().empty());
		BOOST_CHECK(!const_cast<const M&>(mtx).getData().empty());
	}

	template <typename M, typename T>
	void checkValues1(typename M::SizeType size1, typename M::SizeType size2, M& mtx, const T& value)
	{
		checkValues2(size1, size2, mtx, value);

		BOOST_CHECK(!mtx.getData().empty());
		BOOST_CHECK(!const_cast<const M&>(mtx).getData().empty());
	}

	template <typename M>
	void checkEmpty3(typename M::SizeType size1, typename M::SizeType size2, M& mtx)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(mtx.isEmpty());

		BOOST_CHECK_EQUAL(mtx.getData().getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getData().getSize2(), size2);
		BOOST_CHECK(mtx.getData().isEmpty());

		BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData().getSize1(), size1);
		BOOST_CHECK_EQUAL(const_cast<const M&>(mtx).getData().getSize2(), size2);
		BOOST_CHECK(const_cast<const M&>(mtx).getData().isEmpty());

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx.getData()(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx).getData()(size1, size2), Base::IndexError);
	}

	template <typename M>
	void checkEmpty2(typename M::SizeType size1, typename M::SizeType size2, M& mtx)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(mtx.isEmpty());

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}

	template <typename M>
	void checkEmpty1(typename M::SizeType size1, typename M::SizeType size2, M& mtx)
	{
		checkEmpty2(size1, size2, mtx);

		BOOST_CHECK(mtx.getData().empty());
	}

	template <typename M>
	void checkSize(typename M::SizeType size1, typename M::SizeType size2, M& mtx)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
		BOOST_CHECK_EQUAL(mtx.getSize2(), size2);
		BOOST_CHECK(!mtx.isEmpty());

		BOOST_CHECK_THROW(mtx(size1, 0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, 0), Base::IndexError);

		BOOST_CHECK_THROW(mtx(0, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(0, size2), Base::IndexError);

		BOOST_CHECK_THROW(mtx(size1, size2), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const M&>(mtx)(size1, size2), Base::IndexError);
	}
}


BOOST_AUTO_TEST_CASE(MatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m1;

	// ---------

	BOOST_CHECK_EQUAL(m1.getMaxSize(), m1.getData().max_size());

	// ---------

	checkEmpty1(0, 0, m1);

	// ---------

	m1.resize(4, 5, false, 2.2);

	checkValues1(4, 5, m1, 2.2);

	// ---------

	m1(0, 0) = 2.0;
	m1(3, 1) = 3.0;
	m1.getData()[2 * 5 + 4] = -1.0;

	double values1[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	checkValues1(4, 5, m1, values1);

	// ---------

	Matrix<double> m2(m1);

	checkValues1(4, 5, m2, values1);

	// ---------

	Matrix<double> m3(3, 7);

	checkValues1(3, 7, m3, 0.0);

	// ---------

	Matrix<double> m4(5, 2, -1.97);

	checkValues1(5, 2, m4, -1.97);

	// ---------

	Matrix<double> m5(0, 5, 2.2);

	checkEmpty1(0, 5, m5);

	// ---------

	Matrix<double> m6(static_cast<const MatrixExpression<Matrix<double> >&>(m1));

	checkValues1(4, 5, m6, values1);

	// ---------

	double values2[][6] = { 
		{ 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 },
		{ 0.0,  0.0, 1.0, 1.1, 1.2, 1.3 }
	};

	typedef Matrix<double>::SizeType SizeType;

	Matrix<double> m7;

	checkEmpty1(0, 0, m7);

	m7.resize(1, 1, false, 2.0);

	checkValues1(1, 1, m7, values2);

	m7.resize(1, 2, false, -1.2);

	checkValues1(1, 2, m7, values2);

	m7.resize(1, 3, false, 5.0);

	checkValues1(1, 3, m7, values2);

	m7.resize(1, 5, true);

	checkValues1(1, 5, m7, values2);

	m7.resize(1, 6, true, 1.0);

	checkValues1(1, 6, m7, values2);

	m7.resize(1, 3, false, -1.0);

	checkValues1(1, 3, m7, values2);

	m7.resize(1, 1, false, 1.95);

	checkValues1(1, 1, m7, values2);

	m7.resize(0, 0);

	checkEmpty1(0, 0, m7);

	m7.resize(2, 0);

	checkEmpty1(2, 0, m7);

	m7.resize(0, 3);

	checkEmpty1(0, 3, m7);

	m7.resize(1, 1, false, 2.0);

	checkValues1(1, 1, m7, values2);

	m7.resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	checkValues1(2, 6, m7, values2);

	m7.resize(2, 5, true);

	checkValues1(2, 5, m7, values2);

	m7.resize(2, 4, true);
	
	checkValues1(2, 4, m7, values2);

	m7.resize(2, 3, true);
	
	checkValues1(2, 3, m7, values2);

	m7.resize(1, 6, false);
	
	checkValues1(1, 6, m7, values2);

	// ---------

	m7.resize(3, 3, false);
	m7.clear();

	checkValues1(3, 3, m7, 0.0);

	m7.clear(-2.11);

	checkValues1(3, 3, m7, -2.11);

	Matrix<double> m8;

	checkEmpty1(0, 0, m8);

	m8.clear();

	checkEmpty1(0, 0, m8);

	m8.clear(-2);

	checkEmpty1(0, 0, m8);

	// ---------

	BOOST_CHECK(&(m1 *= -2) == &m1);

	double values3[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] *= -2;

	checkValues1(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 /= -2.0) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] /= -2.0;

	checkValues1(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<Matrix<double> >&>(m1)) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] += values3[i][j];

	checkValues1(4, 5, m1, values3);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixContainer<Matrix<double> >&>(m7), Base::SizeError);

	checkValues1(4, 5, m1, values3);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixContainer<Matrix<float> >&>(Matrix<float>()), Base::SizeError);

	checkValues1(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<Matrix<double> >&>(m2)) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixContainer<Matrix<double> >&>(m7), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixContainer<Matrix<float> >&>(Matrix<float>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<Matrix<double> >&>(m2)) == &m1);

	checkValues1(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<Matrix<double> >&>(m1)) == &m1);

	checkValues1(4, 5, m1, 0.0);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<Matrix<double> >&>(m2)) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixExpression<Matrix<double> >&>(m7), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixExpression<Matrix<int> >&>(Matrix<int>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<Matrix<double> >&>(m1)) == &m1);

	checkValues1(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<Matrix<double> >&>(m2)) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixExpression<Matrix<double> >&>(m7), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixExpression<Matrix<float> >&>(Matrix<float>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<Matrix<double> >&>(m1)) == &m1);

	checkValues1(4, 5, m1, 0.0);

	// ---------

	BOOST_CHECK(&m1.plusAssign(m2) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(m7), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(Matrix<float>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.plusAssign(m1) == &m1);

	checkValues1(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&m1.minusAssign(m2) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(m7), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(Matrix<int>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.minusAssign(m1) == &m1);

	checkValues1(4, 5, m1, 0.0);

	// ---------

	m7.resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	m1.resize(2, 6);
	m1.clear();

	checkValues1(2, 6, m1, 0.0);

	BOOST_CHECK(&(m1 = m2) == &m1);

	checkValues1(4, 5, m1, values1);
	
	m1.resize(0, 0);

	checkEmpty1(0, 0, m1);

	m5.resize(4, 5, true, 2.2);

	BOOST_CHECK(&(m1 = m5) == &m1);

	checkValues1(4, 5, m1, 2.2);

	BOOST_CHECK(&(m1 = m7) == &m1);

	checkValues1(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = m1) == &m1);

	checkValues1(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = Matrix<double>()) == &m1);

	checkEmpty1(0, 0, m1);

	BOOST_CHECK(&(m1 = m7) == &m1);

	checkValues1(2, 6, m1, values2);

	// ---------

	m1.resize(1, 3, true);

	checkValues1(1, 3, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<double> >&>(m5)) == &m1);

	checkValues1(4, 5, m1, 2.2);

	m1.resize(0, 3);

	checkEmpty1(0, 3, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<double> >&>(m7)) == &m1);

	checkValues1(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<double> >&>(m6)) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<double> >&>(m1)) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<int> >&>(Matrix<int>())) == &m1);

	checkEmpty1(0, 0, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<double> >&>(m6)) == &m1);

	checkValues1(4, 5, m1, values1);

	// ---------

	m1.resize(3, 4, true);

	checkValues1(3, 4, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<double> >&>(m5)) == &m1);

	checkValues1(4, 5, m1, 2.2);

	m1.resize(0, 1);

	checkEmpty1(0, 1, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<double> >&>(m3)) == &m1);

	checkValues1(3, 7, m1, 0.0);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<double> >&>(m7)) == &m1);

	checkValues1(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<double> >&>(m1)) == &m1);

	checkValues1(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<long double> >&>(Matrix<long double>())) == &m1);

	checkEmpty1(0, 0, m1);
	
	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<double> >&>(m7)) == &m1);

	checkValues1(2, 6, m1, values2);

	// ---------

	BOOST_CHECK(&m1.assign(m3) == &m1);

	checkValues1(3, 7, m1, 0.0);

	m1.resize(0, 0, true);

	checkEmpty1(0, 0, m1);

	BOOST_CHECK(&m1.assign(m5) == &m1);

	checkValues1(4, 5, m1, 2.2);

	BOOST_CHECK(&m1.assign(m6) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK(&m1.assign(m1) == &m1);

	checkValues1(4, 5, m1, values1);

	BOOST_CHECK(&m1.assign(Matrix<float>()) == &m1);

	checkEmpty1(0, 0, m1);

	BOOST_CHECK(&m1.assign(m6) == &m1);

	checkValues1(4, 5, m1, values1);

	// ---------
	
	swap(m1, m7);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);

	swap(m1, m7);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);

	swap(m7, m1);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);

	swap(m7, m1);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);

	m1.swap(m7);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);

	m1.swap(m7);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);

	m7.swap(m1);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);

	m7.swap(m1);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);

	m1.resize(0, 0);

	checkEmpty1(0, 0, m1);

	m1.swap(m7);

	checkEmpty1(0, 0, m7);
	checkValues1(2, 6, m1, values2);

	swap(m7, m7);

	checkEmpty1(0, 0, m7);

	m7.swap(m7);

	checkEmpty1(0, 0, m7);

	swap(m1, m1);

	checkValues1(2, 6, m1, values2);

	m1.swap(m1);

	checkValues1(2, 6, m1, values2);
}

BOOST_AUTO_TEST_CASE(SparseMatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	typedef SparseMatrix<double>::SizeType SizeType;

	SparseMatrix<double> m1;

	// ---------

	BOOST_CHECK_EQUAL(m1.getMaxSize(), m1.getData().max_size());

	// ---------

	checkEmpty2(0, 0, m1);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 0);

	// ---------

	m1.resize(4, 5);

	BOOST_CHECK(m1.getData().empty());

	checkValues2(4, 5, m1, 0.0);

	// ---------

	m1(0, 0) = 2.0;
	m1(3, 1) = 3.0;
	m1(2, 4) = -1.0;

	BOOST_CHECK(m1.getNumElements() == 3);

	double values1[][5] = { 
		{ 2.0, 0.0, 0.0, 0.0,  0.0 }, 
		{ 0.0, 0.0, 0.0, 0.0,  0.0 },
		{ 0.0, 0.0, 0.0, 0.0, -1.0 },
		{ 0.0, 3.0, 0.0, 0.0,  0.0 } 
	};

	checkValues2(4, 5, m1, values1);

	// ---------

	SparseMatrix<double> m2(m1);

	checkValues2(4, 5, m2, values1);

	BOOST_CHECK(m2.getNumElements() == 3);

	// ---------

	SparseMatrix<double> m3(3, 7);

	checkValues2(3, 7, m3, 0.0);

	// ---------

	SparseMatrix<double> m4(5, 2);

	checkValues2(5, 2, m4, 0.0);

	// ---------

	SparseMatrix<double> m6(static_cast<const MatrixExpression<SparseMatrix<double> >&>(m1));

	checkValues2(4, 5, m6, values1);

	BOOST_CHECK(m6.getNumElements() == 3);

	// ---------

	double values2[][6] = { 
	    { 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 },
		{ 0.0,  0.0, 1.0, 1.1, 1.2, 1.3 }
	};

	SparseMatrix<double> m7;

	m7.resize(2, 6);

	m7(0, 0) = 2.0;
	m7(0, 1) = -1.2;
	m7(0, 2) = 5.0;
	m7(0, 3) = 0.0;
	m7(0, 4) = 0.0;
	m7(0, 5) = 1.0;

	BOOST_CHECK(m7.getNumElements() == 4);

	m7.resize(1, 6, false);
	
	checkValues2(1, 6, m7, values2);

	BOOST_CHECK(m7.getNumElements() == 4);

	// ---------

	m7.resize(3, 3);
	m7.clear();

	checkValues2(3, 3, m7, 0.0);

	BOOST_CHECK_EQUAL(m7.getNumElements(), 0);

	// ---------

	BOOST_CHECK(&(m1 *= -2) == &m1);
	BOOST_CHECK(m1.getNumElements() == 3);

	double values3[][5] = { 
		{ 2.0, 0.0, 0.0, 0.0,  0.0 }, 
		{ 0.0, 0.0, 0.0, 0.0,  0.0 },
		{ 0.0, 0.0, 0.0, 0.0, -1.0 },
		{ 0.0, 3.0, 0.0, 0.0,  0.0 } 
	};

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] *= -2;

	checkValues2(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 /= -2.0) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] /= -2.0;

	checkValues2(4, 5, m1, values3);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<SparseMatrix<double> >&>(m1)) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] += values3[i][j];

	checkValues2(4, 5, m1, values3);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixContainer<SparseMatrix<double> >&>(m7), Base::SizeError);

	checkValues2(4, 5, m1, values3);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixContainer<SparseMatrix<float> >&>(SparseMatrix<float>()), Base::SizeError);

	checkValues2(4, 5, m1, values3);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<SparseMatrix<double> >&>(m2)) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixContainer<SparseMatrix<double> >&>(m7), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixContainer<SparseMatrix<float> >&>(SparseMatrix<float>()), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<SparseMatrix<double> >&>(m2)) == &m1);

	checkValues2(4, 5, m1, values3);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<SparseMatrix<double> >&>(m1)) == &m1);

	checkValues2(4, 5, m1, 0.0);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 0);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<SparseMatrix<double> >&>(m2)) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixExpression<SparseMatrix<double> >&>(m7), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixExpression<SparseMatrix<int> >&>(SparseMatrix<int>()), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<SparseMatrix<double> >&>(m1)) == &m1);

	checkValues2(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<SparseMatrix<double> >&>(m2)) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixExpression<SparseMatrix<double> >&>(m7), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixExpression<SparseMatrix<float> >&>(SparseMatrix<float>()), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<SparseMatrix<double> >&>(m1)) == &m1);

	checkValues2(4, 5, m1, 0.0);

	// ---------

	BOOST_CHECK(&m1.plusAssign(m2) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(m7), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(SparseMatrix<float>()), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.plusAssign(m1) == &m1);

	checkValues2(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&m1.minusAssign(m2) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(m7), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(SparseMatrix<int>()), Base::SizeError);

	checkValues2(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.minusAssign(m1) == &m1);

	checkValues2(4, 5, m1, 0.0);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 0);

	// ---------

	m7.resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	m1.resize(2, 6);
	m1.clear();

	checkValues2(2, 6, m1, 0.0);

	BOOST_CHECK(&(m1 = m2) == &m1);
	BOOST_CHECK_EQUAL(m1.getNumElements(), m2.getNumElements());

	checkValues2(4, 5, m1, values1);
	
	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&(m1 = m7) == &m1);

	checkValues2(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = m1) == &m1);

	checkValues2(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = SparseMatrix<double>()) == &m1);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&(m1 = m7) == &m1);

	checkValues2(2, 6, m1, values2);

	// ---------

	m1.resize(1, 3);

	checkValues2(1, 3, m1, values2);

	BOOST_CHECK(&(m1 = ScalarMatrix<double>(4, 5, 2.2)) == &m1);

	checkValues2(4, 5, m1, 2.2);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 20);

	m1.resize(0, 3);

	checkEmpty2(0, 3, m1);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 0);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<SparseMatrix<double> >&>(m7)) == &m1);

	checkValues2(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<SparseMatrix<double> >&>(m6)) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<SparseMatrix<double> >&>(m1)) == &m1);

	checkValues2(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<SparseMatrix<int> >&>(SparseMatrix<int>())) == &m1);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<SparseMatrix<double> >&>(m6)) == &m1);

	checkValues2(4, 5, m1, values1);

	// ---------

	m1.resize(3, 4, true);

	checkValues2(3, 4, m1, values1);

	BOOST_CHECK(&(m1 = ScalarMatrix<double>(4, 5, 3.2)) == &m1);

	checkValues2(4, 5, m1, 3.2);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 20);

	m1.resize(0, 1);

	checkEmpty2(0, 1, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<SparseMatrix<double> >&>(m3)) == &m1);

	checkValues2(3, 7, m1, 0.0);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<SparseMatrix<double> >&>(m7)) == &m1);

	checkValues2(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<SparseMatrix<double> >&>(m1)) == &m1);

	checkValues2(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<SparseMatrix<long double> >&>(SparseMatrix<long double>())) == &m1);

	checkEmpty2(0, 0, m1);
	
	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<SparseMatrix<double> >&>(m7)) == &m1);

	checkValues2(2, 6, m1, values2);

	// ---------

	BOOST_CHECK(&m1.assign(m3) == &m1);

	checkValues2(3, 7, m1, 0.0);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 0);

	BOOST_CHECK(&m1.assign(ScalarMatrix<double>(4, 5, 3.2)) == &m1);

	checkValues2(4, 5, m1, 3.2);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 20);

	BOOST_CHECK(&m1.assign(m6) == &m1);

	checkValues2(4, 5, m1, values1);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	m1.resize(20, 20);

	BOOST_CHECK(&m1.assign(m1) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			BOOST_CHECK_EQUAL(m1(i, j), values1[i][j]);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	BOOST_CHECK(&m1.assign(SparseMatrix<float>()) == &m1);

	checkEmpty2(0, 0, m1);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 0);

	BOOST_CHECK(&m1.assign(m6) == &m1);

	checkValues2(4, 5, m1, values1);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	// ---------

	BOOST_CHECK_EQUAL(m7.getNumElements(), 8);
	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);

	swap(m1, m7);

	checkValues2(4, 5, m7, values1);
	checkValues2(2, 6, m1, values2);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 8);
	BOOST_CHECK_EQUAL(m7.getNumElements(), 3);

	swap(m1, m7);

	checkValues2(2, 6, m7, values2);
	checkValues2(4, 5, m1, values1);

	BOOST_CHECK_EQUAL(m1.getNumElements(), 3);
	BOOST_CHECK_EQUAL(m7.getNumElements(), 8);

	swap(m7, m1);

	checkValues2(4, 5, m7, values1);
	checkValues2(2, 6, m1, values2);

	swap(m7, m1);

	checkValues2(2, 6, m7, values2);
	checkValues2(4, 5, m1, values1);

	m1.swap(m7);

	checkValues2(4, 5, m7, values1);
	checkValues2(2, 6, m1, values2);

	m1.swap(m7);

	checkValues2(2, 6, m7, values2);
	checkValues2(4, 5, m1, values1);

	m7.swap(m1);

	checkValues2(4, 5, m7, values1);
	checkValues2(2, 6, m1, values2);

	m7.swap(m1);

	checkValues2(2, 6, m7, values2);
	checkValues2(4, 5, m1, values1);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	m1.swap(m7);

	checkEmpty2(0, 0, m7);
	checkValues2(2, 6, m1, values2);

	swap(m7, m7);

	checkEmpty2(0, 0, m7);

	m7.swap(m7);

	checkEmpty2(0, 0, m7);

	swap(m1, m1);

	checkValues2(2, 6, m1, values2);

	m1.swap(m1);

	checkValues2(2, 6, m1, values2);
}

BOOST_AUTO_TEST_CASE(BoundedMatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	BoundedMatrix<double, 4, 7> m1;

	checkEmpty2(0, 0, m1);

	// ---------

	BOOST_CHECK_EQUAL(m1.getMaxSize1(), 4);
	BOOST_CHECK_EQUAL(m1.getMaxSize2(), 7);

	BOOST_CHECK_EQUAL((BoundedMatrix<double, 4, 7>::MaxSize1), 4);
	BOOST_CHECK_EQUAL((BoundedMatrix<double, 4, 7>::MaxSize2), 7);

	BOOST_CHECK_EQUAL((BoundedMatrix<double, 0, 7>()).getMaxSize1(), 0);
	BOOST_CHECK_EQUAL((BoundedMatrix<double, 0, 7>()).getMaxSize2(), 7);

	BOOST_CHECK_EQUAL((BoundedMatrix<double, 5, 0>()).getMaxSize1(), 5);
	BOOST_CHECK_EQUAL((BoundedMatrix<double, 5, 0>()).getMaxSize2(), 0);

	BOOST_CHECK_EQUAL((BoundedMatrix<double, 0, 0>()).getMaxSize1(), 0);
	BOOST_CHECK_EQUAL((BoundedMatrix<double, 0, 0>()).getMaxSize2(), 0);

	// ---------

	m1.resize(4, 5, 2.2);

	checkValues4(4, 5, m1, 2.2);

	// ---------

	m1(0, 0) = 2.0;
	m1(3, 1) = 3.0;
	m1.getData()[2][4] = -1.0;

	double values1[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	checkValues4(4, 5, m1, values1);

	// ---------

	BoundedMatrix<double, 4, 7> m2(m1);

	checkValues4(4, 5, m2, values1);

	// ---------

	BoundedMatrix<double, 3, 7> m3(3, 7);

	checkSize(3, 7, m3);

	m3.clear();
	checkValues4(3, 7, m3, 0.0);

	// ---------

	BoundedMatrix<double, 5, 2> m4(5, 2, -1.97);

	checkValues4(5, 2, m4, -1.97);

	// ---------

	BoundedMatrix<double, 5, 5> m5(0, 5, 2.2);

	checkEmpty2(0, 5, m5);

	// ---------

	BoundedMatrix<double, 8, 8> m6(m1);

	checkValues4(4, 5, m6, values1);

	// ---------

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(m1)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(Matrix<double>(5, 3))), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(m6)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(4, 4)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(5, 3)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(5, 4)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(4, 4, 1.0)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(5, 3, 0.0)), Base::RangeError);

	BOOST_CHECK_THROW((BoundedMatrix<double, 4, 3>(5, 4, 2.2)), Base::RangeError);

	// ---------

	double values2[][6] = { 
		{ 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 },
		{ 0.0,  0.0, 1.0, 1.1, 1.2, 1.3 }
	};

	typedef BoundedMatrix<double, 3, 6>::SizeType SizeType;

	BoundedMatrix<double, 3, 6> m7;

	checkEmpty2(0, 0, m7);

	m7.resize(1, 1, 2.0);

	checkValues4(1, 1, m7, values2);

	m7.resize(1, 2, -1.2);

	checkValues4(1, 2, m7, values2);

	m7.resize(1, 3, 5.0);

	checkValues4(1, 3, m7, values2);

	m7.resize(1, 5, 0.0);

	checkValues4(1, 5, m7, values2);

	m7.resize(1, 6, 1.0);

	checkValues4(1, 6, m7, values2);

	m7.resize(1, 3, -1.0);

	checkValues4(1, 3, m7, values2);

	m7.resize(1, 1, 1.95);

	checkValues4(1, 1, m7, values2);

	m7.resize(0, 0);

	checkEmpty2(0, 0, m7);

	m7.resize(2, 0);

	checkEmpty2(2, 0, m7);

	m7.resize(0, 3);

	checkEmpty2(0, 3, m7);

	m7.resize(1, 1);

	checkValues4(1, 1, m7, values2);

	m7.resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	checkValues4(2, 6, m7, values2);

	m7.resize(2, 5);

	checkValues4(2, 5, m7, values2);

	m7.resize(2, 4);
	
	checkValues4(2, 4, m7, values2);

	m7.resize(2, 3);
	
	checkValues4(2, 3, m7, values2);

	m7.resize(2, 6);
	
	checkValues4(2, 6, m7, values2);

	BOOST_CHECK_THROW(m7.resize(3, 7), Base::RangeError);

	checkValues4(2, 6, m7, values2);

	BOOST_CHECK_THROW(m7.resize(4, 6), Base::RangeError);

	checkValues4(2, 6, m7, values2);

	BOOST_CHECK_THROW(m7.resize(4, 7), Base::RangeError);

	checkValues4(2, 6, m7, values2);

	BOOST_CHECK_THROW(m7.resize(3, 7, 1.0), Base::RangeError);

	checkValues4(2, 6, m7, values2);

	BOOST_CHECK_THROW(m7.resize(4, 6, 0.0), Base::RangeError);

	checkValues4(2, 6, m7, values2);

	BOOST_CHECK_THROW(m7.resize(4, 7, -2.3), Base::RangeError);

	checkValues4(2, 6, m7, values2);

	// ---------

	m7.resize(3, 3);
	m7.clear();

	checkValues4(3, 3, m7, 0.0);

	m7.clear(-2.11);

	checkValues4(3, 3, m7, -2.11);

	BoundedMatrix<double, 6, 6> m8;

	checkEmpty2(0, 0, m8);

	m8.clear();

	checkEmpty2(0, 0, m8);

	m8.clear(-2);

	checkEmpty2(0, 0, m8);

	// ---------

	BOOST_CHECK(&(m1 *= -2) == &m1);

	double values3[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] *= -2;

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 /= -2.0) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] /= -2.0;

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<BoundedMatrix<double, 4, 7> >&>(m1)) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] += values3[i][j];

	checkValues4(4, 5, m1, values3);

	BOOST_CHECK_THROW((m1 += static_cast<const MatrixContainer<BoundedMatrix<double, 3, 6> >&>(m7)), Base::SizeError);

	checkValues4(4, 5, m1, values3);

	BOOST_CHECK_THROW((m1 += static_cast<const MatrixContainer<BoundedMatrix<float, 3, 2> >&>(BoundedMatrix<float, 3, 2>())), Base::SizeError);

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<BoundedMatrix<double, 4, 7> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 -= static_cast<const MatrixContainer<BoundedMatrix<double, 3, 6> >&>(m7)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixContainer<Matrix<float> >&>(Matrix<float>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<BoundedMatrix<double, 4, 7> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<BoundedMatrix<double, 4, 7> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, 0.0);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<BoundedMatrix<double, 4, 7> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 += static_cast<const MatrixExpression<BoundedMatrix<double, 3, 6> >&>(m7)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixExpression<Matrix<int> >&>(Matrix<int>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<BoundedMatrix<double, 4, 7> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<BoundedMatrix<double, 4, 7> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 -= static_cast<const MatrixExpression<BoundedMatrix<double, 3, 6> >&>(m7)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 -= static_cast<const MatrixExpression<Matrix<float> >&>(Matrix<float>())), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<BoundedMatrix<double, 4, 7> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, 0.0);

	// ---------
	
	BOOST_CHECK(&m1.plusAssign(m2) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(m7), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(Matrix<float>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.plusAssign(m1) == &m1);

	checkValues4(4, 5, m1, values3);

	// ---------
	
	BOOST_CHECK(&m1.minusAssign(m2) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(Matrix<double>(m1.getSize1(), m1.getSize2() + 1)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(Matrix<double>(m1.getSize1() + 1, m1.getSize2())), Base::SizeError);

	checkValues4(4, 5, m1, values1);
	
	// ---------

	BOOST_CHECK(&m1.minusAssign(m1) == &m1);

	checkValues4(4, 5, m1, 0.0);

	// ---------

	m7.resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	m1.resize(2, 6, 0.0);

	checkValues4(2, 6, m1, 0.0);

	BOOST_CHECK(&(m1 = m2) == &m1);

	checkValues4(4, 5, m1, values1);
	
	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&(m1 = BoundedMatrix<double, 4, 7>(m5)) == &m1);

	checkEmpty2(0, 5, m1);

	BOOST_CHECK(&(m1 = BoundedMatrix<double, 4, 7>(m7)) == &m1);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = m1) == &m1);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = BoundedMatrix<double, 4, 7>()) == &m1);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&(m1 = BoundedMatrix<double, 4, 7>(m7)) == &m1);

	checkValues4(2, 6, m1, values2);

	// ---------

	m1.resize(1, 3);
	m5.resize(4, 5, 2.2);

	checkValues4(1, 3, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<BoundedMatrix<double, 5, 5> >&>(m5)) == &m1);

	checkValues4(4, 5, m1, 2.2);

	m1.resize(0, 3);

	checkEmpty2(0, 3, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<BoundedMatrix<double, 3, 6> >&>(m7)) == &m1);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<BoundedMatrix<double, 8, 8> >&>(m6)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<BoundedMatrix<double, 4, 7> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<int> >&>(Matrix<int>())) == &m1);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<BoundedMatrix<double, 8, 8> >&>(m6)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixExpression<Matrix<double> >&>(Matrix<double>(8, 8))), Base::RangeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixExpression<Matrix<double> >&>(Matrix<double>(4, 8))), Base::RangeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixExpression<Matrix<double> >&>(Matrix<double>(5, 7))), Base::RangeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	m1.resize(3, 4);

	checkValues4(3, 4, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<BoundedMatrix<double, 5, 5> >&>(m5)) == &m1);

	checkValues4(4, 5, m1, 2.2);

	m1.resize(0, 1);

	checkEmpty2(0, 1, m1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<BoundedMatrix<double, 3, 7> >&>(m3)) == &m1);

	checkValues4(3, 7, m1, 0.0);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<BoundedMatrix<double, 3, 6> >&>(m7)) == &m1);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<BoundedMatrix<double, 4, 7> >&>(m1)) == &m1);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<BoundedMatrix<long double, 0, 0> >&>(BoundedMatrix<long double, 0, 0>())) == &m1);

	checkEmpty2(0, 0, m1);
	
	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<BoundedMatrix<double, 3, 6> >&>(m7)) == &m1);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixContainer<Matrix<double> >&>(Matrix<double>(8, 8))), Base::RangeError);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixContainer<Matrix<double> >&>(Matrix<double>(4, 8))), Base::RangeError);

	checkValues4(2, 6, m1, values2);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixContainer<Matrix<double> >&>(Matrix<double>(5, 7))), Base::RangeError);

	checkValues4(2, 6, m1, values2);

	// ---------

	BOOST_CHECK(&m1.assign(m3) == &m1);

	checkValues4(3, 7, m1, 0.0);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&m1.assign(m5) == &m1);

	checkValues4(4, 5, m1, 2.2);

	BOOST_CHECK(&m1.assign(m6) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&m1.assign(m1) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&m1.assign(Matrix<float>()) == &m1);

	checkEmpty2(0, 0, m1);

	BOOST_CHECK(&m1.assign(m6) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.assign(Matrix<double>(8, 8)), Base::RangeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.assign(Matrix<double>(4, 8)), Base::RangeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.assign(Matrix<double>(5, 7)), Base::RangeError);

	checkValues4(4, 5, m1, values1);

	// ---------
	
	BoundedMatrix<double, 4, 7> m10(m7);

	swap(m1, m10);

	checkValues4(4, 5, m10, values1);
	checkValues4(2, 6, m1, values2);

	swap(m1, m10);

	checkValues4(2, 6, m10, values2);
	checkValues4(4, 5, m1, values1);

	swap(m10, m1);

	checkValues4(4, 5, m10, values1);
	checkValues4(2, 6, m1, values2);

	swap(m10, m1);

	checkValues4(2, 6, m10, values2);
	checkValues4(4, 5, m1, values1);

	m1.swap(m10);

	checkValues4(4, 5, m10, values1);
	checkValues4(2, 6, m1, values2);

	m1.swap(m10);

	checkValues4(2, 6, m10, values2);
	checkValues4(4, 5, m1, values1);

	m10.swap(m1);

	checkValues4(4, 5, m10, values1);
	checkValues4(2, 6, m1, values2);

	m10.swap(m1);

	checkValues4(2, 6, m10, values2);
	checkValues4(4, 5, m1, values1);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	m1.swap(m10);

	checkEmpty2(0, 0, m10);
	checkValues4(2, 6, m1, values2);

	swap(m10, m10);

	checkEmpty2(0, 0, m10);

	m10.swap(m10);

	checkEmpty2(0, 0, m10);

	swap(m1, m1);

	checkValues4(2, 6, m1, values2);

	m1.swap(m1);

	checkValues4(2, 6, m1, values2);
}

BOOST_AUTO_TEST_CASE(CMatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	CMatrix<double, 4, 5> m1;

	checkSize(4, 5, m1);

	BOOST_CHECK_EQUAL(m1.getMaxSize1(), 4);
	BOOST_CHECK_EQUAL(m1.getMaxSize2(), 5);

	// ---------

	BOOST_CHECK_EQUAL((CMatrix<double, 6, 12>::Size1), 6);
	BOOST_CHECK_EQUAL((CMatrix<double, 6, 12>::Size2), 12);

	BOOST_CHECK_EQUAL((CMatrix<double, 0, 7>()).getMaxSize1(), 0);
	BOOST_CHECK_EQUAL((CMatrix<double, 0, 7>()).getMaxSize2(), 7);

	checkEmpty2<const CMatrix<double, 0, 7> >(0, 7, CMatrix<double, 0, 7>());

	BOOST_CHECK_EQUAL((CMatrix<double, 5, 0>()).getMaxSize1(), 5);
	BOOST_CHECK_EQUAL((CMatrix<double, 5, 0>()).getMaxSize2(), 0);

	checkEmpty2<const CMatrix<double, 5, 0> >(5, 0, CMatrix<double, 5, 0>());

	BOOST_CHECK_EQUAL((CMatrix<double, 0, 0>()).getMaxSize1(), 0);
	BOOST_CHECK_EQUAL((CMatrix<double, 0, 0>()).getMaxSize2(), 0);

	checkEmpty2<const CMatrix<double, 0, 0> >(0, 0, CMatrix<double, 0, 0>());

	// ---------

	m1.clear(2.2);
	m1(0, 0) = 2.0;
	m1(3, 1) = 3.0;
	m1.getData()[2][4] = -1.0;

	double values1[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	checkValues4(4, 5, m1, values1);

	// ---------

	CMatrix<double, 4, 5> m2(m1);

	checkValues4(4, 5, m2, values1);

	// ---------

	CMatrix<double, 4, 5> m3(2.2);

	checkValues4(4, 5, m3, 2.2);

	// ---------

	CMatrix<double, 5, 2> m4(ScalarMatrix<float>(5, 2, 1.97f));

	checkValues4(5, 2, m4, 1.97f);

	// ---------

	BOOST_CHECK_THROW((CMatrix<double, 4, 3>(m1)), Base::SizeError);

	BOOST_CHECK_THROW((CMatrix<double, 4, 3>(Matrix<double>(5, 3))), Base::SizeError);

	BOOST_CHECK_THROW((CMatrix<double, 0, 7>(m1)), Base::SizeError);

	BOOST_CHECK_THROW((CMatrix<double, 4, 0>(m1)), Base::SizeError);

	BOOST_CHECK_THROW((CMatrix<double, 0, 0>(m1)), Base::SizeError);

	// ---------

	m4.clear();

	checkValues4(5, 2, m4, 0.0);

	m4.clear(2.17);

	checkValues4(5, 2, m4, 2.17);

	// ---------

	BOOST_CHECK(&(m1 *= -2) == &m1);

	double values3[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] *= -2;

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 /= -2.0) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] /= -2.0;

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<CMatrix<double, 4, 5> >&>(m1)) == &m1);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] += values3[i][j];

	checkValues4(4, 5, m1, values3);

	BOOST_CHECK_THROW((m1 += static_cast<const MatrixContainer<CMatrix<double, 5, 2> >&>(m4)), Base::SizeError);

	checkValues4(4, 5, m1, values3);

	BOOST_CHECK_THROW((m1 += static_cast<const MatrixContainer<Matrix<float> >&>(Matrix<float>())), Base::SizeError);

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<CMatrix<double, 4, 5> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 -= static_cast<const MatrixContainer<CMatrix<double, 5, 2> >&>(m4)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 -= static_cast<const MatrixContainer<Matrix<float> >&>(Matrix<float>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixContainer<CMatrix<double, 4, 5> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixContainer<CMatrix<double, 4, 5> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, 0.0);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<CMatrix<double, 4, 5> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 += static_cast<const MatrixExpression<CMatrix<double, 5, 2> >&>(m4)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1 += static_cast<const MatrixExpression<Matrix<int> >&>(Matrix<int>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 += static_cast<const MatrixExpression<CMatrix<double, 4, 5> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, values3);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<CMatrix<double, 4, 5> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 -= static_cast<const MatrixExpression<CMatrix<double, 5, 2> >&>(m4)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 -= static_cast<const MatrixExpression<Matrix<float> >&>(Matrix<float>())), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 -= static_cast<const MatrixExpression<CMatrix<double, 4, 5> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, 0.0);

	// ---------
	
	BOOST_CHECK(&m1.plusAssign(m2) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(m4), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.plusAssign(Matrix<float>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.plusAssign(m1) == &m1);

	checkValues4(4, 5, m1, values3);

	// ---------
	
	BOOST_CHECK(&m1.minusAssign(m2) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(Matrix<double>(m1.getSize1(), m1.getSize2() + 1)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.minusAssign(m4), Base::SizeError);

	checkValues4(4, 5, m1, values1);
	
	// ---------

	BOOST_CHECK(&m1.minusAssign(m1) == &m1);

	checkValues4(4, 5, m1, 0.0);

	// ---------

	BOOST_CHECK(&(m1 = m2) == &m1);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<Matrix<double> >&>(Matrix<double>(4, 5, 2.3))) == &m1);

	checkValues4(4, 5, m1, 2.3);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<CMatrix<double, 4, 5> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixExpression<CMatrix<double, 4, 5> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixExpression<Matrix<double> >&>(Matrix<double>(8, 8))), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixExpression<Matrix<float> >&>(Matrix<float>())), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<Matrix<float> >&>(Matrix<float>(4, 5, 1.0f))) == &m1);

	checkValues4(4, 5, m1, 1.0f);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<CMatrix<double, 4, 5> >&>(m2)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&(m1 = static_cast<const MatrixContainer<CMatrix<double, 4, 5> >&>(m1)) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixContainer<Matrix<double> >&>(Matrix<double>(8, 8))), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW((m1 = static_cast<const MatrixContainer<Matrix<double> >&>(Matrix<double>())), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------

	BOOST_CHECK(&m1.assign(Matrix<double>(4, 5, -2.22)) == &m1);

	checkValues4(4, 5, m1, -2.22);

	BOOST_CHECK(&m1.assign(m2) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK(&m1.assign(m1) == &m1);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.assign(Matrix<double>(4, 8)), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	BOOST_CHECK_THROW(m1.assign(Matrix<double>()), Base::SizeError);

	checkValues4(4, 5, m1, values1);

	// ---------
	
	CMatrix<double, 4, 5> m5(0.27);

	swap(m1, m5);

	checkValues4(4, 5, m5, values1);
	checkValues4(4, 5, m1, 0.27);

	swap(m1, m5);

	checkValues4(4, 5, m5, 0.27);
	checkValues4(4, 5, m1, values1);

	swap(m5, m1);

	checkValues4(4, 5, m5, values1);
	checkValues4(4, 5, m1, 0.27);

	swap(m5, m1);

	checkValues4(4, 5, m5, 0.27);
	checkValues4(4, 5, m1, values1);

	m1.swap(m5);

	checkValues4(4, 5, m5, values1);
	checkValues4(4, 5, m1, 0.27);

	m1.swap(m5);

	checkValues4(4, 5, m5, 0.27);
	checkValues4(4, 5, m1, values1);

	m5.swap(m1);

	checkValues4(4, 5, m5, values1);
	checkValues4(4, 5, m1, 0.27);

	m5.swap(m1);

	checkValues4(4, 5, m5, 0.27);
	checkValues4(4, 5, m1, values1);

	swap(m1, m1);

	checkValues4(4, 5, m1, values1);

	m1.swap(m1);

	checkValues4(4, 5, m1, values1);
}

BOOST_AUTO_TEST_CASE(ZeroMatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	ZeroMatrix<float> m1;

	checkEmpty2(0, 0, m1);

	BOOST_CHECK_EQUAL(m1.getMaxSize1(), std::numeric_limits<ZeroMatrix<float>::SizeType>::max());
	BOOST_CHECK_EQUAL(m1.getMaxSize2(), std::numeric_limits<ZeroMatrix<float>::SizeType>::max());

	// ---------

	ZeroMatrix<float> m2(13, 10);

	checkValues2(13, 10, m2, 0);

	// ---------

	ZeroMatrix<float> m3(m2);

	checkValues2(13, 10, m3, 0);

	// ---------

	ZeroMatrix<float> m4(0, 5);

	checkEmpty2(0, 5, m4);

	ZeroMatrix<float> m5(3, 0);

	checkEmpty2(3, 0, m5);

	ZeroMatrix<float> m6(0, 0);

	checkEmpty2(0, 0, m6);

	// ---------

	m1 = m1;

	checkEmpty2(0, 0, m1);

	m1 = m2;

	checkValues2(13, 10, m1, 0);

	m1 = m1;

	checkValues2(13, 10, m1, 0);
	
	// ---------

	m1.resize(7, 3);

	checkValues2(7, 3, m1, 0);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	m1.resize(0, 4);

	checkEmpty2(0, 4, m1);

	m1.resize(2, 0);

	checkEmpty2(2, 0, m1);

	// ---------

	m1.swap(m3);

	checkValues2(13, 10, m1, 0);
	checkEmpty2(2, 0, m3);

	m1.swap(m3);

	checkValues2(13, 10, m3, 0);
	checkEmpty2(2, 0, m1);

	m3.swap(m1);

	checkValues2(13, 10, m1, 0);
	checkEmpty2(2, 0, m3);

	m3.swap(m1);

	checkValues2(13, 10, m3, 0);
	checkEmpty2(2, 0, m1);
	
	swap(m1, m3);

	checkValues2(13, 10, m1, 0);
	checkEmpty2(2, 0, m3);

	swap(m1, m3);

	checkValues2(13, 10, m3, 0);
	checkEmpty2(2, 0, m1);

	swap(m3, m1);

	checkValues2(13, 10, m1, 0);
	checkEmpty2(2, 0, m3);

	swap(m3, m1);

	checkValues2(13, 10, m3, 0);
	checkEmpty2(2, 0, m1);

	m1.resize(5, 8);

	checkValues2(5, 8, m1, 0);

	m1.swap(m3);

	checkValues2(13, 10, m1, 0);
	checkValues2(5, 8, m3, 0);

	swap(m3, m1);

	checkValues2(13, 10, m3, 0);
	checkValues2(5, 8, m1, 0);

	// ----

	m1.swap(m1);

	checkValues2(5, 8, m1, 0);

	swap(m1, m1);

	checkValues2(5, 8, m1, 0);
}

BOOST_AUTO_TEST_CASE(ScalarMatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	ScalarMatrix<double> m1;

	checkEmpty2(0, 0, m1);

	BOOST_CHECK_EQUAL(m1.getMaxSize1(), std::numeric_limits<ScalarMatrix<double>::SizeType>::max());
	BOOST_CHECK_EQUAL(m1.getMaxSize2(), std::numeric_limits<ScalarMatrix<double>::SizeType>::max());

	// ---------

	ScalarMatrix<double> m2(13, 10, -1.372);

	checkValues2(13, 10, m2, -1.372);

	// ---------

	ScalarMatrix<double> m3(m2);

	checkValues2(13, 10, m3, -1.372);

	// ---------

	ScalarMatrix<double> m4(5, 9);

	checkValues2(5, 9, m4, 0);

	// ---------

	ScalarMatrix<double> m5(0, 2, 1.2);

	checkEmpty2(0, 2, m5);

	ScalarMatrix<float> m6(3, 0);

	checkEmpty2(3, 0, m6);

	ScalarMatrix<float> m7(0, 0);

	checkEmpty2(0, 0, m7);

	// ---------

	m1 = m1;

	checkEmpty2(0, 0, m1);

	m1 = m2;

	checkValues2(13, 10, m1, -1.372);
	checkValues2(13, 10, m2, -1.372);

	m1 = m1;

	checkValues2(13, 10, m1, -1.372);
	
	// ---------

	m1.resize(7, 2);

	checkValues2(7, 2, m1, -1.372);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	m1.resize(0, 4);

	checkEmpty2(0, 4, m1);

	m1.resize(2, 0);

	checkEmpty2(2, 0, m1);

	m1.resize(7, 3);

	checkValues2(7, 3, m1, -1.372);

	// ---------

	m1.swap(m5);

	checkValues2(7, 3, m5, -1.372);
	checkEmpty2(0, 2, m1);

	m1.swap(m5);

	checkValues2(7, 3, m1, -1.372);
	checkEmpty2(0, 2, m5);

	m5.swap(m1);

	checkValues2(7, 3, m5, -1.372);
	checkEmpty2(0, 2, m1);

	m5.swap(m1);

	checkValues2(7, 3, m1, -1.372);
	checkEmpty2(0, 2, m5);

	swap(m1, m5);

	checkValues2(7, 3, m5, -1.372);
	checkEmpty2(0, 2, m1);

	swap(m1, m5);

	checkValues2(7, 3, m1, -1.372);
	checkEmpty2(0, 2, m5);

	swap(m5, m1);

	checkValues2(7, 3, m5, -1.372);
	checkEmpty2(0, 2, m1);

	swap(m5, m1);

	checkValues2(7, 3, m1, -1.372);
	checkEmpty2(0, 2, m5);

	// --

	m5.resize(6, 6);

	checkValues2(6, 6, m5, 1.2);

	m1.swap(m5);

	checkValues2(7, 3, m5, -1.372);
	checkValues2(6, 6, m1, 1.2);

	m1.swap(m5);

	checkValues2(7, 3, m1, -1.372);
	checkValues2(6, 6, m5, 1.2);

	m5.swap(m1);

	checkValues2(7, 3, m5, -1.372);
	checkValues2(6, 6, m1, 1.2);

	m5.swap(m1);

	checkValues2(7, 3, m1, -1.372);
	checkValues2(6, 6, m5, 1.2);

	swap(m1, m5);

	checkValues2(7, 3, m5, -1.372);
	checkValues2(6, 6, m1, 1.2);

	swap(m1, m5);

	checkValues2(7, 3, m1, -1.372);
	checkValues2(6, 6, m5, 1.2);

	swap(m5, m1);

	checkValues2(7, 3, m5, -1.372);
	checkValues2(6, 6, m1, 1.2);

	swap(m5, m1);

	checkValues2(7, 3, m1, -1.372);
	checkValues2(6, 6, m5, 1.2);

	// --

	m1.swap(m1);

	checkValues2(7, 3, m1, -1.372);

	swap(m1, m1);

	checkValues2(7, 3, m1, -1.372);
}

BOOST_AUTO_TEST_CASE(IdentityMatrixTest)
{
	using namespace CDPL;
	using namespace Math;

	IdentityMatrix<float> m1;

	checkEmpty2(0, 0, m1);

	BOOST_CHECK_EQUAL(m1.getMaxSize1(), std::numeric_limits<IdentityMatrix<float>::SizeType>::max());
	BOOST_CHECK_EQUAL(m1.getMaxSize2(), std::numeric_limits<IdentityMatrix<float>::SizeType>::max());

	// ---------

	IdentityMatrix<float> m2(13, 10);

	checkIdentityMatrix(13, 10, m2);

	// ---------

	IdentityMatrix<float> m3(m2);

	checkIdentityMatrix(13, 10, m3);

	// ---------

	IdentityMatrix<float> m4(0, 5);

	checkEmpty2(0, 5, m4);

	IdentityMatrix<float> m5(3, 0);

	checkEmpty2(3, 0, m5);

	IdentityMatrix<float> m6(0, 0);

	checkEmpty2(0, 0, m6);

	// ---------

	m1 = m1;

	checkEmpty2(0, 0, m1);

	m1 = m2;

	checkIdentityMatrix(13, 10, m1);

	m1 = m1;

	checkIdentityMatrix(13, 10, m1);
	
	// ---------

	m1.resize(7, 3);

	checkIdentityMatrix(7, 3, m1);

	m1.resize(0, 0);

	checkEmpty2(0, 0, m1);

	m1.resize(0, 4);

	checkEmpty2(0, 4, m1);

	m1.resize(2, 0);

	checkEmpty2(2, 0, m1);

	// ---------

	m1.swap(m3);

	checkIdentityMatrix(13, 10, m1);
	checkEmpty2(2, 0, m3);

	m1.swap(m3);

	checkIdentityMatrix(13, 10, m3);
	checkEmpty2(2, 0, m1);

	m3.swap(m1);

	checkIdentityMatrix(13, 10, m1);
	checkEmpty2(2, 0, m3);

	m3.swap(m1);

	checkIdentityMatrix(13, 10, m3);
	checkEmpty2(2, 0, m1);
	
	swap(m1, m3);

	checkIdentityMatrix(13, 10, m1);
	checkEmpty2(2, 0, m3);

	swap(m1, m3);

	checkIdentityMatrix(13, 10, m3);
	checkEmpty2(2, 0, m1);

	swap(m3, m1);

	checkIdentityMatrix(13, 10, m1);
	checkEmpty2(2, 0, m3);

	swap(m3, m1);

	checkIdentityMatrix(13, 10, m3);
	checkEmpty2(2, 0, m1);

	m1.resize(5, 8);

	checkIdentityMatrix(5, 8, m1);

	m1.swap(m3);

	checkIdentityMatrix(13, 10, m1);
	checkIdentityMatrix(5, 8, m3);

	swap(m3, m1);

	checkIdentityMatrix(13, 10, m3);
	checkIdentityMatrix(5, 8, m1);

	// ----

	m1.swap(m1);

	checkIdentityMatrix(5, 8, m1);

	swap(m1, m1);

	checkIdentityMatrix(5, 8, m1);
}

BOOST_AUTO_TEST_CASE(MatrixReferenceTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixReference<Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(MatrixReference<Matrix<double> >::ValueType));
	BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(MatrixReference<Matrix<double> >::SizeType));
	BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(MatrixReference<Matrix<double> >::DifferenceType));
	BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(MatrixReference<Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixReference<Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixReference<const Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixReference<const Matrix<double> >::ConstReference));

	// ---------

	Matrix<double> m1;
	MatrixReference<Matrix<double> > m1_ref(m1);

	// ---------

	BOOST_CHECK_EQUAL(m1.getMaxSize(), m1.getData().max_size());
	BOOST_CHECK_EQUAL(m1_ref.getMaxSize(), m1.getMaxSize());

	BOOST_CHECK(&m1_ref.getData() == &m1);
	BOOST_CHECK(&static_cast<const MatrixReference<Matrix<double> >&>(m1_ref).getData() == &m1);

	BOOST_CHECK_EQUAL((MatrixReference<const CMatrix<double, 4, 5> >(CMatrix<double, 4, 5>())).getMaxSize1(), 4);
	BOOST_CHECK_EQUAL((MatrixReference<const CMatrix<double, 4, 5> >(CMatrix<double, 4, 5>())).getMaxSize2(), 5);

	// ---------

	checkEmpty1(0, 0, m1);
	checkEmpty3(0, 0, m1_ref);

	// ---------

	m1.resize(4, 5, false, 2.2);

	checkValues1(4, 5, m1, 2.2);
	checkValues3(4, 5, m1_ref, 2.2);

	// ---------

	m1_ref(0, 0) = 2.0;
	m1_ref(3, 1) = 3.0;
	m1_ref.getData()(2, 4) = -1.0;

	double values1[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------

	Matrix<double> m2(m1);
	MatrixReference<Matrix<double> > m2_ref(m2);

	checkValues1(4, 5, m2, values1);
	checkValues3(4, 5, m2_ref, values1);

	// ---------

	Matrix<double> m3(3, 7);
	MatrixReference<Matrix<double> > m3_ref(m3);

	checkValues1(3, 7, m3, 0.0);
	checkValues3(3, 7, m3_ref, 0.0);

	// ---------

	Matrix<double> m4(5, 2, -1.97);
	MatrixReference<Matrix<double> > m4_ref(m4);

	checkValues1(5, 2, m4, -1.97);
	checkValues3(5, 2, m4_ref, -1.97);

	// ---------

	Matrix<double> m5(0, 5, 2.2);
	MatrixReference<Matrix<double> > m5_ref(m5);

	checkEmpty1(0, 5, m5);
	checkEmpty3(0, 5, m5_ref);

	// ---------

	Matrix<double> m6(static_cast<const MatrixExpression<Matrix<double> >&>(m1));
	MatrixReference<Matrix<double> > m6_ref(m6);

	checkValues1(4, 5, m6, values1);
	checkValues3(4, 5, m6_ref, values1);

	// ---------

	double values2[][6] = { 
		{ 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 },
		{ 0.0,  0.0, 1.0, 1.1, 1.2, 1.3 }
	};

	typedef Matrix<double>::SizeType SizeType;

	Matrix<double> m7;
	MatrixReference<Matrix<double> > m7_ref(m7);

	checkEmpty1(0, 0, m7);
	checkEmpty3(0, 0, m7_ref);

	m7.resize(1, 1, false, 2.0);

	checkValues1(1, 1, m7, values2);
	checkValues3(1, 1, m7_ref, values2);

	m7_ref.getData().resize(1, 2, false, -1.2);

	checkValues1(1, 2, m7, values2);
	checkValues3(1, 2, m7_ref, values2);

	m7.resize(1, 3, false, 5.0);

	checkValues1(1, 3, m7, values2);
	checkValues3(1, 3, m7_ref, values2);

	m7_ref.getData().resize(1, 5, true);

	checkValues1(1, 5, m7, values2);
	checkValues3(1, 5, m7_ref, values2);

	m7.resize(1, 6, true, 1.0);

	checkValues1(1, 6, m7, values2);
	checkValues3(1, 6, m7_ref, values2);

	m7_ref.getData().resize(1, 3, false, -1.0);

	checkValues1(1, 3, m7, values2);
	checkValues3(1, 3, m7_ref, values2);

	m7.resize(1, 1, false, 1.95);

	checkValues1(1, 1, m7, values2);
	checkValues3(1, 1, m7_ref, values2);

	m7_ref.getData().resize(0, 0);

	checkEmpty1(0, 0, m7);
	checkEmpty3(0, 0, m7_ref);

	m7.resize(2, 0);

	checkEmpty1(2, 0, m7);
	checkEmpty3(2, 0, m7_ref);

	m7_ref.getData().resize(0, 3);

	checkEmpty1(0, 3, m7);
	checkEmpty3(0, 3, m7_ref);

	m7.resize(1, 1, false, 2.0);

	checkValues1(1, 1, m7, values2);
	checkValues3(1, 1, m7_ref, values2);

	m7_ref.getData().resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	checkValues1(2, 6, m7, values2);
	checkValues3(2, 6, m7_ref, values2);

	m7.resize(2, 5, true);

	checkValues1(2, 5, m7, values2);
	checkValues3(2, 5, m7_ref, values2);

	m7_ref.getData().resize(2, 4, true);
	
	checkValues1(2, 4, m7, values2);
	checkValues3(2, 4, m7_ref, values2);

	m7.resize(2, 3, true);
	
	checkValues1(2, 3, m7, values2);
	checkValues3(2, 3, m7_ref, values2);

	m7_ref.getData().resize(1, 6, false);
	
	checkValues1(1, 6, m7, values2);
	checkValues3(1, 6, m7_ref, values2);

	// ---------

	m7_ref.getData().resize(3, 3, false);
	m7_ref.getData().clear();

	checkValues1(3, 3, m7, 0.0);
	checkValues3(3, 3, m7_ref, 0.0);

	m7_ref.getData().clear(-2.11);

	checkValues1(3, 3, m7, -2.11);
	checkValues3(3, 3, m7_ref, -2.11);

	Matrix<double> m8;
	MatrixReference<Matrix<double> > m8_ref(m8);

	checkEmpty1(0, 0, m8);
	checkEmpty3(0, 0, m8_ref);

	m8_ref.getData().clear();

	checkEmpty1(0, 0, m8);
	checkEmpty3(0, 0, m8_ref);

	m8_ref.getData().clear(-2);

	checkEmpty1(0, 0, m8);
	checkEmpty3(0, 0, m8_ref);

	// ---------

	BOOST_CHECK(&(m1_ref *= -2) == &m1_ref);

	double values3[][5] = { 
		{ 2.0, 2.2, 2.2, 2.2,  2.2 }, 
		{ 2.2, 2.2, 2.2, 2.2,  2.2 },
		{ 2.2, 2.2, 2.2, 2.2, -1.0 },
		{ 2.2, 3.0, 2.2, 2.2,  2.2 } 
	};

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] *= -2;

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	// ---------

	BOOST_CHECK(&(m1_ref /= -2.0) == &m1_ref);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] /= -2.0;

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	// ---------

	BOOST_CHECK(&(m1_ref += m1_ref) == &m1_ref);

	for (std::size_t i = 0; i < 4; i++)
		for (std::size_t j = 0; j < 5; j++)
			values3[i][j] += values3[i][j];

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	BOOST_CHECK_THROW(m1_ref += m7, Base::SizeError);

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	BOOST_CHECK_THROW(m1_ref += Matrix<float>(), Base::SizeError);

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	// ---------

	BOOST_CHECK(&(m1_ref -= m2) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1 -= m7, Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1 -= Matrix<int>(), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------

	BOOST_CHECK(&(m1_ref += m2_ref) == &m1_ref);

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	// ---------

	BOOST_CHECK(&(m1_ref -= m1_ref) == &m1_ref);

	checkValues1(4, 5, m1, 0.0);
	checkValues3(4, 5, m1_ref, 0.0);

	// ---------

	BOOST_CHECK(&(m1_ref += m2_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref += m7, Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW((m1_ref += CMatrix<double, 0, 0>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------

	BOOST_CHECK(&(m1_ref += m1) == &m1_ref);

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	// ---------

	BOOST_CHECK(&(m1_ref -= m2_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref -= m7, Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref -= Matrix<double>(), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------

	BOOST_CHECK(&(m1_ref -= m1_ref) == &m1_ref);

	checkValues1(4, 5, m1, 0.0);
	checkValues3(4, 5, m1_ref, 0.0);

	// ---------

	BOOST_CHECK(&m1_ref.plusAssign(m2_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref.plusAssign(m7), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref.plusAssign(Matrix<float>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------

	BOOST_CHECK(&m1_ref.plusAssign(m1_ref) == &m1_ref);

	checkValues1(4, 5, m1, values3);
	checkValues3(4, 5, m1_ref, values3);

	// ---------

	BOOST_CHECK(&m1_ref.minusAssign(m2_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref.minusAssign(m7_ref), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK_THROW(m1_ref.minusAssign(Matrix<int>()), Base::SizeError);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------

	BOOST_CHECK(&m1_ref.minusAssign(m1) == &m1_ref);

	checkValues1(4, 5, m1, 0.0);
	checkValues3(4, 5, m1_ref, 0.0);

	// ---------

	m7_ref.getData().resize(2, 6);

	for (SizeType i = 0; i < 2; i++)
		for (SizeType j = 0; j < 6; j++)
			m7(i, j) = values2[i][j];

	m1.resize(2, 6);

	checkValues1(2, 6, m1, 0.0);
	checkValues3(2, 6, m1_ref, 0.0);

	BOOST_CHECK(&(m1_ref = m2_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);
	
	m1_ref.getData().resize(0, 0);

	checkEmpty1(0, 0, m1);
	checkEmpty3(0, 0, m1_ref);

	m5.resize(4, 5, false, 2.2);

	BOOST_CHECK(&(m1_ref = m5) == &m1_ref);

	checkValues1(4, 5, m1, 2.2);
	checkValues3(4, 5, m1_ref, 2.2);

	BOOST_CHECK(&(m1_ref = m7_ref) == &m1_ref);

	checkValues1(2, 6, m1, values2);
	checkValues3(2, 6, m1_ref, values2);

	BOOST_CHECK(&(m1_ref = m1_ref) == &m1_ref);

	checkValues1(2, 6, m1, values2);
	checkValues3(2, 6, m1_ref, values2);

	BOOST_CHECK(&(m1_ref = Matrix<double>()) == &m1_ref);

	checkEmpty1(0, 0, m1);
	checkEmpty3(0, 0, m1_ref);

	BOOST_CHECK(&(m1_ref = m7) == &m1_ref);

	checkValues1(2, 6, m1, values2);
	checkValues3(2, 6, m1_ref, values2);

	// ---------

	BOOST_CHECK(&m1_ref.assign(m3) == &m1_ref);

	checkValues1(3, 7, m1, 0.0);
	checkValues3(3, 7, m1_ref, 0.0);

	m1.resize(0, 0, true);

	checkEmpty1(0, 0, m1);
	checkEmpty3(0, 0, m1_ref);

	BOOST_CHECK(&m1_ref.assign(m5_ref) == &m1_ref);

	checkValues1(4, 5, m1, 2.2);
	checkValues3(4, 5, m1_ref, 2.2);

	BOOST_CHECK(&m1_ref.assign(m6) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK(&m1_ref.assign(m1_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	BOOST_CHECK(&m1_ref.assign(Matrix<int>()) == &m1_ref);

	checkEmpty1(0, 0, m1);
	checkEmpty3(0, 0, m1_ref);

	BOOST_CHECK(&m1_ref.assign(m6_ref) == &m1_ref);

	checkValues1(4, 5, m1, values1);
	checkValues3(4, 5, m1_ref, values1);

	// ---------
	
	swap(m1_ref, m7_ref);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);
	checkValues3(4, 5, m7_ref, values1);
	checkValues3(2, 6, m1_ref, values2);

	swap(m1_ref, m7_ref);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);
	checkValues3(2, 6, m7_ref, values2);
	checkValues3(4, 5, m1_ref, values1);

	swap(m7_ref, m1_ref);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);
	checkValues3(4, 5, m7_ref, values1);
	checkValues3(2, 6, m1_ref, values2);

	swap(m7_ref, m1_ref);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);
	checkValues3(2, 6, m7_ref, values2);
	checkValues3(4, 5, m1_ref, values1);

	m1_ref.swap(m7_ref);

	checkValues1(4, 5, m7, values1);
	checkValues1(2, 6, m1, values2);
	checkValues3(4, 5, m7_ref, values1);
	checkValues3(2, 6, m1_ref, values2);

	m1_ref.swap(m7_ref);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);
	checkValues3(2, 6, m7_ref, values2);
	checkValues3(4, 5, m1_ref, values1);

	m7_ref.swap(m1_ref);

	checkValues1(4, 5, m7, values1);
	checkValues1(4, 5, m7, values1);
	checkValues3(2, 6, m1_ref, values2);
	checkValues3(2, 6, m1_ref, values2);

	m7_ref.swap(m1_ref);

	checkValues1(2, 6, m7, values2);
	checkValues1(4, 5, m1, values1);
	checkValues3(2, 6, m7_ref, values2);
	checkValues3(4, 5, m1_ref, values1);

	m1.resize(0, 0);

	checkEmpty1(0, 0, m1);
	checkEmpty3(0, 0, m1_ref);

	m1_ref.swap(m7_ref);

	checkEmpty1(0, 0, m7);
	checkValues1(2, 6, m1, values2);
	checkEmpty3(0, 0, m7_ref);
	checkValues3(2, 6, m1_ref, values2);

	swap(m7_ref, m7_ref);

	checkEmpty1(0, 0, m7);
	checkEmpty3(0, 0, m7_ref);

	m7_ref.swap(m7_ref);

	checkEmpty1(0, 0, m7);
	checkEmpty3(0, 0, m7_ref);

	swap(m1_ref, m1_ref);

	checkValues1(2, 6, m1, values2);
	checkValues3(2, 6, m1_ref, values2);

	m1_ref.swap(m1_ref);

	checkValues1(2, 6, m1, values2);
	checkValues3(2, 6, m1_ref, values2);
}

BOOST_AUTO_TEST_CASE(DetFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix3F m(0);

	m(0, 0) = -2;
	m(0, 1) = 2;
	m(0, 2) = -3;
	m(1, 0) = -1;
	m(1, 1) = 1;
	m(1, 2) = 3;
	m(2, 0) = 2;
	m(2, 1) = 0;
	m(2, 2) = -1;

	BOOST_CHECK_CLOSE(det(m), 18.0f, 0.0001f);

	//------

	BOOST_CHECK_CLOSE(det(IdentityMatrix<double>(20, 20)), 1.0, 0.0001);

	//------

	BOOST_CHECK_EQUAL(det(ZeroMatrix<float>(10, 10)), 0.0f);
}

BOOST_AUTO_TEST_CASE(InvertFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	typedef CMatrix<double, 300, 300>::SizeType SizeType;

	CMatrix<double, 300, 300> m1;

	boost::rand48 rand;

	while (true) {
		for (SizeType i = 0; i < m1.getSize1(); i++)
			for (SizeType j = 0; j < m1.getSize2(); j++)
				m1(i, j) = double(rand()) / rand.max();

		if (det(m1) != 0)
			break;
	}

	CMatrix<double, 300, 300> m2;

	BOOST_CHECK(invert(m1, m2));

	BOOST_CHECK(equals(m1 * m2, IdentityMatrix<double>(m1.getSize1(), m1.getSize2()), 1e-10));

	//------

	Matrix<double> m3;

	BOOST_CHECK(invert(ZeroMatrix<double>(0, 0), m3));

	BOOST_CHECK(ZeroMatrix<double>(0, 0) == m3);

	BOOST_CHECK(invert(m3));

	BOOST_CHECK(ZeroMatrix<double>(0, 0) == m3);

	//------

	BOOST_CHECK(invert(IdentityMatrix<double>(10, 10), m3));

	BOOST_CHECK(equals(IdentityMatrix<double>(10, 10), m3, 0.0000001));

	m3 = IdentityMatrix<double>(10, 10);

	BOOST_CHECK(invert(m3));

	BOOST_CHECK(equals(IdentityMatrix<double>(10, 10), m3, 0.0000001));

	//------

	BOOST_CHECK(!invert(IdentityMatrix<double>(9, 10), m3));
	BOOST_CHECK(!invert(IdentityMatrix<double>(8, 9), m3));
	BOOST_CHECK(!invert(IdentityMatrix<double>(0, 10), m3));
	BOOST_CHECK(!invert(IdentityMatrix<double>(8, 0), m3));

	m3 = IdentityMatrix<double>(9, 10);

	BOOST_CHECK(!invert(m3));

	m3 = IdentityMatrix<double>(10, 9);

	BOOST_CHECK(!invert(m3));

	m3 = IdentityMatrix<double>(0, 9);

	BOOST_CHECK(!invert(m3));

	m3 = IdentityMatrix<double>(10, 0);

	BOOST_CHECK(!invert(m3));
}
