/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Biomol::MolecularGraphPropertyDefault.
 */

#ifndef CDPL_BIOMOL_MOLECULARGRAPHPROPERTYDEFAULT_HPP
#define CDPL_BIOMOL_MOLECULARGRAPHPROPERTYDEFAULT_HPP

#include <cstddef>

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL 
{

    namespace Biomol
    {

		/**
		 * \addtogroup CDPL_BIOMOL_MOLECULAR_GRAPH_PROPERTIES
		 * @{
		 */

		/**
		 * \brief Provides default values for built-in Chem::MolecularGraph properties.
		 */
		namespace MolecularGraphPropertyDefault
		{

			extern CDPL_BIOMOL_API const std::size_t MODEL_NUMBER;
			extern CDPL_BIOMOL_API const char RESIDUE_INSERTION_CODE;	
		}

		/**
		 * @}
		 */
    }
}

#endif // CDPL_BIOMOL_MOLECULARGRAPHPROPERTYDEFAULT_HPP
