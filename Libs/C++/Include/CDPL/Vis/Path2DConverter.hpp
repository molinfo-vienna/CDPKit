/* 
 * Path2DConverter.hpp 
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
 * \brief Definition of the class CDPL::Vis::Path2DConverter.
 */

#ifndef CDPL_VIS_PATH2DCONVERTER_HPP
#define CDPL_VIS_PATH2DCONVERTER_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Common interface of classes that implement the conversion of Vis::Path2D objects into
         *        rendering backend specific path descriptions or drawing operations.
         */
        class CDPL_VIS_API Path2DConverter
        {

          public:
            /**
             * \brief Virtual destructor.
             */
            virtual ~Path2DConverter() {}

            virtual void moveTo(double x, double y) = 0;
 
            virtual void arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep) = 0;

            virtual void lineTo(double x, double y) = 0;

            virtual void closePath() = 0;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_PATH2DCONVERTER_HPP
