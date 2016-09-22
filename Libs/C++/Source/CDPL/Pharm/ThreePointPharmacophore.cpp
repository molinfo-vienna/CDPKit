/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ThreePointPharmacophore.cpp 
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

#include <algorithm>
#include <utility>

#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"

#include "ThreePointPharmacophore.hpp"


using namespace CDPL; 


namespace
{

    typedef std::pair<const Pharm::Feature*, unsigned int> FeatureWithType;

    struct FeatureWithTypeCompare 
    {

	bool operator()(const FeatureWithType& ft1, const FeatureWithType& ft2) const {
	    return (ft1.second < ft2.second);
	}
    };
}


Pharm::ThreePointPharmacophore::ThreePointPharmacophore(const Feature& ftr1, const Feature& ftr2, const Feature& ftr3)
{
    FeatureWithType ftrs[] = {
       FeatureWithType(&ftr1, getType(ftr1)),
       FeatureWithType(&ftr2, getType(ftr2)),
       FeatureWithType(&ftr3, getType(ftr3))
    };

    std::sort(ftrs, ftrs + 3, FeatureWithTypeCompare());

    ftr1Type = ftrs[0].second;
    ftr2Type = ftrs[1].second;
    ftr3Type = ftrs[2].second;

    const Math::Vector3D& pos1 = get3DCoordinates(*ftrs[0].first);
    const Math::Vector3D& pos2 = get3DCoordinates(*ftrs[1].first);
    const Math::Vector3D& pos3 = get3DCoordinates(*ftrs[2].first);

    ftr12Distance = length(pos2 - pos1);
    ftr23Distance = length(pos3 - pos2);
    ftr13Distance = length(pos3 - pos1);
}

unsigned int Pharm::ThreePointPharmacophore::getFeature1Type() const
{
    return ftr1Type;
}

unsigned int Pharm::ThreePointPharmacophore::getFeature2Type() const
{
    return ftr2Type;
}

unsigned int Pharm::ThreePointPharmacophore::getFeature3Type() const
{
    return ftr3Type;
}

double Pharm::ThreePointPharmacophore::getFeature12Distance() const
{
    return ftr12Distance;
}

double Pharm::ThreePointPharmacophore::getFeature23Distance() const
{
    return ftr23Distance;
}

double Pharm::ThreePointPharmacophore::getFeature13Distance() const
{
    return ftr13Distance;
}
