/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ExceptionTest.cpp 
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


#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(ExceptionTest)
{
	using namespace CDPL;
	using namespace Base;

	BOOST_CHECK(Exception().what() == std::string(""));
	BOOST_CHECK(Exception("Exception").what() == std::string("Exception"));

	BOOST_CHECK(NullPointerException().what() == std::string(""));
	BOOST_CHECK(NullPointerException("NullPointerException").what() == std::string("NullPointerException"));

	BOOST_CHECK(ValueError().what() == std::string(""));
	BOOST_CHECK(ValueError("ValueError").what() == std::string("ValueError"));

	BOOST_CHECK(RangeError().what() == std::string(""));
	BOOST_CHECK(RangeError("RangeError").what() == std::string("RangeError"));

	BOOST_CHECK(IndexError().what() == std::string(""));
	BOOST_CHECK(IndexError("IndexError").what() == std::string("IndexError"));

	BOOST_CHECK(ItemNotFound().what() == std::string(""));
	BOOST_CHECK(ItemNotFound("ItemNotFound").what() == std::string("ItemNotFound"));

	BOOST_CHECK(BadCast().what() == std::string(""));
	BOOST_CHECK(BadCast("BadCast").what() == std::string("BadCast"));

	BOOST_CHECK(OperationFailed().what() == std::string(""));
	BOOST_CHECK(OperationFailed("OperationFailed").what() == std::string("OperationFailed"));

	BOOST_CHECK(CalculationFailed().what() == std::string(""));
	BOOST_CHECK(CalculationFailed("CalculationFailed").what() == std::string("CalculationFailed"));

	BOOST_CHECK(IOError().what() == std::string(""));
	BOOST_CHECK(IOError("IOError").what() == std::string("IOError"));
}

