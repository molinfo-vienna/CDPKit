/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomStructureGeneratorSettingsExport.cpp 
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

#include "CDPL/ConfGen/RandomStructureGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportRandomStructureGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (ConfGen::RandomStructureGeneratorSettings::*SetBoolFunc)(bool);
	typedef bool (ConfGen::RandomStructureGeneratorSettings::*GetBoolFunc)() const;

	python::class_<ConfGen::RandomStructureGeneratorSettings>("RandomStructureGeneratorSettings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::RandomStructureGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::RandomStructureGeneratorSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::RandomStructureGeneratorSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("regardAtomConfiguration", SetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardAtomConfiguration), 
			 (python::arg("self"), python::arg("regard")))
		.def("regardAtomConfiguration", GetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardAtomConfiguration), 
			 python::arg("self"))
		.def("regardBondConfiguration", SetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardBondConfiguration), 
			 (python::arg("self"), python::arg("regard")))
		.def("regardBondConfiguration", GetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardBondConfiguration), 
			 python::arg("self"))
		.def("setMaxNumStructureGenerationTrials", &ConfGen::RandomStructureGeneratorSettings::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::RandomStructureGeneratorSettings::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setMaxNumRefinementIterations", &ConfGen::RandomStructureGeneratorSettings::setMaxNumRefinementIterations, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRefinementIterations", &ConfGen::RandomStructureGeneratorSettings::getMaxNumRefinementIterations, 
			 python::arg("self"))
		.def("setRefinementStopGradient", &ConfGen::RandomStructureGeneratorSettings::setRefinementStopGradient, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getRefinementStopGradient", &ConfGen::RandomStructureGeneratorSettings::getRefinementStopGradient, 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::RandomStructureGeneratorSettings::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::RandomStructureGeneratorSettings::getTimeout, 
			 python::arg("self"))
		.def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::strictForceFieldParameterization),
			 (python::arg("self"), python::arg("strict")))
		.def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::strictForceFieldParameterization),
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::RandomStructureGeneratorSettings::setForceFieldType,
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::RandomStructureGeneratorSettings::getForceFieldType,
			 python::arg("self"))
		.def_readonly("DEFAULT", ConfGen::RandomStructureGeneratorSettings::DEFAULT)

		.add_property("regardAtomConfig", GetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardAtomConfiguration), 
					  SetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardAtomConfiguration))
		.add_property("regardBondConfig", GetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardBondConfiguration), 
					  SetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::regardBondConfiguration))
		.add_property("maxNumStructGenTrials", &ConfGen::RandomStructureGeneratorSettings::getMaxNumStructureGenerationTrials, 
					  &ConfGen::RandomStructureGeneratorSettings::setMaxNumStructureGenerationTrials)
		.add_property("maxNumRefinementIterations", &ConfGen::RandomStructureGeneratorSettings::getMaxNumRefinementIterations, 
					  &ConfGen::RandomStructureGeneratorSettings::setMaxNumRefinementIterations)
		.add_property("refinementStopGradient", &ConfGen::RandomStructureGeneratorSettings::getRefinementStopGradient,
					  &ConfGen::RandomStructureGeneratorSettings::setRefinementStopGradient)
		.add_property("timeout", &ConfGen::RandomStructureGeneratorSettings::getTimeout,
					  &ConfGen::RandomStructureGeneratorSettings::setTimeout)
		.add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::strictForceFieldParameterization),
					  SetBoolFunc(&ConfGen::RandomStructureGeneratorSettings::strictForceFieldParameterization))
		.add_property("forceFieldType", &ConfGen::RandomStructureGeneratorSettings::getForceFieldType,
					  &ConfGen::RandomStructureGeneratorSettings::setForceFieldType);
}
