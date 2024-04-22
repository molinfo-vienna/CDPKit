/* 
 * HBondAcceptorAtomType.hpp 
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
 * \brief Definition of constants in namespace CDPL::MolProp::HBondAcceptorAtomType.
 */

#ifndef CDPL_MOLPROP_HBONDACCEPTORATOMTYPE_HPP
#define CDPL_MOLPROP_HBONDACCEPTORATOMTYPE_HPP


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Provides constants used to specify the structural class of H-bond acceptor atoms.
         */
        namespace HBondAcceptorAtomType
        {

            /**
             * \brief Specifies that the H-bond acceptor type of the atom is undefined.
             */
            constexpr unsigned int UNDEF = 0;

            /**
             * \brief Specifies that the atom is not a H-bond acceptor.
             */
            constexpr unsigned int NONE = 1;

            constexpr unsigned int O_H2O = 2;

            constexpr unsigned int O_UREA = 3;

            constexpr unsigned int O_BARBITURIC_ACID = 4;

            constexpr unsigned int O_URIC_ACID = 5;

            constexpr unsigned int O_ETHER = 6;

            constexpr unsigned int O_AMIDE = 7;

            constexpr unsigned int O_N_OXIDE = 8;

            constexpr unsigned int O_ACID = 9;

            constexpr unsigned int O_ESTER = 10;

            constexpr unsigned int O_SULFOXIDE = 11;

            constexpr unsigned int O_NITRO = 12;

            constexpr unsigned int O_SELEN_OXIDE = 13;

            constexpr unsigned int O_ALDEHYD = 14;

            constexpr unsigned int O_KETONE = 15;

            constexpr unsigned int O_ALCOHOL = 16;

            constexpr unsigned int N_NH3 = 17;

            constexpr unsigned int N_DIAMINE = 18;

            constexpr unsigned int N_MONO_DI_NITRO_ANILINE = 19;

            constexpr unsigned int N_TRI_NITRO_ANILINE = 20;

            constexpr unsigned int N_HALOGENO_ANILINE = 21;

            constexpr unsigned int N_ANILINE = 22;

            constexpr unsigned int N_NITRILE = 23;

            constexpr unsigned int N_AZOLE = 24;

            constexpr unsigned int N_AMINE = 25;

            constexpr unsigned int N_AMIDINE = 26;

            constexpr unsigned int N_AZO = 27;

            constexpr unsigned int N_AZINE = 28;

            constexpr unsigned int N_DIAZINE = 29;

            constexpr unsigned int N_IMINE = 30;

            constexpr unsigned int S_SULFIDE = 31;

            constexpr unsigned int S_THIOUREA = 32;

            constexpr unsigned int P_MONO_DI_PHOSPHINE = 33;

            constexpr unsigned int P_TRI_PHOSPHINE = 34;

            constexpr unsigned int MAX_TYPE = P_TRI_PHOSPHINE;

        } // namespace HBondAcceptorAtomType
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_HBONDACCEPTORATOMTYPE_HPP
