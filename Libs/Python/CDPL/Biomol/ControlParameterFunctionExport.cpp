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
#include "CDPL/Biomol/ControlParameterFunctions.hpp"

#include "FunctionExports.hpp"


#define MAKE_CONTROL_PARAM_FUNC_WRAPPERS(TYPE, FUNC_INFIX)                           \
TYPE get##FUNC_INFIX##ParameterWrapper(CDPL::Base::ControlParameterContainer& cntnr) \
{                                                                                    \
    return CDPL::Biomol::get##FUNC_INFIX##Parameter(cntnr);                          \
}                                                                                    \
                                                                                     \
bool has##FUNC_INFIX##ParameterWrapper(CDPL::Base::ControlParameterContainer& cntnr) \
{                                                                                    \
    return CDPL::Biomol::has##FUNC_INFIX##Parameter(cntnr);                          \
}

#define EXPORT_CONTROL_PARAM_FUNCS(FUNC_INFIX, ARG_NAME)                                                                          \
python::def("get"#FUNC_INFIX"Parameter", &get##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("has"#FUNC_INFIX"Parameter", &has##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("clear"#FUNC_INFIX"Parameter", &Biomol::clear##FUNC_INFIX##Parameter, python::arg("cntnr"));                          \
python::def("set"#FUNC_INFIX"Parameter", &Biomol::set##FUNC_INFIX##Parameter, (python::arg("cntnr"), python::arg(#ARG_NAME))); 

#define EXPORT_CONTROL_PARAM_FUNCS_INT_REF(FUNC_INFIX, ARG_NAME)                                                                  \
python::def("get"#FUNC_INFIX"Parameter", &get##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"),                                \
            python::return_internal_reference<1>());                                                                              \
python::def("has"#FUNC_INFIX"Parameter", &has##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("clear"#FUNC_INFIX"Parameter", &Biomol::clear##FUNC_INFIX##Parameter, python::arg("cntnr"));                          \
python::def("set"#FUNC_INFIX"Parameter", &Biomol::set##FUNC_INFIX##Parameter, (python::arg("cntnr"), python::arg(#ARG_NAME))); 


namespace
{

    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, StrictErrorChecking)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CheckLineLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Biomol::ResidueDictionary::SharedPointer&, ResidueDictionary)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ApplyDictFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ApplyDictAtomTypes)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CalcMissingFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PerceiveMissingBondOrders)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, CombineInterferingResidueCoordinates)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBApplyDictAtomBondingToNonStdResidues)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBApplyDictAtomBondingToStdResidues)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBApplyDictBondOrdersToNonStdResidues)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBApplyDictBondOrdersToStdResidues)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBIgnoreConectRecords)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBDeduceBondOrdersFromCONECTRecords)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBIgnoreFormalChargeField)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBEvaluateMASTERRecord)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBTruncateLines)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBWriteFormalCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBWriteCONECTRecords)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBWriteCONECTRecordsForAllBonds)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, PDBWriteCONECTRecordsReflectingBondOrder)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, PDBFormatVersion)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MMCIFApplyDictAtomBonding)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, MMCIFApplyDictBondOrders)
}


void CDPLPythonBiomol::exportControlParameterFunctions()
{
    using namespace boost;
    using namespace CDPL;

    EXPORT_CONTROL_PARAM_FUNCS(StrictErrorChecking, strict)
    EXPORT_CONTROL_PARAM_FUNCS(CheckLineLength, check)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ResidueDictionary, dict)
    EXPORT_CONTROL_PARAM_FUNCS(ApplyDictFormalCharges, apply)
    EXPORT_CONTROL_PARAM_FUNCS(ApplyDictAtomTypes, apply)
    EXPORT_CONTROL_PARAM_FUNCS(CalcMissingFormalCharges, calc)
    EXPORT_CONTROL_PARAM_FUNCS(PerceiveMissingBondOrders, perceive)
    EXPORT_CONTROL_PARAM_FUNCS(CombineInterferingResidueCoordinates, comb)
    EXPORT_CONTROL_PARAM_FUNCS(PDBApplyDictAtomBondingToNonStdResidues, apply)
    EXPORT_CONTROL_PARAM_FUNCS(PDBApplyDictAtomBondingToStdResidues, apply)
    EXPORT_CONTROL_PARAM_FUNCS(PDBApplyDictBondOrdersToNonStdResidues, apply)
    EXPORT_CONTROL_PARAM_FUNCS(PDBApplyDictBondOrdersToStdResidues, apply)
    EXPORT_CONTROL_PARAM_FUNCS(PDBIgnoreConectRecords, ignore)
    EXPORT_CONTROL_PARAM_FUNCS(PDBDeduceBondOrdersFromCONECTRecords, deduce)
    EXPORT_CONTROL_PARAM_FUNCS(PDBIgnoreFormalChargeField, ignore)
    EXPORT_CONTROL_PARAM_FUNCS(PDBEvaluateMASTERRecord, evaluate)
    EXPORT_CONTROL_PARAM_FUNCS(PDBTruncateLines, trunc)
    EXPORT_CONTROL_PARAM_FUNCS(PDBWriteFormalCharges, write)
    EXPORT_CONTROL_PARAM_FUNCS(PDBWriteCONECTRecords, write)
    EXPORT_CONTROL_PARAM_FUNCS(PDBWriteCONECTRecordsForAllBonds, write)
    EXPORT_CONTROL_PARAM_FUNCS(PDBWriteCONECTRecordsReflectingBondOrder, write)
    EXPORT_CONTROL_PARAM_FUNCS(PDBFormatVersion, ver)
    EXPORT_CONTROL_PARAM_FUNCS(MMCIFApplyDictAtomBonding, apply)
    EXPORT_CONTROL_PARAM_FUNCS(MMCIFApplyDictBondOrders, apply)
}
