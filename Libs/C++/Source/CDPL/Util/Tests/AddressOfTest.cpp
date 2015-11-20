/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AddressOfTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Util/AddressOf.hpp"


BOOST_AUTO_TEST_CASE(AddressOfTest)
{
	using namespace CDPL;
	using namespace Util;

	int data = 0;
	int* data_ptr = &data;

	AddressOf<int> aop1;

	BOOST_CHECK(data_ptr == aop1(data));

	*aop1(data) = 5;

	BOOST_CHECK(data == 5);

	AddressOf<int, const int> aop2;

	BOOST_CHECK(data_ptr == aop2(data));
}
