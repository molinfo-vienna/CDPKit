/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGeneratorExport.cpp 
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

#include "CDPL/ConfGen/SystematicConformerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportSystematicConformerGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::SystematicConformerGenerator, boost::noncopyable> cl("SystematicConformerGenerator", python::no_init);
	python::scope scope = cl;

	python::class_<ConfGen::SystematicConformerGenerator::Settings>("Settings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::SystematicConformerGenerator::Settings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::SystematicConformerGenerator::Settings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::SystematicConformerGenerator::Settings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("enumerateHeteroAtomHydrogens", &ConfGen::SystematicConformerGenerator::Settings::enumerateHeteroAtomHydrogens, 
			 (python::arg("self"), python::arg("enable")))
		.def("heteroAtomHydrogensEnumerated", &ConfGen::SystematicConformerGenerator::Settings::heteroAtomHydrogensEnumerated, 
			 python::arg("self"))
		.def("enumerateRings", &ConfGen::SystematicConformerGenerator::Settings::enumerateRings, 
			 (python::arg("self"), python::arg("enumerate")))
		.def("ringsEnumerated", &ConfGen::SystematicConformerGenerator::Settings::ringsEnumerated, 
			 python::arg("self"))
		.def("enumerateNitrogens", &ConfGen::SystematicConformerGenerator::Settings::enumerateNitrogens, 
			 (python::arg("self"), python::arg("enumerate")))
		.def("nitrogensEnumerated", &ConfGen::SystematicConformerGenerator::Settings::nitrogensEnumerated, 
			 python::arg("self"))
		.def("reuseExistingCoordinates", &ConfGen::SystematicConformerGenerator::Settings::reuseExistingCoordinates, 
			 (python::arg("self"), python::arg("reuse")))
		.def("existingCoordinatesReused", &ConfGen::SystematicConformerGenerator::Settings::existingCoordinatesReused, 
			 python::arg("self"))
		.def("setEnergyWindow", &ConfGen::SystematicConformerGenerator::Settings::setEnergyWindow, 
			 (python::arg("self"), python::arg("win_size")))
		.def("getEnergyWindow", &ConfGen::SystematicConformerGenerator::Settings::getEnergyWindow, 
			 python::arg("self"))
		.def("setTimeout", &ConfGen::SystematicConformerGenerator::Settings::setTimeout, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getTimeout", &ConfGen::SystematicConformerGenerator::Settings::getTimeout, 
			 python::arg("self"))
		.def("setMaxFragmentBuildTime", &ConfGen::SystematicConformerGenerator::Settings::setMaxFragmentBuildTime, 
			 (python::arg("self"), python::arg("mil_secs")))
		.def("getMaxFragmentBuildTime", &ConfGen::SystematicConformerGenerator::Settings::getMaxFragmentBuildTime, 
			 python::arg("self"))
		.def("setFragmentLibrary", &ConfGen::SystematicConformerGenerator::Settings::setFragmentLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getFragmentLibrary", &ConfGen::SystematicConformerGenerator::Settings::getFragmentLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setTorsionLibrary", &ConfGen::SystematicConformerGenerator::Settings::setTorsionLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getTorsionLibrary", &ConfGen::SystematicConformerGenerator::Settings::getTorsionLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("performStrictAtomTyping", &ConfGen::SystematicConformerGenerator::Settings::performStrictAtomTyping, 
			 (python::arg("self"), python::arg("strict")))
		.def("strictAtomTypingPerformed", &ConfGen::SystematicConformerGenerator::Settings::strictAtomTypingPerformed, 
			 python::arg("self"))
		.def("setSearchForceFieldType", &ConfGen::SystematicConformerGenerator::Settings::setSearchForceFieldType, 
			 (python::arg("self"), python::arg("type")))
		.def("getSearchForceFieldType", &ConfGen::SystematicConformerGenerator::Settings::getSearchForceFieldType, 
			 python::arg("self"))
		.def("setBuildForceFieldType", &ConfGen::SystematicConformerGenerator::Settings::setBuildForceFieldType, 
			 (python::arg("self"), python::arg("type")))
		.def("getBuildForceFieldType", &ConfGen::SystematicConformerGenerator::Settings::getBuildForceFieldType, 
			 python::arg("self"))

		.add_property("enumHeteroAtomHydrogens", &ConfGen::SystematicConformerGenerator::Settings::heteroAtomHydrogensEnumerated,
					  &ConfGen::SystematicConformerGenerator::Settings::enumerateHeteroAtomHydrogens)
		.add_property("enumRings", &ConfGen::SystematicConformerGenerator::Settings::ringsEnumerated,
					  &ConfGen::SystematicConformerGenerator::Settings::enumerateRings)
		.add_property("enumNitrogens", &ConfGen::SystematicConformerGenerator::Settings::nitrogensEnumerated,
					  &ConfGen::SystematicConformerGenerator::Settings::enumerateNitrogens)
		.add_property("reuseExistingCoords", &ConfGen::SystematicConformerGenerator::Settings::existingCoordinatesReused,
					  &ConfGen::SystematicConformerGenerator::Settings::reuseExistingCoordinates)
		.add_property("energyWindow", &ConfGen::SystematicConformerGenerator::Settings::getEnergyWindow,
					  &ConfGen::SystematicConformerGenerator::Settings::setEnergyWindow)
		.add_property("timeout", &ConfGen::SystematicConformerGenerator::Settings::getTimeout,
					  &ConfGen::SystematicConformerGenerator::Settings::setTimeout)
		.add_property("maxFragBuildTime", &ConfGen::SystematicConformerGenerator::Settings::getMaxFragmentBuildTime,
					  &ConfGen::SystematicConformerGenerator::Settings::setMaxFragmentBuildTime)
		.add_property("fragmentLibrary", 
					  python::make_function(&ConfGen::SystematicConformerGenerator::Settings::getFragmentLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::SystematicConformerGenerator::Settings::setFragmentLibrary)
		.add_property("torsionLibrary", 
					  python::make_function(&ConfGen::SystematicConformerGenerator::Settings::getTorsionLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::SystematicConformerGenerator::Settings::setTorsionLibrary)
		.add_property("strictAtomTyping", &ConfGen::SystematicConformerGenerator::Settings::strictAtomTypingPerformed, 
					  &ConfGen::SystematicConformerGenerator::Settings::performStrictAtomTyping)
		.add_property("searchForceFieldType", &ConfGen::SystematicConformerGenerator::Settings::getSearchForceFieldType, 
					  &ConfGen::SystematicConformerGenerator::Settings::setSearchForceFieldType)
		.add_property("buildForceFieldType", &ConfGen::SystematicConformerGenerator::Settings::getBuildForceFieldType, 
					  &ConfGen::SystematicConformerGenerator::Settings::setBuildForceFieldType)

		.def_readonly("DEF_TIMEOUT", ConfGen::SystematicConformerGenerator::Settings::DEF_TIMEOUT)
		.def_readonly("DEF_MAX_FRAG_BUILD_TIME", ConfGen::SystematicConformerGenerator::Settings::DEF_MAX_FRAG_BUILD_TIME)
		.def_readonly("DEF_SEARCH_FORCE_FIELD_TYPE", ConfGen::SystematicConformerGenerator::Settings::DEF_SEARCH_FORCE_FIELD_TYPE)
		.def_readonly("DEF_BUILD_FORCE_FIELD_TYPE", ConfGen::SystematicConformerGenerator::Settings::DEF_BUILD_FORCE_FIELD_TYPE)
		.def_readonly("DEF_ENERGY_WINDOW", ConfGen::SystematicConformerGenerator::Settings::DEF_ENERGY_WINDOW)
		;

	cl
		.def(python::init<>(python::arg("self")))
//		.def(python::init<const ConfGen::SystematicConformerGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::SystematicConformerGenerator>())
//		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::SystematicConformerGenerator::operator=), 
//			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("generate", &ConfGen::SystematicConformerGenerator::generate, 
			 (python::arg("self"), python::arg("molgraph")))
		.def("applySettings", &ConfGen::SystematicConformerGenerator::applySettings, 
			 (python::arg("self"), python::arg("settings")))
		.def("getSettings", &ConfGen::SystematicConformerGenerator::getSettings, 
			 python::arg("self"), python::return_internal_reference<>())
		.add_property("settings", python::make_function(&ConfGen::SystematicConformerGenerator::getSettings,
														python::return_internal_reference<>()),
					  &ConfGen::SystematicConformerGenerator::applySettings)
		;
}
