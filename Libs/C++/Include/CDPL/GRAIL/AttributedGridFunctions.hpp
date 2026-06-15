/* 
 * AttributedGridFunctions.hpp 
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
 * \brief Declaration of functions that operate on Grid::AttributedGrid instances.
 */

#ifndef CDPL_GRAIL_ATTRIBUTEDGRIDFUNCTIONS_HPP
#define CDPL_GRAIL_ATTRIBUTEDGRIDFUNCTIONS_HPP

#include "CDPL/GRAIL/APIPrefix.hpp"


namespace CDPL
{

    namespace Grid
    {

        class AttributedGrid;
    }

    namespace GRAIL
    {

        /**
         * \brief Returns the value of the GRAIL::AttributedGridProperty::FEATURE_TYPE property of the grid \a grid.
         * \param grid The grid for which to return the property value.
         * \return The feature type value.
         */
        CDPL_GRAIL_API unsigned int getFeatureType(const Grid::AttributedGrid& grid);

        /**
         * \brief Sets the value of the GRAIL::AttributedGridProperty::FEATURE_TYPE property of the grid \a grid.
         * \param grid The grid for which to set the property value.
         * \param type The new feature type value.
         */
        CDPL_GRAIL_API void setFeatureType(Grid::AttributedGrid& grid, unsigned int type);

        /**
         * \brief Clears the value of the GRAIL::AttributedGridProperty::FEATURE_TYPE property of the grid \a grid.
         * \param grid The grid for which to clear the property value.
         */
        CDPL_GRAIL_API void clearFeatureType(Grid::AttributedGrid& grid);

        /**
         * \brief Tells whether \a grid carries an explicit GRAIL::AttributedGridProperty::FEATURE_TYPE property.
         * \param grid The grid for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_GRAIL_API bool hasFeatureType(const Grid::AttributedGrid& grid);


        /**
         * \brief Returns the value of the GRAIL::AttributedGridProperty::TARGET_FEATURE_TYPE property of the grid \a grid.
         * \param grid The grid for which to return the property value.
         * \return The target feature type value.
         */
        CDPL_GRAIL_API unsigned int getTargetFeatureType(const Grid::AttributedGrid& grid);

        /**
         * \brief Sets the value of the GRAIL::AttributedGridProperty::TARGET_FEATURE_TYPE property of the grid \a grid.
         * \param grid The grid for which to set the property value.
         * \param type The new target feature type value.
         */
        CDPL_GRAIL_API void setTargetFeatureType(Grid::AttributedGrid& grid, unsigned int type);

        /**
         * \brief Clears the value of the GRAIL::AttributedGridProperty::TARGET_FEATURE_TYPE property of the grid \a grid.
         * \param grid The grid for which to clear the property value.
         */
        CDPL_GRAIL_API void clearTargetFeatureType(Grid::AttributedGrid& grid);

        /**
         * \brief Tells whether \a grid carries an explicit GRAIL::AttributedGridProperty::TARGET_FEATURE_TYPE property.
         * \param grid The grid for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_GRAIL_API bool hasTargetFeatureType(const Grid::AttributedGrid& grid);
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_ATTRIBUTEDGRIDFUNCTIONS_HPP
