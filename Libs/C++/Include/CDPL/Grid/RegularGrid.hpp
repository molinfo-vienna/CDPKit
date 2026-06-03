/* 
 * RegularGrid.hpp 
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
 * \brief Definition of a regular spatial grid data type.
 */

#ifndef CDPL_GRID_REGULARGRID_HPP
#define CDPL_GRID_REGULARGRID_HPP

#include <memory>

#include "CDPL/Grid/SpatialGrid.hpp"
#include "CDPL/Math/RegularSpatialGrid.hpp"


namespace CDPL
{

    namespace Grid
    {

        /**
         * \brief Implementation of the Grid::SpatialGrid interface for regular spatial grids.
         *
         * \c %RegularGrid combines the property-bag/grid interface inherited from Grid::SpatialGrid with
         * the data storage and coordinate handling of Math::RegularSpatialGrid. The grid spacing can be
         * specified separately for each spatial dimension or jointly via a single value.
         *
         * \tparam T The grid element value type.
         * \tparam CVT The coordinates value type (defaults to \a T).
         */
        template <typename T, typename CVT = T>
        class RegularGrid : public SpatialGrid<T, CVT>,
                            public Math::RegularSpatialGrid<T, CVT>
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %RegularGrid instances.
             */
            typedef std::shared_ptr<RegularGrid>                            SharedPointer;
            typedef typename SpatialGrid<T, CVT>::ValueType                 ValueType;
            typedef typename SpatialGrid<T, CVT>::CoordinatesValueType      CoordinatesValueType;
            typedef typename SpatialGrid<T, CVT>::CoordinatesType           CoordinatesType;
            typedef typename Math::RegularSpatialGrid<T, CVT>::GridDataType GridDataType;

            /**
             * \brief Constructs an empty \c %RegularGrid with the given grid spacing in \e x, \e y and \e z direction.
             * \param xs The grid spacing in the \e x direction.
             * \param ys The grid spacing in the \e y direction.
             * \param zs The grid spacing in the \e z direction.
             */
            RegularGrid(const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs):
                Math::RegularSpatialGrid<T, CVT>(xs, ys, zs) {}

            /**
             * \brief Constructs a \c %RegularGrid initialized from \a data, with the given grid spacing in \e x, \e y and \e z direction.
             * \param data The initial grid data.
             * \param xs The grid spacing in the \e x direction.
             * \param ys The grid spacing in the \e y direction.
             * \param zs The grid spacing in the \e z direction.
             */
            RegularGrid(const GridDataType& data, const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs):
                Math::RegularSpatialGrid<T, CVT>(data, xs, ys, zs) {}

            /**
             * \brief Constructs an empty \c %RegularGrid with isotropic grid spacing.
             * \param s The isotropic grid spacing applied to all three spatial dimensions.
             */
            explicit RegularGrid(const CoordinatesValueType& s):
                Math::RegularSpatialGrid<T, CVT>(s) {}

            /**
             * \brief Constructs a \c %RegularGrid initialized from \a data with isotropic grid spacing.
             * \param data The initial grid data.
             * \param s The isotropic grid spacing applied to all three spatial dimensions.
             */
            RegularGrid(const GridDataType& data, const CoordinatesValueType& s):
                Math::RegularSpatialGrid<T, CVT>(data, s) {}

            using Math::RegularSpatialGrid<T>::operator();

            using Math::RegularSpatialGrid<T>::getCoordinates;

            /**
             * \brief Returns a reference to the grid element at linear index \a i.
             * \param i The linear element index.
             * \return A reference to the grid element.
             */
            ValueType& operator()(std::size_t i)
            {
                return Math::RegularSpatialGrid<T>::operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the grid element at linear index \a i.
             * \param i The linear element index.
             * \return A \c const reference to the grid element.
             */
            const ValueType& operator()(std::size_t i) const
            {
                return Math::RegularSpatialGrid<T>::operator()(i);
            }

            /**
             * \brief Returns the total number of grid elements.
             * \return The total number of grid elements.
             */
            std::size_t getNumElements() const
            {
                return Math::RegularSpatialGrid<T>::getSize();
            }

            /**
             * \brief Returns the 3D coordinates of the grid element at linear index \a i.
             * \param i The linear element index.
             * \param coords The output coordinates.
             */
            void getCoordinates(std::size_t i, CoordinatesType& coords) const
            {
                Math::RegularSpatialGrid<T>::getCoordinates(i, coords);
            }

            /**
             * \brief Tells whether the grid is empty.
             * \return \c true if the grid is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return Math::RegularSpatialGrid<T>::isEmpty();
            }
        };

        /**
         * \brief A regular spatial grid storing single-precision floating-point values.
         */
        typedef RegularGrid<float>  FRegularGrid;

        /**
         * \brief A regular spatial grid storing double-precision floating-point values.
         */
        typedef RegularGrid<double> DRegularGrid;
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_REGULARGRID_HPP
