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
         * \since 1.3
         */
        CDPL_VIS_API const Shape3D::SharedPointer& getShape(const Object3D& obj);

        CDPL_VIS_API void setShape(Object3D& obj, const Shape3D::SharedPointer& shape);

        CDPL_VIS_API bool hasShape(const Object3D& obj);

        CDPL_VIS_API void clearShape(Object3D& obj);

        /**
         * \since 1.3
         */
        CDPL_VIS_API const Math::Matrix4D& getTransformationMatrix(const Object3D& obj);

        CDPL_VIS_API void setTransformationMatrix(Object3D& obj, const Math::Matrix4D& mtx);

        CDPL_VIS_API bool hasTransformationMatrix(const Object3D& obj);

        CDPL_VIS_API void clearTransformationMatrix(Object3D& obj);

        /**
         * \since 1.3
         */
        CDPL_VIS_API const Material& getMaterial(const Object3D& obj);

        CDPL_VIS_API void setMaterial(Object3D& object3D, const Material& material);

        CDPL_VIS_API bool hasMaterial(const Object3D& obj);

        CDPL_VIS_API void clearMaterial(Object3D& obj);
        
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3DFUNCTIONS_HPP
