/* 
 * IndexedElementIteratorTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Util/IndexedElementIterator.hpp"


namespace
{

	struct AccessFunc
	{

		AccessFunc(int* data): data(data) {}

		int& operator()(std::size_t idx) const {
			return data[idx];
		}

		bool operator==(const AccessFunc& func) const {
			return (data == func.data);
		}

		int* data;
	};
}


BOOST_AUTO_TEST_CASE(IndexedElementIteratorTest)
{
	using namespace CDPL;
	using namespace Util;

	int data[] = { 0, 1, 2, 3, 4 };

	IndexedElementIterator<int, AccessFunc> it1(data, 0);

	BOOST_CHECK(*it1 == 0);
	BOOST_CHECK((IndexedElementIterator<int, AccessFunc>(data, 2) - it1 == 2));
	BOOST_CHECK(it1.getIndex() == 0);
	BOOST_CHECK(it1.getAccessFunc().data == &data[0]);

	++it1;

	BOOST_CHECK(*it1 == 1);
	BOOST_CHECK((IndexedElementIterator<int, AccessFunc>(data, 2) != it1));
	BOOST_CHECK(it1.getIndex() == 1);
	BOOST_CHECK(it1.getAccessFunc().data == &data[0]);

	it1++;

	BOOST_CHECK(*it1 == 2);
	BOOST_CHECK((IndexedElementIterator<int, AccessFunc>(data, 2) == it1));
	BOOST_CHECK(it1.getIndex() == 2);
	BOOST_CHECK(it1.getAccessFunc().data == &data[0]);

	--it1;

	BOOST_CHECK(*it1 == 1);
	BOOST_CHECK(it1.getIndex() == 1);
	BOOST_CHECK(it1.getAccessFunc().data == &data[0]);

	it1--;

	BOOST_CHECK(*it1 == 0);
	BOOST_CHECK(it1.getIndex() == 0);
	BOOST_CHECK(it1.getAccessFunc().data == &data[0]);

	IndexedElementIterator<int, AccessFunc> it2(it1);

	BOOST_CHECK(it1 == it2);
	BOOST_CHECK(*it2 == 0);
	BOOST_CHECK(*it1 == *it2);
	BOOST_CHECK(&*it1 == &*it2);
	BOOST_CHECK(it2.getIndex() == it1.getIndex());
	BOOST_CHECK(it2.getAccessFunc().data == it1.getAccessFunc().data);

	it2 = it1;

	BOOST_CHECK(it1 == it2);
	BOOST_CHECK(*it2 == 0);
	BOOST_CHECK(*it1 == *it2);
	BOOST_CHECK(&*it1 == &*it2);
	BOOST_CHECK(it2.getIndex() == it1.getIndex());
	BOOST_CHECK(it2.getAccessFunc().data == it1.getAccessFunc().data);

	it2 += 3;

	BOOST_CHECK(*it2 == 3);
	BOOST_CHECK(it2 - it1 == 3);
	BOOST_CHECK(it1 - it2 == -3);
	BOOST_CHECK(*it2 != *it1);
	BOOST_CHECK(it2 != it1);
	BOOST_CHECK(&*it1 != &*it2);
	BOOST_CHECK(it2.getIndex() == it1.getIndex() + 3);
	BOOST_CHECK(it2.getAccessFunc().data == it1.getAccessFunc().data);

	it2 -= 3;

	BOOST_CHECK(it1 == it2);
	BOOST_CHECK(*it2 == 0);
	BOOST_CHECK(*it1 == *it2);
	BOOST_CHECK(&*it1 == &*it2);
	BOOST_CHECK(it2 - it1 == 0);
	BOOST_CHECK(it1 - it2 == 0);
	BOOST_CHECK(it2.getIndex() == it1.getIndex());
	BOOST_CHECK(it2.getAccessFunc().data == it1.getAccessFunc().data);

	it2 = it1 + 3;

	BOOST_CHECK(*it2 == 3);
	BOOST_CHECK(it2 - it1 == 3);
	BOOST_CHECK(it1 - it2 == -3);
	BOOST_CHECK(*it2 != *it1);
	BOOST_CHECK(&*it1 != &*it2);
	BOOST_CHECK(it2 != it1);
	BOOST_CHECK(*(it2 - 3) == 0);
	BOOST_CHECK(*(it2 - 3) == *it1);
	BOOST_CHECK(it2 - 3 == it1);
	BOOST_CHECK(it2.getIndex() == it1.getIndex() + 3);
	BOOST_CHECK(it2.getAccessFunc().data == it1.getAccessFunc().data);
}

