/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Random3DCoordinatesGeneratorExport.cpp 
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

#include "CDPL/ConfGen/Random3DCoordinatesGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportRandom3DCoordinatesGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::Random3DCoordinatesGenerator, boost::noncopyable>("Random3DCoordinatesGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::Random3DCoordinatesGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::Random3DCoordinatesGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::Random3DCoordinatesGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("regardAtomConfiguration", &ConfGen::Random3DCoordinatesGenerator::regardAtomConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("atomConfigurationRegarded", &ConfGen::Random3DCoordinatesGenerator::atomConfigurationRegarded, python::arg("self"))
		.def("regardBondConfiguration", &ConfGen::Random3DCoordinatesGenerator::regardBondConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("bondConfigurationRegarded", &ConfGen::Random3DCoordinatesGenerator::bondConfigurationRegarded, python::arg("self"))
		.def("setMaxNumStructureGenerationTrials", &ConfGen::Random3DCoordinatesGenerator::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::Random3DCoordinatesGenerator::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setMaxNumMinimizationSteps", &ConfGen::Random3DCoordinatesGenerator::setMaxNumMinimizationSteps, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumMinimizationSteps", &ConfGen::Random3DCoordinatesGenerator::getMaxNumMinimizationSteps, python::arg("self"))
		.def("setMinimizationStopGradientNorm", &ConfGen::Random3DCoordinatesGenerator::setMinimizationStopGradientNorm, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getMinimizationStopGradientNorm", &ConfGen::Random3DCoordinatesGenerator::getMinimizationStopGradientNorm, python::arg("self"))
		.def("setTimeout", &ConfGen::Random3DCoordinatesGenerator::setTimeout, (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::Random3DCoordinatesGenerator::getTimeout, python::arg("self"))
		.def("performStrictAtomTyping", &ConfGen::Random3DCoordinatesGenerator::performStrictAtomTyping,
			 (python::arg("self"), python::arg("strict")))
		.def("strictAtomTypingPerformed", &ConfGen::Random3DCoordinatesGenerator::strictAtomTypingPerformed,
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::Random3DCoordinatesGenerator::setForceFieldType,
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::Random3DCoordinatesGenerator::getForceFieldType,
			 python::arg("self"))
		.def("setup", &ConfGen::Random3DCoordinatesGenerator::setup, (python::arg("self"), python::arg("molgraph")))
		.def("generate", &ConfGen::Random3DCoordinatesGenerator::generate, (python::arg("self"), python::arg("coords")))
		.def("getEnergy", &ConfGen::Random3DCoordinatesGenerator::getEnergy, python::arg("self"))
		.def_readonly("DEF_FORCE_FIELD_TYPE", ConfGen::Random3DCoordinatesGenerator::DEF_FORCE_FIELD_TYPE)
		.def_readonly("DEF_MAX_NUM_STRUCTURE_GEN_TRIALS", ConfGen::Random3DCoordinatesGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS)
		.def_readonly("DEF_MAX_NUM_MINIMIZATION_STEPS", ConfGen::Random3DCoordinatesGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS)
		.def_readonly("DEF_TIMEOUT", ConfGen::Random3DCoordinatesGenerator::DEF_TIMEOUT)
		.def_readonly("DEF_MINIMIZATION_STOP_GRADIENT_NORM", ConfGen::Random3DCoordinatesGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM)
		.add_property("energy", &ConfGen::Random3DCoordinatesGenerator::getEnergy) 
		.add_property("regardAtomConfig", &ConfGen::Random3DCoordinatesGenerator::atomConfigurationRegarded, 
					  &ConfGen::Random3DCoordinatesGenerator::regardAtomConfiguration)
		.add_property("regardBondConfig", &ConfGen::Random3DCoordinatesGenerator::bondConfigurationRegarded, 
					  &ConfGen::Random3DCoordinatesGenerator::regardBondConfiguration)
		.add_property("maxNumStructGenTrials", &ConfGen::Random3DCoordinatesGenerator::getMaxNumStructureGenerationTrials, 
					  &ConfGen::Random3DCoordinatesGenerator::setMaxNumStructureGenerationTrials)
		.add_property("maxNumMinimizationSteps", &ConfGen::Random3DCoordinatesGenerator::getMaxNumMinimizationSteps, 
					  &ConfGen::Random3DCoordinatesGenerator::setMaxNumMinimizationSteps)
		.add_property("minimizationStopGradientNorm", &ConfGen::Random3DCoordinatesGenerator::getMinimizationStopGradientNorm,
					  &ConfGen::Random3DCoordinatesGenerator::setMinimizationStopGradientNorm)
		.add_property("timeout", &ConfGen::Random3DCoordinatesGenerator::getTimeout,
					  &ConfGen::Random3DCoordinatesGenerator::setTimeout)
		.add_property("strictAtomTyping", &ConfGen::Random3DCoordinatesGenerator::strictAtomTypingPerformed,
					  &ConfGen::Random3DCoordinatesGenerator::performStrictAtomTyping)
		.add_property("forceFieldType", &ConfGen::Random3DCoordinatesGenerator::getForceFieldType,
					  &ConfGen::Random3DCoordinatesGenerator::setForceFieldType);
}
