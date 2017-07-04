/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SubstructureHistogramTyperExport.cpp 
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

#include "CDPL/Chem/SubstructureHistogramGenerator.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportSubstructureHistogramGenerator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::SubstructureHistogramGenerator, Chem::SubstructureHistogramGenerator::SharedPointer> cl("SubstructureHistogramGenerator", python::no_init);

	python::scope scope = cl;

	python::class_<Chem::SubstructureHistogramGenerator::Pattern>("Pattern", python::no_init)
		.def(python::init<const Chem::SubstructureHistogramGenerator::Pattern&>((python::arg("self"), python::arg("ptn"))))
		.def(python::init<const Chem::MolecularGraph::SharedPointer&, std::size_t, std::size_t, bool, bool>(
				 (python::arg("self"), python::arg("structure"), python::arg("id"), (python::arg("priority") = 0), 
				  (python::arg("all_matches") = true), (python::arg("unique_matches") = true))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SubstructureHistogramGenerator::Pattern>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::SubstructureHistogramGenerator::Pattern::operator=), 
			 (python::arg("self"), python::arg("ptn")), python::return_self<>())
		.def("getStructure", &Chem::SubstructureHistogramGenerator::Pattern::getStructure, python::arg("self"),  
			 python::return_value_policy<python::copy_const_reference>())
		.def("getPriority", &Chem::SubstructureHistogramGenerator::Pattern::getPriority, python::arg("self"))
		.def("getID", &Chem::SubstructureHistogramGenerator::Pattern::getID, python::arg("self"))
		.def("processAllMatches", &Chem::SubstructureHistogramGenerator::Pattern::processAllMatches, python::arg("self"))
		.def("processUniqueMatchesOnly", &Chem::SubstructureHistogramGenerator::Pattern::processUniqueMatchesOnly, python::arg("self"))
		.add_property("structure", python::make_function(&Chem::SubstructureHistogramGenerator::Pattern::getStructure, 
														 python::return_value_policy<python::copy_const_reference>()))
		.add_property("priority", &Chem::SubstructureHistogramGenerator::Pattern::getPriority)
		.add_property("id", &Chem::SubstructureHistogramGenerator::Pattern::getID)
		.add_property("allMatches", &Chem::SubstructureHistogramGenerator::Pattern::processAllMatches)
		.add_property("uniqueMatches", &Chem::SubstructureHistogramGenerator::Pattern::processUniqueMatchesOnly);

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::SubstructureHistogramGenerator&>((python::arg("self"), python::arg("generator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SubstructureHistogramGenerator>())	
		.def("addPattern", 
			 static_cast<void (Chem::SubstructureHistogramGenerator::*)(const Chem::MolecularGraph::SharedPointer&, std::size_t, std::size_t, bool, bool)>(&Chem::SubstructureHistogramGenerator::addPattern), 
			 (python::arg("self"), python::arg("structure"), (python::arg("id") = 0), (python::arg("priority") = 0), 
			  (python::arg("all_matches") = true), (python::arg("unique_matches") = true)))
		.def("addPattern", 
			 static_cast<void (Chem::SubstructureHistogramGenerator::*)(const Chem::SubstructureHistogramGenerator::Pattern&)>(&Chem::SubstructureHistogramGenerator::addPattern),
			 (python::arg("self"), python::arg("ptn")))
		.def("getPattern", &Chem::SubstructureHistogramGenerator::getPattern, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("removePattern", static_cast<void (Chem::SubstructureHistogramGenerator::*)(std::size_t)>(&Chem::SubstructureHistogramGenerator::removePattern),
			 (python::arg("self"), python::arg("idx")))
		.def("clear", &Chem::SubstructureHistogramGenerator::clear, python::arg("self"))
		.def("getNumPatterns", &Chem::SubstructureHistogramGenerator::getNumPatterns, python::arg("self"))
		.def("generate", &Chem::SubstructureHistogramGenerator::generate<python::object>, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("histo")))
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::SubstructureHistogramGenerator::operator=), 
			 (python::arg("self"), python::arg("generator")), python::return_self<>())
		.add_property("numPatterns", &Chem::SubstructureHistogramGenerator::getNumPatterns);
}
