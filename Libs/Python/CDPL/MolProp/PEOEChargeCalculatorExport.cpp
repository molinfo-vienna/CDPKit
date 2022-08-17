/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PEOEChargeCalculatorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/MolProp/PEOEChargeCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportPEOEChargeCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolProp::PEOEChargeCalculator, boost::noncopyable>("PEOEChargeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Util::DArray&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("charges"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MolProp::PEOEChargeCalculator>())	
		.def("setNumIterations", &MolProp::PEOEChargeCalculator::setNumIterations, (python::arg("self"), python::arg("num_iter")))
		.def("setDampingFactor", &MolProp::PEOEChargeCalculator::setDampingFactor, (python::arg("self"), python::arg("factor")))
		.def("getNumIterations", &MolProp::PEOEChargeCalculator::getNumIterations, python::arg("self"))
		.def("getDampingFactor", &MolProp::PEOEChargeCalculator::getDampingFactor, python::arg("self"))
		.def("calculate", &MolProp::PEOEChargeCalculator::calculate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("charges")))
		.def("getElectronegativities", &MolProp::PEOEChargeCalculator::getElectronegativities, 
			 (python::arg("self"), python::arg("elnegs")))
		.def_readonly("DEF_NUM_ITERATIONS", MolProp::PEOEChargeCalculator::DEF_NUM_ITERATIONS)
		.def_readonly("DEF_DAMPING_FACTOR", MolProp::PEOEChargeCalculator::DEF_DAMPING_FACTOR)
		.add_property("numIterations", &MolProp::PEOEChargeCalculator::getNumIterations, 
					  &MolProp::PEOEChargeCalculator::setNumIterations)
		.add_property("dampingFactor", &MolProp::PEOEChargeCalculator::getDampingFactor,
					  &MolProp::PEOEChargeCalculator::setDampingFactor);
}
