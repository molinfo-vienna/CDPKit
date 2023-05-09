/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreRDFDescriptorCalculatorExport.cpp 
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

#include "CDPL/Descr/PharmacophoreRDFDescriptorCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::PharmacophoreRDFDescriptorCalculator& calculator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& descr)
    {
		calculator.calculate(cntnr, descr);
    }
}


void CDPLPythonDescr::exportPharmacophoreRDFDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::PharmacophoreRDFDescriptorCalculator, boost::noncopyable>("PharmacophoreRDFDescriptorCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Descr::PharmacophoreRDFDescriptorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::PharmacophoreRDFDescriptorCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Descr::PharmacophoreRDFDescriptorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setFeature3DCoordinatesFunction", &Descr::PharmacophoreRDFDescriptorCalculator::setFeature3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setFeaturePairWeightFunction", &Descr::PharmacophoreRDFDescriptorCalculator::setFeaturePairWeightFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Descr::PharmacophoreRDFDescriptorCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Descr::PharmacophoreRDFDescriptorCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Descr::PharmacophoreRDFDescriptorCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Descr::PharmacophoreRDFDescriptorCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Descr::PharmacophoreRDFDescriptorCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Descr::PharmacophoreRDFDescriptorCalculator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Descr::PharmacophoreRDFDescriptorCalculator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Descr::PharmacophoreRDFDescriptorCalculator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Descr::PharmacophoreRDFDescriptorCalculator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Descr::PharmacophoreRDFDescriptorCalculator::getScalingFactor, python::arg("self"))
		.def("enableDistanceToIntervalCenterRounding", &Descr::PharmacophoreRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding, 
			 (python::arg("self"), python::arg("enable")))
		.def("distanceToIntervalsCenterRoundingEnabled", &Descr::PharmacophoreRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
		.add_property("distanceToIntervalCenterRounding", &Descr::PharmacophoreRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled,
					  &Descr::PharmacophoreRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding)
		.add_property("smoothingFactor", &Descr::PharmacophoreRDFDescriptorCalculator::getSmoothingFactor,
					  &Descr::PharmacophoreRDFDescriptorCalculator::setSmoothingFactor)
		.add_property("scalingFactor", &Descr::PharmacophoreRDFDescriptorCalculator::getScalingFactor,
					  &Descr::PharmacophoreRDFDescriptorCalculator::setScalingFactor)
		.add_property("startRadius", &Descr::PharmacophoreRDFDescriptorCalculator::getStartRadius,
					  &Descr::PharmacophoreRDFDescriptorCalculator::setStartRadius)
		.add_property("radiusIncrement", &Descr::PharmacophoreRDFDescriptorCalculator::getRadiusIncrement,
					  &Descr::PharmacophoreRDFDescriptorCalculator::setRadiusIncrement)
		.add_property("numSteps", &Descr::PharmacophoreRDFDescriptorCalculator::getNumSteps,
					  &Descr::PharmacophoreRDFDescriptorCalculator::setNumSteps);
}
