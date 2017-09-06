/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CationPiInteractionScore.cpp 
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

#include "CDPL/Pharm/CationPiInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/GeneralizedBellFunction.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


const double Pharm::CationPiInteractionScore::DEF_MIN_DISTANCE = 3.5;
const double Pharm::CationPiInteractionScore::DEF_MAX_DISTANCE = 5.5;
const double Pharm::CationPiInteractionScore::DEF_MAX_ANGLE    = 60.0;


Pharm::CationPiInteractionScore::CationPiInteractionScore(bool aro_cat, double min_dist, double max_dist,
														  double max_ang):
	aroCatOrder(aro_cat), minDist(min_dist), maxDist(max_dist), maxAngle(max_ang), 
	normFunc(GeneralizedBellFunction(0.5, 10, 0.0)) {}

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

void Pharm::CationPiInteractionScore::setNormalizationFunction(const NormalizationFunction& func)
{
    normFunc = func;
}

double Pharm::CationPiInteractionScore::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	const Feature& aro_ftr = (aroCatOrder ? ftr1 : ftr2);
    const Feature& cat_ftr = (aroCatOrder ? ftr2 : ftr1);
    const Math::Vector3D& aro_pos = get3DCoordinates(aro_ftr);
    const Math::Vector3D& cat_pos = get3DCoordinates(cat_ftr);

    Math::Vector3D aro_cat_vec(aro_pos - cat_pos);
    double dist = length(aro_cat_vec);
	double score = normFunc((dist - (maxDist + minDist) * 0.5) / (maxDist - minDist));

    if (hasOrientation(aro_ftr)) {
		const Math::Vector3D& orient = getOrientation(aro_ftr);
		double ang_cos = std::abs(angleCos(orient, aro_cat_vec, dist));
		double angle = std::acos(ang_cos) * 180.0 / M_PI;

		return (score * normFunc(angle / maxAngle * 0.5));
    }

    return score;
}
