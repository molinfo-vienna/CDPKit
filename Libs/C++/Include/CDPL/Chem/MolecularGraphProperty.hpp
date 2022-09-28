/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MolecularGraphProperty.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHPROPERTY_HPP
#define CDPL_CHEM_MOLECULARGRAPHPROPERTY_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		class LookupKey;
	}

	namespace Chem
	{

		/**
		 * \brief Provides keys for built-in Chem::MolecularGraph properties.
		 */
		namespace MolecularGraphProperty
		{

			extern CDPL_CHEM_API const Base::LookupKey NAME; 

			extern CDPL_CHEM_API const Base::LookupKey COMPONENTS;
			extern CDPL_CHEM_API const Base::LookupKey RINGS;
			extern CDPL_CHEM_API const Base::LookupKey SSSR;
			extern CDPL_CHEM_API const Base::LookupKey CYCLIC_SUBSTRUCTURE;
			extern CDPL_CHEM_API const Base::LookupKey AROMATIC_SUBSTRUCTURE;
			extern CDPL_CHEM_API const Base::LookupKey PI_ELECTRON_SYSTEMS;
			
			extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;
			extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;
			extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUPS;

			extern CDPL_CHEM_API const Base::LookupKey TOPOLOGICAL_DISTANCE_MATRIX;
			extern CDPL_CHEM_API const Base::LookupKey GEOMETRICAL_DISTANCE_MATRIX;

			extern CDPL_CHEM_API const Base::LookupKey STOICHIOMETRIC_NUMBER;

			extern CDPL_CHEM_API const Base::LookupKey CONFORMATION_INDEX;
			extern CDPL_CHEM_API const Base::LookupKey CONFORMER_ENERGIES;

			extern CDPL_CHEM_API const Base::LookupKey STRUCTURE_DATA;

			extern CDPL_CHEM_API const Base::LookupKey HASH_CODE;

			extern CDPL_CHEM_API const Base::LookupKey MDL_USER_INITIALS;
			extern CDPL_CHEM_API const Base::LookupKey MDL_PROGRAM_NAME;
			extern CDPL_CHEM_API const Base::LookupKey MDL_TIMESTAMP;
			extern CDPL_CHEM_API const Base::LookupKey MDL_REGISTRY_NUMBER;
			extern CDPL_CHEM_API const Base::LookupKey MDL_COMMENT;
			extern CDPL_CHEM_API const Base::LookupKey MDL_CTAB_VERSION;
			extern CDPL_CHEM_API const Base::LookupKey MDL_DIMENSIONALITY; 
			extern CDPL_CHEM_API const Base::LookupKey MDL_SCALING_FACTOR1;
			extern CDPL_CHEM_API const Base::LookupKey MDL_SCALING_FACTOR2;
			extern CDPL_CHEM_API const Base::LookupKey MDL_ENERGY;
			extern CDPL_CHEM_API const Base::LookupKey MDL_CHIRAL_FLAG;

			extern CDPL_CHEM_API const Base::LookupKey MOL2_CHARGE_TYPE;
			extern CDPL_CHEM_API const Base::LookupKey MOL2_MOLECULE_TYPE;
		}
	}
}

#endif // CDPL_CHEM_MOLECULARGRAPHPROPERTY_HPP
