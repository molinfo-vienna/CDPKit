/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentAssemblerExport.cpp 
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

#include "CDPL/ConfGen/FragmentAssembler.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentAssembler()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::FragmentAssembler, boost::noncopyable>("FragmentAssembler", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentAssembler>())
		.def("getSettings", 
			 static_cast<ConfGen::FragmentAssemblerSettings& (ConfGen::FragmentAssembler::*)()>
			 (&ConfGen::FragmentAssembler::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.def("clearFragmentLibraries", &ConfGen::FragmentAssembler::clearFragmentLibraries, 
			 python::arg("self"))
		.def("addFragmentLibrary", &ConfGen::FragmentAssembler::addFragmentLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("setAbortCallback", &ConfGen::FragmentAssembler::setAbortCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getAbortCallback", &ConfGen::FragmentAssembler::getAbortCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setTimeoutCallback", &ConfGen::FragmentAssembler::setTimeoutCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getTimeoutCallback", &ConfGen::FragmentAssembler::getTimeoutCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setLogMessageCallback", &ConfGen::FragmentAssembler::setLogMessageCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getLogMessageCallback", &ConfGen::FragmentAssembler::getLogMessageCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("assemble", &ConfGen::FragmentAssembler::assemble, (python::arg("self"), python::arg("molgraph")))
		.def("getNumConformers", &ConfGen::FragmentAssembler::getNumConformers, python::arg("self"))
		.def("getConformer", 
			 static_cast<ConfGen::ConformerData& (ConfGen::FragmentAssembler::*)(std::size_t)>(&ConfGen::FragmentAssembler::getConformer),
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.def("__getitem__", 
			 static_cast<ConfGen::ConformerData& (ConfGen::FragmentAssembler::*)(std::size_t)>(&ConfGen::FragmentAssembler::getConformer),
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.add_property("numConformers", &ConfGen::FragmentAssembler::getNumConformers)
		.add_property("settings", 
					  python::make_function(static_cast<ConfGen::FragmentAssemblerSettings& (ConfGen::FragmentAssembler::*)()>
											(&ConfGen::FragmentAssembler::getSettings),
											python::return_internal_reference<>()))
		.add_property("abortCallback", 
					  python::make_function(&ConfGen::FragmentAssembler::getAbortCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentAssembler::setAbortCallback)
		.add_property("timeoutCallback", 
					  python::make_function(&ConfGen::FragmentAssembler::getTimeoutCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentAssembler::setTimeoutCallback)
		.add_property("logMessageCallback", 
					  python::make_function(&ConfGen::FragmentAssembler::getLogMessageCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentAssembler::setLogMessageCallback);
}
