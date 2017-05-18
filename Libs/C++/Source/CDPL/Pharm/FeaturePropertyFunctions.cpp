/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeaturePropertyFunctions.cpp 
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
#include "CDPL/Pharm/FeatureProperty.hpp"
#include "CDPL/Pharm/FeaturePropertyDefault.hpp"
#include "CDPL/Pharm/Feature.hpp"


using namespace CDPL; 


#define MAKE_FEATURE_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)   \
void Pharm::set##FUNC_SUFFIX(Pharm::Feature& feature, TYPE arg)	               \
{									       \
    feature.setProperty(FeatureProperty::PROP_NAME, arg);		       \
}									       \
									       \
bool Pharm::has##FUNC_SUFFIX(const Pharm::Feature& feature)		       \
{									       \
    return feature.isPropertySet(FeatureProperty::PROP_NAME);		       \
}									       \
									       \
void Pharm::clear##FUNC_SUFFIX(Pharm::Feature& feature)			       \
{									       \
    feature.removeProperty(FeatureProperty::PROP_NAME);			       \
}

#define MAKE_FEATURE_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)	       \
TYPE Pharm::get##FUNC_SUFFIX(const Pharm::Feature& feature)		       \
{									       \
    return feature.getProperty<TYPE>(FeatureProperty::PROP_NAME);              \
}									       \
									       \
MAKE_FEATURE_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX)    \
TYPE Pharm::get##FUNC_SUFFIX(const Pharm::Feature& feature)	                  \
{									          \
    return feature.getPropertyOrDefault<TYPE>(FeatureProperty::PROP_NAME,	  \
					      FeaturePropertyDefault::PROP_NAME); \
}									          \
									          \
MAKE_FEATURE_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(TYPE, unsigned int, Type) 
MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(GEOMETRY, unsigned int, Geometry) 
MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(LENGTH, double, Length) 
MAKE_FEATURE_PROPERTY_FUNCTIONS(ORIENTATION, const Math::Vector3D&, Orientation) 
MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(TOLERANCE, double, Tolerance) 
MAKE_FEATURE_PROPERTY_FUNCTIONS(SUBSTRUCTURE, const Chem::Fragment::SharedPointer&, Substructure) 
MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(DISABLED_FLAG, bool, DisabledFlag) 
MAKE_FEATURE_PROPERTY_FUNCTIONS_WITH_DEF(OPTIONAL_FLAG, bool, OptionalFlag) 
