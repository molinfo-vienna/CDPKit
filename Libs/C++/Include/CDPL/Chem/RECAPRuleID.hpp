/* 
 * RECAPRuleID.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::RECAPRuleID.
 */

#ifndef CDPL_CHEM_RECAPRULEID_HPP
#define CDPL_CHEM_RECAPRULEID_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants for the identification of RECAP fragmentation rules.
         * \see [\ref RECAP]
         */
        namespace RECAPRuleID
        {

            /** \brief Specifies that no RECAP rule matched the bond. */
            constexpr unsigned int NONE                   = 0;
            /** \brief Specifies the RECAP rule for amide bond cleavage. */
            constexpr unsigned int AMIDE                  = 1;
            /** \brief Specifies the RECAP rule for ester bond cleavage. */
            constexpr unsigned int ESTER                  = 2;
            /** \brief Specifies the RECAP rule for amine bond cleavage. */
            constexpr unsigned int AMINE                  = 3;
            /** \brief Specifies the RECAP rule for urea bond cleavage. */
            constexpr unsigned int UREA                   = 4;
            /** \brief Specifies the RECAP rule for ether bond cleavage. */
            constexpr unsigned int ETHER                  = 5;
            /** \brief Specifies the RECAP rule for olefinic-bond cleavage. */
            constexpr unsigned int OLEFIN                 = 6;
            /** \brief Specifies the RECAP rule for quaternary-nitrogen bond cleavage. */
            constexpr unsigned int QUARTERNARY_N          = 7;
            /** \brief Specifies the RECAP rule for aromatic-N to aliphatic-C bond cleavage. */
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C = 8;
            /** \brief Specifies the RECAP rule for lactam-N to aliphatic-C bond cleavage. */
            constexpr unsigned int LACTAM_N_ALIPHATIC_C   = 9;
            /** \brief Specifies the RECAP rule for aromatic-C to aromatic-C bond cleavage (biaryl). */
            constexpr unsigned int AROMATIC_C_AROMATIC_C  = 10;
            /** \brief Specifies the RECAP rule for sulfonamide bond cleavage. */
            constexpr unsigned int SULFONAMIDE            = 11;
        } // namespace RECAPRuleID
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RECAPRULEID_HPP
