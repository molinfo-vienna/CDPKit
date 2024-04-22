/* 
 * Alignment.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::Alignment.
 */

#ifndef CDPL_VIS_ALIGNMENT_HPP
#define CDPL_VIS_ALIGNMENT_HPP


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Provides flags that are used to specify the 2D alignment of graphical objects within a bounded rectangular
         *        area.
         *
         * The flags may be combined by a bitwise OR operation to specify a composite alignment for both directions. 
         * For example: <tt>(Alignment::RIGHT | Alignment::BOTTOM)</tt> specifies an alignment to the bottom-right corner. 
         */
        namespace Alignment
        {

            /**
             * \brief Specifies that an object has no special alignment.
             */
            constexpr unsigned int NONE = 0;

            /**
             * \brief Specifies an alignment to the left.
             */
            constexpr unsigned int LEFT = 0x1;

            /**
             * \brief Specifies an alignment to the right.
             */
            constexpr unsigned int RIGHT = 0x2;

            /**
             * \brief Specifies that an object has to be centered horizontally.
             */
            constexpr unsigned int H_CENTER = LEFT | RIGHT;

            /**
             * \brief A bitmask for all horizontal alignment flags.
             */
            constexpr unsigned int H_ALIGNMENT_MASK = H_CENTER;

            /**
             * \brief Specifies an alignment to the top.
             */
            constexpr unsigned int TOP = 0x4;

            /**
             * \brief Specifies an alignment to the bottom.
             */
            constexpr unsigned int BOTTOM = 0x8;

            /**
             * \brief Specifies that an object has to be centered vertically.
             */
            constexpr unsigned int V_CENTER = TOP | BOTTOM;

            /**
             * \brief A bitmask for all vertical alignment flags.
             */
            constexpr unsigned int V_ALIGNMENT_MASK = V_CENTER;

            /**
             * \brief Specifies that an object has to be centered horizontally and vertically.
             */
            constexpr unsigned int CENTER = H_CENTER | V_CENTER;
        } // namespace Alignment
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_ALIGNMENT_HPP
