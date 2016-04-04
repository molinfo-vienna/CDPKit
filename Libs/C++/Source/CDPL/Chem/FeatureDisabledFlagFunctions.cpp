/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureDisabledFlagFunctions.cpp 
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

#include "CDPL/Chem/FeatureFunctions.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureProperty.hpp"


using namespace CDPL; 


bool Chem::getDisabledFlag(const Feature& feature)
{
	static const bool DEF_FLAG = false;

    return feature.getPropertyOrDefault<bool>(FeatureProperty::DISABLED_FLAG, DEF_FLAG);
}

void Chem::setDisabledFlag(Feature& feature, bool flag)
{
    feature.setProperty(FeatureProperty::DISABLED_FLAG, flag);
}

void Chem::clearDisabledFlag(Feature& feature)
{
    feature.removeProperty(FeatureProperty::DISABLED_FLAG);
}

bool Chem::hasDisabledFlag(const Feature& feature)
{
    return feature.isPropertySet(FeatureProperty::DISABLED_FLAG);
}
