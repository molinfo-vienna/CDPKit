/* 
 * BRICSRuleID.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BRICSRuleID.
 */

#ifndef CDPL_CHEM_BRICSRULEID_HPP
#define CDPL_CHEM_BRICSRULEID_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants for the identification of \e BRICS fragmentation rules.
         * \see [\ref BRICS]
         */
        namespace BRICSRuleID
        {

            /**
             * \brief Specifies that no rule applies.
             */
            constexpr unsigned int NONE    = 0;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L1 and L2.
             */
            constexpr unsigned int L1_L2   = 1;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L1 and L3.
             */
            constexpr unsigned int L1_L3   = 2;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L1 and L10.
             */
            constexpr unsigned int L1_L10  = 3;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L2 and L12.
             */
            constexpr unsigned int L2_L12  = 4;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L2 and L14.
             */
            constexpr unsigned int L2_L14  = 5;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L2 and L16.
             */
            constexpr unsigned int L2_L16  = 6;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L3 and L4.
             */
            constexpr unsigned int L3_L4   = 7;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L3 and L13.
             */
            constexpr unsigned int L3_L13  = 8;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L3 and L14.
             */
            constexpr unsigned int L3_L14  = 9;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L3 and L15.
             */
            constexpr unsigned int L3_L15  = 10;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L3 and L16.
             */
            constexpr unsigned int L3_L16  = 11;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L4 and L5.
             */
            constexpr unsigned int L4_L5   = 12;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L4 and L11.
             */
            constexpr unsigned int L4_L11  = 13;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L5 and L13.
             */
            constexpr unsigned int L5_L13  = 14;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L5 and L15.
             */
            constexpr unsigned int L5_L15  = 15;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L6 and L13.
             */
            constexpr unsigned int L6_L13  = 16;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L6 and L14.
             */
            constexpr unsigned int L6_L14  = 17;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L6 and L15.
             */
            constexpr unsigned int L6_L15  = 18;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L6 and L16.
             */
            constexpr unsigned int L6_L16  = 19;

            /**
             * \brief Specifies the rule cleaving the bond between two atoms of class L7.
             */
            constexpr unsigned int L7_L7   = 20;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L8 and L9.
             */
            constexpr unsigned int L8_L9   = 21;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L8 and L10.
             */
            constexpr unsigned int L8_L10  = 22;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L8 and L13.
             */
            constexpr unsigned int L8_L13  = 23;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L8 and L14.
             */
            constexpr unsigned int L8_L14  = 24;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L8 and L15.
             */
            constexpr unsigned int L8_L15  = 25;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L8 and L16.
             */
            constexpr unsigned int L8_L16  = 26;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L9 and L15.
             */
            constexpr unsigned int L9_L15  = 27;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L9 and L16.
             */
            constexpr unsigned int L9_L16  = 28;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L10 and L13.
             */
            constexpr unsigned int L10_L13 = 29;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L10 and L14.
             */
            constexpr unsigned int L10_L14 = 30;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L10 and L15.
             */
            constexpr unsigned int L10_L15 = 31;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L10 and L16.
             */
            constexpr unsigned int L10_L16 = 32;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L11 and L13.
             */
            constexpr unsigned int L11_L13 = 33;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L11 and L14.
             */
            constexpr unsigned int L11_L14 = 34;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L11 and L15.
             */
            constexpr unsigned int L11_L15 = 35;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L11 and L16.
             */
            constexpr unsigned int L11_L16 = 36;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L13 and L14.
             */
            constexpr unsigned int L13_L14 = 37;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L13 and L15.
             */
            constexpr unsigned int L13_L15 = 38;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L13 and L16.
             */
            constexpr unsigned int L13_L16 = 39;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L14 and L15.
             */
            constexpr unsigned int L14_L15 = 40;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L14 and L16.
             */
            constexpr unsigned int L14_L16 = 41;

            /**
             * \brief Specifies the rule cleaving the bond between atom class L15 and L16.
             */
            constexpr unsigned int L15_L16 = 42;
        } // namespace BRICSRuleID
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BRICSRULEID_HPP
