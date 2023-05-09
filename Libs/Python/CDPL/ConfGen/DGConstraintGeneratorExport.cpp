/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGConstraintGeneratorExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/ConfGen/DGConstraintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	void addAtomStereoCenter(CDPL::ConfGen::DGConstraintGenerator& gen, CDPL::Chem::Atom& atom, const CDPL::Chem::StereoDescriptor& descr) 
	{
		gen.addAtomStereoCenter(atom, descr);
	}

	void addBondStereoCenter(CDPL::ConfGen::DGConstraintGenerator& gen, CDPL::Chem::Bond& bond, const CDPL::Chem::StereoDescriptor& descr) 
	{
		gen.addBondStereoCenter(bond, descr);
	}
}


void CDPLPythonConfGen::exportDGConstraintGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::DGConstraintGenerator> cl("DGConstraintGenerator", python::no_init);

	python::scope scope = cl;

	python::class_<ConfGen::DGConstraintGenerator::StereoCenterData>("StereoCenterData", python::no_init)
		.def(python::init<std::size_t, const Chem::StereoDescriptor&>((python::arg("self"), python::arg("ctr_idx"), python::arg("descr"))))
		.def(python::init<const ConfGen::DGConstraintGenerator::StereoCenterData&>((python::arg("self"), python::arg("data"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::DGConstraintGenerator::StereoCenterData>())
		.add_property("centerIndex", &ConfGen::DGConstraintGenerator::StereoCenterData::first)
		.add_property("descriptor", &ConfGen::DGConstraintGenerator::StereoCenterData::second);

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::DGConstraintGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::DGConstraintGenerator>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::DGConstraintGenerator::operator=), 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("getExcludedHydrogenMask", &ConfGen::DGConstraintGenerator::getExcludedHydrogenMask, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("addAtomStereoCenter", &addAtomStereoCenter, (python::arg("atom"), python::arg("descr")))
		.def("addBondStereoCenter", &addBondStereoCenter, (python::arg("bond"), python::arg("descr")))
		.def("setup", static_cast<void (ConfGen::DGConstraintGenerator::*)(const Chem::MolecularGraph&)>
			 (&ConfGen::DGConstraintGenerator::setup), (python::arg("self"), python::arg("molgraph")))
		.def("setup", static_cast<void (ConfGen::DGConstraintGenerator::*)(const Chem::MolecularGraph&, const ForceField::MMFF94InteractionData&)>
			 (&ConfGen::DGConstraintGenerator::setup), 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data")))
		.def("getNumAtomStereoCenters", &ConfGen::DGConstraintGenerator::getNumAtomStereoCenters, python::arg("self"))
		.def("getAtomStereoCenterData", &ConfGen::DGConstraintGenerator::getAtomStereoCenterData,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("getBondStereoCenterData", &ConfGen::DGConstraintGenerator::getBondStereoCenterData,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("getNumBondStereoCenters", &ConfGen::DGConstraintGenerator::getNumBondStereoCenters, python::arg("self"))
		.def("addBondLengthConstraints", &ConfGen::DGConstraintGenerator::addBondLengthConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addBondAngleConstraints", &ConfGen::DGConstraintGenerator::addBondAngleConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("add14DistanceConstraints", &ConfGen::DGConstraintGenerator::add14DistanceConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addDefaultDistanceConstraints", &ConfGen::DGConstraintGenerator::addDefaultDistanceConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addAtomPlanarityConstraints", &ConfGen::DGConstraintGenerator::addAtomPlanarityConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addBondPlanarityConstraints", &ConfGen::DGConstraintGenerator::addBondPlanarityConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addAtomConfigurationConstraints", &ConfGen::DGConstraintGenerator::addAtomConfigurationConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addBondConfigurationConstraints", &ConfGen::DGConstraintGenerator::addBondConfigurationConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("getSettings", 
			 static_cast<ConfGen::DGConstraintGeneratorSettings& (ConfGen::DGConstraintGenerator::*)()>
			 (&ConfGen::DGConstraintGenerator::getSettings), 
			 python::arg("self"), python::return_internal_reference<>())
		.add_property("settings", 
					  python::make_function(static_cast<ConfGen::DGConstraintGeneratorSettings& (ConfGen::DGConstraintGenerator::*)()>
											(&ConfGen::DGConstraintGenerator::getSettings),
											python::return_internal_reference<>()))
		.add_property("numAtomStereoCenters",  &ConfGen::DGConstraintGenerator::getNumAtomStereoCenters)
		.add_property("numBondStereoCenters",  &ConfGen::DGConstraintGenerator::getNumBondStereoCenters)
		.add_property("exclHydrogenMask", python::make_function(&ConfGen::DGConstraintGenerator::getExcludedHydrogenMask, 
																python::return_internal_reference<>()));
}
