/* 
 * Object3DPropertyFunctions.cpp 
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

#include "CDPL/Vis/Object3DFunctions.hpp"
#include "CDPL/Vis/Object3DProperty.hpp"
#include "CDPL/Vis/Object3DPropertyDefault.hpp"
#include "CDPL/Vis/Object3D.hpp"


using namespace CDPL;


#define MAKE_OBJECT3D_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
    void Vis::set##FUNC_SUFFIX(Vis::Object3D& obj, TYPE arg)                  \
    {                                                                         \
        obj.setProperty(Object3DProperty::PROP_NAME, arg);                    \
    }                                                                         \
                                                                              \
    bool Vis::has##FUNC_SUFFIX(const Vis::Object3D& obj)                      \
    {                                                                         \
        return obj.isPropertySet(Object3DProperty::PROP_NAME);                \
    }                                                                         \
                                                                              \
    void Vis::clear##FUNC_SUFFIX(Vis::Object3D& obj)                          \
    {                                                                         \
        obj.removeProperty(Object3DProperty::PROP_NAME);                      \
    }

#define MAKE_OBJECT3D_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX) \
    TYPE Vis::get##FUNC_SUFFIX(const Vis::Object3D& obj)               \
    {                                                                  \
        return obj.getProperty<TYPE>(Object3DProperty::PROP_NAME);     \
    }                                                                  \
                                                                       \
    MAKE_OBJECT3D_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_OBJECT3D_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX)    \
    TYPE Vis::get##FUNC_SUFFIX(const Vis::Object3D& obj)                           \
    {                                                                              \
        return obj.getPropertyOrDefault<TYPE>(Object3DProperty::PROP_NAME,         \
                                              Object3DPropertyDefault::PROP_NAME); \
    }                                                                              \
                                                                                   \
    MAKE_OBJECT3D_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_OBJECT3D_PROPERTY_FUNCTIONS_WITH_DEF(SHAPE, const Vis::Shape3D::SharedPointer&, Shape)
