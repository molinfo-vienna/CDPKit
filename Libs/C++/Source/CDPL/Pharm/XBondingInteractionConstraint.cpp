/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * XBondingInteractionConstraint.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/XBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


namespace
{

	const double DEF_LP_TO_AXIS_ANGLE = 65.0;
}


const double Pharm::XBondingInteractionConstraint::DEF_MIN_AX_DISTANCE = 1.6;
const double Pharm::XBondingInteractionConstraint::DEF_MAX_AX_DISTANCE = 3.5;
const double Pharm::XBondingInteractionConstraint::DEF_MIN_AXB_ANGLE = 140.0;
const double Pharm::XBondingInteractionConstraint::DEF_ACC_ANGLE_TOLERANCE = 40.0;


double Pharm::XBondingInteractionConstraint::getMinAXDistance() const
{
	return minAXDist;
}

double Pharm::XBondingInteractionConstraint::getMaxAXDistance() const
{
	return maxAXDist;
}

double Pharm::XBondingInteractionConstraint::getMinAXBAngle() const
{
	return minAXBAngle;
}

double Pharm::XBondingInteractionConstraint::getAcceptorAngleTolerance() const
{
	return accAngleTol;
}

bool Pharm::XBondingInteractionConstraint::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	const Feature& don_ftr = (donAccOrder ? ftr1 : ftr2);
	const Feature& acc_ftr = (donAccOrder ? ftr2 : ftr1);

	const Math::Vector3D& don_pos = get3DCoordinates(don_ftr);
	const Math::Vector3D& acc_pos = get3DCoordinates(acc_ftr);
	Math::Vector3D x_acc_vec(acc_pos - don_pos);

	double ax_dist = length(x_acc_vec);

	if (ax_dist < minAXDist || ax_dist > maxAXDist)
		return false;
	
	if (hasOrientation(don_ftr)) {
		double axb_ang = 180.0 - std::acos(angleCos(x_acc_vec, getOrientation(don_ftr), ax_dist)) * 180.0 / M_PI;
		
		if (axb_ang < minAXBAngle)
			return false;
	}
	
	if (hasOrientation(acc_ftr)) {
		const Math::Vector3D& acc_orient = getOrientation(acc_ftr);
		double acc_ang_dev = std::acos(angleCos(x_acc_vec, acc_orient, ax_dist)) * 180.0 / M_PI;
			
		if (getGeometry(acc_ftr) != FeatureGeometry::VECTOR) 
			acc_ang_dev = std::abs(acc_ang_dev - DEF_LP_TO_AXIS_ANGLE);
		
		if (acc_ang_dev > accAngleTol)
			return false;
	}

	return true;
}
