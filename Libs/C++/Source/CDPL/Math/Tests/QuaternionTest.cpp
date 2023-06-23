/* 
 * QuaternionTest.cpp 
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

#include "CDPL/Math/Quaternion.hpp"


namespace
{

	template <typename Q, typename T>
	void checkValues1(Q& quat, const T& c1, const T& c2 = T(), const T& c3 = T(), const T& c4 = T())
	{
		BOOST_CHECK_EQUAL(quat.getC1(), c1);
		BOOST_CHECK_EQUAL(quat.getC2(), c2);
		BOOST_CHECK_EQUAL(quat.getC3(), c3);
		BOOST_CHECK_EQUAL(quat.getC4(), c4);

		BOOST_CHECK_EQUAL(quat.getData()[0], c1);
		BOOST_CHECK_EQUAL(quat.getData()[1], c2);
		BOOST_CHECK_EQUAL(quat.getData()[2], c3);
		BOOST_CHECK_EQUAL(quat.getData()[3], c4);

		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC1(), c1);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC2(), c2);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC3(), c3);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC4(), c4);

		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getData()[0], c1);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getData()[1], c2);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getData()[2], c3);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getData()[3], c4);
	}

	template <typename Q, typename T>
	void checkValues2(Q& quat, const T& r)
	{
		BOOST_CHECK_EQUAL(quat.getC1(), r);
		BOOST_CHECK_EQUAL(quat.getC2(), T());
		BOOST_CHECK_EQUAL(quat.getC3(), T());
		BOOST_CHECK_EQUAL(quat.getC4(), T());

		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC1(), r);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC2(), T());
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC3(), T());
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC4(), T());
	}

	template <typename Q, typename T>
	void checkValues3(Q& quat, const T& c1, const T& c2 = T(), const T& c3 = T(), const T& c4 = T())
	{
		BOOST_CHECK_EQUAL(quat.getC1(), c1);
		BOOST_CHECK_EQUAL(quat.getC2(), c2);
		BOOST_CHECK_EQUAL(quat.getC3(), c3);
		BOOST_CHECK_EQUAL(quat.getC4(), c4);
	
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC1(), c1);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC2(), c2);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC3(), c3);
		BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC4(), c4);
	}
}


BOOST_AUTO_TEST_CASE(QuaternionTest)
{
	using namespace CDPL;
	using namespace Math;

	Quaternion<double> q1;

	checkValues1(q1, q1.getC1(), q1.getC2(), q1.getC3(), q1.getC4());

	Quaternion<double> q2(-1.47);

	checkValues1(q2, -1.47);

	Quaternion<double> q3(1.47, 2.1);

	checkValues1(q3, 1.47, 2.1);

	Quaternion<double> q4(1.1, -2.1, 3.2);

	checkValues1(q4, 1.1, -2.1, 3.2);

	Quaternion<double> q5(-1.02, 2.21, -3.0, 4.4);

	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	Quaternion<double> q6(q5);

	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q6, -1.02, 2.21, -3.0, 4.4);

	Quaternion<double> q7(static_cast<const QuaternionExpression<Quaternion<double> >&>(q3));

	checkValues1(q3, 1.47, 2.1);
	checkValues1(q7, 1.47, 2.1);

	// ---------

	q1.set();

	checkValues1(q1, 0.0);

	q1.set(-1.0);

	checkValues1(q1, -1.0);

	q1.set(1.1, 2.1);

	checkValues1(q1, 1.1, 2.1);

	q1.set(0.0, -1.1, 0.05);

	checkValues1(q1, 0.0, -1.1, 0.05);

	q1.set(20.12, 1.13, 1.15, -4.44);

	checkValues1(q1, 20.12, 1.13, 1.15, -4.44);

	// ---------

	BOOST_CHECK(&(q1 = q5) == &q1);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1 = static_cast<const QuaternionContainer<Quaternion<double> >&>(q4)) == &q1);

	checkValues1(q1, 1.1, -2.1, 3.2);
	checkValues1(q4, 1.1, -2.1, 3.2);

	BOOST_CHECK(&(q1 = static_cast<const QuaternionExpression<Quaternion<double> >&>(q5)) == &q1);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1 = q1) == &q1);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1 = 2.3) == &q1);

	checkValues1(q1, 2.3);

	// ---------

	BOOST_CHECK(&(q1 -= q1) == &q1);

	checkValues1(q1, 0.0);

	BOOST_CHECK(&(q1 -= q5) == &q1);

	checkValues1(q1, 1.02, -2.21, 3.0, -4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1 -= static_cast<const QuaternionContainer<Quaternion<double> >&>(q4)) == &q1);

	checkValues1(q1, 1.02 - 1.1, -2.21 - -2.1, 3.0 - 3.2, -4.4 - 0.0);
	checkValues1(q4, 1.1, -2.1, 3.2);

	BOOST_CHECK(&(q1 -= static_cast<const QuaternionExpression<Quaternion<double> >&>(q5)) == &q1);

	checkValues1(q1, 1.02 - 1.1 - -1.02, -2.21 - -2.1 - 2.21, 3.0 - 3.2 - -3.0, -4.4 - 0.0 - 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1 -= -4.13f) == &q1);

	checkValues1(q1, 1.02 - 1.1 - -1.02 - -4.13f, -2.21 - -2.1 - 2.21, 3.0 - 3.2 - -3.0, -4.4 - 0.0 - 4.4);

	// ---------

	BOOST_CHECK(&(q1 = q5) == &q1);
	BOOST_CHECK(&(q1 += q1) == &q1);

	checkValues1(q1, -1.02 + -1.02, 2.21 + 2.21, -3.0 + -3.0, 4.4 + 4.4);

	BOOST_CHECK(&(q1 += q4) == &q1);

	checkValues1(q1, -1.02 + -1.02 + 1.1, 2.21 + 2.21 + -2.1, -3.0 + -3.0 + 3.2, 4.4 + 4.4 + 0.0);
	checkValues1(q4, 1.1, -2.1, 3.2);

	BOOST_CHECK(&(q1 += static_cast<const QuaternionContainer<Quaternion<double> >&>(q3)) == &q1);

	checkValues1(q1, -1.02 + -1.02 + 1.1 + 1.47, 2.21 + 2.21 + -2.1 + 2.1, -3.0 + -3.0 + 3.2 + 0.0, 4.4 + 4.4 + 0.0 + 0.0);
	checkValues1(q3, 1.47, 2.1);

	BOOST_CHECK(&(q1 += static_cast<const QuaternionExpression<Quaternion<double> >&>(q5)) == &q1);

	checkValues1(q1, -1.02 + -1.02 + 1.1 + 1.47 + -1.02, 2.21 + 2.21 + -2.1 + 2.1 + 2.21, 
				-3.0 + -3.0 + 3.2 + 0.0 + -3.0, 4.4 + 4.4 + 0.0 + 0.0 + 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1 += 5.67f) == &q1);

	checkValues1(q1, -1.02 + -1.02 + 1.1 + 1.47 + -1.02 + 5.67f, 2.21 + 2.21 + -2.1 + 2.1 + 2.21, 
				-3.0 + -3.0 + 3.2 + 0.0 + -3.0, 4.4 + 4.4 + 0.0 + 0.0 + 4.4);

	// ---------

	BOOST_CHECK(&(q1.assign(q2)) == &q1);

	checkValues1(q1, -1.47);
	checkValues1(q2, -1.47);

	BOOST_CHECK(&(q1.assign(q1)) == &q1);

	checkValues1(q1, -1.47);

	// ---------

	BOOST_CHECK(&(q1.minusAssign(q1)) == &q1);

	checkValues1(q1, 0.0);

	BOOST_CHECK(&(q1.minusAssign(q5)) == &q1);

	checkValues1(q1, 1.02, -2.21, 3.0, -4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);

	// ---------

	BOOST_CHECK(&(q1.plusAssign(q1)) == &q1);

	checkValues1(q1, 1.02 + 1.02, -2.21 + -2.21, 3.0 + 3.0, -4.4 + -4.4);

	BOOST_CHECK(&(q1.plusAssign(q3)) == &q1);

	checkValues1(q1, 1.02 + 1.02 + 1.47, -2.21 + -2.21 + 2.1, 3.0 + 3.0 + 0.0, -4.4 + -4.4 + 0.0);
	checkValues1(q3, 1.47, 2.1);

	// ---------

	BOOST_CHECK(&(q1 *= 0) == &q1);

	checkValues1(q1, 0.0);

	q1.set(5.27, 1.1, 1.2, -1.3);

	BOOST_CHECK(&(q1 *= 2) == &q1);

	checkValues1(q1, 5.27 * 2, 1.1 * 2, 1.2 * 2, -1.3 * 2);

	BOOST_CHECK(&(q1 *= -1.0) == &q1);

	checkValues1(q1, 5.27 * 2 * -1.0, 1.1 * 2 * -1.0, 1.2 * 2 * -1.0, -1.3 * 2 * -1.0);

	// ---------

	BOOST_CHECK(&(q1 /= 2) == &q1);

	checkValues1(q1, 5.27 * 2 * -1.0 / 2, 1.1 * 2 * -1.0 / 2, 1.2 * 2 * -1.0 / 2, -1.3 * 2 * -1.0 / 2);

	BOOST_CHECK(&(q1 /= -1) == &q1);

	checkValues1(q1, 5.27 * 2 * -1.0 / 2 / -1, 1.1 * 2 * -1.0 / 2 / -1, 1.2 * 2 * -1.0 / 2 / -1, -1.3 * 2 * -1.0 / 2 / -1);

	// ---------

	BOOST_CHECK(&(q1 *= Quaternion<float>(0)) == &q1);

	checkValues1(q1, 0.0);

	q1.set(-1.0, 1.1, -1.2, 1.3);

	BOOST_CHECK(&(q1 *= Quaternion<double>(1.0)) == &q1);

	checkValues1(q1, -1.0, 1.1, -1.2, 1.3);

	q1.set(2, 0, -6, 3);
	q2.set(1, 3, -2, 2);

	BOOST_CHECK(&(q1 *= q2) == &q1);

	checkValues1(q1, -16.0, 0.0, -1.0, 25.0);

	q1.set(1, 3, -2, 2);
	q2.set(2, 0, -6, 3);

	BOOST_CHECK(&(q1 *= q2) == &q1);

	checkValues1(q1, -16.0, 12.0, -19.0, -11.0);

	q1.set(1.0);

	BOOST_CHECK(&(q1 *= q1) == &q1);

	checkValues1(q1, 1.0);

	// ---------

	q1.set(2.0, -1.0, 2.0, 3.0);
	
	BOOST_CHECK(&(q1 /= Quaternion<double>(1.0)) == &q1);

	checkValues1(q1, 2.0, -1.0, 2.0, 3.0);

	BOOST_CHECK(&(q1 /= Quaternion<double>(-1.0)) == &q1);

	checkValues1(q1, -2.0, 1.0, -2.0, -3.0);

	BOOST_CHECK(&(q1 /= q1) == &q1);

	checkValues1(q1, 1.0, 0.0, 0.0, 0.0);

	q1.set(2.0, 3.0, 4.0, 5.0);
	q2.set(3.0, 4.0, 5.0, 6.0);

	BOOST_CHECK(&(q1 /= q2) == &q1);

	checkValues1(q1, 0.79069767441860461, 0.023255813953488372, 0.0, 0.046511627906976744);

	// ---------

	q1.set(0.1, 0.2, -0.3, -0.4);

	q1.swap(q2);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);

	q1.swap(q2);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);

	q2.swap(q1);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);

	q2.swap(q1);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);

	swap(q1, q2);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);

	swap(q1, q2);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);

	swap(q2, q1);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);

	swap(q2, q1);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);

	q1.swap(q1);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);

	swap(q2, q2);

	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);
}

BOOST_AUTO_TEST_CASE(RealQuaternionTest)
{
	using namespace CDPL;
	using namespace Math;

	RealQuaternion<double> q1;

	checkValues2(q1, 0.0);

	RealQuaternion<double> q2(1.47);

	checkValues2(q2, 1.47);

	RealQuaternion<double> q3(q2);

	checkValues2(q3, 1.47);

	RealQuaternion<double> q4(RealQuaternion<int>(2));

	checkValues2(q4, 2);

	// ---------

	BOOST_CHECK(&(q1 = 0.0) == &q1);

	checkValues2(q1, 0.0);

	BOOST_CHECK(&(q1 = -1.0f) == &q1);

	checkValues2(q1, -1.0f);

	// ---------

	BOOST_CHECK(&(q1 = RealQuaternion<float>(0.23f)) == &q1);

	checkValues2(q1, 0.23f);

	BOOST_CHECK(&(q1 = q3) == &q1);

	checkValues2(q1, 1.47);
	checkValues2(q3, 1.47);

	BOOST_CHECK(&(q1 = q1) == &q1);

	checkValues2(q1, 1.47);

	// ---------

	BOOST_CHECK(&(q1 -= q1) == &q1);

	checkValues2(q1, 0.0);

	BOOST_CHECK(&(q1 -= q3) == &q1);

	checkValues2(q1, -1.47);
	checkValues2(q3, 1.47);

	BOOST_CHECK(&(q1 -= RealQuaternion<float>(0.23f)) == &q1);

	checkValues2(q1, -1.47 - 0.23f);

	BOOST_CHECK(&(q1 -= 4) == &q1);

	checkValues2(q1, -1.47 - 0.23f - 4);

	// ---------

	BOOST_CHECK(&(q1 = q3) == &q1);
	BOOST_CHECK(&(q1 += q1) == &q1);

	checkValues2(q1, 1.47 + 1.47);

	BOOST_CHECK(&(q1 += q3) == &q1);

	checkValues2(q1, 1.47 + 1.47 + 1.47);

	BOOST_CHECK(&(q1 += RealQuaternion<int>(-3)) == &q1);

	checkValues2(q1, 1.47 + 1.47 + 1.47 + -3);

	BOOST_CHECK(&(q1 += 5.67f) == &q1);

	checkValues2(q1, 1.47 + 1.47 + 1.47 + -3 + 5.67f);

	// ---------

	BOOST_CHECK(&(q1.assign(q2)) == &q1);

	checkValues2(q1, 1.47);
	checkValues2(q2, 1.47);

	BOOST_CHECK(&(q1.assign(RealQuaternion<int>(-10))) == &q1);

	checkValues2(q1, -10);

	BOOST_CHECK(&(q1.assign(q1)) == &q1);

	checkValues2(q1, -10);

	// ---------

	BOOST_CHECK(&(q1.minusAssign(q1)) == &q1);

	checkValues2(q1, 0.0);

	BOOST_CHECK(&(q1.minusAssign(q3)) == &q1);

	checkValues2(q1, -1.47);
	checkValues2(q3, 1.47);

	BOOST_CHECK(&(q1.minusAssign(RealQuaternion<float>(0.47f))) == &q1);

	checkValues2(q1, -1.47 - 0.47f);

	// ---------

	BOOST_CHECK(&(q1 = 2.3) == &q1);

	BOOST_CHECK(&(q1.plusAssign(q1)) == &q1);

	checkValues2(q1, 2.3 + 2.3);

	BOOST_CHECK(&(q1.plusAssign(q3)) == &q1);

	checkValues2(q1, 2.3 + 2.3 + 1.47);
	checkValues2(q3, 1.47);

	BOOST_CHECK(&(q1.plusAssign(RealQuaternion<float>(-0.47f))) == &q1);

	checkValues2(q1, 2.3 + 2.3 + 1.47 + -0.47f);
	
	BOOST_CHECK(&(q1.plusAssign(RealQuaternion<int>())) == &q1);

	checkValues2(q1, 2.3 + 2.3 + 1.47 + -0.47f);

	// ---------

	BOOST_CHECK(&(q1 *= 0) == &q1);

	checkValues2(q1, 0.0);

	BOOST_CHECK(&(q1 = 5.27) == &q1);
	BOOST_CHECK(&(q1 *= 2) == &q1);

	checkValues2(q1, 5.27 * 2);

	BOOST_CHECK(&(q1 *= -1.0) == &q1);

	checkValues2(q1, 5.27 * 2 * -1.0);

	// ---------

	BOOST_CHECK(&(q1 /= 2.0f) == &q1);

	checkValues2(q1, 5.27 * 2 * -1.0 / 2.0f);

	BOOST_CHECK(&(q1 /= -1.0) == &q1);

	checkValues2(q1, 5.27 * 2 * -1.0 / 2.0f / -1.0);

	// ---------

	BOOST_CHECK(&(q1 *= RealQuaternion<float>(0)) == &q1);

	checkValues2(q1, 0.0);

	BOOST_CHECK(&(q1 = 0.027) == &q1);
	BOOST_CHECK(&(q1 *= RealQuaternion<double>(-1.17)) == &q1);

	checkValues2(q1, 0.027 * -1.17);

	BOOST_CHECK(&(q1 *= q1) == &q1);

	checkValues2(q1, 0.027 * -1.17 * 0.027 * -1.17);

	// ---------

	BOOST_CHECK(&(q1 = -12.23) == &q1);
	
	BOOST_CHECK(&(q1 /= RealQuaternion<double>(1.1)) == &q1);

	checkValues2(q1, -12.23 / 1.1);

	BOOST_CHECK(&(q1 /= RealQuaternion<int>(3)) == &q1);

	checkValues2(q1, -12.23 / 1.1 / 3);

	BOOST_CHECK(&(q1 /= q1) == &q1);

	checkValues2(q1, (-12.23 / 1.1 / 3) / (-12.23 / 1.1 / 3));

	// ---------

	BOOST_CHECK(&(q1 = 0.1) == &q1);

	q1.swap(q2);

	checkValues2(q1, 1.47);
	checkValues2(q2, 0.1);

	q1.swap(q2);

	checkValues2(q1, 0.1);
	checkValues2(q2, 1.47);

	q2.swap(q1);

	checkValues2(q1, 1.47);
	checkValues2(q2, 0.1);

	q2.swap(q1);

	checkValues2(q1, 0.1);
	checkValues2(q2, 1.47);

	swap(q1, q2);

	checkValues2(q1, 1.47);
	checkValues2(q2, 0.1);

	swap(q1, q2);

	checkValues2(q1, 0.1);
	checkValues2(q2, 1.47);

	swap(q2, q1);

	checkValues2(q1, 1.47);
	checkValues2(q2, 0.1);

	swap(q2, q1);

	checkValues2(q1, 0.1);
	checkValues2(q2, 1.47);

	q1.swap(q1);

	checkValues2(q1, 0.1);

	swap(q2, q2);

	checkValues2(q2, 1.47);
}

BOOST_AUTO_TEST_CASE(QuaternionReferenceTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Quaternion<double>) == typeid(QuaternionReference<Quaternion<double> >::QuaternionType));
	BOOST_CHECK(typeid(Quaternion<double>::ValueType) == typeid(QuaternionReference<Quaternion<double> >::ValueType));
	BOOST_CHECK(typeid(Quaternion<double>::Reference) == typeid(QuaternionReference<Quaternion<double> >::Reference));
	BOOST_CHECK(typeid(Quaternion<double>::ConstReference) == typeid(QuaternionReference<Quaternion<double> >::ConstReference));
	BOOST_CHECK(typeid(Quaternion<double>::ConstReference) == typeid(QuaternionReference<const Quaternion<double> >::Reference));
	BOOST_CHECK(typeid(Quaternion<double>::ConstReference) == typeid(QuaternionReference<const Quaternion<double> >::ConstReference));

	// ---------

	Quaternion<double> q1;
	QuaternionReference<Quaternion<double> > q1_ref(q1);

	BOOST_CHECK(&q1_ref.getData() == &q1);
	BOOST_CHECK(&const_cast<const QuaternionReference<Quaternion<double> >&>(q1_ref).getData() == &q1);

	checkValues1(q1, q1.getC1(), q1.getC2(), q1.getC3(), q1.getC4());
	checkValues3(q1_ref, q1.getC1(), q1.getC2(), q1.getC3(), q1.getC4());

	Quaternion<double> q2(-1.47);
	QuaternionReference<Quaternion<double> > q2_ref(q2);

	checkValues1(q2, -1.47);
	checkValues3(q2_ref, -1.47);

	Quaternion<double> q3(1.47, 2.1);
	QuaternionReference<const Quaternion<double> > q3_ref(q3);

	checkValues1(q3, 1.47, 2.1);
	checkValues3(q3_ref, 1.47, 2.1);

	Quaternion<double> q4(1.1, -2.1, 3.2);
	QuaternionReference<const Quaternion<double> > q4_ref(q4);

	checkValues1(q4, 1.1, -2.1, 3.2);
	checkValues3(q4_ref, 1.1, -2.1, 3.2);

	Quaternion<double> q5(-1.02, 2.21, -3.0, 4.4);
	QuaternionReference<Quaternion<double> > q5_ref(q5);

	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	Quaternion<double> q6(q5);
	QuaternionReference<const Quaternion<double> > q6_ref(q6);

	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q6, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q6_ref, -1.02, 2.21, -3.0, 4.4);

	Quaternion<double> q7(static_cast<const QuaternionExpression<Quaternion<double> >&>(q3));
	QuaternionReference<const Quaternion<double> > q7_ref(q7);

	checkValues1(q3, 1.47, 2.1);
	checkValues1(q7, 1.47, 2.1);
	checkValues3(q7_ref, 1.47, 2.1);

	// ---------

	q1_ref.set();

	checkValues1(q1, 0.0);
	checkValues3(q1_ref, 0.0);

	q1_ref.set(-1.0);

	checkValues1(q1, -1.0);
	checkValues3(q1_ref, -1.0);

	q1_ref.getData().set(1.1, 2.1);

	checkValues1(q1, 1.1, 2.1);
	checkValues3(q1_ref, 1.1, 2.1);

	q1_ref.set(0.0, -1.1, 0.05);

	checkValues1(q1, 0.0, -1.1, 0.05);
	checkValues3(q1_ref, 0.0, -1.1, 0.05);

	q1_ref.getData().set(20.12, 1.13, 1.15, -4.44);

	checkValues1(q1, 20.12, 1.13, 1.15, -4.44);
	checkValues3(q1_ref, 20.12, 1.13, 1.15, -4.44);

	// ---------

	BOOST_CHECK(&(q1_ref = q5) == &q1_ref);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref = q5_ref) == &q1_ref);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref = static_cast<const QuaternionContainer<Quaternion<double> >&>(q4)) == &q1_ref);

	checkValues1(q1, 1.1, -2.1, 3.2);
	checkValues1(q4, 1.1, -2.1, 3.2);
	checkValues3(q1_ref, 1.1, -2.1, 3.2);
	checkValues3(q4_ref, 1.1, -2.1, 3.2);

	BOOST_CHECK(&(q1_ref = static_cast<const QuaternionExpression<Quaternion<double> >&>(q5)) == &q1_ref);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref = q1_ref) == &q1_ref);

	checkValues1(q1, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref = 2.3) == &q1_ref);

	checkValues1(q1, 2.3);
	checkValues3(q1, 2.3);

	// ---------

	BOOST_CHECK(&(q1_ref -= q1_ref) == &q1_ref);

	checkValues1(q1, 0.0);
	checkValues3(q1_ref, 0.0);

	BOOST_CHECK(&(q1_ref -= q5_ref) == &q1_ref);

	checkValues1(q1, 1.02, -2.21, 3.0, -4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, 1.02, -2.21, 3.0, -4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref -= static_cast<const QuaternionContainer<Quaternion<double> >&>(q4)) == &q1_ref);

	checkValues1(q1, 1.02 - 1.1, -2.21 - -2.1, 3.0 - 3.2, -4.4 - 0.0);
	checkValues1(q4, 1.1, -2.1, 3.2);
	checkValues3(q1_ref, 1.02 - 1.1, -2.21 - -2.1, 3.0 - 3.2, -4.4 - 0.0);
	checkValues3(q4_ref, 1.1, -2.1, 3.2);

	BOOST_CHECK(&(q1_ref -= static_cast<const QuaternionExpression<Quaternion<double> >&>(q5)) == &q1_ref);

	checkValues1(q1, 1.02 - 1.1 - -1.02, -2.21 - -2.1 - 2.21, 3.0 - 3.2 - -3.0, -4.4 - 0.0 - 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, 1.02 - 1.1 - -1.02, -2.21 - -2.1 - 2.21, 3.0 - 3.2 - -3.0, -4.4 - 0.0 - 4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref -= -4.13f) == &q1_ref);

	checkValues1(q1, 1.02 - 1.1 - -1.02 - -4.13f, -2.21 - -2.1 - 2.21, 3.0 - 3.2 - -3.0, -4.4 - 0.0 - 4.4);
	checkValues3(q1_ref, 1.02 - 1.1 - -1.02 - -4.13f, -2.21 - -2.1 - 2.21, 3.0 - 3.2 - -3.0, -4.4 - 0.0 - 4.4);

	// ---------

	BOOST_CHECK(&(q1_ref = q5) == &q1_ref);
	BOOST_CHECK(&(q1_ref += q1_ref) == &q1_ref);

	checkValues1(q1, -1.02 + -1.02, 2.21 + 2.21, -3.0 + -3.0, 4.4 + 4.4);
	checkValues3(q1_ref, -1.02 + -1.02, 2.21 + 2.21, -3.0 + -3.0, 4.4 + 4.4);

	BOOST_CHECK(&(q1_ref += q4_ref) == &q1_ref);

	checkValues1(q1, -1.02 + -1.02 + 1.1, 2.21 + 2.21 + -2.1, -3.0 + -3.0 + 3.2, 4.4 + 4.4 + 0.0);
	checkValues1(q4, 1.1, -2.1, 3.2);
	checkValues3(q1_ref, -1.02 + -1.02 + 1.1, 2.21 + 2.21 + -2.1, -3.0 + -3.0 + 3.2, 4.4 + 4.4 + 0.0);
	checkValues3(q4_ref, 1.1, -2.1, 3.2);

	BOOST_CHECK(&(q1_ref += static_cast<const QuaternionContainer<Quaternion<double> >&>(q3)) == &q1_ref);

	checkValues1(q1, -1.02 + -1.02 + 1.1 + 1.47, 2.21 + 2.21 + -2.1 + 2.1, -3.0 + -3.0 + 3.2 + 0.0, 4.4 + 4.4 + 0.0 + 0.0);
	checkValues1(q3, 1.47, 2.1);
	checkValues3(q1_ref, -1.02 + -1.02 + 1.1 + 1.47, 2.21 + 2.21 + -2.1 + 2.1, -3.0 + -3.0 + 3.2 + 0.0, 4.4 + 4.4 + 0.0 + 0.0);
	checkValues3(q3_ref, 1.47, 2.1);

	BOOST_CHECK(&(q1_ref += static_cast<const QuaternionExpression<Quaternion<double> >&>(q5)) == &q1_ref);

	checkValues1(q1, -1.02 + -1.02 + 1.1 + 1.47 + -1.02, 2.21 + 2.21 + -2.1 + 2.1 + 2.21, 
				-3.0 + -3.0 + 3.2 + 0.0 + -3.0, 4.4 + 4.4 + 0.0 + 0.0 + 4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, -1.02 + -1.02 + 1.1 + 1.47 + -1.02, 2.21 + 2.21 + -2.1 + 2.1 + 2.21, 
				-3.0 + -3.0 + 3.2 + 0.0 + -3.0, 4.4 + 4.4 + 0.0 + 0.0 + 4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	BOOST_CHECK(&(q1_ref += 5.67f) == &q1_ref);

	checkValues1(q1, -1.02 + -1.02 + 1.1 + 1.47 + -1.02 + 5.67f, 2.21 + 2.21 + -2.1 + 2.1 + 2.21, 
				-3.0 + -3.0 + 3.2 + 0.0 + -3.0, 4.4 + 4.4 + 0.0 + 0.0 + 4.4);
	checkValues3(q1_ref, -1.02 + -1.02 + 1.1 + 1.47 + -1.02 + 5.67f, 2.21 + 2.21 + -2.1 + 2.1 + 2.21, 
				-3.0 + -3.0 + 3.2 + 0.0 + -3.0, 4.4 + 4.4 + 0.0 + 0.0 + 4.4);

	// ---------

	BOOST_CHECK(&(q1_ref.assign(q2)) == &q1_ref);

	checkValues1(q1, -1.47);
	checkValues1(q2, -1.47);
	checkValues3(q1_ref, -1.47);
	checkValues3(q2_ref, -1.47);

	BOOST_CHECK(&(q1_ref.assign(q1_ref)) == &q1_ref);

	checkValues1(q1, -1.47);
	checkValues3(q1_ref, -1.47);

	// ---------

	BOOST_CHECK(&(q1_ref.minusAssign(q1_ref)) == &q1_ref);

	checkValues1(q1, 0.0);
	checkValues3(q1_ref, 0.0);

	BOOST_CHECK(&(q1_ref.minusAssign(q5)) == &q1_ref);

	checkValues1(q1, 1.02, -2.21, 3.0, -4.4);
	checkValues1(q5, -1.02, 2.21, -3.0, 4.4);
	checkValues3(q1_ref, 1.02, -2.21, 3.0, -4.4);
	checkValues3(q5_ref, -1.02, 2.21, -3.0, 4.4);

	// ---------

	BOOST_CHECK(&(q1_ref.plusAssign(q1_ref)) == &q1_ref);

	checkValues1(q1, 1.02 + 1.02, -2.21 + -2.21, 3.0 + 3.0, -4.4 + -4.4);
	checkValues3(q1_ref, 1.02 + 1.02, -2.21 + -2.21, 3.0 + 3.0, -4.4 + -4.4);

	BOOST_CHECK(&(q1_ref.plusAssign(q3)) == &q1_ref);

	checkValues1(q1, 1.02 + 1.02 + 1.47, -2.21 + -2.21 + 2.1, 3.0 + 3.0 + 0.0, -4.4 + -4.4 + 0.0);
	checkValues1(q3, 1.47, 2.1);
	checkValues3(q1_ref, 1.02 + 1.02 + 1.47, -2.21 + -2.21 + 2.1, 3.0 + 3.0 + 0.0, -4.4 + -4.4 + 0.0);
	checkValues3(q3_ref, 1.47, 2.1);

	// ---------

	BOOST_CHECK(&(q1_ref *= 0) == &q1_ref);

	checkValues1(q1, 0.0);
	checkValues3(q1_ref, 0.0);

	q1_ref.set(5.27, 1.1, 1.2, -1.3);

	BOOST_CHECK(&(q1_ref *= 2) == &q1_ref);

	checkValues1(q1, 5.27 * 2, 1.1 * 2, 1.2 * 2, -1.3 * 2);
	checkValues3(q1_ref, 5.27 * 2, 1.1 * 2, 1.2 * 2, -1.3 * 2);

	BOOST_CHECK(&(q1_ref *= -1.0) == &q1_ref);

	checkValues1(q1, 5.27 * 2 * -1.0, 1.1 * 2 * -1.0, 1.2 * 2 * -1.0, -1.3 * 2 * -1.0);
	checkValues3(q1_ref, 5.27 * 2 * -1.0, 1.1 * 2 * -1.0, 1.2 * 2 * -1.0, -1.3 * 2 * -1.0);

	// ---------

	BOOST_CHECK(&(q1_ref /= 2) == &q1_ref);

	checkValues1(q1, 5.27 * 2 * -1.0 / 2, 1.1 * 2 * -1.0 / 2, 1.2 * 2 * -1.0 / 2, -1.3 * 2 * -1.0 / 2);
	checkValues3(q1_ref, 5.27 * 2 * -1.0 / 2, 1.1 * 2 * -1.0 / 2, 1.2 * 2 * -1.0 / 2, -1.3 * 2 * -1.0 / 2);

	BOOST_CHECK(&(q1_ref /= -1) == &q1_ref);

	checkValues1(q1, 5.27 * 2 * -1.0 / 2 / -1, 1.1 * 2 * -1.0 / 2 / -1, 1.2 * 2 * -1.0 / 2 / -1, -1.3 * 2 * -1.0 / 2 / -1);
	checkValues3(q1_ref, 5.27 * 2 * -1.0 / 2 / -1, 1.1 * 2 * -1.0 / 2 / -1, 1.2 * 2 * -1.0 / 2 / -1, -1.3 * 2 * -1.0 / 2 / -1);

	// ---------

	BOOST_CHECK(&(q1_ref *= Quaternion<float>(0)) == &q1_ref);

	checkValues1(q1, 0.0);
	checkValues3(q1_ref, 0.0);

	q1.set(-1.0, 1.1, -1.2, 1.3);

	BOOST_CHECK(&(q1_ref *= Quaternion<double>(1.0)) == &q1_ref);

	checkValues1(q1, -1.0, 1.1, -1.2, 1.3);
	checkValues3(q1_ref, -1.0, 1.1, -1.2, 1.3);

	q1_ref.set(2, 0, -6, 3);
	q2_ref.set(1, 3, -2, 2);

	BOOST_CHECK(&(q1_ref *= q2_ref) == &q1_ref);

	checkValues1(q1, -16.0, 0.0, -1.0, 25.0);
	checkValues3(q1_ref, -16.0, 0.0, -1.0, 25.0);

	q1.set(1, 3, -2, 2);
	q2.set(2, 0, -6, 3);

	BOOST_CHECK(&(q1_ref *= q2) == &q1_ref);

	checkValues1(q1, -16.0, 12.0, -19.0, -11.0);
	checkValues3(q1_ref, -16.0, 12.0, -19.0, -11.0);

	q1_ref.set(1.0);

	BOOST_CHECK(&(q1_ref *= q1_ref) == &q1_ref);

	checkValues1(q1, 1.0);
	checkValues3(q1_ref, 1.0);

	// ---------

	q1_ref.set(2.0, -1.0, 2.0, 3.0);
	
	BOOST_CHECK(&(q1_ref /= Quaternion<double>(1.0)) == &q1_ref);

	checkValues1(q1, 2.0, -1.0, 2.0, 3.0);
	checkValues3(q1_ref, 2.0, -1.0, 2.0, 3.0);

	BOOST_CHECK(&(q1_ref /= Quaternion<double>(-1.0)) == &q1_ref);

	checkValues1(q1, -2.0, 1.0, -2.0, -3.0);
	checkValues3(q1_ref, -2.0, 1.0, -2.0, -3.0);

	BOOST_CHECK(&(q1_ref /= q1_ref) == &q1_ref);

	checkValues1(q1, 1.0, 0.0, 0.0, 0.0);
	checkValues3(q1_ref, 1.0, 0.0, 0.0, 0.0);

	q1.set(2.0, 3.0, 4.0, 5.0);
	q2.set(3.0, 4.0, 5.0, 6.0);

	BOOST_CHECK(&(q1_ref /= q2) == &q1_ref);

	checkValues1(q1, 0.79069767441860461, 0.023255813953488372, 0.0, 0.046511627906976744);
	checkValues3(q1_ref, 0.79069767441860461, 0.023255813953488372, 0.0, 0.046511627906976744);

	// ---------

	q1_ref.set(0.1, 0.2, -0.3, -0.4);

	q1_ref.swap(q2_ref);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q1_ref, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q2_ref, 0.1, 0.2, -0.3, -0.4);

	q1_ref.swap(q2_ref);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q1_ref, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q2_ref, 3.0, 4.0, 5.0, 6.0);

	q2_ref.swap(q1_ref);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q1_ref, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q2_ref, 0.1, 0.2, -0.3, -0.4);

	q2_ref.swap(q1_ref);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q1_ref, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q2_ref, 3.0, 4.0, 5.0, 6.0);

	swap(q1_ref, q2_ref);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q1_ref, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q2_ref, 0.1, 0.2, -0.3, -0.4);

	swap(q1_ref, q2_ref);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q1_ref, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q2_ref, 3.0, 4.0, 5.0, 6.0);

	swap(q2_ref, q1_ref);

	checkValues1(q1, 3.0, 4.0, 5.0, 6.0);
	checkValues1(q2, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q1_ref, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q2_ref, 0.1, 0.2, -0.3, -0.4);

	swap(q2_ref, q1_ref);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q1_ref, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q2_ref, 3.0, 4.0, 5.0, 6.0);

	q1_ref.swap(q1_ref);

	checkValues1(q1, 0.1, 0.2, -0.3, -0.4);
	checkValues3(q1_ref, 0.1, 0.2, -0.3, -0.4);

	swap(q2_ref, q2_ref);

	checkValues1(q2, 3.0, 4.0, 5.0, 6.0);
	checkValues3(q2_ref, 3.0, 4.0, 5.0, 6.0);
}

BOOST_AUTO_TEST_CASE(QuatFunction2Test)
{
	using namespace CDPL;
	using namespace Math;

	checkValues3<const RealQuaternion<double> >(quat(21.2), 21.2);
	checkValues3<const RealQuaternion<float> >(quat(1.2f), 1.2f);
	checkValues3<const RealQuaternion<int> >(quat(-17), -17);
	checkValues3<const RealQuaternion<std::complex<double> > >(quat(std::complex<double>(1.1, -2.2)), std::complex<double>(1.1, -2.2));

	// ---------

	checkValues3<const Quaternion<double> >(quat(21.2, 12), 21.2, double(12));
	checkValues3<const Quaternion<float> >(quat(1.2f, 2.2f), 1.2f, 2.2f);
	checkValues3<const Quaternion<int> >(quat(-17, 100), -17, 100);
	checkValues3<const Quaternion<std::complex<double> > >(quat(std::complex<double>(1.1, -2.2), std::complex<double>(-5.1, -52.2)),
														   std::complex<double>(1.1, -2.2), std::complex<double>(-5.1, -52.2));
	// ---------

	checkValues3<const Quaternion<double> >(quat(21.2, 12, -2.3f), 21.2, double(12), double(-2.3f));
	checkValues3<const Quaternion<float> >(quat(1.2f, 2.2f, 2), 1.2f, 2.2f, float(2));
	checkValues3<const Quaternion<int> >(quat(-17, 100, -2), -17, 100, -2);
	checkValues3<const Quaternion<std::complex<double> > >(quat(std::complex<double>(0.0, 2.2), std::complex<double>(1.1, -2.2), std::complex<double>(-5.1, -52.2)),
														   std::complex<double>(0.0, 2.2), std::complex<double>(1.1, -2.2), std::complex<double>(-5.1, -52.2));
	// ---------

	checkValues3<const Quaternion<double> >(quat(21.2, 12, -2.3f, 'c'), 21.2, double(12), double(-2.3f), double('c'));
	checkValues3<const Quaternion<float> >(quat(1.2f, 2.2f, 2, -22.12f), 1.2f, 2.2f, float(2), -22.12f);
	checkValues3<const Quaternion<int> >(quat(-17, 100, -2, 'x'), -17, 100, -2, int('x'));
	checkValues3<const Quaternion<std::complex<double> > >(quat(15.2, std::complex<double>(0.0, 2.2), std::complex<double>(1.1, -2.2), std::complex<double>(-5.1, -52.2)),
														   std::complex<double>(15.2, 0.0), std::complex<double>(0.0, 2.2), 
														   std::complex<double>(1.1, -2.2), std::complex<double>(-5.1, -52.2));

}
