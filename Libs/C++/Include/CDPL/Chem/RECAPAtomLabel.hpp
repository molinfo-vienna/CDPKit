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
         * \brief Provides constants for the labeling of atoms of bonds matched by a RECAP fragmentation rule.
         * \see [\ref RECAP]
         */
        namespace RECAPAtomLabel
        {

            /**
             * \brief Specifies that the atom carries no RECAP label.
             */
            constexpr unsigned int NONE                     = 0;

            /**
             * \brief Specifies the nitrogen side of an amide bond cleaved by the RECAP \c AMIDE rule.
             */
            constexpr unsigned int AMIDE_N                  = 1;

            /**
             * \brief Specifies the carbon side of an amide bond cleaved by the RECAP \c AMIDE rule.
             */
            constexpr unsigned int AMIDE_C                  = 2;

            /**
             * \brief Specifies the oxygen side of an ester bond cleaved by the RECAP \c ESTER rule.
             */
            constexpr unsigned int ESTER_O                  = 3;

            /**
             * \brief Specifies the carbon side of an ester bond cleaved by the RECAP \c ESTER rule.
             */
            constexpr unsigned int ESTER_C                  = 4;

            /**
             * \brief Specifies the nitrogen side of an amine bond cleaved by the RECAP \c AMINE rule.
             */
            constexpr unsigned int AMINE_N                  = 5;

            /**
             * \brief Specifies the carbon side of an amine bond cleaved by the RECAP \c AMINE rule.
             */
            constexpr unsigned int AMINE_C                  = 6;

            /**
             * \brief Specifies the nitrogen side of a urea bond cleaved by the RECAP \c UREA rule.
             */
            constexpr unsigned int UREA_N                   = 7;

            /**
             * \brief Specifies the carbon side of a urea bond cleaved by the RECAP \c UREA rule.
             */
            constexpr unsigned int UREA_C                   = 8;

            /**
             * \brief Specifies the oxygen side of an ether bond cleaved by the RECAP \c ETHER rule.
             */
            constexpr unsigned int ETHER_O                  = 9;

            /**
             * \brief Specifies the carbon side of an ether bond cleaved by the RECAP \c ETHER rule.
             */
            constexpr unsigned int ETHER_C                  = 10;

            /**
             * \brief Specifies a carbon side of an olefinic bond cleaved by the RECAP \c OLEFIN rule.
             */
            constexpr unsigned int OLEFIN_C                 = 11;

            /**
             * \brief Specifies the quaternary-nitrogen side of a bond cleaved by the RECAP \c QUARTERNARY_N rule.
             */
            constexpr unsigned int QUARTERNARY_N_N          = 12;

            /**
             * \brief Specifies the carbon side of a bond cleaved by the RECAP \c QUARTERNARY_N rule.
             */
            constexpr unsigned int QUARTERNARY_N_C          = 13;

            /**
             * \brief Specifies the aromatic-N side of a bond cleaved by the RECAP \c AROMATIC_N_ALIPHATIC_C rule.
             */
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C_N = 14;

            /**
             * \brief Specifies the aliphatic-C side of a bond cleaved by the RECAP \c AROMATIC_N_ALIPHATIC_C rule.
             */
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C_C = 15;

            /**
             * \brief Specifies the lactam-N side of a bond cleaved by the RECAP \c LACTAM_N_ALIPHATIC_C rule.
             */
            constexpr unsigned int LACTAM_N_ALIPHATIC_C_N   = 16;

            /**
             * \brief Specifies the aliphatic-C side of a bond cleaved by the RECAP \c LACTAM_N_ALIPHATIC_C rule.
             */
            constexpr unsigned int LACTAM_N_ALIPHATIC_C_C   = 17;

            /**
             * \brief Specifies an aromatic-C side of a biaryl bond cleaved by the RECAP \c AROMATIC_C_AROMATIC_C rule.
             */
            constexpr unsigned int AROMATIC_C_AROMATIC_C_C  = 18;

            /**
             * \brief Specifies the nitrogen side of a sulfonamide bond cleaved by the RECAP \c SULFONAMIDE rule.
             */
            constexpr unsigned int SULFONAMIDE_N            = 19;

            /**
             * \brief Specifies the sulfur side of a sulfonamide bond cleaved by the RECAP \c SULFONAMIDE rule.
             */
            constexpr unsigned int SULFONAMIDE_S            = 20;
        } // namespace RECAPAtomLabel
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RECAPATOMLABEL_HPP
