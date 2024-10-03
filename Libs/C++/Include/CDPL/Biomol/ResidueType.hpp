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

            constexpr unsigned int UNKNOWN                    = 0;
            constexpr unsigned int OTHER                      = 1;
            constexpr unsigned int NON_POLYMER                = 2;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_PEPTIDE_CARBOXY_TERMINUS = 3;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_PEPTIDE_AMINO_TERMINUS   = 4;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_PEPTIDE_AMINO_TERMINUS   = 5;
            
            constexpr unsigned int PEPTIDE_LINKING            = 6;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_PEPTIDE_LINKING          = 7;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_PEPTIDE_LINKING          = 8;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_BETA_PEPTIDE_LINKING     = 9;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_BETA_PEPTIDE_LINKING     = 10;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_GAMMA_PEPTIDE_LINKING    = 11;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_GAMMA_PEPTIDE_LINKING    = 12;
            
            constexpr unsigned int PEPTIDE_LIKE               = 13;

            /*
             * \since 1.2
             */
            constexpr unsigned int RNA_3_HYDROXY_TERMINUS     = 14;

            /*
             * \since 1.2
             */
            constexpr unsigned int RNA_5_HYDROXY_TERMINUS     = 15;

            /*
             * \since 1.2
             */
            constexpr unsigned int DNA_3_HYDROXY_TERMINUS     = 16;

            /*
             * \since 1.2
             */
            constexpr unsigned int DNA_5_HYDROXY_TERMINUS     = 17;

            constexpr unsigned int RNA_LINKING                = 18;
            constexpr unsigned int DNA_LINKING                = 19;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_RNA_LINKING              = 20;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_DNA_LINKING              = 21;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_SACCHARIDE_1_4_LINKING   = 22;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_SACCHARIDE_1_4_LINKING   = 23;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_SACCHARIDE_ALPHA_LINKING = 24;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_SACCHARIDE_ALPHA_LINKING = 25;

            /*
             * \since 1.2
             */
            constexpr unsigned int L_SACCHARIDE_BETA_LINKING  = 26;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_SACCHARIDE_BETA_LINKING  = 27;
            
            /*
             * \since 1.2
             */
            constexpr unsigned int L_SACCHARIDE               = 28;

            /*
             * \since 1.2
             */
            constexpr unsigned int D_SACCHARIDE               = 29;
            
            constexpr unsigned int SACCHARIDE                 = 30;

            /*
             * \since 1.2
             */
            constexpr unsigned int MAX_TYPE                   = SACCHARIDE;

        } // namespace ResidueType
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_RESIDUETYPE_HPP
