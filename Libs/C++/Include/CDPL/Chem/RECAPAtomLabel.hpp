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
         * \brief Provides constants for the labeling of atoms in bonds matched by a RECAP fragmentation rule.
         * \see [\ref RECAP]
         */
        namespace RECAPAtomLabel
        {

            constexpr unsigned int NONE                     = 0;
            constexpr unsigned int AMIDE_N                  = 1;
            constexpr unsigned int AMIDE_C                  = 2;
            constexpr unsigned int ESTER_O                  = 3;
            constexpr unsigned int ESTER_C                  = 4;
            constexpr unsigned int AMINE_N                  = 5;
            constexpr unsigned int AMINE_C                  = 6;
            constexpr unsigned int UREA_N                   = 7;
            constexpr unsigned int UREA_C                   = 8;
            constexpr unsigned int ETHER_O                  = 9;
            constexpr unsigned int ETHER_C                  = 10;
            constexpr unsigned int OLEFIN_C                 = 11;
            constexpr unsigned int QUARTERNARY_N_N          = 12;
            constexpr unsigned int QUARTERNARY_N_C          = 13;
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C_N = 14;
            constexpr unsigned int AROMATIC_N_ALIPHATIC_C_C = 15;
            constexpr unsigned int LACTAM_N_ALIPHATIC_C_N   = 16;
            constexpr unsigned int LACTAM_N_ALIPHATIC_C_C   = 17;
            constexpr unsigned int AROMATIC_C_AROMATIC_C_C  = 18;
            constexpr unsigned int SULFONAMIDE_N            = 19;
            constexpr unsigned int SULFONAMIDE_S            = 20;
        } // namespace RECAPAtomLabel
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RECAPATOMLABEL_HPP
