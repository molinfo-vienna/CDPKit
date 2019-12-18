/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorSettingsExport.cpp 
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
		.def("setConformerSamplingMode", &ConfGen::ConformerGeneratorSettings::setConformerSamplingMode, 
			 (python::arg("self"), python::arg("mode")))
		.def("getConformerSamplingMode", &ConfGen::ConformerGeneratorSettings::getConformerSamplingMode, 
			 python::arg("self"))
		.def("sampleHeteroAtomHydrogens", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens), 
			 (python::arg("self"), python::arg("sample")))
		.def("sampleHeteroAtomHydrogens", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens), 
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
		.def("setTimeout", &ConfGen::ConformerGeneratorSettings::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::ConformerGeneratorSettings::getTimeout, 
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::ConformerGeneratorSettings::setForceFieldType, 
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::ConformerGeneratorSettings::getForceFieldType, 
			 python::arg("self"))
		.def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization), 
			 (python::arg("self"), python::arg("strict")))
		.def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization), 
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
		.def("setMinMacrocycleSize", &ConfGen::ConformerGeneratorSettings::setMinMacrocycleSize, 
			 (python::arg("self"), python::arg("max_size")))
		.def("getMinMacrocycleSize", &ConfGen::ConformerGeneratorSettings::getMinMacrocycleSize, 
			 python::arg("self"))
		.def("getFragmentBuildSettings", 
			 static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::ConformerGeneratorSettings::*)()>
			 (&ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings),
			 python::arg("self"), python::return_internal_reference<>())
		.def_readonly("DEFAULT", ConfGen::ConformerGeneratorSettings::DEFAULT)
		.add_property("confSamplingMode", &ConfGen::ConformerGeneratorSettings::getConformerSamplingMode,
					  &ConfGen::ConformerGeneratorSettings::setConformerSamplingMode)
		.add_property("sampleHetAtomHydrogens", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens),
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens))
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
		.add_property("timeout", &ConfGen::ConformerGeneratorSettings::getTimeout,
					  &ConfGen::ConformerGeneratorSettings::setTimeout)
		.add_property("forceFieldType", &ConfGen::ConformerGeneratorSettings::getForceFieldType, 
					  &ConfGen::ConformerGeneratorSettings::setForceFieldType)
		.add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization), 
					  SetBoolFunc(&ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization))
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
		.add_property("minMacrocycleSize", &ConfGen::ConformerGeneratorSettings::getMinMacrocycleSize, 
					  &ConfGen::ConformerGeneratorSettings::setMinMacrocycleSize)
		.add_property("fragmentBuildSettings", 
					  python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::ConformerGeneratorSettings::*)()>
											(&ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings),
											python::return_internal_reference<>()));
}
