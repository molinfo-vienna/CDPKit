/* 
 * LUDecompositionTest.cpp 
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


#include <vector>
#include <algorithm>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/LUDecomposition.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/MatrixAdapter.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(VectorSwapRowsFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Vector<int>::SizeType SizeType;

    Vector<int> v1(10);
    std::vector<SizeType> pv1(11);

    BOOST_CHECK_NO_THROW(swapRows(v1, pv1));

    pv1.resize(10);

    // ---------

    for (SizeType i = 0; i < v1.getSize(); i++) {
        v1(i) = i + 1;
        pv1[i] = i;
    }

    const Vector<int> v1_orig(v1);

    swapRows(v1, pv1);

    BOOST_CHECK(v1 == v1_orig);

    // --------- rotate

    std::rotate(pv1.begin(), pv1.begin() + 1, pv1.end());

    pv1[pv1.size() - 1] = pv1.size() - 1;

    Vector<int> v1_tst(v1);

    for (SizeType i = 0; i < v1.getSize(); i++) {
        swapRows(v1, pv1);
    
        std::rotate(v1_tst.getData().begin(), v1_tst.getData().begin() + 1, v1_tst.getData().begin() + v1_tst.getSize());

        BOOST_CHECK(v1 == v1_tst);

        if (i < v1.getSize() - 1)
            BOOST_CHECK(v1 != v1_orig);
        else
            BOOST_CHECK(v1 == v1_orig);
    }

    // --------- revert

    BOOST_CHECK(v1 == v1_orig);
    BOOST_CHECK(v1_tst == v1_orig);

    for (std::size_t i = 0; i < pv1.size(); i++) {
        if (i < pv1.size() / 2)
            pv1[i] = pv1.size() - 1 - i;
        else
            pv1[i] = i;
    }

    std::reverse(v1_tst.getData().begin(), v1_tst.getData().begin() + v1_tst.getSize());

    swapRows(v1, pv1);

    BOOST_CHECK(v1 == v1_tst);
    BOOST_CHECK(v1 != v1_orig);

    swapRows(v1, pv1);

    BOOST_CHECK(v1 == v1_orig);
    BOOST_CHECK(v1 != v1_tst);
}

BOOST_AUTO_TEST_CASE(MatrixSwapRowsFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    Matrix<std::complex<double> > m1(10, 8);
    std::vector<SizeType> pv1(11);

    BOOST_CHECK_NO_THROW(swapRows(m1, pv1));

    pv1.resize(10);

    // ---------

    for (SizeType i = 0; i < m1.getSize1(); i++) {
        pv1[i] = i;
    
        for (SizeType j = 0; j < m1.getSize2(); j++)
            m1(i, j) = i * m1.getSize2() + j + 1;
    }

    const Matrix<std::complex<double> > m1_orig(m1);

    swapRows(m1, pv1);

    BOOST_CHECK(m1 == m1_orig);

    // --------- rotate

    std::rotate(pv1.begin(), pv1.begin() + 1, pv1.end());

    pv1[pv1.size() - 1] = pv1.size() - 1;

    Matrix<std::complex<double> > m1_tst(m1);

    for (SizeType i = 0; i < m1.getSize1(); i++) {
        swapRows(m1, pv1);
    
        for (SizeType j = 0; j < m1.getSize1() - 1; j++) {
            MatrixRow<Matrix<std::complex<double> > > r(m1_tst, j + 1);
            row(m1_tst, j).swap(r);
        }

        BOOST_CHECK(m1 == m1_tst);

        if (i < m1.getSize1() - 1)
            BOOST_CHECK(m1 != m1_orig);
        else
            BOOST_CHECK(m1 == m1_orig);
    }

    // --------- revert

    BOOST_CHECK(m1 == m1_orig);
    BOOST_CHECK(m1_tst == m1_orig);

    for (std::size_t i = 0; i < pv1.size(); i++) {
        if (i < pv1.size() / 2)
            pv1[i] = pv1.size() - 1 - i;
        else
            pv1[i] = i;
    }

    for (SizeType i = 0; i < m1.getSize1() / 2; i++) {
        MatrixRow<Matrix<std::complex<double> > > r(m1_tst, m1.getSize1() - 1 - i);
        row(m1_tst, i).swap(r);
    }

    swapRows(m1, pv1);

    BOOST_CHECK(m1 == m1_tst);
    BOOST_CHECK(m1 != m1_orig);

    swapRows(m1, pv1);

    BOOST_CHECK(m1 == m1_orig);
    BOOST_CHECK(m1 != m1_tst);
}

BOOST_AUTO_TEST_CASE(LUDecomposeFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<double>::SizeType SizeType1;

    Matrix<double> m1(0, 0);

    BOOST_CHECK_EQUAL(luDecompose(m1), 0);

    m1.resize(6, 0);

    BOOST_CHECK_EQUAL(luDecompose(m1), 0);

    m1.resize(0, 6);

    BOOST_CHECK_EQUAL(luDecompose(m1), 0);

    // ---------

    m1.resize(6, 6, true, 0.0);

    BOOST_CHECK_EQUAL(luDecompose(m1), 1);

    // ---------

    m1 = ScalarMatrix<double>(6, 6, 1.0);

    BOOST_CHECK_EQUAL(luDecompose(m1), 2);

    // ---------

    m1 = IdentityMatrix<double>(6, 8) * 2.0;

    BOOST_CHECK_EQUAL(luDecompose(m1), 0);

    BOOST_CHECK(m1 == IdentityMatrix<double>(6, 8) * 2.0);

    m1 = IdentityMatrix<double>(8, 6) * -2.0;

    BOOST_CHECK_EQUAL(luDecompose(m1), 0);

    BOOST_CHECK(m1 == IdentityMatrix<double>(8, 6) * -2.0);

    m1 = IdentityMatrix<double>(6, 6) * 0.5;

    BOOST_CHECK_EQUAL(luDecompose(m1), 0);

    BOOST_CHECK(m1 == IdentityMatrix<double>(6, 6) * 0.5);

    // ---------

    for (int k = 0; k < 5; k++) { 
        switch (k) {

        case 0:
            m1.resize(6, 6, false);
            break;

        case 1:
            m1.resize(6, 8, false);
            break;

        case 2:
            m1.resize(8, 6, false);
            break;

        case 3:
            m1.resize(1, 6, false);
            break;

        case 4:
            m1.resize(6, 1, false);
        }

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++)
                m1(i, j) = (i >= j ? k + 2 : 0.0);

        BOOST_CHECK_EQUAL(luDecompose(m1), 0);

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++) {
                if (i > j)
                    BOOST_CHECK_EQUAL(m1(i, j), 1.0);
                else if (i == j)
                    BOOST_CHECK_EQUAL(m1(i, j), k + 2);
                else
                    BOOST_CHECK_EQUAL(m1(i, j), 0.0);
            }
    }

    // ---------

    for (int k = 0; k < 5; k++) { 
        switch (k) {

        case 0:
            m1.resize(6, 6, false);
            break;

        case 1:
            m1.resize(6, 8, false);
            break;

        case 2:
            m1.resize(8, 6, false);
            break;

        case 3:
            m1.resize(1, 6, false);
            break;

        case 4:
            m1.resize(6, 1, false);
        }

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++)
                m1(i, j) = (i <= j ? k + 2 : 0.0);

        BOOST_CHECK_EQUAL(luDecompose(m1), 0);
    
        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++) {
                if (i <= j)
                    BOOST_CHECK_EQUAL(m1(i, j), k + 2);
                else
                    BOOST_CHECK_EQUAL(m1(i, j), 0.0);
            }
    }

    // ---------

    typedef Matrix<long double>::SizeType SizeType2;

    Matrix<long double> m2(12, 12);

    for (SizeType2 i = 0; i < m2.getSize1(); i++) 
        for (SizeType2 j = 0; j < m2.getSize2(); j++)
            m2(i, j) = i * m2.getSize2() + j - 20.0;

    Matrix<long double> m3 = triang<UnitLower>(m2) * triang<Upper>(m2);

    BOOST_CHECK_EQUAL(luDecompose(m3), 0);

    BOOST_CHECK(equals(m2, m3, 0.000001));
}

BOOST_AUTO_TEST_CASE(PivotingLUDecomposeFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<double>::SizeType SizeType1;

    std::vector<SizeType1> pv1(10);
    std::size_t num_row_swaps;

    Matrix<double> m1(0, 0);

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    m1.resize(6, 0);

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    m1.resize(0, 6);

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    // ---------

    m1.resize(6, 6, true, 0.0);

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 1);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    // ---------

    m1 = ScalarMatrix<double>(6, 6, 1.0);

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 2);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    // ---------

    m1 = IdentityMatrix<double>(6, 8) * 2.0;

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    BOOST_CHECK(m1 == IdentityMatrix<double>(6, 8) * 2.0);

    m1 = IdentityMatrix<double>(8, 6) * -2.0;

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    BOOST_CHECK(m1 == IdentityMatrix<double>(8, 6) * -2.0);

    m1 = IdentityMatrix<double>(6, 6) * 0.5;

    BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 0);

    BOOST_CHECK(m1 == IdentityMatrix<double>(6, 6) * 0.5);

    // ---------

    for (int k = 0; k < 5; k++) { 
        switch (k) {

        case 0:
            m1.resize(6, 6, false);
            break;

        case 1:
            m1.resize(6, 8, false);
            break;

        case 2:
            m1.resize(8, 6, false);
            break;

        case 3:
            m1.resize(1, 6, false);
            break;

        case 4:
            m1.resize(6, 1, false);
        }

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++)
                m1(i, j) = (i >= j ? k + 2 : 0.0);

        BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
        BOOST_CHECK_EQUAL(num_row_swaps, 0);

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++) {
                if (i > j)
                    BOOST_CHECK_EQUAL(m1(i, j), 1.0);
                else if (i == j)
                    BOOST_CHECK_EQUAL(m1(i, j), k + 2);
                else
                    BOOST_CHECK_EQUAL(m1(i, j), 0.0);
            }
    }

    // ---------

    for (int k = 0; k < 5; k++) { 
        switch (k) {

        case 0:
            m1.resize(6, 6, false);
            break;

        case 1:
            m1.resize(6, 8, false);
            break;

        case 2:
            m1.resize(8, 6, false);
            break;

        case 3:
            m1.resize(1, 6, false);
            break;

        case 4:
            m1.resize(6, 1, false);
        }

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++)
                m1(i, j) = (i <= j ? k + 2 : 0.0);

        BOOST_CHECK_EQUAL(luDecompose(m1, pv1, num_row_swaps), 0);
        BOOST_CHECK_EQUAL(num_row_swaps, 0);

        for (SizeType1 i = 0; i < m1.getSize1(); i++) 
            for (SizeType1 j = 0; j < m1.getSize2(); j++) {
                if (i <= j)
                    BOOST_CHECK_EQUAL(m1(i, j), k + 2);
                else
                    BOOST_CHECK_EQUAL(m1(i, j), 0.0);
            }
    }

    // ---------

    typedef Matrix<long double>::SizeType SizeType2;

    Matrix<long double> m2(100, 100);
    std::vector<SizeType2> pv2(m2.getSize1());

    for (SizeType2 i = 0; i < m2.getSize1(); i++) 
        for (SizeType2 j = 0; j < m2.getSize2(); j++)
            m2(i, j) = i * m2.getSize2() + j - 31.0;

    m2 = triang<UnitLower>(m2) * triang<Upper>(m2);

    Matrix<long double> m3 = m2;

    BOOST_CHECK_EQUAL(luDecompose(m3, pv2, num_row_swaps), 0);
    BOOST_CHECK_EQUAL(num_row_swaps, 1);

    m3 = triang<UnitLower>(m3) * triang<Upper>(m3);

    swapRows(m2, pv2);

    BOOST_CHECK(equals(m2, m3, 0.000001));
}

BOOST_AUTO_TEST_CASE(VectorLUSubstituteFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<long double>::SizeType SizeType1;

    Matrix<long double> a1(8, 8);

    for (SizeType1 i = 0; i < a1.getSize1(); i++) 
        for (SizeType1 j = 0; j < a1.getSize2(); j++)
            a1(i, j) = i * a1.getSize2() + j - 20.0;

    a1 = triang<UnitLower>(a1) * triang<Upper>(a1);

    typedef Vector<double>::SizeType SizeType2;

    Vector<double> x1(a1.getSize1());

    for (SizeType2 i = 0; i < x1.getSize(); i++) 
        x1(i) = (x1.getSize() - i) * 0.88 - 6.1235;

    Vector<double> y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(luSubstitute(a1, y1));

    BOOST_CHECK(equals(x1, y1, 0.000001));

    // ---------

    a1 = IdentityMatrix<long double>(6, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));

    // ---------

    a1 = IdentityMatrix<long double>(9, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));

    // ---------

    a1.resize(0, 0);
    x1.resize(0);
    y1.resize(0);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(luSubstitute(a1, y1));

    // ---------

    a1.resize(0, 3);
    x1.resize(3);
    y1.resize(0);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));

    // ---------

    a1.resize(3, 0);
    x1.resize(0);
    y1.resize(3);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));
}

BOOST_AUTO_TEST_CASE(MatrixLUSubstituteFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<long double>::SizeType SizeType1;

    Matrix<long double> a1(8, 8);

    for (SizeType1 i = 0; i < a1.getSize1(); i++) 
        for (SizeType1 j = 0; j < a1.getSize2(); j++)
            a1(i, j) = i * a1.getSize2() + j - 20.0;

    a1 = triang<UnitLower>(a1) * triang<Upper>(a1);

    typedef Matrix<std::complex<long double> >::SizeType SizeType2;

    Matrix<std::complex<long double> > x1(a1.getSize2(), a1.getSize2() + 5);

    for (SizeType2 i = 0; i < x1.getSize1(); i++) 
        for (SizeType2 j = 0; j < x1.getSize2(); j++) 
            x1(i, j) = 1000.0 - (x1.getSize1() * j + i) * 0.88;

    Matrix<std::complex<long double> > y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(luSubstitute(a1, y1));

    BOOST_CHECK(equals(x1, y1, 0.000001));

    // ---------

    a1 = IdentityMatrix<long double>(6, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));

    // ---------

    a1 = IdentityMatrix<long double>(9, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));

    // ---------

    a1.resize(5, 0);
    x1.resize(0, 3);
    y1.resize(5, 3);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(!luSubstitute(a1, y1));

    // ---------

    a1.resize(0, 0);
    x1.resize(0, 3);
    y1.resize(0, 3);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(luSubstitute(a1, y1));

    // ---------

    x1.resize(0, 0);
    y1.resize(0, 0);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(luSubstitute(a1, y1));

    // ---------

    a1 = IdentityMatrix<long double>(3, 3);
    x1.resize(3, 0);
    y1.resize(3, 0);

    BOOST_CHECK_EQUAL(luDecompose(a1), 0);

    BOOST_CHECK(luSubstitute(a1, y1));
}

BOOST_AUTO_TEST_CASE(VectorPivotingLUSubstituteFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<std::complex<long double> >::SizeType SizeType1;
    
    Matrix<std::complex<long double> > a1(8, 8);
    std::vector<SizeType1> pv1(a1.getSize1() + 2);
    std::size_t num_swaps;

    for (SizeType1 i = 0; i < a1.getSize1(); i++) 
        for (SizeType1 j = 0; j < a1.getSize2(); j++)
            a1(i, j) = (i * a1.getSize2() + j - 10.0);

    a1 = triang<UnitLower>(a1) * triang<Upper>(a1);

    typedef Vector<long double>::SizeType SizeType2;

    Vector<long double> x1(a1.getSize1());

    for (SizeType2 i = 0; i < x1.getSize(); i++) 
        x1(i) = (x1.getSize() - i) * 0.88 - 6.1235;

    Vector<std::complex<long double> > y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(luSubstitute(a1, pv1, y1));

    BOOST_CHECK(equals(x1, y1, 0.000001));

    // ---------

    a1 = IdentityMatrix<std::complex<long double> >(6, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));

    // ---------

    a1 = IdentityMatrix<std::complex<long double> >(9, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));

    // ---------

    a1.resize(0, 0);
    x1.resize(0);
    y1.resize(0);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(luSubstitute(a1, pv1, y1));

    // ---------

    a1.resize(0, 3);
    x1.resize(3);
    y1.resize(0);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));

    // ---------

    a1.resize(3, 0);
    x1.resize(0);
    y1.resize(3);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));
}

BOOST_AUTO_TEST_CASE(MatrixPivotingLUSubstituteFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<std::complex<long double> >::SizeType SizeType1;

    Matrix<std::complex<long double> > a1(8, 8);
    std::vector<SizeType1> pv1(a1.getSize1() + 2);
    std::size_t num_swaps;

    for (SizeType1 i = 0; i < a1.getSize1(); i++) 
        for (SizeType1 j = 0; j < a1.getSize2(); j++)
            a1(i, j) = i * a1.getSize2() + j - 20.0;

    a1 = triang<UnitLower>(a1) * triang<Upper>(a1);

    typedef Matrix<std::complex<long double> >::SizeType SizeType2;

    Matrix<std::complex<long double> > x1(a1.getSize2(), a1.getSize2() + 5);

    for (SizeType2 i = 0; i < x1.getSize1(); i++) 
        for (SizeType2 j = 0; j < x1.getSize2(); j++) 
            x1(i, j) = 1000.0 - (x1.getSize1() * j + i) * 0.88;

    Matrix<std::complex<long double> > y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(luSubstitute(a1, pv1, y1));

    BOOST_CHECK(equals(x1, y1, 0.000001));

    // ---------

    a1 = IdentityMatrix<std::complex<long double> >(6, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));

    // ---------

    a1 = IdentityMatrix<std::complex<long double> >(9, 8);
    y1 = a1 * x1;

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));

    // ---------

    a1.resize(5, 0);
    x1.resize(0, 3);
    y1.resize(5, 3);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(!luSubstitute(a1, pv1, y1));

    // ---------

    a1.resize(0, 0);
    x1.resize(0, 3);
    y1.resize(0, 3);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(luSubstitute(a1, pv1, y1));

    // ---------

    x1.resize(0, 0);
    y1.resize(0, 0);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(luSubstitute(a1, pv1, y1));

    // ---------

    a1 = IdentityMatrix<std::complex<long double> >(3, 3);
    x1.resize(3, 0);
    y1.resize(3, 0);

    BOOST_CHECK_EQUAL(luDecompose(a1, pv1, num_swaps), 0);

    BOOST_CHECK(luSubstitute(a1, pv1, y1));
}
