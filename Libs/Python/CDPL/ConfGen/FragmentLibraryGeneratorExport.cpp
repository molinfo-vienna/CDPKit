/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryGeneratorExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentLibraryGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::FragmentLibraryGenerator, boost::noncopyable>("FragmentLibraryGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::FragmentLibrary::SharedPointer&>((python::arg("self"), python::arg("lib"))))
//		.def(python::init<const ConfGen::FragmentLibraryGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentLibraryGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentLibraryGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setFragmentLibrary", &ConfGen::FragmentLibraryGenerator::setFragmentLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getFragmentLibrary", &ConfGen::FragmentLibraryGenerator::getFragmentLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setAbortCallback", &ConfGen::FragmentLibraryGenerator::setAbortCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getAbortCallback", &ConfGen::FragmentLibraryGenerator::getAbortCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setTimeoutCallback", &ConfGen::FragmentLibraryGenerator::setTimeoutCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getTimeoutCallback", &ConfGen::FragmentLibraryGenerator::getTimeoutCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setLogMessageCallback", &ConfGen::FragmentLibraryGenerator::setLogMessageCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getLogMessageCallback", &ConfGen::FragmentLibraryGenerator::getLogMessageCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("process", &ConfGen::FragmentLibraryGenerator::process, 
			 (python::arg("self"), python::arg("frag")))
		.def("getNumGeneratedConformers", &ConfGen::FragmentLibraryGenerator::getNumGeneratedConformers,
			 python::arg("self"))
		.def("getLibraryEntryHashCode", &ConfGen::FragmentLibraryGenerator::getLibraryEntryHashCode,
			 python::arg("self"))
		.def("getSettings", 
			 static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::FragmentLibraryGenerator::*)()>
			 (&ConfGen::FragmentLibraryGenerator::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.add_property("settings", 
					  python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::FragmentLibraryGenerator::*)()>
											(&ConfGen::FragmentLibraryGenerator::getSettings),
											python::return_internal_reference<>()))
		.add_property("abortCallback", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getAbortCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentLibraryGenerator::setAbortCallback)
		.add_property("timeoutCallback", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getTimeoutCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentLibraryGenerator::setTimeoutCallback)
		.add_property("fragmentLibrary", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getFragmentLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::FragmentLibraryGenerator::setFragmentLibrary)
		.add_property("numGeneratedConformers", &ConfGen::FragmentLibraryGenerator::getNumGeneratedConformers)
		.add_property("libraryEntryHashCode", &ConfGen::FragmentLibraryGenerator::getLibraryEntryHashCode)
		.add_property("logMessageCallback", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getLogMessageCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentLibraryGenerator::setLogMessageCallback);
}
