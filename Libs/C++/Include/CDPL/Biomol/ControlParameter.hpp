/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameter.hpp 
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
 * \brief Definition of constants in namespace CDPL::Biomol::ControlParameter.
 */

#ifndef CDPL_BIOMOL_CONTROLPARAMETER_HPP
#define CDPL_BIOMOL_CONTROLPARAMETER_HPP

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
		 * \addtogroup CDPL_BIOMOL_CONTROL_PARAMETERS
		 * @{
		 */

		/**
		 * \brief Provides keys for built-in control-parameters.
		 */
		namespace ControlParameter
		{

			/**
			 * \brief Specifies whether non-fatal recoverable I/O errors should be ignored or cause an I/O operation to fail.
			 *
			 * If the control-parameter is set to \c true, not only severe errors cause an I/O operation to fail, but also
			 * non-fatal errors from which a recovery would be possible. 
			 * If the control-parameter is set to \c false, I/O operations will proceed even if a non-fatal error has been
			 * detected.
			 *
			 * \valuetype \c bool
			 */
			extern CDPL_BIOMOL_API const Base::LookupKey STRICT_ERROR_CHECKING;

			/**
			 * \brief Specifies whether to check if data lines exceed the maximum allowed line length when reading or writing data
			 *        in <em>PDB</em> [\ref PDB] format.
			 *
			 * If the control-parameter is set to \c true, the length of data lines that were read from or have to
			 * be written to data encoded in one of the above mentioned formats will be checked against the maximum
			 * allowed line length. Lines that exceeded the line length limit are considered as an error condition and cause
			 * the input or output operation to fail. If \c %CHECK_LINE_LENGTH is \c false, the length of data lines will
			 * not be checked and has no impact on the success of the performed I/O operation.
			 *
			 * \valuetype \c bool
			 */
			extern CDPL_BIOMOL_API const Base::LookupKey CHECK_LINE_LENGTH;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_RESIDUE_DICTIONARY;
		
			extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES;
	
			extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_IGNORE_CONECT_RECORDS;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_IGNORE_FORMAL_CHARGE_FIELD;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_FORMAL_ATOM_CHARGES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_ATOM_TYPES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_CALC_MISSING_FORMAL_CHARGES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_PERCEIVE_MISSING_BOND_ORDERS;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_EVALUATE_MASTER_RECORD;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_TRUNCATE_LINES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_WRITE_FORMAL_CHARGES;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_WRITE_CONECT_RECORDS;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS;

			extern CDPL_BIOMOL_API const Base::LookupKey PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER;

			extern CDPL_BIOMOL_API const Base::LookupKey COMBINE_INTERFERING_RESIDUE_COORDINATES;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_CONTROLPARAMETER_HPP
