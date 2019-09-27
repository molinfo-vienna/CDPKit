/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomStructureGeneratorExport.cpp 
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

#include "CDPL/ConfGen/RandomStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportRandomStructureGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::RandomStructureGenerator, boost::noncopyable>("RandomStructureGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::RandomStructureGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::RandomStructureGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::RandomStructureGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setup", &ConfGen::RandomStructureGenerator::setup, (python::arg("self"), python::arg("molgraph")))
		.def("generate", &ConfGen::RandomStructureGenerator::generate, (python::arg("self"), python::arg("coords")))
		.def("getEnergy", &ConfGen::RandomStructureGenerator::getEnergy, python::arg("self"))
		.def("getSettings", 
			 static_cast<ConfGen::RandomStructureGeneratorSettings& (ConfGen::RandomStructureGenerator::*)()>
			 (&ConfGen::RandomStructureGenerator::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.add_property("settings", 
					  python::make_function(static_cast<ConfGen::RandomStructureGeneratorSettings& (ConfGen::RandomStructureGenerator::*)()>
											(&ConfGen::RandomStructureGenerator::getSettings),
											python::return_internal_reference<>()))
		.add_property("energy", &ConfGen::RandomStructureGenerator::getEnergy);
}
