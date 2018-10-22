/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomConformerGeneratorExport.cpp 
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

#include "CDPL/ConfGen/RandomConformerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportRandomConformerGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::RandomConformerGenerator> cl("RandomConformerGenerator", python::no_init);
	python::scope scope = cl;

	python::enum_<ConfGen::RandomConformerGenerator::Status>("Status")
		.value("SUCCESS", ConfGen::RandomConformerGenerator::SUCCESS)
		.value("UNINITIALIZED", ConfGen::RandomConformerGenerator::UNINITIALIZED)
		.value("MAX_NUM_TRIALS_EXCEEDED", ConfGen::RandomConformerGenerator::MAX_NUM_TRIALS_EXCEEDED)
		.value("TIMEOUT_EXCEEDED", ConfGen::RandomConformerGenerator::TIMEOUT_EXCEEDED)
		.export_values();

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::RandomConformerGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::RandomConformerGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::RandomConformerGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("regardAtomConfiguration", &ConfGen::RandomConformerGenerator::regardAtomConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("atomConfigurationRegarded", &ConfGen::RandomConformerGenerator::atomConfigurationRegarded, python::arg("self"))
		.def("regardBondConfiguration", &ConfGen::RandomConformerGenerator::regardBondConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("bondConfigurationRegarded", &ConfGen::RandomConformerGenerator::bondConfigurationRegarded, python::arg("self"))
		.def("setMaxNumStructureGenerationTrials", &ConfGen::RandomConformerGenerator::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::RandomConformerGenerator::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setMaxNumMinimizationSteps", &ConfGen::RandomConformerGenerator::setMaxNumMinimizationSteps, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumMinimizationSteps", &ConfGen::RandomConformerGenerator::getMaxNumMinimizationSteps, python::arg("self"))
		.def("setMinimizationStopGradientNorm", &ConfGen::RandomConformerGenerator::setMinimizationStopGradientNorm, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getMinimizationStopGradientNorm", &ConfGen::RandomConformerGenerator::getMinimizationStopGradientNorm, python::arg("self"))
		.def("setTimeout", &ConfGen::RandomConformerGenerator::setTimeout, (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::RandomConformerGenerator::getTimeout, python::arg("self"))
		.def("performStrictMMFF94AtomTyping", &ConfGen::RandomConformerGenerator::performStrictMMFF94AtomTyping,
			 (python::arg("self"), python::arg("strict")))
		.def("strictMMFF94AtomTypingPerformed", &ConfGen::RandomConformerGenerator::strictMMFF94AtomTypingPerformed,
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::RandomConformerGenerator::setForceFieldType,
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::RandomConformerGenerator::getForceFieldType,
			 python::arg("self"))
		.def("setup", &ConfGen::RandomConformerGenerator::setup, (python::arg("self"), python::arg("molgraph")))
		.def("generate", &ConfGen::RandomConformerGenerator::generate, (python::arg("self"), python::arg("coords")))
		.def("getEnergy", &ConfGen::RandomConformerGenerator::getEnergy, python::arg("self"))
		.def_readonly("DEF_FORCE_FIELD_TYPE", ConfGen::RandomConformerGenerator::DEF_FORCE_FIELD_TYPE)
		.def_readonly("DEF_MAX_NUM_STRUCTURE_GEN_TRIALS", ConfGen::RandomConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS)
		.def_readonly("DEF_MAX_NUM_MINIMIZATION_STEPS", ConfGen::RandomConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS)
		.def_readonly("DEF_TIMEOUT", ConfGen::RandomConformerGenerator::DEF_TIMEOUT)
		.def_readonly("DEF_MINIMIZATION_STOP_GRADIENT_NORM", ConfGen::RandomConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM)
		.add_property("energy", &ConfGen::RandomConformerGenerator::getEnergy) 
		.add_property("regardAtomConfig", &ConfGen::RandomConformerGenerator::atomConfigurationRegarded, 
					  &ConfGen::RandomConformerGenerator::regardAtomConfiguration)
		.add_property("regardBondConfig", &ConfGen::RandomConformerGenerator::bondConfigurationRegarded, 
					  &ConfGen::RandomConformerGenerator::regardBondConfiguration)
		.add_property("maxNumStructGenTrials", &ConfGen::RandomConformerGenerator::getMaxNumStructureGenerationTrials, 
					  &ConfGen::RandomConformerGenerator::setMaxNumStructureGenerationTrials)
		.add_property("maxNumMinimizationSteps", &ConfGen::RandomConformerGenerator::getMaxNumMinimizationSteps, 
					  &ConfGen::RandomConformerGenerator::setMaxNumMinimizationSteps)
		.add_property("minimizationStopGradientNorm", &ConfGen::RandomConformerGenerator::getMinimizationStopGradientNorm,
					  &ConfGen::RandomConformerGenerator::setMinimizationStopGradientNorm)
		.add_property("timeout", &ConfGen::RandomConformerGenerator::getTimeout,
					  &ConfGen::RandomConformerGenerator::setTimeout)
		.add_property("strictMMFF94AtomTyping", &ConfGen::RandomConformerGenerator::strictMMFF94AtomTypingPerformed,
					  &ConfGen::RandomConformerGenerator::performStrictMMFF94AtomTyping)
		.add_property("forceFieldType", &ConfGen::RandomConformerGenerator::getForceFieldType,
					  &ConfGen::RandomConformerGenerator::setForceFieldType);
}
