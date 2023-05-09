/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Hydrogen3DCoordinatesCalculatorExport.cpp 
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

#include "CDPL/Chem/Hydrogen3DCoordinatesCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportHydrogen3DCoordinatesCalculator()
{
    using namespace boost;
    using namespace CDPL;

    bool (Chem::Hydrogen3DCoordinatesCalculator::*undefOnlyGetterFunc)() const = &Chem::Hydrogen3DCoordinatesCalculator::undefinedOnly;
    void (Chem::Hydrogen3DCoordinatesCalculator::*undefOnlySetterFunc)(bool) = &Chem::Hydrogen3DCoordinatesCalculator::undefinedOnly;

    python::class_<Chem::Hydrogen3DCoordinatesCalculator, boost::noncopyable>("Hydrogen3DCoordinatesCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Math::Vector3DArray&, bool>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("coords"), python::arg("undef_only") = true)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::Hydrogen3DCoordinatesCalculator>())	
		.def("undefinedOnly", undefOnlySetterFunc, (python::arg("self"), python::arg("undef_only")))
		.def("undefinedOnly", undefOnlyGetterFunc, python::arg("self"))
		.def("setAtom3DCoordinatesFunction", &Chem::Hydrogen3DCoordinatesCalculator::setAtom3DCoordinatesFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &Chem::Hydrogen3DCoordinatesCalculator::getAtom3DCoordinatesFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setAtom3DCoordinatesCheckFunction", &Chem::Hydrogen3DCoordinatesCalculator::setAtom3DCoordinatesCheckFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesCheckFunction", &Chem::Hydrogen3DCoordinatesCalculator::getAtom3DCoordinatesCheckFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setup", &Chem::Hydrogen3DCoordinatesCalculator::setup, 
			 (python::arg("self"), python::arg("molgraph")))
		.def("calculate", static_cast<void (Chem::Hydrogen3DCoordinatesCalculator::*)(const Chem::MolecularGraph&, Math::Vector3DArray&, bool)>(
				 &Chem::Hydrogen3DCoordinatesCalculator::calculate), 
			 (python::arg("self"), python::arg("molgraph"), python::arg("coords"), python::arg("init_coords") = true))
		.def("calculate", static_cast<void (Chem::Hydrogen3DCoordinatesCalculator::*)(Math::Vector3DArray&, bool)>(
				 &Chem::Hydrogen3DCoordinatesCalculator::calculate), 
			 (python::arg("self"), python::arg("coords"), python::arg("init_coords") = true))

		.add_property("undefinedOnly", undefOnlyGetterFunc, undefOnlySetterFunc)
		.add_property("coordsFunction", 
					  python::make_function(&Chem::Hydrogen3DCoordinatesCalculator::getAtom3DCoordinatesFunction, 
											python::return_internal_reference<>()),
					  &Chem::Hydrogen3DCoordinatesCalculator::setAtom3DCoordinatesFunction)
		.add_property("coordsCheckFunction", 
					  python::make_function(&Chem::Hydrogen3DCoordinatesCalculator::getAtom3DCoordinatesCheckFunction, 
											python::return_internal_reference<>()),
					  &Chem::Hydrogen3DCoordinatesCalculator::setAtom3DCoordinatesCheckFunction);
}
