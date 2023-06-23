/* 
 * RangeGeneratorTest.cpp 
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

#include "CDPL/Internal/RangeGenerator.hpp"


BOOST_AUTO_TEST_CASE(RangeGeneratorTest)
{
    using namespace CDPL;
    using namespace Internal;

    int data[4];

    std::generate_n(data, 4, RangeGenerator<int>()); // range_start = 0, inc = 1

    BOOST_CHECK(data[0] == 0 && data[1] == 1 && data[2] == 2 && data[3] == 3);

    std::generate_n(data, 4, RangeGenerator<int>(3)); // range_start = 3, inc = 1

    BOOST_CHECK(data[0] == 3 && data[1] == 4 && data[2] == 5 && data[3] == 6);

    std::generate_n(data, 4, RangeGenerator<int>(2, 2)); // range_start = 2, inc = 2

    BOOST_CHECK(data[0] == 2 && data[1] == 4 && data[2] == 6 && data[3] == 8);

    RangeGenerator<int> rg1(2, 2);

    rg1(), rg1(), rg1(), rg1();

    std::generate_n(data, 4, RangeGenerator<int>(rg1)); // range_start = 8, inc = 2 

    BOOST_CHECK(data[0] == 10 && data[1] == 12 && data[2] == 14 && data[3] == 16);

    RangeGenerator<int> rg2 = rg1;

    std::generate_n(data, 4, rg2); // range_start = 8, inc = 2 

    BOOST_CHECK(data[0] == 10 && data[1] == 12 && data[2] == 14 && data[3] == 16);
}

