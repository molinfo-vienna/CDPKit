/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SubstructureHistogramCalculatorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/SubstructureHistogramCalculator.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportSubstructureHistogramCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::SubstructureHistogramCalculator, Chem::SubstructureHistogramCalculator::SharedPointer> cl("SubstructureHistogramCalculator", python::no_init);

	python::scope scope = cl;

	python::class_<Chem::SubstructureHistogramCalculator::Pattern>("Pattern", python::no_init)
		.def(python::init<const Chem::SubstructureHistogramCalculator::Pattern&>((python::arg("self"), python::arg("ptn"))))
		.def(python::init<const Chem::MolecularGraph::SharedPointer&, std::size_t, std::size_t, bool, bool>(
				 (python::arg("self"), python::arg("structure"), python::arg("id"), (python::arg("priority") = 0), 
				  (python::arg("all_matches") = true), (python::arg("unique_matches") = true))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SubstructureHistogramCalculator::Pattern>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::SubstructureHistogramCalculator::Pattern::operator=), 
			 (python::arg("self"), python::arg("ptn")), python::return_self<>())
		.def("getStructure", &Chem::SubstructureHistogramCalculator::Pattern::getStructure, python::arg("self"),  
			 python::return_value_policy<python::copy_const_reference>())
		.def("getPriority", &Chem::SubstructureHistogramCalculator::Pattern::getPriority, python::arg("self"))
		.def("getID", &Chem::SubstructureHistogramCalculator::Pattern::getID, python::arg("self"))
		.def("processAllMatches", &Chem::SubstructureHistogramCalculator::Pattern::processAllMatches, python::arg("self"))
		.def("processUniqueMatchesOnly", &Chem::SubstructureHistogramCalculator::Pattern::processUniqueMatchesOnly, python::arg("self"))
		.add_property("structure", python::make_function(&Chem::SubstructureHistogramCalculator::Pattern::getStructure, 
														 python::return_value_policy<python::copy_const_reference>()))
		.add_property("priority", &Chem::SubstructureHistogramCalculator::Pattern::getPriority)
		.add_property("id", &Chem::SubstructureHistogramCalculator::Pattern::getID)
		.add_property("allMatches", &Chem::SubstructureHistogramCalculator::Pattern::processAllMatches)
		.add_property("uniqueMatches", &Chem::SubstructureHistogramCalculator::Pattern::processUniqueMatchesOnly);

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::SubstructureHistogramCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SubstructureHistogramCalculator>())	
		.def("addPattern", 
			 static_cast<void (Chem::SubstructureHistogramCalculator::*)(const Chem::MolecularGraph::SharedPointer&, std::size_t, std::size_t, bool, bool)>(&Chem::SubstructureHistogramCalculator::addPattern), 
			 (python::arg("self"), python::arg("structure"), (python::arg("id") = 0), (python::arg("priority") = 0), 
			  (python::arg("all_matches") = true), (python::arg("unique_matches") = true)))
		.def("addPattern", 
			 static_cast<void (Chem::SubstructureHistogramCalculator::*)(const Chem::SubstructureHistogramCalculator::Pattern&)>(&Chem::SubstructureHistogramCalculator::addPattern),
			 (python::arg("self"), python::arg("ptn")))
		.def("getPattern", &Chem::SubstructureHistogramCalculator::getPattern, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("removePattern", static_cast<void (Chem::SubstructureHistogramCalculator::*)(std::size_t)>(&Chem::SubstructureHistogramCalculator::removePattern),
			 (python::arg("self"), python::arg("idx")))
		.def("clear", &Chem::SubstructureHistogramCalculator::clear, python::arg("self"))
		.def("getNumPatterns", &Chem::SubstructureHistogramCalculator::getNumPatterns, python::arg("self"))
		.def("calculate", &Chem::SubstructureHistogramCalculator::calculate<python::object>, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("histo")))
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::SubstructureHistogramCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.add_property("numPatterns", &Chem::SubstructureHistogramCalculator::getNumPatterns);
}
