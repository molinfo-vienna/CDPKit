/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TwoPointPharmacophore.cpp 
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

#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"

#include "TwoPointPharmacophore.hpp"


using namespace CDPL; 


Pharm::TwoPointPharmacophore::TwoPointPharmacophore(const Feature& ftr1, const Feature& ftr2): 
	ftr1Type(getType(ftr1)), ftr2Type(getType(ftr2)), ftrDistance(length(get3DCoordinates(ftr2) - get3DCoordinates(ftr1)))
{
	if (ftr2Type < ftr1Type)
		std::swap(ftr1Type, ftr2Type);
}

unsigned int Pharm::TwoPointPharmacophore::getFeature1Type() const
{
    return ftr1Type;
}

unsigned int Pharm::TwoPointPharmacophore::getFeature2Type() const
{
    return ftr2Type;
}

double Pharm::TwoPointPharmacophore::getFeatureDistance() const
{
    return ftrDistance;
}
