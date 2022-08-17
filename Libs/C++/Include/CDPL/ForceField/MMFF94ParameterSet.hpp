/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94ParameterSet.hpp 
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
 * \brief Definition of constants in namespace CDPL::ForceField::MMFF94ParameterSet.
 */

#ifndef CDPL_FORCEFIELD_MMFF94PARAMETERSET_HPP
#define CDPL_FORCEFIELD_MMFF94PARAMETERSET_HPP


namespace CDPL
{

    namespace ForceField
    {

		/**
		 * \brief Provides flags for the specification of the MMFF94 parameter set to use.
		 */
		namespace MMFF94ParameterSet
		{

			const unsigned int DYNAMIC          = 0;
			const unsigned int STATIC           = 1;
			const unsigned int STATIC_XOOP      = 2;
			const unsigned int STATIC_RTOR      = 3;
			const unsigned int STATIC_RTOR_XOOP = 4;
		}
    }
}

#endif // CDPL_FORCEFIELD_MMFF94PARAMETERSET_HPP
