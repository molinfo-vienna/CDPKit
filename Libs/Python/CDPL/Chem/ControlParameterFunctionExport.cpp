/* 
 * ControlParameterFunctionExport.cpp 
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
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputCanonicalForm)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputKekuleForm)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputAtomStereo)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputBondStereo)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputRingBondStereo)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(std::size_t, SMILESMinStereoBondRingSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputIsotope)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputHydrogenCount)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESMolOutputAtomMappingID)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESRxnOutputAtomMappingID)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputSingleBonds)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESOutputAromaticBonds)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, SMILESNoOrganicSubset)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CDFOutputSinglePrecisionFloats)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, INCHIInputOptions)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, INCHIOutputOptions)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MultiConfImport)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MultiConfExport)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Chem::MultiConfMoleculeInputProcessor::SharedPointer&, MultiConfInputProcessor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, ConfIndexNameSuffixPattern)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, OutputConfEnergyAsComment)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2EnableExtendedAtomTypes)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2EnableAromaticBondTypes)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2ReadPartialAsFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2CalcFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2OutputSubstructures)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MOL2OutputFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, MOL2ChargeType)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, MOL2MoleculeType)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, XYZCommentIsName)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, XYZPerceiveConnectivity)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, XYZPerceiveBondOrders)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, XYZCalcFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputXMLDeclaration)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const std::string&, CMLOutputElementNamespace)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputAtomParity)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputSingleBondStereo)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputDoubleBondStereo)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputKekuleForm)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputMoleculeName)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputStructureData)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputIsotope)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputSpinMultiplicity)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputCompactAtomData)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CMLOutputCompactBondData)
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
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputCanonicalForm, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputKekuleForm, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputAtomStereo, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputBondStereo, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputRingBondStereo, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESMinStereoBondRingSize, min_size)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputIsotope, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputHydrogenCount, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESMolOutputAtomMappingID, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESRxnOutputAtomMappingID, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputSingleBonds, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESOutputAromaticBonds, output)
    EXPORT_CONTROL_PARAM_FUNCS(SMILESNoOrganicSubset, no_subset)
    EXPORT_CONTROL_PARAM_FUNCS(CDFOutputSinglePrecisionFloats, single_prec)
    EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(INCHIInputOptions, opts)
    EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(INCHIOutputOptions, opts)
    EXPORT_CONTROL_PARAM_FUNCS(MultiConfImport, multi_conf)
    EXPORT_CONTROL_PARAM_FUNCS(MultiConfExport, multi_conf)
    EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(MultiConfInputProcessor, proc)
    EXPORT_CONTROL_PARAM_FUNCS(OutputConfEnergyAsComment, output)
    EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(ConfIndexNameSuffixPattern, pattern)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2EnableExtendedAtomTypes, enable)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2EnableAromaticBondTypes, enable)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2ReadPartialAsFormalCharges, read)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2OutputSubstructures, output)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2OutputFormalCharges, output)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2CalcFormalCharges, calc)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2ChargeType, type)
    EXPORT_CONTROL_PARAM_FUNCS(MOL2MoleculeType, type)
    EXPORT_CONTROL_PARAM_FUNCS(XYZCommentIsName, is_name)
    EXPORT_CONTROL_PARAM_FUNCS(XYZPerceiveConnectivity, perceive)
    EXPORT_CONTROL_PARAM_FUNCS(XYZPerceiveBondOrders, perceive)
    EXPORT_CONTROL_PARAM_FUNCS(XYZCalcFormalCharges, calc)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputXMLDeclaration, output)
    EXPORT_CONTROL_PARAM_FUNCS_COPY_REF(CMLOutputElementNamespace, ns)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputAtomParity, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputSingleBondStereo, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputDoubleBondStereo, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputKekuleForm, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputMoleculeName, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputStructureData, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputIsotope, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputSpinMultiplicity, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputCompactAtomData, output)
    EXPORT_CONTROL_PARAM_FUNCS(CMLOutputCompactBondData, output)
}
