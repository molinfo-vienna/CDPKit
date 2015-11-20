/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondStereoFlagGeneratorExport.cpp 
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

#include "CDPL/Chem/BondStereoFlagGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportBondStereoFlagGenerator()
{
	using namespace boost;
	using namespace CDPL;

	const Util::UIArray& (Chem::BondStereoFlagGenerator::*calcFunc1)(const Chem::MolecularGraph&) = 
		&Chem::BondStereoFlagGenerator::generate;

	const Util::UIArray& (Chem::BondStereoFlagGenerator::*calcFunc2)(const Chem::MolecularGraph&, const Math::Vector2DArray&) = 
		&Chem::BondStereoFlagGenerator::generate;

	python::class_<Chem::BondStereoFlagGenerator, boost::noncopyable>("BondStereoFlagGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(python::init<const Chem::MolecularGraph&, const Math::Vector2DArray&>
			 ((python::arg("self"), python::arg("molgraph"), python::arg("coords"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::BondStereoFlagGenerator>())	
		.def("generate", calcFunc1, (python::arg("self"), python::arg("molgraph")), 
			 python::return_internal_reference<>())
		.def("generate", calcFunc2, (python::arg("self"), python::arg("molgraph"), python::arg("coords")), 
			 python::return_internal_reference<>())
		.def("getResult", &Chem::BondStereoFlagGenerator::getResult, python::arg("self"),
			 python::return_internal_reference<>())
		.add_property("result", python::make_function(&Chem::BondStereoFlagGenerator::getResult,
													  python::return_internal_reference<>()));
}
