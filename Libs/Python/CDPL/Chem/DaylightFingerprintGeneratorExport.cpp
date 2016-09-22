/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DaylightFingerprintGeneratorExport.cpp 
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

#include "CDPL/Chem/DaylightFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	CDPL::Base::uint64 defAtomDescriptorFunction(const CDPL::Chem::DaylightFingerprintGenerator::DefAtomDescriptorFunctor& func,
												 CDPL::Chem::Atom& atom)
	{
		return func(atom);
	}

	CDPL::Base::uint64 defBondDescriptorFunction(const CDPL::Chem::DaylightFingerprintGenerator::DefBondDescriptorFunctor& func, 
												 CDPL::Chem::Bond& bond)
	{
		return func(bond);
	}
}


void CDPLPythonChem::exportDaylightFingerprintGenerator()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<Chem::DaylightFingerprintGenerator, 
										 boost::noncopyable>("DaylightFingerprintGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, Util::BitSet&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("fprint"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::DaylightFingerprintGenerator>())	
		.def("setAtomDescriptorFunction", &Chem::DaylightFingerprintGenerator::setAtomDescriptorFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setBondDescriptorFunction", &Chem::DaylightFingerprintGenerator::setBondDescriptorFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setMinPathLength", &Chem::DaylightFingerprintGenerator::setMinPathLength, 
			 (python::arg("self"), python::arg("min_length")))
		.def("setMaxPathLength", &Chem::DaylightFingerprintGenerator::setMaxPathLength, 
			 (python::arg("self"), python::arg("max_length")))
		.def("setNumBits", &Chem::DaylightFingerprintGenerator::setNumBits, 
			 (python::arg("self"), python::arg("num_bits")))
		.def("getMinPathLength", &Chem::DaylightFingerprintGenerator::getMinPathLength, python::arg("self"))
		.def("getMaxPathLength", &Chem::DaylightFingerprintGenerator::getMaxPathLength, python::arg("self"))
		.def("getNumBits", &Chem::DaylightFingerprintGenerator::getNumBits, python::arg("self"))
		.def("generate", &Chem::DaylightFingerprintGenerator::generate,
			 (python::arg("self"), python::arg("molgraph"), python::arg("fprint")))
		.add_property("minPathLength", &Chem::DaylightFingerprintGenerator::getMinPathLength,
					  &Chem::DaylightFingerprintGenerator::setMinPathLength)
		.add_property("maxPathLength", &Chem::DaylightFingerprintGenerator::getMaxPathLength,
					  &Chem::DaylightFingerprintGenerator::setMaxPathLength)
		.add_property("numBits", &Chem::DaylightFingerprintGenerator::getNumBits,
					  &Chem::DaylightFingerprintGenerator::setNumBits)
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::DaylightFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::DaylightFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS);

	python::class_<Chem::DaylightFingerprintGenerator::DefAtomDescriptorFunctor>("DefAtomDescriptorFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
										 Chem::DaylightFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)))
		.def("__call__", &defAtomDescriptorFunction, (python::arg("self"), python::arg("atom")));

	python::class_<Chem::DaylightFingerprintGenerator::DefBondDescriptorFunctor>("DefBondDescriptorFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
										 Chem::DaylightFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS)))
		.def("__call__", &defBondDescriptorFunction, (python::arg("self"), python::arg("bond")));
}
