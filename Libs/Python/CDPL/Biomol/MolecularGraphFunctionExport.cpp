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
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_MOLGRAPH_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::MolecularGraph& molgraph)   \
{                                                                      \
	return CDPL::Biomol::get##FUNC_SUFFIX(molgraph);				   \
}                                                                      \
                                                                       \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::MolecularGraph& molgraph)   \
{                                                                      \
	return CDPL::Biomol::has##FUNC_SUFFIX(molgraph);                   \
}

#define EXPORT_MOLGRAPH_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("molgraph"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"),                              \
            python::return_value_policy<python::copy_const_reference>());                                        \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("molgraph"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"),                              \
            python::return_value_policy<python::copy_const_reference,                                            \
			python::with_custodian_and_ward_postcall<0, 1> >());                                                 \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("molgraph"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)),     \
			python::with_custodian_and_ward<1, 2>());                                                            


namespace
{

	MAKE_MOLGRAPH_FUNC_WRAPPERS(const std::string&, ResidueCode)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, ResidueSequenceNumber)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(char, ResidueInsertionCode)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(char, ChainID)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, ModelNumber)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Biomol::PDBData::SharedPointer&, PDBData)

	MAKE_FUNCTION_WRAPPER4(void, extractEnvironmentResidues, CDPL::Chem::MolecularGraph&, CDPL::Chem::MolecularGraph&, CDPL::Chem::Fragment&, double);
	MAKE_FUNCTION_WRAPPER4(void, extractProximalAtoms, CDPL::Chem::MolecularGraph&, CDPL::Chem::MolecularGraph&, CDPL::Chem::Fragment&, double);
}


void CDPLPythonBiomol::exportMolecularGraphFunctions()
{
	using namespace boost;
	using namespace CDPL;


	python::def("setHydrogenResidueSequenceInfo", &Biomol::setHydrogenResidueSequenceInfo, 
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT));
	python::def("extractEnvironmentResidues", &extractEnvironmentResiduesWrapper4, 
				(python::arg("core"), python::arg("macromol"), python::arg("env_residues"),
				 python::arg("max_dist")));
	python::def("extractProximalAtoms", &extractProximalAtomsWrapper4, 
				(python::arg("core"), python::arg("macromol"), python::arg("env_atoms"),
				 python::arg("max_dist")));

	EXPORT_MOLGRAPH_FUNCS_COPY_REF(ResidueCode, code)
	EXPORT_MOLGRAPH_FUNCS(ResidueSequenceNumber, seq_no)
	EXPORT_MOLGRAPH_FUNCS(ResidueInsertionCode, code)
	EXPORT_MOLGRAPH_FUNCS(ChainID, id)
	EXPORT_MOLGRAPH_FUNCS(ModelNumber, model_no)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(PDBData, data)
}
