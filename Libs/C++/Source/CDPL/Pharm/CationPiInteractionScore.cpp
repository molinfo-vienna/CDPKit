/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CationPiInteractionScore.cpp 
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
#include <functional>

#include "CDPL/Pharm/CationPiInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


constexpr double Pharm::CationPiInteractionScore::DEF_MIN_DISTANCE;
constexpr double Pharm::CationPiInteractionScore::DEF_MAX_DISTANCE;
constexpr double Pharm::CationPiInteractionScore::DEF_MAX_ANGLE;


Pharm::CationPiInteractionScore::CationPiInteractionScore(bool aro_cat, double min_dist, double max_dist,
														  double max_ang):
	aroCatOrder(aro_cat), minDist(min_dist), maxDist(max_dist), maxAngle(max_ang), 
	distScoringFunc(std::bind(&Math::generalizedBell<double>, std::placeholders::_1, 0.5, 10, 0.0)),
	angleScoringFunc(std::bind(&Math::generalizedBell<double>, std::placeholders::_1, 0.5, 2.5, 0.0))
{}

double Pharm::CationPiInteractionScore::getMinDistance() const
{
    return minDist;
}

double Pharm::CationPiInteractionScore::getMaxDistance() const
{
    return maxDist;
}

double Pharm::CationPiInteractionScore::getMaxAngle() const
{
    return maxAngle;
}

void Pharm::CationPiInteractionScore::setDistanceScoringFunction(const DistanceScoringFunction& func)
{
    distScoringFunc = func;
}

void Pharm::CationPiInteractionScore::setAngleScoringFunction(const AngleScoringFunction& func)
{
    angleScoringFunc = func;
}

double Pharm::CationPiInteractionScore::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	const Feature& aro_ftr = (aroCatOrder ? ftr1 : ftr2);
    const Feature& cat_ftr = (aroCatOrder ? ftr2 : ftr1);
    const Math::Vector3D& aro_pos = get3DCoordinates(aro_ftr);
    const Math::Vector3D& cat_pos = get3DCoordinates(cat_ftr);

    Math::Vector3D aro_cat_vec(aro_pos - cat_pos);
    double ctr_dist = length(aro_cat_vec);

    if (hasOrientation(aro_ftr)) {
		const Math::Vector3D& orient = getOrientation(aro_ftr);
		double ang_cos = std::abs(angleCos(orient, aro_cat_vec, ctr_dist));
		double angle = std::acos(ang_cos) * 180.0 / M_PI;
		double plane_dist = ang_cos * ctr_dist;
		double score = distScoringFunc((plane_dist - (maxDist + minDist) * 0.5) / (maxDist - minDist));

		return (score * angleScoringFunc(angle / maxAngle * 0.5) * getWeight(ftr2));
    }

	return distScoringFunc((ctr_dist - (maxDist + minDist) * 0.5) / (maxDist - minDist)) * getWeight(ftr2);
}

double Pharm::CationPiInteractionScore::operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const
{
    Math::Vector3D aro_cat_vec(get3DCoordinates(ftr2) - ftr1_pos);
    double ctr_dist = length(aro_cat_vec);

	if (aroCatOrder)
		return distScoringFunc((ctr_dist - (maxDist + minDist) * 0.5) / (maxDist - minDist)) * getWeight(ftr2);

    if (hasOrientation(ftr2)) {
		const Math::Vector3D& orient = getOrientation(ftr2);
		double ang_cos = std::abs(angleCos(orient, aro_cat_vec, ctr_dist));
		double angle = std::acos(ang_cos) * 180.0 / M_PI;
		double plane_dist = ang_cos * ctr_dist;
		double score = distScoringFunc((plane_dist - (maxDist + minDist) * 0.5) / (maxDist - minDist));
		
		return (score * angleScoringFunc(angle / maxAngle * 0.5) * getWeight(ftr2));
    }

    return distScoringFunc((ctr_dist - (maxDist + minDist) * 0.5) / (maxDist - minDist)) * getWeight(ftr2);
}
