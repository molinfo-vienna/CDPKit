/* 
 * DRegularGridWriter.hpp 
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
 * \brief Definition of the class CDPL::Grid::DRegularGridWriter.
 */

#ifndef CDPL_GRID_DREGULARGRIDWRITER_HPP
#define CDPL_GRID_DREGULARGRIDWRITER_HPP

#include "CDPL/Util/MultiFormatDataWriter.hpp"


namespace CDPL
{

    namespace Grid
    {

        template <typename T> class RegularGrid<T>;
        typedef RegularGrid<double> DRegularGrid;

        /**
         * \brief Writer for grid data of type Grid::DRegularGrid in any supported format.
         */
        typedef Util::MultiFormatDataWriter<DRegularGrid> DRegularGridWriter;

    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_DREGULARGRIDWRITER_HPP
