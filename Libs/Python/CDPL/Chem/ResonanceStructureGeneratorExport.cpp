/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResonanceStructureGeneratorExport.cpp 
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

#include "CDPL/Chem/ResonanceStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportResonanceStructureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::ResonanceStructureGenerator, Chem::ResonanceStructureGenerator::SharedPointer,
				   boost::noncopyable>("ResonanceStructureGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::ResonanceStructureGenerator>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ResonanceStructureGenerator>())	
		.def("generate", &Chem::ResonanceStructureGenerator::generate, 
			 (python::arg("self"), python::arg("molgraph")))
		.def("assign", &Chem::ResonanceStructureGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setCallbackFunction", &Chem::ResonanceStructureGenerator::setCallbackFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getCallbackFunction", &Chem::ResonanceStructureGenerator::getCallbackFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.add_property("callbackFunction", python::make_function(&Chem::ResonanceStructureGenerator::getCallbackFunction,
																python::return_internal_reference<>()),
					  &Chem::ResonanceStructureGenerator::setCallbackFunction)
		;
}
