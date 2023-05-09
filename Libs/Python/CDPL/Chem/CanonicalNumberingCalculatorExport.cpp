/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CanonicalNumberingCalculatorExport.cpp 
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

#include "CDPL/Chem/CanonicalNumberingCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportCanonicalNumberingCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::CanonicalNumberingCalculator, boost::noncopyable>("CanonicalNumberingCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Util::STArray&>((python::arg("self"), python::arg("molgraph"), python::arg("numbering"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::CanonicalNumberingCalculator>())	
		.def("setAtomPropertyFlags", &Chem::CanonicalNumberingCalculator::setAtomPropertyFlags, 
			 (python::arg("self"), python::arg("flags")))
		.def("getAtomPropertyFlags", &Chem::CanonicalNumberingCalculator::getAtomPropertyFlags, python::arg("self"))
		.def("setBondPropertyFlags", &Chem::CanonicalNumberingCalculator::setBondPropertyFlags, 
			 (python::arg("self"), python::arg("flags")))
		.def("getBondPropertyFlags", &Chem::CanonicalNumberingCalculator::getBondPropertyFlags, python::arg("self"))
		.def("setHydrogenCountFunction", &Chem::CanonicalNumberingCalculator::setHydrogenCountFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getHydrogenCountFunction", &Chem::CanonicalNumberingCalculator::getHydrogenCountFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("calculate", &Chem::CanonicalNumberingCalculator::calculate, (python::arg("self"), python::arg("molgraph"), python::arg("numbering")))
		.add_property("atomPropertyFlags", &Chem::CanonicalNumberingCalculator::getAtomPropertyFlags, 
					  &Chem::CanonicalNumberingCalculator::setAtomPropertyFlags)
		.add_property("bondPropertyFlags", &Chem::CanonicalNumberingCalculator::getBondPropertyFlags, 
					  &Chem::CanonicalNumberingCalculator::setBondPropertyFlags)
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::CanonicalNumberingCalculator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::CanonicalNumberingCalculator::DEF_BOND_PROPERTY_FLAGS)
		.add_property("hydrogenCountFunc", 
					  python::make_function(&Chem::CanonicalNumberingCalculator::getHydrogenCountFunction, 
											python::return_internal_reference<>()),
					  &Chem::CanonicalNumberingCalculator::setHydrogenCountFunction);
}
