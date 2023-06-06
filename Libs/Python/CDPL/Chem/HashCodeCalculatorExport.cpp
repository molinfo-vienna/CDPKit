/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HashCodeCalculatorExport.cpp 
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

#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	std::uint64_t defAtomHashSeedFunction(const CDPL::Chem::HashCodeCalculator::DefAtomHashSeedFunctor& func, 
										  CDPL::Chem::Atom& atom)
	{
		return func(atom);
	}

	std::uint64_t defBondHashSeedFunction(const CDPL::Chem::HashCodeCalculator::DefBondHashSeedFunctor& func,
										  CDPL::Chem::Bond& bond)
	{
		return func(bond);
	}
}


void CDPLPythonChem::exportHashCodeCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<Chem::HashCodeCalculator, boost::noncopyable>("HashCodeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::HashCodeCalculator>())	
		.def("setAtomHashSeedFunction", &Chem::HashCodeCalculator::setAtomHashSeedFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("setBondHashSeedFunction", &Chem::HashCodeCalculator::setBondHashSeedFunction,
			 (python::arg("self"), python::arg("func")))
		.def("includeGlobalStereoFeatures", &Chem::HashCodeCalculator::includeGlobalStereoFeatures, 
			 (python::arg("self"), python::arg("include")))
		.def("globalStereoFeaturesIncluded", &Chem::HashCodeCalculator::globalStereoFeaturesIncluded, python::arg("self"))
		.def("calculate", &Chem::HashCodeCalculator::calculate, (python::arg("self"), python::arg("molgraph")))
		.def("getResult", &Chem::HashCodeCalculator::getResult, python::arg("self"))
		.def_readonly("DEF_ATOM_PROPERTY_FLAGS", Chem::HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS)
		.def_readonly("DEF_BOND_PROPERTY_FLAGS", Chem::HashCodeCalculator::DEF_BOND_PROPERTY_FLAGS)
		.add_property("result", &Chem::HashCodeCalculator::getResult)
		.add_property("globalStereoFeatures", &Chem::HashCodeCalculator::globalStereoFeaturesIncluded,
					  &Chem::HashCodeCalculator::includeGlobalStereoFeatures)
		.def("__call__", &Chem::HashCodeCalculator::calculate, (python::arg("self"), python::arg("molgraph")));

	python::class_<Chem::HashCodeCalculator::DefAtomHashSeedFunctor>("DefAtomHashSeedFunctor", python::no_init)
		.def(python::init<const Chem::HashCodeCalculator&, 
			 unsigned int>((python::arg("self"), python::arg("calc"), 
							python::arg("flags") = Chem::HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS)))
		.def("__call__", &defAtomHashSeedFunction, (python::arg("self"), python::arg("atom")));

	python::class_<Chem::HashCodeCalculator::DefBondHashSeedFunctor>("DefBondHashSeedFunctor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), 
										python::arg("flags") = Chem::HashCodeCalculator::DEF_BOND_PROPERTY_FLAGS)))
		.def("__call__", &defBondHashSeedFunction, (python::arg("self"), python::arg("bond")));
}
