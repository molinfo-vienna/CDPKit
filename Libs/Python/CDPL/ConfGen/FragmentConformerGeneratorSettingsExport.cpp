/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorSettingsExport.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentConformerGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::FragmentConformerGeneratorSettings> cl("FragmentConformerGeneratorSettings", python::no_init);
	python::scope scope = cl;

	python::class_<ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings>("RingFragmentSettings")
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("setMaxNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMaxNumSampledConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMaxNumSampledConformers, 
			 python::arg("self"))
		.def("setMinNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMinNumSampledConformers, 
			 (python::arg("self"), python::arg("min_num")))
		.def("getMinNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMinNumSampledConformers, 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getTimeout, 
			 python::arg("self"))
		.def("setEnergyWindow", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setEnergyWindow, 
			 (python::arg("self"), python::arg("win_size")))
		.def("getEnergyWindow", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getEnergyWindow, 
			 python::arg("self"))
		.def("setMaxNumOutputConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMaxNumOutputConformers, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumOutputConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMaxNumOutputConformers, 
			 python::arg("self"))
		.def("setMinRMSD", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMinRMSD, 
			 (python::arg("self"), python::arg("min_rmsd")))
		.def("getMinRMSD", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMinRMSD, 
			 python::arg("self"))
		.add_property("maxNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMaxNumSampledConformers, 
					  &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMaxNumSampledConformers)
		.add_property("minNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMinNumSampledConformers, 
					  &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMinNumSampledConformers)
		.add_property("timeout", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getTimeout,
					  &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setTimeout)
		.add_property("energyWindow", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getEnergyWindow,
					  &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setEnergyWindow)
		.add_property("maxNumOutputConformers", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMaxNumOutputConformers, 
					  &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMaxNumOutputConformers)
		.add_property("minRMSD", &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMinRMSD, 
					  &ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMinRMSD);

	typedef void (ConfGen::FragmentConformerGeneratorSettings::*SetBoolFunc)(bool);
	typedef bool (ConfGen::FragmentConformerGeneratorSettings::*GetBoolFunc)() const;

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::FragmentConformerGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentConformerGeneratorSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentConformerGeneratorSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("setForceFieldType", &ConfGen::FragmentConformerGeneratorSettings::setForceFieldType, 
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::FragmentConformerGeneratorSettings::getForceFieldType, 
			 python::arg("self"))
		.def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization), 
			 (python::arg("self"), python::arg("strict")))
		.def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization), 
			 python::arg("self"))
		.def("setMaxNumRefinementIterations", &ConfGen::FragmentConformerGeneratorSettings::setMaxNumRefinementIterations, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumRefinementIterations", &ConfGen::FragmentConformerGeneratorSettings::getMaxNumRefinementIterations, 
			 python::arg("self"))
		.def("setRefinementStopGradient", &ConfGen::FragmentConformerGeneratorSettings::setRefinementStopGradient, 
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getRefinementStopGradient", &ConfGen::FragmentConformerGeneratorSettings::getRefinementStopGradient, 
			 python::arg("self"))
		.def("setMinMacrocycleSize", &ConfGen::FragmentConformerGeneratorSettings::setMinMacrocycleSize, 
			 (python::arg("self"), python::arg("max_size")))
		.def("getMinMacrocycleSize", &ConfGen::FragmentConformerGeneratorSettings::getMinMacrocycleSize, 
			 python::arg("self"))
		.def("getMacrocycleSettings", 
			 static_cast<ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
			 (&ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings),
			 python::arg("self"), python::return_internal_reference<>())
		.def("getSmallRingSystemSettings", 
			 static_cast<ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
			 (&ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setSmallRingSystemSamplingFactor", &ConfGen::FragmentConformerGeneratorSettings::setSmallRingSystemSamplingFactor, 
			 (python::arg("self"), python::arg("min_rmsd")))
		.def("getSmallRingSystemSamplingFactor", &ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSamplingFactor, 
			 python::arg("self"))
		.def_readonly("DEFAULT", ConfGen::FragmentConformerGeneratorSettings::DEFAULT)
		.add_property("forceFieldType", &ConfGen::FragmentConformerGeneratorSettings::getForceFieldType, 
					  &ConfGen::FragmentConformerGeneratorSettings::setForceFieldType)
		.add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization), 
					  SetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization))
		.add_property("maxNumRefinementIterations", &ConfGen::FragmentConformerGeneratorSettings::getMaxNumRefinementIterations, 
					  &ConfGen::FragmentConformerGeneratorSettings::setMaxNumRefinementIterations)
		.add_property("minimizationStopGradientNorm", &ConfGen::FragmentConformerGeneratorSettings::getRefinementStopGradient,
					  &ConfGen::FragmentConformerGeneratorSettings::setRefinementStopGradient)
		.add_property("minMacrocycleSize", &ConfGen::FragmentConformerGeneratorSettings::getMinMacrocycleSize, 
					  &ConfGen::FragmentConformerGeneratorSettings::setMinMacrocycleSize)
		.add_property("macrocycleSettings", 
					  python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
											(&ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings),
											python::return_internal_reference<>()))
		.add_property("smallRingSysSettings", 
					  python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
											(&ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings),
											python::return_internal_reference<>()))
		.add_property("smallRingSysSamplingFactor", &ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSamplingFactor, 
					  &ConfGen::FragmentConformerGeneratorSettings::setSmallRingSystemSamplingFactor);
}
