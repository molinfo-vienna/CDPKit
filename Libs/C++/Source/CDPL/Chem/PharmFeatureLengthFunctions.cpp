/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmFeatureLengthFunctions.cpp 
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

#include "CDPL/Chem/PharmFeatureFunctions.hpp"
#include "CDPL/Chem/PharmFeature.hpp"
#include "CDPL/Chem/PharmFeatureProperty.hpp"


using namespace CDPL; 


double Chem::getLength(const PharmFeature& feature)
{
    return feature.getPropertyOrDefault<double>(PharmFeatureProperty::LENGTH, 1.0);
}

void Chem::setLength(PharmFeature& feature, double length)
{
    feature.setProperty(PharmFeatureProperty::LENGTH, length);
}

void Chem::clearLength(PharmFeature& feature)
{
    feature.removeProperty(PharmFeatureProperty::LENGTH);
}

bool Chem::hasLength(const PharmFeature& feature)
{
    return feature.isPropertySet(PharmFeatureProperty::LENGTH);
}
