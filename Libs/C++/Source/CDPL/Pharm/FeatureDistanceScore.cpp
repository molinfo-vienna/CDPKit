/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureDistanceScore.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Pharm/FeatureDistanceScore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


Pharm::FeatureDistanceScore::FeatureDistanceScore(double min_dist, double max_dist): 
    minDist(min_dist), maxDist(max_dist), normFunc(boost::bind(&Math::generalizedBell<double>, _1, 0.5, 10, 0.0)) {}

double Pharm::FeatureDistanceScore::getMinDistance() const
{
    return minDist;
}

double Pharm::FeatureDistanceScore::getMaxDistance() const
{
    return maxDist;
}

void Pharm::FeatureDistanceScore::setNormalizationFunction(const NormalizationFunction& func)
{
    normFunc = func;
}

double Pharm::FeatureDistanceScore::operator()(const Feature& ftr1, const Feature& ftr2) const
{
    return operator()(get3DCoordinates(ftr1), ftr2);
}

double Pharm::FeatureDistanceScore::operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const
{
    double dist = length(get3DCoordinates(ftr2) - ftr1_pos);
    double ctr_dev = (dist - (maxDist + minDist) * 0.5) / (maxDist - minDist);

	return normFunc(ctr_dev) * getWeight(ftr2);
}
