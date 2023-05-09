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

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v1.toString(), BadCast);

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = 'X';

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(char));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<char>() == 'X');

	BOOST_CHECK_THROW(v1.getData<unsigned char>(), BadCast);

	BOOST_CHECK(v1.toChar() == 'X');
	BOOST_CHECK(v1.toUChar() == static_cast<unsigned char>('X'));
	BOOST_CHECK(v1.toSChar() == static_cast<signed char>('X'));
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>('X'));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>('X'));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>('X'));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>('X'));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>('X'));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>('X'));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>('X'));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>('X'));

	BOOST_CHECK(v1.toFloat() == static_cast<float>('X'));
	BOOST_CHECK(v1.toDouble() == static_cast<double>('X'));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>('X'));

	BOOST_CHECK(v1.toString() == "X");

	BOOST_CHECK(v1.toBool() == static_cast<bool>('X'));

//-----

	v1 = static_cast<unsigned char>(240);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned char));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<unsigned char>() == static_cast<unsigned char>(240));

	BOOST_CHECK_THROW(v1.getData<signed char>(), BadCast);

	BOOST_CHECK(v1.toChar() == static_cast<char>(240));
	BOOST_CHECK(v1.toUChar() == static_cast<unsigned char>(240));
	BOOST_CHECK(v1.toSChar() == static_cast<signed char>(240));
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(240));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(240));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(240));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(240));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(240));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(240));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(240));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(240));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(240));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(240));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(240));

	BOOST_CHECK(v1.toString() == "240");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(240));

//-----

	v1 = static_cast<signed char>(-120);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(signed char));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<signed char>() == static_cast<signed char>(-120));

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

	BOOST_CHECK(v1.toChar() == static_cast<char>(-120));
	BOOST_CHECK(v1.toUChar() == static_cast<unsigned char>(-120));
	BOOST_CHECK(v1.toSChar() == static_cast<signed char>(-120));
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(-120));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(-120));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(-120));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(-120));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(-120));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(-120));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(-120));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(-120));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(-120));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(-120));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(-120));

	BOOST_CHECK(v1.toString() == "-120");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(-120));

//-----

	v1 = static_cast<unsigned short>(1200);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<unsigned short>() == static_cast<unsigned short>(1200));

	BOOST_CHECK_THROW(v1.getData<unsigned int>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(1200));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(1200));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(1200));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(1200));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(1200));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(1200));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(1200));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(1200));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(1200));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(1200));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(1200));

	BOOST_CHECK(v1.toString() == "1200");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(1200));

//-----

	v1 = static_cast<signed short>(-300);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(signed short));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<signed short>() == static_cast<signed short>(-300));

	BOOST_CHECK_THROW(v1.getData<unsigned short>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(-300));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(-300));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(-300));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(-300));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(-300));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(-300));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(-300));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(-300));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(-300));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(-300));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(-300));

	BOOST_CHECK(v1.toString() == "-300");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(-300));

//-----

	v1 = static_cast<unsigned int>(111200);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned int));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned int>() == static_cast<unsigned int>(111200));

	BOOST_CHECK_THROW(v1.getData<unsigned long>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(111200));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(111200));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(111200));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(111200));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(111200));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(111200));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(111200));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(111200));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(111200));

	BOOST_CHECK(v1.toString() == "111200");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(111200));

//-----

	v1 = static_cast<signed int>(-1000000);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(signed int));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<signed int>() == static_cast<signed int>(-1000000));

	BOOST_CHECK_THROW(v1.getData<unsigned int>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(-1000000));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(-1000000));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(-1000000));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(-1000000));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(-1000000));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(-1000000));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(-1000000));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(-1000000));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(-1000000));

	BOOST_CHECK(v1.toString() == "-1000000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(-1000000));

//-----

	v1 = static_cast<unsigned long>(50000000);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned long));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned long>() == static_cast<unsigned long>(50000000));

	BOOST_CHECK_THROW(v1.getData<signed long>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(50000000));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(50000000));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(50000000));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(50000000));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(50000000));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(50000000));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(50000000));

	BOOST_CHECK(v1.toString() == "50000000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(50000000));

//-----

	v1 = static_cast<signed long>(-1046234000);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(signed long));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<signed long>() == static_cast<signed long>(-1046234000));

	BOOST_CHECK_THROW(v1.getData<unsigned long>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(-1046234000));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(-1046234000));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(-1046234000));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(-1046234000));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(-1046234000));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(-1046234000));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(-1046234000));

	BOOST_CHECK(v1.toString() == "-1046234000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(-1046234000));

//-----

	v1 = static_cast<uint64>(700000000000ULL);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(uint64));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<uint64>() == static_cast<uint64>(700000000000ULL));

	BOOST_CHECK_THROW(v1.getData<int64>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);

	if (sizeof(long) != 8) {
		BOOST_CHECK_THROW(v1.toULong(), BadCast);
		BOOST_CHECK_THROW(v1.toLong(), BadCast);

	} else {
		BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(700000000000ULL));
		BOOST_CHECK(v1.toLong() == static_cast<signed long>(700000000000ULL));	
	}

	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(700000000000ULL));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(700000000000ULL));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(700000000000ULL));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(700000000000ULL));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(700000000000ULL));

	BOOST_CHECK(v1.toString() == "700000000000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(700000000000ULL));

//-----

	v1 = static_cast<int64>(-900010456234000LL);

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(int64));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<int64>() == static_cast<int64>(-900010456234000LL));

	BOOST_CHECK_THROW(v1.getData<uint64>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);

	if (sizeof(long) != 8) {
		BOOST_CHECK_THROW(v1.toULong(), BadCast);
		BOOST_CHECK_THROW(v1.toLong(), BadCast);

	} else {
		BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(-900010456234000LL));
		BOOST_CHECK(v1.toLong() == static_cast<signed long>(-900010456234000LL));	
	}

	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(-900010456234000LL));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(-900010456234000LL));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(-900010456234000LL));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(-900010456234000LL));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(-900010456234000LL));

	BOOST_CHECK(v1.toString() == "-900010456234000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(-900010456234000LL));

//-----

	v1 = 3001.1f;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(float));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<float>() == 3001.1f);

	BOOST_CHECK_THROW(v1.getData<double>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK(v1.toFloat() == 3001.1f);
	BOOST_CHECK(v1.toDouble() == static_cast<double>(3001.1f));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(3001.1f));

	BOOST_CHECK_CLOSE(boost::lexical_cast<float>(v1.toString()), 3001.1f, 0.001);

	BOOST_CHECK(v1.toBool() == static_cast<bool>(3001.1f));

//-----

	v1 = 4001.1;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(double));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<double>() == 4001.1);

	BOOST_CHECK_THROW(v1.getData<long double>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK(v1.toDouble() == 4001.1);
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(4001.1));

	BOOST_CHECK_CLOSE(boost::lexical_cast<double>(v1.toString()), 4001.1, 0.001);

	BOOST_CHECK(v1.toBool() == static_cast<bool>(4001.1));

//-----

	v1 = 4001.1L;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(long double));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<long double>() == 4001.1L);

	BOOST_CHECK_THROW(v1.getData<double>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK(v1.toLDouble() == 4001.1L);

	BOOST_CHECK_CLOSE(boost::lexical_cast<long double>(v1.toString()), 4001.1L, 0.001);

	BOOST_CHECK(v1.toBool() == static_cast<bool>(4001.1L));

//-----

	v1 = true;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(bool));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<bool>() == true);

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

	BOOST_CHECK(v1.toChar() == static_cast<char>(true));
	BOOST_CHECK(v1.toUChar() == static_cast<unsigned char>(true));
	BOOST_CHECK(v1.toSChar() == static_cast<signed char>(true));
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(true));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(true));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(true));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(true));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(true));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(true));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(true));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(true));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(true));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(true));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(true));

	BOOST_CHECK(v1.toString() == boost::lexical_cast<std::string>(true));

	BOOST_CHECK(v1.toBool() == true);

//-----

	v1 = false;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(bool));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<bool>() == false);

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

	BOOST_CHECK(v1.toChar() == static_cast<char>(false));
	BOOST_CHECK(v1.toUChar() == static_cast<unsigned char>(false));
	BOOST_CHECK(v1.toSChar() == static_cast<signed char>(false));
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(false));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(false));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(false));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(false));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(false));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(false));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(false));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(false));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(false));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(false));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(false));

	BOOST_CHECK(v1.toString() == boost::lexical_cast<std::string>(false));

	BOOST_CHECK(v1.toBool() == false);

//-----

	v1 = std::string("");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "");

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK(v1.toString() == "");

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = std::string(" ");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == " ");

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

	BOOST_CHECK(v1.toChar() == ' ');
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK(v1.toString() == " ");

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = std::string("1");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "1");

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

	BOOST_CHECK(v1.toChar() == '1');
	BOOST_CHECK(v1.toUChar() == boost::lexical_cast<unsigned short>("1"));
	BOOST_CHECK(v1.toSChar() == boost::lexical_cast<signed short>("1"));
	BOOST_CHECK(v1.toUShort() == boost::lexical_cast<unsigned short>("1"));
	BOOST_CHECK(v1.toShort() == boost::lexical_cast<signed short>("1"));
	BOOST_CHECK(v1.toUInt() == boost::lexical_cast<unsigned int>("1"));
	BOOST_CHECK(v1.toInt() == boost::lexical_cast<signed int>("1"));
	BOOST_CHECK(v1.toULong() == boost::lexical_cast<unsigned long>("1"));
	BOOST_CHECK(v1.toLong() == boost::lexical_cast<signed long>("1"));
	BOOST_CHECK(v1.toUInt64() == boost::lexical_cast<uint64>("1"));
	BOOST_CHECK(v1.toInt64() == boost::lexical_cast<int64>("1"));

	BOOST_CHECK(v1.toFloat() == boost::lexical_cast<float>("1"));
	BOOST_CHECK(v1.toDouble() == boost::lexical_cast<double>("1"));
	BOOST_CHECK(v1.toLDouble() == boost::lexical_cast<long double>("1"));

	BOOST_CHECK(v1.toString() == "1");

	BOOST_CHECK(v1.toBool() == boost::lexical_cast<bool>("1"));

//-----

	v1 = std::string("1 ");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "1 ");

	BOOST_CHECK_THROW(v1.getData<char>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK(v1.toString() == "1 ");

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = std::string("100");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "100");

	BOOST_CHECK_THROW(v1.getData<unsigned char>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK(v1.toUChar() == boost::lexical_cast<unsigned short>("100"));
	BOOST_CHECK(v1.toSChar() == boost::lexical_cast<signed short>("100"));
	BOOST_CHECK(v1.toUShort() == boost::lexical_cast<unsigned short>("100"));
	BOOST_CHECK(v1.toShort() == boost::lexical_cast<signed short>("100"));
	BOOST_CHECK(v1.toUInt() == boost::lexical_cast<unsigned int>("100"));
	BOOST_CHECK(v1.toInt() == boost::lexical_cast<signed int>("100"));
	BOOST_CHECK(v1.toULong() == boost::lexical_cast<unsigned long>("100"));
	BOOST_CHECK(v1.toLong() == boost::lexical_cast<signed long>("100"));
	BOOST_CHECK(v1.toUInt64() == boost::lexical_cast<uint64>("100"));
	BOOST_CHECK(v1.toInt64() == boost::lexical_cast<int64>("100"));

	BOOST_CHECK(v1.toFloat() == boost::lexical_cast<float>("100"));
	BOOST_CHECK(v1.toDouble() == boost::lexical_cast<double>("100"));
	BOOST_CHECK(v1.toLDouble() == boost::lexical_cast<long double>("100"));

	BOOST_CHECK(v1.toString() == "100");

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = std::string("-1");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "-1");

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK(v1.toSChar() == boost::lexical_cast<signed short>("-1"));
	BOOST_CHECK(v1.toUShort() == boost::lexical_cast<unsigned short>("-1"));
	BOOST_CHECK(v1.toShort() == boost::lexical_cast<signed short>("-1"));
	BOOST_CHECK(v1.toUInt() == boost::lexical_cast<unsigned int>("-1"));
	BOOST_CHECK(v1.toInt() == boost::lexical_cast<signed int>("-1"));
	BOOST_CHECK(v1.toULong() == boost::lexical_cast<unsigned long>("-1"));
	BOOST_CHECK(v1.toLong() == boost::lexical_cast<signed long>("-1"));
	BOOST_CHECK(v1.toUInt64() == boost::lexical_cast<uint64>("-1"));
	BOOST_CHECK(v1.toInt64() == boost::lexical_cast<int64>("-1"));

	BOOST_CHECK(v1.toFloat() == boost::lexical_cast<float>("-1"));
	BOOST_CHECK(v1.toDouble() == boost::lexical_cast<double>("-1"));
	BOOST_CHECK(v1.toLDouble() == boost::lexical_cast<long double>("-1"));

	BOOST_CHECK(v1.toString() == "-1");

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = std::string("0.0");

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == "0.0");

	BOOST_CHECK_THROW(v1.getData<double>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK(v1.toFloat() == boost::lexical_cast<float>("0.0"));
	BOOST_CHECK(v1.toDouble() == boost::lexical_cast<double>("0.0"));
	BOOST_CHECK(v1.toLDouble() == boost::lexical_cast<long double>("0.0"));

	BOOST_CHECK(v1.toString() == "0.0");

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = boost::lexical_cast<std::string>(std::numeric_limits<float>::max());

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == boost::lexical_cast<std::string>(std::numeric_limits<float>::max()));

	BOOST_CHECK_THROW(v1.getData<float>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK(v1.toFloat() == boost::lexical_cast<float>(boost::lexical_cast<std::string>(std::numeric_limits<float>::max())));
	BOOST_CHECK(v1.toDouble() == boost::lexical_cast<double>(boost::lexical_cast<std::string>(std::numeric_limits<float>::max())));
	BOOST_CHECK(v1.toLDouble() == boost::lexical_cast<long double>(boost::lexical_cast<std::string>(std::numeric_limits<float>::max())));

	BOOST_CHECK(v1.toString() == boost::lexical_cast<std::string>(std::numeric_limits<float>::max()));

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = boost::lexical_cast<std::string>(std::numeric_limits<short>::max());

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(std::string));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<std::string>() == boost::lexical_cast<std::string>(std::numeric_limits<short>::max()));

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK(v1.toUShort() == boost::lexical_cast<unsigned short>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toShort() == boost::lexical_cast<signed short>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toUInt() == boost::lexical_cast<unsigned int>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toInt() == boost::lexical_cast<signed int>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toULong() == boost::lexical_cast<unsigned long>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toLong() == boost::lexical_cast<signed long>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toUInt64() == boost::lexical_cast<uint64>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toInt64() == boost::lexical_cast<int64>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));

	BOOST_CHECK(v1.toFloat() == boost::lexical_cast<float>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toDouble() == boost::lexical_cast<double>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));
	BOOST_CHECK(v1.toLDouble() == boost::lexical_cast<long double>(boost::lexical_cast<std::string>(std::numeric_limits<short>::max())));

	BOOST_CHECK(v1.toString() == boost::lexical_cast<std::string>(std::numeric_limits<short>::max()));

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	int int_value = 3;

	v1 = &int_value;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(int*));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<int*>() == &int_value);

	BOOST_CHECK_THROW(v1.getData<unsigned int*>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v1.toString(), BadCast);

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	v1 = TestType();

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(TestType));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<TestType>() == TestType());

	BOOST_CHECK_THROW(v1.getData<int>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v1.toString(), BadCast);

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	boost::shared_ptr<std::string> string_ptr(new std::string("Test"));

	v1 = string_ptr;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(boost::shared_ptr<std::string>));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(&v1.getData<Variant>() == &v1);
	BOOST_CHECK(v1.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

	BOOST_CHECK_THROW(v1.getData<std::string>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v1.toString(), BadCast);

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

//-----

	Variant v2(static_cast<unsigned short>(30000));

	BOOST_CHECK(!v2.isEmpty());

	BOOST_CHECK(v2.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v2.getDataPointer() != 0);

	BOOST_CHECK(&v2.getData<Variant>() == &v2);
	BOOST_CHECK(v2.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v2.getData<short>(), BadCast);

	BOOST_CHECK_THROW(v2.toChar(), BadCast);
	BOOST_CHECK_THROW(v2.toUChar(), BadCast);
	BOOST_CHECK_THROW(v2.toSChar(), BadCast);
	BOOST_CHECK(v2.toUShort() == static_cast<unsigned short>(30000));
	BOOST_CHECK(v2.toShort() == static_cast<signed short>(30000));
	BOOST_CHECK(v2.toUInt() == static_cast<unsigned int>(30000));
	BOOST_CHECK(v2.toInt() == static_cast<signed int>(30000));
	BOOST_CHECK(v2.toULong() == static_cast<unsigned long>(30000));
	BOOST_CHECK(v2.toLong() == static_cast<signed long>(30000));
	BOOST_CHECK(v2.toUInt64() == static_cast<uint64>(30000));
	BOOST_CHECK(v2.toInt64() == static_cast<int64>(30000));

	BOOST_CHECK(v2.toFloat() == static_cast<float>(30000));
	BOOST_CHECK(v2.toDouble() == static_cast<double>(30000));
	BOOST_CHECK(v2.toLDouble() == static_cast<long double>(30000));

	BOOST_CHECK(v2.toString() == "30000");

	BOOST_CHECK(v2.toBool() == static_cast<bool>(30000));

//-----

	Variant v3(v1);

	BOOST_CHECK(!v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(boost::shared_ptr<std::string>));

	BOOST_CHECK(v3.getDataPointer() != 0);

	BOOST_CHECK(&v3.getData<Variant>() == &v3);
	BOOST_CHECK(v3.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

	BOOST_CHECK_THROW(v3.getData<std::string>(), BadCast);

	BOOST_CHECK_THROW(v3.toChar(), BadCast);
	BOOST_CHECK_THROW(v3.toUChar(), BadCast);
	BOOST_CHECK_THROW(v3.toSChar(), BadCast);
	BOOST_CHECK_THROW(v3.toUShort(), BadCast);
	BOOST_CHECK_THROW(v3.toShort(), BadCast);
	BOOST_CHECK_THROW(v3.toUInt(), BadCast);
	BOOST_CHECK_THROW(v3.toInt(), BadCast);
	BOOST_CHECK_THROW(v3.toULong(), BadCast);
	BOOST_CHECK_THROW(v3.toLong(), BadCast);
	BOOST_CHECK_THROW(v3.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v3.toInt64(), BadCast);

	BOOST_CHECK_THROW(v3.toFloat(), BadCast);
	BOOST_CHECK_THROW(v3.toDouble(), BadCast);
	BOOST_CHECK_THROW(v3.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v3.toString(), BadCast);

	BOOST_CHECK_THROW(v3.toBool(), BadCast);

//-----

	v1 = v2;

	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v1.getData<short>(), BadCast);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(30000));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(30000));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(30000));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(30000));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(30000));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(30000));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(30000));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(30000));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(30000));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(30000));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(30000));

	BOOST_CHECK(v1.toString() == "30000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(30000));

	BOOST_CHECK_THROW(v1.getData<boost::shared_ptr<unsigned short> >(), BadCast);

//-----

	v3.swap(v1);

	BOOST_CHECK(!v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v3.getDataPointer() != 0);

	BOOST_CHECK(v3.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v3.toChar(), BadCast);
	BOOST_CHECK_THROW(v3.toUChar(), BadCast);
	BOOST_CHECK_THROW(v3.toSChar(), BadCast);
	BOOST_CHECK(v3.toUShort() == static_cast<unsigned short>(30000));
	BOOST_CHECK(v3.toShort() == static_cast<signed short>(30000));
	BOOST_CHECK(v3.toUInt() == static_cast<unsigned int>(30000));
	BOOST_CHECK(v3.toInt() == static_cast<signed int>(30000));
	BOOST_CHECK(v3.toULong() == static_cast<unsigned long>(30000));
	BOOST_CHECK(v3.toLong() == static_cast<signed long>(30000));
	BOOST_CHECK(v3.toUInt64() == static_cast<uint64>(30000));
	BOOST_CHECK(v3.toInt64() == static_cast<int64>(30000));

	BOOST_CHECK(v3.toFloat() == static_cast<float>(30000));
	BOOST_CHECK(v3.toDouble() == static_cast<double>(30000));
	BOOST_CHECK(v3.toLDouble() == static_cast<long double>(30000));

	BOOST_CHECK(v3.toString() == "30000");

	BOOST_CHECK(v3.toBool() == static_cast<bool>(30000));

	BOOST_CHECK_THROW(v3.getData<boost::shared_ptr<unsigned short> >(), BadCast);


	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(boost::shared_ptr<std::string>));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v1.toString(), BadCast);

	BOOST_CHECK_THROW(v1.toBool(), BadCast);

	BOOST_CHECK(v1.getData<boost::shared_ptr<std::string> >().get() == string_ptr.get());

//-----

	v1 = Variant();

	BOOST_CHECK(v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(void));

	BOOST_CHECK(v1.getDataPointer() == 0);

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUShort(), BadCast);
	BOOST_CHECK_THROW(v1.toShort(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt(), BadCast);
	BOOST_CHECK_THROW(v1.toInt(), BadCast);
	BOOST_CHECK_THROW(v1.toULong(), BadCast);
	BOOST_CHECK_THROW(v1.toLong(), BadCast);
	BOOST_CHECK_THROW(v1.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v1.toInt64(), BadCast);

	BOOST_CHECK_THROW(v1.toFloat(), BadCast);
	BOOST_CHECK_THROW(v1.toDouble(), BadCast);
	BOOST_CHECK_THROW(v1.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v1.toString(), BadCast);

	BOOST_CHECK_THROW(v1.toBool(), BadCast);


	BOOST_CHECK(!v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v3.getDataPointer() != 0);

	BOOST_CHECK(v3.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v3.toChar(), BadCast);
	BOOST_CHECK_THROW(v3.toUChar(), BadCast);
	BOOST_CHECK_THROW(v3.toSChar(), BadCast);
	BOOST_CHECK(v3.toUShort() == static_cast<unsigned short>(30000));
	BOOST_CHECK(v3.toShort() == static_cast<signed short>(30000));
	BOOST_CHECK(v3.toUInt() == static_cast<unsigned int>(30000));
	BOOST_CHECK(v3.toInt() == static_cast<signed int>(30000));
	BOOST_CHECK(v3.toULong() == static_cast<unsigned long>(30000));
	BOOST_CHECK(v3.toLong() == static_cast<signed long>(30000));
	BOOST_CHECK(v3.toUInt64() == static_cast<uint64>(30000));
	BOOST_CHECK(v3.toInt64() == static_cast<int64>(30000));

	BOOST_CHECK(v3.toFloat() == static_cast<float>(30000));
	BOOST_CHECK(v3.toDouble() == static_cast<double>(30000));
	BOOST_CHECK(v3.toLDouble() == static_cast<long double>(30000));

	BOOST_CHECK(v3.toString() == "30000");

	BOOST_CHECK(v3.toBool() == static_cast<bool>(30000));

//-----

	v1.swap(v3);

	BOOST_CHECK(v3.isEmpty());

	BOOST_CHECK(v3.getTypeID() == typeid(void));

	BOOST_CHECK(v3.getDataPointer() == 0);

	BOOST_CHECK_THROW(v3.toChar(), BadCast);
	BOOST_CHECK_THROW(v3.toUChar(), BadCast);
	BOOST_CHECK_THROW(v3.toSChar(), BadCast);
	BOOST_CHECK_THROW(v3.toUShort(), BadCast);
	BOOST_CHECK_THROW(v3.toShort(), BadCast);
	BOOST_CHECK_THROW(v3.toUInt(), BadCast);
	BOOST_CHECK_THROW(v3.toInt(), BadCast);
	BOOST_CHECK_THROW(v3.toULong(), BadCast);
	BOOST_CHECK_THROW(v3.toLong(), BadCast);
	BOOST_CHECK_THROW(v3.toUInt64(), BadCast);
	BOOST_CHECK_THROW(v3.toInt64(), BadCast);

	BOOST_CHECK_THROW(v3.toFloat(), BadCast);
	BOOST_CHECK_THROW(v3.toDouble(), BadCast);
	BOOST_CHECK_THROW(v3.toLDouble(), BadCast);

	BOOST_CHECK_THROW(v3.toString(), BadCast);

	BOOST_CHECK_THROW(v3.toBool(), BadCast);


	BOOST_CHECK(!v1.isEmpty());

	BOOST_CHECK(v1.getTypeID() == typeid(unsigned short));

	BOOST_CHECK(v1.getDataPointer() != 0);

	BOOST_CHECK(v1.getData<unsigned short>() == static_cast<unsigned short>(30000));

	BOOST_CHECK_THROW(v1.toChar(), BadCast);
	BOOST_CHECK_THROW(v1.toUChar(), BadCast);
	BOOST_CHECK_THROW(v1.toSChar(), BadCast);
	BOOST_CHECK(v1.toUShort() == static_cast<unsigned short>(30000));
	BOOST_CHECK(v1.toShort() == static_cast<signed short>(30000));
	BOOST_CHECK(v1.toUInt() == static_cast<unsigned int>(30000));
	BOOST_CHECK(v1.toInt() == static_cast<signed int>(30000));
	BOOST_CHECK(v1.toULong() == static_cast<unsigned long>(30000));
	BOOST_CHECK(v1.toLong() == static_cast<signed long>(30000));
	BOOST_CHECK(v1.toUInt64() == static_cast<uint64>(30000));
	BOOST_CHECK(v1.toInt64() == static_cast<int64>(30000));

	BOOST_CHECK(v1.toFloat() == static_cast<float>(30000));
	BOOST_CHECK(v1.toDouble() == static_cast<double>(30000));
	BOOST_CHECK(v1.toLDouble() == static_cast<long double>(30000));

	BOOST_CHECK(v1.toString() == "30000");

	BOOST_CHECK(v1.toBool() == static_cast<bool>(30000));
}
