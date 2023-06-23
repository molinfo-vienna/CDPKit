/* 
 * RangeTest.cpp 
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

#include "CDPL/Math/Range.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename R>
	void checkRange(typename R::SizeType start, typename R::SizeType stop, R& rng)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(rng.getStart(), start);
		BOOST_CHECK_EQUAL(rng.getStop(), stop);
		BOOST_CHECK_EQUAL(rng.getSize(), stop - start);

		BOOST_CHECK_EQUAL(rng.isEmpty(), start == stop);

		for (typename R::SizeType i = 0; i < (stop - start); i++)
			BOOST_CHECK_EQUAL(rng(i), start + i);

		BOOST_CHECK_THROW(rng(stop - start), Base::IndexError);
	}
}


BOOST_AUTO_TEST_CASE(RangeTest)
{
	using namespace CDPL;
	using namespace Math;

	Range<int> r1;

	checkRange(0, 0, r1);

	Range<int> r2(0, 0);

	checkRange(0, 0, r2);

	Range<int> r3(0, 5);

	checkRange(0, 5, r3);

	Range<int> r4(2, 6);

	checkRange(2, 6, r4);

	Range<int> r5(6, 6);

	checkRange(6, 6, r5);

	Range<int> r6(r4);

	checkRange(2, 6, r6);

	BOOST_CHECK_THROW((Range<int>(1, 0)), Base::RangeError);
	BOOST_CHECK_THROW((Range<int>(2, 1)), Base::RangeError);

	// ----------

	BOOST_CHECK(r6 != r3);
	BOOST_CHECK(r6 == r4);
	
	// ----------

	r1 = r4;

	checkRange(2, 6, r1);

	r1 = r1;

	checkRange(2, 6, r1);

	r1 = r2;

	checkRange(0, 0, r1);

	// ----------

	r1.swap(r4);

	checkRange(0, 0, r4);
	checkRange(2, 6, r1);

	r1.swap(r4);

	checkRange(0, 0, r1);
	checkRange(2, 6, r4);

	r4.swap(r1);

	checkRange(0, 0, r4);
	checkRange(2, 6, r1);

	r4.swap(r1);

	checkRange(0, 0, r1);
	checkRange(2, 6, r4);

	swap(r1, r4);

	checkRange(0, 0, r4);
	checkRange(2, 6, r1);

	swap(r1, r4);

	checkRange(0, 0, r1);
	checkRange(2, 6, r4);

	swap(r4, r1);

	checkRange(0, 0, r4);
	checkRange(2, 6, r1);

	swap(r4, r1);

	checkRange(0, 0, r1);
	checkRange(2, 6, r4);

	// ----------

	r1 = Range<int>(1, 5);

	r1.swap(r4);

	checkRange(1, 5, r4);
	checkRange(2, 6, r1);

	r1.swap(r4);

	checkRange(1, 5, r1);
	checkRange(2, 6, r4);

	r4.swap(r1);

	checkRange(1, 5, r4);
	checkRange(2, 6, r1);

	r4.swap(r1);

	checkRange(1, 5, r1);
	checkRange(2, 6, r4);

	swap(r1, r4);

	checkRange(1, 5, r4);
	checkRange(2, 6, r1);

	swap(r1, r4);

	checkRange(1, 5, r1);
	checkRange(2, 6, r4);

	swap(r4, r1);

	checkRange(1, 5, r4);
	checkRange(2, 6, r1);

	swap(r4, r1);

	checkRange(1, 5, r1);
	checkRange(2, 6, r4);

	// ----------

	r2.swap(r2);

	checkRange(0, 0, r2);

	r4.swap(r4);

	checkRange(2, 6, r4);

	swap(r2, r2);

	checkRange(0, 0, r2);

	swap(r4, r4);

	checkRange(2, 6, r4);
}

BOOST_AUTO_TEST_CASE(RangeFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkRange<const Range<std::size_t> >(0, 0, range(0, 0));
	checkRange<const Range<std::size_t> >(0, 3, range(0, 3));
	checkRange<const Range<std::size_t> >(1, 6, range(1, 6));

	BOOST_CHECK_THROW(range(1, 0), Base::RangeError);
	BOOST_CHECK_THROW(range(2, 1), Base::RangeError);
}
