/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctionsTest.cpp 
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


#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/MatrixProxy.hpp"

#include "TestData.hpp"


BOOST_AUTO_TEST_CASE(CalcQuadrupoleTensorEigenDecompositionFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;

    Math::Vector3D ctr;
    Math::Matrix3D quad;
    Math::Matrix3D quad_evecs;
    Math::Vector3D quad_evals;

    GaussianShapeFunction shape_func;

    shape_func.setShape(*TestData::getShapeData("1dwc_MIT", 2.7));
    shape_func.calcCentroid(ctr);
    shape_func.calcQuadrupoleTensor(ctr, quad);

    calcQuadrupoleTensorEigenDecomposition(quad, quad_evecs, quad_evals);

    BOOST_CHECK_CLOSE(quad_evals[0], 3.34655, 0.001);
    BOOST_CHECK_CLOSE(quad_evals[1], 10.7481, 0.001);
    BOOST_CHECK_CLOSE(quad_evals[2], 6.43386, 0.001);
    
    for (std::size_t i = 0; i < 3; i++)
		BOOST_CHECK(Math::equals(quad * column(quad_evecs, i), column(quad_evecs, i) * quad_evals[i], 0.0001));
}

BOOST_AUTO_TEST_CASE(CalcPrincipalAxesFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;

    Math::Vector3D ctr;
    Math::Matrix3D quad;
    Math::Vector3D x_axis, y_axis, z_axis, dims;

    GaussianShape shape(*TestData::getShapeData("1dwc_MIT", 2.7));
    GaussianShapeFunction shape_func(shape);

    shape_func.calcCentroid(ctr);
    shape_func.calcQuadrupoleTensor(ctr, quad);

    double quad_values[3][3] = { { 3.43959, 0.495398, -0.438027 }, { 0.495398, 10.7038, -0.185749 }, { -0.438027, -0.185749, 6.3851 } };

    for (std::size_t i = 0; i < 3; i++)
		for (std::size_t j = 0; j < 3; j++)
			BOOST_CHECK_CLOSE(quad(i, j), quad_values[i][j], 0.001);

    calcPrincipalAxes(quad, x_axis, y_axis, z_axis, dims);

    BOOST_CHECK_CLOSE(dims[0], 10.7481, 0.001);
    BOOST_CHECK_CLOSE(dims[1], 6.43386, 0.001);
    BOOST_CHECK_CLOSE(dims[2], 3.34655, 0.001);
    
    Math::Matrix3D rot_mtx;

    row(rot_mtx, 0) = x_axis;
    row(rot_mtx, 1) = y_axis;
    row(rot_mtx, 2) = z_axis;

    for (GaussianShape::ElementIterator it = shape.getElementsBegin(), end = shape.getElementsEnd(); it != end; ++it) {
		GaussianShape::Element& elem = *it;

		elem.setPosition(rot_mtx * (elem.getPosition() - ctr));
    }

    shape_func.setShape(shape);

    shape_func.calcCentroid(ctr);
    shape_func.calcQuadrupoleTensor(ctr, quad);

    for (std::size_t i = 0; i < 3; i++)
		for (std::size_t j = 0; j < 3; j++) {
			if (i == j)
				BOOST_CHECK_CLOSE(quad(i, j), dims[i], 0.00001);
			else
				BOOST_CHECK_SMALL(quad(i, j), 0.00001);
		}
}

BOOST_AUTO_TEST_CASE(MatrixToQuaternionFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;
	
    boost::random::mt11213b rand_engine;
    boost::random::uniform_real_distribution<double> transl_dist(-100.0, 100.0);
    boost::random::uniform_real_distribution<double> rot_axis_dist(-1.0, 1.0);
    boost::random::uniform_real_distribution<double> rot_angle_dist(-M_PI + 0.1, M_PI - 0.1);
    QuaternionTransformation quat;
	    
    for (std::size_t i = 0; i < 100; i++) {
		Math::Vector3D rot_axis = Math::vec(rot_axis_dist(rand_engine), rot_axis_dist(rand_engine), rot_axis_dist(rand_engine));
		double rot_angle = rot_angle_dist(rand_engine);
		Math::Vector3D transl = Math::vec(transl_dist(rand_engine), transl_dist(rand_engine), transl_dist(rand_engine));

		rot_axis /= length(rot_axis);

		Math::Matrix4D orig_rot_mtx = Math::RotationMatrix<double>(4, rot_angle, rot_axis[0], rot_axis[1], rot_axis[2]);
		Math::Matrix4D xform_mtx = Math::TranslationMatrix<double>(4, transl[0], transl[1], transl[2]) * orig_rot_mtx;

		matrixToQuaternion(xform_mtx, quat);
	
		for (std::size_t j = 0; j < 3; j++)
			BOOST_CHECK_CLOSE(quat[4 + j], transl[j], 0.00001);

		BOOST_CHECK_CLOSE(std::abs(quat[0]), std::abs(std::cos(rot_angle / 2)), 0.0001);

		for (std::size_t j = 0; j < 3; j++)
			BOOST_CHECK_CLOSE(std::abs(quat[j + 1]), std::abs(std::sin(rot_angle / 2) * rot_axis[j]), 0.0001);

		BOOST_CHECK(Math::equals(orig_rot_mtx, Math::RotationMatrix<double>(4, Math::quat(quat[0], quat[1], quat[2], quat[3])), 0.0001));
    }
}

BOOST_AUTO_TEST_CASE(QuaternionToMatrixFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;
	
    boost::random::mt11213b rand_engine;
    boost::random::uniform_real_distribution<double> transl_dist(-100.0, 100.0);
    boost::random::uniform_real_distribution<double> rot_axis_dist(-1.0, 1.0);
    boost::random::uniform_real_distribution<double> rot_angle_dist(-M_PI + 0.1, M_PI - 0.1);
    QuaternionTransformation quat;
	    
    for (std::size_t i = 0; i < 10; i++) {
		Math::Vector3D rot_axis = Math::vec(rot_axis_dist(rand_engine), rot_axis_dist(rand_engine), rot_axis_dist(rand_engine));
		double rot_angle = rot_angle_dist(rand_engine);
		Math::Vector3D transl = Math::vec(transl_dist(rand_engine), transl_dist(rand_engine), transl_dist(rand_engine));

		rot_axis /= length(rot_axis);

		Math::Matrix4D orig_rot_mtx = Math::RotationMatrix<double>(4, rot_angle, rot_axis[0], rot_axis[1], rot_axis[2]);
		Math::Matrix4D xform_mtx = Math::TranslationMatrix<double>(4, transl[0], transl[1], transl[2]) *
			Math::RotationMatrix<double>(4, rot_angle, rot_axis[0], rot_axis[1], rot_axis[2]);

		quat[0] = std::cos(rot_angle / 2);

		for (std::size_t j = 0; j < 3; j++)
			quat[j + 1] = std::sin(rot_angle / 2) * rot_axis[j];

		for (std::size_t j = 0; j < 3; j++)
			quat[j + 4] = transl[j];

		Math::Matrix4D quat_xform_mtx;
	
		quaternionToMatrix(quat, quat_xform_mtx);
	
		BOOST_CHECK(Math::equals(xform_mtx, quat_xform_mtx, 0.00001));
    }
}
