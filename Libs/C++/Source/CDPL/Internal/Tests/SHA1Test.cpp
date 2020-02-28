/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SHA1Test.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <string>
#include <algorithm>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Internal/SHA1.hpp"


BOOST_AUTO_TEST_CASE(SHA1Test)
{
	using namespace CDPL;
	using namespace Internal;

	std::string test_data1 = "Secure Hash Algorithm 1";
	unsigned char test_data1_sha1sum[] = { 0x3f, 0x6a, 0x58, 0x01, 0x70, 0x6d, 0xc3, 0x54, 0x19, 0x33, 
										   0xa2, 0x70, 0xf0, 0x04, 0x8c, 0xd3, 0xec, 0x26, 0xef, 0xa1 };

	std::string test_data2 = "";
	unsigned char test_data2_sha1sum[] = { 0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55, 
										   0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09 };

	unsigned char sha1_result[SHA1::HASH_SIZE];

	SHA1 sha1;

	sha1.input(test_data1.begin(), test_data1.end());
	sha1.getResult(sha1_result);
	
	BOOST_CHECK(std::equal(sha1_result, sha1_result + SHA1::HASH_SIZE, test_data1_sha1sum));

	sha1.getResult(sha1_result);
	
	BOOST_CHECK(std::equal(sha1_result, sha1_result + SHA1::HASH_SIZE, test_data1_sha1sum));
	
	sha1.reset();
	sha1.getResult(sha1_result);
	
	BOOST_CHECK(!std::equal(sha1_result, sha1_result + SHA1::HASH_SIZE, test_data1_sha1sum));

	sha1.reset();
	sha1.input(test_data1.begin(), test_data1.end());
	sha1.getResult(sha1_result);
	
	BOOST_CHECK(std::equal(sha1_result, sha1_result + SHA1::HASH_SIZE, test_data1_sha1sum));

	sha1.reset();
	sha1.input(test_data2.begin(), test_data2.end());  // empty dataset
	sha1.getResult(sha1_result);
	
	BOOST_CHECK(std::equal(sha1_result, sha1_result + SHA1::HASH_SIZE, test_data2_sha1sum));

	sha1.reset(); 
	sha1.getResult(sha1_result); //  getResult() without preceding input() call == sha1sum(empty dataset)

	BOOST_CHECK(std::equal(sha1_result, sha1_result + SHA1::HASH_SIZE, test_data2_sha1sum));
}

