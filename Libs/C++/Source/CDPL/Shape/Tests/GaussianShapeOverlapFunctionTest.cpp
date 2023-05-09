/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunctionTest.cpp 
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

#include "CDPL/Shape/ExactGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/FastGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Math/AffineTransform.hpp"

#include "TestData.hpp"
#include "../Utilities.hpp"


namespace
{

	double calcGradientRMS(const CDPL::Math::Vector3DArray& grad)
	{
		double rms = 0.0;

		for (std::size_t i = 0; i < grad.getSize(); i++)
			rms += innerProd(grad[i], grad[i]);

		return (std::sqrt(rms / (grad.getSize() * 3)));
	}
}


BOOST_AUTO_TEST_CASE(GaussianShapeOverlapFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;
	
	ExactGaussianShapeOverlapFunction exact_overlap_func;
	FastGaussianShapeOverlapFunction fast_overlap_func;
	GaussianShapeFunction shape_func1, shape_func2;
	Math::Vector3DArray overlap_grad;
	Math::Vector3DArray shape_elem_coords;
	
	shape_func1.setShape(*TestData::getShapeData("1dwc_MIT", 2.7));
	shape_func2 = shape_func1;

	getCoordinates(*shape_func2.getShape(), shape_elem_coords);
	
	exact_overlap_func.setShapeFunction(shape_func1, true);
	exact_overlap_func.setShapeFunction(shape_func2, false);
	fast_overlap_func.setShapeFunction(shape_func1, true);
	fast_overlap_func.setShapeFunction(shape_func2, false);

	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlap(), 341.132, 0.01);
	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlap(shape_elem_coords), 341.132, 0.01);
	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlapGradient(shape_elem_coords, overlap_grad), 341.132, 0.01);
	BOOST_CHECK_CLOSE(exact_overlap_func.calcSelfOverlap(true), 341.132, 0.01);
	BOOST_CHECK_CLOSE(exact_overlap_func.calcSelfOverlap(false), 341.132, 0.01);

	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlap(), 339.985, 0.01);
	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlap(shape_elem_coords), 339.985, 0.01);
	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlapGradient(shape_elem_coords, overlap_grad), 339.985, 0.01);
	BOOST_CHECK_CLOSE(fast_overlap_func.calcSelfOverlap(true), 339.985, 0.01);
	BOOST_CHECK_CLOSE(fast_overlap_func.calcSelfOverlap(false), 339.985, 0.01);

//-
	
	shape_func1.setShape(*TestData::getShapeData("4phv_VAC", 2.7));
	shape_func2 = shape_func1;

	getCoordinates(*shape_func2.getShape(), shape_elem_coords);

	exact_overlap_func.setShapeFunction(shape_func1, true);
	exact_overlap_func.setShapeFunction(shape_func2, false);
	fast_overlap_func.setShapeFunction(shape_func1, true);
	fast_overlap_func.setShapeFunction(shape_func2, false);

	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlap(), 431.894, 0.01);
	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlap(shape_elem_coords), 431.894, 0.01);

	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlap(), 430.85, 0.01);
	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlap(shape_elem_coords), 430.85, 0.01);

//-
	
	shape_func1.setShape(*TestData::getShapeData("1tmn_0ZN", 2.7));
	shape_func2 = shape_func1;

	getCoordinates(*shape_func2.getShape(), shape_elem_coords);

	exact_overlap_func.setShapeFunction(shape_func1, true);
	exact_overlap_func.setShapeFunction(shape_func2, false);
	fast_overlap_func.setShapeFunction(shape_func1, true);
	fast_overlap_func.setShapeFunction(shape_func2, false);

	Math::Vector3DArray trans_shape_elem_coords;

	trans_shape_elem_coords.resize(shape_elem_coords.getSize());

	transform(trans_shape_elem_coords, Math::TranslationMatrix<double>(4, 1.0, 0.0, 0.0), shape_elem_coords);
	
	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlap(), 335.628, 0.01);
	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlap(trans_shape_elem_coords), 277.618, 0.01);
	
	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlap(), 335.238, 0.01);
	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlap(trans_shape_elem_coords), 277.515, 0.01);
	
//-

	BOOST_CHECK_CLOSE(exact_overlap_func.calcOverlapGradient(shape_elem_coords, overlap_grad), exact_overlap_func.calcOverlap(), 0.000001);

	for (std::size_t i = 0, num_elem = shape_func2.getShape()->getNumElements(); i < num_elem; i++) {
		GaussianShape::Element& elem = const_cast<GaussianShape::Element&>(shape_func2.getShape()->getElement(i));
		Math::Vector3D elem_pos = elem.getPosition();
		
		for (std::size_t j = 0; j < 3; j++) {
			Math::Vector3D tmp = elem_pos;

			tmp[j] += 0.00001;
			
			elem.setPosition(tmp);
			shape_func2.setShape(*shape_func2.getShape());

			double num_grad = exact_overlap_func.calcOverlap();

			tmp[j] -= 0.00002;

			elem.setPosition(tmp);
			shape_func2.setShape(*shape_func2.getShape());

			num_grad = (num_grad - exact_overlap_func.calcOverlap()) / 0.00002;
			
			BOOST_CHECK_SMALL(std::abs(overlap_grad[i][j] - num_grad), 0.01);

			elem.setPosition(elem_pos);
		}
	}

	BOOST_CHECK_CLOSE(calcGradientRMS(overlap_grad), 2.642675, 0.01);

	//-

	fast_overlap_func.fastExpFunction(false);
	
	BOOST_CHECK_CLOSE(fast_overlap_func.calcOverlapGradient(shape_elem_coords, overlap_grad), fast_overlap_func.calcOverlap(), 0.0001);

	for (std::size_t i = 0, num_elem = shape_func2.getShape()->getNumElements(); i < num_elem; i++) {
		GaussianShape::Element& elem = const_cast<GaussianShape::Element&>(shape_func2.getShape()->getElement(i));
		Math::Vector3D elem_pos = elem.getPosition();
		
		for (std::size_t j = 0; j < 3; j++) {
			Math::Vector3D tmp = elem_pos;

			tmp[j] += 0.00001;
			
			elem.setPosition(tmp);
			shape_func2.setShape(*shape_func2.getShape());

			double num_grad = fast_overlap_func.calcOverlap();

			tmp[j] -= 0.00002;

			elem.setPosition(tmp);
			shape_func2.setShape(*shape_func2.getShape());

			num_grad = (num_grad - fast_overlap_func.calcOverlap()) / 0.00002;
			
			BOOST_CHECK_SMALL(std::abs(overlap_grad[i][j] - num_grad), 0.01);

			elem.setPosition(elem_pos);
		}
	}

	BOOST_CHECK_CLOSE(calcGradientRMS(overlap_grad), 2.659, 0.01);
}
