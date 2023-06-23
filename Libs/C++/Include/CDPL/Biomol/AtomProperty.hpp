/* 
 * AtomProperty.hpp 
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

/**
 * \file
 * \brief Definition of constants in namespace CDPL::Biomol::AtomProperty.
 */

#ifndef CDPL_BIOMOL_ATOMPROPERTY_HPP
#define CDPL_BIOMOL_ATOMPROPERTY_HPP

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

	namespace Base
	{

		class LookupKey;
	}

	namespace Biomol
	{

		/**
		 * \brief Provides keys for built-in Biomol::Atom properties.
		 */
		namespace AtomProperty
		{

			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_ATOM_NAME;
			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_ALT_ATOM_NAME;
			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_LEAVING_ATOM_FLAG;
			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_LINKING_ATOM_FLAG;
			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_CODE;
			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_SEQUENCE_NUMBER;
			extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_INSERTION_CODE;

			extern CDPL_BIOMOL_API const Base::LookupKey HETERO_ATOM_FLAG;
			extern CDPL_BIOMOL_API const Base::LookupKey SERIAL_NUMBER;
			extern CDPL_BIOMOL_API const Base::LookupKey CHAIN_ID;
			extern CDPL_BIOMOL_API const Base::LookupKey ALT_LOCATION_ID;
			extern CDPL_BIOMOL_API const Base::LookupKey MODEL_NUMBER;
			extern CDPL_BIOMOL_API const Base::LookupKey OCCUPANCY;
			extern CDPL_BIOMOL_API const Base::LookupKey B_FACTOR;
		}
	}
}

#endif // CDPL_BIOMOL_ATOMPROPERTY_HPP
