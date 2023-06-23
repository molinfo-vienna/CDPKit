/* 
 * FeatureContainerPropertyFunctions.cpp 
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

#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerProperty.hpp"
#include "CDPL/Pharm/FeatureContainerPropertyDefault.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"


using namespace CDPL; 


#define MAKE_FTRCONT_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
    void Pharm::set##FUNC_SUFFIX(Pharm::FeatureContainer& cont, TYPE arg) \
    {                                                                    \
        cont.setProperty(FeatureContainerProperty::PROP_NAME, arg);        \
    }                                                                    \
                                                                        \
    bool Pharm::has##FUNC_SUFFIX(const Pharm::FeatureContainer& cont)    \
    {                                                                    \
        return cont.isPropertySet(FeatureContainerProperty::PROP_NAME);    \
    }                                                                    \
                                                                        \
    void Pharm::clear##FUNC_SUFFIX(Pharm::FeatureContainer& cont)        \
    {                                                                    \
        cont.removeProperty(FeatureContainerProperty::PROP_NAME);        \
    }

#define MAKE_FTRCONT_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)    \
    TYPE Pharm::get##FUNC_SUFFIX(const Pharm::FeatureContainer& cont)    \
    {                                                                    \
        return cont.getProperty<TYPE>(FeatureContainerProperty::PROP_NAME);    \
    }                                                                    \
                                                                        \
    MAKE_FTRCONT_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_FTRCONT_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
    TYPE Pharm::get##FUNC_SUFFIX(const Pharm::FeatureContainer& cont)    \
    {                                                                    \
        return cont.getPropertyOrDefault<TYPE>(FeatureContainerProperty::PROP_NAME,    \
                                               FeatureContainerPropertyDefault::PROP_NAME);    \
    }                                                                    \
                                                                        \
    MAKE_FTRCONT_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_FTRCONT_PROPERTY_FUNCTIONS_WITH_DEF(NAME, const std::string&, Name)
