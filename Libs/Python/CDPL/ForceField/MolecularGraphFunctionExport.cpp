/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctionExport.cpp 
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

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_MOLGRAPH_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::MolecularGraph& molgraph)   \
{                                                                      \
	return CDPL::ForceField::get##FUNC_SUFFIX(molgraph);               \
}                                                                      \
                                                                       \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::MolecularGraph& molgraph)   \
{                                                                      \
	return CDPL::ForceField::has##FUNC_SUFFIX(molgraph);               \
}

#define EXPORT_MOLGRAPH_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("molgraph"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"),                              \
            python::return_value_policy<python::copy_const_reference>());                                        \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("molgraph"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"),                              \
            python::return_value_policy<python::copy_const_reference,                                            \
			python::with_custodian_and_ward_postcall<0, 1> >());                                                 \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("molgraph"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)), \
			python::with_custodian_and_ward<1, 2>());                                                            


namespace
{

	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::FragmentList::SharedPointer&, MMFF94AromaticRings)

	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, perceiveMMFF94AromaticRings, CDPL::Chem::MolecularGraph&)
}


void CDPLPythonForceField::exportMolecularGraphFunctions()
{
	using namespace boost;
	using namespace CDPL;
	
	python::def("perceiveMMFF94AromaticRings", &perceiveMMFF94AromaticRingsWrapper1, python::arg("molgraph"));
	python::def("perceiveMMFF94AromaticRings", static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&ForceField::perceiveMMFF94AromaticRings),
				(python::arg("molgraph"), python::arg("overwrite")));

	python::def("assignMMFF94AtomTypes", &ForceField::assignMMFF94AtomTypes, 
				(python::arg("molgraph"), python::arg("strict"), python::arg("overwrite")));
	python::def("assignMMFF94BondTypeIndices", &ForceField::assignMMFF94BondTypeIndices, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcMMFF94AtomCharges", &ForceField::calcMMFF94AtomCharges, 
				(python::arg("molgraph"), python::arg("overwrite")));

	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(MMFF94AromaticRings, rings)
}
