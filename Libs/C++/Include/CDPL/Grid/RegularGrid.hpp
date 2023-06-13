/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RegularGrid.hpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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
		 * \brief RegularGrid.
		 */
		template <typename T, typename CVT = T> 
		class RegularGrid : public SpatialGrid<T, CVT>, public Math::RegularSpatialGrid<T, CVT>
		{

		public:
			typedef std::shared_ptr<RegularGrid> SharedPointer;
			typedef typename SpatialGrid<T, CVT>::ValueType ValueType;
			typedef typename SpatialGrid<T, CVT>::CoordinatesValueType CoordinatesValueType;
			typedef typename SpatialGrid<T, CVT>::CoordinatesType CoordinatesType;
			typedef typename Math::RegularSpatialGrid<T, CVT>::GridDataType GridDataType;
	
			RegularGrid(const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs): Math::RegularSpatialGrid<T, CVT>(xs, ys, zs) {}

			RegularGrid(const GridDataType& data, const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs): Math::RegularSpatialGrid<T, CVT>(data, xs, ys, zs) {}
	
			explicit RegularGrid(const CoordinatesValueType& s): Math::RegularSpatialGrid<T, CVT>(s) {}

			RegularGrid(const GridDataType& data, const CoordinatesValueType& s): Math::RegularSpatialGrid<T, CVT>(data, s) {}

			using Math::RegularSpatialGrid<T>::operator();

			using Math::RegularSpatialGrid<T>::getCoordinates;

			ValueType& operator()(std::size_t i) {
				return Math::RegularSpatialGrid<T>::operator()(i);
			}

			const ValueType& operator()(std::size_t i) const {
				return Math::RegularSpatialGrid<T>::operator()(i);
			}
	
			std::size_t getNumElements() const {
				return Math::RegularSpatialGrid<T>::getSize();
			}

			void getCoordinates(std::size_t i, CoordinatesType& coords) const {
				Math::RegularSpatialGrid<T>::getCoordinates(i, coords);
			}

			bool isEmpty() const {
				return Math::RegularSpatialGrid<T>::isEmpty();
			}
		};

		typedef RegularGrid<float> FRegularGrid;
		typedef RegularGrid<double> DRegularGrid;
    }
}

#endif // CDPL_GRID_REGULARGRID_HPP
