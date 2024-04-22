/* 
 * CoordinationGeometry.hpp 
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
 * \brief Definition of constants in namespace CDPL::MolProp::CoordinationGeometry.
 */

#ifndef CDPL_MOLPROP_COORDINATIONGEOMETRY_HPP
#define CDPL_MOLPROP_COORDINATIONGEOMETRY_HPP


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Provides constants used to specify the spatial geometry of atom arrangements around a common central atom.
         */
        namespace CoordinationGeometry
        {

            /**
             * \brief Specifies undefined or unknown geometry.
             */
            constexpr unsigned int UNDEF = 0;

            /**
             * \brief Specifies that a geometry cannot be assigned due to the lack of enough (>1) defining entities.
             */
            constexpr unsigned int NONE = 1;

            /**
             * \brief Specifies <i>linear</i> geometry.
             */
            constexpr unsigned int LINEAR = 2;

            /**
             * \brief Specifies <i>trigonal planar</i> geometry.
             */
            constexpr unsigned int TRIGONAL_PLANAR = 3;

            /**
             * \brief Specifies <i>tetrahedral</i> geometry.
             */
            constexpr unsigned int TETRAHEDRAL = 4;

            /**
             * \brief Specifies <i>trigonal bipyramidal</i> geometry.
             */
            constexpr unsigned int TRIGONAL_BIPYRAMIDAL = 5;

            /**
             * \brief Specifies <i>octahedral</i> geometry.
             */
            constexpr unsigned int OCTAHEDRAL = 6;

            /**
             * \brief Specifies <i>pentagonal bipyramidal</i> geometry.
             */
            constexpr unsigned int PENTAGONAL_BIPYRAMIDAL = 7;

            /**
             * \brief Specifies <i>square antiprismatic</i> geometry.
             */
            constexpr unsigned int SQUARE_ANTIPRISMATIC = 8;

            /**
             * \brief Specifies <i>bent</i> geometry.
             */
            constexpr unsigned int BENT = 9;

            /**
             * \brief Specifies <i>trigonal pyramidal</i> geometry.
             */
            constexpr unsigned int TRIGONAL_PYRAMIDAL = 10;

            /**
             * \brief Specifies <i>square planar</i> geometry.
             */
            constexpr unsigned int SQUARE_PLANAR = 11;

            /**
             * \brief Specifies <i>square pyramidal</i> geometry.
             */
            constexpr unsigned int SQUARE_PYRAMIDAL = 12;

            /**
             * \brief Specifies <i>T-shaped</i> geometry.
             */
            constexpr unsigned int T_SHAPED = 13;

            /**
             * \brief Specifies <i>seesaw</i> geometry.
             */
            constexpr unsigned int SEESAW = 14;

            /**
             * \brief Specifies <i>pentagonal pyramidal</i> geometry.
             */
            constexpr unsigned int PENTAGONAL_PYRAMIDAL = 15;

            /**
             * \brief Specifies <i>pentagonal planar</i> geometry.
             */
            constexpr unsigned int PENTAGONAL_PLANAR = 16;
        } // namespace CoordinationGeometry
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_COORDINATIONGEOMETRY_HPP
