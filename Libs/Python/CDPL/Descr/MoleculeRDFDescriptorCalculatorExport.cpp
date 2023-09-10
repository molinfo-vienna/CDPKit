/* 
 * MoleculeRDFDescriptorCalculatorExport.cpp 
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

#include "CDPL/Descr/MoleculeRDFDescriptorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::MoleculeRDFDescriptorCalculator& calculator, CDPL::Chem::AtomContainer& cntnr, CDPL::Math::DVector& descr)
    {
        calculator.calculate(cntnr, descr);
    }
}

void CDPLPythonDescr::exportMoleculeRDFDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::MoleculeRDFDescriptorCalculator, boost::noncopyable>("MoleculeRDFDescriptorCalculator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Descr::MoleculeRDFDescriptorCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(python::init<Chem::AtomContainer&, Math::DVector&>(
                 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::MoleculeRDFDescriptorCalculator>())    
        .def("assign", CDPLPythonBase::copyAssOp<Descr::MoleculeRDFDescriptorCalculator>(), 
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("setAtom3DCoordinatesFunction", &Descr::MoleculeRDFDescriptorCalculator::setAtom3DCoordinatesFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setAtomPairWeightFunction", &Descr::MoleculeRDFDescriptorCalculator::setAtomPairWeightFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setNumSteps", &Descr::MoleculeRDFDescriptorCalculator::setNumSteps, 
             (python::arg("self"), python::arg("num_steps")))
        .def("getNumSteps", &Descr::MoleculeRDFDescriptorCalculator::getNumSteps, python::arg("self"))
        .def("setRadiusIncrement", &Descr::MoleculeRDFDescriptorCalculator::setRadiusIncrement, 
             (python::arg("self"), python::arg("radius_inc")))
        .def("getRadiusIncrement", &Descr::MoleculeRDFDescriptorCalculator::getRadiusIncrement, python::arg("self"))
        .def("setStartRadius", &Descr::MoleculeRDFDescriptorCalculator::setStartRadius, 
             (python::arg("self"), python::arg("start_radius")))
        .def("getStartRadius", &Descr::MoleculeRDFDescriptorCalculator::getStartRadius, python::arg("self"))
        .def("setSmoothingFactor", &Descr::MoleculeRDFDescriptorCalculator::setSmoothingFactor, 
             (python::arg("self"), python::arg("factor")))
        .def("getSmoothingFactor", &Descr::MoleculeRDFDescriptorCalculator::getSmoothingFactor, python::arg("self"))
        .def("setScalingFactor", &Descr::MoleculeRDFDescriptorCalculator::setScalingFactor, 
             (python::arg("self"), python::arg("factor")))
        .def("getScalingFactor", &Descr::MoleculeRDFDescriptorCalculator::getScalingFactor, python::arg("self"))
        .def("enableDistanceToIntervalCenterRounding", &Descr::MoleculeRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding, 
             (python::arg("self"), python::arg("enable")))
        .def("distanceToIntervalsCenterRoundingEnabled", &Descr::MoleculeRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled, python::arg("self"))
        .def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
        .add_property("distanceToIntervalCenterRounding", &Descr::MoleculeRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled,
                      &Descr::MoleculeRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding)
        .add_property("smoothingFactor", &Descr::MoleculeRDFDescriptorCalculator::getSmoothingFactor,
                      &Descr::MoleculeRDFDescriptorCalculator::setSmoothingFactor)
        .add_property("scalingFactor", &Descr::MoleculeRDFDescriptorCalculator::getScalingFactor,
                      &Descr::MoleculeRDFDescriptorCalculator::setScalingFactor)
        .add_property("startRadius", &Descr::MoleculeRDFDescriptorCalculator::getStartRadius,
                      &Descr::MoleculeRDFDescriptorCalculator::setStartRadius)
        .add_property("radiusIncrement", &Descr::MoleculeRDFDescriptorCalculator::getRadiusIncrement,
                      &Descr::MoleculeRDFDescriptorCalculator::setRadiusIncrement)
        .add_property("numSteps", &Descr::MoleculeRDFDescriptorCalculator::getNumSteps,
                      &Descr::MoleculeRDFDescriptorCalculator::setNumSteps);
}
