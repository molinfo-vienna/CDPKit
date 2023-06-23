/* 
 * BuriednessGridCalculatorExport.cpp 
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

#include "CDPL/GRAIL/BuriednessGridCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::GRAIL::BuriednessGridCalculator& calculator, CDPL::Chem::AtomContainer& atoms, CDPL::Grid::DSpatialGrid& grid)
    {
		calculator.calculate(atoms, grid);
    }
}


void CDPLPythonGRAIL::exportBuriednessGridCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GRAIL::BuriednessGridCalculator, GRAIL::BuriednessGridCalculator::SharedPointer, boost::noncopyable>("BuriednessGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const GRAIL::BuriednessGridCalculator&>((python::arg("self"), python::arg("calc"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::BuriednessGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&GRAIL::BuriednessGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calc")), python::return_self<>())
		.def("setMinVdWSurfaceDistance", &GRAIL::BuriednessGridCalculator::setMinVdWSurfaceDistance, (python::arg("self"), python::arg("dist")))
		.def("getMinVdWSurfaceDistance", &GRAIL::BuriednessGridCalculator::getMinVdWSurfaceDistance, python::arg("self"))
		.def("setProbeRadius", &GRAIL::BuriednessGridCalculator::setProbeRadius, (python::arg("self"), python::arg("radius")))
		.def("getProbeRadius", &GRAIL::BuriednessGridCalculator::getProbeRadius, python::arg("self"))
		.def("setNumTestRays", &GRAIL::BuriednessGridCalculator::setNumTestRays, (python::arg("self"), python::arg("num_rays")))
		.def("getNumTestRays", &GRAIL::BuriednessGridCalculator::getNumTestRays, python::arg("self"))
		.def("setAtom3DCoordinatesFunction", &GRAIL::BuriednessGridCalculator::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &GRAIL::BuriednessGridCalculator::getAtom3DCoordinatesFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("calculate", &calculate, (python::arg("self"), python::arg("atoms"), python::arg("grid")))
		.add_property("probeRadius", &GRAIL::BuriednessGridCalculator::getProbeRadius, &GRAIL::BuriednessGridCalculator::setProbeRadius)
		.add_property("minVdWSurfaceDistance", &GRAIL::BuriednessGridCalculator::getMinVdWSurfaceDistance, 
					  &GRAIL::BuriednessGridCalculator::setMinVdWSurfaceDistance)
		.add_property("numTestRays", &GRAIL::BuriednessGridCalculator::getNumTestRays, &GRAIL::BuriednessGridCalculator::setNumTestRays)
		.add_property("atom3DCoordinatesFunction", 
					  python::make_function(&GRAIL::BuriednessGridCalculator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
					  &GRAIL::BuriednessGridCalculator::setAtom3DCoordinatesFunction);

}
