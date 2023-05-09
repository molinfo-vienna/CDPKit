/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentExport.cpp 
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

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "AtomContainerVisitor.hpp"
#include "BondContainerVisitor.hpp"
#include "MutableAtomSequenceExport.hpp"
#include "MutableBondSequenceExport.hpp"
#include "ClassExports.hpp"


namespace
{

	bool addAtom(CDPL::Chem::Fragment& frag, CDPL::Chem::Atom& atom)
	{
		return frag.addAtom(atom);
	}

	bool addBond(CDPL::Chem::Fragment& frag, CDPL::Chem::Bond& bond)
	{
		return frag.addBond(bond);
	}

	bool removeAtom(CDPL::Chem::Fragment& frag, CDPL::Chem::Atom& atom)
	{
		return frag.removeAtom(atom);
	}

	bool removeBond(CDPL::Chem::Fragment& frag, CDPL::Chem::Bond& bond)
	{
		return frag.removeBond(bond);
	}
}


void CDPLPythonChem::exportFragment()
{
	using namespace boost;
	using namespace CDPL;

	void (Chem::Fragment::*removeAtomFunc)(std::size_t) = &Chem::Fragment::removeAtom;
	void (Chem::Fragment::*removeBondFunc)(std::size_t) = &Chem::Fragment::removeBond;

	Chem::Fragment& (Chem::Fragment::*copyMolGraphFunc)(const Chem::MolecularGraph&) = &Chem::Fragment::operator=;
	Chem::Fragment& (Chem::Fragment::*copyFragFunc)(const Chem::Fragment&) = &Chem::Fragment::operator=;

	python::scope scope = python::class_<Chem::Fragment, Chem::Fragment::SharedPointer, 
										 python::bases<Chem::MolecularGraph> >("Fragment", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::Fragment&>((python::arg("self"), python::arg("frag")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def("assign", copyFragFunc, (python::arg("self"), python::arg("frag")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("assign", copyMolGraphFunc, (python::arg("self"), python::arg("molgraph")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("addAtom", &addAtom, (python::arg("self"), python::arg("atom")),
			 python::with_custodian_and_ward<1, 2>())
		.def("removeAtom", removeAtomFunc, (python::arg("self"), python::arg("idx")))
		.def("removeAtom", &removeAtom, (python::arg("self"), python::arg("atom")))
		.def("addBond", &addBond, (python::arg("self"), python::arg("bond")), 
			 python::with_custodian_and_ward<1, 2>())
		.def("removeBond", removeBondFunc, (python::arg("self"), python::arg("idx")))
		.def("removeBond", &removeBond, (python::arg("self"), python::arg("bond")))
		.def("clear", &Chem::Fragment::clear, python::arg("self"))
		.def("swap", static_cast<void (Chem::Fragment::*)(Chem::Fragment&)>(&Chem::Fragment::swap), (python::arg("self"), python::arg("frag")))
		.def("getAtoms", &createMutableAtomSequence<Chem::Fragment>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getBonds", &createMutableBondSequence<Chem::Fragment>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("reserveMemoryForAtoms", &Chem::Fragment::reserveMemoryForAtoms, (python::arg("self"), python::arg("num_atoms")))
		.def("reserveMemoryForBonds", &Chem::Fragment::reserveMemoryForBonds, (python::arg("self"), python::arg("num_bonds")))
		.def(AtomContainerSpecialFunctionsVisitor(true))
		.def(BondContainerSpecialFunctionsVisitor(true))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.def("__iadd__", &Chem::Fragment::operator+=, (python::arg("self"), python::arg("molgraph")), 
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("__isub__", &Chem::Fragment::operator-=, (python::arg("self"), python::arg("molgraph")), 
			 python::return_self<>())
		.add_property("atoms", python::make_function(&createMutableAtomSequence<Chem::Fragment>,
													 python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("bonds", python::make_function(&createMutableBondSequence<Chem::Fragment>,
													 python::with_custodian_and_ward_postcall<0, 1>()));

	MutableAtomSequenceExport<Chem::Fragment>("AtomSequence");
	MutableBondSequenceExport<Chem::Fragment>("BondSequence");
}

