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

#include "CDPL/Pharm/PharmacophoreGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    void setFeatureFunction(CDPL::Pharm::PharmacophoreGenerator& generator, unsigned int type, 
							const boost::python::object& callable)
    {
		generator.setFeatureFunction(type, CDPLPythonBase::BinaryFunctionAdapter<void, 
									 CDPL::Chem::MolecularGraph, CDPL::Pharm::Pharmacophore>(callable)); 
    }
}


void CDPLPythonPharm::exportPharmacophoreGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Pharm::PharmacophoreGenerator, boost::noncopyable>("PharmacophoreGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<Pharm::PharmacophoreGenerator>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::PharmacophoreGenerator>())	
		.def("setFeatureFunction", &setFeatureFunction, 
			 (python::arg("self"), python::arg("type"), python::arg("func")))
		.def("removeFeatureFunction", &Pharm::PharmacophoreGenerator::removeFeatureFunction, 
			 (python::arg("self"), python::arg("type")))
		.def("getFeatureFunction", &Pharm::PharmacophoreGenerator::getFeatureFunction, 
			 (python::arg("self"), python::arg("type")),
			 python::return_value_policy<python::copy_const_reference>())
		.def("enableFeature", &Pharm::PharmacophoreGenerator::enableFeature, 
			 (python::arg("self"), python::arg("type"), python::arg("enable")))
		.def("isFeatureEnabled", &Pharm::PharmacophoreGenerator::isFeatureEnabled, 
			 (python::arg("self"), python::arg("ft_type")))
		.def("clearEnabledFeatures", &Pharm::PharmacophoreGenerator::isFeatureEnabled, python::arg("self"))
		.def("assign", &Pharm::PharmacophoreGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("generate", &Pharm::PharmacophoreGenerator::generate,
			 (python::arg("self"), python::arg("molgraph"), python::arg("pharm")));
}
