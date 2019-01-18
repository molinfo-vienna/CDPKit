/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGeneratorExport.cpp 
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

#include "CDPL/ConfGen/SystematicConformerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportSystematicConformerGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::SystematicConformerGenerator, boost::noncopyable> cl("SystematicConformerGenerator", python::no_init);
	python::scope scope = cl;

	python::enum_<ConfGen::SystematicConformerGenerator::Status>("Status")
		.value("SUCCESS", ConfGen::SystematicConformerGenerator::SUCCESS)
		.value("ERROR", ConfGen::SystematicConformerGenerator::ERROR)
		.value("TIMEOUT_EXCEEDED", ConfGen::SystematicConformerGenerator::TIMEOUT_EXCEEDED)
		.export_values();

	cl
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::SystematicConformerGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::SystematicConformerGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::SystematicConformerGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("generate", &ConfGen::SystematicConformerGenerator::generate, (python::arg("self"), python::arg("molgraph")));
}
