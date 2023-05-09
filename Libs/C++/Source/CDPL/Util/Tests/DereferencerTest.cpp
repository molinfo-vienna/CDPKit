/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DereferencerTest.cpp 
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


#include <boost/shared_ptr.hpp>
#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(DereferencerTest)
{
	using namespace CDPL;
	using namespace Util;

	int data = 5;
	int* data_ptr = &data;

	boost::shared_ptr<int> shared_ptr(new int(6));

//------

	Dereferencer<int*, int> deref1;

	BOOST_CHECK(data == deref1(data_ptr));

//------

	Dereferencer<int*, int&> deref2;

	BOOST_CHECK(&deref2(data_ptr) == data_ptr);
	BOOST_CHECK(data == deref2(data_ptr));

	deref2(data_ptr) = 3;

	BOOST_CHECK(data == 3);

//------

	Dereferencer<boost::shared_ptr<int>, int> deref3;

	BOOST_CHECK(*shared_ptr == deref3(shared_ptr));

//------

	Dereferencer<boost::shared_ptr<int>, int&> deref4;

	BOOST_CHECK(&deref4(shared_ptr) == shared_ptr.get());
	BOOST_CHECK(*shared_ptr == deref4(shared_ptr));

	deref4(shared_ptr) = 2;

	BOOST_CHECK(*shared_ptr == 2);

//---------------

	NullCheckDereferencer<int*, int> deref5;

	BOOST_CHECK_THROW(deref5(0), Base::NullPointerException);

	BOOST_CHECK(data == deref5(data_ptr));

//------

	NullCheckDereferencer<int*, int&> deref6;

	BOOST_CHECK_THROW(deref6(0), Base::NullPointerException);

	BOOST_CHECK(&deref6(data_ptr) == data_ptr);
	BOOST_CHECK(data == deref6(data_ptr));

	deref6(data_ptr) = 3;

	BOOST_CHECK(data == 3);

//------

	NullCheckDereferencer<boost::shared_ptr<int>, int> deref7;

	BOOST_CHECK_THROW(deref7(boost::shared_ptr<int>()), Base::NullPointerException);

	BOOST_CHECK(*shared_ptr == deref7(shared_ptr));

//------

	NullCheckDereferencer<boost::shared_ptr<int>, int&> deref8;

	BOOST_CHECK_THROW(deref8(boost::shared_ptr<int>()), Base::NullPointerException);

	BOOST_CHECK(&deref8(shared_ptr) == shared_ptr.get());
	BOOST_CHECK(*shared_ptr == deref8(shared_ptr));

	deref8(shared_ptr) = 9;

	BOOST_CHECK(*shared_ptr == 9);
}

