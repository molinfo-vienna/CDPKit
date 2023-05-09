/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PEOESigmaChargeCalculatorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/MolProp/PEOESigmaChargeCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportPEOESigmaChargeCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolProp::PEOESigmaChargeCalculator, boost::noncopyable>("PEOESigmaChargeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>(
				 (python::arg("self"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MolProp::PEOESigmaChargeCalculator>())	
		.def("setNumIterations", &MolProp::PEOESigmaChargeCalculator::setNumIterations, (python::arg("self"), python::arg("num_iter")))
		.def("setDampingFactor", &MolProp::PEOESigmaChargeCalculator::setDampingFactor, (python::arg("self"), python::arg("factor")))
		.def("getNumIterations", &MolProp::PEOESigmaChargeCalculator::getNumIterations, python::arg("self"))
		.def("getDampingFactor", &MolProp::PEOESigmaChargeCalculator::getDampingFactor, python::arg("self"))
		.def("calculate", &MolProp::PEOESigmaChargeCalculator::calculate, (python::arg("self"), python::arg("molgraph")))
		.def("getCharge", &MolProp::PEOESigmaChargeCalculator::getCharge, (python::arg("self"), python::arg("idx")))
		.def("getElectronegativity", &MolProp::PEOESigmaChargeCalculator::getElectronegativity,
			 (python::arg("self"), python::arg("idx")))
		.def_readonly("DEF_NUM_ITERATIONS", MolProp::PEOESigmaChargeCalculator::DEF_NUM_ITERATIONS)
		.def_readonly("DEF_DAMPING_FACTOR", MolProp::PEOESigmaChargeCalculator::DEF_DAMPING_FACTOR)
		.add_property("numIterations", &MolProp::PEOESigmaChargeCalculator::getNumIterations, 
					  &MolProp::PEOESigmaChargeCalculator::setNumIterations)
		.add_property("dampingFactor", &MolProp::PEOESigmaChargeCalculator::getDampingFactor,
					  &MolProp::PEOESigmaChargeCalculator::setDampingFactor);
}
