/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomAutoCorrelation3DVectorCalculatorExport.cpp 
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

#include "CDPL/Descr/AtomAutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::AtomAutoCorrelation3DVectorCalculator& calculator, CDPL::Chem::AtomContainer& cntnr, CDPL::Math::DVector& vec)
    {
		calculator.calculate(cntnr, vec);
    }
}


void CDPLPythonDescr::exportAtomAutoCorrelation3DVectorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::AtomAutoCorrelation3DVectorCalculator, boost::noncopyable>("AtomAutoCorrelation3DVectorCalculator", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Descr::AtomAutoCorrelation3DVectorCalculator&>((python::arg("self"), python::arg("calculator"))))
	.def(python::init<Chem::AtomContainer&, Math::DVector&>(
		 (python::arg("self"), python::arg("cntnr"), python::arg("vec"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::AtomAutoCorrelation3DVectorCalculator>())	
	.def("assign", CDPLPythonBase::copyAssOp(&Descr::AtomAutoCorrelation3DVectorCalculator::operator=), 
	     (python::arg("self"), python::arg("calculator")), python::return_self<>())
	.def("setEntityPairWeightFunction", &Descr::AtomAutoCorrelation3DVectorCalculator::setEntityPairWeightFunction, 
	     (python::arg("self"), python::arg("func")))
	.def("setEntity3DCoordinatesFunction", &Descr::AtomAutoCorrelation3DVectorCalculator::setEntity3DCoordinatesFunction, 
	     (python::arg("self"), python::arg("func")))
	.def("setNumSteps", &Descr::AtomAutoCorrelation3DVectorCalculator::setNumSteps, 
	     (python::arg("self"), python::arg("num_steps")))
	.def("getNumSteps", &Descr::AtomAutoCorrelation3DVectorCalculator::getNumSteps, python::arg("self"))
	.def("setRadiusIncrement", &Descr::AtomAutoCorrelation3DVectorCalculator::setRadiusIncrement, 
	     (python::arg("self"), python::arg("radius_inc")))
	.def("getRadiusIncrement", &Descr::AtomAutoCorrelation3DVectorCalculator::getRadiusIncrement, python::arg("self"))
	.def("setStartRadius", &Descr::AtomAutoCorrelation3DVectorCalculator::setStartRadius, 
	     (python::arg("self"), python::arg("start_radius")))
	.def("getStartRadius", &Descr::AtomAutoCorrelation3DVectorCalculator::getStartRadius, python::arg("self"))
	.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("vec")))
	.add_property("startRadius", &Descr::AtomAutoCorrelation3DVectorCalculator::getStartRadius,
		      &Descr::AtomAutoCorrelation3DVectorCalculator::setStartRadius)
	.add_property("radiusIncrement", &Descr::AtomAutoCorrelation3DVectorCalculator::getRadiusIncrement,
		      &Descr::AtomAutoCorrelation3DVectorCalculator::setRadiusIncrement)
	.add_property("numSteps", &Descr::AtomAutoCorrelation3DVectorCalculator::getNumSteps,
		      &Descr::AtomAutoCorrelation3DVectorCalculator::setNumSteps);
}
