/* 
 * LinearSolveTest.cpp 
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

#include "CDPL/Math/LinearSolve.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


BOOST_AUTO_TEST_CASE(VectorSolveLowerFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<std::complex<double> > y(6, 0.0);
    Matrix<double> a(4, 7, 1.0);

    BOOST_CHECK(!solveLower(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveLower(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveLower(a, y));
    
    y.resize(7, 0.0);

    BOOST_CHECK(solveLower(a, y));

    BOOST_CHECK(ZeroVector<std::complex<double> >(7) == y);

    // ---------

    Vector<std::complex<double> > x(7, 0.0);

    for (Vector<std::complex<double> >::SizeType i = 0; i < x.getSize(); i++)
        x(i) = (i % 2 == 0 ? 1 : -1) * (double(i + 1) + double(i) / 10);

    typedef Matrix<double>::SizeType SizeType;

    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (j > i)
                a(i, j) = 0.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveLower(a, y));

    BOOST_CHECK(equals(x, y, 0.0000001));
}

BOOST_AUTO_TEST_CASE(VectorSolveUnitLowerFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<std::complex<double> > y(6, 0.0);
    Matrix<double> a(4, 7, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));
    
    y.resize(7, 0.0);

    BOOST_CHECK(solveUnitLower(a, y));

    BOOST_CHECK(ZeroVector<std::complex<double> >(7) == y);

    // ---------

    Vector<std::complex<double> > x(7, 0.0);

    for (Vector<std::complex<double> >::SizeType i = 0; i < x.getSize(); i++)
        x(i) = (i % 2 == 0 ? 1 : -1) * (double(i + 1) + double(i) / 10);

    typedef Matrix<double>::SizeType SizeType;

    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (j > i)
                a(i, j) = 0.0;
            else if (i == j)
                a(i, j) = 1.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveUnitLower(a, y));

    BOOST_CHECK(equals(x, y, 0.0000001));
}

BOOST_AUTO_TEST_CASE(MatrixSolveLowerFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<std::complex<double> > y(6, 8, 0.0);
    Matrix<std::complex<double> > a(4, 7, 1.0);

    BOOST_CHECK(!solveLower(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveLower(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveLower(a, y));
    
    y.resize(8, 7);

    BOOST_CHECK(!solveLower(a, y));
    
    y.resize(7, 8);
    a.resize(6, 7, true, 1.0);

    BOOST_CHECK(!solveLower(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(solveLower(a, y));

    BOOST_CHECK(ZeroMatrix<std::complex<double> >(7, 8) == y);

    // ---------

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    Matrix<std::complex<double> > x(7, 8);

    for (SizeType i = 0; i < x.getSize1(); i++)
        for (SizeType j = 0; j < x.getSize2(); j++)
            x(i, j) = (((i + 2) * x.getSize1() + j) % 2 == 0 ? -1 : 1) * double((i + 5) * x.getSize1() + j) / 14.2345;
        
    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (j > i)
                a(i, j) = 0.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveLower(a, y));

    BOOST_CHECK(equals(x, y, 0.0000001));
}

BOOST_AUTO_TEST_CASE(MatrixSolveUnitLowerFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<std::complex<double> > y(6, 8, 0.0);
    Matrix<std::complex<double> > a(4, 7, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));
    
    y.resize(8, 7);

    BOOST_CHECK(!solveUnitLower(a, y));
    
    y.resize(7, 8);
    a.resize(6, 7, true, 1.0);

    BOOST_CHECK(!solveUnitLower(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(solveUnitLower(a, y));

    BOOST_CHECK(ZeroMatrix<std::complex<double> >(7, 8) == y);

    // ---------

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    Matrix<std::complex<double> > x(7, 8);

    for (SizeType i = 0; i < x.getSize1(); i++)
        for (SizeType j = 0; j < x.getSize2(); j++)
            x(i, j) = (((i + 2) * x.getSize1() + j) % 2 == 0 ? -1 : 1) * double((i + 5) * x.getSize1() + j) / 14.2345;
        
    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (j > i)
                a(i, j) = 0.0;
            else if (i == j)
                a(i, j) = 1.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveUnitLower(a, y));

    BOOST_CHECK(equals(x, y, 0.000001));
}

BOOST_AUTO_TEST_CASE(VectorSolveUpperFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<std::complex<double> > y(6, 0.0);
    Matrix<std::complex<double> > a(4, 7, 1.0);

    BOOST_CHECK(!solveUpper(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveUpper(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveUpper(a, y));
    
    y.resize(7, 0.0);

    BOOST_CHECK(solveUpper(a, y));

    BOOST_CHECK(ZeroVector<std::complex<double> >(7) == y);

    // ---------

    Vector<std::complex<double> > x(7, 0.0);

    for (Vector<std::complex<double> >::SizeType i = 0; i < x.getSize(); i++)
        x(i) = (i % 2 == 0 ? 1 : -1) * (double(i + 1) + double(i) / 10);

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (i > j)
                a(i, j) = 0.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveUpper(a, y));

    BOOST_CHECK(equals(x, y, 0.0000001));
}

BOOST_AUTO_TEST_CASE(VectorSolveUnitUpperFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<std::complex<double> > y(6, 0.0);
    Matrix<std::complex<double> > a(4, 7, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));
    
    y.resize(7, 0.0);

    BOOST_CHECK(solveUnitUpper(a, y));

    BOOST_CHECK(ZeroVector<std::complex<double> >(7) == y);

    // ---------

    Vector<std::complex<double> > x(7, 0.0);

    for (Vector<std::complex<double> >::SizeType i = 0; i < x.getSize(); i++)
        x(i) = (i % 2 == 0 ? 1 : -1) * (double(i + 1) + double(i) / 10);

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (i > j)
                a(i, j) = 0.0;
            else if (i == j)
                a(i, j) = 1.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveUnitUpper(a, y));

    BOOST_CHECK(equals(x, y, 0.0000001));
}

BOOST_AUTO_TEST_CASE(MatrixSolveUpperFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<std::complex<double> > y(6, 8, 0.0);
    Matrix<std::complex<double> > a(4, 7, 1.0);

    BOOST_CHECK(!solveUpper(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveUpper(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveUpper(a, y));
    
    y.resize(8, 7);

    BOOST_CHECK(!solveUpper(a, y));
    
    y.resize(7, 8);
    a.resize(6, 7, true, 1.0);

    BOOST_CHECK(!solveUpper(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(solveUpper(a, y));

    BOOST_CHECK(ZeroMatrix<std::complex<double> >(7, 8) == y);

    // ---------

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    Matrix<std::complex<double> > x(7, 8);

    for (SizeType i = 0; i < x.getSize1(); i++)
        for (SizeType j = 0; j < x.getSize2(); j++)
            x(i, j) = (((i + 2) * x.getSize1() + j) % 2 == 0 ? -1 : 1) * double((i + 5) * x.getSize1() + j) / 14.2345;
        
    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (i > j)
                a(i, j) = 0.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveUpper(a, y));

    BOOST_CHECK(equals(x, y, 0.0000001));
}

BOOST_AUTO_TEST_CASE(MatrixSolveUnitUpperFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Matrix<std::complex<double> > y(6, 8, 0.0);
    Matrix<std::complex<double> > a(4, 7, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));

    a.resize(7, 4, true, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));
    
    y.resize(8, 7);

    BOOST_CHECK(!solveUnitUpper(a, y));
    
    y.resize(7, 8);
    a.resize(6, 7, true, 1.0);

    BOOST_CHECK(!solveUnitUpper(a, y));

    a.resize(7, 7, true, 1.0);

    BOOST_CHECK(solveUnitUpper(a, y));

    BOOST_CHECK(ZeroMatrix<std::complex<double> >(7, 8) == y);

    // ---------

    typedef Matrix<std::complex<double> >::SizeType SizeType;

    Matrix<std::complex<double> > x(7, 8);

    for (SizeType i = 0; i < x.getSize1(); i++)
        for (SizeType j = 0; j < x.getSize2(); j++)
            x(i, j) = (((i + 2) * x.getSize1() + j) % 2 == 0 ? -1 : 1) * double((i + 5) * x.getSize1() + j) / 14.2345;
        
    for (SizeType i = 0; i < a.getSize1(); i++)
        for (SizeType j = 0; j < a.getSize2(); j++) {
            if (i > j)
                a(i, j) = 0.0;
            else if (i == j)
                a(i, j) = 1.0;
            else
                a(i, j) = (((i + 1) * a.getSize1() + j) % 2 == 0 ? 1 : -1) * double((i + 1) * a.getSize1() + j);
        }

    prod(a, x, y);

    BOOST_CHECK(solveUnitUpper(a, y));

    BOOST_CHECK(equals(x, y, 0.000001));
}
