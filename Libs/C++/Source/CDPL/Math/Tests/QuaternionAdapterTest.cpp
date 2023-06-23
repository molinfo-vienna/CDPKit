/* 
 * QuaternionAdapterTest.cpp 
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

#include "CDPL/Math/QuaternionAdapter.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename V, typename Q, typename T>
	void checkValues(V& v, const Q& q, const T& c1, const T& c2 = T(), const T& c3 = T(), const T& c4 = T())
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(v.getSize(), 4);
		BOOST_CHECK_EQUAL(v.isEmpty(), false);

		BOOST_CHECK(&v.getData().getData() == &q);
		BOOST_CHECK(&const_cast<const V&>(v).getData().getData() == &q);

		BOOST_CHECK_EQUAL(q.getC1(), c1);
		BOOST_CHECK_EQUAL(q.getC2(), c2);
		BOOST_CHECK_EQUAL(q.getC3(), c3);
		BOOST_CHECK_EQUAL(q.getC4(), c4);

		BOOST_CHECK_EQUAL(v(0), c1);
		BOOST_CHECK_EQUAL(v(1), c2);
		BOOST_CHECK_EQUAL(v(2), c3);
		BOOST_CHECK_EQUAL(v(3), c4);
		BOOST_CHECK_THROW(v(4), Base::IndexError);

		BOOST_CHECK_EQUAL(const_cast<const V&>(v)(0), c1);
		BOOST_CHECK_EQUAL(const_cast<const V&>(v)(1), c2);
		BOOST_CHECK_EQUAL(const_cast<const V&>(v)(2), c3);
		BOOST_CHECK_EQUAL(const_cast<const V&>(v)(3), c4);
		BOOST_CHECK_THROW(const_cast<const V&>(v)(4), Base::IndexError);

		BOOST_CHECK_EQUAL(v[0], c1);
		BOOST_CHECK_EQUAL(v[1], c2);
		BOOST_CHECK_EQUAL(v[2], c3);
		BOOST_CHECK_EQUAL(v[3], c4);
		BOOST_CHECK_THROW(v[4], Base::IndexError);

		BOOST_CHECK_EQUAL(const_cast<const V&>(v)[0], c1);
		BOOST_CHECK_EQUAL(const_cast<const V&>(v)[1], c2);
		BOOST_CHECK_EQUAL(const_cast<const V&>(v)[2], c3);
		BOOST_CHECK_EQUAL(const_cast<const V&>(v)[3], c4);
		BOOST_CHECK_THROW(const_cast<const V&>(v)[4], Base::IndexError);
	}
}


BOOST_AUTO_TEST_CASE(QuaternionVectorAdapterTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Quaternion<double>) == typeid(QuaternionVectorAdapter<Quaternion<double> >::QuaternionType));
	BOOST_CHECK(typeid(Quaternion<double>::ValueType) == typeid(QuaternionVectorAdapter<Quaternion<double> >::ValueType));
	BOOST_CHECK(typeid(Quaternion<double>::Reference) == typeid(QuaternionVectorAdapter<Quaternion<double> >::Reference));
	BOOST_CHECK(typeid(Quaternion<double>::ConstReference) == typeid(QuaternionVectorAdapter<Quaternion<double> >::ConstReference));
	BOOST_CHECK(typeid(Quaternion<double>::ConstReference) == typeid(QuaternionVectorAdapter<const Quaternion<double> >::Reference));
	BOOST_CHECK(typeid(Quaternion<double>::ConstReference) == typeid(QuaternionVectorAdapter<const Quaternion<double> >::ConstReference));
	BOOST_CHECK(typeid(const Quaternion<double>) == typeid(QuaternionVectorAdapter<const Quaternion<double> >::QuaternionType));
	BOOST_CHECK(typeid(Quaternion<double>) == typeid(QuaternionVectorAdapter<Quaternion<double> >::QuaternionType));

	// ---------

	Quaternion<double> q1(2.0, 2.2, -1.0, 3.0);
	QuaternionVectorAdapter<Quaternion<double> > q1_ad(q1);

	checkValues(q1_ad, q1, 2.0, 2.2, -1.0, 3.0);

	// ---------

	Quaternion<double> q2(q1);
	QuaternionVectorAdapter<Quaternion<double> > q2_ad(q2);

	checkValues(q2_ad, q2, 2.0, 2.2, -1.0, 3.0);

	// ---------

	RealQuaternion<float> q3(-1.1f);
	QuaternionVectorAdapter<RealQuaternion<float> > q3_ad(q3);

	checkValues(q3_ad, q3, -1.1f);

	// ---------

	RealQuaternion<double> q4(4.11);
	QuaternionVectorAdapter<const RealQuaternion<double> > q4_ad(q4);

	checkValues(q4_ad, q4, 4.11);

	// ---------

	Quaternion<double> q5(2.2, 0.0, -1.11, -20.2);
	QuaternionVectorAdapter<const Quaternion<double> > q5_ad(q5);

	checkValues(q5_ad, q5, 2.2, 0.0, -1.11, -20.2);

	// ---------

	QuaternionVectorAdapter<const Quaternion<double> > q6_ad(q5_ad);

	checkValues(q6_ad, q5, 2.2, 0.0, -1.11, -20.2);

	// ---------

	Quaternion<double> q7(0.0);
	QuaternionVectorAdapter<Quaternion<double> > q7_ad(q7);

	checkValues(q7_ad, q7, 0.0);

	q7_ad(0) = 2.0;
	q7_ad(1) = 2.2;
	q7_ad[2] = -1.0;
	q7_ad[3] = 3.0;

	checkValues(q7_ad, q7, 2.0, 2.2, -1.0, 3.0);

	q7_ad.getData().set(4.0, 3.0, 1.0, -2.0);

	checkValues(q7_ad, q7, 4.0, 3.0, 1.0, -2.0);

	// ---------

	BOOST_CHECK(&(q1_ad *= 0.0) == &q1_ad);

	checkValues(q1_ad, q1, 0.0);

	q1 = q2;

	BOOST_CHECK(&(q1_ad *= 2.0) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 * 2.0, 2.2 * 2.0, -1.0 * 2.0, 3.0 * 2.0);

	BOOST_CHECK(&(q1_ad *= -1) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 * 2.0 * -1, 2.2 * 2.0 * -1, -1.0 * 2.0 * -1, 3.0 * 2.0 * -1);

	// ---------

	BOOST_CHECK(&(q1_ad /= -2.0f) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 * 2.0 * -1 / -2.0f, 2.2 * 2.0 * -1 / -2.0f, 
				-1.0 * 2.0 * -1 / -2.0f, 3.0 * 2.0 * -1 / -2.0f);

	BOOST_CHECK(&(q1_ad /= 4.17) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 * 2.0 * -1 / -2.0f / 4.17, 2.2 * 2.0 * -1 / -2.0f / 4.17, 
				-1.0 * 2.0 * -1 / -2.0f / 4.17, 3.0 * 2.0 * -1 / -2.0f / 4.17);

	// ---------

	q1 = q2;

	BOOST_CHECK(&(q1_ad += q1_ad) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 + 2.0, 2.2 + 2.2, -1.0 - 1.0, 3.0 + 3.0);

	BOOST_CHECK(&(q1_ad += q2_ad) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 2.0, 2.2 + 2.2 + 2.2, -1.0 - 1.0 - 1.0, 3.0 + 3.0 + 3.0);

	BOOST_CHECK(&(q1_ad += vec(14.123f, 4.2f, -2.22f, 0.01f)) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 2.0 + 14.123f, 2.2 + 2.2 + 2.2 + 4.2f, 
				-1.0 - 1.0 - 1.0 - 2.22f, 3.0 + 3.0 + 3.0 + 0.01f);

	BOOST_CHECK_THROW((q1_ad += vec(14.123f, 4.2f, -2.22f)), Base::SizeError);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 2.0 + 14.123f, 2.2 + 2.2 + 2.2 + 4.2f, 
				-1.0 - 1.0 - 1.0 - 2.22f, 3.0 + 3.0 + 3.0 + 0.01f);

	BOOST_CHECK_THROW((q1_ad += Vector<int>(5, 8)), Base::SizeError);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 2.0 + 14.123f, 2.2 + 2.2 + 2.2 + 4.2f, 
				-1.0 - 1.0 - 1.0 - 2.22f, 3.0 + 3.0 + 3.0 + 0.01f);

	// ---------

	BOOST_CHECK(&(q1_ad -= q1_ad) == &q1_ad);

	checkValues(q1_ad, q1, 0.0);

	BOOST_CHECK(&(q1_ad -= q2_ad) == &q1_ad);

	checkValues(q1_ad, q1, -2.0, -2.2, 1.0, -3.0);

	BOOST_CHECK(&(q1_ad -= Vector<int>(4, -6)) == &q1_ad);

	checkValues(q1_ad, q1, -2.0 + 6, -2.2 + 6, 1.0 + 6, -3.0 + 6);

	BOOST_CHECK_THROW((q1_ad -= vec(14.123, -4.2, 2)), Base::SizeError);

	checkValues(q1_ad, q1, -2.0 + 6, -2.2 + 6, 1.0 + 6, -3.0 + 6);

	BOOST_CHECK_THROW((q1_ad -= Vector<float>(5, 2.12)), Base::SizeError);

	checkValues(q1_ad, q1, -2.0 + 6, -2.2 + 6, 1.0 + 6, -3.0 + 6);

	// ---------

	q1 = q2;

	checkValues(q1_ad, q1, 2.0, 2.2, -1.0, 3.0);

	BOOST_CHECK(&q1_ad.plusAssign(q1_ad) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 + 2.0, 2.2 + 2.2, -1.0 - 1.0, 3.0 + 3.0);

	BOOST_CHECK(&q1_ad.plusAssign(q7_ad) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 4.0, 2.2 + 2.2 + 3.0, -1.0 - 1.0 + 1.0, 3.0 + 3.0 - 2.0);

	BOOST_CHECK(&q1_ad.plusAssign(vec(14.123f, 4.2f, -2.22f, 1.112f)) == &q1_ad);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 4.0 + 14.123f, 2.2 + 2.2 + 3.0 + 4.2f, -1.0 - 1.0 + 1.0 - 2.22f, 3.0 + 3.0 - 2.0 + 1.112f);

	BOOST_CHECK_THROW(q1_ad.plusAssign(vec(3, 1)), Base::SizeError);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 4.0 + 14.123f, 2.2 + 2.2 + 3.0 + 4.2f, -1.0 - 1.0 + 1.0 - 2.22f, 3.0 + 3.0 - 2.0 + 1.112f);

	BOOST_CHECK_THROW(q1_ad.plusAssign(Vector<double>(5)), Base::SizeError);

	checkValues(q1_ad, q1, 2.0 + 2.0 + 4.0 + 14.123f, 2.2 + 2.2 + 3.0 + 4.2f, -1.0 - 1.0 + 1.0 - 2.22f, 3.0 + 3.0 - 2.0 + 1.112f);

	// ---------

	BOOST_CHECK(&q1_ad.minusAssign(q1_ad) == &q1_ad);

	checkValues(q1_ad, q1, 0.0);

	BOOST_CHECK(&q1_ad.minusAssign(q2_ad) == &q1_ad);

	checkValues(q1_ad, q1, -2.0, -2.2, 1.0, -3.0);

	BOOST_CHECK(&q1_ad.minusAssign(Vector<int>(4, -6)) == &q1_ad);

	checkValues(q1_ad, q1, -2.0 + 6, -2.2 + 6, 1.0 + 6, -3.0 + 6);

	BOOST_CHECK_THROW(q1_ad.minusAssign(vec(14.123, -4.2, 2)), Base::SizeError);

	checkValues(q1_ad, q1, -2.0 + 6, -2.2 + 6, 1.0 + 6, -3.0 + 6);

	BOOST_CHECK_THROW(q1_ad.minusAssign(Vector<float>(5, 2.12)), Base::SizeError);

	checkValues(q1_ad, q1, -2.0 + 6, -2.2 + 6, 1.0 + 6, -3.0 + 6);

	// ---------

	BOOST_CHECK(&(q1_ad = q2_ad) == &q1_ad);

	checkValues(q1_ad, q1, 2.0, 2.2, -1.0, 3.0);

	BOOST_CHECK(&(q1_ad = vec(1.1f, -2.2f, 4.44f, -0.35f)) == &q1_ad);

	checkValues(q1_ad, q1, 1.1f, -2.2f, 4.44f, -0.35f);

	BOOST_CHECK_THROW((q1_ad = Vector<float>(5, 2.12)), Base::SizeError);

	checkValues(q1_ad, q1, 1.1f, -2.2f, 4.44f, -0.35f);

	BOOST_CHECK_THROW((q1_ad = vec(5, 2.12)), Base::SizeError);

	checkValues(q1_ad, q1, 1.1f, -2.2f, 4.44f, -0.35f);

	// ---------

	BOOST_CHECK(&q1_ad.assign(q4_ad) == &q1_ad);

	checkValues(q1_ad, q1, 4.11);

	BOOST_CHECK(&q1_ad.assign(vec(-1.1, -2.2, -4.44, 0.335)) == &q1_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);

	BOOST_CHECK_THROW(q1_ad.assign(CVector<int, 1>()), Base::SizeError);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);

	BOOST_CHECK_THROW(q1_ad.assign(Vector<double>(5, 2.12)), Base::SizeError);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);

	// ---------
	
	swap(q1_ad, q7_ad);

	checkValues(q7_ad, q7, -1.1, -2.2, -4.44, 0.335);
	checkValues(q1_ad, q1, 4.0, 3.0, 1.0, -2.0);

	swap(q1_ad, q7_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);
	checkValues(q7_ad, q7, 4.0, 3.0, 1.0, -2.0);

	swap(q7_ad, q1_ad);

	checkValues(q7_ad, q7, -1.1, -2.2, -4.44, 0.335);
	checkValues(q1_ad, q1, 4.0, 3.0, 1.0, -2.0);

	swap(q7_ad, q1_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);
	checkValues(q7_ad, q7, 4.0, 3.0, 1.0, -2.0);

	q1_ad.swap(q7_ad);

	checkValues(q7_ad, q7, -1.1, -2.2, -4.44, 0.335);
	checkValues(q1_ad, q1, 4.0, 3.0, 1.0, -2.0);

	q1_ad.swap(q7_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);
	checkValues(q7_ad, q7, 4.0, 3.0, 1.0, -2.0);

	q7_ad.swap(q1_ad);

	checkValues(q7_ad, q7, -1.1, -2.2, -4.44, 0.335);
	checkValues(q1_ad, q1, 4.0, 3.0, 1.0, -2.0);

	q7_ad.swap(q1_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);
	checkValues(q7_ad, q7, 4.0, 3.0, 1.0, -2.0);

	q1_ad.swap(q1_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);

	swap(q7_ad, q7_ad);

	checkValues(q1_ad, q1, -1.1, -2.2, -4.44, 0.335);
}

BOOST_AUTO_TEST_CASE(QuaternionVecFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	typedef const QuaternionVectorAdapter<Quaternion<double> > CQVA;
	typedef const QuaternionVectorAdapter<const Quaternion<double> > CCQVA;

	Quaternion<double> q1(-1.11, 2.0, 3.0, 4.0);

	checkValues<CQVA>(vec(q1), q1, -1.11, 2.0, 3.0, 4.0);

	const Quaternion<double>& q1_cref = q1;

	checkValues<CCQVA>(vec(q1_cref), q1_cref, -1.11, 2.0, 3.0, 4.0);

	// ---------

	checkValues<CQVA>((vec(q1) += vec(0.1, 0.2, 0.3, -0.4)), q1, -1.11 + 0.1, 2.0 + 0.2, 3.0 + 0.3, 4.0 + -0.4);
}
