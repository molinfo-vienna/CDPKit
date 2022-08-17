/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondPropertyFlag.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondPropertyFlag.
 */

#ifndef CDPL_CHEM_BONDPROPERTYFLAG_HPP
#define CDPL_CHEM_BONDPROPERTYFLAG_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \brief Provides flags for the specification of basic Chem::Bond properties.
		 */
		namespace BondPropertyFlag
		{
 
			/**
			 * \brief Represents an empty set of bond properties.
			 */
			const unsigned int NONE              = 0x0;

			/**
			 * \brief Represents the default set of bond properties.
			 */
			const unsigned int DEFAULT           = 0x80000000;

			/**
			 * \brief Specifies the <em>CIP</em>-configuration of a double bond.
			 */
			const unsigned int CIP_CONFIGURATION = 0x1;

			/**
			 * \brief Specifies the order of a bond.
			 */
			const unsigned int ORDER             = 0x2;

			/**
			 * \brief Specifies the ring/chain topology of a bond.
			 */
			const unsigned int TOPOLOGY          = 0x4;

			/**
			 * \brief Specifies the membership of a bond in aromatic rings.
			 */
			const unsigned int AROMATICITY       = 0x8;

			/**
			 * \brief Specifies the steric configuration of a double bond.
			 */
			const unsigned int CONFIGURATION     = 0x10;
		}
	}
}

#endif // CDPL_CHEM_BONDPROPERTYFLAG_HPP
