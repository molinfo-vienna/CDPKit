/* 
 * GaussianShapeFunctionTest.cpp 
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

#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"

#include "TestData.hpp"


BOOST_AUTO_TEST_CASE(GaussianShapeFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;

	GaussianShapeFunction shape_func;

	shape_func.setDistanceCutoff(-0.3);
	shape_func.setShape(*TestData::getShapeData("1crn", 2.7));

	BOOST_CHECK_CLOSE(shape_func.calcVolume(), 3736.27, 0.001);

	shape_func.setShape(*TestData::getShapeData("1crn", 2.6));
		
	BOOST_CHECK_CLOSE(shape_func.calcSurfaceArea(), 4245.87, 0.001);

	shape_func.setShape(*TestData::getShapeData("2ins", 2.7));

	BOOST_CHECK_CLOSE(shape_func.calcVolume(), 8720.19, 0.001);

	shape_func.setShape(*TestData::getShapeData("2ins", 2.6));
	
	BOOST_CHECK_CLOSE(shape_func.calcSurfaceArea(), 9857.26, 0.001);

	shape_func.setShape(*TestData::getShapeData("3app", 2.7));

	BOOST_CHECK_CLOSE(shape_func.calcVolume(), 26499.4, 0.001);

	shape_func.setShape(*TestData::getShapeData("3app", 2.6));
	
	BOOST_CHECK_CLOSE(shape_func.calcSurfaceArea(), 30439, 0.001);

	//---------

	shape_func.setDistanceCutoff(0.0);

	Math::Vector3D ctr;
	Math::Matrix3D quad;
	Math::Matrix3D quad_evecs;
	Math::Vector3D quad_evals;

	shape_func.setShape(*TestData::getShapeData("1dwc_MIT", 2.7));
	shape_func.calcCentroid(ctr);
	shape_func.calcQuadrupoleTensor(ctr, quad);
	
	calcQuadrupoleTensorEigenDecomposition(quad, quad_evecs, quad_evals);

	BOOST_CHECK_CLOSE(quad_evals[0], 3.34655, 0.001);
	BOOST_CHECK_CLOSE(quad_evals[1], 10.7481, 0.001);
	BOOST_CHECK_CLOSE(quad_evals[2], 6.43386, 0.001);

	//--
	
	shape_func.setShape(*TestData::getShapeData("4phv_VAC", 2.7));
	shape_func.calcCentroid(ctr);
	shape_func.calcQuadrupoleTensor(ctr, quad);
	
	calcQuadrupoleTensorEigenDecomposition(quad, quad_evecs, quad_evals);

	BOOST_CHECK_CLOSE(quad_evals[0], 22.907, 0.001);
	BOOST_CHECK_CLOSE(quad_evals[1], 1.75017, 0.001);
	BOOST_CHECK_CLOSE(quad_evals[2], 8.41608, 0.001);

	//--
	
	shape_func.setShape(*TestData::getShapeData("1tmn_0ZN", 2.7));
	shape_func.calcCentroid(ctr);
	shape_func.calcQuadrupoleTensor(ctr, quad);
	
	calcQuadrupoleTensorEigenDecomposition(quad, quad_evecs, quad_evals);

	BOOST_CHECK_CLOSE(quad_evals[0], 2.57599, 0.001);
	BOOST_CHECK_CLOSE(quad_evals[1], 8.60334, 0.001);
	BOOST_CHECK_CLOSE(quad_evals[2], 13.4186, 0.001);
}
