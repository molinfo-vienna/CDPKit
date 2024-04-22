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

            constexpr unsigned int I_HI = 2;

            constexpr unsigned int BR_HBR = 3;

            constexpr unsigned int CL_HCL = 4;

            constexpr unsigned int S_HSCN = 5;

            constexpr unsigned int F_HF = 6;

            constexpr unsigned int H_H2 = 7;

            constexpr unsigned int C_HCN = 8;

            constexpr unsigned int C_ETHINE = 9;

            constexpr unsigned int N_HN3 = 10;

            constexpr unsigned int N_NH3 = 11;

            constexpr unsigned int N_NH4 = 12;

            constexpr unsigned int N_AMINE = 13;

            constexpr unsigned int N_AMINIUM = 14;

            constexpr unsigned int N_ANILINE = 15;

            constexpr unsigned int N_MONO_DI_NITRO_ANILINE = 16;

            constexpr unsigned int N_TRI_NITRO_ANILINE = 17;

            constexpr unsigned int N_PYRROLE = 18;

            constexpr unsigned int N_AMIDE = 19;

            constexpr unsigned int N_IMINE = 20;

            constexpr unsigned int N_IMINIUM = 21;

            constexpr unsigned int S_H2S = 22;

            constexpr unsigned int S_HS = 23;

            constexpr unsigned int S_THIOL = 24;

            constexpr unsigned int O_H3PO4 = 25;

            constexpr unsigned int O_H2CO3 = 26;

            constexpr unsigned int O_HCO3 = 27;

            constexpr unsigned int O_H2O2 = 28;

            constexpr unsigned int O_H2O = 29;

            constexpr unsigned int O_CF3SO3H = 30;

            constexpr unsigned int O_HCLO4 = 31;

            constexpr unsigned int O_H2SO4 = 32;

            constexpr unsigned int O_HNO3 = 33;

            constexpr unsigned int O_HSO4 = 34;

            constexpr unsigned int O_HNO2 = 35;

            constexpr unsigned int O_NH2OH = 36;

            constexpr unsigned int O_H2PO4 = 37;

            constexpr unsigned int O_H3BO3 = 38;

            constexpr unsigned int O_H4SIO4 = 39;

            constexpr unsigned int O_HPO4 = 40;

            constexpr unsigned int O_H2BO3 = 41;

            constexpr unsigned int O_HO = 42;

            constexpr unsigned int O_SULFONIC_ACID = 43;

            constexpr unsigned int O_MONO_DI_NITRO_PHENOL = 44;

            constexpr unsigned int O_HALOGENO_ALCOHOL = 45;

            constexpr unsigned int O_ALCOHOL = 46;

            constexpr unsigned int O_TRI_NITRO_PHENOL = 47;

            constexpr unsigned int O_HALOGENO_PHENOL = 48;

            constexpr unsigned int O_PHENOL = 49;

            constexpr unsigned int O_CARBOXYLIC_ACID = 50;

            constexpr unsigned int O_HALOGENO_CARBOXYCLIC_ACID = 51;

            constexpr unsigned int O_ENOL = 52;

            constexpr unsigned int O_OXIME = 53;

            constexpr unsigned int O_CL5_PHENOL = 54;

            constexpr unsigned int MAX_TYPE = O_CL5_PHENOL;

        } // namespace HBondDonorAtomType
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_HBONDDONORATOMTYPE_HPP
