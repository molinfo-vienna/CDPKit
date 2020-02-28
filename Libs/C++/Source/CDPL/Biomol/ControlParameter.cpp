/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameter.cpp 
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
#include "CDPL/Chem/StaticInit.hpp"

#include "CDPL/Base/LookupKeyDefinition.hpp"
#include "CDPL/Biomol/ControlParameter.hpp"


namespace CDPL 
{

	namespace Biomol
	{

		namespace ControlParameter
		{
		
			CDPL_DEFINE_LOOKUP_KEY(STRICT_ERROR_CHECKING);
			CDPL_DEFINE_LOOKUP_KEY(CHECK_LINE_LENGTH);
			CDPL_DEFINE_LOOKUP_KEY(PDB_RESIDUE_DICTIONARY);
			CDPL_DEFINE_LOOKUP_KEY(PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_IGNORE_CONECT_RECORDS);
			CDPL_DEFINE_LOOKUP_KEY(PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS);
			CDPL_DEFINE_LOOKUP_KEY(PDB_IGNORE_FORMAL_CHARGE_FIELD);
			CDPL_DEFINE_LOOKUP_KEY(PDB_APPLY_DICT_FORMAL_ATOM_CHARGES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_APPLY_DICT_ATOM_TYPES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_CALC_MISSING_FORMAL_CHARGES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_PERCEIVE_MISSING_BOND_ORDERS);
			CDPL_DEFINE_LOOKUP_KEY(PDB_EVALUATE_MASTER_RECORD);
			CDPL_DEFINE_LOOKUP_KEY(PDB_TRUNCATE_LINES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_WRITE_FORMAL_CHARGES);
			CDPL_DEFINE_LOOKUP_KEY(PDB_WRITE_CONECT_RECORDS);
			CDPL_DEFINE_LOOKUP_KEY(PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS);
			CDPL_DEFINE_LOOKUP_KEY(PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER);
			CDPL_DEFINE_LOOKUP_KEY(PDB_FORMAT_VERSION);

			CDPL_DEFINE_LOOKUP_KEY(COMBINE_INTERFERING_RESIDUE_COORDINATES);
		}

		void initControlParameters() {}
	}
}
