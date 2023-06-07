/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * OrthogonalPiPiInteractionConstraint.cpp 
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

#include "CDPL/Pharm/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "PiPiInteractionUtilities.hpp"


using namespace CDPL;


constexpr double Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_V_DISTANCE;
constexpr double Pharm::OrthogonalPiPiInteractionConstraint::DEF_MIN_H_DISTANCE;
constexpr double Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_H_DISTANCE;
constexpr double Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_ANGLE;


double Pharm::OrthogonalPiPiInteractionConstraint::getMinHDistance() const
{
    return minHDist;
}

double Pharm::OrthogonalPiPiInteractionConstraint::getMaxHDistance() const
{
    return maxHDist;
}

double Pharm::OrthogonalPiPiInteractionConstraint::getMaxVDistance() const
{
    return maxVDist;
}

double Pharm::OrthogonalPiPiInteractionConstraint::getMaxAngle() const
{
    return maxAngle;
}

bool Pharm::OrthogonalPiPiInteractionConstraint::operator()(const Feature& ftr1, const Feature& ftr2) const
{
    Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));

	bool has_orient1 = hasOrientation(ftr1);
	bool has_orient2 = hasOrientation(ftr2);

   if (!has_orient1 && !has_orient2) {
		double min_dist = minHDist;
		double max_dist = std::sqrt(maxVDist * maxVDist + maxHDist * maxHDist);
		double dist = length(ftr1_ftr2_vec);

		if (dist < min_dist)
			return false;
  
		return (dist <= max_dist);
	}

	if (has_orient1 && has_orient2) {
		const Math::Vector3D& orient1 = getOrientation(ftr1);
		const Math::Vector3D& orient2 = getOrientation(ftr2);

		double ang_cos = angleCos(orient1, orient2, 1);
		double ang = std::acos(ang_cos) * 180.0 / M_PI;

		if (std::abs(ang - 90.0) > maxAngle)
			return false;

		if (checkDistances(orient1, ftr1_ftr2_vec))
			return true;

		return checkDistances(orient2, ftr1_ftr2_vec);
	}
    
	if (has_orient1 && checkDistances(getOrientation(ftr1), ftr1_ftr2_vec))
		return true;

	return (has_orient2 && checkDistances(getOrientation(ftr2), ftr1_ftr2_vec));
}

bool Pharm::OrthogonalPiPiInteractionConstraint::checkDistances(const Math::Vector3D& orient1, const Math::Vector3D& ftr1_ftr2_vec) const
{
	double h_dist = calcHPlaneDistance(orient1, ftr1_ftr2_vec);

    if (h_dist < minHDist)
		return false;
  
    if (h_dist > maxHDist)
		return false;

    double v_dist = calcVPlaneDistance(orient1, ftr1_ftr2_vec);

    if (v_dist > maxVDist)
		return false;

    return true;
}
