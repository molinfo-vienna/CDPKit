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
         * \brief Abstract base class for attributed grids whose elements have a defined 3D position in space.
         *
         * Concrete subclasses (e.g. Grid::RegularGrid) implement element access and the mapping from a linear
         * element index to the corresponding 3D world coordinates.
         *
         * \tparam T The grid element value type.
         * \tparam CVT The coordinate value type (defaults to \a T).
         */
        template <typename T, typename CVT = T>
        class SpatialGrid : public AttributedGrid
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %SpatialGrid instances. */
            typedef std::shared_ptr<SpatialGrid> SharedPointer;
            /** \brief The grid element value type. */
            typedef T                            ValueType;
            /** \brief The coordinate value type. */
            typedef CVT                          CoordinatesValueType;
            /** \brief The fixed-size 3D coordinate vector type. */
            typedef Math::CVector<CVT, 3>        CoordinatesType;

            /**
             * \brief Returns a reference to the grid element at linear index \a i.
             * \param i The linear element index.
             * \return A reference to the grid element.
             */
            virtual ValueType& operator()(std::size_t i) = 0;

            /**
             * \brief Returns a \c const reference to the grid element at linear index \a i.
             * \param i The linear element index.
             * \return A \c const reference to the grid element.
             */
            virtual const ValueType& operator()(std::size_t i) const = 0;

            /**
             * \brief Returns the 3D coordinates of the grid element at linear index \a i.
             * \param i The linear element index.
             * \param coords The output coordinates.
             */
            virtual void getCoordinates(std::size_t i, CoordinatesType& coords) const = 0;

          protected:
            SpatialGrid& operator=(const SpatialGrid& grid)
            {
                AttributedGrid::operator=(grid);
                return *this;
            }
        };

        /** \brief Convenience alias for the single-precision spatial-grid abstract base. */
        typedef SpatialGrid<float>  FSpatialGrid;
        /** \brief Convenience alias for the double-precision spatial-grid abstract base. */
        typedef SpatialGrid<double> DSpatialGrid;
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_SPATIALGRID_HPP
