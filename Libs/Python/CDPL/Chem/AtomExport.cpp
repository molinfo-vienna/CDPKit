/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomExport.cpp 
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

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "AtomContainerVisitor.hpp"
#include "BondContainerVisitor.hpp"
#include "AtomSequenceExport.hpp"
#include "BondSequenceExport.hpp"
#include "ClassExports.hpp"


namespace
{

	struct AtomWrapper : CDPL::Chem::Atom, boost::python::wrapper<CDPL::Chem::Atom> 
	{

		ATOMCONTAINER_IMPL()
		BONDCONTAINER_IMPL()

		PROPERTYCONTAINER_IMPL(AtomWrapper) 

		const CDPL::Chem::Molecule& getMolecule() const {
			return this->get_override("getMolecule")();
		}

		CDPL::Chem::Molecule& getMolecule() {
			return this->get_override("getMolecule")();
		}

		const CDPL::Chem::Bond& getBondToAtom(const CDPL::Chem::Atom& atom) const {
			return this->get_override("getBondToAtom")(boost::ref(atom));
		}

		CDPL::Chem::Bond& getBondToAtom(const CDPL::Chem::Atom& atom) {
			return this->get_override("getBondToAtom")(boost::ref(atom));
		}

		const CDPL::Chem::Bond* findBondToAtom(const CDPL::Chem::Atom& atom) const {
			return this->get_override("findBondToAtom")(boost::ref(atom));
		}

		CDPL::Chem::Bond* findBondToAtom(const CDPL::Chem::Atom& atom) {
			return this->get_override("findBondToAtom")(boost::ref(atom));
		}
	
		std::size_t getIndex() const {
			return this->get_override("getIndex")();
		}

		static CDPL::Chem::Bond& getBondToAtomWrapper(CDPL::Chem::Atom& self, CDPL::Chem::Atom& atom) {
			return self.getBondToAtom(atom);
		}

		static CDPL::Chem::Bond* findBondToAtomWrapper(CDPL::Chem::Atom& self, CDPL::Chem::Atom& atom) {
			return self.findBondToAtom(atom);
		}

		static CDPL::Chem::Atom& assign(CDPL::Chem::Atom& self, CDPL::Chem::Atom& atom) {
			return (self = atom);
		}
	};
}


void CDPLPythonChem::exportAtom()
{
	using namespace boost;
	using namespace CDPL;

	Chem::Molecule& (Chem::Atom::*getMoleculeFunc)() = &Chem::Atom::getMolecule;

	python::scope scope = python::class_<AtomWrapper, python::bases<Chem::AtomContainer, Chem::BondContainer, Chem::Entity3D>,
		boost::noncopyable>("Atom", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("getMolecule", python::pure_virtual(getMoleculeFunc), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("getBondToAtom", python::pure_virtual(&AtomWrapper::getBondToAtomWrapper), 
			 (python::arg("self"), python::arg("atom")), python::return_internal_reference<1>())
		.def("findBondToAtom", python::pure_virtual(&AtomWrapper::findBondToAtomWrapper),
			 (python::arg("self"), python::arg("atom")), python::return_internal_reference<1>())
		.def("getIndex", python::pure_virtual(&Chem::Atom::getIndex), python::arg("self"))
		.def("assign", &AtomWrapper::assign, (python::arg("self"), python::arg("atom")), python::return_self<>())
		.def("getAtoms", &createAtomSequence<Chem::AtomContainer>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getBonds", &createBondSequence<Chem::BondContainer>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def(AtomContainerVirtualFunctionsVisitor<AtomWrapper>())
		.def(BondContainerVirtualFunctionsVisitor())
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<AtomWrapper>())
		.def(AtomContainerSpecialFunctionsVisitor(true))
		.def(BondContainerSpecialFunctionsVisitor(true))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("molecule", python::make_function(getMoleculeFunc, python::return_internal_reference<1>()))
		.add_property("index", &Chem::Atom::getIndex)
		.add_property("atoms", python::make_function(&createAtomSequence<Chem::Atom>, 
													 python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("bonds", python::make_function(&createBondSequence<Chem::Atom>, 
													 python::with_custodian_and_ward_postcall<0, 1>()));

	AtomSequenceExport<Chem::Atom>("AtomSequence");
	BondSequenceExport<Chem::Atom>("BondSequence");
}
