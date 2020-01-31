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

#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/ControlParameter.hpp"
#include "CDPL/Chem/ControlParameterDefault.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


using namespace CDPL; 


#define MAKE_CONTROL_PARAM_FUNCTIONS(PARAM_NAME, TYPE, FUNC_INFIX)		\
	TYPE Chem::get##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr)	\
	{																	\
		return cntnr.getParameterOrDefault<TYPE>(ControlParameter::PARAM_NAME, \
												 ControlParameterDefault::PARAM_NAME); \
	}																	\
																		\
	void Chem::set##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr, TYPE arg) \
	{																	\
		cntnr.setParameter(ControlParameter::PARAM_NAME, arg);			\
	}																	\
																		\
	bool Chem::has##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr)	\
	{																	\
		return cntnr.isParameterSet(ControlParameter::PARAM_NAME);		\
	}																	\
																		\
	void Chem::clear##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr)	\
	{																	\
		cntnr.removeParameter(ControlParameter::PARAM_NAME);			\
	}


MAKE_CONTROL_PARAM_FUNCTIONS(ORDINARY_HYDROGEN_DEPLETE, bool, OrdinaryHydrogenDeplete)
MAKE_CONTROL_PARAM_FUNCTIONS(COORDINATES_DIMENSION, std::size_t, CoordinatesDimension)
MAKE_CONTROL_PARAM_FUNCTIONS(STRICT_ERROR_CHECKING, bool, StrictErrorChecking)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_SEPARATOR, const std::string&, RecordSeparator)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_MEMBER_SWAP_STEREO_FIX, bool, BondMemberSwapStereoFix)
MAKE_CONTROL_PARAM_FUNCTIONS(CHECK_LINE_LENGTH, bool, CheckLineLength)

MAKE_CONTROL_PARAM_FUNCTIONS(MDL_CTAB_VERSION, unsigned int, MDLCTABVersion)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_IGNORE_PARITY, bool, MDLIgnoreParity)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_UPDATE_TIMESTAMP, bool, MDLUpdateTimestamp)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_TRIM_STRINGS, bool, MDLTrimStrings)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_TRIM_LINES, bool, MDLTrimLines)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_TRUNCATE_STRINGS, bool, MDLTruncateStrings)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_TRUNCATE_LINES, bool, MDLTruncateLines)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_RXN_FILE_VERSION, unsigned int, MDLRXNFileVersion)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD, bool, MDLOutputConfEnergyToEnergyField)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY, bool, MDLOutputConfEnergyAsSDEntry)
MAKE_CONTROL_PARAM_FUNCTIONS(MDL_CONF_ENERGY_SD_TAG, const std::string&, MDLConfEnergySDTag)

MAKE_CONTROL_PARAM_FUNCTIONS(JME_SEPARATE_COMPONENTS, bool, JMESeparateComponents)

MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_RECORD_FORMAT, const std::string&, SMILESRecordFormat)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_CANONICAL_FORM, bool, SMILESWriteCanonicalForm)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_KEKULE_FORM, bool, SMILESWriteKekuleForm)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_ATOM_STEREO, bool, SMILESWriteAtomStereo)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_BOND_STEREO, bool, SMILESWriteBondStereo)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_RING_BOND_STEREO, bool, SMILESWriteRingBondStereo)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_MIN_STEREO_BOND_RING_SIZE, std::size_t, SMILESMinStereoBondRingSize)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_ISOTOPE, bool, SMILESWriteIsotope)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_MOL_WRITE_ATOM_MAPPING_ID, bool, SMILESMolWriteAtomMappingID)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_RXN_WRITE_ATOM_MAPPING_ID, bool, SMILESRxnWriteAtomMappingID)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_SINGLE_BONDS, bool, SMILESWriteSingleBonds)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_WRITE_AROMATIC_BONDS, bool, SMILESWriteAromaticBonds)
MAKE_CONTROL_PARAM_FUNCTIONS(SMILES_NO_ORGANIC_SUBSET, bool, SMILESNoOrganicSubset)

MAKE_CONTROL_PARAM_FUNCTIONS(INCHI_INPUT_OPTIONS, const std::string&, INCHIInputOptions)
MAKE_CONTROL_PARAM_FUNCTIONS(INCHI_OUTPUT_OPTIONS, const std::string&, INCHIOutputOptions)

MAKE_CONTROL_PARAM_FUNCTIONS(MULTI_CONF_IMPORT, bool, MultiConfImport)
MAKE_CONTROL_PARAM_FUNCTIONS(MULTI_CONF_EXPORT, bool, MultiConfExport)
MAKE_CONTROL_PARAM_FUNCTIONS(MULTI_CONF_INPUT_PROCESSOR, const Chem::MultiConfMoleculeInputProcessor::SharedPointer&, MultiConfInputProcessor)
MAKE_CONTROL_PARAM_FUNCTIONS(OUTPUT_CONF_ENERGY_AS_COMMENT, bool, OutputConfEnergyAsComment)

MAKE_CONTROL_PARAM_FUNCTIONS(CDF_WRITE_SINGLE_PRECISION_FLOATS, bool, CDFWriteSinglePrecisionFloats)

MAKE_CONTROL_PARAM_FUNCTIONS(MOL2_ENABLE_EXTENDED_ATOM_TYPES, bool, MOL2EnableExtendedAtomTypes)
MAKE_CONTROL_PARAM_FUNCTIONS(MOL2_ENABLE_AROMATIC_BOND_TYPES, bool, MOL2EnableAromaticBondTypes)
MAKE_CONTROL_PARAM_FUNCTIONS(MOL2_CALC_FORMAL_CHARGES, bool, MOL2CalcFormalCharges)
MAKE_CONTROL_PARAM_FUNCTIONS(MOL2_OUTPUT_SUBSTRUCTURES, bool, MOL2OutputSubstructures)
MAKE_CONTROL_PARAM_FUNCTIONS(MOL2_CHARGE_TYPE, unsigned int, MOL2ChargeType)
MAKE_CONTROL_PARAM_FUNCTIONS(MOL2_MOLECULE_TYPE, unsigned int, MOL2MoleculeType)
