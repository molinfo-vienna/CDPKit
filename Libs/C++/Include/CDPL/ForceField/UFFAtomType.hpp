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
			const unsigned int NONE     = 0;

			const unsigned int H        = 1;

			/**
			 * \brief Hydrogen bridging between two boron atoms.
			 */
			const unsigned int H_b      = 2;

			const unsigned int He_4_4   = 3;

			const unsigned int Li       = 4;

			const unsigned int Be_3_2   = 5;

			const unsigned int B_3      = 6;

			const unsigned int B_2      = 7;

			const unsigned int C_3      = 8;

			const unsigned int C_R      = 9;

			const unsigned int C_2      = 10;

			const unsigned int C_1      = 11;

			const unsigned int N_3      = 12;

			const unsigned int N_R      = 13;

			const unsigned int N_2      = 14;

			const unsigned int N_1      = 15;

			const unsigned int O_3      = 16;

			/**
			 * \brief Oxygen in a zeolite framework.
			 */
			const unsigned int O_3_z    = 17;

			const unsigned int O_R      = 18;

			const unsigned int O_2      = 19;

			const unsigned int O_1      = 20;

			const unsigned int F        = 21;

			const unsigned int Ne_4_4   = 22;
			
			const unsigned int Na       = 23;
			
			const unsigned int Mg_3_2   = 24;
			
			const unsigned int Al_3     = 25;
			
			const unsigned int Si_3     = 26;
			
			const unsigned int P_3_3    = 27;
			
			const unsigned int P_3_5    = 28;
			
			const unsigned int P_3_q    = 29;
			
			const unsigned int S_3_2    = 30;
			
			const unsigned int S_3_4    = 31;
			
			const unsigned int S_3_6    = 32;
			
			const unsigned int S_R      = 33;
			
			const unsigned int S_2      = 34;
			
			const unsigned int Cl       = 35;
			
			const unsigned int Ar_4_4   = 36;
			
			const unsigned int K        = 37;
			
			const unsigned int Ca_6_2   = 38;
			
			const unsigned int Sc_3_3   = 39;
			
			const unsigned int Ti_3_4   = 40;

			const unsigned int Ti_6_4   = 41;
			
			const unsigned int V_3_5    = 42;
			
			const unsigned int Cr_6_3   = 43;
			
			const unsigned int Mn_6_2   = 44;
			
			const unsigned int Fe_3_2   = 45;
			
			const unsigned int Fe_6_2   = 46;
			
			const unsigned int Co_6_3   = 47;
			
			const unsigned int Ni_4_2   = 48;
			
			const unsigned int Cu_3_1   = 49;
			
			const unsigned int Zn_3_2   = 50;
			
			const unsigned int Ga_3_3   = 51;
			
			const unsigned int Ge_3     = 52;
			
			const unsigned int As_3_3   = 53;
			
			const unsigned int Se_3_2   = 54;
			
			const unsigned int Br       = 55;
			
			const unsigned int Kr_4_4   = 56;
			
			const unsigned int Rb       = 57;
			
			const unsigned int Sr_6_2   = 58;
			
			const unsigned int Y_3_3    = 59;
			
			const unsigned int Zr_3_4   = 60;
			
			const unsigned int Nb_3_5   = 61;
			
			const unsigned int Mo_6_6   = 62;
			
			const unsigned int Mo_3_6   = 63;
			
			const unsigned int Tc_6_5   = 64;
			
			const unsigned int Ru_6_2   = 65;
			
			const unsigned int Rh_6_3   = 66;
			
			const unsigned int Pd_4_2   = 67;
			
			const unsigned int Ag_1_1   = 68;
			
			const unsigned int Cd_3_2   = 69;
			
			const unsigned int In_3_3   = 70;
			
			const unsigned int Sn_3     = 71;
			
			const unsigned int Sb_3_3   = 72;
			
			const unsigned int Te_3_2   = 73;
			
			const unsigned int I        = 74;
			
			const unsigned int Xe_4_4   = 75;
			
			const unsigned int Cs       = 76;
			
			const unsigned int Ba_6_2   = 77;
			
			const unsigned int La_3_3   = 78;
			
			const unsigned int Ce_6_3   = 79;
			
			const unsigned int Pr_6_3   = 80;
			
			const unsigned int Nd_6_3   = 81;
			
			const unsigned int Pm_6_3   = 82;
			
			const unsigned int Sm_6_3   = 83;
			
			const unsigned int Eu_6_3   = 84;
			
			const unsigned int Gd_6_3   = 85;
			
			const unsigned int Tb_6_3   = 86;
			
			const unsigned int Dy_6_3   = 87;
			
			const unsigned int Ho_6_3   = 88;
			
			const unsigned int Er_6_3   = 89;
			
			const unsigned int Tm_6_3   = 90;
			
			const unsigned int Yb_6_3   = 91;
			
			const unsigned int Lu_6_3   = 92;
			
			const unsigned int Hf_3_4   = 93;
			
			const unsigned int Ta_3_5   = 94;
			
			const unsigned int W_6_6    = 95;
			
			const unsigned int W_3_4    = 96;
			
			const unsigned int W_3_6    = 97;
			
			const unsigned int Re_6_5   = 98;
			
			const unsigned int Re_3_7   = 99;
			
			const unsigned int Os_6_6   = 100;
			
			const unsigned int Ir_6_3   = 101;
			
			const unsigned int Pt_4_2   = 102;
			
			const unsigned int Au_4_3   = 103;
			
			const unsigned int Hg_1_2   = 104;
			
			const unsigned int Tl_3_3   = 105;
			
			const unsigned int Pb_3     = 106;
			
			const unsigned int Bi_3_3   = 107;
			
			const unsigned int Po_3_2   = 108;
			
			const unsigned int At       = 109;
			
			const unsigned int Rn_4_4   = 110;
			
			const unsigned int Fr       = 111;
			
			const unsigned int Ra_6_2   = 112;
			
			const unsigned int Ac_6_3   = 113;
			
			const unsigned int Th_6_4   = 114;
			
			const unsigned int Pa_6_4   = 115;
			
			const unsigned int U_6_4    = 116;
			
			const unsigned int Np_6_4   = 117;
			
			const unsigned int Pu_6_4   = 118;
			
			const unsigned int Am_6_4   = 119;
			
			const unsigned int Cm_6_3   = 120;
			
			const unsigned int Bk_6_3   = 121;
			
			const unsigned int Cf_6_3   = 122;
			
			const unsigned int Es_6_3   = 123;
			
			const unsigned int Fm_6_3   = 124;
			
			const unsigned int Md_6_3   = 125;
			
			const unsigned int No_6_3   = 126;
			
			const unsigned int Lr_6_3   = 127;

			const unsigned int MAX_TYPE = Lr_6_3;
		}
    }
}

#endif // CDPL_FORCEFIELD_UFFATOMTYPE_HPP
