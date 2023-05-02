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

#include "CDPL/GRAIL/AtomDensityGridCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	void calculate(CDPL::GRAIL::AtomDensityGridCalculator& calculator, CDPL::Chem::AtomContainer& atoms, CDPL::Grid::DSpatialGrid& grid)
	{
		calculator.calculate(atoms, grid);
	}
}


void CDPLPythonGRAIL::exportAtomDensityGridCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::class_<GRAIL::AtomDensityGridCalculator, GRAIL::AtomDensityGridCalculator::SharedPointer, boost::noncopyable>("AtomDensityGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const GRAIL::AtomDensityGridCalculator::DensityFunction&>(
				 (python::arg("self"), python::arg("func"))))
		.def(python::init<const GRAIL::AtomDensityGridCalculator::DensityFunction&, const GRAIL::AtomDensityGridCalculator::DensityCombinationFunction&>(
				 (python::arg("self"), python::arg("density_func"), python::arg("comb_func"))))
		.def(python::init<const GRAIL::AtomDensityGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::AtomDensityGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&GRAIL::AtomDensityGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setDistanceCutoff", &GRAIL::AtomDensityGridCalculator::setDistanceCutoff,
			 (python::arg("self"), python::arg("dist")))
		.def("getDistanceCutoff", &GRAIL::AtomDensityGridCalculator::getDistanceCutoff,
			 python::arg("self"))
		.def("getDensityFunction", &GRAIL::AtomDensityGridCalculator::getDensityFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setDensityFunction", &GRAIL::AtomDensityGridCalculator::setDensityFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getDensityFunction", &GRAIL::AtomDensityGridCalculator::getDensityFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setDensityCombinationFunction", &GRAIL::AtomDensityGridCalculator::setDensityCombinationFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getDensityCombinationFunction", &GRAIL::AtomDensityGridCalculator::getDensityCombinationFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setAtom3DCoordinatesFunction", &GRAIL::AtomDensityGridCalculator::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &GRAIL::AtomDensityGridCalculator::getAtom3DCoordinatesFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("calculate", &calculate, (python::arg("self"), python::arg("atoms"), python::arg("grid")))
		.add_property("distanceCutoff", &GRAIL::AtomDensityGridCalculator::getDistanceCutoff, &GRAIL::AtomDensityGridCalculator::setDistanceCutoff)
		.add_property("densityFunction", 
					  python::make_function(&GRAIL::AtomDensityGridCalculator::getDensityFunction, python::return_internal_reference<>()),
					  &GRAIL::AtomDensityGridCalculator::setDensityFunction)
		.add_property("densityCombinationFunction", 
					  python::make_function(&GRAIL::AtomDensityGridCalculator::getDensityCombinationFunction, python::return_internal_reference<>()),
					  &GRAIL::AtomDensityGridCalculator::setDensityCombinationFunction)	
		.add_property("atomCoordinatesFunction", 
					  python::make_function(&GRAIL::AtomDensityGridCalculator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
					  &GRAIL::AtomDensityGridCalculator::setAtom3DCoordinatesFunction);

}
