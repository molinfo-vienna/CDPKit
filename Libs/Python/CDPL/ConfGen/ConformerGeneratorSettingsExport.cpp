/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorSettingsExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportConformerGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (ConfGen::ConformerGeneratorSettings::*SetBoolFunc)(bool);
	typedef bool (ConfGen::ConformerGeneratorSettings::*GetBoolFunc)() const;

	python::class_<ConfGen::ConformerGeneratorSettings>("ConformerGeneratorSettings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::ConformerGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::ConformerGeneratorSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::ConformerGeneratorSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("setSamplingMode", &ConfGen::ConformerGeneratorSettings::setSamplingMode, 
			 (python::arg("self"), python::arg("mode")))
		.def("getSamplingMode", &ConfGen::ConformerGeneratorSettings::getSamplingMode, 
			 python::arg("self"))
		.def("sampleHeteroAtomHydrogens", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens), 
			 (python::arg("self"), python::arg("sample")))
		.def("sampleHeteroAtomHydrogens", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens), 
			 python::arg("self"))
		.def("sampleAngleToleranceRanges", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleAngleToleranceRanges), 
			 (python::arg("self"), python::arg("sample")))
		.def("sampleAngleToleranceRanges", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleAngleToleranceRanges), 
			 python::arg("self"))
		.def("enumerateRings", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::enumerateRings), 
			 (python::arg("self"), python::arg("enumerate")))
		.def("enumerateRings", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::enumerateRings), 
			 python::arg("self"))
		.def("setNitrogenEnumerationMode", &ConfGen::ConformerGeneratorSettings::setNitrogenEnumerationMode, 
			 (python::arg("self"), python::arg("mode")))
		.def("getNitrogenEnumerationMode", &ConfGen::ConformerGeneratorSettings::getNitrogenEnumerationMode, 
			 python::arg("self"))
		.def("generateCoordinatesFromScratch", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::generateCoordinatesFromScratch), 
			 (python::arg("self"), python::arg("generate")))
		.def("generateCoordinatesFromScratch", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::generateCoordinatesFromScratch), 
			 python::arg("self"))
		.def("includeInputCoordinates", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::includeInputCoordinates), 
			 (python::arg("self"), python::arg("include")))
		.def("includeInputCoordinates", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::includeInputCoordinates), 
			 python::arg("self"))
		.def("setEnergyWindow", &ConfGen::ConformerGeneratorSettings::setEnergyWindow, 
			 (python::arg("self"), python::arg("win_size")))
		.def("getEnergyWindow", &ConfGen::ConformerGeneratorSettings::getEnergyWindow, 
			 python::arg("self"))
		.def("setMaxPoolSize", &ConfGen::ConformerGeneratorSettings::setMaxPoolSize, 
			 (python::arg("self"), python::arg("max_size")))
		.def("getMaxPoolSize", &ConfGen::ConformerGeneratorSettings::getMaxPoolSize, 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::ConformerGeneratorSettings::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::ConformerGeneratorSettings::getTimeout, 
			 python::arg("self"))
		.def("setForceFieldTypeSystematic", &ConfGen::ConformerGeneratorSettings::setForceFieldTypeSystematic, 
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldTypeSystematic", &ConfGen::ConformerGeneratorSettings::getForceFieldTypeSystematic, 
			 python::arg("self"))
		.def("setForceFieldTypeStochastic", &ConfGen::ConformerGeneratorSettings::setForceFieldTypeStochastic, 
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldTypeStochastic", &ConfGen::ConformerGeneratorSettings::getForceFieldTypeStochastic, 
			 python::arg("self"))
		.def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization), 
			 (python::arg("self"), python::arg("strict")))
		.def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization), 
			 python::arg("self"))
		.def("setDielectricConstant", &ConfGen::ConformerGeneratorSettings::setDielectricConstant, 
			 (python::arg("self"), python::arg("de_const")))
		.def("getDielectricConstant", &ConfGen::ConformerGeneratorSettings::getDielectricConstant, 
			 python::arg("self"))
		.def("setDistanceExponent", &ConfGen::ConformerGeneratorSettings::setDistanceExponent, 
			 (python::arg("self"), python::arg("dist_expo")))
		.def("getDistanceExponent", &ConfGen::ConformerGeneratorSettings::getDistanceExponent, 
			 python::arg("self"))
		.def("setMaxNumOutputConformers", &ConfGen::ConformerGeneratorSettings::setMaxNumOutputConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumOutputConformers", &ConfGen::ConformerGeneratorSettings::getMaxNumOutputConformers, 
			 python::arg("self"))
		.def("setMinRMSD", &ConfGen::ConformerGeneratorSettings::setMinRMSD, 
			 (python::arg("self"), python::arg("min_rmsd")))
		.def("getMinRMSD", &ConfGen::ConformerGeneratorSettings::getMinRMSD, 
			 python::arg("self"))
		.def("setMaxNumRefinementIterations", &ConfGen::ConformerGeneratorSettings::setMaxNumRefinementIterations, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRefinementIterations", &ConfGen::ConformerGeneratorSettings::getMaxNumRefinementIterations, 
			 python::arg("self"))
		.def("setRefinementStopGradient", &ConfGen::ConformerGeneratorSettings::setRefinementStopGradient, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getRefinementStopGradient", &ConfGen::ConformerGeneratorSettings::getRefinementStopGradient, 
			 python::arg("self"))
		.def("setMaxNumSampledConformers", &ConfGen::ConformerGeneratorSettings::setMaxNumSampledConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumSampledConformers", &ConfGen::ConformerGeneratorSettings::getMaxNumSampledConformers, 
			 python::arg("self"))
		.def("setConvergenceIterationCount", &ConfGen::ConformerGeneratorSettings::setConvergenceIterationCount, 
			 (python::arg("self"), python::arg("count")))
		.def("getConvergenceIterationCount", &ConfGen::ConformerGeneratorSettings::getConvergenceIterationCount, 
			 python::arg("self"))
		.def("setMacrocycleRotorBondCountThreshold", &ConfGen::ConformerGeneratorSettings::setMacrocycleRotorBondCountThreshold, 
			 (python::arg("self"), python::arg("max_size")))
		.def("getMacrocycleRotorBondCountThreshold", &ConfGen::ConformerGeneratorSettings::getMacrocycleRotorBondCountThreshold, 
			 python::arg("self"))
		.def("getFragmentBuildSettings", 
			 static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::ConformerGeneratorSettings::*)()>
			 (&ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings),
			 python::arg("self"), python::return_internal_reference<>())
		.def_readonly("DEFAULT", ConfGen::ConformerGeneratorSettings::DEFAULT)
		.def_readonly("SMALL_SET_DIVERSE", ConfGen::ConformerGeneratorSettings::SMALL_SET_DIVERSE)
		.def_readonly("MEDIUM_SET_DIVERSE", ConfGen::ConformerGeneratorSettings::MEDIUM_SET_DIVERSE)
		.def_readonly("LARGE_SET_DIVERSE", ConfGen::ConformerGeneratorSettings::LARGE_SET_DIVERSE)
		.def_readonly("SMALL_SET_DENSE", ConfGen::ConformerGeneratorSettings::SMALL_SET_DENSE)
		.def_readonly("MEDIUM_SET_DENSE", ConfGen::ConformerGeneratorSettings::MEDIUM_SET_DENSE)
		.def_readonly("LARGE_SET_DENSE", ConfGen::ConformerGeneratorSettings::LARGE_SET_DENSE)
		.add_property("samplingMode", &ConfGen::ConformerGeneratorSettings::getSamplingMode,
					  &ConfGen::ConformerGeneratorSettings::setSamplingMode)
		.add_property("sampleHetAtomHydrogens", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens),
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens))
		.add_property("sampleAngleTolRanges", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleAngleToleranceRanges),
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleAngleToleranceRanges))
		.add_property("enumRings", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::enumerateRings),
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::enumerateRings))
		.add_property("nitrogenEnumMode", &ConfGen::ConformerGeneratorSettings::getNitrogenEnumerationMode,
					  &ConfGen::ConformerGeneratorSettings::setNitrogenEnumerationMode)
		.add_property("genCoordsFromScratch", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::generateCoordinatesFromScratch),
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::generateCoordinatesFromScratch))
		.add_property("includeInputCoords", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::includeInputCoordinates),
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::includeInputCoordinates))
		.add_property("energyWindow", &ConfGen::ConformerGeneratorSettings::getEnergyWindow,
					  &ConfGen::ConformerGeneratorSettings::setEnergyWindow)
		.add_property("maxPoolSize", &ConfGen::ConformerGeneratorSettings::getMaxPoolSize,
					  &ConfGen::ConformerGeneratorSettings::setMaxPoolSize)
		.add_property("timeout", &ConfGen::ConformerGeneratorSettings::getTimeout,
					  &ConfGen::ConformerGeneratorSettings::setTimeout)
		.add_property("forceFieldTypeSystematic", &ConfGen::ConformerGeneratorSettings::getForceFieldTypeSystematic, 
					  &ConfGen::ConformerGeneratorSettings::setForceFieldTypeSystematic)
		.add_property("forceFieldTypeStochastic", &ConfGen::ConformerGeneratorSettings::getForceFieldTypeStochastic, 
					  &ConfGen::ConformerGeneratorSettings::setForceFieldTypeStochastic)
		.add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization), 
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization))
		.add_property("dielectricConstant", &ConfGen::ConformerGeneratorSettings::getDielectricConstant, 
					  &ConfGen::ConformerGeneratorSettings::setDielectricConstant)
		.add_property("distanceExponent", &ConfGen::ConformerGeneratorSettings::getDistanceExponent, 
					  &ConfGen::ConformerGeneratorSettings::setDistanceExponent)
		.add_property("maxNumOutputConformers", &ConfGen::ConformerGeneratorSettings::getMaxNumOutputConformers, 
					  &ConfGen::ConformerGeneratorSettings::setMaxNumOutputConformers)
		.add_property("minRMSD", &ConfGen::ConformerGeneratorSettings::getMinRMSD, 
					  &ConfGen::ConformerGeneratorSettings::setMinRMSD)
		.add_property("maxNumRefinementIterations", &ConfGen::ConformerGeneratorSettings::getMaxNumRefinementIterations, 
					  &ConfGen::ConformerGeneratorSettings::setMaxNumRefinementIterations)
		.add_property("refinementStopGradient", &ConfGen::ConformerGeneratorSettings::getRefinementStopGradient,
					  &ConfGen::ConformerGeneratorSettings::setRefinementStopGradient)
		.add_property("maxNumSampledConformers", &ConfGen::ConformerGeneratorSettings::getMaxNumSampledConformers, 
					  &ConfGen::ConformerGeneratorSettings::setMaxNumSampledConformers)
		.add_property("convergenceIterationCount", &ConfGen::ConformerGeneratorSettings::getConvergenceIterationCount, 
					  &ConfGen::ConformerGeneratorSettings::setConvergenceIterationCount)
		.add_property("macrocycleRotorBondCountThresh", &ConfGen::ConformerGeneratorSettings::getMacrocycleRotorBondCountThreshold, 
					  &ConfGen::ConformerGeneratorSettings::setMacrocycleRotorBondCountThreshold)
		.add_property("fragmentBuildSettings", 
					  python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::ConformerGeneratorSettings::*)()>
											(&ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings),
											python::return_internal_reference<>()));
}
