/* 
 * SybylAtomType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::SybylAtomType.
 */

#ifndef CDPL_CHEM_SYBYLATOMTYPE_HPP
#define CDPL_CHEM_SYBYLATOMTYPE_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants for the specification of the <em>Tripos Sybyl</em> atom type.
         */
        namespace SybylAtomType
        {

            /**
             * \brief Atom with no matching \e Sybyl atom type.
             */
            constexpr unsigned int UNKNOWN = 0;

            /**
             * \brief Specifies sp3 carbon.
             */
            constexpr unsigned int C_3 = 1;

            /**
             * \brief Specifies sp2 carbon.
             */
            constexpr unsigned int C_2 = 2;

            /**
             * \brief Specifies sp carbon.
             */
            constexpr unsigned int C_1 = 3;

            /**
             * \brief Specifies an aromatic carbon.
             */
            constexpr unsigned int C_ar = 4;

            /**
             * \brief Specifies a carbocation (C+), used only in a guanidinium group.
             */
            constexpr unsigned int C_cat = 5;

            /**
             * \brief Specifies sp3 nitrogen.
             */
            constexpr unsigned int N_3 = 6;

            /**
             * \brief Specifies sp2 nitrogen.
             */
            constexpr unsigned int N_2 = 7;

            /**
             * \brief Specifies sp nitrogen.
             */
            constexpr unsigned int N_1 = 8;

            /**
             * \brief Specifies an aromatic nitrogen.
             */
            constexpr unsigned int N_ar = 9;

            /**
             * \brief Specifies nitrogen in amides.
             */
            constexpr unsigned int N_am = 10;

            /**
             * \brief Specifies a trigonal planar nitrogen.
             */
            constexpr unsigned int N_pl3 = 11;

            /**
             * \brief Specifies a positively charged sp3 nitrogen.
             */
            constexpr unsigned int N_4 = 12;

            /**
             * \brief Specifies sp3 oxygen.
             */
            constexpr unsigned int O_3 = 13;

            /**
             * \brief Specifies sp2 oxygen.
             */
            constexpr unsigned int O_2 = 14;

            /**
             * \brief Specifies oxygen in carboxylate and phosphate groups.
             */
            constexpr unsigned int O_co2 = 15;

            /**
             * \brief Specifies oxygen in the <em>Single Point Charge (SPC)</em> water model.
             */
            constexpr unsigned int O_spc = 16;

            /**
             * \brief Specifies oxygen in the <em>Transferable Intermolecular Potential (TIP3P)</em> water model.
             */
            constexpr unsigned int O_t3p = 17;

            /**
             * \brief Specifies sp3 sulfur.
             */
            constexpr unsigned int S_3 = 18;

            /**
             * \brief Specifies sp2 sulfur.
             */
            constexpr unsigned int S_2 = 19;

            /**
             * \brief Specifies sulfur in sulfoxides.
             */
            constexpr unsigned int S_O = 20;

            /**
             * \brief Specifies sulfur in sulfones.
             */
            constexpr unsigned int S_O2 = 21;

            /**
             * \brief Specifies sp3 phosphorous.
             */
            constexpr unsigned int P_3 = 22;

            /**
             * \brief Specifies fluorine.
             */
            constexpr unsigned int F = 23;

            /**
             * \brief Specifies hydrogen.
             */
            constexpr unsigned int H = 24;

            /**
             * \brief Specifies hydrogen in the <em>Single Point Charge (SPC)</em> water model.
             */
            constexpr unsigned int H_spc = 25;

            /**
             * \brief Specifies hydrogen in the <em>Transferable intermolecular Potential (TIP3P)</em> water model.
             */
            constexpr unsigned int H_t3p = 26;

            /**
             * \brief Specifies a lone pair.
             */
            constexpr unsigned int LP = 27;

            /**
             * \brief Specifies a dummy atom.
             */
            constexpr unsigned int Du = 28;

            /**
             * \brief Specifies a dummy carbon.
             */
            constexpr unsigned int Du_C = 29;

            /**
             * \brief Specifies any atom.
             */
            constexpr unsigned int Any = 30;

            /**
             * \brief Specifies any halogen.
             */
            constexpr unsigned int Hal = 31;

            /**
             * \brief Specifies a heteroatom (N, O, S or P).
             */
            constexpr unsigned int Het = 32;

            /**
             * \brief Specifies any heavy atom (non-Hydrogen).
             */
            constexpr unsigned int Hev = 33;

            /**
             * \brief Specifies lithium.
             */
            constexpr unsigned int Li = 34;

            /**
             * \brief Specifies sodium.
             */
            constexpr unsigned int Na = 35;

            /**
             * \brief Specifies magnesium.
             */
            constexpr unsigned int Mg = 36;

            /**
             * \brief Specifies aluminum.
             */
            constexpr unsigned int Al = 37;

            /**
             * \brief Specifies silicon.
             */
            constexpr unsigned int Si = 38;

            /**
             * \brief Specifies potassium.
             */
            constexpr unsigned int K = 39;

            /**
             * \brief Specifies calcium.
             */
            constexpr unsigned int Ca = 40;

            /**
             * \brief Specifies chromium (tetrahedral).
             */
            constexpr unsigned int Cr_th = 41;

            /**
             * \brief Specifies chromium (octahedral).
             */
            constexpr unsigned int Cr_oh = 42;

            /**
             * \brief Specifies manganese.
             */
            constexpr unsigned int Mn = 43;

            /**
             * \brief Specifies iron.
             */
            constexpr unsigned int Fe = 44;

            /**
             * \brief Specifies cobalt (octahedral).
             */
            constexpr unsigned int Co_oh = 45;

            /**
             * \brief Specifies copper.
             */
            constexpr unsigned int Cu = 46;

            /**
             * \brief Specifies chlorine.
             */
            constexpr unsigned int Cl = 47;

            /**
             * \brief Specifies bromine.
             */
            constexpr unsigned int Br = 48;

            /**
             * \brief Specifies iodine.
             */
            constexpr unsigned int I = 49;

            /**
             * \brief Specifies zinc.
             */
            constexpr unsigned int Zn = 50;

            /**
             * \brief Specifies selenium.
             */
            constexpr unsigned int Se = 51;

            /**
             * \brief Specifies molybdenum.
             */
            constexpr unsigned int Mo = 52;

            /**
             * \brief Specifies tin.
             */
            constexpr unsigned int Sn = 53;

            /**
             * \brief Marks the end of the default Sybyl atom types.
             */
            constexpr unsigned int MAX_DEFAULT_TYPE = Sn;

            /**
             * \brief Specifies boron.
             */
            constexpr unsigned int B = 54;

            /**
             * \brief Specifies platinum.
             */
            constexpr unsigned int Pt = 55;

            /**
             * \brief Marks the end of all supported atom types.
             */
            constexpr unsigned int MAX_TYPE = Pt;
        } // namespace SybylAtomType
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SYBYLATOMTYPE_HPP
