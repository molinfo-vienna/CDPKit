/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureRDFCodeCalculatorExport.cpp 
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

#include "CDPL/Pharm/FeatureRDFCodeCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Pharm::FeatureRDFCodeCalculator& calculator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& rdf_code)
    {
		calculator.calculate(cntnr, rdf_code);
    }
}

void CDPLPythonPharm::exportFeatureRDFCodeCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeatureRDFCodeCalculator, boost::noncopyable>("FeatureRDFCodeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::FeatureRDFCodeCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("rdf_code"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureRDFCodeCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::FeatureRDFCodeCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setEntityPairWeightFunction", &Pharm::FeatureRDFCodeCalculator::setEntityPairWeightFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setEntity3DCoordinatesFunction", &Pharm::FeatureRDFCodeCalculator::setEntity3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Pharm::FeatureRDFCodeCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Pharm::FeatureRDFCodeCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Pharm::FeatureRDFCodeCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Pharm::FeatureRDFCodeCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Pharm::FeatureRDFCodeCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Pharm::FeatureRDFCodeCalculator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Pharm::FeatureRDFCodeCalculator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Pharm::FeatureRDFCodeCalculator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Pharm::FeatureRDFCodeCalculator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Pharm::FeatureRDFCodeCalculator::getScalingFactor, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("rdf_code")))
		.add_property("smoothingFactor", &Pharm::FeatureRDFCodeCalculator::getSmoothingFactor,
					  &Pharm::FeatureRDFCodeCalculator::setSmoothingFactor)
		.add_property("scalingFactor", &Pharm::FeatureRDFCodeCalculator::getScalingFactor,
					  &Pharm::FeatureRDFCodeCalculator::setScalingFactor)
		.add_property("startRadius", &Pharm::FeatureRDFCodeCalculator::getStartRadius,
					  &Pharm::FeatureRDFCodeCalculator::setStartRadius)
		.add_property("radiusIncrement", &Pharm::FeatureRDFCodeCalculator::getRadiusIncrement,
					  &Pharm::FeatureRDFCodeCalculator::setRadiusIncrement)
		.add_property("numSteps", &Pharm::FeatureRDFCodeCalculator::getNumSteps,
					  &Pharm::FeatureRDFCodeCalculator::setNumSteps);
}
