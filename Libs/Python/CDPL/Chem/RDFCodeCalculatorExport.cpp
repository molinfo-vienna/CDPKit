/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RDFCodeCalculatorExport.cpp 
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

#include "CDPL/Chem/RDFCodeCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	void setAtomPairWeightFunction(CDPL::Chem::RDFCodeCalculator& calculator, const boost::python::object& callable)
	{
		calculator.setAtomPairWeightFunction(CDPLPythonBase::BinaryFunctionAdapter<double, CDPL::Chem::Atom, CDPL::Chem::Atom>(callable)); 
	}

	const CDPL::Math::DVector& calculate(CDPL::Chem::RDFCodeCalculator& calculator, CDPL::Chem::MolecularGraph& molgraph)
	{
		return calculator.calculate(molgraph);
	}
}


void CDPLPythonChem::exportRDFCodeCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::RDFCodeCalculator, boost::noncopyable>("RDFCodeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::RDFCodeCalculator>())	
		.def("setAtomPairWeightFunction", &setAtomPairWeightFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Chem::RDFCodeCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Chem::RDFCodeCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Chem::RDFCodeCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Chem::RDFCodeCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Chem::RDFCodeCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Chem::RDFCodeCalculator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Chem::RDFCodeCalculator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Chem::RDFCodeCalculator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Chem::RDFCodeCalculator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Chem::RDFCodeCalculator::getScalingFactor, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("molgraph")),
			 python::return_internal_reference<>())
		.def("getResult", &Chem::RDFCodeCalculator::getResult, python::arg("self"),
			 python::return_internal_reference<>())
		.add_property("result", python::make_function(&Chem::RDFCodeCalculator::getResult,
													  python::return_internal_reference<>()))
		.add_property("smoothingFactor", &Chem::RDFCodeCalculator::getSmoothingFactor,
					  &Chem::RDFCodeCalculator::setSmoothingFactor)
		.add_property("scalingFactor", &Chem::RDFCodeCalculator::getScalingFactor,
					  &Chem::RDFCodeCalculator::setScalingFactor)
		.add_property("startRadius", &Chem::RDFCodeCalculator::getStartRadius,
					  &Chem::RDFCodeCalculator::setStartRadius)
		.add_property("radiusIncrement", &Chem::RDFCodeCalculator::getRadiusIncrement,
					  &Chem::RDFCodeCalculator::setRadiusIncrement)
		.add_property("numSteps", &Chem::RDFCodeCalculator::getNumSteps,
					  &Chem::RDFCodeCalculator::setNumSteps);
}
