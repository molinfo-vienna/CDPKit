/* 
 * Object3DFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Vis::Object3D instances.
 */

#ifndef CDPL_VIS_OBJECT3DFUNCTIONS_HPP
#define CDPL_VIS_OBJECT3DFUNCTIONS_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Shape3D.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Object3D;
        class Material;

        /**
         * \brief Returns the value of the Vis::Object3DProperty::SHAPE property of the 3D object \a obj.
         * \param obj The 3D object for which to return the property value.
         * \return The value of the Vis::Object3DProperty::SHAPE property.
         * \since 1.3
         */
        CDPL_VIS_API const Shape3D::SharedPointer& getShape(const Object3D& obj);

        /**
         * \brief Sets the value of the Vis::Object3DProperty::SHAPE property of the 3D object \a obj to \a shape.
         * \param obj The 3D object for which to set the property value.
         * \param shape The new value of the Vis::Object3DProperty::SHAPE property.
         * \since 1.3
         */
        CDPL_VIS_API void setShape(Object3D& obj, const Shape3D::SharedPointer& shape);

        /**
         * \brief Tells whether the Vis::Object3DProperty::SHAPE property of the 3D object \a obj is set.
         * \param obj The 3D object for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_VIS_API bool hasShape(const Object3D& obj);

        /**
         * \brief Clears the value of the Vis::Object3DProperty::SHAPE property of the 3D object \a obj.
         * \param obj The 3D object for which to clear the property value.
         * \since 1.3
         */
        CDPL_VIS_API void clearShape(Object3D& obj);

        /**
         * \brief Returns the value of the Vis::Object3DProperty::TRANSFORMATION_MATRIX property of the 3D object \a obj.
         * \param obj The 3D object for which to return the property value.
         * \return The value of the Vis::Object3DProperty::TRANSFORMATION_MATRIX property.
         * \since 1.3
         */
        CDPL_VIS_API const Math::Matrix4D& getTransformationMatrix(const Object3D& obj);

        /**
         * \brief Sets the value of the Vis::Object3DProperty::TRANSFORMATION_MATRIX property of the 3D object \a obj to \a mtx.
         * \param obj The 3D object for which to set the property value.
         * \param mtx The new value of the Vis::Object3DProperty::TRANSFORMATION_MATRIX property.
         * \since 1.3
         */
        CDPL_VIS_API void setTransformationMatrix(Object3D& obj, const Math::Matrix4D& mtx);

        /**
         * \brief Tells whether the Vis::Object3DProperty::TRANSFORMATION_MATRIX property of the 3D object \a obj is set.
         * \param obj The 3D object for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_VIS_API bool hasTransformationMatrix(const Object3D& obj);

        /**
         * \brief Clears the value of the Vis::Object3DProperty::TRANSFORMATION_MATRIX property of the 3D object \a obj.
         * \param obj The 3D object for which to clear the property value.
         * \since 1.3
         */
        CDPL_VIS_API void clearTransformationMatrix(Object3D& obj);

        /**
         * \brief Returns the value of the Vis::Object3DProperty::MATERIAL property of the 3D object \a obj.
         * \param obj The 3D object for which to return the property value.
         * \return The value of the Vis::Object3DProperty::MATERIAL property.
         * \since 1.3
         */
        CDPL_VIS_API const Material& getMaterial(const Object3D& obj);

        /**
         * \brief Sets the value of the Vis::Object3DProperty::MATERIAL property of the 3D object \a object3D to \a material.
         * \param object3D The 3D object for which to set the property value.
         * \param material The new value of the Vis::Object3DProperty::MATERIAL property.
         * \since 1.3
         */
        CDPL_VIS_API void setMaterial(Object3D& object3D, const Material& material);

        /**
         * \brief Tells whether the Vis::Object3DProperty::MATERIAL property of the 3D object \a obj is set.
         * \param obj The 3D object for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_VIS_API bool hasMaterial(const Object3D& obj);

        /**
         * \brief Clears the value of the Vis::Object3DProperty::MATERIAL property of the 3D object \a obj.
         * \param obj The 3D object for which to clear the property value.
         * \since 1.3
         */
        CDPL_VIS_API void clearMaterial(Object3D& obj);
        
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3DFUNCTIONS_HPP
