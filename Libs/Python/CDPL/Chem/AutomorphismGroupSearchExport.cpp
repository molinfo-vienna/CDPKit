/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AutomorphismGroupSearchExport.cpp 
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

#include "CDPL/Chem/AutomorphismGroupSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
//#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportAutomorphismGroupSearch()
{
	using namespace boost;
	using namespace CDPL;

	Chem::AtomBondMapping& (Chem::AutomorphismGroupSearch::*getMappingFunc)(std::size_t) = &Chem::AutomorphismGroupSearch::getMapping;

	python::class_<Chem::AutomorphismGroupSearch, boost::noncopyable>("AutomorphismGroupSearch", python::no_init)
		.def(python::init<unsigned int, unsigned int>((python::arg("self"), 
													   python::arg("atom_flags") = Chem::AutomorphismGroupSearch::DEF_ATOM_PROPERTY_FLAGS, 
													   python::arg("bond_flags") = Chem::AutomorphismGroupSearch::DEF_BOND_PROPERTY_FLAGS)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AutomorphismGroupSearch>())	
		.def("setAtomPropertyFlags", &Chem::AutomorphismGroupSearch::setAtomPropertyFlags, (python::arg("self"), python::arg("flags")))
		.def("getAtomPropertyFlags", &Chem::AutomorphismGroupSearch::getAtomPropertyFlags, python::arg("self"))
		.def("setBondPropertyFlags", &Chem::AutomorphismGroupSearch::setBondPropertyFlags, (python::arg("self"), python::arg("flags")))
		.def("getBondPropertyFlags", &Chem::AutomorphismGroupSearch::getBondPropertyFlags, python::arg("self"))
		.def("includeIdentityMapping", &Chem::AutomorphismGroupSearch::includeIdentityMapping, (python::arg("self"), python::arg("include")))
		.def("identityMappingIncluded", &Chem::AutomorphismGroupSearch::identityMappingIncluded, python::arg("self"))
		.def("findMappings", &Chem::AutomorphismGroupSearch::findMappings, (python::arg("self"), python::arg("molgraph")), 
			 python::with_custodian_and_ward<1, 2>())
		.def("getNumMappings", &Chem::AutomorphismGroupSearch::getNumMappings, python::arg("self"))
		.def("getMapping", getMappingFunc, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<1>())
		.def("getMaxNumMappings", &Chem::AutomorphismGroupSearch::getMaxNumMappings, python::arg("self"))
		.def("setMaxNumMappings", &Chem::AutomorphismGroupSearch::setMaxNumMappings, 
			 (python::arg("self"), python::arg("max_num_mappings")))
		.def("setFoundMappingCallback", &Chem::AutomorphismGroupSearch::setFoundMappingCallback,
			 (python::arg("self"), python::arg("func")))
		.def("getFoundMappingCallback", &Chem::AutomorphismGroupSearch::getFoundMappingCallback,
			 python::arg("self"), python::return_internal_reference<1>())
		.add_property("atomPropertyFlags", &Chem::AutomorphismGroupSearch::getAtomPropertyFlags, 
					  &Chem::AutomorphismGroupSearch::setAtomPropertyFlags)
		.add_property("bondPropertyFlags", &Chem::AutomorphismGroupSearch::getBondPropertyFlags, 
					  &Chem::AutomorphismGroupSearch::setBondPropertyFlags)
		.add_property("incIdentityMapping", &Chem::AutomorphismGroupSearch::identityMappingIncluded, 
					  &Chem::AutomorphismGroupSearch::includeIdentityMapping)
		.add_property("numMappings", &Chem::AutomorphismGroupSearch::getNumMappings)
		.add_property("maxNumMappings", &Chem::AutomorphismGroupSearch::getMaxNumMappings, 
					  &Chem::AutomorphismGroupSearch::setMaxNumMappings)
		.add_property("foundMappingCallback", python::make_function(&Chem::AutomorphismGroupSearch::getFoundMappingCallback, 
																	python::return_internal_reference<>()),
					  &Chem::AutomorphismGroupSearch::setFoundMappingCallback)
		.def("__getitem__", getMappingFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__len__", &Chem::AutomorphismGroupSearch::getNumMappings, python::arg("self"));
}
