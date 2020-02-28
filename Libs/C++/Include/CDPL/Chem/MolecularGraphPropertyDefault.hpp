/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MolecularGraphPropertyDefault.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHPROPERTYDEFAULT_HPP
#define CDPL_CHEM_MOLECULARGRAPHPROPERTYDEFAULT_HPP

#include <string>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_MOLECULAR_GRAPH_PROPERTIES
		 * @{
		 */

		/**
		 * \brief Provides default values for built-in Chem::MolecularGraph properties.
		 */
		namespace MolecularGraphPropertyDefault
		{

			extern CDPL_CHEM_API const std::string NAME;
			extern CDPL_CHEM_API const double STOICHIOMETRIC_NUMBER;
			extern CDPL_CHEM_API const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS;
			extern CDPL_CHEM_API const unsigned int MDL_CTAB_VERSION;
			extern CDPL_CHEM_API const std::string MDL_COMMENT;
			extern CDPL_CHEM_API const std::string MDL_PROGRAM_NAME;
			extern CDPL_CHEM_API const std::string MDL_USER_INITIALS;
			extern CDPL_CHEM_API const std::size_t MDL_DIMENSIONALITY;
			extern CDPL_CHEM_API const double MDL_ENERGY;
			extern CDPL_CHEM_API const bool MDL_CHIRAL_FLAG;
			extern CDPL_CHEM_API const long MDL_SCALING_FACTOR1;
			extern CDPL_CHEM_API const double MDL_SCALING_FACTOR2;
			extern CDPL_CHEM_API const unsigned int MOL2_MOLECULE_TYPE;
			extern CDPL_CHEM_API const unsigned int MOL2_CHARGE_TYPE;
		}

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_MOLECULARGRAPHPROPERTYDEFAULT_HPP
