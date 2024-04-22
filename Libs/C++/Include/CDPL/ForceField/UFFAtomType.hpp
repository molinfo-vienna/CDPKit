/* 
 * UFFAtomType.hpp 
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
 * \brief Definition of constants in namespace CDPL::ForceField::UFFAtomType.
 */

#ifndef CDPL_FORCEFIELD_UFFATOMTYPE_HPP
#define CDPL_FORCEFIELD_UFFATOMTYPE_HPP


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Provides constants for the specification of <em>Universal Force Field (UFF)</em> atom types.
         * \see [\ref UFF]
         */
        namespace UFFAtomType
        {

            /**
             * \brief Atom with no matching UFF atom type.
             */
            constexpr unsigned int NONE = 0;

            constexpr unsigned int H = 1;

            /**
             * \brief Hydrogen bridging between two boron atoms.
             */
            constexpr unsigned int H_b = 2;

            constexpr unsigned int He_4_4 = 3;

            constexpr unsigned int Li = 4;

            constexpr unsigned int Be_3_2 = 5;

            constexpr unsigned int B_3 = 6;

            constexpr unsigned int B_2 = 7;

            constexpr unsigned int C_3 = 8;

            constexpr unsigned int C_R = 9;

            constexpr unsigned int C_2 = 10;

            constexpr unsigned int C_1 = 11;

            constexpr unsigned int N_3 = 12;

            constexpr unsigned int N_R = 13;

            constexpr unsigned int N_2 = 14;

            constexpr unsigned int N_1 = 15;

            constexpr unsigned int O_3 = 16;

            /**
             * \brief Oxygen in a zeolite framework.
             */
            constexpr unsigned int O_3_z = 17;

            constexpr unsigned int O_R = 18;

            constexpr unsigned int O_2 = 19;

            constexpr unsigned int O_1 = 20;

            constexpr unsigned int F = 21;

            constexpr unsigned int Ne_4_4 = 22;

            constexpr unsigned int Na = 23;

            constexpr unsigned int Mg_3_2 = 24;

            constexpr unsigned int Al_3 = 25;

            constexpr unsigned int Si_3 = 26;

            constexpr unsigned int P_3_3 = 27;

            constexpr unsigned int P_3_5 = 28;

            constexpr unsigned int P_3_q = 29;

            constexpr unsigned int S_3_2 = 30;

            constexpr unsigned int S_3_4 = 31;

            constexpr unsigned int S_3_6 = 32;

            constexpr unsigned int S_R = 33;

            constexpr unsigned int S_2 = 34;

            constexpr unsigned int Cl = 35;

            constexpr unsigned int Ar_4_4 = 36;

            constexpr unsigned int K = 37;

            constexpr unsigned int Ca_6_2 = 38;

            constexpr unsigned int Sc_3_3 = 39;

            constexpr unsigned int Ti_3_4 = 40;

            constexpr unsigned int Ti_6_4 = 41;

            constexpr unsigned int V_3_5 = 42;

            constexpr unsigned int Cr_6_3 = 43;

            constexpr unsigned int Mn_6_2 = 44;

            constexpr unsigned int Fe_3_2 = 45;

            constexpr unsigned int Fe_6_2 = 46;

            constexpr unsigned int Co_6_3 = 47;

            constexpr unsigned int Ni_4_2 = 48;

            constexpr unsigned int Cu_3_1 = 49;

            constexpr unsigned int Zn_3_2 = 50;

            constexpr unsigned int Ga_3_3 = 51;

            constexpr unsigned int Ge_3 = 52;

            constexpr unsigned int As_3_3 = 53;

            constexpr unsigned int Se_3_2 = 54;

            constexpr unsigned int Br = 55;

            constexpr unsigned int Kr_4_4 = 56;

            constexpr unsigned int Rb = 57;

            constexpr unsigned int Sr_6_2 = 58;

            constexpr unsigned int Y_3_3 = 59;

            constexpr unsigned int Zr_3_4 = 60;

            constexpr unsigned int Nb_3_5 = 61;

            constexpr unsigned int Mo_6_6 = 62;

            constexpr unsigned int Mo_3_6 = 63;

            constexpr unsigned int Tc_6_5 = 64;

            constexpr unsigned int Ru_6_2 = 65;

            constexpr unsigned int Rh_6_3 = 66;

            constexpr unsigned int Pd_4_2 = 67;

            constexpr unsigned int Ag_1_1 = 68;

            constexpr unsigned int Cd_3_2 = 69;

            constexpr unsigned int In_3_3 = 70;

            constexpr unsigned int Sn_3 = 71;

            constexpr unsigned int Sb_3_3 = 72;

            constexpr unsigned int Te_3_2 = 73;

            constexpr unsigned int I = 74;

            constexpr unsigned int Xe_4_4 = 75;

            constexpr unsigned int Cs = 76;

            constexpr unsigned int Ba_6_2 = 77;

            constexpr unsigned int La_3_3 = 78;

            constexpr unsigned int Ce_6_3 = 79;

            constexpr unsigned int Pr_6_3 = 80;

            constexpr unsigned int Nd_6_3 = 81;

            constexpr unsigned int Pm_6_3 = 82;

            constexpr unsigned int Sm_6_3 = 83;

            constexpr unsigned int Eu_6_3 = 84;

            constexpr unsigned int Gd_6_3 = 85;

            constexpr unsigned int Tb_6_3 = 86;

            constexpr unsigned int Dy_6_3 = 87;

            constexpr unsigned int Ho_6_3 = 88;

            constexpr unsigned int Er_6_3 = 89;

            constexpr unsigned int Tm_6_3 = 90;

            constexpr unsigned int Yb_6_3 = 91;

            constexpr unsigned int Lu_6_3 = 92;

            constexpr unsigned int Hf_3_4 = 93;

            constexpr unsigned int Ta_3_5 = 94;

            constexpr unsigned int W_6_6 = 95;

            constexpr unsigned int W_3_4 = 96;

            constexpr unsigned int W_3_6 = 97;

            constexpr unsigned int Re_6_5 = 98;

            constexpr unsigned int Re_3_7 = 99;

            constexpr unsigned int Os_6_6 = 100;

            constexpr unsigned int Ir_6_3 = 101;

            constexpr unsigned int Pt_4_2 = 102;

            constexpr unsigned int Au_4_3 = 103;

            constexpr unsigned int Hg_1_2 = 104;

            constexpr unsigned int Tl_3_3 = 105;

            constexpr unsigned int Pb_3 = 106;

            constexpr unsigned int Bi_3_3 = 107;

            constexpr unsigned int Po_3_2 = 108;

            constexpr unsigned int At = 109;

            constexpr unsigned int Rn_4_4 = 110;

            constexpr unsigned int Fr = 111;

            constexpr unsigned int Ra_6_2 = 112;

            constexpr unsigned int Ac_6_3 = 113;

            constexpr unsigned int Th_6_4 = 114;

            constexpr unsigned int Pa_6_4 = 115;

            constexpr unsigned int U_6_4 = 116;

            constexpr unsigned int Np_6_4 = 117;

            constexpr unsigned int Pu_6_4 = 118;

            constexpr unsigned int Am_6_4 = 119;

            constexpr unsigned int Cm_6_3 = 120;

            constexpr unsigned int Bk_6_3 = 121;

            constexpr unsigned int Cf_6_3 = 122;

            constexpr unsigned int Es_6_3 = 123;

            constexpr unsigned int Fm_6_3 = 124;

            constexpr unsigned int Md_6_3 = 125;

            constexpr unsigned int No_6_3 = 126;

            constexpr unsigned int Lr_6_3 = 127;

            constexpr unsigned int MAX_TYPE = Lr_6_3;
        } // namespace UFFAtomType
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_UFFATOMTYPE_HPP
