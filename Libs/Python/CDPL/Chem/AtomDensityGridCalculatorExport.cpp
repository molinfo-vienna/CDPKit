/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDensityGridCalculatorExport.cpp 
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

#include "CDPL/Chem/AtomDensityGridCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	void calculate(CDPL::Chem::AtomDensityGridCalculator& calculator, CDPL::Chem::AtomContainer& atoms, CDPL::Grid::DSpatialGrid& grid)
	{
		calculator.calculate(atoms, grid);
	}
}


void CDPLPythonChem::exportAtomDensityGridCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::class_<Chem::AtomDensityGridCalculator, Chem::AtomDensityGridCalculator::SharedPointer, boost::noncopyable>("AtomDensityGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::AtomDensityGridCalculator::DensityFunction&>(
				 (python::arg("self"), python::arg("func"))))
		.def(python::init<const Chem::AtomDensityGridCalculator::DensityFunction&, const Chem::AtomDensityGridCalculator::DensityCombinationFunction&>(
				 (python::arg("self"), python::arg("density_func"), python::arg("comb_func"))))
		.def(python::init<const Chem::AtomDensityGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AtomDensityGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::AtomDensityGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setDensityFunction", &Chem::AtomDensityGridCalculator::setDensityFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getDensityFunction", &Chem::AtomDensityGridCalculator::getDensityFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setDensityCombinationFunction", &Chem::AtomDensityGridCalculator::setDensityCombinationFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getDensityCombinationFunction", &Chem::AtomDensityGridCalculator::getDensityCombinationFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setAtom3DCoordinatesFunction", &Chem::AtomDensityGridCalculator::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &Chem::AtomDensityGridCalculator::getAtom3DCoordinatesFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("calculate", &calculate, (python::arg("self"), python::arg("atoms"), python::arg("grid")))
		.add_property("densityFunction", 
					  python::make_function(&Chem::AtomDensityGridCalculator::getDensityFunction, python::return_internal_reference<>()),
					  &Chem::AtomDensityGridCalculator::setDensityFunction)
		.add_property("densityCombinationFunction", 
					  python::make_function(&Chem::AtomDensityGridCalculator::getDensityCombinationFunction, python::return_internal_reference<>()),
					  &Chem::AtomDensityGridCalculator::setDensityCombinationFunction)	
		.add_property("atomCoordinatesFunction", 
					  python::make_function(&Chem::AtomDensityGridCalculator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
					  &Chem::AtomDensityGridCalculator::setAtom3DCoordinatesFunction);

}
