/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctionExport.cpp 
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

#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "FunctionExports.hpp"


namespace
{

	bool containsFragmentWithBond(const CDPL::Chem::FragmentList& frag_list, CDPL::Chem::Bond& bond)
	{
		return CDPL::Chem::containsFragmentWithBond(frag_list, bond);
	}
}


void CDPLPythonChem::exportUtilityFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("parseSMARTS", static_cast<Chem::Molecule::SharedPointer (*)(const std::string&, bool)>(&Chem::parseSMARTS), 
				(python::arg("smarts"), python::arg("init_qry") = true));
	python::def("parseSMARTS", static_cast<bool (*)(const std::string&, Chem::Molecule&, bool)>(&Chem::parseSMARTS), 
				(python::arg("smarts"), python::arg("mol"), python::arg("init_qry") = true));
	python::def("parseSMILES", static_cast<Chem::Molecule::SharedPointer (*)(const std::string&)>(&Chem::parseSMILES), 
				python::arg("smiles"));
	python::def("parseSMILES", static_cast<bool (*)(const std::string&, Chem::Molecule&)>(&Chem::parseSMILES), 
				(python::arg("smiles"), python::arg("mol")));
	python::def("extendBoundingBox", &Chem::extendBoundingBox, (python::arg("min"), python::arg("max"), python::arg("coords"), python::arg("reset") = false));
	python::def("insideBoundingBox", &Chem::insideBoundingBox, (python::arg("min"), python::arg("max"), python::arg("coords")));
	python::def("isAromatic", &Chem::isAromatic, (python::arg("ring"), python::arg("molgraph"), python::arg("arom_bond_mask")));
	python::def("isNotAromatic", &Chem::isNotAromatic, (python::arg("ring"), python::arg("molgraph")));
	python::def("containsFragmentWithBond", &containsFragmentWithBond, (python::arg("frag_list"), python::arg("bond")));
	python::def("containsFragmentWithMinSize", &Chem::containsFragmentWithMinSize, (python::arg("frag_list"), python::arg("min_size")));
	python::def("atomTypesMatch", &Chem::atomTypesMatch, (python::arg("qry_type"), python::arg("tgt_type")));
	python::def("sybylToAtomType", &Chem::sybylToAtomType, python::arg("sybyl_type"));
}
