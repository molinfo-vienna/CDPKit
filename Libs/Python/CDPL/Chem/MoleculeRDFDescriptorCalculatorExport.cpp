/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeRDFDescriptorCalculatorExport.cpp 
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

#include "CDPL/Chem/MoleculeRDFDescriptorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Chem::MoleculeRDFDescriptorCalculator& calculator, CDPL::Chem::AtomContainer& cntnr, CDPL::Math::DVector& descr)
    {
		calculator.calculate(cntnr, descr);
    }
}

void CDPLPythonChem::exportMoleculeRDFDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::MoleculeRDFDescriptorCalculator, boost::noncopyable>("MoleculeRDFDescriptorCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MoleculeRDFDescriptorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<Chem::AtomContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MoleculeRDFDescriptorCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::MoleculeRDFDescriptorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setAtom3DCoordinatesFunction", &Chem::MoleculeRDFDescriptorCalculator::setAtom3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setAtomPairWeightFunction", &Chem::MoleculeRDFDescriptorCalculator::setAtomPairWeightFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Chem::MoleculeRDFDescriptorCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Chem::MoleculeRDFDescriptorCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Chem::MoleculeRDFDescriptorCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Chem::MoleculeRDFDescriptorCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Chem::MoleculeRDFDescriptorCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Chem::MoleculeRDFDescriptorCalculator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Chem::MoleculeRDFDescriptorCalculator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Chem::MoleculeRDFDescriptorCalculator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Chem::MoleculeRDFDescriptorCalculator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Chem::MoleculeRDFDescriptorCalculator::getScalingFactor, python::arg("self"))
		.def("enableDistanceToIntervalCenterRounding", &Chem::MoleculeRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding, 
			 (python::arg("self"), python::arg("enable")))
		.def("distanceToIntervalsCenterRoundingEnabled", &Chem::MoleculeRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
		.add_property("distanceToIntervalCenterRounding", &Chem::MoleculeRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled,
					  &Chem::MoleculeRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding)
		.add_property("smoothingFactor", &Chem::MoleculeRDFDescriptorCalculator::getSmoothingFactor,
					  &Chem::MoleculeRDFDescriptorCalculator::setSmoothingFactor)
		.add_property("scalingFactor", &Chem::MoleculeRDFDescriptorCalculator::getScalingFactor,
					  &Chem::MoleculeRDFDescriptorCalculator::setScalingFactor)
		.add_property("startRadius", &Chem::MoleculeRDFDescriptorCalculator::getStartRadius,
					  &Chem::MoleculeRDFDescriptorCalculator::setStartRadius)
		.add_property("radiusIncrement", &Chem::MoleculeRDFDescriptorCalculator::getRadiusIncrement,
					  &Chem::MoleculeRDFDescriptorCalculator::setRadiusIncrement)
		.add_property("numSteps", &Chem::MoleculeRDFDescriptorCalculator::getNumSteps,
					  &Chem::MoleculeRDFDescriptorCalculator::setNumSteps);
}
