/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterFunctionExport.cpp 
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

#include "CDPL/Base/ControlParameterContainer.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"

#include "FunctionExports.hpp"


#define MAKE_CONTROL_PARAM_FUNC_WRAPPERS(TYPE, FUNC_INFIX)                           \
TYPE get##FUNC_INFIX##ParameterWrapper(CDPL::Base::ControlParameterContainer& cntnr) \
{                                                                                    \
	return CDPL::Chem::get##FUNC_INFIX##Parameter(cntnr);                            \
}                                                                                    \
                                                                                     \
bool has##FUNC_INFIX##ParameterWrapper(CDPL::Base::ControlParameterContainer& cntnr) \
{                                                                                    \
	return CDPL::Chem::has##FUNC_INFIX##Parameter(cntnr);                            \
}

#define EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(FUNC_INFIX, ARG_NAME)                                                                 \
python::def("get"#FUNC_INFIX"Parameter", &get##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"),                                \
            python::return_value_policy<python::copy_const_reference>());                                                         \
python::def("has"#FUNC_INFIX"Parameter", &has##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("clear"#FUNC_INFIX"Parameter", &CDPL::Chem::clear##FUNC_INFIX##Parameter, python::arg("cntnr"));                      \
python::def("set"#FUNC_INFIX"Parameter", &CDPL::Chem::set##FUNC_INFIX##Parameter, (python::arg("cntnr"), python::arg(#ARG_NAME))); 

#define EXPORT_CONTROL_PARAM_FUNCS(FUNC_INFIX, ARG_NAME)                                                                          \
python::def("get"#FUNC_INFIX"Parameter", &get##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("has"#FUNC_INFIX"Parameter", &has##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("clear"#FUNC_INFIX"Parameter", &Chem::clear##FUNC_INFIX##Parameter, python::arg("cntnr"));                            \
python::def("set"#FUNC_INFIX"Parameter", &Chem::set##FUNC_INFIX##Parameter, (python::arg("cntnr"), python::arg(#ARG_NAME))); 


namespace
{

	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, OrdinaryHydrogenDeplete)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(std::size_t, CoordinatesDimension)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, StrictErrorChecking)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, RecordSeparator)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, BondMemberSwapStereoFix)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CheckLineLength)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, MDLCTABVersion)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLIgnoreParity)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLUpdateTimestamp)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLTrimStrings)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLTrimLines)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLTruncateStrings)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLTruncateLines)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, MDLRXNFileVersion)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, SMILESRecordFormat)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, JMESeparateComponents)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLOutputConfEnergyToEnergyField)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MDLOutputConfEnergyAsSDEntry)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, MDLConfEnergySDTag)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteCanonicalForm)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteKekuleForm)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteAtomStereo)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteBondStereo)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteRingBondStereo)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(std::size_t, SMILESMinStereoBondRingSize)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteIsotope)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESMolWriteAtomMappingID)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESRxnWriteAtomMappingID)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteSingleBonds)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESWriteAromaticBonds)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESNoOrganicSubset)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CDFWriteSinglePrecisionFloats)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, INCHIInputOptions)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, INCHIOutputOptions)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MultiConfImport)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MultiConfExport)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Chem::MultiConfMoleculeInputProcessor::SharedPointer&, MultiConfInputProcessor)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, OutputConfEnergyAsComment)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2EnableExtendedAtomTypes)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2EnableAromaticBondTypes)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2CalcFormalCharges)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2OutputSubstructures)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, MOL2ChargeType)
	MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, MOL2MoleculeType)
}


void CDPLPythonChem::exportControlParameterFunctions()
{
	using namespace boost;
	using namespace CDPL;

	EXPORT_CONTROL_PARAM_FUNCS(OrdinaryHydrogenDeplete, deplete)
	EXPORT_CONTROL_PARAM_FUNCS(CoordinatesDimension, dim)
	EXPORT_CONTROL_PARAM_FUNCS(StrictErrorChecking, strict)
	EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(RecordSeparator, sep)
	EXPORT_CONTROL_PARAM_FUNCS(BondMemberSwapStereoFix, fix)
	EXPORT_CONTROL_PARAM_FUNCS(CheckLineLength, check)
	EXPORT_CONTROL_PARAM_FUNCS(MDLCTABVersion, version)
	EXPORT_CONTROL_PARAM_FUNCS(MDLIgnoreParity, ignore)
	EXPORT_CONTROL_PARAM_FUNCS(MDLUpdateTimestamp, update)
	EXPORT_CONTROL_PARAM_FUNCS(MDLTrimStrings, trim)
	EXPORT_CONTROL_PARAM_FUNCS(MDLTrimLines, trim)
	EXPORT_CONTROL_PARAM_FUNCS(MDLTruncateStrings, trunc)
	EXPORT_CONTROL_PARAM_FUNCS(MDLTruncateLines, trunc)
	EXPORT_CONTROL_PARAM_FUNCS(MDLRXNFileVersion, version)
	EXPORT_CONTROL_PARAM_FUNCS(MDLOutputConfEnergyToEnergyField, output)
	EXPORT_CONTROL_PARAM_FUNCS(MDLOutputConfEnergyAsSDEntry, output)
	EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(MDLConfEnergySDTag, tag)
	EXPORT_CONTROL_PARAM_FUNCS(JMESeparateComponents, separate)
	EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(SMILESRecordFormat, format)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteCanonicalForm, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteKekuleForm, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteAtomStereo, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteBondStereo, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteRingBondStereo, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESMinStereoBondRingSize, min_size)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteIsotope, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESMolWriteAtomMappingID, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESRxnWriteAtomMappingID, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteSingleBonds, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESWriteAromaticBonds, write)
	EXPORT_CONTROL_PARAM_FUNCS(SMILESNoOrganicSubset, no_subset)
	EXPORT_CONTROL_PARAM_FUNCS(CDFWriteSinglePrecisionFloats, single_prec)
	EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(INCHIInputOptions, opts)
	EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(INCHIOutputOptions, opts)
	EXPORT_CONTROL_PARAM_FUNCS(MultiConfImport, multi_conf)
	EXPORT_CONTROL_PARAM_FUNCS(MultiConfExport, multi_conf)
	EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(MultiConfInputProcessor, proc)
	EXPORT_CONTROL_PARAM_FUNCS(OutputConfEnergyAsComment, output)
	EXPORT_CONTROL_PARAM_FUNCS(MOL2EnableExtendedAtomTypes, enable)
	EXPORT_CONTROL_PARAM_FUNCS(MOL2EnableAromaticBondTypes, enable)
	EXPORT_CONTROL_PARAM_FUNCS(MOL2OutputSubstructures, output)
	EXPORT_CONTROL_PARAM_FUNCS(MOL2CalcFormalCharges, calc)
	EXPORT_CONTROL_PARAM_FUNCS(MOL2ChargeType, type)
	EXPORT_CONTROL_PARAM_FUNCS(MOL2MoleculeType, type)
}
