/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondDirection.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondDirection.
 */

#ifndef CDPL_CHEM_BONDDIRECTION_HPP
#define CDPL_CHEM_BONDDIRECTION_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \brief Provides constants for the specification of directional bonds in <em>Daylight SMILES</em> and
		 *        \e SMARTS strings.
		 *
		 * Directional bonds in <em>Daylight SMILES</em> or \e SMARTS strings are used to specify the configuration 
		 * around a double bond by indicating the relative direction of the bonds to its substituent atoms. They have only
		 * a meaning when they occur on both sides of the double bond (see [\ref SMILES, \ref SMARTS]). 
		 */
		namespace BondDirection
		{

			/**
			 * \brief Specifies that the bond has no associated direction.
			 */
			const unsigned int NONE        = 0x0; 

			/**
			 * \brief Specifies that the bond is directed upwards.
			 *
			 * In \e SMILES and \e SMARTS strings \e up bonds are specified by a slash '/'.
			 */
			const unsigned int UP          = 0x1; 

			/**
			 * \brief Specifies that the bond is directed downwards.
			 *
			 * In \e SMILES and \e SMARTS strings \e down bonds are specified by a backslash '\'.
			 */
			const unsigned int DOWN        = 0x2; 

			/**
			 * \brief In a substructure search query pattern this flag indicates that the specified query bond direction is not mandatory and
			 *        that target bonds with an unspecified direction shall also be considered as a match.
			 *
			 * The flag only has a meaning for directional bonds in \e SMARTS patterns where
			 * - its resulting bitwise OR combination with BondDirection::UP specifies that a matching target bond is required to have an
			 *   <em>upward or unspecified</em> direction 
			 * - and its combination with BondDirection::DOWN specifies that a target bond must have a
			 *   <em>downward or unspecified</em> direction to be considered as a match.
			 */
			const unsigned int UNSPECIFIED = 0x4; 
		}
	}
}

#endif // CDPL_CHEM_BONDDIRECTION_HPP
