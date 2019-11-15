/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/ConformerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportConformerGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::ConformerGenerator, boost::noncopyable>("ConformerGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::ConformerGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::ConformerGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::ConformerGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("generate", &ConfGen::ConformerGenerator::generate, 
			 (python::arg("self"), python::arg("molgraph")))
		.def("getSettings", 
			 static_cast<ConfGen::ConformerGeneratorSettings& (ConfGen::ConformerGenerator::*)()>
			 (&ConfGen::ConformerGenerator::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.def("clearFragmentLibraries", &ConfGen::ConformerGenerator::clearFragmentLibraries, 
			 python::arg("self"))
		.def("addFragmentLibrary", &ConfGen::ConformerGenerator::addFragmentLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("setAbortCallback", &ConfGen::ConformerGenerator::setAbortCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getAbortCallback", &ConfGen::ConformerGenerator::getAbortCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setTimeoutCallback", &ConfGen::ConformerGenerator::setTimeoutCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getTimeoutCallback", &ConfGen::ConformerGenerator::getTimeoutCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("generate", &ConfGen::ConformerGenerator::generate, (python::arg("self"), python::arg("molgraph")))
		.def("getNumConformers", &ConfGen::ConformerGenerator::getNumConformers, python::arg("self"))
		.def("getConformer", 
			 static_cast<ConfGen::ConformerData& (ConfGen::ConformerGenerator::*)(std::size_t)>(&ConfGen::ConformerGenerator::getConformer),
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.def("__getitem__", 
			 static_cast<ConfGen::ConformerData& (ConfGen::ConformerGenerator::*)(std::size_t)>(&ConfGen::ConformerGenerator::getConformer),
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.add_property("numConformers", &ConfGen::ConformerGenerator::getNumConformers)
		.add_property("settings", 
					  python::make_function(static_cast<ConfGen::ConformerGeneratorSettings& (ConfGen::ConformerGenerator::*)()>
											(&ConfGen::ConformerGenerator::getSettings),
											python::return_internal_reference<>()))
		.add_property("abortCallback", 
					  python::make_function(&ConfGen::ConformerGenerator::getAbortCallback,
											python::return_internal_reference<>()),
					  &ConfGen::ConformerGenerator::setAbortCallback)
		.add_property("timeoutCallback", 
					  python::make_function(&ConfGen::ConformerGenerator::getTimeoutCallback,
											python::return_internal_reference<>()),
					  &ConfGen::ConformerGenerator::setTimeoutCallback);
}
