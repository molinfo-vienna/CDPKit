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
         * \brief Provides constants for the identification of BRICS fragmentation rules.
         * \see [\ref BRICS]
         */
        namespace BRICSRuleID
        {

            constexpr unsigned int NONE    = 0;
            constexpr unsigned int L1_L2   = 1;
            constexpr unsigned int L1_L3   = 2;
            constexpr unsigned int L1_L10  = 3;
            constexpr unsigned int L2_L12  = 4;
            constexpr unsigned int L2_L14  = 5;
            constexpr unsigned int L2_L16  = 6;
            constexpr unsigned int L3_L4   = 7;
            constexpr unsigned int L3_L13  = 8;
            constexpr unsigned int L3_L14  = 9;
            constexpr unsigned int L3_L15  = 10;
            constexpr unsigned int L3_L16  = 11;
            constexpr unsigned int L4_L5   = 12;
            constexpr unsigned int L4_L11  = 13;
            constexpr unsigned int L5_L13  = 14;
            constexpr unsigned int L5_L15  = 15;
            constexpr unsigned int L6_L13  = 16;
            constexpr unsigned int L6_L14  = 17;
            constexpr unsigned int L6_L15  = 18;
            constexpr unsigned int L6_L16  = 19;
            constexpr unsigned int L7_L7   = 20;
            constexpr unsigned int L8_L9   = 21;
            constexpr unsigned int L8_L10  = 22;
            constexpr unsigned int L8_L13  = 23;
            constexpr unsigned int L8_L14  = 24;
            constexpr unsigned int L8_L15  = 25;
            constexpr unsigned int L8_L16  = 26;
            constexpr unsigned int L9_L15  = 27;
            constexpr unsigned int L9_L16  = 28;
            constexpr unsigned int L10_L13 = 29;
            constexpr unsigned int L10_L14 = 30;
            constexpr unsigned int L10_L15 = 31;
            constexpr unsigned int L10_L16 = 32;
            constexpr unsigned int L11_L13 = 33;
            constexpr unsigned int L11_L14 = 34;
            constexpr unsigned int L11_L15 = 35;
            constexpr unsigned int L11_L16 = 36;
            constexpr unsigned int L13_L14 = 37;
            constexpr unsigned int L13_L15 = 38;
            constexpr unsigned int L13_L16 = 39;
            constexpr unsigned int L14_L15 = 40;
            constexpr unsigned int L14_L16 = 41;
            constexpr unsigned int L15_L16 = 42;
        } // namespace BRICSRuleID
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BRICSRULEID_HPP
