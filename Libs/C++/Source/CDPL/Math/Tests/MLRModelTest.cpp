/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MLRModelTest.cpp 
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
#include <boost/test/floating_point_comparison.hpp>
#include <boost/random/linear_congruential.hpp>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#include "CDPL/Math/MLRModel.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Math/IO.hpp"


BOOST_AUTO_TEST_CASE(MLRModelTest)
{
	using namespace CDPL;
	using namespace Math;

	boost::rand48 rand;

	MLRModel<> mlr_model;

	Matrix<double> test_x_values(200, 100);
	Vector<double> test_calc_y(200);
	Vector<double> test_coeffs(100);
	
	for (std::size_t i = 0; i < 100; i++)
		test_coeffs(i) = 1e-8 * (rand() - rand.max() * 0.7); 

	for (std::size_t i = 0; i < 200; i++) 
		for (std::size_t j = 0; j < 100; j++)
			test_x_values(i, j) = 1e-7 * (rand() - rand.max() * 0.5); 

	test_calc_y = prod(test_x_values, test_coeffs);

	//-----

	mlr_model.resizeDataSet(200, 100);

	BOOST_CHECK(normFrob(mlr_model.getXMatrix()) == 0.0);
	BOOST_CHECK(norm2(mlr_model.getYValues()) == 0.0);

	for (std::size_t i = 50; i <= 150; i++) {
		mlr_model.setXYData(i, ScalarVector<double>(i, 1.0), i);
	}

	BOOST_CHECK_CLOSE(double(normFrob(mlr_model.getXMatrix())), std::sqrt(100.0 * 101.0), 0.0001);
	
	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 200 &&
				const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 150);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 200 && 
				const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 150);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getYValues().getSize() == 200);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getYValues().getSize() == 200);

	//-----

	mlr_model.resizeDataSet(100, 100);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 100 &&
				const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 100);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 100 &&
				const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 100);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getYValues().getSize() == 100);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getYValues().getSize() == 100);

	for (std::size_t i = 0; i < 200; i++) 
		mlr_model.setXYData(i, row(test_x_values, i), test_calc_y(i));

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 200 &&
				const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 100);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 200 &&
				const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 100);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getYValues().getSize() == 200);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getYValues().getSize() == 200);

	mlr_model.buildModel();

	BOOST_CHECK(mlr_model.getCoefficients().getSize() == 100);
	BOOST_CHECK_SMALL(norm2(mlr_model.getCoefficients() - test_coeffs), 0.00001);

	BOOST_CHECK_CLOSE(mlr_model.calcYValue(row(test_x_values, 0)), test_calc_y(0), 0.00001);
	BOOST_CHECK_CLOSE(mlr_model(row(test_x_values, 112)), test_calc_y(112), 0.00001);

	BOOST_CHECK_THROW(mlr_model.calcYValue(CVector<double, 90>()), Base::CalculationFailed);
	BOOST_CHECK_THROW(mlr_model(CVector<double, 90>()), Base::CalculationFailed);

	mlr_model.calcStatistics();
	
	BOOST_CHECK_SMALL(mlr_model.getChiSquare(), 0.00001);
	BOOST_CHECK_SMALL(mlr_model.getStandardDeviation(), 0.00001);
	BOOST_CHECK_CLOSE(1.0, mlr_model.getCorrelationCoefficient(), 0.00001);
	BOOST_CHECK_CLOSE(1.0, mlr_model.getGoodnessOfFit(), 0.00001);

	//-----

	mlr_model.clearDataSet();

	BOOST_CHECK(normFrob(mlr_model.getXMatrix()) == 0.0);
	BOOST_CHECK(norm2(mlr_model.getYValues()) == 0.0);

	for (std::size_t i = 0; i < 100; i++) 
		mlr_model.addXYData(ScalarVector<double>(i, 1.0), 0.0);

	for (std::size_t i = 0; i < 100; i++) 
		mlr_model.addXYData(ScalarVector<double>(100 - i - 1, 1.0), 0.0);

	BOOST_CHECK_CLOSE(double(normFrob(mlr_model.getXMatrix())), std::sqrt(100 * 99.0), 0.00001);
	BOOST_CHECK_SMALL(double(norm2(mlr_model.getYValues())), 0.000001);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 200 &&
				const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 99);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 200 && 
				const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 99);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getYValues().getSize() == 200);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getYValues().getSize() == 200);

	//-----

	mlr_model.clearDataSet();

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 0 &&
				const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 0);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 0 &&
				const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 0);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getYValues().getSize() == 0);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getYValues().getSize() == 0);

	for (std::size_t i = 0; i < 150; i++) 
		mlr_model.addXYData(row(test_x_values, i), test_calc_y(i) + (i % 2 ? 1.0 : -1.0));

	BOOST_CHECK_SMALL(norm2(mlr_model.getCoefficients() - test_coeffs), 0.00001);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 150 &&
				const_cast<const MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 100);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize1() == 150 &&
				const_cast<MLRModel<>&>(mlr_model).getXMatrix().getSize2() == 100);

	BOOST_CHECK(const_cast<const MLRModel<>&>(mlr_model).getYValues().getSize() == 150);
	BOOST_CHECK(const_cast<MLRModel<>&>(mlr_model).getYValues().getSize() == 150);

	mlr_model.calcStatistics();

	BOOST_CHECK_CLOSE(mlr_model.getChiSquare(), 150.0, 0.00001);
	BOOST_CHECK_CLOSE(mlr_model.getStandardDeviation(), std::sqrt(150.0 / (150 - 100)), 0.00001);

	BOOST_CHECK_CLOSE(1.0, mlr_model.getCorrelationCoefficient(), 0.00001);
	
	mlr_model.getXMatrix().resize(149, 100);

	BOOST_CHECK_THROW(mlr_model.calcStatistics(), Base::CalculationFailed);

	mlr_model.getXMatrix().resize(150, 100);
	mlr_model.calcStatistics();

	mlr_model.resizeDataSet(150, 90);

	BOOST_CHECK_THROW(mlr_model.calcStatistics(), Base::CalculationFailed);
}
