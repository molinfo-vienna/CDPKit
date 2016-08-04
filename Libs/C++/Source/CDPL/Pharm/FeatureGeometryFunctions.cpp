/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureGeometryFunctions.cpp 
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

#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureProperty.hpp"


using namespace CDPL; 


unsigned int Pharm::getGeometry(const Feature& feature)
{
    return feature.getPropertyOrDefault<unsigned int>(FeatureProperty::GEOMETRY, FeatureGeometry::UNDEF);
}

void Pharm::setGeometry(Feature& feature, unsigned int geom)
{
    feature.setProperty(FeatureProperty::GEOMETRY, geom);
}

void Pharm::clearGeometry(Feature& feature)
{
    feature.removeProperty(FeatureProperty::GEOMETRY);
}

bool Pharm::hasGeometry(const Feature& feature)
{
    return feature.isPropertySet(FeatureProperty::GEOMETRY);
}
