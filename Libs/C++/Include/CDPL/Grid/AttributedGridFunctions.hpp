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

#ifndef CDPL_GRID_ATTRIBUTEDGRIDFUNCTIONS_HPP
#define CDPL_GRID_ATTRIBUTEDGRIDFUNCTIONS_HPP

#include <string>

#include "CDPL/Grid/APIPrefix.hpp"


namespace CDPL
{

    namespace Grid
    {

        class AttributedGrid;

        /**
         * \brief Returns the value of the Grid::AttributedGridProperty::NAME property of the attributed grid \a grid.
         * \param grid The attributed grid for which to return the property value.
         * \return A \c const reference to the name.
         */
        CDPL_GRID_API const std::string& getName(const AttributedGrid& grid);

        /**
         * \brief Sets the value of the Grid::AttributedGridProperty::NAME property of the attributed grid \a grid to \a name.
         * \param grid The attributed grid for which to set the property value.
         * \param name The new name.
         */
        CDPL_GRID_API void setName(AttributedGrid& grid, const std::string& name);

        /**
         * \brief Clears the value of the Grid::AttributedGridProperty::NAME property of the attributed grid \a grid.
         * \param grid The attributed grid for which to clear the property value.
         */
        CDPL_GRID_API void clearName(AttributedGrid& grid);

        /**
         * \brief Tells whether the Grid::AttributedGridProperty::NAME property of the attributed grid \a grid is set.
         * \param grid The attributed grid for which to query the property value.
         * \return \c true if the name property is set, and \c false otherwise.
         */
        CDPL_GRID_API bool hasName(const AttributedGrid& grid);


        /**
         * \brief Returns the value of the Grid::AttributedGridProperty::COMMENT property of the attributed grid \a grid.
         * \param grid The attributed grid for which to return the property value.
         * \return A \c const reference to the comment.
         * \since 1.4
         */
        CDPL_GRID_API const std::string& getComment(const AttributedGrid& grid);

        /**
         * \brief Sets the value of the Grid::AttributedGridProperty::COMMENT property of the attributed grid \a grid to \a comment.
         * \param grid The attributed grid for which to set the property value.
         * \param comment The new comment.
         * \since 1.4
         */
        CDPL_GRID_API void setComment(AttributedGrid& grid, const std::string& comment);

        /**
         * \brief Clears the value of the Grid::AttributedGridProperty::COMMENT property of the attributed grid \a grid.
         * \param grid The attributed grid for which to clear the property value.
         * \since 1.4
         */
        CDPL_GRID_API void clearComment(AttributedGrid& grid);

        /**
         * \brief Tells whether the Grid::AttributedGridProperty::COMMENT property of the attributed grid \a grid is set.
         * \param grid The attributed grid for which to query the property value.
         * \return \c true if the comment property is set, and \c false otherwise.
         * \since 1.4
         */
        CDPL_GRID_API bool hasComment(const AttributedGrid& grid);
        
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_ATTRIBUTEDGRIDFUNCTIONS_HPP
