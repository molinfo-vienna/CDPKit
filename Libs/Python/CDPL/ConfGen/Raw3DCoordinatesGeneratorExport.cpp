/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Raw3DCoordinatesGeneratorExport.cpp 
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

#include "CDPL/ConfGen/Raw3DCoordinatesGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportRaw3DCoordinatesGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::Raw3DCoordinatesGenerator>("Raw3DCoordinatesGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::Raw3DCoordinatesGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::Raw3DCoordinatesGenerator>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::Raw3DCoordinatesGenerator::operator=), 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setBoxSize", &ConfGen::Raw3DCoordinatesGenerator::setBoxSize, 
			 (python::arg("self"), python::arg("size")))
		.def("getBoxSize", &ConfGen::Raw3DCoordinatesGenerator::getBoxSize, python::arg("self"))
		.def("excludeHydrogens", &ConfGen::Raw3DCoordinatesGenerator::excludeHydrogens, 
			 (python::arg("self"), python::arg("exclude")))
		.def("hydrogensExcluded", &ConfGen::Raw3DCoordinatesGenerator::hydrogensExcluded, python::arg("self"))
		.def("enablePlanarityConstraints", &ConfGen::Raw3DCoordinatesGenerator::enablePlanarityConstraints, 
			 (python::arg("self"), python::arg("exclude")))
		.def("planarityConstraintsEnabled", &ConfGen::Raw3DCoordinatesGenerator::planarityConstraintsEnabled, python::arg("self"))
		.def("regardAtomConfiguration", &ConfGen::Raw3DCoordinatesGenerator::regardAtomConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("atomConfigurationRegarded", &ConfGen::Raw3DCoordinatesGenerator::atomConfigurationRegarded, python::arg("self"))
		.def("regardBondConfiguration", &ConfGen::Raw3DCoordinatesGenerator::regardBondConfiguration, 
			 (python::arg("self"), python::arg("regard")))
		.def("bondConfigurationRegarded", &ConfGen::Raw3DCoordinatesGenerator::bondConfigurationRegarded, python::arg("self"))
		.def("getExcludedHydrogenMask", &ConfGen::Raw3DCoordinatesGenerator::getExcludedHydrogenMask, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("setup", static_cast<void (ConfGen::Raw3DCoordinatesGenerator::*)(const Chem::MolecularGraph&)>
			 (&ConfGen::Raw3DCoordinatesGenerator::setup), (python::arg("self"), python::arg("molgraph")))
		.def("setup", static_cast<void (ConfGen::Raw3DCoordinatesGenerator::*)(const Chem::MolecularGraph&, const ForceField::MMFF94InteractionData&)>
			 (&ConfGen::Raw3DCoordinatesGenerator::setup), 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data")))
		.def("generate", &ConfGen::Raw3DCoordinatesGenerator::generate, (python::arg("self"), python::arg("coords")))
		.def("checkAtomConfigurations", &ConfGen::Raw3DCoordinatesGenerator::checkAtomConfigurations,
			 (python::arg("self"), python::arg("coords")))
		.def("checkBondConfigurations", &ConfGen::Raw3DCoordinatesGenerator::checkBondConfigurations,
			 (python::arg("self"), python::arg("coords")))
		.add_property("exclHydrogenMask", python::make_function(&ConfGen::Raw3DCoordinatesGenerator::getExcludedHydrogenMask, 
																python::return_internal_reference<>())) 
		.add_property("boxSize", &ConfGen::Raw3DCoordinatesGenerator::getBoxSize, 
					  &ConfGen::Raw3DCoordinatesGenerator::setBoxSize)
		.add_property("planarityConstraints", &ConfGen::Raw3DCoordinatesGenerator::planarityConstraintsEnabled, 
					  &ConfGen::Raw3DCoordinatesGenerator::enablePlanarityConstraints)
		.add_property("exclHydrogens", &ConfGen::Raw3DCoordinatesGenerator::hydrogensExcluded, 
					  &ConfGen::Raw3DCoordinatesGenerator::excludeHydrogens)
		.add_property("regardAtomConfig", &ConfGen::Raw3DCoordinatesGenerator::atomConfigurationRegarded, 
					  &ConfGen::Raw3DCoordinatesGenerator::regardAtomConfiguration)
		.add_property("regardBondConfig", &ConfGen::Raw3DCoordinatesGenerator::bondConfigurationRegarded, 
					  &ConfGen::Raw3DCoordinatesGenerator::regardBondConfiguration);
}
