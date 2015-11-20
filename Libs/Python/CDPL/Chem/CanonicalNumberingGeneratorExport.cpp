/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CanonicalNumberingGeneratorExport.cpp 
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

#include "CDPL/Chem/CanonicalNumberingGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportCanonicalNumberingGenerator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::CanonicalNumberingGenerator, boost::noncopyable>("CanonicalNumberingGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::CanonicalNumberingGenerator>())	
		.def("setAtomPropertyFlags", &Chem::CanonicalNumberingGenerator::setAtomPropertyFlags, 
			 (python::arg("self"), python::arg("flags")))
		.def("getAtomPropertyFlags", &Chem::CanonicalNumberingGenerator::getAtomPropertyFlags, python::arg("self"))
		.def("setBondPropertyFlags", &Chem::CanonicalNumberingGenerator::setBondPropertyFlags, 
			 (python::arg("self"), python::arg("flags")))
		.def("getBondPropertyFlags", &Chem::CanonicalNumberingGenerator::getBondPropertyFlags, python::arg("self"))
		.def("generate", &Chem::CanonicalNumberingGenerator::generate, (python::arg("self"), python::arg("molgraph")), 
			 python::return_internal_reference<>())
		.def("getResult", &Chem::CanonicalNumberingGenerator::getResult, python::arg("self"), 
			 python::return_internal_reference<>())
		.add_property("atomPropertyFlags", &Chem::CanonicalNumberingGenerator::getAtomPropertyFlags, 
					  &Chem::CanonicalNumberingGenerator::setAtomPropertyFlags)
		.add_property("bondPropertyFlags", &Chem::CanonicalNumberingGenerator::getBondPropertyFlags, 
					  &Chem::CanonicalNumberingGenerator::setBondPropertyFlags)
		.add_property("result", python::make_function(&Chem::CanonicalNumberingGenerator::getResult,
													  python::return_internal_reference<>()))
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::CanonicalNumberingGenerator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::CanonicalNumberingGenerator::DEF_BOND_PROPERTY_FLAGS);
}
