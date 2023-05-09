/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
			const unsigned int UNDEF                       = 0;

			/**
			 * \brief Specifies that the atom is not a H-bond donor.
			 */
			const unsigned int NONE                        = 1;

			const unsigned int I_HI                        = 2;
			
			const unsigned int BR_HBR                      = 3;
			
			const unsigned int CL_HCL                      = 4;
			
			const unsigned int S_HSCN                      = 5;
			
			const unsigned int F_HF                        = 6;
			
			const unsigned int H_H2                        = 7;
			
			const unsigned int C_HCN                       = 8;
			
			const unsigned int C_ETHINE                    = 9;
			
			const unsigned int N_HN3                       = 10;
			
			const unsigned int N_NH3                       = 11;

			const unsigned int N_NH4                       = 12;
			
			const unsigned int N_AMINE                     = 13;

			const unsigned int N_AMINIUM                   = 14;

			const unsigned int N_ANILINE                   = 15;
			
			const unsigned int N_MONO_DI_NITRO_ANILINE     = 16;
			
			const unsigned int N_TRI_NITRO_ANILINE         = 17;
			
			const unsigned int N_PYRROLE                   = 18;
			
			const unsigned int N_AMIDE                     = 19;

			const unsigned int N_IMINE                     = 20;

			const unsigned int N_IMINIUM                   = 21;
			
			const unsigned int S_H2S                       = 22;
			
			const unsigned int S_HS                        = 23;
			
			const unsigned int S_THIOL                     = 24;
			
			const unsigned int O_H3PO4                     = 25;
			
			const unsigned int O_H2CO3                     = 26;
			
			const unsigned int O_HCO3                      = 27;
			
			const unsigned int O_H2O2                      = 28;
			
			const unsigned int O_H2O                       = 29;
			
			const unsigned int O_CF3SO3H                   = 30;
			
			const unsigned int O_HCLO4                     = 31;
			
			const unsigned int O_H2SO4                     = 32;
			
			const unsigned int O_HNO3                      = 33;
			
			const unsigned int O_HSO4                      = 34;
			
			const unsigned int O_HNO2                      = 35;
			
			const unsigned int O_NH2OH                     = 36;
			
			const unsigned int O_H2PO4                     = 37;
			
			const unsigned int O_H3BO3                     = 38;
			
			const unsigned int O_H4SIO4                    = 39;
			
			const unsigned int O_HPO4                      = 40;
			
			const unsigned int O_H2BO3                     = 41;
			
			const unsigned int O_HO                        = 42;
			
			const unsigned int O_SULFONIC_ACID             = 43;
			
			const unsigned int O_MONO_DI_NITRO_PHENOL      = 44;
			
			const unsigned int O_HALOGENO_ALCOHOL          = 45;
			
			const unsigned int O_ALCOHOL                   = 46;
			
			const unsigned int O_TRI_NITRO_PHENOL          = 47;
			
			const unsigned int O_HALOGENO_PHENOL           = 48;
			
			const unsigned int O_PHENOL                    = 49;
			
			const unsigned int O_CARBOXYLIC_ACID           = 50;
			
			const unsigned int O_HALOGENO_CARBOXYCLIC_ACID = 51;
			
			const unsigned int O_ENOL                      = 52;
			
			const unsigned int O_OXIME                     = 53;
			
			const unsigned int O_CL5_PHENOL                = 54;

			const unsigned int MAX_TYPE                    = O_CL5_PHENOL;

		}
    }
}

#endif // CDPL_MOLPROP_HBONDDONORATOMTYPE_HPP
