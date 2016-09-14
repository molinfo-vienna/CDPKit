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

#include "CDPL/Pharm/HydrophobicFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportHydrophobicFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::HydrophobicFeatureGenerator, python::bases<Pharm::PatternBasedFeatureGenerator>, 
				   boost::noncopyable>("HydrophobicFeatureGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Pharm::Pharmacophore&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("pharm"))))
		.def(python::init<const Pharm::HydrophobicFeatureGenerator&>(
				 (python::arg("self"), python::arg("gen"))))
		.def("assign", &Pharm::HydrophobicFeatureGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setFeatureType", &Pharm::HydrophobicFeatureGenerator::setFeatureType, 
			 (python::arg("self"), python::arg("type")))
		.def("setFeatureGeometry", &Pharm::HydrophobicFeatureGenerator::setFeatureGeometry, 
			 (python::arg("self"), python::arg("geom")))
		.def("setFeatureTolerance", &Pharm::HydrophobicFeatureGenerator::setFeatureTolerance, 
			 (python::arg("self"), python::arg("tol")))
		.def("setRingHydrophobicityThreshold", &Pharm::HydrophobicFeatureGenerator::setRingHydrophobicityThreshold, 
			 (python::arg("self"), python::arg("thresh")))
		.def("setChainHydrophobicityThreshold", &Pharm::HydrophobicFeatureGenerator::setChainHydrophobicityThreshold, 
			 (python::arg("self"), python::arg("thresh")))
		.def("setGroupHydrophobicityThreshold", &Pharm::HydrophobicFeatureGenerator::setGroupHydrophobicityThreshold, 
			 (python::arg("self"), python::arg("thresh")))
		.def("getFeatureType", &Pharm::HydrophobicFeatureGenerator::getFeatureType, python::arg("self"))
		.def("getFeatureGeometry", &Pharm::HydrophobicFeatureGenerator::getFeatureGeometry, python::arg("self"))
		.def("getFeatureTolerance", &Pharm::HydrophobicFeatureGenerator::getFeatureTolerance, python::arg("self"))
		.def("getRingHydrophobicityThreshold", &Pharm::HydrophobicFeatureGenerator::getRingHydrophobicityThreshold, python::arg("self"))
		.def("getChainHydrophobicityThreshold", &Pharm::HydrophobicFeatureGenerator::getChainHydrophobicityThreshold, python::arg("self"))
		.def("getGroupHydrophobicityThreshold", &Pharm::HydrophobicFeatureGenerator::getGroupHydrophobicityThreshold, python::arg("self"))
		.def("assign", &Pharm::HydrophobicFeatureGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def_readonly("DEF_FEATURE_TOL", Pharm::HydrophobicFeatureGenerator::DEF_FEATURE_TOL)
		.def_readonly("DEF_FEATURE_TYPE", Pharm::HydrophobicFeatureGenerator::DEF_FEATURE_TYPE)
		.def_readonly("DEF_FEATURE_GEOM", Pharm::HydrophobicFeatureGenerator::DEF_FEATURE_GEOM)
		.def_readonly("DEF_HYD_THRESHOLD_RING", Pharm::HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_RING)
		.def_readonly("DEF_HYD_THRESHOLD_CHAIN", Pharm::HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_CHAIN)
		.def_readonly("DEF_HYD_THRESHOLD_GROUP", Pharm::HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_GROUP)
		.add_property("featureType", &Pharm::HydrophobicFeatureGenerator::getFeatureType,
					  &Pharm::HydrophobicFeatureGenerator::setFeatureType)
		.add_property("featureGeometry", &Pharm::HydrophobicFeatureGenerator::getFeatureGeometry,
					  &Pharm::HydrophobicFeatureGenerator::setFeatureGeometry)
		.add_property("featureTolerance", &Pharm::HydrophobicFeatureGenerator::getFeatureTolerance,
					  &Pharm::HydrophobicFeatureGenerator::setFeatureTolerance)
		.add_property("ringHydThreshold", &Pharm::HydrophobicFeatureGenerator::getRingHydrophobicityThreshold,
					  &Pharm::HydrophobicFeatureGenerator::setRingHydrophobicityThreshold)
		.add_property("chainHydThreshold", &Pharm::HydrophobicFeatureGenerator::getChainHydrophobicityThreshold,
					  &Pharm::HydrophobicFeatureGenerator::setChainHydrophobicityThreshold)
		.add_property("groupHydThreshold", &Pharm::HydrophobicFeatureGenerator::getGroupHydrophobicityThreshold,
					  &Pharm::HydrophobicFeatureGenerator::setGroupHydrophobicityThreshold);
}
