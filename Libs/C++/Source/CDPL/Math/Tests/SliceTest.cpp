/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SliceTest.cpp 
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

#include "CDPL/Math/Slice.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename S>
	void checkSlice(typename S::SizeType start, typename S::DifferenceType stride, typename S::SizeType size, S& slc)
	{
		BOOST_CHECK_EQUAL(slc.getStart(), start);
		BOOST_CHECK_EQUAL(slc.getStride(), stride);
		BOOST_CHECK_EQUAL(slc.getSize(), size);

		BOOST_CHECK_EQUAL(slc.isEmpty(), size == typename S::SizeType(0));

		for (typename S::SizeType i = 0; i < size; i++)
			BOOST_CHECK_EQUAL(slc(i), start + i * stride);

		BOOST_CHECK_THROW(slc(size), CDPL::Base::IndexError);
	}
}


BOOST_AUTO_TEST_CASE(SliceTest)
{
	using namespace CDPL;
	using namespace Math;

	Slice<unsigned int, int> s1;

	checkSlice(0, 0, 0, s1);

	Slice<unsigned int, int> s2(0, 0, 0);

	checkSlice(0, 0, 0, s2);

	Slice<unsigned int, int> s3(0, 2, 5);

	checkSlice(0, 2, 5, s3);

	Slice<unsigned int, int> s4(12, -2, 6);

	checkSlice(12, -2, 6, s4);

	Slice<unsigned int, int> s5(6, 0, 6);

	checkSlice(6, 0, 6, s5);

	Slice<unsigned int, int> s6(s4);

	checkSlice(12, -2, 6, s6);

	BOOST_CHECK_THROW((Slice<unsigned int, int>(2, -2, 3)), Base::RangeError);
	BOOST_CHECK_THROW((Slice<unsigned int, int>(5, -1, 7)), Base::RangeError);

	// ----------

	BOOST_CHECK(s6 != s3);
	BOOST_CHECK(s6 == s4);
	
	// ----------

	s1 = s4;

	checkSlice(12, -2, 6, s1);

	s1 = s1;

	checkSlice(12, -2, 6, s1);

	s1 = s2;

	checkSlice(0, 0, 0, s1);

	// ----------

	s1.swap(s4);

	checkSlice(0, 0, 0, s4);
	checkSlice(12, -2, 6, s1);

	s1.swap(s4);

	checkSlice(0, 0, 0, s1);
	checkSlice(12, -2, 6, s4);

	s4.swap(s1);

	checkSlice(0, 0, 0, s4);
	checkSlice(12, -2, 6, s1);

	s4.swap(s1);

	checkSlice(0, 0, 0, s1);
	checkSlice(12, -2, 6, s4);

	swap(s1, s4);

	checkSlice(0, 0, 0, s4);
	checkSlice(12, -2, 6, s1);

	swap(s1, s4);

	checkSlice(0, 0, 0, s1);
	checkSlice(12, -2, 6, s4);

	swap(s4, s1);

	checkSlice(0, 0, 0, s4);
	checkSlice(12, -2, 6, s1);

	swap(s4, s1);

	checkSlice(0, 0, 0, s1);
	checkSlice(12, -2, 6, s4);

	// ----------

	s1 = Slice<unsigned int, int>(1, 2, 5);

	s1.swap(s4);

	checkSlice(1, 2, 5, s4);
	checkSlice(12, -2, 6, s1);

	s1.swap(s4);

	checkSlice(1, 2, 5, s1);
	checkSlice(12, -2, 6, s4);

	s4.swap(s1);

	checkSlice(1, 2, 5, s4);
	checkSlice(12, -2, 6, s1);

	s4.swap(s1);

	checkSlice(1, 2, 5, s1);
	checkSlice(12, -2, 6, s4);

	swap(s1, s4);

	checkSlice(1, 2, 5, s4);
	checkSlice(12, -2, 6, s1);

	swap(s1, s4);

	checkSlice(1, 2, 5, s1);
	checkSlice(12, -2, 6, s4);

	swap(s4, s1);

	checkSlice(1, 2, 5, s4);
	checkSlice(12, -2, 6, s1);

	swap(s4, s1);

	checkSlice(1, 2, 5, s1);
	checkSlice(12, -2, 6, s4);

	// ----------

	s2.swap(s2);

	checkSlice(0, 0, 0, s2);

	s4.swap(s4);

	checkSlice(12, -2, 6, s4);

	swap(s2, s2);

	checkSlice(0, 0, 0, s2);

	swap(s4, s4);

	checkSlice(12, -2, 6, s4);
}

BOOST_AUTO_TEST_CASE(SliceFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkSlice<const Slice<std::size_t, std::ptrdiff_t> >(0, 0, 0, slice(0, 0, 0));
	checkSlice<const Slice<std::size_t, std::ptrdiff_t> >(7, -1, 3, slice(7, -1, 3));
	checkSlice<const Slice<std::size_t, std::ptrdiff_t> >(1, 2, 6, slice(1, 2, 6));

	BOOST_CHECK_THROW(slice(0, -1, 3), Base::RangeError);
	BOOST_CHECK_THROW(slice(2, -4, 2), Base::RangeError);
}
