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
		.def("regardAtomConfiguration", &ConfGen::RandomStructureGenerator::regardAtomConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("atomConfigurationRegarded", &ConfGen::RandomStructureGenerator::atomConfigurationRegarded, python::arg("self"))
		.def("regardBondConfiguration", &ConfGen::RandomStructureGenerator::regardBondConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("bondConfigurationRegarded", &ConfGen::RandomStructureGenerator::bondConfigurationRegarded, python::arg("self"))
		.def("setMaxNumStructureGenerationTrials", &ConfGen::RandomStructureGenerator::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::RandomStructureGenerator::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setMaxNumMinimizationSteps", &ConfGen::RandomStructureGenerator::setMaxNumMinimizationSteps, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumMinimizationSteps", &ConfGen::RandomStructureGenerator::getMaxNumMinimizationSteps, python::arg("self"))
		.def("setMinimizationStopGradientNorm", &ConfGen::RandomStructureGenerator::setMinimizationStopGradientNorm, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getMinimizationStopGradientNorm", &ConfGen::RandomStructureGenerator::getMinimizationStopGradientNorm, python::arg("self"))
		.def("setTimeout", &ConfGen::RandomStructureGenerator::setTimeout, (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::RandomStructureGenerator::getTimeout, python::arg("self"))
		.def("performStrictAtomTyping", &ConfGen::RandomStructureGenerator::performStrictAtomTyping,
			 (python::arg("self"), python::arg("strict")))
		.def("strictAtomTypingPerformed", &ConfGen::RandomStructureGenerator::strictAtomTypingPerformed,
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::RandomStructureGenerator::setForceFieldType,
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::RandomStructureGenerator::getForceFieldType,
			 python::arg("self"))
		.def("setup", &ConfGen::RandomStructureGenerator::setup, (python::arg("self"), python::arg("molgraph")))
		.def("generate", &ConfGen::RandomStructureGenerator::generate, (python::arg("self"), python::arg("coords")))
		.def("getEnergy", &ConfGen::RandomStructureGenerator::getEnergy, python::arg("self"))
		.def_readonly("DEF_FORCE_FIELD_TYPE", ConfGen::RandomStructureGenerator::DEF_FORCE_FIELD_TYPE)
		.def_readonly("DEF_MAX_NUM_STRUCTURE_GEN_TRIALS", ConfGen::RandomStructureGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS)
		.def_readonly("DEF_MAX_NUM_MINIMIZATION_STEPS", ConfGen::RandomStructureGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS)
		.def_readonly("DEF_TIMEOUT", ConfGen::RandomStructureGenerator::DEF_TIMEOUT)
		.def_readonly("DEF_MINIMIZATION_STOP_GRADIENT_NORM", ConfGen::RandomStructureGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM)
		.add_property("energy", &ConfGen::RandomStructureGenerator::getEnergy) 
		.add_property("regardAtomConfig", &ConfGen::RandomStructureGenerator::atomConfigurationRegarded, 
					  &ConfGen::RandomStructureGenerator::regardAtomConfiguration)
		.add_property("regardBondConfig", &ConfGen::RandomStructureGenerator::bondConfigurationRegarded, 
					  &ConfGen::RandomStructureGenerator::regardBondConfiguration)
		.add_property("maxNumStructGenTrials", &ConfGen::RandomStructureGenerator::getMaxNumStructureGenerationTrials, 
					  &ConfGen::RandomStructureGenerator::setMaxNumStructureGenerationTrials)
		.add_property("maxNumMinimizationSteps", &ConfGen::RandomStructureGenerator::getMaxNumMinimizationSteps, 
					  &ConfGen::RandomStructureGenerator::setMaxNumMinimizationSteps)
		.add_property("minimizationStopGradientNorm", &ConfGen::RandomStructureGenerator::getMinimizationStopGradientNorm,
					  &ConfGen::RandomStructureGenerator::setMinimizationStopGradientNorm)
		.add_property("timeout", &ConfGen::RandomStructureGenerator::getTimeout,
					  &ConfGen::RandomStructureGenerator::setTimeout)
		.add_property("strictAtomTyping", &ConfGen::RandomStructureGenerator::strictAtomTypingPerformed,
					  &ConfGen::RandomStructureGenerator::performStrictAtomTyping)
		.add_property("forceFieldType", &ConfGen::RandomStructureGenerator::getForceFieldType,
					  &ConfGen::RandomStructureGenerator::setForceFieldType);
}
