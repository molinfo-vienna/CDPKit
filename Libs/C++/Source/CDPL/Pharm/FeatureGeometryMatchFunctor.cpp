/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureGeometryMatchFunctor.cpp 
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

#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Math/MatrixProxy.hpp"


using namespace CDPL; 


const double Pharm::FeatureGeometryMatchFunctor::DEF_HBA_ANGLE_TOLERANCE      = 80.0;
const double Pharm::FeatureGeometryMatchFunctor::DEF_HBD_ANGLE_TOLERANCE      = 80.0;
const double Pharm::FeatureGeometryMatchFunctor::DEF_AR_PLANE_ANGLE_TOLERANCE = 30.0;


double Pharm::FeatureGeometryMatchFunctor::getHBondAcceptorAngleTolerance() const
{
	return hbaVecAngleTol;
}

double Pharm::FeatureGeometryMatchFunctor::getHBondDonorAngleTolerance() const
{
	return hbdVecAngleTol;
}

double Pharm::FeatureGeometryMatchFunctor::getAromPlaneAngleTolerance() const
{
	return arPlaneAngleTol;
}

bool Pharm::FeatureGeometryMatchFunctor::strictGeometryMatching() const
{
	return strictMode;
}

double Pharm::FeatureGeometryMatchFunctor::operator()(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const
{
	unsigned int ftr1_geom = getGeometry(ftr1);
	unsigned int ftr2_geom = getGeometry(ftr2);

	if (strictMode && ftr1_geom != ftr2_geom)
		return 0.0;

	if (ftr1_geom != FeatureGeometry::VECTOR && ftr1_geom != FeatureGeometry::PLANE)
		return 1.0;

	if (ftr2_geom != FeatureGeometry::VECTOR && ftr2_geom != FeatureGeometry::PLANE)
		return 1.0;

	if (ftr1_geom != ftr2_geom)
		return 0.0;

	if (!hasOrientation(ftr1))
		return (strictMode ? 0.0 : 1.0);

	if (!hasOrientation(ftr2))
		return (strictMode ? 0.0 : 1.0);

	double ang_tol = 0.0;
	unsigned int ftr1_type = getType(ftr1);

	switch (ftr1_type) {

		case FeatureType::H_BOND_DONOR:
			ang_tol = hbdVecAngleTol;
			break;

		case FeatureType::H_BOND_ACCEPTOR:
			ang_tol = hbdVecAngleTol;
			break;

		case FeatureType::AROMATIC:
			ang_tol = arPlaneAngleTol;
			break;

		default:
			return 1.0;
	}

	const Math::Vector3D& orient2 = getOrientation(ftr2);
	Math::Vector3D trans_or2;

	prod(range(xform, 0, 3, 0, 3), orient2, trans_or2);

	double ang = std::acos(angleCos(getOrientation(ftr1), trans_or2, 1.0)) / M_PI * 180.0;

	if (ftr1_geom == FeatureGeometry::PLANE && ang > 90.0) 
		ang = 180.0 - ang;

	double score = 1.0 - (ang / ang_tol);

	return (score < 0.0 ? 0.0 : score);
}
