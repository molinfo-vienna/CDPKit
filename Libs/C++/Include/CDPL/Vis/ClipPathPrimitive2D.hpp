/* 
 * ClipPathPrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::ClipPathPrimitive2D.
 */

#ifndef CDPL_VIS_CLIPPATHPRIMITIVE2D_HPP
#define CDPL_VIS_CLIPPATHPRIMITIVE2D_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Vis/GraphicsPrimitive2D.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief A graphics primitive representing a clipping region in 2D space.
         */
        class CDPL_VIS_API ClipPathPrimitive2D : public Path2D,
                                                 public GraphicsPrimitive2D
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ClipPathPrimitive2D instances.
             */
            typedef std::shared_ptr<ClipPathPrimitive2D> SharedPointer;

            /**
             * \brief Constructs an undefined path primitive.
             */
            ClipPathPrimitive2D() {}

            void render(Renderer2D& renderer) const;

            GraphicsPrimitive2D::SharedPointer clone() const;

            void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics = 0) const;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_CLIPPATHPRIMITIVE2D_HPP
