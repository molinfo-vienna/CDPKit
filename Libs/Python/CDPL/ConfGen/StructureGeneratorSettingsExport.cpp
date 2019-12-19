/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureGeneratorSettingsExport.cpp 
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

#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportStructureGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (ConfGen::StructureGeneratorSettings::*SetBoolFunc)(bool);
	typedef bool (ConfGen::StructureGeneratorSettings::*GetBoolFunc)() const;

	python::class_<ConfGen::StructureGeneratorSettings>("StructureGeneratorSettings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::StructureGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::StructureGeneratorSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::StructureGeneratorSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("generateCoordinatesFromScratch", SetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch), 
			 (python::arg("self"), python::arg("generate")))
		.def("generateCoordinatesFromScratch", GetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch), 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::StructureGeneratorSettings::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::StructureGeneratorSettings::getTimeout, 
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::StructureGeneratorSettings::setForceFieldType, 
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::StructureGeneratorSettings::getForceFieldType, 
			 python::arg("self"))
		.def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization), 
			 (python::arg("self"), python::arg("strict")))
		.def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization), 
			 python::arg("self"))
		.def("setMaxNumRefinementIterations", &ConfGen::StructureGeneratorSettings::setMaxNumRefinementIterations, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRefinementIterations", &ConfGen::StructureGeneratorSettings::getMaxNumRefinementIterations, 
			 python::arg("self"))
		.def("setRefinementStopGradient", &ConfGen::StructureGeneratorSettings::setRefinementStopGradient, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getRefinementStopGradient", &ConfGen::StructureGeneratorSettings::getRefinementStopGradient, 
			 python::arg("self"))
		.def("setMinMacrocycleSize", &ConfGen::StructureGeneratorSettings::setMinMacrocycleSize, 
			 (python::arg("self"), python::arg("max_size")))
		.def("getMinMacrocycleSize", &ConfGen::StructureGeneratorSettings::getMinMacrocycleSize, 
			 python::arg("self"))
		.def("getFragmentBuildSettings", 
			 static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::StructureGeneratorSettings::*)()>
			 (&ConfGen::StructureGeneratorSettings::getFragmentBuildSettings),
			 python::arg("self"), python::return_internal_reference<>())
		.def_readonly("DEFAULT", ConfGen::StructureGeneratorSettings::DEFAULT)
		.add_property("genCoordsFromScratch", GetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch),
					  SetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch))
		.add_property("timeout", &ConfGen::StructureGeneratorSettings::getTimeout,
					  &ConfGen::StructureGeneratorSettings::setTimeout)
		.add_property("forceFieldType", &ConfGen::StructureGeneratorSettings::getForceFieldType, 
					  &ConfGen::StructureGeneratorSettings::setForceFieldType)
		.add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization), 
					  SetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization))
		.add_property("maxNumRefinementIterations", &ConfGen::StructureGeneratorSettings::getMaxNumRefinementIterations, 
					  &ConfGen::StructureGeneratorSettings::setMaxNumRefinementIterations)
		.add_property("refinementStopGradient", &ConfGen::StructureGeneratorSettings::getRefinementStopGradient,
					  &ConfGen::StructureGeneratorSettings::setRefinementStopGradient)
		.add_property("minMacrocycleSize", &ConfGen::StructureGeneratorSettings::getMinMacrocycleSize, 
					  &ConfGen::StructureGeneratorSettings::setMinMacrocycleSize)
		.add_property("fragmentBuildSettings", 
					  python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::StructureGeneratorSettings::*)()>
											(&ConfGen::StructureGeneratorSettings::getFragmentBuildSettings),
											python::return_internal_reference<>()));
}
