/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AromaticFeatureGeneratorExport.cpp 
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

#include "CDPL/Pharm/AromaticFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportAromaticFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::AromaticFeatureGenerator, python::bases<Pharm::PatternBasedFeatureGenerator>, 
				   boost::noncopyable>("AromaticFeatureGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::AromaticFeatureGenerator&>(
				 (python::arg("self"), python::arg("gen"))))
		.def(python::init<const Chem::MolecularGraph&, Pharm::Pharmacophore&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("pharm"))))
		.def("setFeatureType", &Pharm::AromaticFeatureGenerator::setFeatureType, 
			 (python::arg("self"), python::arg("type")))
		.def("setFeatureGeometry", &Pharm::AromaticFeatureGenerator::setFeatureGeometry, 
			 (python::arg("self"), python::arg("geom")))
		.def("setFeatureTolerance", &Pharm::AromaticFeatureGenerator::setFeatureTolerance, 
			 (python::arg("self"), python::arg("tol")))
		.def("getFeatureType", &Pharm::AromaticFeatureGenerator::getFeatureType, python::arg("self"))
		.def("getFeatureGeometry", &Pharm::AromaticFeatureGenerator::getFeatureGeometry, python::arg("self"))
		.def("getFeatureTolerance", &Pharm::AromaticFeatureGenerator::getFeatureTolerance, python::arg("self"))
		.def("assign", &Pharm::AromaticFeatureGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def_readonly("DEF_FEATURE_TOL", Pharm::AromaticFeatureGenerator::DEF_FEATURE_TOL)
		.def_readonly("DEF_FEATURE_TYPE", Pharm::AromaticFeatureGenerator::DEF_FEATURE_TYPE)
		.def_readonly("DEF_FEATURE_GEOM", Pharm::AromaticFeatureGenerator::DEF_FEATURE_GEOM)
		.add_property("featureType", &Pharm::AromaticFeatureGenerator::getFeatureType,
					  &Pharm::AromaticFeatureGenerator::setFeatureType)
		.add_property("featureGeometry", &Pharm::AromaticFeatureGenerator::getFeatureGeometry,
					  &Pharm::AromaticFeatureGenerator::setFeatureGeometry)
		.add_property("featureTolerance", &Pharm::AromaticFeatureGenerator::getFeatureTolerance,
					  &Pharm::AromaticFeatureGenerator::setFeatureTolerance);
}
