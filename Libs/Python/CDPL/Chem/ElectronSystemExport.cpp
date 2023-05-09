/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ElectronSystemExport.cpp 
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

#include "CDPL/Chem/ElectronSystem.hpp"
#include "CDPL/Chem/Atom.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "AtomContainerVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	bool addAtom(CDPL::Chem::ElectronSystem& elec_sys, CDPL::Chem::Atom& atom, std::size_t elec_contrib)
	{
		return elec_sys.addAtom(atom, elec_contrib);
	}

	bool removeAtom(CDPL::Chem::ElectronSystem& elec_sys, CDPL::Chem::Atom& atom)
	{
		return elec_sys.removeAtom(atom);
	}

	std::size_t getElectronContrib(CDPL::Chem::ElectronSystem& elec_sys, CDPL::Chem::Atom& atom)
	{
		return elec_sys.getElectronContrib(atom);
	}

	void setElectronContrib(CDPL::Chem::ElectronSystem& elec_sys, CDPL::Chem::Atom& atom, std::size_t elec_contrib)
	{
		elec_sys.setElectronContrib(atom, elec_contrib);
	}

	bool connected(CDPL::Chem::ElectronSystem& elec_sys1, CDPL::Chem::ElectronSystem& elec_sys2, CDPL::Chem::BondContainer& bonds)
	{
		return elec_sys1.connected(elec_sys2, bonds);
	}
}


void CDPLPythonChem::exportElectronSystem()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::ElectronSystem, Chem::ElectronSystem::SharedPointer, 
				   python::bases<Chem::AtomContainer> >("ElectronSystem", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::ElectronSystem&>((python::arg("self"), python::arg("elec_sys")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ElectronSystem>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::ElectronSystem::operator=), (python::arg("self"), python::arg("elec_sys")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("addAtom", &addAtom, (python::arg("self"), python::arg("atom"), python::arg("elec_contrib")),
			 python::with_custodian_and_ward<1, 2>())
		.def("addAtoms", &Chem::ElectronSystem::addAtoms, (python::arg("self"), python::arg("elec_sys")),
			 python::with_custodian_and_ward<1, 2>())
		.def("removeAtom", static_cast<void (Chem::ElectronSystem::*)(std::size_t)>(&Chem::ElectronSystem::removeAtom),
			 (python::arg("self"), python::arg("idx")))
		.def("removeAtom", &removeAtom, (python::arg("self"), python::arg("atom")))
		.def("clear", &Chem::ElectronSystem::clear, python::arg("self"))
		.def("swap", &Chem::ElectronSystem::swap, (python::arg("self"), python::arg("elec_sys")))
		.def("getNumElectrons", &Chem::ElectronSystem::getNumElectrons, python::arg("self"))
		.def("getElectronContrib", &getElectronContrib, (python::arg("self"), python::arg("atom")))
		.def("getElectronContrib", static_cast<std::size_t (Chem::ElectronSystem::*)(std::size_t) const>(&Chem::ElectronSystem::getElectronContrib),
			 (python::arg("self"), python::arg("atom")))
		.def("setElectronContrib", &setElectronContrib, (python::arg("self"), python::arg("atom"), python::arg("elec_contrib")))
		.def("setElectronContrib", static_cast<void (Chem::ElectronSystem::*)(std::size_t, std::size_t)>(&Chem::ElectronSystem::setElectronContrib),
			 (python::arg("self"), python::arg("atom"), python::arg("elec_contrib")))
		.def("merge", &Chem::ElectronSystem::merge, (python::arg("self"), python::arg("elec_sys")))
		.def("overlaps", &Chem::ElectronSystem::overlaps, (python::arg("self"), python::arg("elec_sys")))
		.def("contains", &Chem::ElectronSystem::contains, (python::arg("self"), python::arg("elec_sys")))
		.def("connected", &connected, (python::arg("self"), python::arg("elec_sys"), python::arg("bonds")))
		.def(AtomContainerSpecialFunctionsVisitor(false))
		.add_property("numElectrons", &Chem::ElectronSystem::getNumElectrons);
}

