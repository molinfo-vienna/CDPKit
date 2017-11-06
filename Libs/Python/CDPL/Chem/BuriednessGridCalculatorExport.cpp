/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BuriednessGridCalculatorExport.cpp 
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

#include "CDPL/Chem/BuriednessGridCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Chem::BuriednessGridCalculator& calculator, CDPL::Chem::AtomContainer& atoms, CDPL::Grid::DSpatialGrid& grid)
    {
		calculator.calculate(atoms, grid);
    }
}


void CDPLPythonChem::exportBuriednessGridCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::BuriednessGridCalculator, Chem::BuriednessGridCalculator::SharedPointer, boost::noncopyable>("BuriednessGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::BuriednessGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::BuriednessGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::BuriednessGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setMinVdWSurfaceDistance", &Chem::BuriednessGridCalculator::setMinVdWSurfaceDistance, (python::arg("self"), python::arg("dist")))
		.def("getMinVdWSurfaceDistance", &Chem::BuriednessGridCalculator::getMinVdWSurfaceDistance, python::arg("self"))
		.def("setProbeRadius", &Chem::BuriednessGridCalculator::setProbeRadius, (python::arg("self"), python::arg("radius")))
		.def("getProbeRadius", &Chem::BuriednessGridCalculator::getProbeRadius, python::arg("self"))
		.def("setNumTestRays", &Chem::BuriednessGridCalculator::setNumTestRays, (python::arg("self"), python::arg("num_rays")))
		.def("getNumTestRays", &Chem::BuriednessGridCalculator::getNumTestRays, python::arg("self"))
		.def("setAtom3DCoordinatesFunction", &Chem::BuriednessGridCalculator::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &Chem::BuriednessGridCalculator::getAtom3DCoordinatesFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("calculate", &calculate, (python::arg("self"), python::arg("atoms"), python::arg("grid")))
		.add_property("probeRadius", &Chem::BuriednessGridCalculator::getProbeRadius, &Chem::BuriednessGridCalculator::setProbeRadius)
		.add_property("minVdWSurfaceDistance", &Chem::BuriednessGridCalculator::getMinVdWSurfaceDistance, 
					  &Chem::BuriednessGridCalculator::setMinVdWSurfaceDistance)
		.add_property("numTestRays", &Chem::BuriednessGridCalculator::getNumTestRays, &Chem::BuriednessGridCalculator::setNumTestRays)
		.add_property("atomCoordinatesFunction", 
					  python::make_function(&Chem::BuriednessGridCalculator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
					  &Chem::BuriednessGridCalculator::setAtom3DCoordinatesFunction);

}
