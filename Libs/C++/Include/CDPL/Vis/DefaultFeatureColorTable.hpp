/* 
 * DefaultFeatureColorTable.hpp 
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
 * \brief Definition of class CDPL::Vis::DefaultFeatureColorTable.
 */

#ifndef CDPL_VIS_DEFAULTFEATURECOLORTABLE_HPP
#define CDPL_VIS_DEFAULTFEATURECOLORTABLE_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Provides default colors for the type dependent coloring of chemical features in 3D visualizations 
         *        of pharmacophores.
         * \since 1.3
         */
        class CDPL_VIS_API DefaultFeatureColorTable : public ColorTable
        {

          public:
            /**
             * \brief Initializes the table with default colors for builtin pharmacophoric feature types.
             */
            DefaultFeatureColorTable();
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_DEFAULTFEATURECOLORTABLE_HPP
