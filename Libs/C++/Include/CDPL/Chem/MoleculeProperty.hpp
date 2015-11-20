/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MoleculeProperty.
 */

#ifndef CDPL_CHEM_MOLECULEPROPERTY_HPP
#define CDPL_CHEM_MOLECULEPROPERTY_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		class ValueKey;
	}

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_MOLECULE_PROPERTIES
		 * @{
		 */
	
		/**
		 * \brief Provides keys for built-in Chem::Molecule properties.
		 */
		namespace MoleculeProperty
		{

			extern CDPL_CHEM_API const Base::ValueKey MATCH_CONSTRAINTS;
			extern CDPL_CHEM_API const Base::ValueKey MATCH_EXPRESSION;
			
			extern CDPL_CHEM_API const Base::ValueKey RINGS;
			extern CDPL_CHEM_API const Base::ValueKey AROMATIC_RINGS;
			extern CDPL_CHEM_API const Base::ValueKey SSSR;
			extern CDPL_CHEM_API const Base::ValueKey AROMATIC_ATOMS_AND_BONDS;
			extern CDPL_CHEM_API const Base::ValueKey RING_ATOMS_AND_BONDS;
	
			extern CDPL_CHEM_API const Base::ValueKey COMPONENTS;
			extern CDPL_CHEM_API const Base::ValueKey COMPONENT_GROUPS;

			extern CDPL_CHEM_API const Base::ValueKey STOICHIOMETRIC_NUMBER;

			extern CDPL_CHEM_API const Base::ValueKey TOPOLOGICAL_DISTANCE_MATRIX;
			extern CDPL_CHEM_API const Base::ValueKey GEOMETRICAL_DISTANCE_MATRIX;

			extern CDPL_CHEM_API const Base::ValueKey MDL_USER_INITIALS;
			extern CDPL_CHEM_API const Base::ValueKey MDL_PROGRAM_NAME;
			extern CDPL_CHEM_API const Base::ValueKey MDL_TIMESTAMP;
			extern CDPL_CHEM_API const Base::ValueKey MDL_REGISTRY_NUMBER;
			extern CDPL_CHEM_API const Base::ValueKey MDL_COMMENT;
			extern CDPL_CHEM_API const Base::ValueKey MDL_CTAB_VERSION;
			extern CDPL_CHEM_API const Base::ValueKey MDL_STRUCTURE_DATA;
			extern CDPL_CHEM_API const Base::ValueKey MDL_DIMENSIONALITY; 
			extern CDPL_CHEM_API const Base::ValueKey MDL_SCALING_FACTOR1;
			extern CDPL_CHEM_API const Base::ValueKey MDL_SCALING_FACTOR2;
			extern CDPL_CHEM_API const Base::ValueKey MDL_ENERGY;
			extern CDPL_CHEM_API const Base::ValueKey MDL_CHIRAL_FLAG;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOLECULEPROPERTY_HPP
