/* 
 * SpatialGrid.hpp 
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
 * \brief Definition of a spatial grid data type.
 */

#ifndef CDPL_GRID_SPATIALGRID_HPP
#define CDPL_GRID_SPATIALGRID_HPP

#include <memory>

#include "CDPL/Grid/AttributedGrid.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Grid
    {

        /**
         * \brief SpatialGrid.
         */
        template <typename T, typename CVT = T>
        class SpatialGrid : public AttributedGrid
        {

          public:
            typedef std::shared_ptr<SpatialGrid> SharedPointer;
            typedef T                            ValueType;
            typedef CVT                          CoordinatesValueType;
            typedef Math::CVector<CVT, 3>        CoordinatesType;

            virtual ValueType& operator()(std::size_t i) = 0;

            virtual const ValueType& operator()(std::size_t i) const = 0;

            virtual void getCoordinates(std::size_t i, CoordinatesType& coords) const = 0;

          protected:
            SpatialGrid& operator=(const SpatialGrid& grid)
            {
                AttributedGrid::operator=(grid);
                return *this;
            }
        };

        typedef SpatialGrid<float>  FSpatialGrid;
        typedef SpatialGrid<double> DSpatialGrid;
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_SPATIALGRID_HPP
