/* 
 * VectorAssignmentTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    template <typename V, typename T>
    void checkValues(typename V::SizeType size, V& vec, T values[])
    {
        BOOST_CHECK_EQUAL(vec.getSize(), size);

        for (typename V::SizeType i = 0; i < size; i++) {
            BOOST_CHECK_EQUAL(vec(i), values[i]);
            BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), values[i]);

            BOOST_CHECK_EQUAL(vec[i], values[i]);
            BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], values[i]);
        }
    }

    template <typename V, typename T>
    void checkValues(typename V::SizeType size, V& vec, const T& value)
    {
        BOOST_CHECK_EQUAL(vec.getSize(), size);

        for (typename V::SizeType i = 0; i < size; i++) {
            BOOST_CHECK_EQUAL(vec(i), value);
            BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), value);

            BOOST_CHECK_EQUAL(vec[i], value);
            BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], value);
        }
    }

    template <typename T1, typename T2>
    struct DirectAssignment
    {

        static void apply(T1& t1, const T2& t2) {
            t1 = t2;
        }
    };

    template <typename T1, typename T2>
    struct AdditionAssignment
    {

        static void apply(T1& t1, const T2& t2) {
            t1 += t2;
        }
    };
}


BOOST_AUTO_TEST_CASE(VectorAssignVectorFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<double> v1;
    ScalarVector<double> v2(0, 4.25);

    checkValues(0, v1, 0.0);
    checkValues(0, v2, 4.25);

    // -------

    vectorAssignVector<AdditionAssignment>(v1, v2);

    checkValues(0, v1, 0.0);
    checkValues(0, v2, 4.25);

    // -------

    v2.resize(6);

    checkValues(6, v2, 4.25);

    BOOST_CHECK_THROW(vectorAssignVector<AdditionAssignment>(v1, v2), Base::SizeError);

    checkValues(6, v2, 4.25);

    // -------

    v1.resize(7, 1.25);

    checkValues(7, v1, 1.25);

    BOOST_CHECK_THROW(vectorAssignVector<AdditionAssignment>(v1, v2), Base::SizeError);

    checkValues(7, v1, 1.25);

    // -------

    v1.resize(3, 1.25);

    checkValues(3, v1, 1.25);

    BOOST_CHECK_THROW(vectorAssignVector<AdditionAssignment>(v1, v2), Base::SizeError);

    checkValues(3, v1, 1.25);

    // -------

    v2.resize(0);

    checkValues(0, v2, 4.25);

    BOOST_CHECK_THROW(vectorAssignVector<AdditionAssignment>(v1, v2), Base::SizeError);

    checkValues(3, v1, 1.25);

    // -------

    v1.resize(4, 1.25);

    checkValues(4, v1, 1.25);

    BOOST_CHECK_THROW(vectorAssignVector<AdditionAssignment>(v1, v2), Base::SizeError);

    checkValues(4, v1, 1.25);

    // -------

    v1.clear(1.12);

    checkValues(4, v1, 1.12);

    BOOST_CHECK_THROW(vectorAssignVector<AdditionAssignment>(v1, v2), Base::SizeError);

    checkValues(4, v1, 1.12);

    // -------

    v1.resize(7);
    v2.resize(7);

    v1.clear(1.25);

    checkValues(7, v1, 1.25);
    checkValues(7, v2, 4.25);

    vectorAssignVector<AdditionAssignment>(v1, v2);

    checkValues(7, v1, 1.25 + 4.25);
    checkValues(7, v2, 4.25);

    // -------

    vectorAssignVector<DirectAssignment>(v1, v2);

    checkValues(7, v1, 4.25);
    checkValues(7, v2, 4.25);

    // -------

    typedef Vector<double>::SizeType SizeType;

    double values1[7];
    double values3[7];
    Vector<double> v3(7);

    for (SizeType i = 0; i < 7; i++) {
        values1[i] = double(i);
        values3[i] = -values1[i];

        v1(i) = values1[i];
        v3(i) = values3[i];
    }

    checkValues(7, v1, values1);
    checkValues(7, v3, values3);

    vectorAssignVector<AdditionAssignment>(v1, v3);

    checkValues(7, v1, 0.0);
    checkValues(7, v3, values3);

    vectorAssignVector<DirectAssignment>(v1, v3);

    checkValues(7, v1, values3);
    checkValues(7, v3, values3);

    vectorAssignVector<AdditionAssignment>(v1, ScalarVector<double>(7, 2.27));

    for (std::size_t i = 0; i < 7; i++)
        values3[i] += 2.27;

    checkValues(7, v1, values3);

    // -------

    vectorAssignVector<DirectAssignment>(v1, ScalarVector<int>(7, -3));

    checkValues(7, v1, double(int(-3)));

    // -------

    v1.clear(2.17);

    vectorAssignVector<AdditionAssignment>(v1, v1);

    checkValues(7, v1, 2.17 + 2.17);
}

BOOST_AUTO_TEST_CASE(VectorAssignScalarFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Vector<double>::SizeType SizeType;

    Vector<double> v1;

    checkValues(0, v1, 0.0);

    // -------

    vectorAssignScalar<AdditionAssignment>(v1, 4.25);

    checkValues(0, v1, 0.0);

    // -------

    v1.resize(7);

    checkValues(7, v1, 0.0);

    vectorAssignScalar<AdditionAssignment>(v1, 1.12);

    checkValues(7, v1, 1.12);

    vectorAssignScalar<AdditionAssignment>(v1, 1.22);

    checkValues(7, v1, 1.12 + 1.22);

    // -------

    v1.resize(4, 1.25);

    vectorAssignScalar<DirectAssignment>(v1, -4.0);

    checkValues(4, v1, -4.0);

    // -------

    v1.resize(7, -4.0);

    checkValues(7, v1, -4.0);

    double values[7];

    for (SizeType i = 0; i < 7; i++) {
        values[i] = double(i);
        v1(i) = values[i];
    }

    checkValues(7, v1, values);

    vectorAssignScalar<AdditionAssignment>(v1, -2.12);

    for (std::size_t i = 0; i < 7; i++) {
        values[i] += -2.12;
    }

    checkValues(7, v1, values);

    vectorAssignScalar<DirectAssignment>(v1, 4.123);

    checkValues(7, v1, 4.123);

    // -------

    vectorAssignScalar<DirectAssignment>(v1, int(-2));

    checkValues(7, v1, double(int(-2)));
}

BOOST_AUTO_TEST_CASE(VectorSwapFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Vector<double>::SizeType SizeType;

    Vector<double> v1;
    Vector<double> v2(0, 4.25);

    checkValues(0, v1, 0.0);
    checkValues(0, v2, 4.25);

    // -------

    vectorSwap(v1, v2);

    checkValues(0, v1, 0.0);
    checkValues(0, v2, 4.25);

    // -------

    v2.resize(7, 4.25);

    checkValues(7, v2, 4.25);

    BOOST_CHECK_THROW(vectorSwap(v1, v2), Base::SizeError);

    checkValues(0, v1, 0.0);
    checkValues(7, v2, 4.25);

    // -------

    v1.resize(6, 1.25);

    checkValues(6, v1, 1.25);

    BOOST_CHECK_THROW(vectorSwap(v1, v2), Base::SizeError);

    checkValues(6, v1, 1.25);
    checkValues(7, v2, 4.25);

    // -------

    v1.resize(8, 1.25);

    checkValues(8, v1, 1.25);

    BOOST_CHECK_THROW(vectorSwap(v1, v2), Base::SizeError);

    checkValues(8, v1, 1.25);
    checkValues(7, v2, 4.25);

    // -------

    v2.resize(0);

    checkValues(0, v2, 4.25);

    BOOST_CHECK_THROW(vectorSwap(v1, v2), Base::SizeError);

    checkValues(8, v1, 1.25);
    checkValues(0, v2, 4.25);

    // -------

    v1.resize(7);
    v2.resize(7);

    v2.clear(4.25);

    checkValues(7, v1, 1.25);
    checkValues(7, v2, 4.25);

    vectorSwap(v1, v2);

    checkValues(7, v2, 1.25);
    checkValues(7, v1, 4.25);

    // -------

    vectorSwap(v2, v1);

    checkValues(7, v1, 1.25);
    checkValues(7, v2, 4.25);

    // -------

    double values1[7];
    double values2[7];

    for (SizeType i = 0; i < 7; i++) {
        values1[i] = double(i);
        values2[i] = -values1[i];

        v1(i) = values1[i];
        v2(i) = values2[i];
    }

    checkValues(7, v1, values1);
    checkValues(7, v2, values2);

    vectorSwap(v1, v2);

    checkValues(7, v1, values2);
    checkValues(7, v2, values1);

    vectorSwap(v1, v2);

    checkValues(7, v1, values1);
    checkValues(7, v2, values2);

    vectorSwap(v2, v1);

    checkValues(7, v1, values2);
    checkValues(7, v2, values1);

    vectorSwap(v2, v1);

    checkValues(7, v1, values1);
    checkValues(7, v2, values2);

    // -------

    vectorSwap(v1, v1);

    checkValues(7, v1, values1);
}
