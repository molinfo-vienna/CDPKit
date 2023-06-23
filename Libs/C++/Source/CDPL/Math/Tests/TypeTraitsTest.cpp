/* 
 * TypeTraitsTest.cpp 
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


#include <typeinfo>
#include <complex>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/TypeTraits.hpp"


BOOST_AUTO_TEST_CASE(ScalarTraitsTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(ScalarTraits<float>::ValueType) == typeid(float));
    BOOST_CHECK(typeid(ScalarTraits<float>::RealType) == typeid(float));
    BOOST_CHECK(typeid(ScalarTraits<float>::ConstReference) == typeid(const float&));
    BOOST_CHECK(typeid(ScalarTraits<float>::SelfType) == typeid(ScalarTraits<float>));

    // --------

    BOOST_CHECK_EQUAL(ScalarTraits<float>::real(-1.12f), -1.12f);

    BOOST_CHECK_EQUAL(ScalarTraits<float>::imag(-1.22f), 0.0f);

    BOOST_CHECK_EQUAL(ScalarTraits<float>::conj(-1.32f), -1.32f);

    BOOST_CHECK_EQUAL(ScalarTraits<float>::abs(-1.32f), 1.32f);
    BOOST_CHECK_EQUAL(ScalarTraits<float>::abs(1.32f), 1.32f);

    BOOST_CHECK_EQUAL(ScalarTraits<float>::sqrt(2.32f), std::sqrt(2.32f));

    BOOST_CHECK_EQUAL(ScalarTraits<float>::norm1(-2.42f), 2.42f);
    BOOST_CHECK_EQUAL(ScalarTraits<float>::norm1(2.42f), 2.42f);

    BOOST_CHECK_EQUAL(ScalarTraits<float>::norm2(-3.42f), 3.42f);
    BOOST_CHECK_EQUAL(ScalarTraits<float>::norm2(3.42f), 3.42f);

    BOOST_CHECK_EQUAL(ScalarTraits<float>::normInf(-4.42f), 4.42f);
    BOOST_CHECK_EQUAL(ScalarTraits<float>::normInf(4.42f), 4.42f);
}

BOOST_AUTO_TEST_CASE(ComplexTraitsTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(ComplexTraits<std::complex<double> >::ValueType) == typeid(std::complex<double>));
    BOOST_CHECK(typeid(ComplexTraits<std::complex<double> >::RealType) == typeid(double));
    BOOST_CHECK(typeid(ComplexTraits<std::complex<double> >::ConstReference) == typeid(const std::complex<double>&));
    BOOST_CHECK(typeid(ComplexTraits<std::complex<double> >::SelfType) == typeid(ComplexTraits<std::complex<double> >));

    // --------

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::real(std::complex<double>(-1.12, 2.17)), -1.12);

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::imag(std::complex<double>(-1.22, 2.17)), 2.17);

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::conj(std::complex<double>(-1.32, 2.17)), std::complex<double>(-1.32, -2.17));

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::abs(std::complex<double>(-1.32, -3.2)), std::abs(std::complex<double>(-1.32, -3.2)));

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::sqrt(std::complex<double>(2.32, 20.5)), std::sqrt(std::complex<double>(2.32, 20.5)));

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::norm1(std::complex<double>(-2.42, 4.17)), 2.42 + 4.17);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::norm1(std::complex<double>(2.42, -3.22)), 2.42 + 3.22);

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::norm2(std::complex<double>(-3.42, -112.0)), std::abs(std::complex<double>(-3.42, -112.0)));

    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(-4.42, 100.3)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(4.42, -100.3)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(-4.42, -100.3)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(4.42, 100.3)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(100.3, -4.42)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(-100.3, 4.42)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(-100.3, -4.42)), 100.3);
    BOOST_CHECK_EQUAL(ComplexTraits<std::complex<double> >::normInf(std::complex<double>(100.3, 4.42)), 100.3);
}

BOOST_AUTO_TEST_CASE(TypeTraitsTest)
{
    using namespace CDPL;
    using namespace Math;

    TypeTraits<float> type_traits1;

    BOOST_CHECK(&static_cast<ScalarTraits<float>& >(type_traits1));

    TypeTraits<std::complex<double> > type_traits2;

    BOOST_CHECK(&static_cast<ComplexTraits<std::complex<double> >& >(type_traits2));
}

BOOST_AUTO_TEST_CASE(IsScalarTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(IsScalar<char>::value);
    BOOST_CHECK(IsScalar<unsigned char>::value);
    BOOST_CHECK(IsScalar<signed char>::value);

    BOOST_CHECK(IsScalar<unsigned short int>::value);
    BOOST_CHECK(IsScalar<signed short int>::value);

    BOOST_CHECK(IsScalar<unsigned int>::value);
    BOOST_CHECK(IsScalar<signed int>::value);

    BOOST_CHECK(IsScalar<unsigned long int>::value);
    BOOST_CHECK(IsScalar<signed long int>::value);

    BOOST_CHECK(IsScalar<float>::value);
    BOOST_CHECK(IsScalar<double>::value);
    BOOST_CHECK(IsScalar<long double>::value);

    BOOST_CHECK(IsScalar<std::complex<int> >::value);
    BOOST_CHECK(IsScalar<std::complex<float> >::value);
    BOOST_CHECK(IsScalar<std::complex<double> >::value);
    BOOST_CHECK(IsScalar<std::complex<long double> >::value);

    // ---------

    BOOST_CHECK(!IsScalar<char*>::value);
    BOOST_CHECK(!IsScalar<std::string>::value);
    BOOST_CHECK(!IsScalar<std::complex<std::string> >::value);
}
