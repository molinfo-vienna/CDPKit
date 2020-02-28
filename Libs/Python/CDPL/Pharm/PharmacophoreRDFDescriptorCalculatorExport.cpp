/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreRDFDescriptorCalculatorExport.cpp 
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

#include "CDPL/Pharm/PharmacophoreRDFDescriptorCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Pharm::PharmacophoreRDFDescriptorCalculator& calculator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& descr)
    {
		calculator.calculate(cntnr, descr);
    }
}

void CDPLPythonPharm::exportPharmacophoreRDFDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::PharmacophoreRDFDescriptorCalculator, boost::noncopyable>("PharmacophoreRDFDescriptorCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::PharmacophoreRDFDescriptorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::PharmacophoreRDFDescriptorCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::PharmacophoreRDFDescriptorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setFeature3DCoordinatesFunction", &Pharm::PharmacophoreRDFDescriptorCalculator::setFeature3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setFeaturePairWeightFunction", &Pharm::PharmacophoreRDFDescriptorCalculator::setFeaturePairWeightFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Pharm::PharmacophoreRDFDescriptorCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Pharm::PharmacophoreRDFDescriptorCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Pharm::PharmacophoreRDFDescriptorCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Pharm::PharmacophoreRDFDescriptorCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Pharm::PharmacophoreRDFDescriptorCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Pharm::PharmacophoreRDFDescriptorCalculator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Pharm::PharmacophoreRDFDescriptorCalculator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Pharm::PharmacophoreRDFDescriptorCalculator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Pharm::PharmacophoreRDFDescriptorCalculator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Pharm::PharmacophoreRDFDescriptorCalculator::getScalingFactor, python::arg("self"))
		.def("enableDistanceToIntervalCenterRounding", &Pharm::PharmacophoreRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding, 
			 (python::arg("self"), python::arg("enable")))
		.def("distanceToIntervalsCenterRoundingEnabled", &Pharm::PharmacophoreRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
		.add_property("distanceToIntervalCenterRounding", &Pharm::PharmacophoreRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled,
					  &Pharm::PharmacophoreRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding)
		.add_property("smoothingFactor", &Pharm::PharmacophoreRDFDescriptorCalculator::getSmoothingFactor,
					  &Pharm::PharmacophoreRDFDescriptorCalculator::setSmoothingFactor)
		.add_property("scalingFactor", &Pharm::PharmacophoreRDFDescriptorCalculator::getScalingFactor,
					  &Pharm::PharmacophoreRDFDescriptorCalculator::setScalingFactor)
		.add_property("startRadius", &Pharm::PharmacophoreRDFDescriptorCalculator::getStartRadius,
					  &Pharm::PharmacophoreRDFDescriptorCalculator::setStartRadius)
		.add_property("radiusIncrement", &Pharm::PharmacophoreRDFDescriptorCalculator::getRadiusIncrement,
					  &Pharm::PharmacophoreRDFDescriptorCalculator::setRadiusIncrement)
		.add_property("numSteps", &Pharm::PharmacophoreRDFDescriptorCalculator::getNumSteps,
					  &Pharm::PharmacophoreRDFDescriptorCalculator::setNumSteps);
}
