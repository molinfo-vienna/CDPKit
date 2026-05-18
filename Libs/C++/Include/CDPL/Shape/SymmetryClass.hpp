/* 
 * SymmetryClass.hpp 
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
 * \brief Definition of constants in namespace CDPL::Shape::SymmetryClass.
 */

#ifndef CDPL_SHAPE_SYMMETRYCLASS_HPP
#define CDPL_SHAPE_SYMMETRYCLASS_HPP


namespace CDPL
{

    namespace Shape
    {

        /**
         * \brief Provides constants for the rotational symmetry class of a Gaussian shape.
         */
        namespace SymmetryClass
        {


            /**
             * \brief Specifies an undefined symmetry class.
             */
            constexpr unsigned int UNDEF = 0;

            /**
             * \brief Specifies an asymmetric shape (all three principal moments of inertia distinct).
             */
            constexpr unsigned int ASYMMETRIC = 1;

            /**
             * \brief Specifies an oblate (disc-shaped) symmetric top.
             */
            constexpr unsigned int OBLATE = 2;

            /**
             * \brief Specifies a prolate (cigar-shaped) symmetric top.
             */
            constexpr unsigned int PROLATE = 3;

            /**
             * \brief Specifies a spherical top (all three principal moments of inertia equal).
             */
            constexpr unsigned int SPHERICAL = 4;
        } // namespace SymmetryClass
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_SYMMETRYCLASS_HPP
