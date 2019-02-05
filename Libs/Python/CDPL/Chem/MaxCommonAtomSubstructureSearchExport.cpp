/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MaxCommonAtomSubstructureSearchExport.cpp 
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

#include "CDPL/Chem/MaxCommonAtomSubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportMaxCommonAtomSubstructureSearch()
{
	using namespace boost;
	using namespace CDPL;

	Chem::AtomBondMapping& (Chem::MaxCommonAtomSubstructureSearch::*getMappingFunc)(std::size_t) = &Chem::MaxCommonAtomSubstructureSearch::getMapping;

	bool (Chem::MaxCommonAtomSubstructureSearch::*uniqueMappingsOnlyGetFunc)() const = &Chem::MaxCommonAtomSubstructureSearch::uniqueMappingsOnly;
	void (Chem::MaxCommonAtomSubstructureSearch::*uniqueMappingsOnlySetFunc)(bool) = &Chem::MaxCommonAtomSubstructureSearch::uniqueMappingsOnly;

	python::class_<Chem::MaxCommonAtomSubstructureSearch, 
		boost::noncopyable>("MaxCommonAtomSubstructureSearch", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("query")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MaxCommonAtomSubstructureSearch>())	
		.def("mappingExists", &Chem::MaxCommonAtomSubstructureSearch::mappingExists, 
			 (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
		.def("findAllMappings", &Chem::MaxCommonAtomSubstructureSearch::findAllMappings, 
			 (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
		.def("findMaxBondMappings", &Chem::MaxCommonAtomSubstructureSearch::findMaxBondMappings, 
			 (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
		.def("getNumMappings", &Chem::MaxCommonAtomSubstructureSearch::getNumMappings, python::arg("self"))
		.def("getMapping", getMappingFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("uniqueMappingsOnly", uniqueMappingsOnlySetFunc, (python::arg("self"), python::arg("unique")))
		.def("uniqueMappingsOnly", uniqueMappingsOnlyGetFunc, python::arg("self"))
		.def("getMaxNumMappings", &Chem::MaxCommonAtomSubstructureSearch::getMaxNumMappings, python::arg("self"))
		.def("setMaxNumMappings", &Chem::MaxCommonAtomSubstructureSearch::setMaxNumMappings, 
			 (python::arg("self"), python::arg("max_num_mappings")))
		.def("getMinSubstructureSize", &Chem::MaxCommonAtomSubstructureSearch::getMinSubstructureSize, 
			 python::arg("self"))
		.def("setMinSubstructureSize", &Chem::MaxCommonAtomSubstructureSearch::setMinSubstructureSize, 
			 (python::arg("self"), python::arg("min_size")))
		.def("setQuery", &Chem::MaxCommonAtomSubstructureSearch::setQuery, 
			 (python::arg("self"), python::arg("query")), python::with_custodian_and_ward<1, 2>())
		.add_property("numMappings", &Chem::MaxCommonAtomSubstructureSearch::getNumMappings)
		.add_property("uniqueMappings", uniqueMappingsOnlyGetFunc, uniqueMappingsOnlySetFunc)
		.add_property("maxNumMappings", &Chem::MaxCommonAtomSubstructureSearch::getMaxNumMappings, 
					  &Chem::MaxCommonAtomSubstructureSearch::setMaxNumMappings)
		.add_property("minSubstructureSize", &Chem::MaxCommonAtomSubstructureSearch::getMinSubstructureSize, 
					  &Chem::MaxCommonAtomSubstructureSearch::setMinSubstructureSize)
		.def("__getitem__", getMappingFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__len__", &Chem::MaxCommonAtomSubstructureSearch::getNumMappings, python::arg("self"))
		.def("__nonzero__", &Chem::MaxCommonAtomSubstructureSearch::mappingExists, python::arg("self"))
		.def("__bool__", &Chem::MaxCommonAtomSubstructureSearch::mappingExists, python::arg("self"));
}
