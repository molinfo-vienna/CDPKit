/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ForceFieldType.hpp 
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
 * \brief Definition of constants in namespace CDPL::ConfGen::ForceFieldType.
 */

#ifndef CDPL_CONFGEN_FORCEFIELDTYPE_HPP
#define CDPL_CONFGEN_FORCEFIELDTYPE_HPP


namespace CDPL 
{

	namespace ConfGen
	{

		/**
		 * \addtogroup CDPL_CONFGEN_CONSTANTS
		 * @{
		 */

		/**
		 * \brief Provides constants that are used to specify the forcefield that shall be used 
		 *        for 3D coordinates refinement and energy calculations.
		 */
		namespace ForceFieldType
		{
					
			const unsigned int MMFF94                = 0;
			const unsigned int MMFF94_NO_ESTAT       = 1;
			const unsigned int MMFF94S               = 2;
			const unsigned int MMFF94S_NO_ESTAT      = 3;
			const unsigned int MMFF94S_EXT           = 4;
			const unsigned int MMFF94S_EXT_NO_ESTAT  = 5;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CONFGEN_FORCEFIELDTYPE_HPP
