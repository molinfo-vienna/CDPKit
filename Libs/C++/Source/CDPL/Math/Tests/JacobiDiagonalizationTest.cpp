/* 
 * JacobiDiagonalizationTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "Tools.hpp"


BOOST_AUTO_TEST_CASE(JacobiDiagonalizationTest)
{
    using namespace CDPL;
    using namespace Math;

    double test_matrix_data[] = { 5, 1, 2, 0, 4,
                                  1, 4, 2, 1, 3,
                                  2, 2, 5, 4, 0,
                                  0, 1, 4, 1, 3,
                                  4, 3, 0, 3, 4 };

    double test_eigenval_data[] = { 12.0258,   5.67255,    3.36188,  -3.55784,   1.49766 };
    double test_eigenvec_data[] = { 0.485108, -0.440209,   0.616027,  0.311869, -0.306813,
                                    0.411359,  0.0115005, -0.690171,  0.182146, -0.56669,
                                    0.450676,  0.712073,   0.2933,   -0.425024, -0.152226,
                                    0.343352,  0.334081,  -0.0830438, 0.662313,  0.570039,
                                    0.523884, -0.432927,  -0.22639,  -0.500256,  0.486427 };

    Matrix<double> a(5, 5);
    Matrix<double> v(5, 5);
    Vector<double> d(5);

    initMatrix(a, test_matrix_data);

    BOOST_CHECK(jacobiDiagonalize(a, d, v));

//-------

    Vector<double> test_eigenval_vec(5);

    initVector(test_eigenval_vec, test_eigenval_data); 

    BOOST_CHECK_SMALL(norm2(test_eigenval_vec - d), 0.0001); 

//-------

    CMatrix<double, 5, 5> test_eigenvec_mtx;

    initMatrix(test_eigenvec_mtx, test_eigenvec_data);

    BOOST_CHECK_SMALL(double(normFrob(test_eigenvec_mtx - v)), 0.00001); 

//-------

    initMatrix(a, test_matrix_data);

    BOOST_CHECK_SMALL(norm2(prod(a, column(v, 0)) - column(v, 0) * d(0)), 0.00001); 
    BOOST_CHECK_SMALL(norm2(prod(a, column(v, 1)) - column(v, 1) * d(1)), 0.00001); 
    BOOST_CHECK_SMALL(norm2(prod(a, column(v, 2)) - column(v, 2) * d(2)), 0.00001); 
    BOOST_CHECK_SMALL(norm2(prod(a, column(v, 3)) - column(v, 3) * d(3)), 0.00001); 
    BOOST_CHECK_SMALL(norm2(prod(a, column(v, 4)) - column(v, 4) * d(4)), 0.00001); 

//-------

    Matrix<double> fail_mtx(4, 5);

    BOOST_CHECK_THROW(jacobiDiagonalize(fail_mtx, d, v), Base::SizeError);

    fail_mtx.resize(0, 0);

    BOOST_CHECK_THROW(jacobiDiagonalize(fail_mtx, d, v), Base::SizeError);

    fail_mtx.resize(0, 1);

    BOOST_CHECK_THROW(jacobiDiagonalize(fail_mtx, d, v), Base::SizeError);

    fail_mtx.resize(1, 0);

    BOOST_CHECK_THROW(jacobiDiagonalize(fail_mtx, d, v), Base::SizeError);
}

