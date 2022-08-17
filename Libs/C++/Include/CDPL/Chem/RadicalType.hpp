/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RadicalType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::RadicalType.
 */

#ifndef CDPL_CHEM_RADICALTYPE_HPP
#define CDPL_CHEM_RADICALTYPE_HPP


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief Provides constants that are used to specify the degeneracy of the electronic state of radical atoms.
		 */
		namespace RadicalType
		{
			
			/**
			 * \brief Specifies that the atom is not a radical.
			 */
			const unsigned int NOT_RADICALIC = 0;

			/**
			 * \brief Specifies that the atom is a singlet diradical.
			 *
			 * Singlet diradicals have two electrons with antiparallel spin (\e +1/2 and \e –1/2) 
			 * in one orbital. The other adjacent, degenerate (equal energy) orbital is empty.
			 */
			const unsigned int SINGLET       = 1;

			/**
			 * \brief Specifies that the atom is a doublet radical.
			 *
			 * Doublet radicals are simple free radicals with one unpaired electron.
			 */
			const unsigned int DOUBLET       = 2;
	
			/**
			 * \brief Specifies that the atom is a triplet diradical.
			 *
			 * Triplet diradicals have two spin-up electrons in adjacent, degenerate (equal energy)
			 * orbitals.
			 */
			const unsigned int TRIPLET       = 3;
		}
	}
}

#endif // CDPL_CHEM_RADICALTYPE_HPP
