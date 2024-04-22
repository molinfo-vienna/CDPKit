/* 
 * ResidueType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Biomol::ResidueType.
 */

#ifndef CDPL_BIOMOL_RESIDUETYPE_HPP
#define CDPL_BIOMOL_RESIDUETYPE_HPP


namespace CDPL
{

    namespace Biomol
    {

        namespace ResidueType
        {

            constexpr unsigned int UNKNOWN                  = 0;
            constexpr unsigned int OTHER                    = 1;
            constexpr unsigned int NON_POLYMER              = 2;
            constexpr unsigned int PEPTIDE_CARBOXY_TERMINUS = 3;
            constexpr unsigned int PEPTIDE_AMINO_TERMINUS   = 4;
            constexpr unsigned int PEPTIDE_LINKING          = 5;
            constexpr unsigned int BETA_PEPTIDE_LINKING     = 6;
            constexpr unsigned int GAMMA_PEPTIDE_LINKING    = 7;
            constexpr unsigned int PEPTIDE_LIKE             = 8;
            constexpr unsigned int RNA_HYDROXY_TERMINUS     = 9;
            constexpr unsigned int DNA_HYDROXY_TERMINUS     = 10;
            constexpr unsigned int RNA_LINKING              = 11;
            constexpr unsigned int DNA_LINKING              = 12;
            constexpr unsigned int SACCHARIDE_LINKING       = 13;
            constexpr unsigned int SACCHARIDE               = 14;
        } // namespace ResidueType
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_RESIDUETYPE_HPP
