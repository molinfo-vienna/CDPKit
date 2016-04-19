/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreGeneratorExport.cpp 
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

#include "CDPL/Chem/PharmacophoreGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    void setFeatureFunction(CDPL::Chem::PharmacophoreGenerator& generator, unsigned int type, 
							const boost::python::object& callable)
    {
		generator.setFeatureFunction(type, CDPLPythonBase::BinaryFunctionAdapter<void, 
									 CDPL::Chem::MolecularGraph, CDPL::Chem::Pharmacophore>(callable)); 
    }

	void featureFuncCall(CDPL::Chem::PharmacophoreGenerator::FeatureFunction& func, 
						 CDPL::Chem::MolecularGraph& molgraph, CDPL::Chem::Pharmacophore& pharm)
    {
		func(molgraph, pharm);
    }

	void featureFuncNonZero(CDPL::Chem::PharmacophoreGenerator::FeatureFunction& func)
    {
		!func.empty();
    }
}


void CDPLPythonChem::exportPharmacophoreGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<Chem::PharmacophoreGenerator, boost::noncopyable>("PharmacophoreGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::PharmacophoreGenerator>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PharmacophoreGenerator>())	
		.def("setFeatureFunction", &setFeatureFunction, 
			 (python::arg("self"), python::arg("type"), python::arg("func")))
		.def("removeFeatureFunction", &Chem::PharmacophoreGenerator::removeFeatureFunction, 
			 (python::arg("self"), python::arg("type")))
		.def("getFeatureFunction", &Chem::PharmacophoreGenerator::getFeatureFunction, 
			 (python::arg("self"), python::arg("type")),
			 python::return_value_policy<python::copy_const_reference>())
		.def("enableFeature", &Chem::PharmacophoreGenerator::enableFeature, 
			 (python::arg("self"), python::arg("type"), python::arg("enable")))
		.def("isFeatureEnabled", &Chem::PharmacophoreGenerator::isFeatureEnabled, 
			 (python::arg("self"), python::arg("ft_type")))
		.def("clearEnabledFeatures", &Chem::PharmacophoreGenerator::isFeatureEnabled, python::arg("self"))
		.def("assign", &Chem::PharmacophoreGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("generate", &Chem::PharmacophoreGenerator::generate,
			 (python::arg("self"), python::arg("molgraph"), python::arg("pharm")));

	python::class_<Chem::PharmacophoreGenerator::FeatureFunction>("FeatureFunction", python::no_init)
		.def("__call__", &featureFuncCall, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("pharm")))
		.def("__nonzero__", &featureFuncNonZero, python::arg("self"));
}
