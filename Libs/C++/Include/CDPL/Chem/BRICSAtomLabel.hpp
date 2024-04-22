/* 
 * BRICSAtomLabel.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BRICSAtomLabel.
 */

#ifndef CDPL_CHEM_BRICSATOMLABEL_HPP
#define CDPL_CHEM_BRICSATOMLABEL_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
     * \brief Provides constants for the labeling of atoms in bonds matched by a BRICS fragmentation rule.
     * \see [\ref BRICS]
     */
        namespace BRICSAtomLabel
        {

            constexpr unsigned int NONE = 0;
            constexpr unsigned int L1   = 1;
            constexpr unsigned int L2   = 2;
            constexpr unsigned int L3   = 3;
            constexpr unsigned int L4   = 4;
            constexpr unsigned int L5   = 5;
            constexpr unsigned int L6   = 6;
            constexpr unsigned int L7   = 7;
            constexpr unsigned int L8   = 8;
            constexpr unsigned int L9   = 9;
            constexpr unsigned int L10  = 10;
            constexpr unsigned int L11  = 11;
            constexpr unsigned int L12  = 12;
            constexpr unsigned int L13  = 13;
            constexpr unsigned int L14  = 14;
            constexpr unsigned int L15  = 15;
            constexpr unsigned int L16  = 16;
        } // namespace BRICSAtomLabel
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BRICSATOMLABEL_HPP
