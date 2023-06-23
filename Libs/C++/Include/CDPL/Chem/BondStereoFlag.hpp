/* 
 * BondStereoFlag.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondStereoFlag.
 */

#ifndef CDPL_CHEM_BONDSTEREOFLAG_HPP
#define CDPL_CHEM_BONDSTEREOFLAG_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \brief Provides constants for the specification of stereo bonds in 2D depictions of chemical structures.
		 */
		namespace BondStereoFlag
		{

			/**
			 * \brief Specifies a bond whose member atoms are located in the plane of the paper.
			 *
			 * Plain bonds are drawn as simple lines.
			 */
			const unsigned int PLAIN          = 0;
			
			/**
			 * \brief Specifies a bond where the end atom is above and the start atom is
			 *        in the plane of the paper.
			 *
			 * Bonds of this type are drawn as filled wedges with the narrow end at the start atom
			 * and the broad end at the end atom of the bond.
			 */
			const unsigned int UP             = 1; 

			/**
			 * \brief Specifies a bond where the start atom is above and the end atom is
			 *        in the plane of the paper.
			 *
			 * Bonds of this type are drawn as filled wedges with the broad end at the start atom and
			 * the narrow end at the end atom of the bond.
			 */
			const unsigned int REVERSE_UP     = 2; 

			/**
			 * \brief Specifies a bond where the end atom is below and the start atom is
			 *        in the plane of the paper.
			 *
			 * Bonds of this type are drawn as hashed wedges with the narrow end at the start atom and the broad
			 * end at the end atom of the bond.
			 */
			const unsigned int DOWN           = 3; 

			/**
			 * \brief Specifies a bond where the start atom is below and the end atom is
			 *        in the plane of the paper.
			 *
			 * Bonds of this type are drawn as hashed wedges with the broad end at the start atom and the
			 * narrow end at the end atom of the bond.
			 */
			const unsigned int REVERSE_DOWN   = 4; 
			
			/**
			 * \brief Specifies that stereogenic member atoms of the bond or any double bonds (including the bond
			 *        itself) that are incident to a member atom have an undefined stereochemistry.
			 *
			 * Bonds of this type are drawn as zig-zag wedges with the narrow end at the start atom and the broad
			 * end at the end atom of the bond. Double bonds are drawn with crossed lines.
			 *
			 * \note The flag is logically equivalent to BondStereoFlag::REVERSE_EITHER;
			 */
			const unsigned int EITHER         = 5;

			/**
			 * \brief Specifies that stereogenic member atoms of the bond or any double bonds (including the bond
			 *        itself) that are incident to a member atom have an undefined stereochemistry.
			 *
			 * Bonds of this type are drawn as zig-zag wedges with the broad end at the start atom and the narrow
			 * end at the end atom of the bond. Double bonds are drawn with crossed lines.
			 *
			 * \note The flag is logically equivalent to BondStereoFlag::EITHER;
			 */
			const unsigned int REVERSE_EITHER = 6;
		}
	}
}

#endif // CDPL_CHEM_BONDSTEREOFLAG_HPP
