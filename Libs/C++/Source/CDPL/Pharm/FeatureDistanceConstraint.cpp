/* 
 * FeatureDistanceConstraint.cpp 
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

#include "CDPL/Pharm/FeatureDistanceConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


double Pharm::FeatureDistanceConstraint::getMinDistance() const
{
	return minDist;
}

double Pharm::FeatureDistanceConstraint::getMaxDistance() const
{
	return maxDist;
}

bool Pharm::FeatureDistanceConstraint::operator()(const Feature& ftr1, const Feature& ftr2) const
{
	double dist = length(get3DCoordinates(ftr2) - get3DCoordinates(ftr1));

	return (dist >= minDist && dist <= maxDist);
}
