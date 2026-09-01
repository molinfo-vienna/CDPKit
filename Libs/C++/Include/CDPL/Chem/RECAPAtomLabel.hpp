/* 
 * RECAPAtomLabel.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::RECAPAtomLabel.
 */

#ifndef CDPL_CHEM_RECAPATOMLABEL_HPP
#define CDPL_CHEM_RECAPATOMLABEL_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants for labeling the endpoints of bonds matched by \e RECAP fragmentation rules.
         * \see [\ref RECAP]
         */
        namespace RECAPAtomLabel
        {

            /**
             * \brief Specifies that the atom carries no label.
             */
            constexpr unsigned int NONE                     = 0;

            /**
             * \brief Specifies the nitrogen side of an amide bond.
             */
            constexpr unsigned int AMIDE_N                  = 1;

            /**
             * \brief Specifies the carbon side of an amide bond.
             */
            constexpr unsigned int AMIDE_C                  = 2;

            /**
             * \brief Specifies the oxygen side of an ester bond.
             */
            constexpr unsigned int ESTER_O                  = 3;

            /**
             * \brief Specifies the carbon side of an ester bond.
             */
            constexpr unsigned int ESTER_C                  = 4;

            /**
             * \brief Specifies the nitrogen side of an amine bond.
             */
            constexpr unsigned int AMINE_N                  = 5;

            /**
             * \brief Specifies the carbon side of an amine bond.
             */
            constexpr unsigned int AMINE_C                  = 6;

            /**
             * \brief Specifies the nitrogen side of a urea bond.
             */
            constexpr unsigned int UREA_N                   = 7;

            /**
             * \brief Specifies the carbon side of a urea bond.
             */
            constexpr unsigned int UREA_C                   = 8;

            /**
             * \brief Specifies the oxygen side of an ether bond.
             */
            constexpr unsigned int ETHER_O                  = 9;

            /**
             * \brief Specifies the carbon side of an ether bond.
             */
            constexpr unsigned int ETHER_C                  = 10;

            /**
             * \brief Specifies a carbon side of an olefinic bond.
             */
            constexpr unsigned int OLEFIN_C                 = 11;

            /**
             * \brief Specifies the nitrogen side of a quaternary amine bond.
             */
            constexpr unsigned int QUATERNARY_N_N           = 12;

            /**
             * \brief Specifies the carbon side of a quaternary amine bond.
             */
            constexpr unsigned int QUATERNARY_N_C           = 13;

            /**
             * \brief Specifies the nitrogen side of an aromatic nitrogen to aliphatic carbon bond.
             */
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C_N = 14;

            /**
             * \brief Specifies the carbon side of an aromatic nitrogen to aliphatic carbon bond.
             */
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C_C = 15;

            /**
             * \brief Specifies the nitrogen side of a lactam bond.
             */
            constexpr unsigned int LACTAM_N_ALIPHATIC_C_N   = 16;

            /**
             * \brief Specifies the carbon side of a lactam bond.
             */
            constexpr unsigned int LACTAM_N_ALIPHATIC_C_C   = 17;

            /**
             * \brief Specifies an atom of an aromatic carbon-carbon bond.
             */
            constexpr unsigned int AROMATIC_C_AROMATIC_C_C  = 18;

            /**
             * \brief Specifies the nitrogen side of a sulfonamide bond.
             */
            constexpr unsigned int SULFONAMIDE_N            = 19;

            /**
             * \brief Specifies the sulfur side of a sulfonamide bond.
             */
            constexpr unsigned int SULFONAMIDE_S            = 20;
        } // namespace RECAPAtomLabel
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RECAPATOMLABEL_HPP
