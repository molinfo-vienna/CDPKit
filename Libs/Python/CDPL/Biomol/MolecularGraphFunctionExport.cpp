/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctionExport.cpp 
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

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Fragment.hpp"

#include "FunctionExports.hpp"


#define EXPORT_MOLGRAPH_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &Biomol::get##FUNC_SUFFIX, python::arg("molgraph"));                              \
python::def("has"#FUNC_SUFFIX, &Biomol::has##FUNC_SUFFIX, python::arg("molgraph"));                              \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("molgraph"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &Biomol::get##FUNC_SUFFIX, python::arg("molgraph"),                               \
            python::return_value_policy<python::copy_const_reference>());                                        \
python::def("has"#FUNC_SUFFIX, &Biomol::has##FUNC_SUFFIX, python::arg("molgraph"));                              \
python::def("clear"#FUNC_SUFFIX, &Biomol::clear##FUNC_SUFFIX, python::arg("molgraph"));                          \
python::def("set"#FUNC_SUFFIX, &Biomol::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 


void CDPLPythonBiomol::exportMolecularGraphFunctions()
{
	using namespace boost;
	using namespace CDPL;

	EXPORT_MOLGRAPH_FUNCS_COPY_REF(ResidueCode, code)
	EXPORT_MOLGRAPH_FUNCS(ResidueSequenceNumber, seq_no)
	EXPORT_MOLGRAPH_FUNCS(ResidueInsertionCode, code)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(ChainID, id)
	EXPORT_MOLGRAPH_FUNCS(ModelNumber, model_no)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(PDBData, data)

	python::def("convertMOL2ToPDBResidueInfo", &Biomol::convertMOL2ToPDBResidueInfo, (python::arg("molgraph"), python::arg("override")));
	python::def("extractResidueSubstructures", &Biomol::extractResidueSubstructures,
				(python::arg("molgraph"), python::arg("parent_molgraph"), python::arg("res_substructs"), 
				 python::arg("cnctd_only") = false, python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT,
				 python::arg("append") = false));
	python::def("extractProximalAtoms", static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Chem::Fragment&, 
															 double, bool, bool)>(&Biomol::extractProximalAtoms), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_atoms"),
				 python::arg("max_dist"), python::arg("inc_core_atoms") = false, python::arg("append") = false));
	python::def("extractProximalAtoms", static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Chem::Fragment&, 
															 const Chem::Atom3DCoordinatesFunction&, double, bool, bool)>(&Biomol::extractProximalAtoms), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_atoms"),
				 python::arg("coords_func"), python::arg("max_dist"), python::arg("inc_core_atoms") = false, python::arg("append") = false));
	python::def("extractEnvironmentResidues",
				static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&,
									 Chem::Fragment&, double, bool)>(&Biomol::extractEnvironmentResidues), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_residues"),
				 python::arg("max_dist"), python::arg("append") = false));
	python::def("extractEnvironmentResidues",
				static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&,
									 Chem::Fragment&, const Chem::Atom3DCoordinatesFunction&, double, bool)>(&Biomol::extractEnvironmentResidues), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_residues"),
				 python::arg("coords_func"), python::arg("max_dist"), python::arg("append") = false));
	python::def("setHydrogenResidueSequenceInfo", &Biomol::setHydrogenResidueSequenceInfo, 
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT));
	python::def("matchesResidueInfo", &Biomol::matchesResidueInfo, 
				(python::arg("molgraph"), python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0));
}
