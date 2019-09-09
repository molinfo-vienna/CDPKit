/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorExport.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentConformerGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::FragmentConformerGenerator, boost::noncopyable>("FragmentConformerGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::FragmentConformerGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentConformerGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentConformerGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setProgressCallback", &ConfGen::FragmentConformerGenerator::setProgressCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getProgressCallback", &ConfGen::FragmentConformerGenerator::getProgressCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setMaxNumStructureGenerationTrials", &ConfGen::FragmentConformerGenerator::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::FragmentConformerGenerator::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::FragmentConformerGenerator::setForceFieldType,
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::FragmentConformerGenerator::getForceFieldType,
			 python::arg("self"))
		.def("performStrictAtomTyping", &ConfGen::FragmentConformerGenerator::performStrictAtomTyping,
			 (python::arg("self"), python::arg("strict")))
		.def("strictAtomTypingPerformed", &ConfGen::FragmentConformerGenerator::strictAtomTypingPerformed,
			 python::arg("self"))
		.def("setMaxNumMinimizationSteps", &ConfGen::FragmentConformerGenerator::setMaxNumMinimizationSteps, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumMinimizationSteps", &ConfGen::FragmentConformerGenerator::getMaxNumMinimizationSteps, 
			 python::arg("self"))
		.def("setMinimizationStopGradientNorm", &ConfGen::FragmentConformerGenerator::setMinimizationStopGradientNorm, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getMinimizationStopGradientNorm", &ConfGen::FragmentConformerGenerator::getMinimizationStopGradientNorm, 
			 python::arg("self"))
		.def("setMinimizationStopEnergyDelta", &ConfGen::FragmentConformerGenerator::setMinimizationStopEnergyDelta, 
			 (python::arg("self"), python::arg("e_delta")))
		.def("getMinimizationStopEnergyDelta", &ConfGen::FragmentConformerGenerator::getMinimizationStopEnergyDelta, 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::FragmentConformerGenerator::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::FragmentConformerGenerator::getTimeout, 
			 python::arg("self"))
		.def("reuseExistingCoordinates", &ConfGen::FragmentConformerGenerator::reuseExistingCoordinates,
			 (python::arg("self"), python::arg("reuse")))
		.def("existingCoordinatesReused", &ConfGen::FragmentConformerGenerator::existingCoordinatesReused,
			 python::arg("self"))
		.def("setEnergyWindow", &ConfGen::FragmentConformerGenerator::setEnergyWindow,
			 (python::arg("self"), python::arg("win_size")))
		.def("getEnergyWindow", &ConfGen::FragmentConformerGenerator::getEnergyWindow,
			 python::arg("self"))
		.def("setRingConformerTrialFactor", &ConfGen::FragmentConformerGenerator::setRingConformerTrialFactor,
			 (python::arg("self"), python::arg("factor")))
		.def("getRingConformerTrialFactor", &ConfGen::FragmentConformerGenerator::getRingConformerTrialFactor,
			 python::arg("self"))
		.def("setMaxNumRingConformerTrials", &ConfGen::FragmentConformerGenerator::setMaxNumRingConformerTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRingConformerTrials", &ConfGen::FragmentConformerGenerator::getMaxNumRingConformerTrials, 
			 python::arg("self"))
		.def("setMinNumRingConformerTrials", &ConfGen::FragmentConformerGenerator::setMinNumRingConformerTrials, 
			 (python::arg("self"), python::arg("min_num")))
		.def("getMinNumRingConformerTrials", &ConfGen::FragmentConformerGenerator::getMinNumRingConformerTrials, 
			 python::arg("self"))
		.def("setMinRMSD", &ConfGen::FragmentConformerGenerator::setMinRMSD,
			 (python::arg("self"), python::arg("min_rmsd")))
		.def("getMinRMSD", &ConfGen::FragmentConformerGenerator::getMinRMSD,
			 python::arg("self"))
		.def("setMaxNumOutputConformers", &ConfGen::FragmentConformerGenerator::setMaxNumOutputConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumOutputConformers", &ConfGen::FragmentConformerGenerator::getMaxNumOutputConformers, 
			 python::arg("self"))
		.def("generate", &ConfGen::FragmentConformerGenerator::generate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("frag_type")))
		.def("getExistingCoordinates", &ConfGen::FragmentConformerGenerator::getExistingCoordinates, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("coords")))
		.def("getNumConformers", &ConfGen::FragmentConformerGenerator::getNumConformers, python::arg("self"))
		.def("getCoordinates", static_cast<Math::Vector3DArray& (ConfGen::FragmentConformerGenerator::*)(std::size_t)>(
				 &ConfGen::FragmentConformerGenerator::getCoordinates),
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.def("getEnergy", &ConfGen::FragmentConformerGenerator::getEnergy, 
			 (python::arg("self"), python::arg("conf_idx")))
		.def_readonly("DEF_MAX_NUM_STRUCTURE_GEN_TRIALS", ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS)
		.def_readonly("DEF_MAX_NUM_MINIMIZATION_STEPS", ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS)
		.def_readonly("DEF_MAX_NUM_OUTPUT_CONFORMERS", ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_OUTPUT_CONFORMERS)
		.def_readonly("DEF_TIMEOUT", ConfGen::FragmentConformerGenerator::DEF_TIMEOUT)
		.def_readonly("DEF_RING_CONFORMER_TRIAL_FACTOR", ConfGen::FragmentConformerGenerator::DEF_RING_CONFORMER_TRIAL_FACTOR)
		.def_readonly("DEF_MINIMIZATION_STOP_GRADIENT_NORM", ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM)
		.def_readonly("DEF_MINIMIZATION_STOP_ENERGY_DELTA", ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_ENERGY_DELTA)
		.def_readonly("DEF_FORCEFIELD_TYPE", ConfGen::FragmentConformerGenerator::DEF_FORCEFIELD_TYPE)
		.def_readonly("DEF_ENERGY_WINDOW", ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW)
		.def_readonly("DEF_MIN_RMSD", ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD)
		.add_property("progressCallback", 
					  python::make_function(&ConfGen::FragmentConformerGenerator::getProgressCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentConformerGenerator::setProgressCallback)
		.add_property("numConformers", &ConfGen::FragmentConformerGenerator::getNumConformers) 
		.add_property("maxNumStructGenTrials", &ConfGen::FragmentConformerGenerator::getMaxNumStructureGenerationTrials, 
					  &ConfGen::FragmentConformerGenerator::setMaxNumStructureGenerationTrials)
		.add_property("strictAtomTyping", &ConfGen::FragmentConformerGenerator::strictAtomTypingPerformed,
					  &ConfGen::FragmentConformerGenerator::performStrictAtomTyping)
		.add_property("forceFieldType", &ConfGen::FragmentConformerGenerator::getForceFieldType,
					  &ConfGen::FragmentConformerGenerator::setForceFieldType)
		.add_property("maxNumMinimizationSteps", &ConfGen::FragmentConformerGenerator::getMaxNumMinimizationSteps, 
					  &ConfGen::FragmentConformerGenerator::setMaxNumMinimizationSteps)
		.add_property("maxNumOutputConformers", &ConfGen::FragmentConformerGenerator::getMaxNumOutputConformers, 
					  &ConfGen::FragmentConformerGenerator::setMaxNumOutputConformers)
		.add_property("minimizationStopGradientNorm", &ConfGen::FragmentConformerGenerator::getMinimizationStopGradientNorm,
					  &ConfGen::FragmentConformerGenerator::setMinimizationStopGradientNorm)
		.add_property("minimizationStopEnergyDelta", &ConfGen::FragmentConformerGenerator::getMinimizationStopEnergyDelta,
					  &ConfGen::FragmentConformerGenerator::setMinimizationStopEnergyDelta)
		.add_property("timeout", &ConfGen::FragmentConformerGenerator::getTimeout,
					  &ConfGen::FragmentConformerGenerator::setTimeout)
		.add_property("reuseExistingCoords", &ConfGen::FragmentConformerGenerator::existingCoordinatesReused,
					  &ConfGen::FragmentConformerGenerator::reuseExistingCoordinates)
		.add_property("energyWindow", &ConfGen::FragmentConformerGenerator::getEnergyWindow,
					  &ConfGen::FragmentConformerGenerator::setEnergyWindow)
		.add_property("ringConfTrialFactor", &ConfGen::FragmentConformerGenerator::getRingConformerTrialFactor,
					  &ConfGen::FragmentConformerGenerator::setRingConformerTrialFactor)
		.add_property("maxNumRingConfTrials", &ConfGen::FragmentConformerGenerator::getMaxNumRingConformerTrials,
					  &ConfGen::FragmentConformerGenerator::setMaxNumRingConformerTrials)
		.add_property("minNumRingConfTrials", &ConfGen::FragmentConformerGenerator::getMinNumRingConformerTrials,
					  &ConfGen::FragmentConformerGenerator::setMinNumRingConformerTrials)
		.add_property("minRMSD", &ConfGen::FragmentConformerGenerator::getMinRMSD,
					  &ConfGen::FragmentConformerGenerator::setMinRMSD);
}
