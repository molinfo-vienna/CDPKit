/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureGeneratorExport.cpp 
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

#include "CDPL/ConfGen/StructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportStructureGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::StructureGenerator, boost::noncopyable>("StructureGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::StructureGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::StructureGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::StructureGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("getSettings", 
			 static_cast<ConfGen::StructureGeneratorSettings& (ConfGen::StructureGenerator::*)()>
			 (&ConfGen::StructureGenerator::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.def("clearFragmentLibraries", &ConfGen::StructureGenerator::clearFragmentLibraries, 
			 python::arg("self"))
		.def("addFragmentLibrary", &ConfGen::StructureGenerator::addFragmentLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("setTorsionLibrary", &ConfGen::StructureGenerator::setTorsionLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getTorsionLibrary", &ConfGen::StructureGenerator::getTorsionLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setAbortCallback", &ConfGen::StructureGenerator::setAbortCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getAbortCallback", &ConfGen::StructureGenerator::getAbortCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setTimeoutCallback", &ConfGen::StructureGenerator::setTimeoutCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getTimeoutCallback", &ConfGen::StructureGenerator::getTimeoutCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("generate", static_cast<unsigned int (ConfGen::StructureGenerator::*)
			 (const Chem::MolecularGraph&, ConfGen::ConformerData&)>(&ConfGen::StructureGenerator::generate),
			 (python::arg("self"), python::arg("molgraph"), python::arg("conf_data")))
		.def("generate", static_cast<unsigned int (ConfGen::StructureGenerator::*)
			 (const Chem::MolecularGraph&, Math::Vector3DArray&)>(&ConfGen::StructureGenerator::generate),
			 (python::arg("self"), python::arg("molgraph"), python::arg("coords")))
		.add_property("settings", 
					  python::make_function(static_cast<ConfGen::StructureGeneratorSettings& (ConfGen::StructureGenerator::*)()>
											(&ConfGen::StructureGenerator::getSettings),
											python::return_internal_reference<>()))
		.add_property("torsionLibrary", 
					  python::make_function(&ConfGen::StructureGenerator::getTorsionLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::StructureGenerator::setTorsionLibrary)
		.add_property("abortCallback", 
					  python::make_function(&ConfGen::StructureGenerator::getAbortCallback,
											python::return_internal_reference<>()),
					  &ConfGen::StructureGenerator::setAbortCallback)
		.add_property("timeoutCallback", 
					  python::make_function(&ConfGen::StructureGenerator::getTimeoutCallback,
											python::return_internal_reference<>()),
					  &ConfGen::StructureGenerator::setTimeoutCallback);
}
