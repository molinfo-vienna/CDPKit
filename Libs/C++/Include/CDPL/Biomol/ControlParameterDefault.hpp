/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Biomol::ControlParameterDefault.
 */

#ifndef CDPL_BIOMOL_CONTROLPARAMETERDEFAULT_HPP
#define CDPL_BIOMOL_CONTROLPARAMETERDEFAULT_HPP

#include <cstddef>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"


namespace CDPL 
{

	namespace Biomol
	{

		/**
		 * \addtogroup CDPL_BIOMOL_CONTROL_PARAMETERS
		 * @{
		 */

		/**
		 * \brief Provides default values for built-in control-parameters.
		 */
		namespace ControlParameterDefault
		{

			/**
			 * \brief Default setting (= \c false) for the control-parameter Biomol::ControlParameter::STRICT_ERROR_CHECKING.
			 */
			extern CDPL_BIOMOL_API const bool STRICT_ERROR_CHECKING;

			/**
			 * \brief Default setting (= \c false) for the control-parameter Biomol::ControlParameter::CHECK_LINE_LENGTH.
			 */
			extern CDPL_BIOMOL_API const bool CHECK_LINE_LENGTH;

			extern CDPL_BIOMOL_API const ResidueDictionary::SharedPointer PDB_RESIDUE_DICTIONARY;

			extern CDPL_BIOMOL_API const bool PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES;

			extern CDPL_BIOMOL_API const bool PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES;
	
			extern CDPL_BIOMOL_API const bool PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES;

			extern CDPL_BIOMOL_API const bool PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES;

			extern CDPL_BIOMOL_API const bool PDB_IGNORE_CONECT_RECORDS;

			extern CDPL_BIOMOL_API const bool PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS;

			extern CDPL_BIOMOL_API const bool PDB_IGNORE_FORMAL_CHARGE_FIELD;

			extern CDPL_BIOMOL_API const bool PDB_APPLY_DICT_FORMAL_ATOM_CHARGES;

			extern CDPL_BIOMOL_API const bool PDB_APPLY_DICT_ATOM_TYPES;

			extern CDPL_BIOMOL_API const bool PDB_CALC_MISSING_FORMAL_CHARGES;

			extern CDPL_BIOMOL_API const bool PDB_PERCEIVE_MISSING_BOND_ORDERS;

			extern CDPL_BIOMOL_API const bool PDB_EVALUATE_MASTER_RECORD;

			extern CDPL_BIOMOL_API const bool PDB_TRUNCATE_LINES;

			extern CDPL_BIOMOL_API const bool PDB_WRITE_FORMAL_CHARGES;

			extern CDPL_BIOMOL_API const bool PDB_WRITE_CONECT_RECORDS;

			extern CDPL_BIOMOL_API const bool PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS;

			extern CDPL_BIOMOL_API const bool PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER;

			extern CDPL_BIOMOL_API const unsigned int PDB_FORMAT_VERSION;

			extern CDPL_BIOMOL_API const bool COMBINE_INTERFERING_RESIDUE_COORDINATES;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_CONTROLPARAMETERDEFAULT_HPP
