/* 
 * DirectAssignmentProxyTest.cpp 
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

#include "CDPL/Math/DirectAssignmentProxy.hpp"


namespace
{

	struct TestContainer
	{

		typedef TestContainer& ClosureType;

		enum Action {

			NONE,
			ASSIGN,
			PLUS_ASSIGN,
			MINUS_ASSIGN
		};

		TestContainer(): value(0), action(NONE) {}

		TestContainer& assign(int value) {
			this->value = value;
			action = ASSIGN;
			return *this;
		}

		TestContainer& plusAssign(int value) {
			this->value = value;
			action = PLUS_ASSIGN;
			return *this;
		}

		TestContainer& minusAssign(int value) {
			this->value = value;
			action = MINUS_ASSIGN;
			return *this;
		}

		void reset() {
			value = 0;
			action = NONE;
		}

		int    value;
		Action action;
	};
}


BOOST_AUTO_TEST_CASE(DirectAssignmentProxyTest)
{
	using namespace CDPL;
	using namespace Math;

	TestContainer test_cont;

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	DirectAssignmentProxy<TestContainer> proxy1(test_cont);

	BOOST_CHECK(&(proxy1 = 1) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, 1);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::ASSIGN);

	// ----------

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(proxy1 += -3) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, -3);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::PLUS_ASSIGN);

	// ----------

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(proxy1 -= 5) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, 5);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::MINUS_ASSIGN);

	// ----------

	DirectAssignmentProxy<TestContainer> proxy2(proxy1);

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(proxy2 = 10) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, 10);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::ASSIGN);

	// ----------

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(proxy2 += 21) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, 21);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::PLUS_ASSIGN);

	// ----------

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(proxy2 -= -15) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, -15);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::MINUS_ASSIGN);

}

BOOST_AUTO_TEST_CASE(DirectFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	TestContainer test_cont;

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(direct(test_cont) = 1) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, 1);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::ASSIGN);

	// ----------

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(direct(test_cont) += -3) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, -3);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::PLUS_ASSIGN);

	// ----------

	test_cont.reset();

	BOOST_CHECK_EQUAL(test_cont.value, 0);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::NONE);

	BOOST_CHECK(&(direct(test_cont) -= 5) == &test_cont);

	BOOST_CHECK_EQUAL(test_cont.value, 5);
	BOOST_CHECK_EQUAL(test_cont.action, TestContainer::MINUS_ASSIGN);
}
