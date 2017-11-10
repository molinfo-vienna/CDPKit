/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreRDFFingerprintGeneratorExport.cpp 
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

#include "CDPL/Pharm/PharmacophoreRDFFingerprintGenerator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void generate(CDPL::Pharm::PharmacophoreRDFFingerprintGenerator& generator, CDPL::Pharm::FeatureContainer& cntnr, CDPL::Math::DVector& fp)
    {
		generator.generate(cntnr, fp);
    }
}

void CDPLPythonPharm::exportPharmacophoreRDFFingerprintGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::PharmacophoreRDFFingerprintGenerator, boost::noncopyable>("PharmacophoreRDFFingerprintGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::PharmacophoreRDFFingerprintGenerator&>((python::arg("self"), python::arg("generator"))))
		.def(python::init<Pharm::FeatureContainer&, Math::DVector&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("fp"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::PharmacophoreRDFFingerprintGenerator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::PharmacophoreRDFFingerprintGenerator::operator=), 
			 (python::arg("self"), python::arg("generator")), python::return_self<>())
		.def("setFeature3DCoordinatesFunction", &Pharm::PharmacophoreRDFFingerprintGenerator::setFeature3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumSteps", &Pharm::PharmacophoreRDFFingerprintGenerator::setNumSteps, 
			 (python::arg("self"), python::arg("num_steps")))
		.def("getNumSteps", &Pharm::PharmacophoreRDFFingerprintGenerator::getNumSteps, python::arg("self"))
		.def("setRadiusIncrement", &Pharm::PharmacophoreRDFFingerprintGenerator::setRadiusIncrement, 
			 (python::arg("self"), python::arg("radius_inc")))
		.def("getRadiusIncrement", &Pharm::PharmacophoreRDFFingerprintGenerator::getRadiusIncrement, python::arg("self"))
		.def("setStartRadius", &Pharm::PharmacophoreRDFFingerprintGenerator::setStartRadius, 
			 (python::arg("self"), python::arg("start_radius")))
		.def("getStartRadius", &Pharm::PharmacophoreRDFFingerprintGenerator::getStartRadius, python::arg("self"))
		.def("setSmoothingFactor", &Pharm::PharmacophoreRDFFingerprintGenerator::setSmoothingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getSmoothingFactor", &Pharm::PharmacophoreRDFFingerprintGenerator::getSmoothingFactor, python::arg("self"))
		.def("setScalingFactor", &Pharm::PharmacophoreRDFFingerprintGenerator::setScalingFactor, 
			 (python::arg("self"), python::arg("factor")))
		.def("getScalingFactor", &Pharm::PharmacophoreRDFFingerprintGenerator::getScalingFactor, python::arg("self"))
		.def("generate", &generate, (python::arg("self"), python::arg("cntnr"), python::arg("fp")))
		.add_property("smoothingFactor", &Pharm::PharmacophoreRDFFingerprintGenerator::getSmoothingFactor,
					  &Pharm::PharmacophoreRDFFingerprintGenerator::setSmoothingFactor)
		.add_property("scalingFactor", &Pharm::PharmacophoreRDFFingerprintGenerator::getScalingFactor,
					  &Pharm::PharmacophoreRDFFingerprintGenerator::setScalingFactor)
		.add_property("startRadius", &Pharm::PharmacophoreRDFFingerprintGenerator::getStartRadius,
					  &Pharm::PharmacophoreRDFFingerprintGenerator::setStartRadius)
		.add_property("radiusIncrement", &Pharm::PharmacophoreRDFFingerprintGenerator::getRadiusIncrement,
					  &Pharm::PharmacophoreRDFFingerprintGenerator::setRadiusIncrement)
		.add_property("numSteps", &Pharm::PharmacophoreRDFFingerprintGenerator::getNumSteps,
					  &Pharm::PharmacophoreRDFFingerprintGenerator::setNumSteps);
}
