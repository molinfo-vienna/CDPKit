/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VariantTest.cpp 
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


#include <string>
#include <typeinfo>
#include <limits>
#include <locale>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Base/Variant.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace
{

	struct TestType 
	{

		bool operator==(const TestType&) const {
			return true;
		}
	};
}


BOOST_AUTO_TEST_CASE(VariantTest)
{
	using namespace CDPL;
	using namespace Base;

	std::locale::global(std::locale::classic());

	Variant v1;

	BOOST_CHECK(v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(void));

	BOOST_CHECK(v1.getDataPointer() == 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);

	BOOST_CHECK_THROW(v1.getData<char>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<unsigned char>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<signed char>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<unsigned short>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<signed short>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<unsigned int>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<signed int>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<unsigned long>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<signed long>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<uint64>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<int64>(), BadCast);

	BOOST_CHECK_THROW(v1.getData<float>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<double>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<long double>(), BadCast);

	BOOST_CHECK_THROW(v1.getData<std::string>(), BadCast);

	BOOST_CHECK_THROW(v1.getData<bool>(), BadCast);

//-----

	v1 = 'X';

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(char));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<char>() == 'X');

	BOOST_CHECK_THROW(v1.getData<unsigned char>(), BadCast);

//-----

	v1 = static_cast<unsigned char>(240);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned char));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<unsigned char>() == static_cast<unsigned char>(240));

	BOOST_CHECK_THROW(v1.getData<signed char>(), BadCast);

//-----

	v1 = static_cast<signed char>(-120);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(signed char));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<signed char>() == static_cast<signed char>(-120));

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

//-----

	v1 = static_cast<unsigned long>(50000000);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned long));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned long>() == static_cast<unsigned long>(50000000));

	BOOST_CHECK_THROW(v1.getData<signed long>(), BadCast);

//-----

	v1 = 3001.1f;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(float));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<float>() == 3001.1f);

	BOOST_CHECK_THROW(v1.getData<double>(), BadCast);

//-----

	v1 = 4001.1;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(double));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<double>() == 4001.1);

	BOOST_CHECK_THROW(v1.getData<long double>(), BadCast);

//-----

	v1 = true;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(bool));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<bool>() == true);

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

//-----

	v1 = false;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(bool));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<bool>() == false);

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

//-----

	v1 = std::string("");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "");

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

//-----

	v1 = std::string("1");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "1");

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

//-----

	int int_value = 3;

	v1 = &int_value;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(int*));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<int*>() == &int_value);

	BOOST_CHECK_THROW(v1.getData<unsigned int*>(), BadCast);

//-----

	v1 = TestType();

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(TestType));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<TestType>() == TestType());

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

//-----

	boost::shared_ptr<std::string> string_ptr(new std::string("Test"));

	v1 = string_ptr;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(boost::shared_ptr<std::string>));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

	BOOST_CHECK_THROW(v1.getData<std::string>(), BadCast);

//-----

	Variant v2(static_cast<unsigned short>(30000));

	BOOST_CHECK(!v2.isEmpty());

	BOOST_CHECK(v2.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v2.getDataPointer() != 0);

	BOOST_CHECK(&v2.getData<Variant>() == &v2);
	BOOST_CHECK(v2.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v2.getData<short>(), BadCast);

//-----

	Variant v3(v1);

	BOOST_CHECK(!v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(boost::shared_ptr<std::string>));

	BOOST_CHECK(v3.getDataPointer() != 0);

	BOOST_CHECK(&v3.getData<Variant>() == &v3);
	BOOST_CHECK(v3.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

	BOOST_CHECK_THROW(v3.getData<std::string>(), BadCast);

//-----

	v1 = v2;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);
	BOOST_CHECK_THROW(v1.getData<boost::shared_ptr<unsigned short> >(), BadCast);

//-----

	v3.swap(v1);

	BOOST_CHECK(!v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v3.getDataPointer() != 0);

	BOOST_CHECK(v3.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v3.getData<boost::shared_ptr<unsigned short> >(), BadCast);


	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(boost::shared_ptr<std::string>));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

	BOOST_CHECK(v1.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

//-----

	v1 = Variant();

	BOOST_CHECK(v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(void));

	BOOST_CHECK(v1.getDataPointer() == 0);


	BOOST_CHECK(!v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v3.getDataPointer() != 0);

	BOOST_CHECK(v3.getData<unsigned short>() == static_cast<unsigned short>(30000));

//-----

	v1.swap(v3);

	BOOST_CHECK(v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(void));

	BOOST_CHECK(v3.getDataPointer() == 0);


	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned short>() == static_cast<unsigned short>(30000));
}
