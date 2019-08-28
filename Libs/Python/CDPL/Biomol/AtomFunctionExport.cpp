/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctionExport.cpp 
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

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"

#include "FunctionExports.hpp"


#define MAKE_ATOM_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
	return CDPL::Biomol::get##FUNC_SUFFIX(atom);				   \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
	return CDPL::Biomol::has##FUNC_SUFFIX(atom);                   \
}

#define EXPORT_ATOM_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("atom"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("atom"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
			python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("atom"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)),     \
			python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_ATOM_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("atom"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("atom"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)),     \
			python::with_custodian_and_ward<1, 2>());  


namespace
{

	MAKE_ATOM_FUNC_WRAPPERS(bool, ResidueLeavingAtomFlag)
	MAKE_ATOM_FUNC_WRAPPERS(bool, ResidueLinkingAtomFlag)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, ResidueAtomName)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, ResidueAltAtomName)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, ResidueCode)
	MAKE_ATOM_FUNC_WRAPPERS(bool, HeteroAtomFlag)
	MAKE_ATOM_FUNC_WRAPPERS(long, ResidueSequenceNumber)
	MAKE_ATOM_FUNC_WRAPPERS(char, ResidueInsertionCode)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, ChainID)
	MAKE_ATOM_FUNC_WRAPPERS(char, AltLocationID)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, ModelNumber)
	MAKE_ATOM_FUNC_WRAPPERS(long, SerialNumber)
	MAKE_ATOM_FUNC_WRAPPERS(double, Occupancy)
	MAKE_ATOM_FUNC_WRAPPERS(double, BFactor)
}


void CDPLPythonBiomol::exportAtomFunctions()
{
	using namespace boost;
	using namespace CDPL;
	
	EXPORT_ATOM_FUNCS(ResidueLinkingAtomFlag, linking)
	EXPORT_ATOM_FUNCS(ResidueLeavingAtomFlag, leaving)
	EXPORT_ATOM_FUNCS_COPY_REF(ResidueAtomName, name)
	EXPORT_ATOM_FUNCS_COPY_REF(ResidueAltAtomName, name)
	EXPORT_ATOM_FUNCS_COPY_REF(ResidueCode, code)
	EXPORT_ATOM_FUNCS(ResidueSequenceNumber, seq_no)
	EXPORT_ATOM_FUNCS(ResidueInsertionCode, code)
	EXPORT_ATOM_FUNCS(HeteroAtomFlag, is_het)
	EXPORT_ATOM_FUNCS_COPY_REF(ChainID, id)
	EXPORT_ATOM_FUNCS(AltLocationID, id)
	EXPORT_ATOM_FUNCS(ModelNumber, model_no)
	EXPORT_ATOM_FUNCS(SerialNumber, serial_no)
	EXPORT_ATOM_FUNCS(Occupancy, occupancy)
	EXPORT_ATOM_FUNCS(BFactor, factor)
}
