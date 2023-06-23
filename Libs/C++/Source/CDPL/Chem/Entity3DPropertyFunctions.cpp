/* 
 * Entity3DPropertyFunctions.cpp 
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

#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Entity3DProperty.hpp"
#include "CDPL/Chem/Entity3D.hpp"


using namespace CDPL; 


#define MAKE_ENTITY3D_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
    void Chem::set##FUNC_SUFFIX(Chem::Entity3D& entity, TYPE arg)        \
    {                                                                    \
        entity.setProperty(Entity3DProperty::PROP_NAME, arg);            \
    }                                                                    \
                                                                        \
    bool Chem::has##FUNC_SUFFIX(const Chem::Entity3D& entity)            \
    {                                                                    \
        return entity.isPropertySet(Entity3DProperty::PROP_NAME);        \
    }                                                                    \
                                                                        \
    void Chem::clear##FUNC_SUFFIX(Chem::Entity3D& entity)                \
    {                                                                    \
        entity.removeProperty(Entity3DProperty::PROP_NAME);                \
    }

#define MAKE_ENTITY3D_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)    \
    TYPE Chem::get##FUNC_SUFFIX(const Chem::Entity3D& entity)            \
    {                                                                    \
        return entity.getProperty<TYPE>(Entity3DProperty::PROP_NAME);    \
    }                                                                    \
                                                                        \
    MAKE_ENTITY3D_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

MAKE_ENTITY3D_PROPERTY_FUNCTIONS(COORDINATES_3D, const Math::Vector3D&, 3DCoordinates)
