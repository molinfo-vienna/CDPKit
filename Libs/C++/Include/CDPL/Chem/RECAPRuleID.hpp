/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RECAPRuleID.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::RECAPRuleID.
 */

#ifndef CDPL_CHEM_RECAPRULEID_HPP
#define CDPL_CHEM_RECAPRULEID_HPP


namespace CDPL 
{

    namespace Chem 
    {

		/**
		 * \addtogroup CDPL_CHEM_CONSTANTS
		 * @{
		 */

		/**
		 * \brief Provides constants for the identification of RECAP rules.
		 * \see [\ref RECAP]
		 */
		namespace RECAPRuleID 
		{

			const unsigned int NONE                   = 0;
			const unsigned int AMIDE                  = 1;
			const unsigned int ESTER                  = 2;
			const unsigned int AMINE                  = 3;
			const unsigned int UREA                   = 4;
			const unsigned int ETHER                  = 5;
			const unsigned int OLEFIN                 = 6;
			const unsigned int QUARTERNARY_N          = 7;
			const unsigned int AROMATIC_N_ALIPHATIC_C = 8;
			const unsigned int LACTAM_N_ALIPHATIC_C   = 9;
			const unsigned int AROMATIC_C_AROMATIC_C  = 10;
			const unsigned int SULFONAMIDE            = 11;
		}

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_RECAPRULEID_HPP
