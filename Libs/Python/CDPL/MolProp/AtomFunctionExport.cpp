/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctionExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_ATOM_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
    return CDPL::MolProp::get##FUNC_SUFFIX(atom);				   \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
	return CDPL::MolProp::has##FUNC_SUFFIX(atom);                  \
}

#define EXPORT_ATOM_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("atom"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("atom"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
			python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("atom"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)),    \
			python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_ATOM_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("atom"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("atom"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)),    \
			python::with_custodian_and_ward<1, 2>());  


namespace
{

	MAKE_ATOM_FUNC_WRAPPERS(double, Hydrophobicity)
	MAKE_ATOM_FUNC_WRAPPERS(double, PEOECharge)

	MAKE_FUNCTION_WRAPPER2(double, getHybridPolarizability, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);

	MAKE_FUNCTION_WRAPPER3(double, calcEffectivePolarizability, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, double);
}


void CDPLPythonMolProp::exportAtomFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("getHybridPolarizability", &getHybridPolarizabilityWrapper2, 
				(python::arg("atom"), python::arg("molgraph")));
	python::def("calcEffectivePolarizability", &calcEffectivePolarizabilityWrapper3, 
				(python::arg("atom"), python::arg("molgraph"), python::arg("damping") = 0.75));

	EXPORT_ATOM_FUNCS(PEOECharge, charge)
	EXPORT_ATOM_FUNCS(Hydrophobicity, hyd)
}
