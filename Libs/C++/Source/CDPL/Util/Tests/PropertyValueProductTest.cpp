/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyValueProductTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Base/PropertyContainer.hpp"
#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Util/PropertyValueProduct.hpp"


namespace
{

	class TestPropertyContainer : public CDPL::Base::PropertyContainer {};
}


BOOST_AUTO_TEST_CASE(PropertyValueProductTest)
{
	using namespace CDPL;
	using namespace Util;
	using namespace Base;

	TestPropertyContainer prop_cntnr1, prop_cntnr2;
	//LookupKey key1 = LookupKey::create("key1");
	LookupKey key2 = LookupKey::create("key2");

	prop_cntnr1.setProperty(key2, long(-3));
	prop_cntnr2.setProperty(key2, long(0));

	BOOST_CHECK((PropertyValueProduct<long>(key2)(prop_cntnr1, prop_cntnr2) == 0));

	prop_cntnr2.setProperty(key2, long(4));

	BOOST_CHECK((PropertyValueProduct<long>(key2)(prop_cntnr2, prop_cntnr1) == -12));

	prop_cntnr1.setProperty(key2, long(5));

	BOOST_CHECK((PropertyValueProduct<long>(key2)(prop_cntnr1, prop_cntnr2) == 20));
}

