/* 
 * TautomerizationType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::TautomerizationType.
 */

#ifndef CDPL_CHEM_TAUTOMERIZATIONTYPE_HPP
#define CDPL_CHEM_TAUTOMERIZATIONTYPE_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants serving as identifiers for built-in Chem::TautomerizationRule implementations.
         */
        namespace TautomerizationType
        {

            constexpr unsigned int KETO_ENOL             = 0;
            constexpr unsigned int IMINE_ENAMINE         = 1;
            constexpr unsigned int NITROSO_OXIME         = 2;
            constexpr unsigned int AMIDE_IMIDIC_ACID     = 3;
            constexpr unsigned int LACTAM_LACTIM         = 4;
            constexpr unsigned int KETENE_YNOL           = 5;
            constexpr unsigned int NITRO_ACI             = 6;
            constexpr unsigned int PHOSPHINIC_ACID       = 7;
            constexpr unsigned int SULFENIC_ACID         = 8;
            constexpr unsigned int GENERIC_H_13_SHIFT    = 9;
            constexpr unsigned int GENERIC_H_15_SHIFT    = 10;

            /**
             * \since 1.3
             */
            constexpr unsigned int CONJ_RING_BOND_SWITCH = 11;

        } // namespace TautomerizationType
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_TAUTOMERIZATIONTYPE_HPP
