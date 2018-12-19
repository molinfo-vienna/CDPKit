/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Biomol/ControlParameter.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct ControlParameter {};
}


void CDPLPythonBiomol::exportControlParameters()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ControlParameter, boost::noncopyable>("ControlParameter", python::no_init)
		.def_readonly("STRICT_ERROR_CHECKING", &Biomol::ControlParameter::STRICT_ERROR_CHECKING)
		.def_readonly("CHECK_LINE_LENGTH", &Biomol::ControlParameter::CHECK_LINE_LENGTH)
		.def_readonly("PDB_RESIDUE_DICTIONARY", &Biomol::ControlParameter::PDB_RESIDUE_DICTIONARY)
		.def_readonly("PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES", &Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES)
		.def_readonly("PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES", &Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES)
		.def_readonly("PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES", &Biomol::ControlParameter::PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES)
		.def_readonly("PDB_IGNORE_CONECT_RECORDS", &Biomol::ControlParameter::PDB_IGNORE_CONECT_RECORDS)
		.def_readonly("PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS", &Biomol::ControlParameter::PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS)
		.def_readonly("PDB_IGNORE_FORMAL_CHARGE_FIELD", &Biomol::ControlParameter::PDB_IGNORE_FORMAL_CHARGE_FIELD)
		.def_readonly("PDB_APPLY_DICT_FORMAL_ATOM_CHARGES", &Biomol::ControlParameter::PDB_APPLY_DICT_FORMAL_ATOM_CHARGES)
		.def_readonly("PDB_APPLY_DICT_ATOM_TYPES", &Biomol::ControlParameter::PDB_APPLY_DICT_ATOM_TYPES)
		.def_readonly("PDB_CALC_MISSING_FORMAL_CHARGES", &Biomol::ControlParameter::PDB_CALC_MISSING_FORMAL_CHARGES)
		.def_readonly("PDB_PERCEIVE_MISSING_BOND_ORDERS", &Biomol::ControlParameter::PDB_PERCEIVE_MISSING_BOND_ORDERS)
		.def_readonly("PDB_EVALUATE_MASTER_RECORD", &Biomol::ControlParameter::PDB_EVALUATE_MASTER_RECORD)
		.def_readonly("PDB_TRUNCATE_LINES", &Biomol::ControlParameter::PDB_TRUNCATE_LINES)
		.def_readonly("PDB_WRITE_FORMAL_CHARGES", &Biomol::ControlParameter::PDB_WRITE_FORMAL_CHARGES)
		.def_readonly("PDB_WRITE_CONECT_RECORDS", &Biomol::ControlParameter::PDB_WRITE_CONECT_RECORDS)
		.def_readonly("PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS", &Biomol::ControlParameter::PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS)
		.def_readonly("PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER", &Biomol::ControlParameter::PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER)
		.def_readonly("COMBINE_INTERFERING_RESIDUE_COORDINATES", &Biomol::ControlParameter::COMBINE_INTERFERING_RESIDUE_COORDINATES)
		;
}
