/* 
 * GraphicsPrimitive3D.hpp 
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
 * \brief Definition of the class CDPL::Vis::GraphicsPrimitive3D.
 */

#ifndef CDPL_VIS_GRAPHICSPRIMITIVE3D_HPP
#define CDPL_VIS_GRAPHICSPRIMITIVE3D_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Vis
    {

        class GraphicsPrimitive3DVisitor;

        /**
         * \brief The abstract base class of all 3D graphics primitives.
         *
         * Graphics primitives are simple (atomic) geometrical objects which can be used as building blocks for
         * larger and more complex 3D objects (e.g. the 3D representation of a molecular structure). 
         */
        class CDPL_VIS_API GraphicsPrimitive3D
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GraphicsPrimitive3D instances.
             */
            typedef std::shared_ptr<GraphicsPrimitive3D> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~GraphicsPrimitive3D() {}

            /**
             * \brief Creates a dynamically allocated copy of the graphics primitive.
             * \return The copy of the graphics primitive.
             */
            virtual SharedPointer clone() const = 0;

            /**
             * \brief GraphicsPrimitive3DVisitor implementation accept method [\ref VPTN].
             */
            virtual void accept(GraphicsPrimitive3DVisitor& visitor) const = 0;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_GRAPHICSPRIMITIVE3D_HPP
