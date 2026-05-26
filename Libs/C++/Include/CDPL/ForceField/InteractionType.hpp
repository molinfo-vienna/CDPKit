/* 
 * InteractionType.hpp 
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
 * \brief Definition of constants in namespace CDPL::ForceField::InteractionType.
 */

#ifndef CDPL_FORCEFIELD_INTERACTIONTYPE_HPP
#define CDPL_FORCEFIELD_INTERACTIONTYPE_HPP


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Provides flags for the specification of a set of force field interaction types.
         */
        namespace InteractionType
        {

            /**
             * \brief Specifies no interaction.
             */
            constexpr unsigned int NONE                 = 0x00;

            /**
             * \brief Specifies a bond stretching interaction.
             */
            constexpr unsigned int BOND_STRETCHING      = 0x01;

            /**
             * \brief Specifies an angle bending interaction.
             */
            constexpr unsigned int ANGLE_BENDING        = 0x02;

            /**
             * \brief Specifies a stretch-bend coupling interaction.
             */
            constexpr unsigned int STRETCH_BEND         = 0x04;

            /**
             * \brief Specifies an out-of-plane bending interaction.
             */
            constexpr unsigned int OUT_OF_PLANE_BENDING = 0x08;

            /**
             * \brief Specifies a torsion interaction.
             */
            constexpr unsigned int TORSION              = 0x10;

            /**
             * \brief Specifies a Van der Waals interaction.
             */
            constexpr unsigned int VAN_DER_WAALS        = 0x20;

            /**
             * \brief Specifies an electrostatic interaction.
             */
            constexpr unsigned int ELECTROSTATIC        = 0x40;

            /**
             * \brief A bitmask covering all interaction types.
             */
            constexpr unsigned int ALL                  = 0x7f;
        } // namespace InteractionType
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_INTERACTIONTYPE_HPP
