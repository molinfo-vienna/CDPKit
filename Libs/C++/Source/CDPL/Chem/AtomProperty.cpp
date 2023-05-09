/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomProperty.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Base/LookupKeyDefinition.hpp"


namespace CDPL 
{

	namespace Chem
	{

		namespace AtomProperty
		{

			CDPL_DEFINE_LOOKUP_KEY(NAME);
			CDPL_DEFINE_LOOKUP_KEY(SYMBOL);
			CDPL_DEFINE_LOOKUP_KEY(TYPE);

			CDPL_DEFINE_LOOKUP_KEY(FORMAL_CHARGE);
			CDPL_DEFINE_LOOKUP_KEY(ISOTOPE);
			CDPL_DEFINE_LOOKUP_KEY(RADICAL_TYPE);
			CDPL_DEFINE_LOOKUP_KEY(HYBRIDIZATION); 

			CDPL_DEFINE_LOOKUP_KEY(RING_FLAG);
			CDPL_DEFINE_LOOKUP_KEY(AROMATICITY_FLAG);

			CDPL_DEFINE_LOOKUP_KEY(UNPAIRED_ELECTRON_COUNT);
		
			CDPL_DEFINE_LOOKUP_KEY(IMPLICIT_HYDROGEN_COUNT);
	
			CDPL_DEFINE_LOOKUP_KEY(COORDINATES_2D);
			CDPL_DEFINE_LOOKUP_KEY(COORDINATES_3D_ARRAY);
		
			CDPL_DEFINE_LOOKUP_KEY(MORGAN_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(CANONICAL_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(CIP_PRIORITY);
			CDPL_DEFINE_LOOKUP_KEY(SYMMETRY_CLASS);

			CDPL_DEFINE_LOOKUP_KEY(STEREO_DESCRIPTOR);
			CDPL_DEFINE_LOOKUP_KEY(STEREO_CENTER_FLAG);
			CDPL_DEFINE_LOOKUP_KEY(CIP_CONFIGURATION);
			CDPL_DEFINE_LOOKUP_KEY(MDL_PARITY);
			CDPL_DEFINE_LOOKUP_KEY(MDL_DB_STEREO_CARE_FLAG);

			CDPL_DEFINE_LOOKUP_KEY(SYBYL_TYPE);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_CHARGE);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_NAME);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_SUBSTRUCTURE_ID);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_SUBSTRUCTURE_NAME);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_SUBSTRUCTURE_SUBTYPE);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_SUBSTRUCTURE_CHAIN);
		
			CDPL_DEFINE_LOOKUP_KEY(REACTION_CENTER_STATUS);
			CDPL_DEFINE_LOOKUP_KEY(ATOM_MAPPING_ID);
			
			CDPL_DEFINE_LOOKUP_KEY(MATCH_CONSTRAINTS);
			CDPL_DEFINE_LOOKUP_KEY(MATCH_EXPRESSION);
			CDPL_DEFINE_LOOKUP_KEY(MATCH_EXPRESSION_STRING);
		
			CDPL_DEFINE_LOOKUP_KEY(COMPONENT_GROUP_ID);
		}

		void initAtomProperties() {}
	}
}
