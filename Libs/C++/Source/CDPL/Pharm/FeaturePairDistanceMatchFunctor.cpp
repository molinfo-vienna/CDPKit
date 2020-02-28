/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeaturePairDistanceMatchFunctor.cpp 
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

#include "CDPL/Pharm/FeaturePairDistanceMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


bool Pharm::FeaturePairDistanceMatchFunctor::queryMode() const
{
	return qryMode;
}

bool Pharm::FeaturePairDistanceMatchFunctor::operator()(const Feature& p1_ftr1, const Feature& p1_ftr2,
														const Feature& p2_ftr1, const Feature& p2_ftr2) const
{
	double dist1 = length(get3DCoordinates(p1_ftr2) - get3DCoordinates(p1_ftr1));
    double dist2 = length(get3DCoordinates(p2_ftr2) - get3DCoordinates(p2_ftr1));

    double p1_tol1 = getTolerance(p1_ftr1);
    double p1_tol2 = getTolerance(p1_ftr2);

    if (dist2 >= (dist1 - p1_tol1 - p1_tol2) &&
		dist2 <= (dist1 + p1_tol1 + p1_tol2))
		return true;

    if (qryMode)
		return false;

    double p2_tol1 = getTolerance(p2_ftr1);
    double p2_tol2 = getTolerance(p2_ftr2);

    return (dist1 >= (dist2 - p2_tol1 - p2_tol2) &&
			dist1 <= (dist2 + p2_tol1 + p2_tol2));
}
