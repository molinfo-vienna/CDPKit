/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphDGConstraintGeneratorExport.cpp 
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

#include "CDPL/ConfGen/MolecularGraphDGConstraintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportMolecularGraphDGConstraintGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::MolecularGraphDGConstraintGenerator>("MolecularGraphDGConstraintGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::MolecularGraphDGConstraintGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::MolecularGraphDGConstraintGenerator>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::MolecularGraphDGConstraintGenerator::operator=), 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("excludeHydrogens", &ConfGen::MolecularGraphDGConstraintGenerator::excludeHydrogens, 
			 (python::arg("self"), python::arg("exclude")))
		.def("hydrogensExcluded", &ConfGen::MolecularGraphDGConstraintGenerator::hydrogensExcluded, python::arg("self"))
		.def("regardAtomStereo", &ConfGen::MolecularGraphDGConstraintGenerator::regardAtomStereo, 
			 (python::arg("self"), python::arg("regard")))
		.def("atomStereoRegarded", &ConfGen::MolecularGraphDGConstraintGenerator::atomStereoRegarded, python::arg("self"))
		.def("regardBondStereo", &ConfGen::MolecularGraphDGConstraintGenerator::regardBondStereo, 
			 (python::arg("self"), python::arg("regard")))
		.def("bondStereoRegarded", &ConfGen::MolecularGraphDGConstraintGenerator::bondStereoRegarded, python::arg("self"))
		.def("setup", &ConfGen::MolecularGraphDGConstraintGenerator::setup, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data")))
		.def("addBondLengthConstraints", &ConfGen::MolecularGraphDGConstraintGenerator::addBondLengthConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addBondAngleConstraints", &ConfGen::MolecularGraphDGConstraintGenerator::addBondAngleConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("add14DistanceConstraints", &ConfGen::MolecularGraphDGConstraintGenerator::add14DistanceConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addDefaultDistanceConstraints", &ConfGen::MolecularGraphDGConstraintGenerator::addDefaultDistanceConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addAtomPlanarityConstraints", &ConfGen::MolecularGraphDGConstraintGenerator::addAtomPlanarityConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))
		.def("addBondPlanarityConstraints", &ConfGen::MolecularGraphDGConstraintGenerator::addBondPlanarityConstraints, 
			 (python::arg("self"), python::arg("coords_gen")))

		.add_property("hydrogens", &ConfGen::MolecularGraphDGConstraintGenerator::hydrogensExcluded, 
					  &ConfGen::MolecularGraphDGConstraintGenerator::excludeHydrogens)
		.add_property("atomStereo", &ConfGen::MolecularGraphDGConstraintGenerator::atomStereoRegarded, 
					  &ConfGen::MolecularGraphDGConstraintGenerator::regardAtomStereo)
		.add_property("bondStereo", &ConfGen::MolecularGraphDGConstraintGenerator::bondStereoRegarded, 
					  &ConfGen::MolecularGraphDGConstraintGenerator::regardBondStereo);
}
