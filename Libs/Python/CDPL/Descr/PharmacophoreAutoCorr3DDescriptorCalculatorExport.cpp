/* 
 * PharmacophoreAutoCorr3DDescriptorCalculatorExport.cpp 
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

#include "CDPL/Descr/PharmacophoreAutoCorr3DDescriptorCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator& calculator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& descr)
    {
        calculator.calculate(cntnr, descr);
    }
}


void CDPLPythonDescr::exportPharmacophoreAutoCorr3DDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::PharmacophoreAutoCorr3DDescriptorCalculator, boost::noncopyable>("PharmacophoreAutoCorr3DDescriptorCalculator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Descr::PharmacophoreAutoCorr3DDescriptorCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
                 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::PharmacophoreAutoCorr3DDescriptorCalculator>())    
        .def("assign", CDPLPythonBase::copyAssOp(&Descr::PharmacophoreAutoCorr3DDescriptorCalculator::operator=), 
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("setFeature3DCoordinatesFunction", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setFeature3DCoordinatesFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setFeaturePairWeightFunction", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setFeaturePairWeightFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setNumSteps", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setNumSteps, 
             (python::arg("self"), python::arg("num_steps")))
        .def("getNumSteps", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getNumSteps, python::arg("self"))
        .def("setRadiusIncrement", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setRadiusIncrement, 
             (python::arg("self"), python::arg("radius_inc")))
        .def("getRadiusIncrement", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getRadiusIncrement, python::arg("self"))
        .def("setStartRadius", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setStartRadius, 
             (python::arg("self"), python::arg("start_radius")))
        .def("getStartRadius", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getStartRadius, python::arg("self"))
        .def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
        .add_property("startRadius", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getStartRadius,
                      &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setStartRadius)
        .add_property("radiusIncrement", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getRadiusIncrement,
                      &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setRadiusIncrement)
        .add_property("numSteps", &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getNumSteps,
                      &Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setNumSteps);
}
