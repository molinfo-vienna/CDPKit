/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PEOEChargeCalculatorExport.cpp 
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

#include "CDPL/Chem/PEOEChargeCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportPEOEChargeCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::PEOEChargeCalculator, boost::noncopyable>("PEOEChargeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PEOEChargeCalculator>())	
		.def("setNumIterations", &Chem::PEOEChargeCalculator::setNumIterations, (python::arg("self"), python::arg("num_iter")))
		.def("setDampingFactor", &Chem::PEOEChargeCalculator::setDampingFactor, (python::arg("self"), python::arg("factor")))
		.def("getNumIterations", &Chem::PEOEChargeCalculator::getNumIterations, python::arg("self"))
		.def("getDampingFactor", &Chem::PEOEChargeCalculator::getDampingFactor, python::arg("self"))
		.def("calculate", &Chem::PEOEChargeCalculator::calculate, (python::arg("self"), python::arg("molgraph")), 
			 python::return_internal_reference<>())
		.def("getResult", &Chem::PEOEChargeCalculator::getResult, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("getElectronegativities", &Chem::PEOEChargeCalculator::getElectronegativities, python::arg("self"), 
			 python::return_internal_reference<>())
		.add_property("result", python::make_function(&Chem::PEOEChargeCalculator::getResult,
													  python::return_internal_reference<>()))
		.add_property("electronegativities", python::make_function(&Chem::PEOEChargeCalculator::getElectronegativities,
													  python::return_internal_reference<>()))
		.add_property("numIterations", &Chem::PEOEChargeCalculator::getNumIterations, 
					  &Chem::PEOEChargeCalculator::setNumIterations)
		.add_property("dampingFactor", &Chem::PEOEChargeCalculator::getDampingFactor,
					  &Chem::PEOEChargeCalculator::setDampingFactor);
}
