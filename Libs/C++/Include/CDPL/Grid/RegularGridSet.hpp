/* 
 * RegularGridSet.hpp 
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
 * \brief Definition of class CDPL::Grid::RegularGridSet.
 */

#ifndef CDPL_GRID_REGULARGRIDSET_HPP
#define CDPL_GRID_REGULARGRIDSET_HPP

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Util/IndirectArray.hpp"


namespace CDPL
{

    namespace Grid
    {

        /**
         * \brief An indirected array of dynamically allocated Grid::RegularGrid instances.
         * \tparam T The grid cell value type.
         * \tparam CVT The world-coordinate value type used by the wrapped Grid::RegularGrid (defaults to \a T).
         */
        template <typename T, typename CVT = T>
        class RegularGridSet : public Util::IndirectArray<RegularGrid<T, CVT> >
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %RegularGridSet instances. */
            typedef std::shared_ptr<RegularGridSet> SharedPointer;

          private:
            const char* getClassName() const
            {
                return "RegularGridSet";
            }
        };

        /** \brief Convenience alias for the double-precision regular spatial grid sets. */
        typedef RegularGridSet<double> DRegularGridSet;
        /** \brief Convenience alias for the single-precision regular spatial grid sets. */
        typedef RegularGridSet<float>  FRegularGridSet;
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_REGULARGRIDSET_HPP
