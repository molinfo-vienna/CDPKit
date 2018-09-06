/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGCoordinatesGeneratorTest.cpp 
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


#include <vector>
#include <cstddef>
#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include "CDPL/Util/DGCoordinatesGenerator.hpp"
#include "CDPL/Math/Vector.hpp"


BOOST_AUTO_TEST_CASE(DGCoordinatesGeneratorTest)
{
	using namespace CDPL;
	using namespace Util;
	
	const std::size_t NUM_POINTS = 100;
	const double      BOX_SIZE   = 50.0; 
	const double      MAX_ERROR  = 0.25; 

	DGCoordinatesGenerator<3, double> coords_gen;
	std::vector<Math::Vector3D> test_points(NUM_POINTS);
	boost::random::mt19937 rand_eng;
	boost::random::uniform_real_distribution<double> rand_dist(0.0, BOX_SIZE);

	for (std::size_t i = 0; i < NUM_POINTS; i++) {
		test_points[i][0] = rand_dist(rand_eng);
		test_points[i][1] = rand_dist(rand_eng);
		test_points[i][2] = rand_dist(rand_eng);
	}

	for (std::size_t i = 0; i < NUM_POINTS; i++) {
		for (std::size_t j = i + 1; j < NUM_POINTS; j++) {
			double dist = length(test_points[i] - test_points[j]);

			coords_gen.addDistanceConstraint(i, j, dist, dist);
		}
	}

	coords_gen.setNumPoints(NUM_POINTS);
	coords_gen.setBoxSize(BOX_SIZE);
	coords_gen.setMaxError(MAX_ERROR);
	coords_gen.generate();

	std::vector<Math::Vector3D> gen_coords(NUM_POINTS);

	coords_gen.getCoordinates(gen_coords);

	double rms_dev = 0.0;

	for (std::size_t i = 0; i < NUM_POINTS; i++) {
		for (std::size_t j = i + 1; j < NUM_POINTS; j++) {
			double orig_dist = length(test_points[i] - test_points[j]);
			double gen_dist = length(gen_coords[i] - gen_coords[j]);
			double diff = orig_dist - gen_dist;

			rms_dev += diff * diff;
		}
	}

	rms_dev = std::sqrt(rms_dev / (NUM_POINTS * (NUM_POINTS - 1) * 0.5));

	std::cerr << " RMSD = " << rms_dev << std::endl;
}

