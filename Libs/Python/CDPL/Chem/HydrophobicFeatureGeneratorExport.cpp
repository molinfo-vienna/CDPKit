/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HydrophobicFeatureGeneratorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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

#include "CDPL/Chem/HydrophobicFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportHydrophobicFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::HydrophobicFeatureGenerator, python::bases<Chem::PatternBasedFeatureGenerator>,
		   boost::noncopyable>("HydrophobicFeatureGenerator", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Chem::MolecularGraph&, Chem::Pharmacophore&>(
		 (python::arg("self"), python::arg("molgraph"), python::arg("pharm"))))
	.def(python::init<const Chem::HydrophobicFeatureGenerator&>(
		 (python::arg("self"), python::arg("gen"))))
	.def("assign", &Chem::HydrophobicFeatureGenerator::operator=, 
	     (python::arg("self"), python::arg("gen")), python::return_self<>())
	.def("setFeatureType", &Chem::HydrophobicFeatureGenerator::setFeatureType, 
	     (python::arg("self"), python::arg("type")))
	.def("setFeatureGeometry", &Chem::HydrophobicFeatureGenerator::setFeatureGeometry, 
	     (python::arg("self"), python::arg("geom")))
	.def("setFeatureTolerance", &Chem::HydrophobicFeatureGenerator::setFeatureTolerance, 
	     (python::arg("self"), python::arg("tol")))
	.def("setRingHydrophobicityThreshold", &Chem::HydrophobicFeatureGenerator::setRingHydrophobicityThreshold, 
	     (python::arg("self"), python::arg("thresh")))
	.def("setChainHydrophobicityThreshold", &Chem::HydrophobicFeatureGenerator::setChainHydrophobicityThreshold, 
	     (python::arg("self"), python::arg("thresh")))
	.def("setGroupHydrophobicityThreshold", &Chem::HydrophobicFeatureGenerator::setGroupHydrophobicityThreshold, 
	     (python::arg("self"), python::arg("thresh")))
	.def("getFeatureType", &Chem::HydrophobicFeatureGenerator::getFeatureType, python::arg("self"))
	.def("getFeatureGeometry", &Chem::HydrophobicFeatureGenerator::getFeatureGeometry, python::arg("self"))
	.def("getFeatureTolerance", &Chem::HydrophobicFeatureGenerator::getFeatureTolerance, python::arg("self"))
	.def("getRingHydrophobicityThreshold", &Chem::HydrophobicFeatureGenerator::getRingHydrophobicityThreshold, python::arg("self"))
	.def("getChainHydrophobicityThreshold", &Chem::HydrophobicFeatureGenerator::getChainHydrophobicityThreshold, python::arg("self"))
	.def("getGroupHydrophobicityThreshold", &Chem::HydrophobicFeatureGenerator::getGroupHydrophobicityThreshold, python::arg("self"))
	.add_property("featureType", &Chem::HydrophobicFeatureGenerator::getFeatureType,
		      &Chem::HydrophobicFeatureGenerator::setFeatureType)
	.add_property("featureGeometry", &Chem::HydrophobicFeatureGenerator::getFeatureGeometry,
		      &Chem::HydrophobicFeatureGenerator::setFeatureGeometry)
	.add_property("featureTolerance", &Chem::HydrophobicFeatureGenerator::getFeatureTolerance,
		      &Chem::HydrophobicFeatureGenerator::setFeatureTolerance)
	.add_property("ringHydThreshold", &Chem::HydrophobicFeatureGenerator::getRingHydrophobicityThreshold,
		      &Chem::HydrophobicFeatureGenerator::setRingHydrophobicityThreshold)
	.add_property("chainHydThreshold", &Chem::HydrophobicFeatureGenerator::getChainHydrophobicityThreshold,
		      &Chem::HydrophobicFeatureGenerator::setChainHydrophobicityThreshold)
	.add_property("groupHydThreshold", &Chem::HydrophobicFeatureGenerator::getGroupHydrophobicityThreshold,
		      &Chem::HydrophobicFeatureGenerator::setGroupHydrophobicityThreshold);
}
