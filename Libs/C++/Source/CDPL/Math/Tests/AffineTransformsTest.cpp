/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AffineTransformsTest.cpp 
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


#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Math/AffineTransform.hpp"

#include "Tools.hpp"


BOOST_AUTO_TEST_CASE(AffineTransformsTest)
{
	using namespace CDPL;
	using namespace Math;

	double a = M_PI / 180.0 * 67.0;

	double test_x_scaling_mtx_data[] = { 4, 0, 0, 0,
										 0, 1, 0, 0,
										 0, 0, 1, 0,
										 0, 0, 0, 1 };
	
	double test_y_scaling_mtx_data[] = { 1, 0, 0, 0,
										 0, 3, 0, 0,
										 0, 0, 1, 0,
										 0, 0, 0, 1 };
	
	double test_z_scaling_mtx_data[] = { 1, 0, 0, 0,
										 0, 1, 0, 0,
										 0, 0, 5, 0,
										 0, 0, 0, 1 };
	
	double test_x_translation_mtx_data[] = { 1, 0, 0, 4,
											 0, 1, 0, 0,
											 0, 0, 1, 0,
											 0, 0, 0, 1 };
	
	double test_y_translation_mtx_data[] = { 1, 0, 0, 0,
											 0, 1, 0, 1,
											 0, 0, 1, 0,
											 0, 0, 0, 1 };
	
	double test_z_translation_mtx_data[] = { 1, 0, 0, 0,
											 0, 1, 0, 0,
											 0, 0, 1, 5,
											 0, 0, 0, 1 };
	
	double test_x_rotation_mtx_data[] = { 1, 0,            0,           0,
										  0, std::cos(a), -std::sin(a), 0,
										  0, std::sin(a),  std::cos(a), 0,
										  0, 0,            0,           1 };
	
	double test_y_rotation_mtx_data[] = {  std::cos(a), 0, std::sin(a), 0,
										   0,           1, 0,           0,
										  -std::sin(a), 0, std::cos(a), 0,
										   0,           0, 0,           1 };
	
	double test_z_rotation_mtx_data[] = { std::cos(a), -std::sin(a), 0, 0,
										  std::sin(a),  std::cos(a), 0, 0,
										  0,            0,           1, 0,
										  0,            0,           0, 1 };

	Matrix<double> mtx(4, 4);

//-----

	BOOST_CHECK_SMALL(double(norm_frobenius(AffineTransform<double, 4>() - IdentityMatrix<double>(4))), 0.00001);

//-----

	initMatrix(mtx, test_x_scaling_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(XScaling<double, 4>(4) - mtx)), 0.00001);

//-----

	initMatrix(mtx, test_y_scaling_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(YScaling<double, 4>(3) - mtx)), 0.00001);

//-----

	initMatrix(mtx, test_z_scaling_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(ZScaling<double, 4>(5) - mtx)), 0.00001);

//------

	initMatrix(mtx, test_x_translation_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(XTranslation<double, 4>(4) - mtx)), 0.00001);

//------

	initMatrix(mtx, test_y_translation_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(YTranslation<double, 4>(1) - mtx)), 0.00001);

//------


	initMatrix(mtx, test_z_translation_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(ZTranslation<double, 4>(5) - mtx)), 0.00001);

//------

	initMatrix(mtx, test_x_rotation_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(XRotation<double, 4>(a) - mtx)), 0.00001);

//------

	initMatrix(mtx, test_y_rotation_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(YRotation<double, 4>(a) - mtx)), 0.00001);

//------

	initMatrix(mtx, test_z_rotation_mtx_data);

	BOOST_CHECK_SMALL(double(norm_frobenius(ZRotation<double, 4>(a) - mtx)), 0.00001);

//------

	XScaling3D s(2.0);

	s.concatenate(YScaling3D(4.0)).concatenate(ZScaling3D(6.0));

	BOOST_CHECK_CLOSE(s(0, 0), 2.0, 0.00001);
	BOOST_CHECK_CLOSE(s(1, 1), 4.0, 0.00001);
	BOOST_CHECK_CLOSE(s(2, 2), 6.0, 0.00001);

//------

	ZRotation3D r(M_PI * 0.5);

	r.concatenate(YRotation3D(M_PI));

	BOOST_CHECK_SMALL(norm_2(prod(ZRotation3D(-M_PI * 0.5), UnitVector<double>(3, 0)) - prod(r, UnitVector<double>(3, 0))), 0.00001);

//------

	Vector2D vec1;

	BOOST_CHECK(vec1(0) == 0.0);
	BOOST_CHECK(vec1(1) == 0.0);

	transformPoint(vec1, XTranslation<double, 1>(3.0));

	BOOST_CHECK_SMALL(vec1(0), 0.00001);
	BOOST_CHECK_SMALL(vec1(1), 0.00001);

	transformPoint(vec1, XTranslation<double, 2>(3.0));

	BOOST_CHECK_SMALL(vec1(0), 0.00001);
	BOOST_CHECK_SMALL(vec1(1), 0.00001);

	transformPoint(vec1, XTranslation<double, 3>(4.0));

	BOOST_CHECK_CLOSE(vec1(0), 4.0, 0.00001);
	BOOST_CHECK_CLOSE(vec1(1), 0.0, 0.00001);

//------

	Vector2D vec2;

	transformVector(vec2, XTranslation<double, 1>(3.0));

	BOOST_CHECK_SMALL(vec2(0), 0.00001);
	BOOST_CHECK_SMALL(vec2(1), 0.00001);

	transformVector(vec2, XTranslation<double, 2>(3.0));

	BOOST_CHECK_SMALL(vec2(0), 0.00001);
	BOOST_CHECK_SMALL(vec2(1), 0.00001);

	transformVector(vec2, XTranslation<double, 3>(4.0));

	BOOST_CHECK_SMALL(vec2(0), 0.00001);
	BOOST_CHECK_SMALL(vec2(1), 0.00001);

//------

	Vector2D vec3(1.0, 0.0);

	BOOST_CHECK(vec3(0) == 1.0);
	BOOST_CHECK(vec3(1) == 0.0);

	transformVector(vec3, XTranslation<double, 1>(3.0));

	BOOST_CHECK_CLOSE(vec3(0), 1.0, 0.00001);
	BOOST_CHECK_SMALL(vec3(1), 0.00001);

	transformVector(vec3, XTranslation<double, 2>(4.0));

	BOOST_CHECK_CLOSE(vec3(0), 1.0, 0.00001);
	BOOST_CHECK_SMALL(vec3(1), 0.00001);

	transformVector(vec3, XTranslation<double, 3>(5.0));

	BOOST_CHECK_CLOSE(vec3(0), 1.0, 0.00001);
	BOOST_CHECK_SMALL(vec3(1), 0.00001);

	transformVector(vec3, ZRotation<double, 2>(M_PI * 0.5));

	BOOST_CHECK_SMALL(vec3(0), 0.00001);
	BOOST_CHECK_CLOSE(vec3(1), 1.0, 0.00001);

}

