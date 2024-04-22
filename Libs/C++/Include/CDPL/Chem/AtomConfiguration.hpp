/* 
 * AtomConfiguration.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::AtomConfiguration.
 */

#ifndef CDPL_CHEM_ATOMCONFIGURATION_HPP
#define CDPL_CHEM_ATOMCONFIGURATION_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants that are used to specify the <em>R/S</em> configuration of atoms.
         */
        namespace AtomConfiguration
        {

            /**
             * \brief Specifies that the configuration of the atom is completely undefined.
             */
            constexpr unsigned int UNDEF  = 0;

            /**
             * \brief Specifies that the atom does not meet the requirements to be assigned a configuration.
             */
            constexpr unsigned int NONE   = 0x1;

            /**
             * \brief Specifies that the atom has \e R configuration.
             */
            constexpr unsigned int R      = 0x2;

            /**
             * \brief Specifies that the atom has \e S configuration.
             */
            constexpr unsigned int S      = 0x4;

            /**
             * \brief Specifies that the atom meets the requirements but has no defined configuration.
             */
            constexpr unsigned int EITHER = 0x8;

            /**
             * \brief Specifies that the geometry of the ligand arrangement is <em>square planar</em>.
             */
            constexpr unsigned int SP     = 16;

            /**
             * \brief Specifies that the geometry of the ligand arrangement is <em>trigonal bipyramidal</em>.
             */
            constexpr unsigned int TB     = SP + 4;

            /**
             * \brief Specifies that the geometry of the ligand arrangement is <em>octahedral</em>.
             */
            constexpr unsigned int OH     = TB + 21;
            
        } // namespace AtomConfiguration
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMCONFIGURATION_HPP
