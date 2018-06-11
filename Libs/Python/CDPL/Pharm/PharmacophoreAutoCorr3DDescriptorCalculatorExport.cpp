/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreAutoCorr3DDescriptorCalculatorExport.cpp 
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

#include "CDPL/Pharm/PharmacophoreAutoCorr3DDescriptorCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Pharm::PharmacophoreAutoCorr3DDescriptorCalculator& calculator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& descr)
    {
		calculator.calculate(cntnr, descr);
    }
}

void CDPLPythonPharm::exportPharmacophoreAutoCorr3DDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::PharmacophoreAutoCorr3DDescriptorCalculator, boost::noncopyable>("PharmacophoreAutoCorr3DDescriptorCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::PharmacophoreAutoCorr3DDescriptorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::PharmacophoreAutoCorr3DDescriptorCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setFeature3DCoordinatesFunction", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setFeature3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::getStartRadius, python::arg("self"))
		.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
		.add_property("startRadius", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::getStartRadius,
					  &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setStartRadius)
		.add_property("radiusIncrement", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::getRadiusIncrement,
					  &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setRadiusIncrement)
		.add_property("numSteps", &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::getNumSteps,
					  &Pharm::PharmacophoreAutoCorr3DDescriptorCalculator::setNumSteps);
}
