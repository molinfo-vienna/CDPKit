/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondFunctionExport.cpp 
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

#include "CDPL/MolProp/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_BOND_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond)             \
{                                                                  \
	return CDPL::MolProp::get##FUNC_SUFFIX(bond);				   \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond)             \
{                                                                  \
	return CDPL::MolProp::has##FUNC_SUFFIX(bond);                  \
}

#define EXPORT_BOND_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("bond"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 

#define EXPORT_BOND_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("bond"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 

#define EXPORT_BOND_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
			python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("bond"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME)),    \
			python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_BOND_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("bond"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME)),    \
			python::with_custodian_and_ward<1, 2>());  


namespace
{

	MAKE_FUNCTION_WRAPPER1(bool, isHydrogenBond, CDPL::Chem::Bond&)

	MAKE_FUNCTION_WRAPPER2(bool, isInRing, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getNumContainingSSSRRings, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(bool, isHydrogenRotor, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(bool, isHeteroAtomHydrogenRotor, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);

	MAKE_FUNCTION_WRAPPER3(double, calcPolarizability, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, double);
	MAKE_FUNCTION_WRAPPER3(bool, isInRingOfSize, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, std::size_t);

	MAKE_FUNCTION_WRAPPER4(bool, isAmideBond, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, bool, bool);

	MAKE_FUNCTION_WRAPPER5(bool, isRotatable, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, bool, bool, bool);

	MAKE_BOND_FUNC_WRAPPERS(double, MHMOPiOrder)
}


void CDPLPythonMolProp::exportBondFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("isHydrogenBond", &isHydrogenBondWrapper1, python::arg("bond"));

	python::def("isInRing", &isInRingWrapper2, (python::arg("bond"), python::arg("molgraph")));
	python::def("isHydrogenRotor", &isHydrogenRotorWrapper2, (python::arg("bond"), python::arg("molgraph")));
	python::def("isHeteroAtomHydrogenRotor", &isHeteroAtomHydrogenRotorWrapper2,
				(python::arg("bond"), python::arg("molgraph")));
	python::def("getNumContainingSSSRRings", &getNumContainingSSSRRingsWrapper2, 
				(python::arg("bond"), python::arg("molgraph")));

	python::def("calcPolarizability", &calcPolarizabilityWrapper3, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("damping") = 0.75));
	python::def("isInRingOfSize", &isInRingOfSizeWrapper3,
				(python::arg("bond"), python::arg("molgraph"), python::arg("size")));

	python::def("isAmideBond", &isAmideBondWrapper4, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("c_only") = false, python::arg("db_o_only") = false));

	python::def("isRotatable", &isRotatableWrapper5, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("h_rotors"), python::arg("ring_bonds"), python::arg("amide_bonds")));

	EXPORT_BOND_FUNCS(MHMOPiOrder, order)
}
