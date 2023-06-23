/* 
 * ScreeningProcessorExport.cpp 
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

#include "CDPL/Shape/ScreeningProcessor.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportScreeningProcessor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::ScreeningProcessor, Shape::ScreeningProcessor::SharedPointer, boost::noncopyable>("ScreeningProcessor", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("query")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ScreeningProcessor>())
		.def("setHitCallback", &Shape::ScreeningProcessor::setHitCallback,
			 (python::arg("self"), python::arg("func")))
		.def("getHitCallback", &Shape::ScreeningProcessor::getHitCallback,
			 python::arg("self"), python::return_internal_reference<>())
		.def("getSettings", 
			 static_cast<Shape::ScreeningSettings& (Shape::ScreeningProcessor::*)()>
			 (&Shape::ScreeningProcessor::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.def("clearQuerySet", &Shape::ScreeningProcessor::clearQuerySet,
			 python::arg("self"))
		.def("addQuery", &Shape::ScreeningProcessor::addQuery,
			 (python::arg("self"), python::arg("molgraph")), python::with_custodian_and_ward<1, 2>())
		.def("getQuerySetSize", &Shape::ScreeningProcessor::getQuerySetSize, 
			 python::arg("self"))
		.def("getQuery", &Shape::ScreeningProcessor::getQuery,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("process", static_cast<bool (Shape::ScreeningProcessor::*)(const Chem::MolecularGraph&)>(&Shape::ScreeningProcessor::process), 
			 (python::arg("self"), python::arg("molgraph")))
		.add_property("hitCallback", python::make_function(&Shape::ScreeningProcessor::getHitCallback,
														   python::return_internal_reference<>()),
					  &Shape::ScreeningProcessor::setHitCallback)
		.add_property("settings", 
					  python::make_function(static_cast<Shape::ScreeningSettings& (Shape::ScreeningProcessor::*)()>
											(&Shape::ScreeningProcessor::getSettings),
											python::return_internal_reference<>()))
		.add_property("querySetSize", &Shape::ScreeningProcessor::getQuerySetSize);
}
