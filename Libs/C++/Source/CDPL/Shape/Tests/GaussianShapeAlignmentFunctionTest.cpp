/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentFunctionTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Shape/GaussianShapeAlignmentFunction.hpp"
#include "CDPL/Shape/ExactGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/FastGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/IO.hpp"

#include "TestData.hpp"


BOOST_AUTO_TEST_CASE(GaussianShapeAlignmentFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;

	ExactGaussianShapeOverlapFunction exact_overlap_func;
	GaussianShapeFunction shape_func1, shape_func2;
	GaussianShape shape1(*TestData::getShapeData("1dwc_MIT", 2.7));
	GaussianShape shape2;

	shape_func1.setShape(shape1);

	Math::Vector3D ctr;

	shape_func1.calcCentroid(ctr);

	for (GaussianShape::ElementIterator it = shape1.getElementsBegin(), end = shape1.getElementsEnd(); it != end; ++it)
		it->setPosition(it->getPosition() - ctr);

	shape2 = shape1;

	//--

	shape_func1.setShape(shape1);
	shape_func2.setShape(shape2);
	
	exact_overlap_func.setShapeFunction(shape_func1, true);
	exact_overlap_func.setShapeFunction(shape_func2, false);

	GaussianShapeAlignmentFunction exact_alignment_func(exact_overlap_func);
	QuaternionTransformation xform;
	QuaternionTransformation xform_grad;

	xform[0] = std::cos(45.0 * M_PI / 180.0) - 0.03;
	xform[1] = std::sin(45.0 * M_PI / 180.0) * 1.0;
	xform[2] = std::sin(45.0 * M_PI / 180.0) * 0.0 ;
	xform[3] = std::sin(45.0 * M_PI / 180.0) * 0.0 + 0.001;
	xform[4] = 0.1;
	xform[5] = 0.9;
	xform[6] = 0.2;

	BOOST_CHECK_CLOSE(exact_alignment_func(xform, xform_grad),  exact_alignment_func(xform), 0.000001);
	
	for (std::size_t i = 0; i < 7; i++) {
		xform[i] += 0.000001;
		
		double num_grad = exact_alignment_func(xform);

		xform[i] -= 0.000002;

		num_grad = (num_grad - exact_alignment_func(xform)) / 0.000002;
		
		xform[i] += 0.000001;

		BOOST_TEST_MESSAGE("num grad " << i << ": " << num_grad << ", anal grad: " << xform_grad[i]);
		
		BOOST_CHECK_SMALL(std::abs(xform_grad[i] - num_grad), 0.001);
	}

	//--

	shape_func1.setMaxOrder(4);
	shape_func1.setShape(shape1);
	shape_func2.setMaxOrder(4);
	shape_func2.setShape(shape2);

	FastGaussianShapeOverlapFunction fast_overlap_func;
	
	//fast_overlap_func.fastExpFunction(false);
	fast_overlap_func.setShapeFunction(shape_func1, true);
	fast_overlap_func.setShapeFunction(shape_func2, false);

	GaussianShapeAlignmentFunction fast_alignment_func(fast_overlap_func);
	double w = 30.0;
	
	xform[0] = std::cos(0.5 * w * M_PI / 180.0);
	xform[1] = std::sin(0.5 * w * M_PI / 180.0) * 0.0;
	xform[2] = std::sin(0.5 * w * M_PI / 180.0) * 1.0 ;
	xform[3] = std::sin(0.5 * w * M_PI / 180.0) * 0.0;
	xform[4] = 0.8;
	xform[5] = -0.4;
	xform[6] = 0.0;

	BOOST_TEST_MESSAGE("self overlap = " << fast_overlap_func.calcSelfOverlap(true));
	BOOST_TEST_MESSAGE("fval before opt = " << fast_alignment_func(xform));
		
	Math::BFGSMinimizer<QuaternionTransformation> minimizer(boost::ref(fast_alignment_func), boost::ref(fast_alignment_func));

	minimizer.setup(xform, xform_grad, 0.01, 0.1);

	BOOST_TEST_MESSAGE("minimization status = " << minimizer.minimize(xform, xform_grad, 0, 0.1, -1.0, false));

	double quat_norm = std::sqrt(xform[0] * xform[0] + xform[1] * xform[1] + xform[2] * xform[2] + xform[3] * xform[3]);

	BOOST_TEST_MESSAGE("num iter = " << minimizer.getNumIterations());
	BOOST_TEST_MESSAGE("gnorm = " << minimizer.getGradientNorm());
	BOOST_TEST_MESSAGE("grad = " << xform_grad);
	BOOST_TEST_MESSAGE("xform = " << xform);
	BOOST_TEST_MESSAGE("opt fval = " << fast_alignment_func(xform));
	
	for (std::size_t i = 0; i < 4; i++)
		xform[i] /= quat_norm;

	BOOST_TEST_MESSAGE("norm xform = " << xform);
	BOOST_TEST_MESSAGE("norm xform fval = " << fast_alignment_func(xform));

}
