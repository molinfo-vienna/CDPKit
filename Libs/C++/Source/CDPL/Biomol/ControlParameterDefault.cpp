/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterDefault.cpp 
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

#include "CDPL/Biomol/ControlParameterDefault.hpp"
#include "CDPL/Biomol/PDBFormatVersion.hpp"


namespace CDPL
{

	namespace Biomol
	{

		namespace ControlParameterDefault
		{

			const bool STRICT_ERROR_CHECKING                               = false;
			const bool CHECK_LINE_LENGTH                                   = false;
			const ResidueDictionary::SharedPointer PDB_RESIDUE_DICTIONARY  = ResidueDictionary::SharedPointer();
			const bool PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES     = false;
			const bool PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES         = true;
			const bool PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES      = true;
			const bool PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES          = true;
			const bool PDB_IGNORE_CONECT_RECORDS                           = false;
			const bool PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS          = false;
			const bool PDB_IGNORE_FORMAL_CHARGE_FIELD                      = false;
			const bool PDB_APPLY_DICT_FORMAL_ATOM_CHARGES                  = false;
			const bool PDB_APPLY_DICT_ATOM_TYPES                           = true;
			const bool PDB_CALC_MISSING_FORMAL_CHARGES                     = false;
			const bool PDB_PERCEIVE_MISSING_BOND_ORDERS                    = true;
			const bool PDB_EVALUATE_MASTER_RECORD                          = false;
			const bool PDB_TRUNCATE_LINES                                  = false;
			const bool PDB_WRITE_FORMAL_CHARGES                            = true;
			const bool PDB_WRITE_CONECT_RECORDS                            = true;
			const bool PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS              = false;
			const bool PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER      = false;
			const unsigned int PDB_FORMAT_VERSION                          = PDBFormatVersion::V3;
			const bool COMBINE_INTERFERING_RESIDUE_COORDINATES             = true;
		}

		void initControlParameterDefaults() {}
	}
}
