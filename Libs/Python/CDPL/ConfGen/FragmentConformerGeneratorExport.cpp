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

	python::class_<ConfGen::FragmentConformerGenerator>("FragmentConformerGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::FragmentConformerGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentConformerGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentConformerGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setMaxNumStructureGenerationTrials", &ConfGen::FragmentConformerGenerator::setMaxNumStructureGenerationTrials, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumStructureGenerationTrials", &ConfGen::FragmentConformerGenerator::getMaxNumStructureGenerationTrials, 
			 python::arg("self"))
		.def("setMaxNumMinimizationSteps", &ConfGen::FragmentConformerGenerator::setMaxNumMinimizationSteps, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumMinimizationSteps", &ConfGen::FragmentConformerGenerator::getMaxNumMinimizationSteps, 
			 python::arg("self"))
		.def("setMinimizationStopGradientNorm", &ConfGen::FragmentConformerGenerator::setMinimizationStopGradientNorm, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getMinimizationStopGradientNorm", &ConfGen::FragmentConformerGenerator::getMinimizationStopGradientNorm, 
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
		.def("setRingConformerRetrialFactor", &ConfGen::FragmentConformerGenerator::setRingConformerRetrialFactor,
			 (python::arg("self"), python::arg("factor")))
		.def("getRingConformerRetrialFactor", &ConfGen::FragmentConformerGenerator::getRingConformerRetrialFactor,
			 python::arg("self"))
		.def("setMinRMSD", &ConfGen::FragmentConformerGenerator::setMinRMSD,
			 (python::arg("self"), python::arg("min_rmsd")))
		.def("getMinRMSD", &ConfGen::FragmentConformerGenerator::getMinRMSD,
			 python::arg("self"))
		.def("setMaxNumRingConformers", &ConfGen::FragmentConformerGenerator::setMaxNumRingConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRingConformers", &ConfGen::FragmentConformerGenerator::getMaxNumRingConformers, 
			 python::arg("self"))
		.def("generate", &ConfGen::FragmentConformerGenerator::generate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("frag_type")))
		.def("getNumConformers", &ConfGen::FragmentConformerGenerator::getNumConformers, python::arg("self"))
		.def("getCoordinates", static_cast<Math::Vector3DArray& (ConfGen::FragmentConformerGenerator::*)(std::size_t)>(
				 &ConfGen::FragmentConformerGenerator::getCoordinates),
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.def("getEnergy", &ConfGen::FragmentConformerGenerator::getEnergy, 
			 (python::arg("self"), python::arg("conf_idx")))
		.def_readonly("DEF_MAX_NUM_STRUCTURE_GEN_TRIALS", ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS)
		.def_readonly("DEF_MAX_NUM_MINIMIZATION_STEPS", ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS)
		.def_readonly("DEF_MAX_NUM_RING_CONFORMERS", ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_RING_CONFORMERS)
		.def_readonly("DEF_TIMEOUT", ConfGen::FragmentConformerGenerator::DEF_TIMEOUT)
		.def_readonly("DEF_RING_CONF_RETRIAL_FACTOR", ConfGen::FragmentConformerGenerator::DEF_RING_CONF_RETRIAL_FACTOR)
		.def_readonly("DEF_MINIMIZATION_STOP_GRADIENT_NORM", ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM)
		.def_readonly("DEF_ENERGY_WINDOW", ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW)
		.def_readonly("DEF_MIN_RMSD", ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD)
		.add_property("numConformers", &ConfGen::FragmentConformerGenerator::getNumConformers) 
		.add_property("maxNumStructGenTrials", &ConfGen::FragmentConformerGenerator::getMaxNumStructureGenerationTrials, 
					  &ConfGen::FragmentConformerGenerator::setMaxNumStructureGenerationTrials)
		.add_property("maxNumMinimizationSteps", &ConfGen::FragmentConformerGenerator::getMaxNumMinimizationSteps, 
					  &ConfGen::FragmentConformerGenerator::setMaxNumMinimizationSteps)
		.add_property("maxNumRingConformers", &ConfGen::FragmentConformerGenerator::getMaxNumRingConformers, 
					  &ConfGen::FragmentConformerGenerator::setMaxNumRingConformers)
		.add_property("minimizationStopGradientNorm", &ConfGen::FragmentConformerGenerator::getMinimizationStopGradientNorm,
					  &ConfGen::FragmentConformerGenerator::setMinimizationStopGradientNorm)
		.add_property("timeout", &ConfGen::FragmentConformerGenerator::getTimeout,
					  &ConfGen::FragmentConformerGenerator::setTimeout)
		.add_property("reuseExistingCoords", &ConfGen::FragmentConformerGenerator::existingCoordinatesReused,
					  &ConfGen::FragmentConformerGenerator::reuseExistingCoordinates)
		.add_property("energyWindow", &ConfGen::FragmentConformerGenerator::getEnergyWindow,
					  &ConfGen::FragmentConformerGenerator::setEnergyWindow)
		.add_property("ringConfRetrialFactor", &ConfGen::FragmentConformerGenerator::getRingConformerRetrialFactor,
					  &ConfGen::FragmentConformerGenerator::setRingConformerRetrialFactor)
		.add_property("minRMSD", &ConfGen::FragmentConformerGenerator::getMinRMSD,
					  &ConfGen::FragmentConformerGenerator::setMinRMSD);
}
