/* 
 * AttributedGrid.hpp 
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
 * \brief Definition of class CDPL::Grid::AttributedGrid.
 */

#ifndef CDPL_GRID_ATTRIBUTEDGRID_HPP
#define CDPL_GRID_ATTRIBUTEDGRID_HPP

#include <cstddef>
#include <memory>

#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL
{

    namespace Grid
    {

        /**
         * \brief Abstract base class for grid types that also carry generic key/value properties.
         *
         * \c %AttributedGrid combines the property-bag interface from Base::PropertyContainer with the
         * minimal grid interface required to know the number of grid elements and whether the grid is
         * empty. Concrete grid types (e.g. Grid::RegularGrid) implement the pure virtual member functions.
         */
        class AttributedGrid : public Base::PropertyContainer
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %AttributedGrid instances.
             */
            typedef std::shared_ptr<AttributedGrid> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~AttributedGrid() {}

            /**
             * \brief Returns the total number of grid elements.
             * \return The number of grid elements.
             */
            virtual std::size_t getNumElements() const = 0;

            /**
             * \brief Tells whether the grid is empty.
             * \return \c true if the grid is empty, and \c false otherwise.
             */
            virtual bool isEmpty() const = 0;

          protected:
            /**
             * \brief Assignment operator.
             * \param grid The other \c %AttributedGrid instance.
             * \return A reference to itself.
             */
            AttributedGrid& operator=(const AttributedGrid& grid)
            {
                Base::PropertyContainer::operator=(grid);
                return *this;
            }
        };
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_ATTRIBUTEDGRID_HPP
