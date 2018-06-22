/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterFunctions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/ControlParameter.hpp"
#include "CDPL/Biomol/ControlParameterDefault.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


using namespace CDPL; 


#define MAKE_CONTROL_PARAM_FUNCTIONS(PARAM_NAME, TYPE, FUNC_INFIX)		\
	TYPE Biomol::get##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr) \
	{																	\
		return cntnr.getParameterOrDefault<TYPE>(ControlParameter::PARAM_NAME, \
												 ControlParameterDefault::PARAM_NAME); \
	}																	\
																		\
	void Biomol::set##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr, TYPE arg) \
	{																	\
		cntnr.setParameter(ControlParameter::PARAM_NAME, arg);			\
	}																	\
																		\
	bool Biomol::has##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr) \
	{																	\
		return cntnr.isParameterSet(ControlParameter::PARAM_NAME);		\
	}																	\
																		\
	void Biomol::clear##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr) \
	{																	\
		cntnr.removeParameter(ControlParameter::PARAM_NAME);			\
	}


MAKE_CONTROL_PARAM_FUNCTIONS(STRICT_ERROR_CHECKING, bool, StrictErrorChecking)
MAKE_CONTROL_PARAM_FUNCTIONS(CHECK_LINE_LENGTH, bool, CheckLineLength)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_RESIDUE_DICTIONARY, const Biomol::ResidueDictionary::SharedPointer&, PDBResidueDictionary)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES, bool, PDBApplyDictAtomBondingToNonStdResidues)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES, bool, PDBApplyDictAtomBondingToStdResidues)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES, bool, PDBApplyDictBondOrdersToNonStdResidues)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES, bool, PDBApplyDictBondOrdersToStdResidues)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_IGNORE_CONECT_RECORDS, bool, PDBIgnoreConectRecords)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS, bool, PDBDeduceBondOrdersFromCONECTRecords)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_IGNORE_FORMAL_CHARGE_FIELD, bool, PDBIgnoreFormalChargeField)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_APPLY_DICT_FORMAL_ATOM_CHARGES, bool, PDBApplyDictFormalAtomCharges)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_APPLY_DICT_ATOM_TYPES, bool, PDBApplyDictAtomTypes)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_CALC_MISSING_FORMAL_CHARGES, bool, PDBCalcMissingFormalCharges)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_PERCEIVE_MISSING_BOND_ORDERS, bool, PDBPerceiveMissingBondOrders)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_EVALUATE_MASTER_RECORD, bool, PDBEvaluateMASTERRecord)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_TRUNCATE_LINES, bool, PDBTruncateLines)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_WRITE_FORMAL_CHARGES, bool, PDBWriteFormalCharges)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_WRITE_CONECT_RECORDS, bool, PDBWriteCONECTRecords)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS, bool, PDBWriteCONECTRecordsForAllBonds)
MAKE_CONTROL_PARAM_FUNCTIONS(PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER, bool, PDBWriteCONECTRecordsReflectingBondOrder)
