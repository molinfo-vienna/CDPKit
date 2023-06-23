/* 
 * KabschAlgorithmTest.cpp 
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


#include <cstddef>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Math/KabschAlgorithm.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(KabschAlgorithmTest)
{
    using namespace CDPL;
    using namespace Math;

    double points[][3] = { 
        { 1, 1, 1},
	{ 0, 1, 1},
	{ 0, 1, 0},
	{ 1, 1, 0},
	{ 1, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 0},
	{ 1, 0, 0}
    }; 

    Matrix<double> points_mtx(3, 8);
    Matrix<double> ref_points_mtx(3, 8);
    KabschAlgorithm<double> algo;

    for (std::size_t i = 0; i < 3; i++)
	for (std::size_t j = 0; j < 8; j++)
	    points_mtx(i, j) = points[j][i];
    
    // ---------

    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(2, 3, 1.0), ScalarVector<double>(8, 1.0)), Base::SizeError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 5, 1.0), ScalarVector<double>(8, 1.0)), Base::SizeError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 9, 1.0), ScalarVector<double>(8, 1.0)), Base::SizeError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 8, 1.0), ScalarVector<double>(7, 1.0)), Base::SizeError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 8, 1.0), ScalarVector<double>(9, 1.0)), Base::SizeError);

    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 8, 1.0), ScalarVector<double>(8, 0.0)), Base::ValueError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 8, 1.0), ScalarVector<double>(8, -1.0)), Base::ValueError);
 
   // ---------

    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(2, 3, 1.0)), Base::SizeError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 5, 1.0)), Base::SizeError);
    BOOST_CHECK_THROW(algo.align(points_mtx, ScalarMatrix<double>(3, 9, 1.0)), Base::SizeError);

    // ---------

    ref_points_mtx = points_mtx;

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, ScalarVector<double>(8, 1.0)));
    BOOST_CHECK(equals(algo.getTransform(), IdentityMatrix<double>(4, 4), 1.0e-13));
 
    // ---------

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx));
    BOOST_CHECK(equals(algo.getTransform(), IdentityMatrix<double>(4, 4), 1.0e-13));

    // ---------

    ref_points_mtx += outerProd(vec(4.0, 5.0, 6.0), ScalarVector<double>(8, 1.0)); 

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, ScalarVector<double>(8, 0.4)));
    BOOST_CHECK(equals(algo.getTransform(), TranslationMatrix<double>(4, 4.0, 5.0, 6.0), 1.0e-13));
  
    // ---------

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx));
    BOOST_CHECK(equals(algo.getTransform(), TranslationMatrix<double>(4, 4.0, 5.0, 6.0), 1.0e-13));

    // ---------

    points_mtx += outerProd(vec(3.0, 2.0, 1.0), ScalarVector<double>(8, 1.0)); 

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, ScalarVector<double>(8, 1.4)));
    BOOST_CHECK(equals(algo.getTransform(), TranslationMatrix<double>(4, 1.0, 3.0, 5.0), 1.0e-13));

    // ---------

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx));
    BOOST_CHECK(equals(algo.getTransform(), TranslationMatrix<double>(4, 1.0, 3.0, 5.0), 1.0e-13));

    // ---------

    ref_points_mtx = prod(RotationMatrix<double>(3, 37.2 * M_PI / 180.0, 0.0, 0.0, 1.0), points_mtx);
    ref_points_mtx = prod(RotationMatrix<double>(3, 13.2 * M_PI / 180.0, 0.0, 1.0, 0.0), ref_points_mtx);
    ref_points_mtx += outerProd(vec(-13.2, 3.4, -5.6), ScalarVector<double>(8, 1.0));

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, ScalarVector<double>(8, 1.0)));

    Vector4D vec1 = vec(0, 0, 0, 1.0), vec2 = vec(0, 0, 0, 1.0);

    for (std::size_t i = 0; i < 8; i++) {
	range(vec1, 0, 3) = column(points_mtx, i);
	range(vec2, 0, 3) = column(ref_points_mtx, i);
	BOOST_CHECK_SMALL(norm2(algo.getTransform() * vec1 - vec2), 1.0e-13);
    }

    // ---------
  
    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx));

    for (std::size_t i = 0; i < 8; i++) {
	range(vec1, 0, 3) = column(points_mtx, i);
	range(vec2, 0, 3) = column(ref_points_mtx, i);
	BOOST_CHECK_SMALL(norm2(algo.getTransform() * vec1 - vec2), 1.0e-13);
    }

    // ---------
  
    Matrix<double> orig_xform = RotationMatrix<double>(3, 13.2 * M_PI / 180.0, 0.0, 1.0, 0.0) *
	RotationMatrix<double>(3, 37.2 * M_PI / 180.0, 0.0, 0.0, 1.0);

    ref_points_mtx = prod(orig_xform, points_mtx);

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, ScalarVector<double>(8, 1.0), true));

    Matrix<double> xform = algo.getTransform();

    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, ScalarVector<double>(8, 1.0), false));

    BOOST_CHECK(equals(xform, algo.getTransform(), 1.0e-13));
    BOOST_CHECK(equals(vec(0, 0, 0, 1.0), column(xform, 3), 1.0e-13));

    BOOST_CHECK(equals(orig_xform, range(algo.getTransform(), 0, 3, 0, 3), 1.0e-13));
  
    // ---------
  
    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, false));

    BOOST_CHECK(equals(xform, algo.getTransform(), 1.0e-13));

    // ---------
  
    BOOST_CHECK(algo.align(points_mtx, ref_points_mtx, true));

    BOOST_CHECK(equals(xform, algo.getTransform(), 1.0e-13));
}

