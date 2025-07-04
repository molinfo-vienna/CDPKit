/* 
 * Object3DProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::Object3DProperty.
 */

#ifndef CDPL_VIS_OBJECT3DPROPERTY_HPP
#define CDPL_VIS_OBJECT3DPROPERTY_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Vis
    {

        /**
         * \brief Provides keys for built-in Vis::Object3D properties.
         * \since 1.3
         */
        namespace Object3DProperty
        {

            /**
             * \brief Specifies the color of the 3D object.
             * \valuetype Vis::Color
             */
            extern CDPL_VIS_API const Base::LookupKey COLOR;
            
        } // namespace Object3DProperty
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3DPROPERTY_HPP
