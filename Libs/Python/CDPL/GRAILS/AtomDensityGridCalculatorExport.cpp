/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDensityGridCalculatorExport.cpp 
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

#include "CDPL/GRAILS/AtomDensityGridCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	void calculate(CDPL::GRAILS::AtomDensityGridCalculator& calculator, CDPL::Chem::AtomContainer& atoms, CDPL::Grid::DSpatialGrid& grid)
	{
		calculator.calculate(atoms, grid);
	}
}


void CDPLPythonGRAILS::exportAtomDensityGridCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::class_<GRAILS::AtomDensityGridCalculator, GRAILS::AtomDensityGridCalculator::SharedPointer, boost::noncopyable>("AtomDensityGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const GRAILS::AtomDensityGridCalculator::DensityFunction&>(
				 (python::arg("self"), python::arg("func"))))
		.def(python::init<const GRAILS::AtomDensityGridCalculator::DensityFunction&, const GRAILS::AtomDensityGridCalculator::DensityCombinationFunction&>(
				 (python::arg("self"), python::arg("density_func"), python::arg("comb_func"))))
		.def(python::init<const GRAILS::AtomDensityGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAILS::AtomDensityGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&GRAILS::AtomDensityGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setDistanceCutoff", &GRAILS::AtomDensityGridCalculator::setDistanceCutoff,
			 (python::arg("self"), python::arg("dist")))
		.def("getDistanceCutoff", &GRAILS::AtomDensityGridCalculator::getDistanceCutoff,
			 python::arg("self"))
		.def("getDensityFunction", &GRAILS::AtomDensityGridCalculator::getDensityFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setDensityFunction", &GRAILS::AtomDensityGridCalculator::setDensityFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getDensityFunction", &GRAILS::AtomDensityGridCalculator::getDensityFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setDensityCombinationFunction", &GRAILS::AtomDensityGridCalculator::setDensityCombinationFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getDensityCombinationFunction", &GRAILS::AtomDensityGridCalculator::getDensityCombinationFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setAtom3DCoordinatesFunction", &GRAILS::AtomDensityGridCalculator::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &GRAILS::AtomDensityGridCalculator::getAtom3DCoordinatesFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("calculate", &calculate, (python::arg("self"), python::arg("atoms"), python::arg("grid")))
		.add_property("distanceCutoff", &GRAILS::AtomDensityGridCalculator::getDistanceCutoff, &GRAILS::AtomDensityGridCalculator::setDistanceCutoff)
		.add_property("densityFunction", 
					  python::make_function(&GRAILS::AtomDensityGridCalculator::getDensityFunction, python::return_internal_reference<>()),
					  &GRAILS::AtomDensityGridCalculator::setDensityFunction)
		.add_property("densityCombinationFunction", 
					  python::make_function(&GRAILS::AtomDensityGridCalculator::getDensityCombinationFunction, python::return_internal_reference<>()),
					  &GRAILS::AtomDensityGridCalculator::setDensityCombinationFunction)	
		.add_property("atomCoordinatesFunction", 
					  python::make_function(&GRAILS::AtomDensityGridCalculator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
					  &GRAILS::AtomDensityGridCalculator::setAtom3DCoordinatesFunction);

}
