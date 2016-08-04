/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyFlag.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of constants in namespace CDPL::Chem::AtomPropertyFlag.
 */

#ifndef CDPL_CHEM_ATOMPROPERTYFLAG_HPP
#define CDPL_CHEM_ATOMPROPERTYFLAG_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_CONSTANTS
		 * @{
		 */

		/**
		 * \brief Provides flags for the specification of basic Chem::Atom properties.
		 */
		namespace AtomPropertyFlag
		{

			/**
			 * \brief Represents an empty set of atom properties.
			 */
			const unsigned int NONE              = 0x0;

			/**
			 * \brief Represents the default set of atom properties.
			 */
			const unsigned int DEFAULT           = 0x80000000;

			/**
			 * \brief Specifies the <em>CIP</em>-configuration of a chiral atom.
			 */
			const unsigned int CIP_CONFIGURATION = 0x1;

			/**
			 * \brief Specifies the generic type or element of an atom.
			 */
			const unsigned int TYPE              = 0x2;

			/**
			 * \brief Specifies the isotopic mass of an atom.
			 */
			const unsigned int ISOTOPE           = 0x4;

			/**
			 * \brief Specifies the formal charge of an atom.
			 */
			const unsigned int FORMAL_CHARGE     = 0x8;

			/**
			 * \brief Specifies the hydrogen count of an atom.
			 */
			const unsigned int H_COUNT           = 0x10;

			/**
			 * \brief Specifies the symbol of an atom's element.
			 */
			const unsigned int SYMBOL            = 0x20;

			/**
			 * \brief Specifies the ring/chain topology of an atom.
			 */
			const unsigned int TOPOLOGY          = 0x40;

			/**
			 * \brief Specifies the membership of an atom in aromatic rings.
			 */
			const unsigned int AROMATICITY       = 0x80;

			/**
			 * \brief Specifies the configuration of a stereogenic atom.
			 */
			const unsigned int CONFIGURATION     = 0x100;

			/**
			 * \brief Specifies the atom-mapping ID an atom in a reaction.
			 */
			const unsigned int ATOM_MAPPING_ID   = 0x200;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ATOMPROPERTYFLAG_HPP
