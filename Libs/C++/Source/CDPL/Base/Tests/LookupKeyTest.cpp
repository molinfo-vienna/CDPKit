/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LookupKeyTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Base/LookupKey.hpp"


BOOST_AUTO_TEST_CASE(LookupKeyTest)
{
	using namespace CDPL;
	using namespace Base;

	LookupKey key1 = LookupKey::create("key1");
	LookupKey key2 = LookupKey::create("key2");

	BOOST_CHECK(key1.getName() == "key1");
	BOOST_CHECK(key2.getName() == "key2");

	key1.setName("keyX");

	BOOST_CHECK(key1.getName() == "keyX");
	BOOST_CHECK(key2.getName() == "key2");

	key2.setName("keyY");

	BOOST_CHECK(key1.getName() == "keyX");
	BOOST_CHECK(key2.getName() == "keyY");

	key2.setName("keyX");

	BOOST_CHECK(key1.getName() == "keyX");
	BOOST_CHECK(key2.getName() == "keyX");

	LookupKey key3 = LookupKey::create("keyX");

	BOOST_CHECK(key1.getName() == "keyX");
	BOOST_CHECK(key2.getName() == "keyX");
	BOOST_CHECK(key3.getName() == "keyX");

	key1.setName("keyZ");

	BOOST_CHECK(key1.getName() == "keyZ");
	BOOST_CHECK(key2.getName() == "keyX");
	BOOST_CHECK(key3.getName() == "keyX");	

	LookupKey key4 = LookupKey::create("");

	BOOST_CHECK(key4.getName() == "");

	key1.setName("");

	BOOST_CHECK(key1.getName() == "");

	// ---------

	BOOST_CHECK(!(key1 == key2));
	BOOST_CHECK(key1 != key2);
	BOOST_CHECK(key1.getID() != key2.getID());

	BOOST_CHECK(key1 < key2);

	LookupKey key5(key1);

	BOOST_CHECK(key5.getName() == key1.getName());
	BOOST_CHECK(key5.getName() != "key1");

	key5.setName("key1");

	BOOST_CHECK(key5.getName() == "key1");
	BOOST_CHECK(key5.getName() == key1.getName());

	BOOST_CHECK(key1 == key5);
	BOOST_CHECK(!(key1 != key5));
	BOOST_CHECK(key1.getID() == key5.getID());
	
	BOOST_CHECK(!(key2 == key5));
	BOOST_CHECK(key2 != key5);
	BOOST_CHECK(key2.getID() != key5.getID());

	key5 = key2;
	
	BOOST_CHECK(key5.getName() == key2.getName());
	BOOST_CHECK(key5.getName() != key1.getName());

	BOOST_CHECK(key2 == key5);
	BOOST_CHECK(!(key2 != key5));
	BOOST_CHECK(key2.getID() == key5.getID());

	BOOST_CHECK(!(key1 == key5));
	BOOST_CHECK(key1 != key5);
	BOOST_CHECK(key1.getID() != key5.getID());
}
