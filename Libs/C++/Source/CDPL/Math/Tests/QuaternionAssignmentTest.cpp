/* 
 * QuaternionAssignmentTest.cpp 
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

#include "CDPL/Math/QuaternionAssignment.hpp"
#include "CDPL/Math/Quaternion.hpp"


namespace
{

	template <typename Q, typename T>
	void checkValues(Q& quat, const T& c1, const T& c2 = T(), const T& c3 = T(), const T& c4 = T())
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

	template <typename T1, typename T2>
	struct DirectAssignment
	{

		static void apply(T1& t1, const T2& t2) {
			t1 = t2;
		}
	};

	template <typename T1, typename T2>
	struct MultiplicationAssignment
	{

		static void apply(T1& t1, const T2& t2) {
			t1 *= t2;
		}
	};
}


BOOST_AUTO_TEST_CASE(QuaternionAssignQuaternionFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Quaternion<double> q1(0.0);
	Quaternion<double> q2(0.0);

	quaternionAssignQuaternion<DirectAssignment>(q1, q2);

	checkValues(q1, 0.0);
	checkValues(q2, 0.0);

	// ----------

	q2.set(1.1, 2.1, 3.1, 4.1);
	checkValues(q2, 1.1, 2.1, 3.1, 4.1);

	quaternionAssignQuaternion<DirectAssignment>(q1, q2);

	checkValues(q1, 1.1, 2.1, 3.1, 4.1);
	checkValues(q2, 1.1, 2.1, 3.1, 4.1);

	// ----------

	q2.set(2.1, -3.1, 4.1, -5.1);
	checkValues(q2, 2.1, -3.1, 4.1, -5.1);

	quaternionAssignQuaternion<MultiplicationAssignment>(q1, q2);

	checkValues(q1, 1.1 * 2.1, 2.1 * -3.1, 3.1 * 4.1, 4.1 * -5.1);
	checkValues(q2, 2.1, -3.1, 4.1, -5.1);

	// ----------

	quaternionAssignQuaternion<MultiplicationAssignment>(q1, RealQuaternion<float>(-2.2345f));

	checkValues(q1, 1.1 * 2.1 * -2.2345f, 0.0, 0.0, 0.0);

	// ----------

	q1.set(2.1, -3.1, 4.1, -5.1);
	checkValues(q1, 2.1, -3.1, 4.1, -5.1);

	quaternionAssignQuaternion<MultiplicationAssignment>(q1, q1);

	checkValues(q1, 2.1 * 2.1, -3.1 * -3.1, 4.1 * 4.1, -5.1 * -5.1);
}

BOOST_AUTO_TEST_CASE(QuaternionAssignScalarFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Quaternion<double> q1(0.0);

	checkValues(q1, 0.0);

	quaternionAssignScalar<DirectAssignment>(q1, -2.57);

	checkValues(q1, -2.57, -2.57, -2.57, -2.57);

	// ----------

	q1.set(1.1, 2.1, 3.1, 4.1);
	checkValues(q1, 1.1, 2.1, 3.1, 4.1);

	quaternionAssignScalar<MultiplicationAssignment>(q1, 5.16f);

	checkValues(q1, 1.1 * 5.16f, 2.1 * 5.16f, 3.1 * 5.16f, 4.1 * 5.16f);
}

BOOST_AUTO_TEST_CASE(QuaternionSwapFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Quaternion<double> q1(0.0);
	Quaternion<double> q2(0.0);

	quaternionSwap(q1, q2);

	checkValues(q1, 0.0);
	checkValues(q2, 0.0);

	// ----------

	q1.set(-1.12, -2.12, -3.12, 15.0);
	q2.set(4.0, 2.0, 3.0, 1.0);

	checkValues(q1, -1.12, -2.12, -3.12, 15.0);
	checkValues(q2, 4.0, 2.0, 3.0, 1.0);

	quaternionSwap(q1, q2);

	checkValues(q1, 4.0, 2.0, 3.0, 1.0);
	checkValues(q2, -1.12, -2.12, -3.12, 15.0);

	quaternionSwap(q1, q2);

	checkValues(q1, -1.12, -2.12, -3.12, 15.0);
	checkValues(q2, 4.0, 2.0, 3.0, 1.0);

	quaternionSwap(q2, q1);

	checkValues(q1, 4.0, 2.0, 3.0, 1.0);
	checkValues(q2, -1.12, -2.12, -3.12, 15.0);

	quaternionSwap(q2, q1);

	checkValues(q1, -1.12, -2.12, -3.12, 15.0);
	checkValues(q2, 4.0, 2.0, 3.0, 1.0);

	// ----------

	quaternionSwap(q1, q1);

	checkValues(q1, -1.12, -2.12, -3.12, 15.0);
}
