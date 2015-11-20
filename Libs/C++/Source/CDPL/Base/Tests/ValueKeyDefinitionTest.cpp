/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ValueKeyDefinitionTest.cpp 
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


#include <algorithm>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Base/ValueKeyDefinition.hpp"


BOOST_AUTO_TEST_CASE(ValueKeyDefinitionTest)
{
	using namespace CDPL;
	using namespace Base;

	CDPL_DEFINE_VALUE_KEY(key1);
	CDPL_DEFINE_VALUE_KEY(key2);

	BOOST_CHECK(!(key1 == key2));
	BOOST_CHECK(key1.getID() != key2.getID());

	BOOST_CHECK(key1.getName() == "key1");
	BOOST_CHECK(key2.getName() == "key2");
}

