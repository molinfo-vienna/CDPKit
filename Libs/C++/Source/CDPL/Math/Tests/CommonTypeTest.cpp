/* 
 * CommonTypeTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <complex>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/CommonType.hpp"


BOOST_AUTO_TEST_CASE(CommonTypeTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(CommonType<short int, short int>::Type) == typeid(short int));

    BOOST_CHECK(typeid(CommonType<unsigned short int, unsigned short int>::Type) == typeid(unsigned short int));

    BOOST_CHECK(typeid(CommonType<unsigned int, unsigned int>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<char, char>::Type) == typeid(char));

    BOOST_CHECK(typeid(CommonType<float, float>::Type) == typeid(float));

    BOOST_CHECK(typeid(CommonType<std::complex<double>, std::complex<double> >::Type) == typeid(std::complex<double>));

    // -----------

    BOOST_CHECK(typeid(CommonType<short int, int>::Type) == typeid(int));
    BOOST_CHECK(typeid(CommonType<int, short int>::Type) == typeid(int));

    BOOST_CHECK(typeid(CommonType<short int, unsigned int>::Type) == typeid(unsigned int));
    BOOST_CHECK(typeid(CommonType<unsigned int, short int>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<unsigned short int, int>::Type) == typeid(int));
    BOOST_CHECK(typeid(CommonType<int, unsigned short int>::Type) == typeid(int));

    BOOST_CHECK(typeid(CommonType<unsigned short int, unsigned int>::Type) == typeid(unsigned int));
    BOOST_CHECK(typeid(CommonType<unsigned int, unsigned short int>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<int, unsigned int>::Type) == typeid(unsigned int));
    BOOST_CHECK(typeid(CommonType<unsigned int, int>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<char, unsigned int>::Type) == typeid(unsigned int));
    BOOST_CHECK(typeid(CommonType<unsigned int, char>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<signed char, unsigned int>::Type) == typeid(unsigned int));
    BOOST_CHECK(typeid(CommonType<unsigned int, signed char>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<unsigned char, unsigned int>::Type) == typeid(unsigned int));
    BOOST_CHECK(typeid(CommonType<unsigned int, unsigned char>::Type) == typeid(unsigned int));

    BOOST_CHECK(typeid(CommonType<char, int>::Type) == typeid(int));
    BOOST_CHECK(typeid(CommonType<int, char>::Type) == typeid(int));

    BOOST_CHECK(typeid(CommonType<signed char, int>::Type) == typeid(int));
    BOOST_CHECK(typeid(CommonType<int, signed char>::Type) == typeid(int));

    BOOST_CHECK(typeid(CommonType<unsigned char, int>::Type) == typeid(int));
    BOOST_CHECK(typeid(CommonType<int, unsigned char>::Type) == typeid(int));

    // -----------

    BOOST_CHECK(typeid(CommonType<float, double>::Type) == typeid(double));
    BOOST_CHECK(typeid(CommonType<double, float>::Type) == typeid(double));

    BOOST_CHECK(typeid(CommonType<float, int>::Type) == typeid(float));
    BOOST_CHECK(typeid(CommonType<int, float>::Type) == typeid(float));

    BOOST_CHECK(typeid(CommonType<float, short>::Type) == typeid(float));
    BOOST_CHECK(typeid(CommonType<short, float>::Type) == typeid(float));

    BOOST_CHECK(typeid(CommonType<float, unsigned int>::Type) == typeid(float));
    BOOST_CHECK(typeid(CommonType<unsigned int, float>::Type) == typeid(float));

    // -----------

    BOOST_CHECK(typeid(CommonType<float, std::complex<float> >::Type) == typeid(std::complex<float>));
    BOOST_CHECK(typeid(CommonType<std::complex<float>, float>::Type) == typeid(std::complex<float>));
}
