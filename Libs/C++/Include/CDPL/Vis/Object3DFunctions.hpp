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
#include "CDPL/Vis/GraphicsPrimitive3D.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Object3D;

        /**
         * \since 1.3
         */
        CDPL_VIS_API const GraphicsPrimitive3D::SharedPointer& getGraphicsPrimitive(const Object3D& obj);

        CDPL_VIS_API void setGraphicsPrimitive(Object3D& object3D, const GraphicsPrimitive3D::SharedPointer& prim);

        CDPL_VIS_API bool hasGraphicsPrimitive(const Object3D& obj);

        CDPL_VIS_API void clearGraphicsPrimitive(Object3D& obj);
        
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3DFUNCTIONS_HPP
