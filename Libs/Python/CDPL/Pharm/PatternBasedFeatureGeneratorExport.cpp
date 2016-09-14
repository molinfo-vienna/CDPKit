/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedFeatureGeneratorExport.cpp 
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

#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportPatternBasedFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Pharm::PatternBasedFeatureGenerator, python::bases<Pharm::FeatureGenerator>, 
										 boost::noncopyable>("PatternBasedFeatureGenerator", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Pharm::PatternBasedFeatureGenerator&>(
		 (python::arg("self"), python::arg("gen"))))
	.def("addIncludePattern", &Pharm::PatternBasedFeatureGenerator::addIncludePattern, 
	     (python::arg("self"), python::arg("substruct"), python::arg("type"), python::arg("tol"),
	      python::arg("geom"), python::arg("length") = 1.0))
	.def("addExcludePattern", &Pharm::PatternBasedFeatureGenerator::addExcludePattern, 
	     (python::arg("self"), python::arg("substruct")))
	.def("clearIncludePatterns", &Pharm::PatternBasedFeatureGenerator::clearIncludePatterns, 
	     python::arg("self"))
	.def("clearExcludePatterns", &Pharm::PatternBasedFeatureGenerator::clearExcludePatterns, 
	     python::arg("self"))
	.def("assign", &Pharm::PatternBasedFeatureGenerator::operator=, 
	     (python::arg("self"), python::arg("gen")), python::return_self<>())
	.def("generate", &Pharm::PatternBasedFeatureGenerator::generate,
	     (python::arg("self"), python::arg("molgraph"), python::arg("pharm")))
	.def("__call__", &Pharm::PatternBasedFeatureGenerator::generate,
	     (python::arg("self"), python::arg("molgraph"), python::arg("pharm")));

	python::enum_<Pharm::PatternBasedFeatureGenerator::PatternAtomLabelFlag>("PatternAtomLabelFlag")
		.value("FEATURE_ATOM_FLAG", Pharm::PatternBasedFeatureGenerator::FEATURE_ATOM_FLAG)
		.value("POS_REF_ATOM_FLAG", Pharm::PatternBasedFeatureGenerator::POS_REF_ATOM_FLAG)
		.value("GEOM_REF_ATOM1_FLAG", Pharm::PatternBasedFeatureGenerator::GEOM_REF_ATOM1_FLAG)
		.value("GEOM_REF_ATOM2_FLAG", Pharm::PatternBasedFeatureGenerator::GEOM_REF_ATOM2_FLAG)
		.export_values();
}
