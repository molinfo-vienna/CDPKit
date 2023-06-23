/* 
 * FeatureRDFCodeCalculatorExport.cpp 
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

#include "CDPL/Descr/FeatureRDFCodeCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::FeatureRDFCodeCalculator& calculator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& rdf_code)
    {
        calculator.calculate(cntnr, rdf_code);
    }
}


void CDPLPythonDescr::exportFeatureRDFCodeCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::FeatureRDFCodeCalculator, boost::noncopyable>("FeatureRDFCodeCalculator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Descr::FeatureRDFCodeCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
                 (python::arg("self"), python::arg("cntnr"), python::arg("rdf_code"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::FeatureRDFCodeCalculator>())    
        .def("assign", CDPLPythonBase::copyAssOp(&Descr::FeatureRDFCodeCalculator::operator=), 
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("setEntityPairWeightFunction", &Descr::FeatureRDFCodeCalculator::setEntityPairWeightFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setEntity3DCoordinatesFunction", &Descr::FeatureRDFCodeCalculator::setEntity3DCoordinatesFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setNumSteps", &Descr::FeatureRDFCodeCalculator::setNumSteps, 
             (python::arg("self"), python::arg("num_steps")))
        .def("getNumSteps", &Descr::FeatureRDFCodeCalculator::getNumSteps, python::arg("self"))
        .def("setRadiusIncrement", &Descr::FeatureRDFCodeCalculator::setRadiusIncrement, 
             (python::arg("self"), python::arg("radius_inc")))
        .def("getRadiusIncrement", &Descr::FeatureRDFCodeCalculator::getRadiusIncrement, python::arg("self"))
        .def("setStartRadius", &Descr::FeatureRDFCodeCalculator::setStartRadius, 
             (python::arg("self"), python::arg("start_radius")))
        .def("getStartRadius", &Descr::FeatureRDFCodeCalculator::getStartRadius, python::arg("self"))
        .def("setSmoothingFactor", &Descr::FeatureRDFCodeCalculator::setSmoothingFactor, 
             (python::arg("self"), python::arg("factor")))
        .def("getSmoothingFactor", &Descr::FeatureRDFCodeCalculator::getSmoothingFactor, python::arg("self"))
        .def("setScalingFactor", &Descr::FeatureRDFCodeCalculator::setScalingFactor, 
             (python::arg("self"), python::arg("factor")))
        .def("getScalingFactor", &Descr::FeatureRDFCodeCalculator::getScalingFactor, python::arg("self"))
        .def("enableDistanceToIntervalCenterRounding", &Descr::FeatureRDFCodeCalculator::enableDistanceToIntervalCenterRounding, 
             (python::arg("self"), python::arg("enable")))
        .def("distanceToIntervalsCenterRoundingEnabled", &Descr::FeatureRDFCodeCalculator::distanceToIntervalsCenterRoundingEnabled, python::arg("self"))
        .def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("rdf_code")))
        .add_property("distanceToIntervalCenterRounding", &Descr::FeatureRDFCodeCalculator::distanceToIntervalsCenterRoundingEnabled,
                      &Descr::FeatureRDFCodeCalculator::enableDistanceToIntervalCenterRounding)
        .add_property("smoothingFactor", &Descr::FeatureRDFCodeCalculator::getSmoothingFactor,
                      &Descr::FeatureRDFCodeCalculator::setSmoothingFactor)
        .add_property("scalingFactor", &Descr::FeatureRDFCodeCalculator::getScalingFactor,
                      &Descr::FeatureRDFCodeCalculator::setScalingFactor)
        .add_property("startRadius", &Descr::FeatureRDFCodeCalculator::getStartRadius,
                      &Descr::FeatureRDFCodeCalculator::setStartRadius)
        .add_property("radiusIncrement", &Descr::FeatureRDFCodeCalculator::getRadiusIncrement,
                      &Descr::FeatureRDFCodeCalculator::setRadiusIncrement)
        .add_property("numSteps", &Descr::FeatureRDFCodeCalculator::getNumSteps,
                      &Descr::FeatureRDFCodeCalculator::setNumSteps);
}
