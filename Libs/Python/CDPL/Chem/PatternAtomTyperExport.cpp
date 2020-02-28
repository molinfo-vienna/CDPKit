/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternAtomTyperExport.cpp 
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

#include "CDPL/Chem/PatternAtomTyper.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportPatternAtomTyper()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::PatternAtomTyper, Chem::PatternAtomTyper::SharedPointer> cl("PatternAtomTyper", python::no_init);

	python::scope scope = cl;

	python::class_<Chem::PatternAtomTyper::Pattern>("Pattern", python::no_init)
		.def(python::init<const Chem::PatternAtomTyper::Pattern&>((python::arg("self"), python::arg("ptn"))))
		.def(python::init<const Chem::MolecularGraph::SharedPointer&, std::size_t, std::size_t, bool, bool>(
				 (python::arg("self"), python::arg("structure"), (python::arg("atom_label") = 0), (python::arg("priority") = 0), 
				  (python::arg("all_matches") = true), (python::arg("unique_matches") = false))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PatternAtomTyper::Pattern>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::PatternAtomTyper::Pattern::operator=), 
			 (python::arg("self"), python::arg("ptn")), python::return_self<>())
		.def("getStructure", &Chem::PatternAtomTyper::Pattern::getStructure, python::arg("self"),  
			 python::return_value_policy<python::copy_const_reference>())
		.def("getPriority", &Chem::PatternAtomTyper::Pattern::getPriority, python::arg("self"))
		.def("getAtomLabel", &Chem::PatternAtomTyper::Pattern::getAtomLabel, python::arg("self"))
		.def("processAllMatches", &Chem::PatternAtomTyper::Pattern::processAllMatches, python::arg("self"))
		.def("processUniqueMatchesOnly", &Chem::PatternAtomTyper::Pattern::processUniqueMatchesOnly, python::arg("self"))
		.add_property("structure", python::make_function(&Chem::PatternAtomTyper::Pattern::getStructure, 
														 python::return_value_policy<python::copy_const_reference>()))
		.add_property("priority", &Chem::PatternAtomTyper::Pattern::getPriority)
		.add_property("atomLabel", &Chem::PatternAtomTyper::Pattern::getAtomLabel)
		.add_property("allMatches", &Chem::PatternAtomTyper::Pattern::processAllMatches)
		.add_property("uniqueMatches", &Chem::PatternAtomTyper::Pattern::processUniqueMatchesOnly);

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::PatternAtomTyper&>((python::arg("self"), python::arg("typer"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PatternAtomTyper>())	
		.def("addPattern", 
			 static_cast<void (Chem::PatternAtomTyper::*)(const Chem::MolecularGraph::SharedPointer&, std::size_t, std::size_t, bool, bool)>(&Chem::PatternAtomTyper::addPattern), 
			 (python::arg("self"), python::arg("structure"), (python::arg("atom_label") = 0), (python::arg("priority") = 0), 
			  (python::arg("all_matches") = true), (python::arg("unique_matches") = false)))
		.def("addPattern", 
			 static_cast<void (Chem::PatternAtomTyper::*)(const Chem::PatternAtomTyper::Pattern&)>(&Chem::PatternAtomTyper::addPattern),
			 (python::arg("self"), python::arg("ptn")))
		.def("getPattern", &Chem::PatternAtomTyper::getPattern, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("removePattern", static_cast<void (Chem::PatternAtomTyper::*)(std::size_t)>(&Chem::PatternAtomTyper::removePattern),
			 (python::arg("self"), python::arg("idx")))
		.def("clear", &Chem::PatternAtomTyper::clear, python::arg("self"))
		.def("getNumPatterns", &Chem::PatternAtomTyper::getNumPatterns, python::arg("self"))
		.def("getAtomLabel", &Chem::PatternAtomTyper::getAtomLabel, (python::arg("self"), python::arg("idx")))
		.def("getPatternIndex", &Chem::PatternAtomTyper::getPatternIndex, (python::arg("self"), python::arg("idx")))
		.def("hasAtomLabel", &Chem::PatternAtomTyper::hasAtomLabel, (python::arg("self"), python::arg("idx")))
		.def("execute", &Chem::PatternAtomTyper::execute, (python::arg("self"), python::arg("molgraph")))
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::PatternAtomTyper::operator=), 
			 (python::arg("self"), python::arg("typer")), python::return_self<>())
		.add_property("numPatterns", &Chem::PatternAtomTyper::getNumPatterns);
}
