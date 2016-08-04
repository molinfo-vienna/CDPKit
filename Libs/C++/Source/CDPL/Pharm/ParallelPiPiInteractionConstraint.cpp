/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ParallelPiPiInteractionConstraint.cpp 
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

#include "CDPL/Pharm/ParallelPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "PiPiInteractionUtilities.hpp"


using namespace CDPL;


const double Pharm::ParallelPiPiInteractionConstraint::DEF_MAX_H_DISTANCE;
const double Pharm::ParallelPiPiInteractionConstraint::DEF_MIN_V_DISTANCE;
const double Pharm::ParallelPiPiInteractionConstraint::DEF_MAX_V_DISTANCE;
const double Pharm::ParallelPiPiInteractionConstraint::DEF_ANGLE_TOLERANCE;


double Pharm::ParallelPiPiInteractionConstraint::getMinVDistance() const
{
    return minVDist;
}

double Pharm::ParallelPiPiInteractionConstraint::getMaxVDistance() const
{
    return maxVDist;
}

double Pharm::ParallelPiPiInteractionConstraint::getMaxHDistance() const
{
    return maxHDist;
}

double Pharm::ParallelPiPiInteractionConstraint::getAngleTolerance() const
{
    return angleTol;
}

bool Pharm::ParallelPiPiInteractionConstraint::operator()(const Feature& ftr1, const Feature& ftr2) const
{
    if (!has3DCoordinates(ftr1) || !has3DCoordinates(ftr2))
	return false;

    if (!hasOrientation(ftr1) || !hasOrientation(ftr2))
	return false;

    const Math::Vector3D& orient1 = getOrientation(ftr1);
    const Math::Vector3D& orient2 = getOrientation(ftr2);

    double ang_cos = std::abs(angleCos(orient1, orient2, 1));
    double ang = std::acos(ang_cos) * 180.0 / M_PI;

    if (ang > angleTol)
	return false;

    Math::Vector3D ftr1_ftr2_vec(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));
    
    double v_dist1 = calcVPlaneDistance(orient1, ftr1_ftr2_vec);
    double v_dist2 = calcVPlaneDistance(orient2, ftr1_ftr2_vec);

    if (std::min(v_dist1, v_dist2) < minVDist)
	return false;
  
    if (std::max(v_dist1, v_dist2) > maxVDist)
	return false;
    
    double h_dist1 = calcHPlaneDistance(orient1, ftr1_ftr2_vec);
    double h_dist2 = calcHPlaneDistance(orient2, ftr1_ftr2_vec);
  
    if (std::max(h_dist1, h_dist2) > maxHDist)
	return false;
   
    return true;
}
