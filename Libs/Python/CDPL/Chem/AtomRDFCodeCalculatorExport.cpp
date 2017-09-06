/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomRDFCodeCalculatorExport.cpp 
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

#include "CDPL/Chem/AtomRDFCodeCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	void calculate(CDPL::Chem::AtomRDFCodeCalculator& calculator, CDPL::Chem::AtomContainer& cntnr, CDPL::Math::DVector& rdf_code)
	{
		calculator.calculate(cntnr, rdf_code);
	}
}

void CDPLPythonChem::exportAtomRDFCodeCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::AtomRDFCodeCalculator, boost::noncopyable>("AtomRDFCodeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::AtomRDFCodeCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<Chem::AtomContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("rdf_code"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AtomRDFCodeCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::AtomRDFCodeCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setEntityPairWeightFunction", &Chem::AtomRDFCodeCalculator::setEntityPairWeightFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setEntity3DCoordinatesFunction", &Chem::AtomRDFCodeCalculator::setEntity3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Chem::AtomRDFCodeCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Chem::AtomRDFCodeCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Chem::AtomRDFCodeCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Chem::AtomRDFCodeCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Chem::AtomRDFCodeCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Chem::AtomRDFCodeCalculator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Chem::AtomRDFCodeCalculator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Chem::AtomRDFCodeCalculator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Chem::AtomRDFCodeCalculator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Chem::AtomRDFCodeCalculator::getScalingFactor, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("rdf_code")))
		.add_property("smoothingFactor", &Chem::AtomRDFCodeCalculator::getSmoothingFactor,
					  &Chem::AtomRDFCodeCalculator::setSmoothingFactor)
		.add_property("scalingFactor", &Chem::AtomRDFCodeCalculator::getScalingFactor,
					  &Chem::AtomRDFCodeCalculator::setScalingFactor)
		.add_property("startRadius", &Chem::AtomRDFCodeCalculator::getStartRadius,
					  &Chem::AtomRDFCodeCalculator::setStartRadius)
		.add_property("radiusIncrement", &Chem::AtomRDFCodeCalculator::getRadiusIncrement,
					  &Chem::AtomRDFCodeCalculator::setRadiusIncrement)
		.add_property("numSteps", &Chem::AtomRDFCodeCalculator::getNumSteps,
					  &Chem::AtomRDFCodeCalculator::setNumSteps);
}
