/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CircularFingerprintGeneratorExport.cpp 
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

#include "CDPL/Chem/CircularFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	CDPL::Base::uint64 defAtomIdentifierFunction(const CDPL::Chem::CircularFingerprintGenerator::DefAtomIdentifierFunctor& func,
												 CDPL::Chem::Atom& atom, CDPL::Chem::MolecularGraph& molgraph)
	{
		return func(atom, molgraph);
	}

	CDPL::Base::uint64 defBondIdentifierFunction(const CDPL::Chem::CircularFingerprintGenerator::DefBondIdentifierFunctor& func, 
												 CDPL::Chem::Bond& bond)
	{
		return func(bond);
	}
}


void CDPLPythonChem::exportCircularFingerprintGenerator()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<Chem::CircularFingerprintGenerator>("CircularFingerprintGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::CircularFingerprintGenerator&>((python::arg("self"), python::arg("gen"))))
		.def(python::init<const Chem::MolecularGraph&, Util::BitSet&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("fp"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::CircularFingerprintGenerator>())	
		.def("setAtomIdentifierFunction", &Chem::CircularFingerprintGenerator::setAtomIdentifierFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setBondIdentifierFunction", &Chem::CircularFingerprintGenerator::setBondIdentifierFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setNumBits", &Chem::CircularFingerprintGenerator::setNumBits, 
			 (python::arg("self"), python::arg("num_bits")))
		.def("getNumBits", &Chem::CircularFingerprintGenerator::getNumBits, python::arg("self"))
		.def("setNumIterations", &Chem::CircularFingerprintGenerator::setNumIterations, 
			 (python::arg("self"), python::arg("num_iter")))
		.def("getNumIterations", &Chem::CircularFingerprintGenerator::getNumIterations, python::arg("self"))
		.def("removeDuplicates", &Chem::CircularFingerprintGenerator::removeDuplicates, (python::arg("self"), python::arg("remove")))
		.def("duplicatesRemoved", &Chem::CircularFingerprintGenerator::duplicatesRemoved, python::arg("self"))
		.def("includeAtomStereo", &Chem::CircularFingerprintGenerator::includeAtomStereo, (python::arg("self"), python::arg("include")))
		.def("includeBondStereo", &Chem::CircularFingerprintGenerator::includeBondStereo, (python::arg("self"), python::arg("include")))
		.def("atomStereoIncluded", &Chem::CircularFingerprintGenerator::atomStereoIncluded, python::arg("self"))
		.def("bondStereoIncluded", &Chem::CircularFingerprintGenerator::bondStereoIncluded, python::arg("self"))
		.def("generate", static_cast<void (Chem::CircularFingerprintGenerator::*)(const Chem::MolecularGraph&, Util::BitSet&)>(&Chem::CircularFingerprintGenerator::generate),
			 (python::arg("self"), python::arg("molgraph"), python::arg("fp")))
		.def("generate", static_cast<void (Chem::CircularFingerprintGenerator::*)(const Chem::MolecularGraph&)>(&Chem::CircularFingerprintGenerator::generate),
			 (python::arg("self"), python::arg("molgraph")))
		.def("getNumFeatures", &Chem::CircularFingerprintGenerator::getNumFeatures, python::arg("self"))
		.def("getFeatureIdentifier", &Chem::CircularFingerprintGenerator::getFeatureIdentifier, (python::arg("self"), python::arg("idx")))
		.def("getFeatureSubstructure", &Chem::CircularFingerprintGenerator::getFeatureSubstructure, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<>())
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::CircularFingerprintGenerator::operator=), 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.add_property("numFeatures", &Chem::CircularFingerprintGenerator::getNumFeatures)
		.add_property("numBits", &Chem::CircularFingerprintGenerator::getNumBits,
					  &Chem::CircularFingerprintGenerator::setNumBits)
		.add_property("numIterations", &Chem::CircularFingerprintGenerator::getNumIterations,
					  &Chem::CircularFingerprintGenerator::setNumIterations)
		.add_property("remDuplicates", &Chem::CircularFingerprintGenerator::duplicatesRemoved,
					  &Chem::CircularFingerprintGenerator::removeDuplicates)
		.add_property("incAtomStereo", &Chem::CircularFingerprintGenerator::atomStereoIncluded,
					  &Chem::CircularFingerprintGenerator::includeAtomStereo)
		.add_property("incBondStereo", &Chem::CircularFingerprintGenerator::bondStereoIncluded,
					  &Chem::CircularFingerprintGenerator::includeBondStereo)
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::CircularFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::CircularFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS);

	python::class_<Chem::CircularFingerprintGenerator::DefAtomIdentifierFunctor>("DefAtomIdentifierFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
										 Chem::CircularFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)))
		.def("__call__", &defAtomIdentifierFunction, (python::arg("self"), python::arg("atom"), python::arg("molgraph")));

	python::class_<Chem::CircularFingerprintGenerator::DefBondIdentifierFunctor>("DefBondIdentifierFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
										 Chem::CircularFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS)))
		.def("__call__", &defBondIdentifierFunction, (python::arg("self"), python::arg("bond")));
}
