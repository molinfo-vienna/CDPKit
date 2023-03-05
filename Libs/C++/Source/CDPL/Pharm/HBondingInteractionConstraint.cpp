/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondingInteractionConstraint.cpp 
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

#include "CDPL/Pharm/HBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


namespace
{

	const double DEF_DONOR_TO_H_DIST = 1.05;
	const double DEF_H_BOND_TO_AXIS_ANGLE = 65.0;
}


const double Pharm::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH = 1.2;
const double Pharm::HBondingInteractionConstraint::DEF_MAX_HB_LENGTH = 2.8;
const double Pharm::HBondingInteractionConstraint::DEF_MIN_AHD_ANGLE = 135.0;
const double Pharm::HBondingInteractionConstraint::DEF_MAX_ACC_ANGLE = 85.0;


double Pharm::HBondingInteractionConstraint::getMinLength() const
{
	return minLength;
}

double Pharm::HBondingInteractionConstraint::getMaxLength() const
{
	return maxLength;
}

double Pharm::HBondingInteractionConstraint::getMinAHDAngle() const
{
	return minAHDAngle;
}

double Pharm::HBondingInteractionConstraint::getMaxAcceptorAngle() const
{
	return maxAccAngle;
}

bool Pharm::HBondingInteractionConstraint::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	const Feature& don_ftr = (donAccOrder ? ftr1 : ftr2);
	const Feature& acc_ftr = (donAccOrder ? ftr2 : ftr1);
	const Math::Vector3D& don_pos = get3DCoordinates(don_ftr);
	const Math::Vector3D& acc_pos = get3DCoordinates(acc_ftr);
	unsigned int don_geom = getGeometry(don_ftr);
	Math::Vector3D h_acc_vec;

	if ((don_geom == FeatureGeometry::VECTOR || don_geom == FeatureGeometry::SPHERE) && hasOrientation(don_ftr)) {
		const Math::Vector3D& orient = getOrientation(don_ftr);

		if (don_geom == FeatureGeometry::VECTOR) { 
			Math::Vector3D don_h_vec(orient * (hasLength(don_ftr) ? getLength(don_ftr) : DEF_DONOR_TO_H_DIST));
		
			h_acc_vec.assign(acc_pos - (don_pos + don_h_vec));

			double hb_len = length(h_acc_vec);

			if (hb_len < minLength || hb_len > maxLength)
				return false;

			h_acc_vec /= hb_len;
			
			double ahd_ang = std::acos(angleCos(-orient, h_acc_vec, 1)) * 180.0 / M_PI;

			if (ahd_ang < minAHDAngle)
				return false;
			
		} else {
			h_acc_vec.assign(acc_pos - don_pos);
			
			double don_acc_vec_len = length(h_acc_vec);
			double hda_ang = std::abs(std::acos(angleCos(orient, h_acc_vec, don_acc_vec_len)) - DEF_H_BOND_TO_AXIS_ANGLE / 180.0 * M_PI);
			double hb_len = std::sqrt(DEF_DONOR_TO_H_DIST * DEF_DONOR_TO_H_DIST + don_acc_vec_len * don_acc_vec_len - 2 * DEF_DONOR_TO_H_DIST * don_acc_vec_len * std::cos(hda_ang));

			if (hb_len < minLength || hb_len > maxLength)
				return false;

			double ahd_ang = std::acos((DEF_DONOR_TO_H_DIST * DEF_DONOR_TO_H_DIST - don_acc_vec_len * don_acc_vec_len + hb_len * hb_len) / (2 * DEF_DONOR_TO_H_DIST * hb_len)) * 180.0 / M_PI;

			if (ahd_ang < minAHDAngle)
				return false;

			h_acc_vec /= hb_len;
		}
		
	} else {
		h_acc_vec.assign(acc_pos - don_pos);

		double don_acc_vec_len = length(h_acc_vec);
		double hb_len = don_acc_vec_len - DEF_DONOR_TO_H_DIST;

		if (hb_len < minLength || hb_len > maxLength)
			return false;

		h_acc_vec /= don_acc_vec_len;
	}
	
	if (hasOrientation(acc_ftr)) {
		const Math::Vector3D& acc_vec = getOrientation(acc_ftr);
		double acc_ang = std::acos(angleCos(h_acc_vec, acc_vec, 1)) * 180.0 / M_PI;

		if (acc_ang > maxAccAngle)
			return false;
	}

	return true;
}
