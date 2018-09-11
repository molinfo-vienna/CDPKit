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
#include "CDPL/Math/IO.hpp"


namespace
{

	typedef std::vector<CDPL::Math::Vector3D> CoordsArray;

	double calcVolume(std::size_t pt_inds[4], const CoordsArray& coords)
	{
		using namespace CDPL;

		const Math::Vector3D& pt1 = coords[pt_inds[0]];
		const Math::Vector3D& pt2 = coords[pt_inds[1]];
		const Math::Vector3D& pt3 = coords[pt_inds[2]];
		const Math::Vector3D& pt4 = coords[pt_inds[3]];

		return innerProd(pt1 - pt4, crossProd(pt2 - pt4, pt3 - pt4)) / 6.0;
	}
}


BOOST_AUTO_TEST_CASE(DGCoordinatesGeneratorTest)
{
	using namespace CDPL;
	using namespace Util;
	
	const std::size_t NUM_POINTS     = 1000;
	const std::size_t MAX_NUM_TRIALS = 5;
	const double      BOX_SIZE       = 100.0; 

	std::size_t VOL_CONSTRAINT_INDS[][4] = {
	    { 0, 1, 2, 3 },
	    { 2, 10, 12, 22 },
	    { 1, 4, 8, 11 },
	    { 4, 5, 6, 7 },
	    { 5, 16, 17, 24 }
	};

	std::size_t NUM_VOL_CONSTRAINTS = 5;

	DGCoordinatesGenerator<3, double> coords_gen;
	CoordsArray test_points(NUM_POINTS);
	CoordsArray gen_coords(NUM_POINTS);

	boost::random::mt19937 rand_eng(100);
	boost::random::uniform_real_distribution<double> rand_dist(0.0, BOX_SIZE);

	// generate random test point set

	for (std::size_t i = 0; i < NUM_POINTS; i++) {
		test_points[i][2] = rand_dist(rand_eng);
		test_points[i][1] = rand_dist(rand_eng);
		test_points[i][0] = rand_dist(rand_eng);
	}

	// specify distance constraints from inter test point distances

	for (std::size_t i = 0; i < NUM_POINTS; i++) {
		for (std::size_t j = i + 1; j < NUM_POINTS; j++) {
			double dist = length(test_points[i] - test_points[j]);
			
			coords_gen.addDistanceConstraint(i, j, dist, dist);
		}
	}

	// specify volume constraints using arbitrary quadruples of the test points

	for (std::size_t i = 0; i < NUM_VOL_CONSTRAINTS; i++) {
		double vol = calcVolume(VOL_CONSTRAINT_INDS[i], test_points);

		coords_gen.addVolumeConstraint(VOL_CONSTRAINT_INDS[i][0], VOL_CONSTRAINT_INDS[i][1], VOL_CONSTRAINT_INDS[i][2], VOL_CONSTRAINT_INDS[i][3],
									   vol, vol);
	}

	// setup DG coordinates generator and run

	coords_gen.setNumPoints(NUM_POINTS);
	coords_gen.setBoxSize(BOX_SIZE);

	std::size_t num_trials = 0;

	for ( ; num_trials < MAX_NUM_TRIALS; num_trials++) {
		coords_gen.generate();
		
		if (coords_gen.getDistanceError() < 0.5 && coords_gen.getVolumeError() < 0.5) 
			break;
	}

	BOOST_CHECK(num_trials < MAX_NUM_TRIALS);

	coords_gen.getCoordinates(gen_coords);

	// check results

	double dist_rms_dev = 0.0;

	for (std::size_t i = 0; i < NUM_POINTS; i++) {
		for (std::size_t j = i + 1; j < NUM_POINTS; j++) {
			double orig_dist = length(test_points[i] - test_points[j]);
			double gen_dist = length(gen_coords[i] - gen_coords[j]);
			double diff = orig_dist - gen_dist;

			dist_rms_dev += diff * diff;
		}
	}

	dist_rms_dev = std::sqrt(dist_rms_dev / (NUM_POINTS * (NUM_POINTS - 1) * 0.5));

	double vol_rms_dev = 0.0;

	for (std::size_t i = 0; i < NUM_VOL_CONSTRAINTS; i++) {
		double orig_vol = calcVolume(VOL_CONSTRAINT_INDS[i], test_points);
		double gen_vol = calcVolume(VOL_CONSTRAINT_INDS[i], gen_coords);
		double diff = orig_vol - gen_vol;

		vol_rms_dev += diff * diff;
	}

	vol_rms_dev = std::sqrt(vol_rms_dev / NUM_VOL_CONSTRAINTS);

	BOOST_CHECK(dist_rms_dev < 0.000001);
	BOOST_CHECK(vol_rms_dev < 0.000001);

	//BOOST_MESSAGE("Solution distance RMSD: " << dist_rms_dev);
	//BOOST_MESSAGE("Solution volume RMSD: " << vol_rms_dev);
}

