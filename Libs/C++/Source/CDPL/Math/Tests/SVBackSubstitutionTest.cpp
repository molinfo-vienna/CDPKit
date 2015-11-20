/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SVBackSubstitutionTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/SVBackSubstitution.hpp"
#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "Tools.hpp"


BOOST_AUTO_TEST_CASE(SVBackSubstitutionTest)
{
	using namespace CDPL;
	using namespace Math;

	double test_matrix_data[] = {  1,  12,  3,    4,   15,  10,
								   6,  0,   18,   19,  10,  60,
								   -1, -2,  -3,   -4,   5,   0,
								   2,  0,   3,   -3,   4,  -10, 
								   2,  10,  3.3, -3,   14,  3,
								   5,  4,   3,   -13,  14,  7.5,
								   5,  34, -10,  -13, -14,  1,
								   0, -1,   4,   -8,   10,  0 };

	double test_x_vec_data[] = { 1, 2, -6, 8, 11, -150 };

	Vector<double> test_x_vec(6);
	Vector<double> sol_x_vec(6);
	Matrix<double> u(8, 6);
	Vector<double> w(6);
	Matrix<double> v(6, 6);
	Vector<double> b;

	initMatrix(u, test_matrix_data);
	initVector(test_x_vec, test_x_vec_data);

	b = prod(u, test_x_vec);

	BOOST_CHECK(svDecomposition(u, w, v));

	svBackSubstitution(u, w, v, b, sol_x_vec);

	BOOST_CHECK_SMALL(norm_2(test_x_vec - sol_x_vec), 0.00001);
}

