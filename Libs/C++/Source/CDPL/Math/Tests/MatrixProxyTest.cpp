/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixProxyTest.cpp 
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


#include <algorithm>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename MR, typename M>
	void checkMatrixRow(MR& mr, const M& m, typename M::SizeType idx, const M* values)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mr.getSize(), m.getSize2());
		BOOST_CHECK_EQUAL(mr.getIndex(), idx);
		BOOST_CHECK(mr.isEmpty() == (m.getSize2() == 0));

		BOOST_CHECK(&mr.getData().getData() == &m);
		BOOST_CHECK(&const_cast<const MR&>(mr).getData().getData() == &m);

		typedef typename MR::SizeType SizeType;

		for (SizeType i = 0; i < mr.getSize() + 3; i++) {
			if (i >= mr.getSize()) {
				BOOST_CHECK_THROW(mr[i], Base::IndexError);
				BOOST_CHECK_THROW(mr(i), Base::IndexError);

				BOOST_CHECK_THROW(const_cast<const MR&>(mr)[i], Base::IndexError);
				BOOST_CHECK_THROW(const_cast<const MR&>(mr)(i), Base::IndexError);

				BOOST_CHECK_THROW(m(idx, i), Base::IndexError);

			} else {
				BOOST_CHECK_EQUAL(mr[i], m(idx, i));
				BOOST_CHECK_EQUAL(mr(i), m(idx, i));

				BOOST_CHECK_EQUAL(const_cast<const MR&>(mr)[i], m(idx, i));
				BOOST_CHECK_EQUAL(const_cast<const MR&>(mr)(i), m(idx, i));
			}
		}

		if (values) {
			for (SizeType i = 0; i < m.getSize1(); i++)
				for (SizeType j = 0; j < m.getSize2(); j++)
					BOOST_CHECK_EQUAL(m(i, j), (*values)(i, j)); 
		}
	}

	template <typename MC, typename M>
	void checkMatrixColumn(MC& mc, const M& m, typename M::SizeType idx, const M* values)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mc.getSize(), m.getSize1());
		BOOST_CHECK_EQUAL(mc.getIndex(), idx);
		BOOST_CHECK(mc.isEmpty() == (m.getSize1() == 0));

		BOOST_CHECK(&mc.getData().getData() == &m);
		BOOST_CHECK(&const_cast<const MC&>(mc).getData().getData() == &m);

		typedef typename MC::SizeType SizeType;

		for (SizeType i = 0; i < mc.getSize() + 3; i++) {
			if (i >= mc.getSize()) {
				BOOST_CHECK_THROW(mc[i], Base::IndexError);
				BOOST_CHECK_THROW(mc(i), Base::IndexError);

				BOOST_CHECK_THROW(const_cast<const MC&>(mc)[i], Base::IndexError);
				BOOST_CHECK_THROW(const_cast<const MC&>(mc)(i), Base::IndexError);

				BOOST_CHECK_THROW(m(i, idx), Base::IndexError);

			} else {
				BOOST_CHECK_EQUAL(mc[i], m(i, idx));
				BOOST_CHECK_EQUAL(mc(i), m(i, idx));

				BOOST_CHECK_EQUAL(const_cast<const MC&>(mc)[i], m(i, idx));
				BOOST_CHECK_EQUAL(const_cast<const MC&>(mc)(i), m(i, idx));
			}
		}

		if (values) {
			for (SizeType i = 0; i < m.getSize1(); i++)
				for (SizeType j = 0; j < m.getSize2(); j++)
					BOOST_CHECK_EQUAL(m(i, j), (*values)(i, j)); 
		}
	}

	template <typename MR, typename M, typename R, typename VM>
	void checkMatrixRange(MR& mr, const M& m, const R& r_rows, const R& r_cols, const VM* values)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(mr.getSize1(), r_rows.getSize());
		BOOST_CHECK_EQUAL(mr.getStart1(), r_rows.getStart());

		BOOST_CHECK_EQUAL(mr.getSize2(), r_cols.getSize());
		BOOST_CHECK_EQUAL(mr.getStart2(), r_cols.getStart());

		BOOST_CHECK(mr.isEmpty() == (r_rows.isEmpty() || r_cols.isEmpty()));

		typedef typename MR::SizeType SizeType;

		for (SizeType i = 0; i < mr.getSize1() + 3; i++) {
			for (SizeType j = 0; j < mr.getSize2() + 3; j++) {
				if (i >= mr.getSize1() || j >= mr.getSize2()) {
					BOOST_CHECK_THROW(mr(i, j), Base::IndexError);
					BOOST_CHECK_THROW(const_cast<const MR&>(mr)(i, j), Base::IndexError);

				} else {
					BOOST_CHECK_EQUAL(mr(i, j), m(r_rows(i), r_cols(j)));
					BOOST_CHECK_EQUAL(const_cast<const MR&>(mr)(i, j), m(r_rows(i), r_cols(j)));
				}
			}
		}

		if (values) {
			for (SizeType i = 0; i < m.getSize1(); i++)
				for (SizeType j = 0; j < m.getSize2(); j++)
					BOOST_CHECK_EQUAL(m(i, j), (*values)(i, j)); 
		}
	}

	template <typename MS, typename M, typename S, typename VM>
	void checkMatrixSlice(MS& ms, const M& m, const S& s_rows, const S& s_cols, const VM* values)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(ms.getSize1(), s_rows.getSize());
		BOOST_CHECK_EQUAL(ms.getStart1(), s_rows.getStart());
		BOOST_CHECK_EQUAL(ms.getStride1(), s_rows.getStride());

		BOOST_CHECK_EQUAL(ms.getSize2(), s_cols.getSize());
		BOOST_CHECK_EQUAL(ms.getStart2(), s_cols.getStart());
		BOOST_CHECK_EQUAL(ms.getStride2(), s_cols.getStride());

		BOOST_CHECK(ms.isEmpty() == (s_rows.isEmpty() || s_cols.isEmpty()));

		typedef typename MS::SizeType SizeType;

		for (SizeType i = 0; i < ms.getSize1() + 3; i++) {
			for (SizeType j = 0; j < ms.getSize2() + 3; j++) {
				if (i >= ms.getSize1() || j >= ms.getSize2()) {
					BOOST_CHECK_THROW(ms(i, j), Base::IndexError);
					BOOST_CHECK_THROW(const_cast<const MS&>(ms)(i, j), Base::IndexError);

				} else {
					BOOST_CHECK_EQUAL(ms(i, j), m(s_rows(i), s_cols(j)));
					BOOST_CHECK_EQUAL(const_cast<const MS&>(ms)(i, j), m(s_rows(i), s_cols(j)));
				}
			}
		}

		if (values) {
			for (SizeType i = 0; i < m.getSize1(); i++)
				for (SizeType j = 0; j < m.getSize2(); j++)
					BOOST_CHECK_EQUAL(m(i, j), (*values)(i, j)); 
		}
	}
}


BOOST_AUTO_TEST_CASE(MatrixRowTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixRow<Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(MatrixRow<Matrix<double> >::ValueType));
	BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(MatrixRow<Matrix<double> >::SizeType));
	BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(MatrixRow<Matrix<double> >::DifferenceType));
	BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(MatrixRow<Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixRow<Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixRow<const Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixRow<const Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(const Matrix<double>) == typeid(MatrixRow<const Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixRow<Matrix<double> >::MatrixType));

	// ---------

	typedef Matrix<double>::SizeType SizeType1;

	Matrix<double> m1;
	MatrixRow<Matrix<double> > m1_row(m1, 2);

	BOOST_CHECK_THROW(m1_row(0), Base::IndexError);
	BOOST_CHECK_THROW(m1_row[0], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)(0), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)[0], Base::IndexError);

	m1.resize(1, 5);

	BOOST_CHECK_THROW(m1_row(0), Base::IndexError);
	BOOST_CHECK_THROW(m1_row[0], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)(0), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)[0], Base::IndexError);

	m1.resize(3, 5);

	BOOST_CHECK_THROW(m1_row(5), Base::IndexError);
	BOOST_CHECK_THROW(m1_row[5], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)(5), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)[5], Base::IndexError);

	BOOST_CHECK_NO_THROW(m1_row(0));
	BOOST_CHECK_NO_THROW(m1_row[0]);
	BOOST_CHECK_NO_THROW(m1_row(4));
	BOOST_CHECK_NO_THROW(m1_row[4]);

	BOOST_CHECK_NO_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)(0));
	BOOST_CHECK_NO_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)[0]);
	BOOST_CHECK_NO_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)(4));
	BOOST_CHECK_NO_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)[4]);

	m1.resize(2, 5);

	BOOST_CHECK_THROW(m1_row(0), Base::IndexError);
	BOOST_CHECK_THROW(m1_row[0], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)(0), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixRow<Matrix<double> >&>(m1_row)[0], Base::IndexError);

	// ---------

	m1.resize(5, 4);

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			m1(i, j) =  i * m1.getSize2() + j + i / 10.0;

	Matrix<double> values1(m1);

	m1_row[0] = 2.0;
	m1_row.getData()(2, 1) = -1.0;
	m1_row.getData()(0, 0) = -50.0;
	m1_row(2) = 3.0;

	values1(0, 0) = -50.0;
	values1(2, 0) = 2.0;
	values1(2, 1) = -1.0;
	values1(2, 2) = 3.0;

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	Matrix<double> m2(m1);
	MatrixRow<Matrix<double> > m2_row(m2, 0);

	checkMatrixRow(m2_row, m2, 0, &values1);

	// ---------

	Matrix<double> m3(m1);
	MatrixRow<Matrix<double> > m3_row(m3, 4);
	MatrixRow<Matrix<double> > m3_row_tmp(m3_row);

	checkMatrixRow(m3_row, m3, 4, &values1);
	checkMatrixRow(m3_row_tmp, m3, 4, &values1);

	// ---------

	Matrix<double> m4(m1);
	MatrixRow<const Matrix<double> > m4_row(m4, 3);

	m4.resize(5, 3, true);

	checkMatrixRow(m4_row, m4, 3, &values1);

	// ---------

	MatrixRow<const Matrix<double> > m5_row(m4_row);

	checkMatrixRow(m5_row, m4, 3, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) *= -2.0;

	BOOST_CHECK(&(m1_row *= -2.0) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) /= -2.0;

	BOOST_CHECK(&(m1_row /= -2.0) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += m2(0, i);

	BOOST_CHECK(&(m1_row += vec(m2(0, 0), m2(0, 1), m2(0, 2), m2(0, 3))) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row += Vector<float>(3, -0.123), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row += Vector<int>(5, 23), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) -= m2(3, i);

	BOOST_CHECK(&(m1_row -= vec(m2(3, 0), m2(3, 1), m2(3, 2), m2(3, 3))) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row -= Vector<int>(5, 0), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row -= vec(1.0, 2.0), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += values1(2, i);

	BOOST_CHECK(&(m1_row += m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = 0.0;

	BOOST_CHECK(&(m1_row -= m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += m2_row(i);

	BOOST_CHECK(&(m1_row += m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) -= m3_row(i);

	BOOST_CHECK(&(m1_row -= m3_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += m3_row(i);

	BOOST_CHECK(&m1_row.plusAssign(m3_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.plusAssign(m4_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.plusAssign(Vector<float>(10)), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------
	
	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) -= i + 1 + 0.1 * i;

	BOOST_CHECK(&m1_row.minusAssign(vec(1.0, 2.1, 3.2, 4.3)) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.minusAssign(m4_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.minusAssign(Vector<int>(5)), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += values1(2, i);

	BOOST_CHECK(&m1_row.plusAssign(m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = 0.0;

	BOOST_CHECK(&m1_row.minusAssign(m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += m2_row(i);

	BOOST_CHECK(&m1_row.plusAssign(m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = 0.0;

	BOOST_CHECK(&m1_row.minusAssign(m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = m2_row(i);

	BOOST_CHECK(&(m1_row = m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK(&(m1_row = m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = 0.0f;

	BOOST_CHECK(&(m1_row = Vector<float>(4, 0.0f)) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = m2_row(i);

	BOOST_CHECK(&(m1_row = m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW((m1_row = m4_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW((m1_row = Vector<float>(2, 0.0f)), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW((m1_row = Vector<int>(5, 0)), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) += values1(2, i);

	BOOST_CHECK(&(m1_row += m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = m2_row(i);

	BOOST_CHECK(&m1_row.assign(m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK(&m1_row.assign(m1_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = 1;

	BOOST_CHECK(&m1_row.assign(ScalarVector<int>(4, 1)) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize2(); i++)
		values1(2, i) = m2_row(i);

	BOOST_CHECK(&m1_row.assign(m2_row) == &m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.assign(m4_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.assign(Vector<float>(5, 0.0f)), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_row.assign(Vector<double>(0)), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);

	// ---------
	
	m1 = m2;
	values1 = m1;

	Matrix<double> values1_swp(values1);
	Matrix<double> values2(m2);
	Matrix<double> values2_swp(values2);

	for (SizeType1 i = 0; i < values1_swp.getSize2(); i++)
		std::swap(values1_swp(2, i), values2_swp(0, i));

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m2_row, m2, 0, &values2);

	swap(m1_row, m2_row);

	checkMatrixRow(m1_row, m1, 2, &values1_swp);
	checkMatrixRow(m2_row, m2, 0, &values2_swp);

	swap(m1_row, m2_row);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m2_row, m2, 0, &values2);

	swap(m2_row, m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1_swp);
	checkMatrixRow(m2_row, m2, 0, &values2_swp);

	swap(m2_row, m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m2_row, m2, 0, &values2);

	m1_row.swap(m2_row);

	checkMatrixRow(m1_row, m1, 2, &values1_swp);
	checkMatrixRow(m2_row, m2, 0, &values2_swp);

	m1_row.swap(m2_row);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m2_row, m2, 0, &values2);

	m2_row.swap(m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1_swp);
	checkMatrixRow(m2_row, m2, 0, &values2_swp);

	m2_row.swap(m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m2_row, m2, 0, &values2);

	// ---------

	Matrix<double> m6(m4);
	Matrix<double> values3(m4);
	MatrixRow<Matrix<double> > m6_row(m6, 4);

	checkMatrixRow(m6_row, m6, 4, &values3);

	BOOST_CHECK_THROW(m1_row.swap(m6_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m6_row, m6, 4, &values3);

	BOOST_CHECK_THROW(swap(m1_row, m6_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m6_row, m6, 4, &values3);

	BOOST_CHECK_THROW(m6_row.swap(m1_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m6_row, m6, 4, &values3);

	BOOST_CHECK_THROW(swap(m6_row, m1_row), Base::SizeError);

	checkMatrixRow(m1_row, m1, 2, &values1);
	checkMatrixRow(m6_row, m6, 4, &values3);

	// ---------

	m1_row.swap(m1_row);

	checkMatrixRow(m1_row, m1, 2, &values1);
	
	swap(m6_row, m6_row);

	checkMatrixRow(m6_row, m6, 4, &values3);
}

BOOST_AUTO_TEST_CASE(MatrixColumnTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixColumn<Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(MatrixColumn<Matrix<double> >::ValueType));
	BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(MatrixColumn<Matrix<double> >::SizeType));
	BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(MatrixColumn<Matrix<double> >::DifferenceType));
	BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(MatrixColumn<Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixColumn<Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixColumn<const Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixColumn<const Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(const Matrix<double>) == typeid(MatrixColumn<const Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixColumn<Matrix<double> >::MatrixType));

	// ---------

	typedef Matrix<double>::SizeType SizeType1;

	Matrix<double> m1;
	MatrixColumn<Matrix<double> > m1_col(m1, 2);

	BOOST_CHECK_THROW(m1_col(0), Base::IndexError);
	BOOST_CHECK_THROW(m1_col[0], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)(0), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)[0], Base::IndexError);

	m1.resize(5, 1);

	BOOST_CHECK_THROW(m1_col(0), Base::IndexError);
	BOOST_CHECK_THROW(m1_col[0], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)(0), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)[0], Base::IndexError);

	m1.resize(5, 3);

	BOOST_CHECK_THROW(m1_col(5), Base::IndexError);
	BOOST_CHECK_THROW(m1_col[5], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)(5), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)[5], Base::IndexError);

	BOOST_CHECK_NO_THROW(m1_col(0));
	BOOST_CHECK_NO_THROW(m1_col[0]);
	BOOST_CHECK_NO_THROW(m1_col(4));
	BOOST_CHECK_NO_THROW(m1_col[4]);

	BOOST_CHECK_NO_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)(0));
	BOOST_CHECK_NO_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)[0]);
	BOOST_CHECK_NO_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)(4));
	BOOST_CHECK_NO_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)[4]);

	m1.resize(5, 2);

	BOOST_CHECK_THROW(m1_col(0), Base::IndexError);
	BOOST_CHECK_THROW(m1_col[0], Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)(0), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixColumn<Matrix<double> >&>(m1_col)[0], Base::IndexError);

	// ---------

	m1.resize(4, 5);

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			m1(i, j) =  i * m1.getSize2() + j + i / 10.0;

	Matrix<double> values1(m1);

	m1_col[0] = 2.0;
	m1_col.getData()(1, 2) = -1.0;
	m1_col.getData()(0, 0) = -50.0;
	m1_col(2) = 3.0;

	values1(0, 0) = -50.0;
	values1(0, 2) = 2.0;
	values1(1, 2) = -1.0;
	values1(2, 2) = 3.0;

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	Matrix<double> m2(m1);
	MatrixColumn<Matrix<double> > m2_col(m2, 0);

	checkMatrixColumn(m2_col, m2, 0, &values1);

	// ---------

	Matrix<double> m3(m1);
	MatrixColumn<Matrix<double> > m3_col(m3, 4);
	MatrixColumn<Matrix<double> > m3_col_tmp(m3_col);

	checkMatrixColumn(m3_col, m3, 4, &values1);
	checkMatrixColumn(m3_col_tmp, m3, 4, &values1);

	// ---------

	Matrix<double> m4(m1);
	MatrixColumn<const Matrix<double> > m4_col(m4, 3);

	m4.resize(3, 5, true);

	checkMatrixColumn(m4_col, m4, 3, &values1);

	// ---------

	MatrixColumn<const Matrix<double> > m5_col(m4_col);

	checkMatrixColumn(m5_col, m4, 3, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) *= -2.0;

	BOOST_CHECK(&(m1_col *= -2.0) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) /= -2.0;

	BOOST_CHECK(&(m1_col /= -2.0) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += m2(i, 0);

	BOOST_CHECK(&(m1_col += vec(m2(0, 0), m2(1, 0), m2(2, 0), m2(3, 0))) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col += Vector<float>(3, -0.123), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col += Vector<int>(5, 23), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) -= m2(i, 3);

	BOOST_CHECK(&(m1_col -= vec(m2(0, 3), m2(1, 3), m2(2, 3), m2(3, 3))) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col -= Vector<int>(5, 0), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col -= vec(1.0, 2.0), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += values1(i, 2);

	BOOST_CHECK(&(m1_col += m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = 0.0;

	BOOST_CHECK(&(m1_col -= m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += m2_col(i);

	BOOST_CHECK(&(m1_col += m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) -= m3_col(i);

	BOOST_CHECK(&(m1_col -= m3_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += m3_col(i);

	BOOST_CHECK(&m1_col.plusAssign(m3_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.plusAssign(m4_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.plusAssign(Vector<float>(10)), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------
	
	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) -= i + 1 + 0.1 * i;

	BOOST_CHECK(&m1_col.minusAssign(vec(1.0, 2.1, 3.2, 4.3)) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.minusAssign(m4_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.minusAssign(Vector<int>(5)), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += values1(i, 2);

	BOOST_CHECK(&m1_col.plusAssign(m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = 0.0;

	BOOST_CHECK(&m1_col.minusAssign(m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += m2_col(i);

	BOOST_CHECK(&m1_col.plusAssign(m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = 0.0;

	BOOST_CHECK(&m1_col.minusAssign(m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = m2_col(i);

	BOOST_CHECK(&(m1_col = m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK(&(m1_col = m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = 0.0f;

	BOOST_CHECK(&(m1_col = Vector<float>(4, 0.0f)) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = m2_col(i);

	BOOST_CHECK(&(m1_col = m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW((m1_col = m4_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW((m1_col = Vector<float>(2, 0.0f)), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW((m1_col = Vector<int>(5, 0)), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) += values1(i, 2);

	BOOST_CHECK(&(m1_col += m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = m2_col(i);

	BOOST_CHECK(&m1_col.assign(m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK(&m1_col.assign(m1_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = 1;

	BOOST_CHECK(&m1_col.assign(ScalarVector<int>(4, 1)) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	for (SizeType1 i = 0; i < values1.getSize1(); i++)
		values1(i, 2) = m2_col(i);

	BOOST_CHECK(&m1_col.assign(m2_col) == &m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.assign(m4_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.assign(Vector<float>(5, 0.0f)), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	BOOST_CHECK_THROW(m1_col.assign(Vector<double>(0)), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);

	// ---------
	
	m1 = m2;
	values1 = m1;

	Matrix<double> values1_swp(values1);
	Matrix<double> values2(m2);
	Matrix<double> values2_swp(values2);

	for (SizeType1 i = 0; i < values1_swp.getSize1(); i++)
		std::swap(values1_swp(i, 2), values2_swp(i, 0));

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m2_col, m2, 0, &values2);

	swap(m1_col, m2_col);

	checkMatrixColumn(m1_col, m1, 2, &values1_swp);
	checkMatrixColumn(m2_col, m2, 0, &values2_swp);

	swap(m1_col, m2_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m2_col, m2, 0, &values2);

	swap(m2_col, m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1_swp);
	checkMatrixColumn(m2_col, m2, 0, &values2_swp);

	swap(m2_col, m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m2_col, m2, 0, &values2);

	m1_col.swap(m2_col);

	checkMatrixColumn(m1_col, m1, 2, &values1_swp);
	checkMatrixColumn(m2_col, m2, 0, &values2_swp);

	m1_col.swap(m2_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m2_col, m2, 0, &values2);

	m2_col.swap(m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1_swp);
	checkMatrixColumn(m2_col, m2, 0, &values2_swp);

	m2_col.swap(m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m2_col, m2, 0, &values2);

	// ---------

	Matrix<double> m6(m4);
	Matrix<double> values3(m4);
	MatrixColumn<Matrix<double> > m6_col(m6, 4);

	checkMatrixColumn(m6_col, m6, 4, &values3);

	BOOST_CHECK_THROW(m1_col.swap(m6_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m6_col, m6, 4, &values3);

	BOOST_CHECK_THROW(swap(m1_col, m6_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m6_col, m6, 4, &values3);

	BOOST_CHECK_THROW(m6_col.swap(m1_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m6_col, m6, 4, &values3);

	BOOST_CHECK_THROW(swap(m6_col, m1_col), Base::SizeError);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	checkMatrixColumn(m6_col, m6, 4, &values3);

	// ---------

	m1_col.swap(m1_col);

	checkMatrixColumn(m1_col, m1, 2, &values1);
	
	swap(m6_col, m6_col);

	checkMatrixColumn(m6_col, m6, 4, &values3);
}

BOOST_AUTO_TEST_CASE(RowFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m(0, 0);
	const Matrix<double>& const_m_ref = m;

	typedef Matrix<double>::SizeType SizeType;
	typedef const MatrixRow<Matrix<double> > CMR;
	typedef const MatrixRow<const Matrix<double> > CCMR;

	// ---------

	BOOST_CHECK_NO_THROW(row(m, 0));
	BOOST_CHECK_NO_THROW(row(m, 1));
	
	BOOST_CHECK_THROW(row(m, 0)(0), Base::IndexError);
	BOOST_CHECK_THROW(row(m, 0)(1), Base::IndexError);

	m.resize(0, 6);

	BOOST_CHECK_NO_THROW(row(m, 0));
	BOOST_CHECK_NO_THROW(row(m, 1));
	
	BOOST_CHECK_THROW(row(m, 0)(0), Base::IndexError);
	BOOST_CHECK_THROW(row(m, 0)(1), Base::IndexError);

	m.resize(5, 0);

	BOOST_CHECK_NO_THROW(row(m, 0));
	BOOST_CHECK_NO_THROW(row(m, 5));
	BOOST_CHECK_NO_THROW(row(m, 6));

	BOOST_CHECK_THROW(row(m, 0)(0), Base::IndexError);
	BOOST_CHECK_THROW(row(m, 0)(1), Base::IndexError);

	// ---------

	m.resize(5, 6);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			m(i, j) =  i * m.getSize2() + j + i / 10.0;

	// ---------

	checkMatrixRow<CMR>(row(m, 0), m, 0, static_cast<const Matrix<double>*>(0));
	checkMatrixRow<CMR>(row(m, 3), m, 3, static_cast<const Matrix<double>*>(0));
	checkMatrixRow<CMR>(row(m, 4), m, 4, static_cast<const Matrix<double>*>(0));

	BOOST_CHECK_NO_THROW(row(m, 0)(2));

	BOOST_CHECK_THROW(row(m, 0)(6), Base::IndexError);
	BOOST_CHECK_THROW(row(m, 5)(0), Base::IndexError);

	BOOST_CHECK_EQUAL(m(0, 1), 1.0);
	BOOST_CHECK_EQUAL(row(m, 0)(1), 1.0);

	row(m, 0)(1) = -5.0;

	BOOST_CHECK_EQUAL(m(0, 1), -5.0);
	BOOST_CHECK_EQUAL(row(m, 0)(1), -5.0);

	m(0, 1) = 1.0;

	BOOST_CHECK_EQUAL(row(m, 0)(1), 1.0);

	// ---------

	checkMatrixRow<CCMR>(row(const_m_ref, 0), m, 0, static_cast<const Matrix<double>*>(0));
	checkMatrixRow<CCMR>(row(const_m_ref, 3), m, 3, static_cast<const Matrix<double>*>(0));
	checkMatrixRow<CCMR>(row(const_m_ref, 4), m, 4, static_cast<const Matrix<double>*>(0));

	BOOST_CHECK_NO_THROW(row(const_m_ref, 0)(2));

	BOOST_CHECK_THROW(row(const_m_ref, 0)(6), Base::IndexError);
	BOOST_CHECK_THROW(row(const_m_ref, 5)(0), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(ColumnFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m(0, 0);
	const Matrix<double>& const_m_ref = m;

	typedef Matrix<double>::SizeType SizeType;
	typedef const MatrixColumn<Matrix<double> > CMC;
	typedef const MatrixColumn<const Matrix<double> > CCMC;

	// ---------

	BOOST_CHECK_NO_THROW(column(m, 0));
	BOOST_CHECK_NO_THROW(column(m, 1));
	
	BOOST_CHECK_THROW(column(m, 0)(0), Base::IndexError);
	BOOST_CHECK_THROW(column(m, 0)(1), Base::IndexError);

	m.resize(6, 0);

	BOOST_CHECK_NO_THROW(column(m, 0));
	BOOST_CHECK_NO_THROW(column(m, 1));
	
	BOOST_CHECK_THROW(column(m, 0)(0), Base::IndexError);
	BOOST_CHECK_THROW(column(m, 0)(1), Base::IndexError);

	m.resize(0, 5);

	BOOST_CHECK_NO_THROW(column(m, 0));
	BOOST_CHECK_NO_THROW(column(m, 5));
	BOOST_CHECK_NO_THROW(column(m, 6));

	BOOST_CHECK_THROW(column(m, 0)(0), Base::IndexError);
	BOOST_CHECK_THROW(column(m, 0)(1), Base::IndexError);

	// ---------

	m.resize(6, 5);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			m(i, j) =  i * m.getSize2() + j;

	// ---------

	checkMatrixColumn<CMC>(column(m, 0), m, 0, static_cast<const Matrix<double>*>(0));
	checkMatrixColumn<CMC>(column(m, 3), m, 3, static_cast<const Matrix<double>*>(0));
	checkMatrixColumn<CMC>(column(m, 4), m, 4, static_cast<const Matrix<double>*>(0));

	BOOST_CHECK_NO_THROW(column(m, 0)(2));

	BOOST_CHECK_THROW(column(m, 0)(6), Base::IndexError);
	BOOST_CHECK_THROW(column(m, 5)(0), Base::IndexError);

	BOOST_CHECK_EQUAL(m(1, 0), 5.0);
	BOOST_CHECK_EQUAL(column(m, 0)(1), 5.0);

	column(m, 0)(1) = -2.23;

	BOOST_CHECK_EQUAL(m(1, 0), -2.23);
	BOOST_CHECK_EQUAL(column(m, 0)(1), -2.23);

	m(1, 0) = 5.0;

	BOOST_CHECK_EQUAL(column(m, 0)(1), 5.0);

	// ---------

	checkMatrixColumn<CCMC>(column(const_m_ref, 0), m, 0, static_cast<const Matrix<double>*>(0));
	checkMatrixColumn<CCMC>(column(const_m_ref, 3), m, 3, static_cast<const Matrix<double>*>(0));
	checkMatrixColumn<CCMC>(column(const_m_ref, 4), m, 4, static_cast<const Matrix<double>*>(0));

	BOOST_CHECK_NO_THROW(column(const_m_ref, 0)(2));

	BOOST_CHECK_THROW(column(const_m_ref, 0)(6), Base::IndexError);
	BOOST_CHECK_THROW(column(const_m_ref, 5)(0), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(MatrixRangeTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixRange<Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(MatrixRange<Matrix<double> >::ValueType));
	BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(MatrixRange<Matrix<double> >::SizeType));
	BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(MatrixRange<Matrix<double> >::DifferenceType));
	BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(MatrixRange<Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixRange<Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixRange<const Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixRange<const Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(const Matrix<double>) == typeid(MatrixRange<const Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixRange<Matrix<double> >::MatrixType));

	BOOST_CHECK(typeid(Range<Matrix<double>::SizeType>) == typeid(MatrixRange<Matrix<double> >::RangeType));
	BOOST_CHECK(typeid(Range<Matrix<double>::SizeType>) == typeid(MatrixRange<const Matrix<double> >::RangeType));

	// ---------

	typedef Matrix<double>::SizeType SizeType1;
	typedef MatrixRange<Matrix<double> >::RangeType RangeType1;

	Matrix<double> m1;
	RangeType1 r_rng1(1, 4);
	RangeType1 c_rng1(0, 3);
	MatrixRange<Matrix<double> > m1_rng(m1, r_rng1, c_rng1);

	BOOST_CHECK(&m1_rng.getData().getData() == &m1);
	BOOST_CHECK(&const_cast<const MatrixRange<Matrix<double> >&>(m1_rng).getData().getData() == &m1);

	// ---------

	BOOST_CHECK_THROW(m1_rng(0, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(0, 0), Base::IndexError);

	m1.resize(1, 0, true, 1.1);

	BOOST_CHECK_THROW(m1_rng(0, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(0, 0), Base::IndexError);

	m1.resize(3, 2, true, 2.2);

	BOOST_CHECK_THROW(m1_rng(2, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(2, 0), Base::IndexError);

	BOOST_CHECK_NO_THROW(m1_rng(0, 0));
	BOOST_CHECK_NO_THROW(m1_rng(1, 1));

	BOOST_CHECK_NO_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(0, 0));
	BOOST_CHECK_NO_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(1, 1));

	m1.resize(4, 2, true, 4.4);

	BOOST_CHECK_THROW(m1_rng(2, 2), Base::IndexError);
	BOOST_CHECK_THROW(m1_rng(3, 1), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(2, 2), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(3, 1), Base::IndexError);

	BOOST_CHECK_NO_THROW(m1_rng(2, 1));

	BOOST_CHECK_NO_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(2, 1));

	m1.resize(4, 3, true, 5.5);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, static_cast<Matrix<double>*>(0));

	m1.resize(1, 1, true, 5.5);

	BOOST_CHECK_THROW(m1_rng(0, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixRange<Matrix<double> >&>(m1_rng)(0, 0), Base::IndexError);

	// ---------

	m1.resize(5, 5, true);

	Matrix<double> values1(m1);

	m1_rng(0, 0) = -100.0;
	m1_rng.getData()(2, 1) = -200.0;
	m1_rng(2, 2) = -3.33;

	values1(1, 0) = -100.0;
	values1(2, 1) = -200.0;
	values1(3, 2) = -3.33;

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			m1(i, j) = i * m1.getSize2() + j + 1;

	values1 = m1;

	Matrix<double> values2(3, 3);

	for (SizeType1 i = 0; i < 3; i++)
		for (SizeType1 j = 0; j < 3; j++)
			values2(i, j) = m1(i + 1, j);

	Matrix<double> m2(m1_rng);
	RangeType1 r_rng2(0, 3);
	RangeType1 c_rng2(0, 3);
	MatrixRange<Matrix<double> > m2_rng(m2, r_rng2, c_rng2);

	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	// ---------

	Matrix<double> m3(m1);
	RangeType1 r_rng3(0, 5);
	RangeType1 c_rng3(1, 3);
	MatrixRange<Matrix<double> > m3_rng(m3, r_rng3, c_rng3);
	MatrixRange<Matrix<double> > m3_rng_tmp(m3_rng);

	checkMatrixRange(m3_rng, m3, r_rng3, c_rng3, &values1);
	checkMatrixRange(m3_rng_tmp, m3, r_rng3, c_rng3, &values1);

	// ---------

	Matrix<double> m4(m1);
	RangeType1 r_rng4(2, 2);
	RangeType1 c_rng4(6, 6);
	MatrixRange<Matrix<double> > m4_rng(m4, r_rng4, c_rng4);

	checkMatrixRange(m4_rng, m4, r_rng4, c_rng4, &values1);

	// ---------

	Matrix<double> m5(m1);
	RangeType1 r_rng5(0, 2);
	RangeType1 c_rng5(2, 4);
	MatrixRange<const Matrix<double> > m5_rng(m5, r_rng5, c_rng5);

	checkMatrixRange(m5_rng, m5, r_rng5, c_rng5, &values1);

	// ---------

	MatrixRange<MatrixRange<const Matrix<double> > > m6_rng(m5_rng, r_rng5, r_rng5);
	CMatrix<double, 2, 2> values5;

	values5(0, 0) = m5(0, 2);
	values5(1, 0) = m5(1, 2);
	values5(0, 1) = m5(0, 3);
	values5(1, 1) = m5(1, 3);

	checkMatrixRange(m6_rng, m5_rng, r_rng5, r_rng5, &values5);

	BOOST_CHECK(&m6_rng.getData().getData().getData() == &m5);
	BOOST_CHECK(&const_cast<const MatrixRange<MatrixRange<const Matrix<double> > >&>(m6_rng).getData().getData().getData() == &m5);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) *= -2.12;

	BOOST_CHECK(&(m1_rng *= -2.12) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) /= -1.112;

	BOOST_CHECK(&(m1_rng /= -1.112) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) += m2(i, j);

	BOOST_CHECK(&(m1_rng += m2) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng += m1, Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng += Matrix<float>(2, 2), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------
	
	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) -= m2(i, j);

	BOOST_CHECK(&(m1_rng -= m2) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng -= m5_rng, Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng -= Matrix<int>(4, 3), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) += values1(r_rng1(i), c_rng1(j));

	BOOST_CHECK(&(m1_rng += m1_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------
	
	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = 0.0;

	BOOST_CHECK(&(m1_rng -= m1_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) += m2(i, j) * -2.12;

	BOOST_CHECK(&(m1_rng += m2 * -2.12) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) -= m2_rng(i, j);

	BOOST_CHECK(&(m1_rng -= m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) += m2(i, j);

	BOOST_CHECK(&m1_rng.plusAssign(m2) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.plusAssign(m1), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.plusAssign(Matrix<float>()), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) -= m2(i, j);

	BOOST_CHECK(&m1_rng.minusAssign(m2) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.minusAssign(m5_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.minusAssign(Matrix<int>(2, 1)), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) += m1_rng(i, j);

	BOOST_CHECK(&m1_rng.plusAssign(m1_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) -= m1_rng(i, j);

	BOOST_CHECK(&m1_rng.minusAssign(m1_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) += m2_rng(i, j);

	BOOST_CHECK(&m1_rng.plusAssign(m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) -= m2_rng(i, j);

	BOOST_CHECK(&m1_rng.minusAssign(m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	m2 *= 1.1123;
	values2 *= 1.1123;

	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = m2_rng(i, j);

	BOOST_CHECK(&(m1_rng = m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK(&(m1_rng = m1_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = 1.0f;

	BOOST_CHECK(&(m1_rng = ScalarMatrix<float>(r_rng1.getSize(), c_rng1.getSize(), 1.0f)) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = m2_rng(i, j);

	BOOST_CHECK(&(m1_rng = m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW((m1_rng = m3_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW((m1_rng = Matrix<float>(2, 3, 0.0f)), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW((m1_rng = Matrix<int>(5, 0, 0)), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = -1.12;

	BOOST_CHECK(&(m1_rng = ScalarMatrix<double>(r_rng1.getSize(), c_rng1.getSize(), -1.12)) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = m2_rng(i, j);

	BOOST_CHECK(&m1_rng.assign(m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK(&m1_rng.assign(m1_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = -3;

	BOOST_CHECK(&m1_rng.assign(Matrix<int>(3, 3, -3)) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			values1(r_rng1(i), c_rng1(j)) = m2_rng(i, j);

	BOOST_CHECK(&m1_rng.assign(m2_rng) == &m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.assign(m3_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.assign(Matrix<float>(0, 0)), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	BOOST_CHECK_THROW(m1_rng.assign(Matrix<int>(4, 3, 0)), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);

	// ---------
	
	BOOST_CHECK(m1_rng == m2_rng);

	m1 *= 2.234;
	values1 *= 2.234;

	m2 *= -1.112;
	values2 *= -1.112;
	
	BOOST_CHECK(m1_rng != m2_rng);

	Matrix<double> values1_swp = values1;
	Matrix<double> values2_swp = values2;

	for (SizeType1 i = 0; i < r_rng1.getSize(); i++)
		for (SizeType1 j = 0; j < c_rng1.getSize(); j++)
			std::swap(values1_swp(r_rng1(i), c_rng1(j)), values2_swp(r_rng2(i), c_rng2(j)));

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	swap(m1_rng, m2_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1_swp);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2_swp);

	swap(m1_rng, m2_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	swap(m2_rng, m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1_swp);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2_swp);

	swap(m2_rng, m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	m1_rng.swap(m2_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1_swp);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2_swp);

	m1_rng.swap(m2_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	m2_rng.swap(m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1_swp);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2_swp);

	m2_rng.swap(m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);

	// ---------

	Matrix<double> values3(m3);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m3_rng, m3, r_rng3, c_rng3, &values3);

	BOOST_CHECK_THROW(m1_rng.swap(m3_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m3_rng, m3, r_rng3, c_rng3, &values3);

	BOOST_CHECK_THROW(swap(m1_rng, m3_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m3_rng, m3, r_rng3, c_rng3, &values3);

	BOOST_CHECK_THROW(m3_rng.swap(m1_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m3_rng, m3, r_rng3, c_rng3, &values3);

	BOOST_CHECK_THROW(swap(m3_rng, m1_rng), Base::SizeError);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	checkMatrixRange(m3_rng, m3, r_rng3, c_rng3, &values3);

	// ---------

	m1_rng.swap(m1_rng);

	checkMatrixRange(m1_rng, m1, r_rng1, c_rng1, &values1);
	
	swap(m2_rng, m2_rng);

	checkMatrixRange(m2_rng, m2, r_rng2, c_rng2, &values2);
}

BOOST_AUTO_TEST_CASE(MatrixSliceTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixSlice<Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(MatrixSlice<Matrix<double> >::ValueType));
	BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(MatrixSlice<Matrix<double> >::SizeType));
	BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(MatrixSlice<Matrix<double> >::DifferenceType));
	BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(MatrixSlice<Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixSlice<Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixSlice<const Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixSlice<const Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(const Matrix<double>) == typeid(MatrixSlice<const Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixSlice<Matrix<double> >::MatrixType));

	BOOST_CHECK(typeid(Slice<Matrix<double>::SizeType, Matrix<double>::DifferenceType>) == typeid(MatrixSlice<Matrix<double> >::SliceType));
	BOOST_CHECK(typeid(Slice<Matrix<double>::SizeType, Matrix<double>::DifferenceType>) == typeid(MatrixSlice<const Matrix<double> >::SliceType));

	// ---------

	typedef Matrix<double>::SizeType SizeType1;
	typedef MatrixSlice<Matrix<double> >::SliceType SliceType1;

	Matrix<double> m1;
	SliceType1 r_slc1(1, 1, 3);
	SliceType1 c_slc1(0, 1, 3);
	MatrixSlice<Matrix<double> > m1_slc(m1, r_slc1, c_slc1);

	BOOST_CHECK(&m1_slc.getData().getData() == &m1);
	BOOST_CHECK(&const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc).getData().getData() == &m1);

	// ---------

	BOOST_CHECK_THROW(m1_slc(0, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(0, 0), Base::IndexError);

	m1.resize(1, 0, true, 1.1);

	BOOST_CHECK_THROW(m1_slc(0, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(0, 0), Base::IndexError);

	m1.resize(3, 2, true, 2.2);

	BOOST_CHECK_THROW(m1_slc(2, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(2, 0), Base::IndexError);

	BOOST_CHECK_NO_THROW(m1_slc(0, 0));
	BOOST_CHECK_NO_THROW(m1_slc(1, 1));

	BOOST_CHECK_NO_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(0, 0));
	BOOST_CHECK_NO_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(1, 1));

	m1.resize(4, 2, true, 4.4);

	BOOST_CHECK_THROW(m1_slc(2, 2), Base::IndexError);
	BOOST_CHECK_THROW(m1_slc(3, 1), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(2, 2), Base::IndexError);
	BOOST_CHECK_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(3, 1), Base::IndexError);

	BOOST_CHECK_NO_THROW(m1_slc(2, 1));

	BOOST_CHECK_NO_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(2, 1));

	m1.resize(4, 3, true, 5.5);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, static_cast<Matrix<double>*>(0));

	m1.resize(1, 1, true, 5.5);

	BOOST_CHECK_THROW(m1_slc(0, 0), Base::IndexError);

	BOOST_CHECK_THROW(const_cast<const MatrixSlice<Matrix<double> >&>(m1_slc)(0, 0), Base::IndexError);

	// ---------

	m1.resize(5, 5, true);

	Matrix<double> values1(m1);

	m1_slc(0, 0) = -100.0;
	m1_slc.getData()(2, 1) = -200.0;
	m1_slc(2, 2) = -3.33;

	values1(1, 0) = -100.0;
	values1(2, 1) = -200.0;
	values1(3, 2) = -3.33;

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			m1(i, j) = i * m1.getSize2() + j + 1;

	values1 = m1;

	Matrix<double> values2(3, 3);

	for (SizeType1 i = 0; i < 3; i++)
		for (SizeType1 j = 0; j < 3; j++)
			values2(i, j) = m1(i + 1, j);

	Matrix<double> m2(m1_slc);
	SliceType1 r_slc2(2, -1, 3);
	SliceType1 c_slc2(0, 1, 3);
	MatrixSlice<Matrix<double> > m2_slc(m2, r_slc2, c_slc2);

	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	// ---------

	Matrix<double> m3(m1);
	SliceType1 r_slc3(0, 1, 5);
	SliceType1 c_slc3(4, -2, 2);
	MatrixSlice<Matrix<double> > m3_slc(m3, r_slc3, c_slc3);
	MatrixSlice<Matrix<double> > m3_slc_tmp(m3_slc);

	checkMatrixSlice(m3_slc, m3, r_slc3, c_slc3, &values1);
	checkMatrixSlice(m3_slc_tmp, m3, r_slc3, c_slc3, &values1);

	// ---------

	Matrix<double> m4(m1);
	SliceType1 r_slc4(2, 0, 2);
	SliceType1 c_slc4(6, -5, 0);
	MatrixSlice<Matrix<double> > m4_slc(m4, r_slc4, c_slc4);

	checkMatrixSlice(m4_slc, m4, r_slc4, c_slc4, &values1);

	// ---------

	Matrix<double> m5(m1);
	SliceType1 r_slc5(0, 1, 2);
	SliceType1 c_slc5(2, 1, 2);
	MatrixSlice<const Matrix<double> > m5_slc(m5, r_slc5, c_slc5);

	checkMatrixSlice(m5_slc, m5, r_slc5, c_slc5, &values1);

	// ---------

	MatrixSlice<MatrixSlice<const Matrix<double> > > m6_slc(m5_slc, r_slc5, r_slc5);
	CMatrix<double, 2, 2> values5;

	values5(0, 0) = m5(0, 2);
	values5(1, 0) = m5(1, 2);
	values5(0, 1) = m5(0, 3);
	values5(1, 1) = m5(1, 3);

	checkMatrixSlice(m6_slc, m5_slc, r_slc5, r_slc5, &values5);

	BOOST_CHECK(&m6_slc.getData().getData().getData() == &m5);
	BOOST_CHECK(&const_cast<const MatrixSlice<MatrixSlice<const Matrix<double> > >&>(m6_slc).getData().getData().getData() == &m5);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) *= -2.12;

	BOOST_CHECK(&(m1_slc *= -2.12) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) /= -1.112;

	BOOST_CHECK(&(m1_slc /= -1.112) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) += m2(i, j);

	BOOST_CHECK(&(m1_slc += m2) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc += m1, Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc += Matrix<float>(2, 2), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------
	
	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) -= m2(i, j);

	BOOST_CHECK(&(m1_slc -= m2) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc -= m5_slc, Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc -= Matrix<int>(4, 3), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) += values1(r_slc1(i), c_slc1(j));

	BOOST_CHECK(&(m1_slc += m1_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------
	
	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = 0.0;

	BOOST_CHECK(&(m1_slc -= m1_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) += m2(i, j) * -2.12;

	BOOST_CHECK(&(m1_slc += m2 * -2.12) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) -= m2_slc(i, j);

	BOOST_CHECK(&(m1_slc -= m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) += m2(i, j);

	BOOST_CHECK(&m1_slc.plusAssign(m2) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.plusAssign(m1), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.plusAssign(Matrix<float>()), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) -= m2(i, j);

	BOOST_CHECK(&m1_slc.minusAssign(m2) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.minusAssign(m5_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.minusAssign(Matrix<int>(2, 1)), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) += m1_slc(i, j);

	BOOST_CHECK(&m1_slc.plusAssign(m1_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) -= m1_slc(i, j);

	BOOST_CHECK(&m1_slc.minusAssign(m1_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) += m2_slc(i, j);

	BOOST_CHECK(&m1_slc.plusAssign(m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) -= m2_slc(i, j);

	BOOST_CHECK(&m1_slc.minusAssign(m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	m2 *= 1.1123;
	values2 *= 1.1123;

	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = m2_slc(i, j);

	BOOST_CHECK(&(m1_slc = m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK(&(m1_slc = m1_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = 1.0f;

	BOOST_CHECK(&(m1_slc = ScalarMatrix<float>(r_slc1.getSize(), c_slc1.getSize(), 1.0f)) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = m2_slc(i, j);

	BOOST_CHECK(&(m1_slc = m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW((m1_slc = m3_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW((m1_slc = Matrix<float>(2, 3, 0.0f)), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW((m1_slc = Matrix<int>(5, 0, 0)), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = -1.12;

	BOOST_CHECK(&(m1_slc = ScalarMatrix<double>(r_slc1.getSize(), c_slc1.getSize(), -1.12)) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = m2_slc(i, j);

	BOOST_CHECK(&m1_slc.assign(m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK(&m1_slc.assign(m1_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = -3;

	BOOST_CHECK(&m1_slc.assign(Matrix<int>(3, 3, -3)) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			values1(r_slc1(i), c_slc1(j)) = m2_slc(i, j);

	BOOST_CHECK(&m1_slc.assign(m2_slc) == &m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.assign(m3_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.assign(Matrix<float>(0, 0)), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	BOOST_CHECK_THROW(m1_slc.assign(Matrix<int>(4, 3, 0)), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);

	// ---------
	
	BOOST_CHECK(m1_slc == m2_slc);

	m1 *= 2.234;
	values1 *= 2.234;

	m2 *= -1.112;
	values2 *= -1.112;
	
	BOOST_CHECK(m1_slc != m2_slc);

	Matrix<double> values1_swp = values1;
	Matrix<double> values2_swp = values2;

	for (SizeType1 i = 0; i < r_slc1.getSize(); i++)
		for (SizeType1 j = 0; j < c_slc1.getSize(); j++)
			std::swap(values1_swp(r_slc1(i), c_slc1(j)), values2_swp(r_slc2(i), c_slc2(j)));

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	swap(m1_slc, m2_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1_swp);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2_swp);

	swap(m1_slc, m2_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	swap(m2_slc, m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1_swp);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2_swp);

	swap(m2_slc, m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	m1_slc.swap(m2_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1_swp);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2_swp);

	m1_slc.swap(m2_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	m2_slc.swap(m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1_swp);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2_swp);

	m2_slc.swap(m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);

	// ---------

	Matrix<double> values3(m3);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m3_slc, m3, r_slc3, c_slc3, &values3);

	BOOST_CHECK_THROW(m1_slc.swap(m3_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m3_slc, m3, r_slc3, c_slc3, &values3);

	BOOST_CHECK_THROW(swap(m1_slc, m3_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m3_slc, m3, r_slc3, c_slc3, &values3);

	BOOST_CHECK_THROW(m3_slc.swap(m1_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m3_slc, m3, r_slc3, c_slc3, &values3);

	BOOST_CHECK_THROW(swap(m3_slc, m1_slc), Base::SizeError);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	checkMatrixSlice(m3_slc, m3, r_slc3, c_slc3, &values3);

	// ---------

	m1_slc.swap(m1_slc);

	checkMatrixSlice(m1_slc, m1, r_slc1, c_slc1, &values1);
	
	swap(m2_slc, m2_slc);

	checkMatrixSlice(m2_slc, m2, r_slc2, c_slc2, &values2);
}

BOOST_AUTO_TEST_CASE(MatrixRangeFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m(10, 10);
	const Matrix<double>& const_m_ref = m;

	typedef Matrix<double>::SizeType SizeType;

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			m(i, j) = i * m.getSize2() + j + 1;

	typedef const MatrixRange<Matrix<double> > CMR;
	typedef const MatrixRange<const Matrix<double> > CCMR;
	typedef MatrixRange<Matrix<double> >::RangeType RangeType;

	// ---------

	BOOST_CHECK(&range(m, RangeType(0, 10), RangeType(0, 10)).getData().getData() == &m);

	checkMatrixRange<CMR>(range(m, RangeType(0, 10), RangeType(0, 10)), m, RangeType(0, 10), RangeType(0, 10), &m);
	checkMatrixRange<CMR>(range(m, RangeType(0, 5), RangeType(0, 5)), m, RangeType(0, 5), RangeType(0, 5), &m);
	checkMatrixRange<CMR>(range(m, RangeType(0, 0), RangeType(0, 0)), m, RangeType(0, 0), RangeType(0, 0), &m);

	checkMatrixRange<CMR>(range(m, RangeType(1, 10), RangeType(1, 10)), m, RangeType(1, 10), RangeType(1, 10), &m);
	checkMatrixRange<CMR>(range(m, RangeType(2, 5), RangeType(2, 5)), m, RangeType(2, 5), RangeType(2, 5), &m);
	checkMatrixRange<CMR>(range(m, RangeType(3, 3), RangeType(3, 3)), m, RangeType(3, 3), RangeType(3, 3), &m);

	checkMatrixRange<CMR>(range(m, RangeType(10, 10), RangeType(10, 10)), m, RangeType(10, 10), RangeType(10, 10), &m);
	checkMatrixRange<CMR>(range(m, RangeType(11, 11), RangeType(11, 11)), m, RangeType(11, 11), RangeType(11, 11), &m);

	BOOST_CHECK_NO_THROW(range(m, RangeType(5, 8), RangeType(5, 8))(2, 2));
	BOOST_CHECK_THROW(range(m, RangeType(5, 8), RangeType(5, 8))(3, 1), Base::IndexError);
	BOOST_CHECK_NO_THROW(range(m, RangeType(5, 12), RangeType(5, 12))(4, 4));
	BOOST_CHECK_THROW(range(m, RangeType(5, 12), RangeType(5, 12))(5, 4), Base::IndexError);

	BOOST_CHECK_EQUAL(m(3, 3), (3 * m.getSize2() + 3 + 1));

	range(m, RangeType(2, 5), RangeType(2, 5))(1, 1) = -5.0;

	BOOST_CHECK_EQUAL(m(3, 3), -5.0);

	m(3, 3) = 3 * m.getSize2() + 3 + 1;

	// ---------

	BOOST_CHECK(&range(m, 0, 10, 0, 10).getData().getData() == &m);

	checkMatrixRange<CMR>(range(m, 0, 10, 0, 10), m, RangeType(0, 10), RangeType(0, 10), &m);
	checkMatrixRange<CMR>(range(m, 0, 5, 0, 5), m, RangeType(0, 5), RangeType(0, 5), &m);
	checkMatrixRange<CMR>(range(m, 0, 0, 0, 0), m, RangeType(0, 0), RangeType(0, 0), &m);

	checkMatrixRange<CMR>(range(m, 1, 10, 1, 10), m, RangeType(1, 10), RangeType(1, 10), &m);
	checkMatrixRange<CMR>(range(m, 2, 5, 2, 5), m, RangeType(2, 5), RangeType(2, 5), &m);
	checkMatrixRange<CMR>(range(m, 3, 3, 3, 3), m, RangeType(3, 3), RangeType(3, 3), &m);

	checkMatrixRange<CMR>(range(m, 10, 10, 10, 10), m, RangeType(10, 10), RangeType(10, 10), &m);
	checkMatrixRange<CMR>(range(m, 11, 11, 11, 11), m, RangeType(11, 11), RangeType(11, 11), &m);

	BOOST_CHECK_NO_THROW(range(m, 5, 8, 5, 8)(2, 2));
	BOOST_CHECK_THROW(range(m, 5, 8, 5, 8)(1, 3), Base::IndexError);
	BOOST_CHECK_NO_THROW(range(m, 5, 12, 5, 12)(4, 4));
	BOOST_CHECK_THROW(range(m, 5, 12, 5, 12)(5, 2), Base::IndexError);

	BOOST_CHECK_EQUAL(m(3, 3), (3 * m.getSize2() + 3 + 1));

	range(m, 2, 5, 2, 5)(1, 1) = -5.0;

	BOOST_CHECK_EQUAL(m(3, 3), -5.0);

	m(3, 3) = 3 * m.getSize2() + 3 + 1;

	// ---------

	BOOST_CHECK(&range(const_m_ref, RangeType(0, 10), RangeType(0, 10)).getData().getData() == &m);

	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(0, 10), RangeType(0, 10)), m, RangeType(0, 10), RangeType(0, 10), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(0, 5), RangeType(0, 5)), m, RangeType(0, 5), RangeType(0, 5), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(0, 0), RangeType(0, 0)), m, RangeType(0, 0), RangeType(0, 0), &m);

	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(1, 10), RangeType(1, 10)), m, RangeType(1, 10), RangeType(1, 10), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(2, 5), RangeType(2, 5)), m, RangeType(2, 5), RangeType(2, 5), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(3, 3), RangeType(3, 3)), m, RangeType(3, 3), RangeType(3, 3), &m);

	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(10, 10), RangeType(10, 10)), m, RangeType(10, 10), RangeType(10, 10), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, RangeType(11, 11), RangeType(11, 11)), m, RangeType(11, 11), RangeType(11, 11), &m);

	BOOST_CHECK_NO_THROW(range(const_m_ref, RangeType(5, 8), RangeType(5, 8))(2, 2));
	BOOST_CHECK_THROW(range(const_m_ref, RangeType(5, 8), RangeType(5, 8))(1, 3), Base::IndexError);
	BOOST_CHECK_NO_THROW(range(const_m_ref, RangeType(5, 12), RangeType(5, 12))(4, 4));
	BOOST_CHECK_THROW(range(const_m_ref, RangeType(5, 12), RangeType(5, 12))(5, 1), Base::IndexError);

	// ---------

	BOOST_CHECK(&range(const_m_ref, 0, 10, 0, 10).getData().getData() == &m);

	checkMatrixRange<CCMR>(range(const_m_ref, 0, 10, 0, 10), m, RangeType(0, 10), RangeType(0, 10), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, 0, 5, 0, 5), m, RangeType(0, 5), RangeType(0, 5), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, 0, 0, 0, 0), m, RangeType(0, 0), RangeType(0, 0), &m);

	checkMatrixRange<CCMR>(range(const_m_ref, 1, 10, 1, 10), m, RangeType(1, 10), RangeType(1, 10), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, 2, 5, 2, 5), m, RangeType(2, 5), RangeType(2, 5), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, 3, 3, 3, 3), m, RangeType(3, 3), RangeType(3, 3), &m);

	checkMatrixRange<CCMR>(range(const_m_ref, 10, 10, 10, 10), m, RangeType(10, 10), RangeType(10, 10), &m);
	checkMatrixRange<CCMR>(range(const_m_ref, 11, 11, 11, 11), m, RangeType(11, 11), RangeType(11, 11), &m);

	BOOST_CHECK_NO_THROW(range(const_m_ref, 5, 8, 5, 8)(2, 2));
	BOOST_CHECK_THROW(range(const_m_ref, 5, 8, 5, 8)(2, 3), Base::IndexError);
	BOOST_CHECK_NO_THROW(range(const_m_ref, 5, 12, 5, 12)(4, 4));
	BOOST_CHECK_THROW(range(const_m_ref, 5, 12, 5, 12)(5, 4), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(MatrixSliceFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m(10, 10);
	const Matrix<double>& const_m_ref = m;

	typedef Matrix<double>::SizeType SizeType;

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			m(i, j) = i * m.getSize2() + j + 1;

	typedef const MatrixSlice<Matrix<double> > CMS;
	typedef const MatrixSlice<const Matrix<double> > CCMS;
	typedef MatrixSlice<Matrix<double> >::SliceType SliceType;

	// ---------

	BOOST_CHECK(&slice(m, SliceType(0, 1, 10), SliceType(0, 1, 10)).getData().getData() == &m);

	checkMatrixSlice<CMS>(slice(m, SliceType(0, 1, 10), SliceType(0, 1, 10)), m, SliceType(0, 1, 10), SliceType(0, 1, 10), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(0, 2, 5), SliceType(0, 2, 5)), m, SliceType(0, 2, 5), SliceType(0, 2, 5), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(9, -2, 5), SliceType(9, -2, 5)), m, SliceType(9, -2, 5), SliceType(9, -2, 5), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(0, 2, 5), SliceType(0, 1, 5)), m, SliceType(0, 2, 5), SliceType(0, 1, 5), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(0, 1, 0), SliceType(0, 1, 0)), m, SliceType(0, 1, 0), SliceType(0, 1, 0), &m);

	checkMatrixSlice<CMS>(slice(m, SliceType(1, 1, 9), SliceType(1, 1, 9)), m, SliceType(1, 1, 9), SliceType(1, 1, 9), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(9, -1, 9), SliceType(9, -1, 9)), m, SliceType(9, -1, 9), SliceType(9, -1, 9), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(2, 1, 3), SliceType(2, 1, 3)), m, SliceType(2, 1, 3), SliceType(2, 1, 3), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(3, 1, 0), SliceType(3, 1, 0)), m, SliceType(3, 1, 0), SliceType(3, 1, 0), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(3, 0, 20), SliceType(3, 0, 20)), m, SliceType(3, 0, 20), SliceType(3, 0, 20), &m);

	checkMatrixSlice<CMS>(slice(m, SliceType(10, 0, 0), SliceType(10, 0, 0)), m, SliceType(10, 0, 0), SliceType(10, 0, 0), &m);
	checkMatrixSlice<CMS>(slice(m, SliceType(11, 1, 0), SliceType(11, 1, 0)), m, SliceType(11, 1, 0), SliceType(11, 1, 0), &m);

	BOOST_CHECK_NO_THROW(slice(m, SliceType(5, 2, 3), SliceType(5, 2, 3))(2, 2));
	BOOST_CHECK_THROW(slice(m, SliceType(5, 2, 3), SliceType(5, 2, 3))(3, 2), Base::IndexError);
	BOOST_CHECK_NO_THROW(slice(m, SliceType(5, 1, 7), SliceType(5, 1, 7))(4, 4));
	BOOST_CHECK_THROW(slice(m, SliceType(5, 1, 7), SliceType(5, 1, 7))(3, 5), Base::IndexError);

	BOOST_CHECK_EQUAL(m(4, 4), (4 * m.getSize2() + 4 + 1));

	slice(m, SliceType(2, 2, 3), SliceType(2, 2, 3))(1, 1) = -6.0;

	BOOST_CHECK_EQUAL(m(4, 4), -6.0);

	m(4, 4) = 4 * m.getSize2() + 4 + 1;

	// ---------

	BOOST_CHECK(&slice(m, 0, 1, 10, 0, 1, 10).getData().getData() == &m);

	checkMatrixSlice<CMS>(slice(m, 0, 1, 10, 0, 1, 10), m, SliceType(0, 1, 10), SliceType(0, 1, 10), &m);
	checkMatrixSlice<CMS>(slice(m, 0, 2, 5, 0, 2, 5), m, SliceType(0, 2, 5), SliceType(0, 2, 5), &m);
	checkMatrixSlice<CMS>(slice(m, 9, -2, 5, 9, -2, 5), m, SliceType(9, -2, 5), SliceType(9, -2, 5), &m);
	checkMatrixSlice<CMS>(slice(m, 0, 1, 5, 0, 1, 5), m, SliceType(0, 1, 5), SliceType(0, 1, 5), &m);
	checkMatrixSlice<CMS>(slice(m, 0, 1, 0, 0, 1, 0), m, SliceType(0, 1, 0), SliceType(0, 1, 0), &m);

	checkMatrixSlice<CMS>(slice(m, 9, -1, 9, 1, 1, 9), m, SliceType(9, -1, 9), SliceType(1, 1, 9), &m);
	checkMatrixSlice<CMS>(slice(m, 9, -1, 9, 9, -1, 9), m, SliceType(9, -1, 9), SliceType(9, -1, 9), &m);
	checkMatrixSlice<CMS>(slice(m, 2, 1, 3, 2, 1, 3), m, SliceType(2, 1, 3), SliceType(2, 1, 3), &m);
	checkMatrixSlice<CMS>(slice(m, 3, 1, 0, 3, 1, 0), m, SliceType(3, 1, 0), SliceType(3, 1, 0), &m);
	checkMatrixSlice<CMS>(slice(m, 3, 0, 20, 3, 0, 20), m, SliceType(3, 0, 20), SliceType(3, 0, 20), &m);

	checkMatrixSlice<CMS>(slice(m, 10, 0, 0, 10, 0, 0), m, SliceType(10, 0, 0), SliceType(10, 0, 0), &m);
	checkMatrixSlice<CMS>(slice(m, 11, 1, 0, 11, 1, 0), m, SliceType(11, 1, 0), SliceType(11, 1, 0), &m);

	BOOST_CHECK_NO_THROW(slice(m, 5, 2, 3, 5, 2, 3)(2, 2));
	BOOST_CHECK_THROW(slice(m, 5, 2, 3, 5, 2, 3)(3, 0), Base::IndexError);
	BOOST_CHECK_NO_THROW(slice(m, 5, 1, 7, 5, 1, 7)(4, 4));
	BOOST_CHECK_THROW(slice(m, 5, 1, 7, 5, 1, 7)(3, 5), Base::IndexError);

	BOOST_CHECK_EQUAL(m(1, 1), (1 * m.getSize2() + 1 + 1));

	slice(m, SliceType(2, -1, 3), SliceType(2, -1, 3))(1, 1) = -6.0;

	BOOST_CHECK_EQUAL(m(1, 1), -6.0);

	m(1, 1) = 1 * m.getSize2() + 1 + 1;

	// ---------

	BOOST_CHECK(&slice(const_m_ref, SliceType(0, 1, 10), SliceType(0, 1, 10)).getData().getData() == &m);

	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(0, 1, 10), SliceType(0, 1, 10)), m, SliceType(0, 1, 10), SliceType(0, 1, 10), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(0, 1, 5), SliceType(0, 2, 5)), m, SliceType(0, 1, 5), SliceType(0, 2, 5), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(9, -2, 5), SliceType(9, -2, 5)), m, SliceType(9, -2, 5), SliceType(9, -2, 5), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(0, 1, 5), SliceType(0, 1, 5)), m, SliceType(0, 1, 5), SliceType(0, 1, 5), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(0, 1, 0), SliceType(0, 1, 0)), m, SliceType(0, 1, 0), SliceType(0, 1, 0), &m);

	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(1, 1, 9), SliceType(1, 1, 9)), m, SliceType(1, 1, 9), SliceType(1, 1, 9), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(9, -1, 9), SliceType(9, -1, 9)), m, SliceType(9, -1, 9), SliceType(9, -1, 9), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(2, 1, 3), SliceType(2, 1, 3)), m, SliceType(2, 1, 3), SliceType(2, 1, 3), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(2, 1, 3), SliceType(2, 2, 3)), m, SliceType(2, 1, 3), SliceType(2, 2, 3), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(7, -1, 0), SliceType(3, 1, 0)), m, SliceType(7, -1, 0), SliceType(3, 1, 0), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(3, 0, 20), SliceType(3, 0, 20)), m, SliceType(3, 0, 20), SliceType(3, 0, 20), &m);

	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(10, 0, 0), SliceType(10, 0, 0)), m, SliceType(10, 0, 0), SliceType(10, 0, 0), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, SliceType(11, 1, 0), SliceType(11, 1, 0)), m, SliceType(11, 1, 0), SliceType(11, 1, 0), &m);

	BOOST_CHECK_NO_THROW(slice(const_m_ref, SliceType(5, 2, 3), SliceType(5, 2, 3))(2, 2));
	BOOST_CHECK_THROW(slice(const_m_ref, SliceType(5, 2, 3), SliceType(5, 2, 3))(3, 1), Base::IndexError);
	BOOST_CHECK_NO_THROW(slice(const_m_ref, SliceType(5, 1, 7), SliceType(5, 1, 7))(4, 4));
	BOOST_CHECK_THROW(slice(const_m_ref, SliceType(5, 1, 7), SliceType(5, 1, 7))(2, 7), Base::IndexError);

	// ---------

	BOOST_CHECK(&slice(const_m_ref, 0, 1, 10, 0, 1, 10).getData().getData() == &m);

	checkMatrixSlice<CCMS>(slice(const_m_ref, 0, 1, 10, 0, 1, 10), m, SliceType(0, 1, 10), SliceType(0, 1, 10), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 0, 2, 5, 0, 2, 5), m, SliceType(0, 2, 5), SliceType(0, 2, 5), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 9, -2, 5, 9, -2, 5), m, SliceType(9, -2, 5), SliceType(9, -2, 5), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 0, 1, 5, 0, 1, 5), m, SliceType(0, 1, 5), SliceType(0, 1, 5), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 0, 1, 0, 0, 1, 0), m, SliceType(0, 1, 0), SliceType(0, 1, 0), &m);

	checkMatrixSlice<CCMS>(slice(const_m_ref, 1, 1, 9, 1, 1, 9), m, SliceType(1, 1, 9), SliceType(1, 1, 9), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 9, -1, 9, 9, -1, 9), m, SliceType(9, -1, 9), SliceType(9, -1, 9), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 2, 1, 3, 2, 1, 3), m, SliceType(2, 1, 3), SliceType(2, 1, 3), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 3, 1, 0, 3, 1, 0), m, SliceType(3, 1, 0), SliceType(3, 1, 0), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 3, 0, 20, 3, 0, 20), m, SliceType(3, 0, 20), SliceType(3, 0, 20), &m);

	checkMatrixSlice<CCMS>(slice(const_m_ref, 10, 0, 0, 10, 0, 0), m, SliceType(10, 0, 0), SliceType(10, 0, 0), &m);
	checkMatrixSlice<CCMS>(slice(const_m_ref, 11, 1, 0, 11, 1, 0), m, SliceType(11, 1, 0), SliceType(11, 1, 0), &m);

	BOOST_CHECK_NO_THROW(slice(const_m_ref, 5, 2, 3, 5, 2, 3)(2, 2));
	BOOST_CHECK_THROW(slice(const_m_ref, 5, 2, 3, 5, 2, 3)(3, 0), Base::IndexError);
	BOOST_CHECK_NO_THROW(slice(const_m_ref, 5, 1, 7, 5, 1, 7)(4, 4));
	BOOST_CHECK_THROW(slice(const_m_ref, 5, 1, 7, 5, 1, 7)(0, 5), Base::IndexError);
}
