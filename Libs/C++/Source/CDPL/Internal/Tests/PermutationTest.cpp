/* 
 * PermutationTest.cpp 
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

#include "CDPL/Internal/Permutation.hpp"


BOOST_AUTO_TEST_CASE(PermutationTest)
{
    using namespace CDPL;
    using namespace Internal;

    int data[25 * 4] = { 0, 1, 2, 3 };

    BOOST_CHECK(nextPermutation(data, data) == 0);
    BOOST_CHECK(nextPermutation(data, data + 1) == 0);

    int* data_ptr = data;

    for (int i = 0; i < 24; i++, data_ptr += 4) {
        std::copy(data_ptr, data_ptr + 4, data_ptr + 4);
        
        nextPermutation(data_ptr + 4, data_ptr + 8);
    }

    BOOST_CHECK(std::equal(data_ptr, data_ptr + 4, data));

    bool no_duplicates = true;

    for (int i = 0; i < 24 && no_duplicates; i++) {
        for (int j = i + 1; j < 24; j++) {
            if (std::equal(data + i * 4, data + i * 4 + 4, data + j * 4)) {
                no_duplicates = false;
                break;
            }
        }
    }

    BOOST_CHECK(no_duplicates);
}

