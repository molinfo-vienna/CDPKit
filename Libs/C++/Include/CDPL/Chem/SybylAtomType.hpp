/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SybylAtomType.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
			 * \brief Atom with no matching Sybyl atom type.
			 */
			const unsigned int UNKNOWN          = 0;

			/**
			 * \brief Specifies sp3 \e Carbon.
			 */
			const unsigned int C_3              = 1;

			/**
			 * \brief Specifies sp2 \e Carbon.
			 */
			const unsigned int C_2              = 2;

			/**
			 * \brief Specifies sp \e Carbon.
			 */
			const unsigned int C_1              = 3;

			/**
			 * \brief Specifies an aromatic \e Carbon.
			 */
			const unsigned int C_ar             = 4;
 
			/**
			 * \brief Specifies a \e Carbocation (C+), used only in a guanidinium group.
			 */
			const unsigned int C_cat            = 5;
 
			/**
			 * \brief Specifies sp3 \e Nitrogen.
			 */
			const unsigned int N_3              = 6;

			/**
			 * \brief Specifies sp2 \e Nitrogen.
			 */
			const unsigned int N_2              = 7;

			/**
			 * \brief Specifies sp \e Nitrogen.
			 */
			const unsigned int N_1              = 8;

			/**
			 * \brief Specifies an aromatic \e Nitrogen.
			 */
			const unsigned int N_ar             = 9;

			/**
			 * \brief Specifies \e Nitrogen in amides.
			 */
			const unsigned int N_am             = 10;

			/**
			 * \brief Specifies a trigonal planar \e Nitrogen.
			 */
			const unsigned int N_pl3            = 11;
	
			/**
			 * \brief Specifies a positively charged sp3 \e Nitrogen.
			 */
			const unsigned int N_4              = 12;
	
			/**
			 * \brief Specifies sp3 \e Oxygen.
			 */
			const unsigned int O_3              = 13;

			/**
			 * \brief Specifies sp2 \e Oxygen.
			 */
			const unsigned int O_2              = 14;

			/**
			 * \brief Specifies \e Oxygen in carboxylate and phosphate groups.
			 */
			const unsigned int O_co2            = 15;

			/**
			 * \brief Specifies \e Oxygen in the <em>Single Point Charge (SPC)</em> water model.
			 */
			const unsigned int O_spc            = 16;

			/**
			 * \brief Specifies \e Oxygen in the <em>Transferable Intermolecular Potential (TIP3P)</em> water model.
			 */
			const unsigned int O_t3p            = 17;

			/**
			 * \brief Specifies sp3 \e Sulfur.
			 */
			const unsigned int S_3              = 18;

			/**
			 * \brief Specifies sp2 \e Sulfur.
			 */
			const unsigned int S_2              = 19;

			/**
			 * \brief Specifies \e Sulfur in sulfoxides.
			 */
			const unsigned int S_O              = 20;

			/**
			 * \brief Specifies \e Sulfur in sulfones.
			 */
			const unsigned int S_O2             = 21;

			/**
			 * \brief Specifies sp3 \e Phosphorous.
			 */
			const unsigned int P_3              = 22;

			/**
			 * \brief Specifies \e Fluorine.
			 */
			const unsigned int F                = 23;
	  
			/**
			 * \brief Specifies \e Hydrogen.
			 */
			const unsigned int H                = 24;

			/**
			 * \brief Specifies \e Hydrogen in the <em>Single Point Charge (SPC)</em> water model.
			 */
			const unsigned int H_spc            = 25;

			/**
			 * \brief Specifies \e Hydrogen in the <em>Transferable intermolecular Potential (TIP3P)</em> water model.
			 */
			const unsigned int H_t3p            = 26;

			/**
			 * \brief Specifies a lone pair.
			 */
			const unsigned int LP               = 27;

			/**
			 * \brief Specifies a dummy atom.
			 */
			const unsigned int Du               = 28;

			/**
			 * \brief Specifies a dummy \e Carbon.
			 */
			const unsigned int Du_C             = 29;

			/**
			 * \brief Specifies any atom.
			 */
			const unsigned int Any              = 30;

			/**
			 * \brief Specifies any halogen.
			 */
			const unsigned int Hal              = 31;

			/**
			 * \brief Specifies a heteroatom (N, O, S or P).
			 */
			const unsigned int Het              = 32;

			/**
			 * \brief Specifies any heavy atom (non-Hydrogen).
			 */
			const unsigned int Hev              = 33;

			/**
			 * \brief Specifies \e Lithium.
			 */
			const unsigned int Li               = 34;

			/**
			 * \brief Specifies \e Sodium.
			 */
			const unsigned int Na               = 35;

			/**
			 * \brief Specifies \e Magnesium.
			 */
			const unsigned int Mg               = 36;

			/**
			 * \brief Specifies \e Aluminum.
			 */
			const unsigned int Al               = 37;

			/**
			 * \brief Specifies \e Silicon.
			 */
			const unsigned int Si               = 38;

			/**
			 * \brief Specifies \e Potassium.
			 */
			const unsigned int K                = 39;

			/**
			 * \brief Specifies \e Calcium.
			 */
			const unsigned int Ca               = 40;

			/**
			 * \brief Specifies \e Chromium (tetrahedral).
			 */
			const unsigned int Cr_th            = 41;

			/**
			 * \brief Specifies \e Chromium (octahedral).
			 */
			const unsigned int Cr_oh            = 42;

			/**
			 * \brief Specifies \e Manganese.
			 */
			const unsigned int Mn               = 43;

			/**
			 * \brief Specifies \e Iron.
			 */
			const unsigned int Fe               = 44;

			/**
			 * \brief Specifies \e Cobalt (octahedral).
			 */
			const unsigned int Co_oh            = 45;

			/**
			 * \brief Specifies \e Copper.
			 */
			const unsigned int Cu               = 46;

			/**
			 * \brief Specifies \e Chlorine.
			 */
			const unsigned int Cl               = 47;

			/**
			 * \brief Specifies \e Bromine.
			 */
			const unsigned int Br               = 48;

			/**
			 * \brief Specifies \e Iodine.
			 */
			const unsigned int I                = 49;

			/**
			 * \brief Specifies \e Zinc.
			 */
			const unsigned int Zn               = 50;

			/**
			 * \brief Specifies \e Selenium.
			 */	    
			const unsigned int Se               = 51;

			/**
			 * \brief Specifies \e Molybdenum.
			 */	    
			const unsigned int Mo               = 52;

			/**
			 * \brief Specifies \e Tin.
			 */
			const unsigned int Sn               = 53;

			/**
			 * \brief Marks the end of all supported atom types.
			 */
			const unsigned int MAX_TYPE         = Sn;
		}
    }
}

#endif // CDPL_CHEM_SYBYLATOMTYPE_HPP
