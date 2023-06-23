/* 
 * ReactionCenterStatus.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::ReactionCenterStatus.
 */

#ifndef CDPL_CHEM_REACTIONCENTERSTATUS_HPP
#define CDPL_CHEM_REACTIONCENTERSTATUS_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \brief Provides flags that are used to describe state changes of atoms and bonds in a
		 *        reaction center.
		 * \note The flags ReactionCenterStatus::IS_CENTER, ReactionCenterStatus::BOND_MADE, ReactionCenterStatus::BOND_BROKEN,
		 *       and ReactionCenterStatus::BOND_ORDER_CHANGE may be combined by bitwise OR operations to obtain a composite
		 *       reaction center state.
		 */
		namespace ReactionCenterStatus
		{

			/**
			 * \brief Specifies that the atom or bond is not part of the reaction center.
			 */
			const unsigned int NONE              = 0;

			/**
			 * \brief Specifies for bonds in a reaction substructure search query that matching target bonds must not
			 *        be part of a reaction center.
			 */
			const unsigned int NO_CENTER         = 0x1;

			/**
			 * \brief Specifies that the bond is part of the reaction center.
			 */
			const unsigned int IS_CENTER         = 0x2;

			/**
			 * \brief Specifies that the bond is made by the reaction.
			 */
			const unsigned int BOND_MADE         = 0x4;

			/**
			 * \brief Specifies that the bond is broken by the reaction.
			 */
			const unsigned int BOND_BROKEN       = 0x8;

			/**
			 * \brief Specifies that the bond order is changed by the reaction.
			 */
			const unsigned int BOND_ORDER_CHANGE = 0x10;

			/**
			 * \brief Specifies that the bond is left unaltered by the reaction.
			 */
			const unsigned int NO_CHANGE         = 0x20;

			/**
			 * \brief Specifies that the configuration of the atom is inverted by the reaction.
			 */
			const unsigned int STEREO_INVERSION  = 0x40;

			/**
			 * \brief Specifies that the configuration of the atom is retained in the reaction.
			 */
			const unsigned int STEREO_RETENTION  = 0x80;

			/**
			 * \brief Specifies that the change of the atom is exactly as specified.
			 */
			const unsigned int EXACT_CHANGE      = 0x80;
		}
	}
}

#endif // CDPL_CHEM_REACTIONCENTERSTATUS_HPP
