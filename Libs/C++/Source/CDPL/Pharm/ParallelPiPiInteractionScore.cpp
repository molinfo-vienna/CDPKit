/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ParallelPiPiInteractionScore.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

 
#include "StaticInit.hpp"

#include <cmath>
#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "PiPiInteractionUtilities.hpp"


using namespace CDPL;


const double Pharm::ParallelPiPiInteractionScore::DEF_MAX_H_DISTANCE  = 2.8;
const double Pharm::ParallelPiPiInteractionScore::DEF_MIN_V_DISTANCE  = 3.0;
const double Pharm::ParallelPiPiInteractionScore::DEF_MAX_V_DISTANCE  = 5.5;
const double Pharm::ParallelPiPiInteractionScore::DEF_ANGLE_TOLERANCE = 20.0;


Pharm::ParallelPiPiInteractionScore::ParallelPiPiInteractionScore(double min_v_dist, double max_v_dist,
																  double max_h_dist, double ang_tol):
	minVDist(min_v_dist), maxVDist(max_v_dist),  maxHDist(max_h_dist), angleTol(ang_tol), 
	normFunc(boost::bind(&Math::generalizedBell<double>, _1, 0.5, 10, 0.0)) {}

double Pharm::ParallelPiPiInteractionScore::getMinVDistance() const
{
    return minVDist;
}

double Pharm::ParallelPiPiInteractionScore::getMaxVDistance() const
{
    return maxVDist;
}

double Pharm::ParallelPiPiInteractionScore::getMaxHDistance() const
{
    return maxHDist;
}

double Pharm::ParallelPiPiInteractionScore::getAngleTolerance() const
{
    return angleTol;
}

void Pharm::ParallelPiPiInteractionScore::setNormalizationFunction(const NormalizationFunction& func)
{
    normFunc = func;
}

double Pharm::ParallelPiPiInteractionScore::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	bool has_orient1 = hasOrientation(ftr1);
	bool has_orient2 = hasOrientation(ftr2);

	if (!has_orient1 && !has_orient2)
		return 0.0;

	if (has_orient1 && has_orient2) {
		const Math::Vector3D& orient1 = getOrientation(ftr1);
		const Math::Vector3D& orient2 = getOrientation(ftr2);

		double ang_cos = std::abs(angleCos(orient1, orient2, 1));
		double ang = std::acos(ang_cos) * 180.0 / M_PI;
		double ang_score = normFunc(ang / angleTol * 0.5);

		Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));

		double v_dist = std::min(calcVPlaneDistance(orient1, ftr1_ftr2_vec), calcVPlaneDistance(orient2, ftr1_ftr2_vec));
		double v_dist_score = normFunc((v_dist - (maxVDist + minVDist) * 0.5) / (maxVDist - minVDist));

		double h_dist = std::max(calcHPlaneDistance(orient1, ftr1_ftr2_vec), calcHPlaneDistance(orient2, ftr1_ftr2_vec));
		double h_dist_score = normFunc(h_dist / maxHDist * 0.5);

		return (ang_score * h_dist_score * v_dist_score);
	}
 
	if (has_orient1) {
		const Math::Vector3D& orient1 = getOrientation(ftr1);

		Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));

		double v_dist = calcVPlaneDistance(orient1, ftr1_ftr2_vec);
		double v_dist_score = normFunc((v_dist - (maxVDist + minVDist) * 0.5) / (maxVDist - minVDist));

		double h_dist = calcHPlaneDistance(orient1, ftr1_ftr2_vec);
		double h_dist_score = normFunc(h_dist / maxHDist * 0.5);

		return (h_dist_score * v_dist_score);
	}

	const Math::Vector3D& orient2 = getOrientation(ftr2);

	Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));

	double v_dist = calcVPlaneDistance(orient2, ftr1_ftr2_vec);
	double v_dist_score = normFunc((v_dist - (maxVDist + minVDist) * 0.5) / (maxVDist - minVDist));

	double h_dist = calcHPlaneDistance(orient2, ftr1_ftr2_vec);
	double h_dist_score = normFunc(h_dist / maxHDist * 0.5);

	return (h_dist_score * v_dist_score);
}

double Pharm::ParallelPiPiInteractionScore::operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const
{
	if (!hasOrientation(ftr2))
		return 0.0;

	const Math::Vector3D& orient2 = getOrientation(ftr2);

	Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - ftr1_pos);

	double v_dist = calcVPlaneDistance(orient2, ftr1_ftr2_vec);
	double v_dist_score = normFunc((v_dist - (maxVDist + minVDist) * 0.5) / (maxVDist - minVDist));

	double h_dist = calcHPlaneDistance(orient2, ftr1_ftr2_vec);
	double h_dist_score = normFunc(h_dist / maxHDist * 0.5);

	return (h_dist_score * v_dist_score);
}
