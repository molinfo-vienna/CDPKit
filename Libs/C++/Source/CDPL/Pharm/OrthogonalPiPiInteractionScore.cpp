/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * OrthogonalPiPiInteractionScore.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "PiPiInteractionUtilities.hpp"


using namespace CDPL;


constexpr double Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_V_DISTANCE;
constexpr double Pharm::OrthogonalPiPiInteractionScore::DEF_MIN_H_DISTANCE;
constexpr double Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_H_DISTANCE;
constexpr double Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_ANGLE;


Pharm::OrthogonalPiPiInteractionScore::OrthogonalPiPiInteractionScore(double min_h_dist, double max_h_dist,
																	  double max_v_dist, double max_ang):
	minHDist(min_h_dist), maxHDist(max_h_dist),  maxVDist(max_v_dist), maxAngle(max_ang),
	distScoringFunc(boost::bind(&Math::generalizedBell<double>, _1, 0.5, 10, 0.0)),
	angleScoringFunc(boost::bind(&Math::generalizedBell<double>, _1, 0.5, 2.5, 0.0)) {}

double Pharm::OrthogonalPiPiInteractionScore::getMinHDistance() const
{
    return minHDist;
}

double Pharm::OrthogonalPiPiInteractionScore::getMaxHDistance() const
{
    return maxHDist;
}

double Pharm::OrthogonalPiPiInteractionScore::getMaxVDistance() const
{
    return maxVDist;
}

double Pharm::OrthogonalPiPiInteractionScore::getMaxAngle() const
{
    return maxAngle;
}

void Pharm::OrthogonalPiPiInteractionScore::setDistanceScoringFunction(const DistanceScoringFunction& func)
{
    distScoringFunc = func;
}

void Pharm::OrthogonalPiPiInteractionScore::setAngleScoringFunction(const AngleScoringFunction& func)
{
    angleScoringFunc = func;
}

double Pharm::OrthogonalPiPiInteractionScore::operator()(const Feature& ftr1, const Feature& ftr2) const
{
    Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));

	bool has_orient1 = hasOrientation(ftr1);
	bool has_orient2 = hasOrientation(ftr2);

    if (!has_orient1 && !has_orient2) {
		double min_dist = minHDist;
		double max_dist = std::sqrt(maxVDist * maxVDist + maxHDist * maxHDist);

		return distScoringFunc((length(ftr1_ftr2_vec) - (max_dist + min_dist) * 0.5) / (max_dist - min_dist));
	}

	double ang_score = 1.0;

	if (has_orient1 && has_orient2) {
		const Math::Vector3D& orient1 = getOrientation(ftr1);
		const Math::Vector3D& orient2 = getOrientation(ftr2);

		double ang_cos = angleCos(orient1, orient2, 1);
		double ang = std::acos(ang_cos) * 180.0 / M_PI - 90.0;

		ang_score = angleScoringFunc(ang / maxAngle * 0.5);
	}

	double dist_score1 = (has_orient1 ? calcDistanceScore(getOrientation(ftr1), ftr1_ftr2_vec) : 0.0);
	double dist_score2 = (has_orient2 ? calcDistanceScore(getOrientation(ftr2), ftr1_ftr2_vec) : 0.0);

	return (std::max(dist_score1, dist_score2) * ang_score * getWeight(ftr2));
}

double Pharm::OrthogonalPiPiInteractionScore::operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const
{
    Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - ftr1_pos);

    if (!hasOrientation(ftr2)) {
		double min_dist = minHDist;
		double max_dist = std::sqrt(maxVDist * maxVDist + maxHDist * maxHDist);

		return distScoringFunc((length(ftr1_ftr2_vec) - (max_dist + min_dist) * 0.5) / (max_dist - min_dist));
	}

	return calcDistanceScore(getOrientation(ftr2), ftr1_ftr2_vec) * getWeight(ftr2);
}

double Pharm::OrthogonalPiPiInteractionScore::calcDistanceScore(const Math::Vector3D& orient, const Math::Vector3D& ftr1_ftr2_vec) const
{
	double h_dist = calcHPlaneDistance(orient, ftr1_ftr2_vec);
	double h_dist_score = distScoringFunc((h_dist - (maxHDist + minHDist) * 0.5) / (maxHDist - minHDist));

    double v_dist = calcVPlaneDistance(orient, ftr1_ftr2_vec);
	double v_dist_score = distScoringFunc(v_dist / maxVDist * 0.5);
	
    return (h_dist_score * v_dist_score);
}
