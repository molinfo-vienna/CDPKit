/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunctionTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Math/AffineTransform.hpp"

#include "TestData.hpp"


namespace
{

	double calcGradientRMS(const CDPL::Math::Vector3DArray& grad)
	{
		double rms = 0.0;

		for (std::size_t i = 0; i < grad.getSize(); i++)
			rms += innerProd(grad[i], grad[i]);

		return (std::sqrt(rms / grad.getSize()));
	}
}


BOOST_AUTO_TEST_CASE(GaussianShapeOverlapFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;
	
	GaussianShapeOverlapFunction overlap_func(*TestData::getShapeData("1dwc_MIT", 2.7), *TestData::getShapeData("1dwc_MIT", 2.7));
	
	BOOST_TEST_MESSAGE("1dwc_MIT shape volume: " << overlap_func.getShapeFunction(true).calcVolume());
	BOOST_TEST_MESSAGE("1dwc_MIT shape overlap: " << overlap_func.calcOverlap());

	overlap_func.setShape(*TestData::getShapeData("4phv_VAC", 2.7), true);
	overlap_func.setShape(*TestData::getShapeData("4phv_VAC", 2.7), false);

	BOOST_TEST_MESSAGE("4phv_VAC shape volume: " << overlap_func.getShapeFunction(true).calcVolume());
	BOOST_TEST_MESSAGE("4phv_VAC shape overlap: " << overlap_func.calcOverlap());

	overlap_func.setShape(*TestData::getShapeData("1tmn_0ZN", 2.7), true);
	overlap_func.setShape(*TestData::getShapeData("1tmn_0ZN", 2.7), false);

	BOOST_TEST_MESSAGE("1tmn_0ZN shape volume: " << overlap_func.getShapeFunction(true).calcVolume());
	BOOST_TEST_MESSAGE("1tmn_0ZN shape overlap: " << overlap_func.calcOverlap());
	BOOST_TEST_MESSAGE("1tmn_0ZN shape xform overlap: " << overlap_func.calcOverlap(Math::IdentityMatrix<double>(4, 4)));

	//

	Math::Vector3DArray overlap_grad;

	double overlap = overlap_func.calcOverlapGradient(Math::IdentityMatrix<double>(4, 4), overlap_grad);

	BOOST_TEST_MESSAGE("grad. overlap: " << overlap);
	BOOST_TEST_MESSAGE("anal. grad. RMS: " << calcGradientRMS(overlap_grad));
/*
	Math::Vector3DArray num_overlap_grad;
	std::size_t num_elem = shape_func2.getShape()->getNumElements();

	num_overlap_grad.resize(num_elem);

	for (std::size_t i = 0; i < num_elem; i++) {
		Math::Vector3D& grad = num_overlap_grad[i];
		GaussianShape::Element& elem = const_cast<GaussianShape::Element&>(shape_func2.getShape()->getElement(i));

		elem.setPosition(elem.getPosition() + Math::vec(0.00001, 0.0, 0.0));

		shape_func2.setShape(*shape_func2.getShape());
		overlap_func.setShapeFunction2(shape_func2);

		overlap = overlap_func.calcOverlap();

		elem.setPosition(elem.getPosition() + Math::vec(-2 * 0.00001, 0.0, 0.0));

		shape_func2.setShape(*shape_func2.getShape());
		overlap_func.setShapeFunction2(shape_func2);

		overlap -= overlap_func.calcOverlap();

		grad[0] = overlap / (2 * 0.00001);
		elem.setPosition(elem.getPosition() + Math::vec(0.00001, 0.0, 0.0));

//
		elem.setPosition(elem.getPosition() + Math::vec(0.0, 0.00001, 0.0));

		shape_func2.setShape(*shape_func2.getShape());
		overlap_func.setShapeFunction2(shape_func2);

		overlap = overlap_func.calcOverlap();

		elem.setPosition(elem.getPosition() + Math::vec(0.0, -2 * 0.00001, 0.0));

		shape_func2.setShape(*shape_func2.getShape());
		overlap_func.setShapeFunction2(shape_func2);

		overlap -= overlap_func.calcOverlap();

		grad[1] = overlap / (2 * 0.00001);
		elem.setPosition(elem.getPosition() + Math::vec(0.0, 0.00001, 0.0));
		   
//
		elem.setPosition(elem.getPosition() + Math::vec(0.0, 0.0, 0.00001));

		shape_func2.setShape(*shape_func2.getShape());
		overlap_func.setShapeFunction2(shape_func2);

		overlap = overlap_func.calcOverlap();

		elem.setPosition(elem.getPosition() + Math::vec(0.0, 0.0, -2 * 0.00001));

		shape_func2.setShape(*shape_func2.getShape());
		overlap_func.setShapeFunction2(shape_func2);

		overlap -= overlap_func.calcOverlap();

		grad[2] = overlap / (2 * 0.00001);
		elem.setPosition(elem.getPosition() + Math::vec(0.0, 0.0, 0.00001));
	}

	BOOST_TEST_MESSAGE("num. grad. RMS: " << calcGradientRMS(num_overlap_grad));
*/
}
