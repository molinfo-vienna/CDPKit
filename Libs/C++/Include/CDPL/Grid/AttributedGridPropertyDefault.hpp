/* 
 * AttributedGridPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Grid::AttributedGridPropertyDefault.
 */

#ifndef CDPL_GRID_ATTRIBUTEDGRIDPROPERTYDEFAULT_HPP
#define CDPL_GRID_ATTRIBUTEDGRIDPROPERTYDEFAULT_HPP

#include <string>

#include "CDPL/Grid/APIPrefix.hpp"


namespace CDPL
{

    namespace Grid
    {

        /**
         * \brief Provides default values for built-in Grid::AttributedGrid properties.
         */
        namespace AttributedGridPropertyDefault
        {

            extern CDPL_GRID_API const std::string NAME;
        }
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_ATTRIBUTEDGRIDPROPERTYDEFAULT_HPP
