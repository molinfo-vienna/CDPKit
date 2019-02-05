/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SubstructureSearchExport.cpp 
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

#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportSubstructureSearch()
{
	using namespace boost;
	using namespace CDPL;

	Chem::AtomBondMapping& (Chem::SubstructureSearch::*getMappingFunc)(std::size_t) = &Chem::SubstructureSearch::getMapping;

	bool (Chem::SubstructureSearch::*uniqueMappingsOnlyGetFunc)() const = &Chem::SubstructureSearch::uniqueMappingsOnly;
	void (Chem::SubstructureSearch::*uniqueMappingsOnlySetFunc)(bool) = &Chem::SubstructureSearch::uniqueMappingsOnly;

	python::class_<Chem::SubstructureSearch, boost::noncopyable>("SubstructureSearch", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("query")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SubstructureSearch>())	
		.def("setAtomMatchExpressionFunction", &Chem::SubstructureSearch::setAtomMatchExpressionFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setBondMatchExpressionFunction", &Chem::SubstructureSearch::setBondMatchExpressionFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setMolecularGraphMatchExpressionFunction", &Chem::SubstructureSearch::setMolecularGraphMatchExpressionFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("mappingExists", &Chem::SubstructureSearch::mappingExists, (python::arg("self"), python::arg("target")), 
			 python::with_custodian_and_ward<1, 2>())
		.def("findMappings", &Chem::SubstructureSearch::findMappings, (python::arg("self"), python::arg("target")), 
			 python::with_custodian_and_ward<1, 2>())
		.def("getNumMappings", &Chem::SubstructureSearch::getNumMappings, python::arg("self"))
		.def("getMapping", getMappingFunc, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<1>())
		.def("uniqueMappingsOnly", uniqueMappingsOnlySetFunc, (python::arg("self"), python::arg("unique")))
		.def("uniqueMappingsOnly", uniqueMappingsOnlyGetFunc, python::arg("self"))
		.def("getMaxNumMappings", &Chem::SubstructureSearch::getMaxNumMappings, python::arg("self"))
		.def("setMaxNumMappings", &Chem::SubstructureSearch::setMaxNumMappings, 
			 (python::arg("self"), python::arg("max_num_mappings")))
		.def("clearAtomMappingConstraints", &Chem::SubstructureSearch::clearAtomMappingConstraints, python::arg("self"))
		.def("addAtomMappingConstraint", &Chem::SubstructureSearch::addAtomMappingConstraint, 
			 (python::arg("self"), python::arg("query_atom_idx"), python::arg("target_atom_idx")))
		.def("clearBondMappingConstraints", &Chem::SubstructureSearch::clearBondMappingConstraints, python::arg("self"))
		.def("addBondMappingConstraint", &Chem::SubstructureSearch::addBondMappingConstraint, 
			 (python::arg("self"), python::arg("query_bond_idx"), python::arg("target_bond_idx")))
		.def("setQuery", &Chem::SubstructureSearch::setQuery, (python::arg("self"), python::arg("query")), 
			 python::with_custodian_and_ward<1, 2>())
		.add_property("numMappings", &Chem::SubstructureSearch::getNumMappings)
		.add_property("uniqueMappings", uniqueMappingsOnlyGetFunc, uniqueMappingsOnlySetFunc)
		.add_property("maxNumMappings", &Chem::SubstructureSearch::getMaxNumMappings, 
					  &Chem::SubstructureSearch::setMaxNumMappings)
		.def("__getitem__", getMappingFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__len__", &Chem::SubstructureSearch::getNumMappings, python::arg("self"))
		.def("__nonzero__", &Chem::SubstructureSearch::mappingExists, python::arg("self"))
		.def("__bool__", &Chem::SubstructureSearch::mappingExists, python::arg("self"));
}
