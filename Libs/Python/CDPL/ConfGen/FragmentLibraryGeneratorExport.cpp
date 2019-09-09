/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryGeneratorExport.cpp 
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

#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
//#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentLibraryGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::FragmentLibraryGenerator, boost::noncopyable>("FragmentLibraryGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::FragmentLibrary::SharedPointer&>((python::arg("self"), python::arg("lib"))))
//		.def(python::init<const ConfGen::FragmentLibraryGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentLibraryGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentLibraryGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setFragmentLibrary", &ConfGen::FragmentLibraryGenerator::setFragmentLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getFragmentLibrary", &ConfGen::FragmentLibraryGenerator::getFragmentLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setProcessingResultCallback", &ConfGen::FragmentLibraryGenerator::setProcessingResultCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getProcessingResultCallback", &ConfGen::FragmentLibraryGenerator::getProcessingResultCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setProcessingErrorCallback", &ConfGen::FragmentLibraryGenerator::setProcessingErrorCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getProcessingErrorCallback", &ConfGen::FragmentLibraryGenerator::getProcessingErrorCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setProgressCallback", &ConfGen::FragmentLibraryGenerator::setProgressCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getProgressCallback", &ConfGen::FragmentLibraryGenerator::getProgressCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setMaxNumStructureGenerationTrials", &ConfGen::FragmentLibraryGenerator::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::FragmentLibraryGenerator::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setMaxNumMinimizationSteps", &ConfGen::FragmentLibraryGenerator::setMaxNumMinimizationSteps, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumMinimizationSteps", &ConfGen::FragmentLibraryGenerator::getMaxNumMinimizationSteps, 
			 python::arg("self"))
		.def("setMinimizationStopGradientNorm", &ConfGen::FragmentLibraryGenerator::setMinimizationStopGradientNorm, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getMinimizationStopGradientNorm", &ConfGen::FragmentLibraryGenerator::getMinimizationStopGradientNorm, 
			 python::arg("self"))
		.def("setMinimizationStopEnergyDelta", &ConfGen::FragmentLibraryGenerator::setMinimizationStopEnergyDelta, 
			 (python::arg("self"), python::arg("e_delta")))
		.def("getMinimizationStopEnergyDelta", &ConfGen::FragmentLibraryGenerator::getMinimizationStopEnergyDelta, 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::FragmentLibraryGenerator::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::FragmentLibraryGenerator::getTimeout, 
			 python::arg("self"))
		.def("reuseExistingCoordinates", &ConfGen::FragmentLibraryGenerator::reuseExistingCoordinates,
			 (python::arg("self"), python::arg("reuse")))
		.def("existingCoordinatesReused", &ConfGen::FragmentLibraryGenerator::existingCoordinatesReused,
			 python::arg("self"))
		.def("setEnergyWindow", &ConfGen::FragmentLibraryGenerator::setEnergyWindow,
			 (python::arg("self"), python::arg("win_size")))
		.def("getEnergyWindow", &ConfGen::FragmentLibraryGenerator::getEnergyWindow,
			 python::arg("self"))
		.def("setRingConformerTrialFactor", &ConfGen::FragmentLibraryGenerator::setRingConformerTrialFactor,
			 (python::arg("self"), python::arg("factor")))
		.def("getRingConformerTrialFactor", &ConfGen::FragmentLibraryGenerator::getRingConformerTrialFactor,
			 python::arg("self"))
		.def("setMaxNumRingConformerTrials", &ConfGen::FragmentLibraryGenerator::setMaxNumRingConformerTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRingConformerTrials", &ConfGen::FragmentLibraryGenerator::getMaxNumRingConformerTrials, 
			 python::arg("self"))
		.def("setMinNumRingConformerTrials", &ConfGen::FragmentLibraryGenerator::setMinNumRingConformerTrials, 
			 (python::arg("self"), python::arg("min_num")))
		.def("getMinNumRingConformerTrials", &ConfGen::FragmentLibraryGenerator::getMinNumRingConformerTrials, 
			 python::arg("self"))
		.def("setMinRMSD", &ConfGen::FragmentLibraryGenerator::setMinRMSD,
			 (python::arg("self"), python::arg("min_rmsd")))
		.def("getMinRMSD", &ConfGen::FragmentLibraryGenerator::getMinRMSD,
			 python::arg("self"))
		.def("setMaxNumOutputConformers", &ConfGen::FragmentLibraryGenerator::setMaxNumOutputConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumOutputConformers", &ConfGen::FragmentLibraryGenerator::getMaxNumOutputConformers, 
			 python::arg("self"))
		.def("process", &ConfGen::FragmentLibraryGenerator::process, 
			 (python::arg("self"), python::arg("molgraph")))
		.add_property("resultCallback", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getProcessingResultCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentLibraryGenerator::setProcessingResultCallback)
		.add_property("errorCallback", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getProcessingErrorCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentLibraryGenerator::setProcessingErrorCallback)
		.add_property("progressCallback", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getProgressCallback,
											python::return_internal_reference<>()),
					  &ConfGen::FragmentLibraryGenerator::setProgressCallback)
		.add_property("fragmentLibrary", 
					  python::make_function(&ConfGen::FragmentLibraryGenerator::getFragmentLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::FragmentLibraryGenerator::setFragmentLibrary)
		.add_property("maxNumStructGenTrials", &ConfGen::FragmentLibraryGenerator::getMaxNumStructureGenerationTrials, 
					  &ConfGen::FragmentLibraryGenerator::setMaxNumStructureGenerationTrials)
		.add_property("maxNumMinimizationSteps", &ConfGen::FragmentLibraryGenerator::getMaxNumMinimizationSteps, 
					  &ConfGen::FragmentLibraryGenerator::setMaxNumMinimizationSteps)
		.add_property("maxNumOutputConformers", &ConfGen::FragmentLibraryGenerator::getMaxNumOutputConformers, 
					  &ConfGen::FragmentLibraryGenerator::setMaxNumOutputConformers)
		.add_property("minimizationStopGradientNorm", &ConfGen::FragmentLibraryGenerator::getMinimizationStopGradientNorm,
					  &ConfGen::FragmentLibraryGenerator::setMinimizationStopGradientNorm)
		.add_property("minimizationStopEnergyDelta", &ConfGen::FragmentLibraryGenerator::getMinimizationStopEnergyDelta,
					  &ConfGen::FragmentLibraryGenerator::setMinimizationStopEnergyDelta)
		.add_property("timeout", &ConfGen::FragmentLibraryGenerator::getTimeout,
					  &ConfGen::FragmentLibraryGenerator::setTimeout)
		.add_property("reuseExistingCoords", &ConfGen::FragmentLibraryGenerator::existingCoordinatesReused,
					  &ConfGen::FragmentLibraryGenerator::reuseExistingCoordinates)
		.add_property("energyWindow", &ConfGen::FragmentLibraryGenerator::getEnergyWindow,
					  &ConfGen::FragmentLibraryGenerator::setEnergyWindow)
		.add_property("ringConfTrialFactor", &ConfGen::FragmentLibraryGenerator::getRingConformerTrialFactor,
					  &ConfGen::FragmentLibraryGenerator::setRingConformerTrialFactor)
		.add_property("maxNumRingConfTrials", &ConfGen::FragmentLibraryGenerator::getMaxNumRingConformerTrials,
					  &ConfGen::FragmentLibraryGenerator::setMaxNumRingConformerTrials)
		.add_property("minNumRingConfTrials", &ConfGen::FragmentLibraryGenerator::getMinNumRingConformerTrials,
					  &ConfGen::FragmentLibraryGenerator::setMinNumRingConformerTrials)
		.add_property("minRMSD", &ConfGen::FragmentLibraryGenerator::getMinRMSD,
					  &ConfGen::FragmentLibraryGenerator::setMinRMSD);
}
