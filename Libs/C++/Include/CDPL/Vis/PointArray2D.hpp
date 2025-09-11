/* 
 * PointArray2D.hpp 
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
 * \brief Definition of class CDPL::Vis::PointArray2D.
 */

#ifndef CDPL_VIS_POINTARRAY2D_HPP
#define CDPL_VIS_POINTARRAY2D_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Rectangle2D;

        /**
         * \brief Stores a set of points in 2D space.
         */
        class CDPL_VIS_API PointArray2D : public Math::Vector2DArray
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PointArray2D instances.
             */
            typedef std::shared_ptr<PointArray2D> SharedPointer;

            /**
             * \brief Translates all points by \a vec.
             * \param vec The translation vector.
             */
            void translate(const Math::Vector2D& vec);

            void getBounds(Rectangle2D& bounds) const;

          private:
            const char* getClassName() const;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_POINTARRAY2D_HPP
