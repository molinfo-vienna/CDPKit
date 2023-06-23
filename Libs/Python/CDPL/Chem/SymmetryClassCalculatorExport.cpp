/* 
 * SymmetryClassCalculatorExport.cpp 
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

#include "CDPL/Chem/SymmetryClassCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportSymmetryClassCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::SymmetryClassCalculator, boost::noncopyable>("SymmetryClassCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Util::STArray&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("class_ids"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SymmetryClassCalculator>())	
		.def("setAtomPropertyFlags", &Chem::SymmetryClassCalculator::setAtomPropertyFlags, 
			 (python::arg("self"), python::arg("flags")))
		.def("setBondPropertyFlags", &Chem::SymmetryClassCalculator::setBondPropertyFlags, 
			 (python::arg("self"), python::arg("flags")))
		.def("includeImplicitHydrogens", &Chem::SymmetryClassCalculator::includeImplicitHydrogens, 
			 (python::arg("self"), python::arg("include")))
		.def("getAtomPropertyFlags", &Chem::SymmetryClassCalculator::getAtomPropertyFlags, python::arg("self"))
		.def("getBondPropertyFlags", &Chem::SymmetryClassCalculator::getBondPropertyFlags, python::arg("self"))
		.def("implicitHydrogensIncluded", &Chem::SymmetryClassCalculator::implicitHydrogensIncluded, python::arg("self"))
		.def("calculate", &Chem::SymmetryClassCalculator::calculate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("class_ids")))
		.add_property("atomPropertyFlags", &Chem::SymmetryClassCalculator::getAtomPropertyFlags, 
					  &Chem::SymmetryClassCalculator::setAtomPropertyFlags)
		.add_property("bondPropertyFlags", &Chem::SymmetryClassCalculator::getBondPropertyFlags, 
					  &Chem::SymmetryClassCalculator::setBondPropertyFlags)
		.add_property("hydrogenComplete", &Chem::SymmetryClassCalculator::implicitHydrogensIncluded, 
					  &Chem::SymmetryClassCalculator::includeImplicitHydrogens)
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::SymmetryClassCalculator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::SymmetryClassCalculator::DEF_BOND_PROPERTY_FLAGS);
}
