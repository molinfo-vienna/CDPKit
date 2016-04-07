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
}


void CDPLPythonChem::exportPharmacophoreGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::PharmacophoreGenerator, boost::noncopyable>("PharmacophoreGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PharmacophoreGenerator>())	
		.def("setFeatureFunction", &setFeatureFunction, 
			 (python::arg("self"), python::arg("type"), python::arg("func")))
		.def("enableFeature", &Chem::PharmacophoreGenerator::enableFeature, 
			 (python::arg("self"), python::arg("type"), python::arg("enable")))
		.def("isFeatureEnabled", &Chem::PharmacophoreGenerator::isFeatureEnabled, 
			 (python::arg("self"), python::arg("ft_type")))
		.def("clearEnabledFeatures", &Chem::PharmacophoreGenerator::isFeatureEnabled, python::arg("self"))
		.def("generate", &Chem::PharmacophoreGenerator::generate,
			 (python::arg("self"), python::arg("molgraph"), python::arg("pharm")));
}
