/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondingInteractionScore.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


namespace
{

	const double H_BOND_LENGTH = 1.05;
	const double DEF_H_BOND_TO_AXIS_ANGLE = 65.0;
}


const double Pharm::HBondingInteractionScore::DEF_MIN_HB_LENGTH = 1.2;
const double Pharm::HBondingInteractionScore::DEF_MAX_HB_LENGTH = 2.8;
const double Pharm::HBondingInteractionScore::DEF_MIN_AHD_ANGLE = 130.0;
const double Pharm::HBondingInteractionScore::DEF_MAX_ACC_ANGLE = 85.0;


Pharm::HBondingInteractionScore::HBondingInteractionScore(bool don_acc, double min_len, double max_len, double min_ahd_ang, double max_acc_ang): 
	donAccOrder(don_acc), minLength(min_len), maxLength(max_len), minAHDAngle(min_ahd_ang), 
	maxAccAngle(max_acc_ang), normFunc(boost::bind(&Math::generalizedBell<double>, _1, 0.5, 10, 0.0)) {}

double Pharm::HBondingInteractionScore::getMinLength() const
{
	return minLength;
}

double Pharm::HBondingInteractionScore::getMaxLength() const
{
	return maxLength;
}

double Pharm::HBondingInteractionScore::getMinAHDAngle() const
{
	return minAHDAngle;
}

double Pharm::HBondingInteractionScore::getMaxAcceptorAngle() const
{
	return maxAccAngle;
}

void Pharm::HBondingInteractionScore::setNormalizationFunction(const NormalizationFunction& func)
{
    normFunc = func;
}

double Pharm::HBondingInteractionScore::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	const Feature& don_ftr = (donAccOrder ? ftr1 : ftr2);
	const Feature& acc_ftr = (donAccOrder ? ftr2 : ftr1);
	const Math::Vector3D& don_pos = get3DCoordinates(don_ftr);
	const Math::Vector3D& acc_pos = get3DCoordinates(acc_ftr);
	unsigned int don_geom = getGeometry(don_ftr);
	Math::Vector3D h_acc_vec;
	double score = 1.0;

	if ((don_geom == FeatureGeometry::VECTOR || don_geom == FeatureGeometry::SPHERE) && hasOrientation(don_ftr)) {
		const Math::Vector3D& orient = getOrientation(don_ftr);

		if (don_geom == FeatureGeometry::VECTOR) { 
			Math::Vector3D don_h_vec(orient * H_BOND_LENGTH /*getLength(don_ftr)*/);
		
			h_acc_vec.assign(acc_pos - (don_pos + don_h_vec));

			double hb_len = length(h_acc_vec);
			double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);

			score = normFunc(ctr_dev);

			h_acc_vec /= hb_len;

			double ahd_ang = std::acos(angleCos(-orient, h_acc_vec, 1)) * 180.0 / M_PI;
			double opt_ang_dev = (180.0 - ahd_ang) * 0.5 / (180.0 - minAHDAngle); 

			score *= normFunc(opt_ang_dev);
			
		} else {
			h_acc_vec.assign(acc_pos - don_pos);
			
			double don_acc_vec_len = length(h_acc_vec);
			double hda_ang = std::abs(std::acos(angleCos(orient, h_acc_vec, don_acc_vec_len)) - DEF_H_BOND_TO_AXIS_ANGLE / 180.0 * M_PI);
			double hb_len = std::sqrt(H_BOND_LENGTH * H_BOND_LENGTH + don_acc_vec_len * don_acc_vec_len - 2 * H_BOND_LENGTH * don_acc_vec_len * std::cos(hda_ang));
			double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);

			score = normFunc(ctr_dev);

			double ahd_ang = std::acos((H_BOND_LENGTH * H_BOND_LENGTH - don_acc_vec_len * don_acc_vec_len + hb_len * hb_len) / (2 * H_BOND_LENGTH * hb_len)) * 180.0 / M_PI;
			double opt_ang_dev = (180.0 - ahd_ang) * 0.5 / (180.0 - minAHDAngle);

			score *= normFunc(opt_ang_dev);
			h_acc_vec /= don_acc_vec_len;
		}
		
	} else {
		h_acc_vec.assign(acc_pos - don_pos);

		double don_acc_vec_len = length(h_acc_vec);
		double hb_len = don_acc_vec_len - H_BOND_LENGTH;
		double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);

		score = normFunc(ctr_dev);

		h_acc_vec /= don_acc_vec_len;
	}

	if (hasOrientation(acc_ftr)) {
		const Math::Vector3D& acc_vec = getOrientation(acc_ftr);
		double acc_ang = std::acos(angleCos(h_acc_vec, acc_vec, 1)) * 180.0 / M_PI;
		double opt_ang_dev = acc_ang * 0.5 / maxAccAngle; 

		score *= normFunc(opt_ang_dev);
	}

	return score * getWeight(ftr2);
}

double Pharm::HBondingInteractionScore::operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const
{
	if (donAccOrder) {
		Math::Vector3D h_acc_vec(get3DCoordinates(ftr2) - ftr1_pos);

		double don_acc_vec_len = length(h_acc_vec);
		double hb_len = don_acc_vec_len - H_BOND_LENGTH;
		double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);
		double score = normFunc(ctr_dev);

		h_acc_vec /= don_acc_vec_len;

		if (hasOrientation(ftr2)) {
			const Math::Vector3D& acc_vec = getOrientation(ftr2);
			double acc_ang = std::acos(angleCos(h_acc_vec, acc_vec, 1)) * 180.0 / M_PI;
			double opt_ang_dev = acc_ang * 0.5 / maxAccAngle; 

			score *= normFunc(opt_ang_dev);
		}

		return score * getWeight(ftr2);
	}

	unsigned int don_geom = getGeometry(ftr2);

	if ((don_geom == FeatureGeometry::VECTOR || don_geom == FeatureGeometry::SPHERE) && hasOrientation(ftr2)) {
		const Math::Vector3D& orient = getOrientation(ftr2);
		
		if (don_geom == FeatureGeometry::VECTOR) { 
			Math::Vector3D don_h_vec(orient * H_BOND_LENGTH /*getLength(ftr2)*/);
			Math::Vector3D h_acc_vec(ftr1_pos - (get3DCoordinates(ftr2) + don_h_vec));

			double hb_len = length(h_acc_vec);
			double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);
			double score = normFunc(ctr_dev);

			h_acc_vec /= hb_len;

			double ahd_ang = std::acos(angleCos(-orient, h_acc_vec, 1)) * 180.0 / M_PI;
			double opt_ang_dev = (180.0 - ahd_ang) * 0.5 / (180.0 - minAHDAngle); 

			return score * normFunc(opt_ang_dev) * getWeight(ftr2);
		}

		Math::Vector3D don_acc_vec(ftr1_pos - get3DCoordinates(ftr2));
			
		double don_acc_vec_len = length(don_acc_vec);
		double hda_ang = std::abs(std::acos(angleCos(orient, don_acc_vec, don_acc_vec_len)) - DEF_H_BOND_TO_AXIS_ANGLE / 180.0 * M_PI);
		double hb_len = std::sqrt(H_BOND_LENGTH * H_BOND_LENGTH + don_acc_vec_len * don_acc_vec_len - 2 * H_BOND_LENGTH * don_acc_vec_len * std::cos(hda_ang));
		double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);

		double score = normFunc(ctr_dev);

		double ahd_ang = std::acos((H_BOND_LENGTH * H_BOND_LENGTH - don_acc_vec_len * don_acc_vec_len + hb_len * hb_len) / (2 * H_BOND_LENGTH * hb_len)) * 180.0 / M_PI;
		double opt_ang_dev = (180.0 - ahd_ang) * 0.5 / (180.0 - minAHDAngle);

		return score * normFunc(opt_ang_dev) * getWeight(ftr2);
	}

	double don_acc_vec_len = length(ftr1_pos - get3DCoordinates(ftr2));
	double hb_len = don_acc_vec_len - H_BOND_LENGTH;
	double ctr_dev = (hb_len - (maxLength + minLength) * 0.5) / (maxLength - minLength);

	return normFunc(ctr_dev) * getWeight(ftr2);
}


