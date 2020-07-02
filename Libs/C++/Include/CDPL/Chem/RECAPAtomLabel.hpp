/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RECAPAtomLabel.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::RECAPAtomLabel.
 */

#ifndef CDPL_CHEM_RECAPATOMLABEL_HPP
#define CDPL_CHEM_RECAPATOMLABEL_HPP


namespace CDPL 
{

    namespace Chem 
    {

	/**
	 * \addtogroup CDPL_CHEM_CONSTANTS
	 * @{
	 */

	/**
	 * \brief Provides constants for the labeling of atoms in bonds matched by a RECAP rule.
	 * \see [\ref RECAP]
	 */
	namespace RECAPAtomLabel 
	{

	    const unsigned int NONE                     = 0;
	    const unsigned int AMIDE_N                  = 1;
	    const unsigned int AMIDE_C                  = 2;
	    const unsigned int ESTER_O                  = 3;
	    const unsigned int ESTER_C                  = 4;
	    const unsigned int AMINE_N                  = 5;
	    const unsigned int AMINE_C                  = 6;
	    const unsigned int UREA_N                   = 7;
	    const unsigned int UREA_C                   = 8;
	    const unsigned int ETHER_O                  = 9;
	    const unsigned int ETHER_C                  = 10;
	    const unsigned int OLEFIN_C                 = 11;
	    const unsigned int QUARTERNARY_N_N          = 12;
	    const unsigned int QUARTERNARY_N_C          = 13;
	    const unsigned int AROMATIC_N_ALIPHATIC_C_N = 14;
	    const unsigned int AROMATIC_N_ALIPHATIC_C_C = 15;
	    const unsigned int LACTAM_N_ALIPHATIC_C_N   = 16;
	    const unsigned int LACTAM_N_ALIPHATIC_C_C   = 17;
	    const unsigned int AROMATIC_C_AROMATIC_C_C  = 18;
	    const unsigned int SULFONAMIDE_N            = 19;
	    const unsigned int SULFONAMIDE_S            = 20;
	}

	/**
	 * @}
	 */
    }
}

#endif // CDPL_CHEM_RECAPATOMLABEL_HPP
