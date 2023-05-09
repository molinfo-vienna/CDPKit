/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondExport.cpp 
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

#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "AtomContainerVisitor.hpp"
#include "AtomSequenceExport.hpp"
#include "ClassExports.hpp"


namespace
{

    struct BondWrapper : CDPL::Chem::Bond, boost::python::wrapper<CDPL::Chem::Bond> 
	{

	    ATOMCONTAINER_IMPL()
	
		PROPERTYCONTAINER_IMPL(BondWrapper) 

	    const CDPL::Chem::Molecule& getMolecule() const {
			return this->get_override("getMolecule")();
		}

		CDPL::Chem::Molecule& getMolecule() {
			return this->get_override("getMolecule")();
		}

	    std::size_t getIndex() const {
			return this->get_override("getIndex")();
		}

	    const CDPL::Chem::Atom& getBegin() const {
		    return this->get_override("getBegin")();
		}

	    CDPL::Chem::Atom& getBegin() {
		    return this->get_override("getBegin")();
	    }

	    const CDPL::Chem::Atom& getEnd() const {
		    return this->get_override("getEnd")();
		}

	    CDPL::Chem::Atom& getEnd() {
		    return this->get_override("getEnd")();
		}

	    const CDPL::Chem::Atom& getNeighbor(const CDPL::Chem::Atom& atom) const {
		    return this->get_override("getNeighbor")(boost::ref(atom));
		}

	    CDPL::Chem::Atom& getNeighbor(const CDPL::Chem::Atom& atom) {
		    return this->get_override("getNeighbor")(boost::ref(atom));
		}

		static CDPL::Chem::Bond& assign(CDPL::Chem::Bond& self, CDPL::Chem::Bond& bond) {
			return (self = bond);
		}

	    CDPL::Chem::Atom& getNeighborWrapper(CDPL::Chem::Bond& self, CDPL::Chem::Atom& atom) {
  		    return self.getNeighbor(atom);
		}
	};
}


void CDPLPythonChem::exportBond()
{
	using namespace boost;
	using namespace CDPL;

	Chem::Atom& (Chem::Bond::*getBeginFunc)() = &Chem::Bond::getBegin;
	Chem::Atom& (Chem::Bond::*getEndFunc)() = &Chem::Bond::getEnd;

	Chem::Molecule& (Chem::Bond::*getMoleculeFunc)() = &Chem::Bond::getMolecule;

	python::scope scope = python::class_<BondWrapper, python::bases<Chem::AtomContainer, Base::PropertyContainer>,
				   boost::noncopyable>("Bond", python::no_init)
		.def(python::init<>(python::arg("self")))
	    .def("getNeighbor", python::pure_virtual(&BondWrapper::getNeighborWrapper),
			 (python::arg("self"), python::arg("atom")), python::return_internal_reference<1>())
	    .def("getBegin", python::pure_virtual(getBeginFunc), python::arg("self"), python::return_internal_reference<1>())
	    .def("getEnd", python::pure_virtual(getEndFunc), python::arg("self"), python::return_internal_reference<1>())
		.def("getMolecule", python::pure_virtual(getMoleculeFunc), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("getIndex", python::pure_virtual(&Chem::Bond::getIndex), python::arg("self"))
		.def("assign", &BondWrapper::assign, (python::arg("self"), python::arg("bond")), python::return_self<>())
		.def("getAtoms", &createAtomSequence<Chem::AtomContainer>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def(AtomContainerVirtualFunctionsVisitor<BondWrapper>())
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<BondWrapper>())
		.def(AtomContainerSpecialFunctionsVisitor(true))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("begin", python::make_function(getBeginFunc, python::return_internal_reference<1>()))
		.add_property("end", python::make_function(getEndFunc, python::return_internal_reference<1>()))
		.add_property("molecule", python::make_function(getMoleculeFunc, python::return_internal_reference<1>()))
		.add_property("index", &Chem::Atom::getIndex)
		.add_property("atoms", python::make_function(&createAtomSequence<Chem::Bond>, 
													 python::with_custodian_and_ward_postcall<0, 1>()));

	AtomSequenceExport<Chem::Bond>("AtomSequence");
}
