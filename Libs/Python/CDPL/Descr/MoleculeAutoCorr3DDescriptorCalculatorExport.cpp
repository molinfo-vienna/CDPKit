/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeAutoCorr3DDescriptorCalculatorExport.cpp 
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

#include "CDPL/Descr/MoleculeAutoCorr3DDescriptorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::MoleculeAutoCorr3DDescriptorCalculator& calculator, CDPL::Chem::AtomContainer& cntnr, CDPL::Math::DVector& descr)
    {
		calculator.calculate(cntnr, descr);
    }
}


void CDPLPythonDescr::exportMoleculeAutoCorr3DDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::MoleculeAutoCorr3DDescriptorCalculator, boost::noncopyable>("MoleculeAutoCorr3DDescriptorCalculator", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Descr::MoleculeAutoCorr3DDescriptorCalculator&>((python::arg("self"), python::arg("calculator"))))
	.def(python::init<Chem::AtomContainer&, Math::DVector&>(
		 (python::arg("self"), python::arg("cntnr"), python::arg("descr"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::MoleculeAutoCorr3DDescriptorCalculator>())	
	.def("assign", CDPLPythonBase::copyAssOp(&Descr::MoleculeAutoCorr3DDescriptorCalculator::operator=), 
	     (python::arg("self"), python::arg("calculator")), python::return_self<>())
	.def("setAtom3DCoordinatesFunction", &Descr::MoleculeAutoCorr3DDescriptorCalculator::setAtom3DCoordinatesFunction, 
	     (python::arg("self"), python::arg("func")))
	.def("setAtomPairWeightFunction", &Descr::MoleculeAutoCorr3DDescriptorCalculator::setAtomPairWeightFunction, 
	     (python::arg("self"), python::arg("func")))
	.def("setNumSteps", &Descr::MoleculeAutoCorr3DDescriptorCalculator::setNumSteps, 
	     (python::arg("self"), python::arg("num_steps")))
	.def("getNumSteps", &Descr::MoleculeAutoCorr3DDescriptorCalculator::getNumSteps, python::arg("self"))
	.def("setRadiusIncrement", &Descr::MoleculeAutoCorr3DDescriptorCalculator::setRadiusIncrement, 
	     (python::arg("self"), python::arg("radius_inc")))
	.def("getRadiusIncrement", &Descr::MoleculeAutoCorr3DDescriptorCalculator::getRadiusIncrement, python::arg("self"))
	.def("setStartRadius", &Descr::MoleculeAutoCorr3DDescriptorCalculator::setStartRadius, 
	     (python::arg("self"), python::arg("start_radius")))
	.def("getStartRadius", &Descr::MoleculeAutoCorr3DDescriptorCalculator::getStartRadius, python::arg("self"))
	.def("calculate", &calculate, (python::arg("self"), python::arg("cntnr"), python::arg("descr")))
	.add_property("startRadius", &Descr::MoleculeAutoCorr3DDescriptorCalculator::getStartRadius,
		      &Descr::MoleculeAutoCorr3DDescriptorCalculator::setStartRadius)
	.add_property("radiusIncrement", &Descr::MoleculeAutoCorr3DDescriptorCalculator::getRadiusIncrement,
		      &Descr::MoleculeAutoCorr3DDescriptorCalculator::setRadiusIncrement)
	.add_property("numSteps", &Descr::MoleculeAutoCorr3DDescriptorCalculator::getNumSteps,
		      &Descr::MoleculeAutoCorr3DDescriptorCalculator::setNumSteps);
}
