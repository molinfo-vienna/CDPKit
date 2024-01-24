/* 
 * CIPDescriptor.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::CIPDescriptor.
 */

#ifndef CDPL_CHEM_CIPDESCRIPTOR_HPP
#define CDPL_CHEM_CIPDESCRIPTOR_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants for the specification of stereogenic atom/bond configurations 
         *        determined by the CIP sequence rules.
         * \since 1.1
         */
        namespace CIPDescriptor
        {

            /**
             * \brief Specifies that the configuration of the stereocenter (if any) is completely undefined.
             */
            const unsigned int UNDEF    = 0;

            /**
             * \brief Specifies that the atom/bond is not a stereogenic center and thus cannot be assigned a 
             *        configuration.
             */ 
            const unsigned int NONE     = 1;

            /**
             * \brief Specifies that the atom/bond is a stereogenic center but has no specified configuration.
             */
            const unsigned int NS       = 2;

            /**
             * \brief Specifies that the stereocenter has \e R configuration.
             */
            const unsigned int R        = 3;

            /**
             * \brief Specifies that the stereocenter has \e S configuration.
             */
            const unsigned int S        = 4;

            /**
             * \brief Specifies that the stereocenter has \e r configuration.
             */
            const unsigned int r        = 5;

            /**
             * \brief Specifies that the stereocenter has \e s configuration.
             */
            const unsigned int s        = 6;

            /**
             * \brief Specifies that the stereocenter has \e seqTrans configuration.
             */
            const unsigned int seqTrans = 7;
            
            /**
             * \brief Specifies that the stereocenter has \e seqCis configuration.
             */
            const unsigned int seqCis   = 8;

            /**
             * \brief Specifies that the stereocenter has \e E configuration.
             */
            const unsigned int E        = 9;
            
            /**
             * \brief Specifies that the stereocenter has \e Z configuration.
             */
            const unsigned int Z        = 10;
            
            /**
             * \brief Specifies that the stereocenter has \e M configuration.
             */
            const unsigned int M        = 11;
            
            /**
             * \brief Specifies that the stereocenter has \e P configuration.
             */
            const unsigned int P        = 12;

            /**
             * \brief Specifies that the stereocenter has \e m configuration.
             */
            const unsigned int m        = 13;

            /**
             * \brief Specifies that the stereocenter has \e p configuration.
             */
            const unsigned int p        = 14;
        } // namespace CIPDescriptor
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPDESCRIPTOR_HPP
