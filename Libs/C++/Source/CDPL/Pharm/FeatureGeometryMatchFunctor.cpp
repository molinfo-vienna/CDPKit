/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureGeometryMatchFunctor.cpp 
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

#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Math/MatrixProxy.hpp"


using namespace CDPL; 


namespace
{
	
	const Math::Matrix4D ID_XFORM         = Math::IdentityMatrix<double>(4, 4);
	const double DEF_H_BOND_TO_AXIS_ANGLE = 65.0;
}


const double Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBA_INTERACTION_DIR_ANGLE     = 85.0;
const double Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBA_ORIENTATION_DEVIATION     = 45.0;
const double Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBD_INTERACTION_DIR_DEVIATION = 45.0;
const double Pharm::FeatureGeometryMatchFunctor::DEF_MAX_AR_ORIENTATION_DEVIATION      = 45.0;


Pharm::FeatureGeometryMatchFunctor::FeatureGeometryMatchFunctor(double max_hba_int_dir_angle,
																double max_hba_orient_dev,
																double max_hbd_int_dir_dev,
																double max_ar_orient_dev):
	maxHBAInteractionDirAngle(max_hba_int_dir_angle), maxHBAOrientationDeviation(max_hba_orient_dev),
	maxHBDInteractionDirDeviation(max_hbd_int_dir_dev), maxAROrientationDeviation(max_ar_orient_dev)
{}

double Pharm::FeatureGeometryMatchFunctor::getMaxHBAInteractionDirAngle() const
{
	return maxHBAInteractionDirAngle;
}

void Pharm::FeatureGeometryMatchFunctor::setMaxHBAInteractionDirAngle(double angle)
{
	maxHBAInteractionDirAngle = angle;
}

double Pharm::FeatureGeometryMatchFunctor::getMaxHBAOrientationDeviation() const
{
	return maxHBAOrientationDeviation;
}

void Pharm::FeatureGeometryMatchFunctor::setMaxHBAOrientationDeviation(double angle)
{
	maxHBAOrientationDeviation = angle;
}

double Pharm::FeatureGeometryMatchFunctor::getMaxHBDInteractionDirDeviation() const
{
	return maxHBDInteractionDirDeviation;
}

void Pharm::FeatureGeometryMatchFunctor::setMaxHBDInteractionDirDeviation(double angle)
{
	maxHBDInteractionDirDeviation = angle;
}

double Pharm::FeatureGeometryMatchFunctor::getMaxAROrientationDeviation() const
{
	return maxAROrientationDeviation;
}

void Pharm::FeatureGeometryMatchFunctor::setMaxAROrientationDeviation(double angle)
{
	maxAROrientationDeviation = angle;
}

double Pharm::FeatureGeometryMatchFunctor::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	return this->operator()(ftr1, ftr2, ID_XFORM);
}

double Pharm::FeatureGeometryMatchFunctor::operator()(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const
{
	unsigned int ftr1_type = getType(ftr1);

	switch (ftr1_type) {

		case FeatureType::H_BOND_DONOR:
			return calcHBDFeatureMatchScore(ftr1, ftr2, xform);

		case FeatureType::H_BOND_ACCEPTOR:
			return calcHBAFeatureMatchScore(ftr1, ftr2, xform);

		case FeatureType::AROMATIC:
			return calcARFeatureMatchScore(ftr1, ftr2, xform);

		default:
			break;
	}

	return 1.0;
}

double Pharm::FeatureGeometryMatchFunctor::calcHBDFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const
{
	if (!hasOrientation(ftr1) || !hasOrientation(ftr2))
		return 1.0;

	unsigned int ftr1_geom = getGeometry(ftr1);
	unsigned int ftr2_geom = getGeometry(ftr2);
	double ang_offs = 0.0;
	
	if ((ftr1_geom == FeatureGeometry::SPHERE && ftr2_geom == FeatureGeometry::VECTOR) ||
		(ftr1_geom == FeatureGeometry::VECTOR && ftr2_geom == FeatureGeometry::SPHERE)) {
		ang_offs = DEF_H_BOND_TO_AXIS_ANGLE;

	} else if (!((ftr1_geom == FeatureGeometry::SPHERE || ftr1_geom == FeatureGeometry::VECTOR) && ftr1_geom == ftr2_geom)) 
		return 1.0;

	Math::Vector3D trans_orient2; transformOrientation(ftr2, xform, trans_orient2);
		
	double dev_angle = std::abs(std::acos(angleCos(getOrientation(ftr1), trans_orient2, 1.0)) / M_PI * 180.0 - ang_offs);
	double score = 1.0 - (dev_angle / maxHBDInteractionDirDeviation);

	return (score < 0.0 ? 0.0 : score);
}

double Pharm::FeatureGeometryMatchFunctor::calcHBAFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const
{
	if (!hasOrientation(ftr1) || !hasOrientation(ftr2))
		return 1.0;
	
	unsigned int ftr1_geom = getGeometry(ftr1);
	unsigned int ftr2_geom = getGeometry(ftr2);
	double max_ang_dev = 0.0;
	
	if ((ftr1_geom == FeatureGeometry::SPHERE && ftr2_geom == FeatureGeometry::SPHERE) ||
		(ftr1_geom == FeatureGeometry::VECTOR && ftr2_geom == FeatureGeometry::VECTOR)) {
		max_ang_dev = maxHBAOrientationDeviation;

	} else if ((ftr1_geom == FeatureGeometry::SPHERE && ftr2_geom == FeatureGeometry::VECTOR) ||
			   (ftr1_geom == FeatureGeometry::VECTOR && ftr2_geom == FeatureGeometry::SPHERE)) {
		max_ang_dev = maxHBAInteractionDirAngle;

	} else 
		return 1.0;
	
	Math::Vector3D trans_orient2; transformOrientation(ftr2, xform, trans_orient2);
		
	double dev_angle = std::acos(angleCos(getOrientation(ftr1), trans_orient2, 1.0)) / M_PI * 180.0;
	double score = 1.0 - (dev_angle / max_ang_dev);

	return (score < 0.0 ? 0.0 : score);
}

double Pharm::FeatureGeometryMatchFunctor::calcARFeatureMatchScore(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const
{
	if (getGeometry(ftr1) == FeatureGeometry::PLANE && getGeometry(ftr2) == FeatureGeometry::PLANE && hasOrientation(ftr1) && hasOrientation(ftr2)) {
		Math::Vector3D trans_orient2;

		transformOrientation(ftr2, xform, trans_orient2);
		
		double dev_angle = std::acos(angleCos(getOrientation(ftr1), trans_orient2, 1.0)) / M_PI * 180.0;

		if (dev_angle > 90.0) 
			dev_angle = 180.0 - dev_angle;

		double score = 1.0 - (dev_angle / maxAROrientationDeviation);

		return (score < 0.0 ? 0.0 : score);
	}
	
	return 1.0;
}

void Pharm::FeatureGeometryMatchFunctor::transformOrientation(const Feature& ftr, const Math::Matrix4D& xform, Math::Vector3D& trans_orient) const
{
	prod(range(xform, 0, 3, 0, 3), getOrientation(ftr), trans_orient);
}
