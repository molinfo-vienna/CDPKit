/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctionTest.cpp 
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

#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "TestData.hpp"


BOOST_AUTO_TEST_CASE(GaussianShapeFunctionTest)
{
    using namespace CDPL;
    using namespace Shape;

	GaussianShapeFunction shape_func;
	
	shape_func.setup(*TestData::getShapeData("1crn", 2.7));

	BOOST_TEST_MESSAGE("1crn volume: " << shape_func.calcVolume());

	shape_func.setup(*TestData::getShapeData("1crn", 2.6));
		
	BOOST_TEST_MESSAGE("1crn surf. area: " << shape_func.calcSurfaceArea());

	shape_func.setup(*TestData::getShapeData("2ins", 2.7));

	BOOST_TEST_MESSAGE("2ins volume: " << shape_func.calcVolume());

	shape_func.setup(*TestData::getShapeData("2ins", 2.6));
	
	BOOST_TEST_MESSAGE("2ins surf. area: " << shape_func.calcSurfaceArea());

	shape_func.setup(*TestData::getShapeData("3app", 2.7));

	BOOST_TEST_MESSAGE("3app volume: " << shape_func.calcVolume());

	shape_func.setup(*TestData::getShapeData("3app", 2.6));
	
	BOOST_TEST_MESSAGE("3app surf. area: " << shape_func.calcSurfaceArea());
}
