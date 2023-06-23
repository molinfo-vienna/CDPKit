/* 
 * MatrixAssignmentTest.cpp 
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

#include "CDPL/Math/MatrixAssignment.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    template <typename M, typename T, std::size_t N>
    void checkValues(typename M::SizeType size1, typename M::SizeType size2, M& mtx, T values[][N])
    {
        BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
        BOOST_CHECK_EQUAL(mtx.getSize2(), size2);

        for (typename M::SizeType i = 0; i < size1; i++) {
            for (typename M::SizeType j = 0; j < size2; j++) {
                BOOST_CHECK_EQUAL(mtx(i, j), values[i][j]);
                BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), values[i][j]);
            }
        }
    }

    template <typename M, typename T>
    void checkValues(typename M::SizeType size1, typename M::SizeType size2, M& mtx, const T& value)
    {
        BOOST_CHECK_EQUAL(mtx.getSize1(), size1);
        BOOST_CHECK_EQUAL(mtx.getSize2(), size2);

        for (typename M::SizeType i = 0; i < size1; i++) {
            for (typename M::SizeType j = 0; j < size2; j++) {
                BOOST_CHECK_EQUAL(mtx(i, j), value);
                BOOST_CHECK_EQUAL(const_cast<const M&>(mtx)(i, j), value);
            }
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


BOOST_AUTO_TEST_CASE(MatrixAssignMatrixFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<double> m1;
    ScalarMatrix<double> m2(0, 0, 4.25);

    checkValues(0, 0, m1, 0.0);
    checkValues(0, 0, m2, 4.25);

    // -------

    matrixAssignMatrix<AdditionAssignment>(m1, m2);

    checkValues(0, 0, m1, 0.0);
    checkValues(0, 0, m2, 4.25);

    // -------

    m2.resize(0, 6);

    checkValues(0, 6, m2, 4.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(0, 6, m2, 4.25);

    // -------

    m2.resize(5, 0);

    checkValues(5, 0, m2, 4.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(5, 0, m2, 4.25);

    // -------

    m2.resize(7, 3);

    checkValues(7, 3, m2, 4.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(7, 3, m2, 4.25);

    // -------

    m1.resize(7, 6, true, 1.25);

    checkValues(7, 6, m1, 1.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(7, 6, m1, 1.25);

    // -------

    m1.resize(3, 3, true, 1.25);

    checkValues(3, 3, m1, 1.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(3, 3, m1, 1.25);

    // -------

    m1.resize(4, 4, true, 1.25);

    checkValues(4, 4, m1, 1.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(4, 4, m1, 1.25);

    // -------

    m1.resize(0, 3);
    m2.resize(0, 0);

    checkValues(0, 3, m1, 1.25);
    checkValues(0, 0, m2, 4.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(0, 3, m1, 1.25);

    // -------

    m1.resize(4, 0);

    checkValues(4, 0, m1, 1.25);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(4, 0, m1, 1.25);

    // -------

    m1.resize(3, 3);
    m1.clear(1.12);

    checkValues(3, 3, m1, 1.12);

    BOOST_CHECK_THROW(matrixAssignMatrix<AdditionAssignment>(m1, m2), Base::SizeError);

    checkValues(3, 3, m1, 1.12);

    // -------

    m1.resize(7, 3);
    m2.resize(7, 3);

    m1.clear(1.25);

    checkValues(7, 3, m1, 1.25);
    checkValues(7, 3, m2, 4.25);

    matrixAssignMatrix<AdditionAssignment>(m1, m2);

    checkValues(7, 3, m1, 1.25 + 4.25);
    checkValues(7, 3, m2, 4.25);

    // -------

    matrixAssignMatrix<DirectAssignment>(m1, m2);

    checkValues(7, 3, m1, 4.25);
    checkValues(7, 3, m2, 4.25);

    // -------

    double values1[7][3];
    double values3[7][3];
    Matrix<double> m3(7, 3);

    typedef Matrix<double>::SizeType SizeType;

    for (SizeType i = 0; i < 7; i++) {
        for (SizeType j = 0; j < 3; j++) {
            values1[i][j] = double(i * 7 + j);
            values3[i][j] = -values1[i][j];

            m1(i, j) = values1[i][j];
            m3(i, j) = values3[i][j];
        }
    }

    checkValues(7, 3, m1, values1);
    checkValues(7, 3, m3, values3);

    matrixAssignMatrix<AdditionAssignment>(m1, m3);

    checkValues(7, 3, m1, 0.0);
    checkValues(7, 3, m3, values3);

    matrixAssignMatrix<DirectAssignment>(m1, m3);

    checkValues(7, 3, m1, values3);
    checkValues(7, 3, m3, values3);

    matrixAssignMatrix<AdditionAssignment>(m1, ScalarMatrix<double>(7, 3, 2.27));

    for (std::size_t i = 0; i < 7; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            values3[i][j] += 2.27;
        }
    }

    checkValues(7, 3, m1, values3);

    // -------

    matrixAssignMatrix<DirectAssignment>(m1, ScalarMatrix<int>(7, 3, -3));

    checkValues(7, 3, m1, double(int(-3)));

    // -------

    m1.clear(2.17);

    matrixAssignMatrix<AdditionAssignment>(m1, m1);

    checkValues(7, 3, m1, 2.17 + 2.17);
}

BOOST_AUTO_TEST_CASE(MatrixAssignScalarFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<double> m1;

    checkValues(0, 0, m1, 0.0);

    // -------

    matrixAssignScalar<AdditionAssignment>(m1, 4.25);

    checkValues(0, 0, m1, 0.0);

    // -------

    m1.resize(0, 6);

    checkValues(0, 6, m1, 0.0);

    matrixAssignScalar<AdditionAssignment>(m1, 1.11);

    checkValues(0, 6, m1, 0.0);

    // -------

    m1.resize(5, 0);

    checkValues(5, 0, m1, 0.0);

    matrixAssignScalar<DirectAssignment>(m1, -2.11);

    checkValues(5, 0, m1, 0.0);

    // -------

    m1.resize(7, 3);

    checkValues(7, 3, m1, 0.0);

    matrixAssignScalar<AdditionAssignment>(m1, 1.12);

    checkValues(7, 3, m1, 1.12);

    matrixAssignScalar<AdditionAssignment>(m1, 1.22);

    checkValues(7, 3, m1, 1.12 + 1.22);

    // -------

    m1.resize(7, 6, true, 1.25);

    matrixAssignScalar<DirectAssignment>(m1, -4.0);

    checkValues(7, 6, m1, -4.0);

    // -------

    m1.resize(7, 3);

    checkValues(7, 3, m1, -4.0);

    double values[7][3];

    typedef Matrix<double>::SizeType SizeType;

    for (SizeType i = 0; i < 7; i++) {
        for (SizeType j = 0; j < 3; j++) {
            values[i][j] = double(i * 7 + j);
            m1(i, j) = values[i][j];
        }
    }

    checkValues(7, 3, m1, values);

    matrixAssignScalar<AdditionAssignment>(m1, -2.12);

    for (std::size_t i = 0; i < 7; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            values[i][j] += -2.12;
        }
    }

    checkValues(7, 3, m1, values);

    matrixAssignScalar<DirectAssignment>(m1, 4.123);

    checkValues(7, 3, m1, 4.123);

    // -------

    matrixAssignScalar<DirectAssignment>(m1, int(-2));

    checkValues(7, 3, m1, double(int(-2)));
}

BOOST_AUTO_TEST_CASE(MatrixSwapFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<double> m1;
    Matrix<double> m2(0, 0, 4.25);

    checkValues(0, 0, m1, 0.0);
    checkValues(0, 0, m2, 4.25);

    // -------

    matrixSwap(m1, m2);

    checkValues(0, 0, m1, 0.0);
    checkValues(0, 0, m2, 4.25);

    // -------

    m2.resize(0, 6, false, 4.25);

    checkValues(0, 6, m2, 4.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(0, 0, m1, 0.0);
    checkValues(0, 6, m2, 4.25);

    // -------

    m2.resize(5, 0, false, 4.25);

    checkValues(5, 0, m2, 4.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(0, 0, m1, 0.0);
    checkValues(5, 0, m2, 4.25);

    // -------

    m2.resize(7, 3, false, 4.25);

    checkValues(7, 3, m2, 4.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(0, 0, m1, 0.0);
    checkValues(7, 3, m2, 4.25);

    // -------

    m1.resize(7, 6, false, 1.25);

    checkValues(7, 6, m1, 1.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(7, 6, m1, 1.25);
    checkValues(7, 3, m2, 4.25);

    // -------

    m1.resize(3, 3, false, 1.25);

    checkValues(3, 3, m1, 1.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(3, 3, m1, 1.25);
    checkValues(7, 3, m2, 4.25);

    // -------

    m1.resize(4, 4, true, 1.25);

    checkValues(4, 4, m1, 1.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(4, 4, m1, 1.25);
    checkValues(7, 3, m2, 4.25);

    // -------

    m1.resize(0, 3);
    m2.resize(0, 0);

    checkValues(0, 3, m1, 1.25);
    checkValues(0, 0, m2, 4.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(0, 3, m1, 1.25);
    checkValues(0, 0, m2, 4.25);

    // -------

    m1.resize(4, 0);

    checkValues(4, 0, m1, 1.25);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(4, 0, m1, 1.25);
    checkValues(0, 0, m2, 4.25);

    // -------

    m1.resize(3, 3);
    m1.clear(1.12);

    checkValues(3, 3, m1, 1.12);

    BOOST_CHECK_THROW(matrixSwap(m1, m2), Base::SizeError);

    checkValues(3, 3, m1, 1.12);
    checkValues(0, 0, m2, 4.25);

    // -------

    m1.resize(7, 3);
    m2.resize(7, 3);

    m1.clear(1.25);
    m2.clear(4.25);

    checkValues(7, 3, m1, 1.25);
    checkValues(7, 3, m2, 4.25);

    matrixSwap(m1, m2);

    checkValues(7, 3, m2, 1.25);
    checkValues(7, 3, m1, 4.25);

    // -------

    matrixSwap(m2, m1);

    checkValues(7, 3, m1, 1.25);
    checkValues(7, 3, m2, 4.25);

    // -------

    double values1[7][3];
    double values2[7][3];

    typedef Matrix<double>::SizeType SizeType;

    for (SizeType i = 0; i < 7; i++) {
        for (SizeType j = 0; j < 3; j++) {
            values1[i][j] = double(i * 7 + j);
            values2[i][j] = -values1[i][j];

            m1(i, j) = values1[i][j];
            m2(i, j) = values2[i][j];
        }
    }

    checkValues(7, 3, m1, values1);
    checkValues(7, 3, m2, values2);

    matrixSwap(m1, m2);

    checkValues(7, 3, m1, values2);
    checkValues(7, 3, m2, values1);

    matrixSwap(m1, m2);

    checkValues(7, 3, m1, values1);
    checkValues(7, 3, m2, values2);

    matrixSwap(m2, m1);

    checkValues(7, 3, m1, values2);
    checkValues(7, 3, m2, values1);

    matrixSwap(m2, m1);

    checkValues(7, 3, m1, values1);
    checkValues(7, 3, m2, values2);

    // -------

    matrixSwap(m1, m1);

    checkValues(7, 3, m1, values1);
}
