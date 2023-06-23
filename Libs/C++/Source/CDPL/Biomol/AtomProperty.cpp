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

#include "CDPL/Biomol/AtomProperty.hpp"
#include "CDPL/Base/LookupKeyDefinition.hpp"


namespace CDPL 
{

	namespace Biomol
	{

		namespace AtomProperty
		{

			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_ATOM_NAME);
			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_ALT_ATOM_NAME);
			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_LEAVING_ATOM_FLAG);
			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_LINKING_ATOM_FLAG);
			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_CODE);
			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_SEQUENCE_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(RESIDUE_INSERTION_CODE);

			CDPL_DEFINE_LOOKUP_KEY(HETERO_ATOM_FLAG);
			CDPL_DEFINE_LOOKUP_KEY(CHAIN_ID);
			CDPL_DEFINE_LOOKUP_KEY(ALT_LOCATION_ID);
			CDPL_DEFINE_LOOKUP_KEY(MODEL_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(SERIAL_NUMBER);
			CDPL_DEFINE_LOOKUP_KEY(OCCUPANCY);
			CDPL_DEFINE_LOOKUP_KEY(B_FACTOR);
		}

		void initAtomProperties() {}
	}
}
