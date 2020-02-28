/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PathFingerprintGeneratorExport.cpp 
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

#include "CDPL/Chem/PathFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	CDPL::Base::uint64 defAtomDescriptorFunction(const CDPL::Chem::PathFingerprintGenerator::DefAtomDescriptorFunctor& func,
												 CDPL::Chem::Atom& atom)
	{
		return func(atom);
	}

	CDPL::Base::uint64 defBondDescriptorFunction(const CDPL::Chem::PathFingerprintGenerator::DefBondDescriptorFunctor& func, 
												 CDPL::Chem::Bond& bond)
	{
		return func(bond);
	}
}


void CDPLPythonChem::exportPathFingerprintGenerator()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<Chem::PathFingerprintGenerator>("PathFingerprintGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Util::BitSet&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("fp"))))
		.def(python::init<const Chem::PathFingerprintGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PathFingerprintGenerator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::PathFingerprintGenerator::operator=), 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("setAtomDescriptorFunction", &Chem::PathFingerprintGenerator::setAtomDescriptorFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setBondDescriptorFunction", &Chem::PathFingerprintGenerator::setBondDescriptorFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setMinPathLength", &Chem::PathFingerprintGenerator::setMinPathLength, 
			 (python::arg("self"), python::arg("min_length")))
		.def("setMaxPathLength", &Chem::PathFingerprintGenerator::setMaxPathLength, 
			 (python::arg("self"), python::arg("max_length")))
		.def("setNumBits", &Chem::PathFingerprintGenerator::setNumBits, 
			 (python::arg("self"), python::arg("num_bits")))
		.def("getMinPathLength", &Chem::PathFingerprintGenerator::getMinPathLength, python::arg("self"))
		.def("getMaxPathLength", &Chem::PathFingerprintGenerator::getMaxPathLength, python::arg("self"))
		.def("getNumBits", &Chem::PathFingerprintGenerator::getNumBits, python::arg("self"))
		.def("generate", &Chem::PathFingerprintGenerator::generate,
			 (python::arg("self"), python::arg("molgraph"), python::arg("fp")))
		.add_property("minPathLength", &Chem::PathFingerprintGenerator::getMinPathLength,
					  &Chem::PathFingerprintGenerator::setMinPathLength)
		.add_property("maxPathLength", &Chem::PathFingerprintGenerator::getMaxPathLength,
					  &Chem::PathFingerprintGenerator::setMaxPathLength)
		.add_property("numBits", &Chem::PathFingerprintGenerator::getNumBits,
					  &Chem::PathFingerprintGenerator::setNumBits)
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::PathFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::PathFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS);

	python::class_<Chem::PathFingerprintGenerator::DefAtomDescriptorFunctor>("DefAtomDescriptorFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
										 Chem::PathFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)))
		.def("__call__", &defAtomDescriptorFunction, (python::arg("self"), python::arg("atom")));

	python::class_<Chem::PathFingerprintGenerator::DefBondDescriptorFunctor>("DefBondDescriptorFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
										 Chem::PathFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS)))
		.def("__call__", &defBondDescriptorFunction, (python::arg("self"), python::arg("bond")));
}
