/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphProperty.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Base/LookupKeyDefinition.hpp"


namespace CDPL 
{

	namespace Chem
	{

		namespace MolecularGraphProperty
		{

			CDPL_DEFINE_LOOKUP_KEY(NAME); 

			CDPL_DEFINE_LOOKUP_KEY(COMPONENTS);
			CDPL_DEFINE_LOOKUP_KEY(RINGS);
			CDPL_DEFINE_LOOKUP_KEY(SSSR);
			CDPL_DEFINE_LOOKUP_KEY(CYCLIC_SUBSTRUCTURE);
			CDPL_DEFINE_LOOKUP_KEY(AROMATIC_SUBSTRUCTURE);

			CDPL_DEFINE_LOOKUP_KEY(MATCH_CONSTRAINTS);
			CDPL_DEFINE_LOOKUP_KEY(MATCH_EXPRESSION);
			CDPL_DEFINE_LOOKUP_KEY(COMPONENT_GROUPS);

			CDPL_DEFINE_LOOKUP_KEY(TOPOLOGICAL_DISTANCE_MATRIX);
			CDPL_DEFINE_LOOKUP_KEY(GEOMETRICAL_DISTANCE_MATRIX);

			CDPL_DEFINE_LOOKUP_KEY(STOICHIOMETRIC_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(CONFORMATION_INDEX);
			CDPL_DEFINE_LOOKUP_KEY(CONFORMER_ENERGIES);

			CDPL_DEFINE_LOOKUP_KEY(STRUCTURE_DATA);

			CDPL_DEFINE_LOOKUP_KEY(HASH_CODE);

			CDPL_DEFINE_LOOKUP_KEY(MDL_USER_INITIALS);
			CDPL_DEFINE_LOOKUP_KEY(MDL_PROGRAM_NAME);
			CDPL_DEFINE_LOOKUP_KEY(MDL_TIMESTAMP);
			CDPL_DEFINE_LOOKUP_KEY(MDL_DIMENSIONALITY);
			CDPL_DEFINE_LOOKUP_KEY(MDL_SCALING_FACTOR1);
			CDPL_DEFINE_LOOKUP_KEY(MDL_SCALING_FACTOR2);
			CDPL_DEFINE_LOOKUP_KEY(MDL_ENERGY);
			CDPL_DEFINE_LOOKUP_KEY(MDL_REGISTRY_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(MDL_COMMENT);
			CDPL_DEFINE_LOOKUP_KEY(MDL_CHIRAL_FLAG);
			CDPL_DEFINE_LOOKUP_KEY(MDL_CTAB_VERSION);

			CDPL_DEFINE_LOOKUP_KEY(MOL2_CHARGE_TYPE);
			CDPL_DEFINE_LOOKUP_KEY(MOL2_MOLECULE_TYPE);
		}

		void initMolecularGraphProperties() {}
	}
}
