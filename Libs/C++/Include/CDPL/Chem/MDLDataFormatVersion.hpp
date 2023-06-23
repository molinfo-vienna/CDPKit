/* 
 * MDLDataFormatVersion.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MDLDataFormatVersion.
 */

#ifndef CDPL_CHEM_MDLDATAFORMATVERSION_HPP
#define CDPL_CHEM_MDLDATAFORMATVERSION_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \brief Provides constants that are used to specify the connection table and \e Rxn-File version for the
		 *        I/O of molecular graphs and reactions in \e MDL format [\ref CTFILE].
		 */
		namespace MDLDataFormatVersion
		{

			/**
			 * \brief Specifies that the data format version is undefined.
			 */
			const unsigned int UNDEF    = 0;

			/**
			 * \brief Specifies the data format version \e V2000.
			 */
			const unsigned int V2000    = 2000;

			/**
			 * \brief Specifies the extended data format version \e V3000.
			 */
			const unsigned int V3000    = 3000;
		}
	}
}

#endif // CDPL_CHEM_MDLDATAFORMATVERSION_HPP
