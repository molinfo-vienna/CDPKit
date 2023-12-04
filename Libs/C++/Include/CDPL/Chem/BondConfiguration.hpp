/* 
 * BondConfiguration.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondConfiguration.
 */

#ifndef CDPL_CHEM_BONDCONFIGURATION_HPP
#define CDPL_CHEM_BONDCONFIGURATION_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants that are used to specify the <em>cis/trans</em> configuration of bonds.
         */
        namespace BondConfiguration
        {

            /**
             * \brief Specifies that the configuration of the bond is completely undefined.
             */
            const unsigned int UNDEF  = 0;

            /**
             * \brief Specifies that a bond does not meet the requirements to be assigned a configuration.
             */
            const unsigned int NONE   = 0x1;

            /**
             * \brief Specifies that the bond has <em>trans</em> configuration.
             */
            const unsigned int TRANS  = 0x2;

            /**
             * \brief Specifies that the bond has <em>cis</em> configuration.
             */
            const unsigned int CIS    = 0x4;

            /**
             * \brief Specifies that the bond meets the requirements but has no defined configuration.
             */
            const unsigned int EITHER = 0x8;
          
        } // namespace BondConfiguration
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDCONFIGURATION_HPP
