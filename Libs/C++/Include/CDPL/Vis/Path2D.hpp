/* 
 * Path2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::Path2D.
 */

#ifndef CDPL_VIS_PATH2D_HPP
#define CDPL_VIS_PATH2D_HPP

#include <vector>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Path2DConverter;
        
        /**
         * \brief Specifies a Path in 2D space constructed from arcs and lines.
         */
        class CDPL_VIS_API Path2D
        {

          public:
            enum FillRule
            {

                EVEN_ODD,
                WINDING
            };

            /**
             * \brief Constructs an empty path.
             */
            Path2D();

            /**
             * \brief Constructs a copy of \a path.
             * \param path The \c Path2D instance to copy.
             */
            Path2D(const Path2D& path);

            /**
             * \brief Virtual destructor.
             */
            virtual ~Path2D();

            bool isEmpty() const;

            void clear();

            void setFillRule(FillRule rule);

            FillRule getFillRule() const;

            void moveTo(double x, double y);

            void moveTo(const Math::Vector2D& pos);
            
            void arc(double cx, double cy, double rx, double ry, double start_ang, double sweep);

            void arc(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep);

            void arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep);

            void arcTo(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep);

            void lineTo(double x, double y);

            void lineTo(const Math::Vector2D& pos);

            void closePath();

            void convert(Path2DConverter& conv) const;
            
            bool operator==(const Path2D& path) const;

            bool operator!=(const Path2D& path) const;

            Path2D& operator+=(const Path2D& path);

            Path2D& operator=(const Path2D& path);
            
          private:
            struct Element;

            typedef std::vector<Element> ElementList;

            FillRule    fillRule;
            ElementList elements;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_PATH2D_HPP
