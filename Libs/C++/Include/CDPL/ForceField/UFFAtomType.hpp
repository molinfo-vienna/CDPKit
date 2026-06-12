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
         * \brief Provides constants for the specification of numeric <em>Universal Force Field (UFF)</em> atom types.
         * \see [\ref UFF]
         */
        namespace UFFAtomType
        {

            /**
             * \brief Atom with no matching UFF type.
             */
            constexpr unsigned int NONE = 0;

            /** \brief Hydrogen. */
            constexpr unsigned int H = 1;

            /** \brief Hydrogen (bridging boron atoms). */
            constexpr unsigned int H_b = 2;

            /** \brief Helium. */
            constexpr unsigned int He_4_4 = 3;

            /** \brief Lithium. */
            constexpr unsigned int Li = 4;

            /** \brief Beryllium. */
            constexpr unsigned int Be_3_2 = 5;

            /** \brief Boron (sp3). */
            constexpr unsigned int B_3 = 6;

            /** \brief Boron (sp2). */
            constexpr unsigned int B_2 = 7;

            /** \brief Carbon (sp3). */
            constexpr unsigned int C_3 = 8;

            /** \brief Carbon (aromatic/resonant). */
            constexpr unsigned int C_R = 9;

            /** \brief Carbon (sp2). */
            constexpr unsigned int C_2 = 10;

            /** \brief Carbon (sp). */
            constexpr unsigned int C_1 = 11;

            /** \brief Nitrogen (sp3). */
            constexpr unsigned int N_3 = 12;

            /** \brief Nitrogen (aromatic/resonant). */
            constexpr unsigned int N_R = 13;

            /** \brief Nitrogen (sp2). */
            constexpr unsigned int N_2 = 14;

            /** \brief Nitrogen (sp). */
            constexpr unsigned int N_1 = 15;

            /** \brief Oxygen (sp3). */
            constexpr unsigned int O_3 = 16;

            /** \brief Oxygen (sp3, in zeolite framework). */
            constexpr unsigned int O_3_z = 17;

            /** \brief Oxygen (aromatic/resonant). */
            constexpr unsigned int O_R = 18;

            /** \brief Oxygen (sp2). */
            constexpr unsigned int O_2 = 19;

            /** \brief Oxygen (sp). */
            constexpr unsigned int O_1 = 20;

            /** \brief Fluorine. */
            constexpr unsigned int F = 21;

            /** \brief Neon. */
            constexpr unsigned int Ne_4_4 = 22;

            /** \brief Sodium. */
            constexpr unsigned int Na = 23;

            /** \brief Magnesium. */
            constexpr unsigned int Mg_3_2 = 24;

            /** \brief Aluminum. */
            constexpr unsigned int Al_3 = 25;

            /** \brief Silicon. */
            constexpr unsigned int Si_3 = 26;

            /** \brief Phosphorus (sp3, trivalent). */
            constexpr unsigned int P_3_3 = 27;

            /** \brief Phosphorus (sp3, pentavalent). */
            constexpr unsigned int P_3_5 = 28;

            /** \brief Phosphorus (sp3, in organometallic complexes). */
            constexpr unsigned int P_3_q = 29;

            /** \brief Sulfur (sp3, bivalent). */
            constexpr unsigned int S_3_2 = 30;

            /** \brief Sulfur (sp3, tetravalent). */
            constexpr unsigned int S_3_4 = 31;

            /** \brief Sulfur (sp3, hexavalent). */
            constexpr unsigned int S_3_6 = 32;

            /** \brief Sulfur (aromatic/resonant). */
            constexpr unsigned int S_R = 33;

            /** \brief Sulfur (sp2). */
            constexpr unsigned int S_2 = 34;

            /** \brief Chlorine. */
            constexpr unsigned int Cl = 35;

            /** \brief Argon. */
            constexpr unsigned int Ar_4_4 = 36;

            /** \brief Potassium. */
            constexpr unsigned int K = 37;

            /** \brief Calcium. */
            constexpr unsigned int Ca_6_2 = 38;

            /** \brief Scandium. */
            constexpr unsigned int Sc_3_3 = 39;

            /** \brief Titanium (tetrahedral). */
            constexpr unsigned int Ti_3_4 = 40;

            /** \brief Titanium (octahedral). */
            constexpr unsigned int Ti_6_4 = 41;

            /** \brief Vanadium. */
            constexpr unsigned int V_3_5 = 42;

            /** \brief Chromium. */
            constexpr unsigned int Cr_6_3 = 43;

            /** \brief Manganese. */
            constexpr unsigned int Mn_6_2 = 44;

            /** \brief Iron (tetrahedral). */
            constexpr unsigned int Fe_3_2 = 45;

            /** \brief Iron (octahedral). */
            constexpr unsigned int Fe_6_2 = 46;

            /** \brief Cobalt. */
            constexpr unsigned int Co_6_3 = 47;

            /** \brief Nickel. */
            constexpr unsigned int Ni_4_2 = 48;

            /** \brief Copper. */
            constexpr unsigned int Cu_3_1 = 49;

            /** \brief Zinc. */
            constexpr unsigned int Zn_3_2 = 50;

            /** \brief Gallium. */
            constexpr unsigned int Ga_3_3 = 51;

            /** \brief Germanium. */
            constexpr unsigned int Ge_3 = 52;

            /** \brief Arsenic. */
            constexpr unsigned int As_3_3 = 53;

            /** \brief Selenium. */
            constexpr unsigned int Se_3_2 = 54;

            /** \brief Bromine. */
            constexpr unsigned int Br = 55;

            /** \brief Krypton. */
            constexpr unsigned int Kr_4_4 = 56;

            /** \brief Rubidium. */
            constexpr unsigned int Rb = 57;

            /** \brief Strontium. */
            constexpr unsigned int Sr_6_2 = 58;

            /** \brief Yttrium. */
            constexpr unsigned int Y_3_3 = 59;

            /** \brief Zirconium. */
            constexpr unsigned int Zr_3_4 = 60;

            /** \brief Niobium. */
            constexpr unsigned int Nb_3_5 = 61;

            /** \brief Molybdenum (octahedral). */
            constexpr unsigned int Mo_6_6 = 62;

            /** \brief Molybdenum (tetrahedral). */
            constexpr unsigned int Mo_3_6 = 63;

            /** \brief Technetium. */
            constexpr unsigned int Tc_6_5 = 64;

            /** \brief Ruthenium. */
            constexpr unsigned int Ru_6_2 = 65;

            /** \brief Rhodium. */
            constexpr unsigned int Rh_6_3 = 66;

            /** \brief Palladium. */
            constexpr unsigned int Pd_4_2 = 67;

            /** \brief Silver. */
            constexpr unsigned int Ag_1_1 = 68;

            /** \brief Cadmium. */
            constexpr unsigned int Cd_3_2 = 69;

            /** \brief Indium. */
            constexpr unsigned int In_3_3 = 70;

            /** \brief Tin. */
            constexpr unsigned int Sn_3 = 71;

            /** \brief Antimony. */
            constexpr unsigned int Sb_3_3 = 72;

            /** \brief Tellurium. */
            constexpr unsigned int Te_3_2 = 73;

            /** \brief Iodine. */
            constexpr unsigned int I = 74;

            /** \brief Xenon. */
            constexpr unsigned int Xe_4_4 = 75;

            /** \brief Caesium. */
            constexpr unsigned int Cs = 76;

            /** \brief Barium. */
            constexpr unsigned int Ba_6_2 = 77;

            /** \brief Lanthanum. */
            constexpr unsigned int La_3_3 = 78;

            /** \brief Cerium. */
            constexpr unsigned int Ce_6_3 = 79;

            /** \brief Praseodymium. */
            constexpr unsigned int Pr_6_3 = 80;

            /** \brief Neodymium. */
            constexpr unsigned int Nd_6_3 = 81;

            /** \brief Promethium. */
            constexpr unsigned int Pm_6_3 = 82;

            /** \brief Samarium. */
            constexpr unsigned int Sm_6_3 = 83;

            /** \brief Europium. */
            constexpr unsigned int Eu_6_3 = 84;

            /** \brief Gadolinium. */
            constexpr unsigned int Gd_6_3 = 85;

            /** \brief Terbium. */
            constexpr unsigned int Tb_6_3 = 86;

            /** \brief Dysprosium. */
            constexpr unsigned int Dy_6_3 = 87;

            /** \brief Holmium. */
            constexpr unsigned int Ho_6_3 = 88;

            /** \brief Erbium. */
            constexpr unsigned int Er_6_3 = 89;

            /** \brief Thulium. */
            constexpr unsigned int Tm_6_3 = 90;

            /** \brief Ytterbium. */
            constexpr unsigned int Yb_6_3 = 91;

            /** \brief Lutetium. */
            constexpr unsigned int Lu_6_3 = 92;

            /** \brief Hafnium. */
            constexpr unsigned int Hf_3_4 = 93;

            /** \brief Tantalum. */
            constexpr unsigned int Ta_3_5 = 94;

            /** \brief Tungsten (octahedral). */
            constexpr unsigned int W_6_6 = 95;

            /** \brief Tungsten (tetrahedral). */
            constexpr unsigned int W_3_4 = 96;

            /** \brief Tungsten (tetrahedral, higher oxidation state). */
            constexpr unsigned int W_3_6 = 97;

            /** \brief Rhenium (octahedral). */
            constexpr unsigned int Re_6_5 = 98;

            /** \brief Rhenium (tetrahedral). */
            constexpr unsigned int Re_3_7 = 99;

            /** \brief Osmium. */
            constexpr unsigned int Os_6_6 = 100;

            /** \brief Iridium. */
            constexpr unsigned int Ir_6_3 = 101;

            /** \brief Platinum. */
            constexpr unsigned int Pt_4_2 = 102;

            /** \brief Gold. */
            constexpr unsigned int Au_4_3 = 103;

            /** \brief Mercury. */
            constexpr unsigned int Hg_1_2 = 104;

            /** \brief Thallium. */
            constexpr unsigned int Tl_3_3 = 105;

            /** \brief Lead. */
            constexpr unsigned int Pb_3 = 106;

            /** \brief Bismuth. */
            constexpr unsigned int Bi_3_3 = 107;

            /** \brief Polonium. */
            constexpr unsigned int Po_3_2 = 108;

            /** \brief Astatine. */
            constexpr unsigned int At = 109;

            /** \brief Radon. */
            constexpr unsigned int Rn_4_4 = 110;

            /** \brief Francium. */
            constexpr unsigned int Fr = 111;

            /** \brief Radium. */
            constexpr unsigned int Ra_6_2 = 112;

            /** \brief Actinium. */
            constexpr unsigned int Ac_6_3 = 113;

            /** \brief Thorium. */
            constexpr unsigned int Th_6_4 = 114;

            /** \brief Protactinium. */
            constexpr unsigned int Pa_6_4 = 115;

            /** \brief Uranium. */
            constexpr unsigned int U_6_4 = 116;

            /** \brief Neptunium. */
            constexpr unsigned int Np_6_4 = 117;

            /** \brief Plutonium. */
            constexpr unsigned int Pu_6_4 = 118;

            /** \brief Americium. */
            constexpr unsigned int Am_6_4 = 119;

            /** \brief Curium. */
            constexpr unsigned int Cm_6_3 = 120;

            /** \brief Berkelium. */
            constexpr unsigned int Bk_6_3 = 121;

            /** \brief Californium. */
            constexpr unsigned int Cf_6_3 = 122;

            /** \brief Einsteinium. */
            constexpr unsigned int Es_6_3 = 123;

            /** \brief Fermium. */
            constexpr unsigned int Fm_6_3 = 124;

            /** \brief Mendelevium. */
            constexpr unsigned int Md_6_3 = 125;

            /** \brief Nobelium. */
            constexpr unsigned int No_6_3 = 126;

            /** \brief Lawrencium. */
            constexpr unsigned int Lr_6_3 = 127;

            /** \brief The highest UFF atom type value. */
            constexpr unsigned int MAX_TYPE = Lr_6_3;
        } // namespace UFFAtomType
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_UFFATOMTYPE_HPP
