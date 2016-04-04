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

#include "CDPL/Chem/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportPatternBasedFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::PatternBasedFeatureGenerator, boost::noncopyable>("PatternBasedFeatureGenerator", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Chem::MolecularGraph&, Chem::Pharmacophore&>(
		 (python::arg("self"), python::arg("molgraph"), python::arg("pharm"))))
	.def(python::init<const Chem::PatternBasedFeatureGenerator&>(
		 (python::arg("self"), python::arg("gen"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PatternBasedFeatureGenerator>())	
	.def("addIncludePattern", &Chem::PatternBasedFeatureGenerator::addIncludePattern, 
	     (python::arg("self"), python::arg("substruct"), python::arg("ftr_type"), python::arg("tol") = 1.0,
	      python::arg("ftr_geom") = Chem::FeatureGeometry::SPHERE, python::arg("length") = 1.0))
	.def("addExcludePattern", &Chem::PatternBasedFeatureGenerator::addExcludePattern, 
	     (python::arg("self"), python::arg("substruct")))
	.def("clearIncludePatterns", &Chem::PatternBasedFeatureGenerator::clearIncludePatterns, 
	     python::arg("self"))
	.def("clearExcludePatterns", &Chem::PatternBasedFeatureGenerator::clearExcludePatterns, 
	     python::arg("self"))
	.def("assign", &Chem::PatternBasedFeatureGenerator::operator=, 
	     (python::arg("self"), python::arg("gen")), python::return_self<>())
	.def("generate", &Chem::PatternBasedFeatureGenerator::generate,
	     (python::arg("self"), python::arg("molgraph"), python::arg("pharm")));
}
