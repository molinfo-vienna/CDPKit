/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::AtomProperty.
 */

#ifndef CDPL_CHEM_ATOMPROPERTY_HPP
#define CDPL_CHEM_ATOMPROPERTY_HPP

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
		 * \addtogroup CDPL_CHEM_ATOM_PROPERTIES
		 * @{
		 */

		/**
		 * \brief Provides keys for built-in Chem::Atom properties.
		 */
		namespace AtomProperty
		{

			extern CDPL_CHEM_API const Base::LookupKey NAME;
			extern CDPL_CHEM_API const Base::LookupKey SYMBOL;
			extern CDPL_CHEM_API const Base::LookupKey TYPE;

			extern CDPL_CHEM_API const Base::LookupKey FORMAL_CHARGE;
			extern CDPL_CHEM_API const Base::LookupKey ISOTOPE;
			extern CDPL_CHEM_API const Base::LookupKey RADICAL_TYPE;
			extern CDPL_CHEM_API const Base::LookupKey HYBRIDIZATION; 

			extern CDPL_CHEM_API const Base::LookupKey RING_FLAG;
			extern CDPL_CHEM_API const Base::LookupKey AROMATICITY_FLAG;

			extern CDPL_CHEM_API const Base::LookupKey UNPAIRED_ELECTRON_COUNT;
	
			extern CDPL_CHEM_API const Base::LookupKey IMPLICIT_HYDROGEN_COUNT;
	
			extern CDPL_CHEM_API const Base::LookupKey COORDINATES_2D;
			extern CDPL_CHEM_API const Base::LookupKey COORDINATES_3D_ARRAY;
		
			extern CDPL_CHEM_API const Base::LookupKey MORGAN_NUMBER;
			extern CDPL_CHEM_API const Base::LookupKey CANONICAL_NUMBER;
			extern CDPL_CHEM_API const Base::LookupKey CIP_PRIORITY;
			extern CDPL_CHEM_API const Base::LookupKey SYMMETRY_CLASS;

			extern CDPL_CHEM_API const Base::LookupKey STEREO_DESCRIPTOR;
			extern CDPL_CHEM_API const Base::LookupKey STEREO_CENTER_FLAG;
			extern CDPL_CHEM_API const Base::LookupKey CIP_CONFIGURATION;
			extern CDPL_CHEM_API const Base::LookupKey MDL_PARITY;
			extern CDPL_CHEM_API const Base::LookupKey MDL_DB_STEREO_CARE_FLAG;

			extern CDPL_CHEM_API const Base::LookupKey SYBYL_TYPE;
			extern CDPL_CHEM_API const Base::LookupKey MOL2_CHARGE;

			extern CDPL_CHEM_API const Base::LookupKey PEOE_CHARGE;
	
			extern CDPL_CHEM_API const Base::LookupKey REACTION_CENTER_STATUS;
			extern CDPL_CHEM_API const Base::LookupKey REACTION_ATOM_MAPPING_ID;
			
			extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;
			extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;
			extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION_STRING;
		
			extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUP_ID;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ATOMPROPERTY_HPP
