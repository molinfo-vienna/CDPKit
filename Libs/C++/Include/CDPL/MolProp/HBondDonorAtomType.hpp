/* 
 * HBondDonorAtomType.hpp 
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
 * \brief Definition of constants in namespace CDPL::MolProp::HBondDonorAtomType.
 */

#ifndef CDPL_MOLPROP_HBONDDONORATOMTYPE_HPP
#define CDPL_MOLPROP_HBONDDONORATOMTYPE_HPP


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Provides constants used to specify the structural class of H-bond donor atoms.
         */
        namespace HBondDonorAtomType
        {

            /**
             * \brief Specifies that the H-bond donor type of the atom is undefined.
             */
            constexpr unsigned int UNDEF = 0;

            /**
             * \brief Specifies that the atom is not a H-bond donor.
             */
            constexpr unsigned int NONE = 1;

            /** \brief Iodine donor of hydrogen iodide. */
            constexpr unsigned int I_HI = 2;

            /** \brief Bromine donor of hydrogen bromide. */
            constexpr unsigned int BR_HBR = 3;

            /** \brief Chlorine donor of hydrogen chloride. */
            constexpr unsigned int CL_HCL = 4;

            /** \brief Sulfur donor of thiocyanic acid. */
            constexpr unsigned int S_HSCN = 5;

            /** \brief Fluorine donor of hydrogen fluoride. */
            constexpr unsigned int F_HF = 6;

            /** \brief Hydrogen donor of molecular hydrogen. */
            constexpr unsigned int H_H2 = 7;

            /** \brief Carbon donor of hydrogen cyanide. */
            constexpr unsigned int C_HCN = 8;

            /** \brief Carbon donor of terminal-alkyne hydrogen. */
            constexpr unsigned int C_ETHINE = 9;

            /** \brief Nitrogen donor of hydrazoic acid (HN3). */
            constexpr unsigned int N_HN3 = 10;

            /** \brief Nitrogen donor of ammonia. */
            constexpr unsigned int N_NH3 = 11;

            /** \brief Nitrogen donor of ammonium. */
            constexpr unsigned int N_NH4 = 12;

            /** \brief Aliphatic amine nitrogen donor. */
            constexpr unsigned int N_AMINE = 13;

            /** \brief Aliphatic aminium nitrogen donor. */
            constexpr unsigned int N_AMINIUM = 14;

            /** \brief Aniline nitrogen donor. */
            constexpr unsigned int N_ANILINE = 15;

            /** \brief Mono-/di-nitro-aniline nitrogen donor. */
            constexpr unsigned int N_MONO_DI_NITRO_ANILINE = 16;

            /** \brief Tri-nitro-aniline nitrogen donor. */
            constexpr unsigned int N_TRI_NITRO_ANILINE = 17;

            /** \brief Pyrrole-like aromatic nitrogen donor. */
            constexpr unsigned int N_PYRROLE = 18;

            /** \brief Amide nitrogen donor. */
            constexpr unsigned int N_AMIDE = 19;

            /** \brief Imine nitrogen donor. */
            constexpr unsigned int N_IMINE = 20;

            /** \brief Iminium nitrogen donor. */
            constexpr unsigned int N_IMINIUM = 21;

            /** \brief Sulfur donor of hydrogen sulfide. */
            constexpr unsigned int S_H2S = 22;

            /** \brief Sulfur donor of bisulfide. */
            constexpr unsigned int S_HS = 23;

            /** \brief Thiol sulfur donor. */
            constexpr unsigned int S_THIOL = 24;

            /** \brief Oxygen donor of phosphoric acid (H3PO4). */
            constexpr unsigned int O_H3PO4 = 25;

            /** \brief Oxygen donor of carbonic acid (H2CO3). */
            constexpr unsigned int O_H2CO3 = 26;

            /** \brief Oxygen donor of bicarbonate (HCO3-). */
            constexpr unsigned int O_HCO3 = 27;

            /** \brief Oxygen donor of hydrogen peroxide (H2O2). */
            constexpr unsigned int O_H2O2 = 28;

            /** \brief Oxygen donor of water. */
            constexpr unsigned int O_H2O = 29;

            /** \brief Oxygen donor of triflic acid (CF3SO3H). */
            constexpr unsigned int O_CF3SO3H = 30;

            /** \brief Oxygen donor of perchloric acid (HClO4). */
            constexpr unsigned int O_HCLO4 = 31;

            /** \brief Oxygen donor of sulfuric acid (H2SO4). */
            constexpr unsigned int O_H2SO4 = 32;

            /** \brief Oxygen donor of nitric acid (HNO3). */
            constexpr unsigned int O_HNO3 = 33;

            /** \brief Oxygen donor of hydrogen sulfate (HSO4-). */
            constexpr unsigned int O_HSO4 = 34;

            /** \brief Oxygen donor of nitrous acid (HNO2). */
            constexpr unsigned int O_HNO2 = 35;

            /** \brief Oxygen donor of hydroxylamine (NH2OH). */
            constexpr unsigned int O_NH2OH = 36;

            /** \brief Oxygen donor of dihydrogen phosphate (H2PO4-). */
            constexpr unsigned int O_H2PO4 = 37;

            /** \brief Oxygen donor of boric acid (H3BO3). */
            constexpr unsigned int O_H3BO3 = 38;

            /** \brief Oxygen donor of silicic acid (H4SiO4). */
            constexpr unsigned int O_H4SIO4 = 39;

            /** \brief Oxygen donor of hydrogen phosphate (HPO4(2-)). */
            constexpr unsigned int O_HPO4 = 40;

            /** \brief Oxygen donor of dihydrogen borate (H2BO3-). */
            constexpr unsigned int O_H2BO3 = 41;

            /** \brief Oxygen donor of hydroxide (HO-). */
            constexpr unsigned int O_HO = 42;

            /** \brief Sulfonic-acid oxygen donor. */
            constexpr unsigned int O_SULFONIC_ACID = 43;

            /** \brief Mono-/di-nitro-phenol oxygen donor. */
            constexpr unsigned int O_MONO_DI_NITRO_PHENOL = 44;

            /** \brief Halogeno-alcohol oxygen donor. */
            constexpr unsigned int O_HALOGENO_ALCOHOL = 45;

            /** \brief Alcohol oxygen donor. */
            constexpr unsigned int O_ALCOHOL = 46;

            /** \brief Tri-nitro-phenol oxygen donor. */
            constexpr unsigned int O_TRI_NITRO_PHENOL = 47;

            /** \brief Halogeno-phenol oxygen donor. */
            constexpr unsigned int O_HALOGENO_PHENOL = 48;

            /** \brief Phenol oxygen donor. */
            constexpr unsigned int O_PHENOL = 49;

            /** \brief Carboxylic-acid oxygen donor. */
            constexpr unsigned int O_CARBOXYLIC_ACID = 50;

            /** \brief Halogeno-carboxylic-acid oxygen donor. */
            constexpr unsigned int O_HALOGENO_CARBOXYCLIC_ACID = 51;

            /** \brief Enol oxygen donor. */
            constexpr unsigned int O_ENOL = 52;

            /** \brief Oxime oxygen donor. */
            constexpr unsigned int O_OXIME = 53;

            /** \brief Pentachloro-phenol oxygen donor. */
            constexpr unsigned int O_CL5_PHENOL = 54;

            /** \brief Highest H-bond donor type constant defined in this namespace. */
            constexpr unsigned int MAX_TYPE = O_CL5_PHENOL;

        } // namespace HBondDonorAtomType
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_HBONDDONORATOMTYPE_HPP
