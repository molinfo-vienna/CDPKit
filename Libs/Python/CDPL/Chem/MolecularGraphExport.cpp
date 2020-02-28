/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphExport.cpp 
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
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "AtomContainerVisitor.hpp"
#include "BondContainerVisitor.hpp"
#include "AtomSequenceExport.hpp"
#include "BondSequenceExport.hpp"
#include "ClassExports.hpp"


namespace
{

	struct MolecularGraphWrapper : CDPL::Chem::MolecularGraph, boost::python::wrapper<CDPL::Chem::MolecularGraph> 
	{
	
		typedef boost::shared_ptr<MolecularGraphWrapper> SharedPointer;

		ATOMCONTAINER_IMPL()
		BONDCONTAINER_IMPL()

		PROPERTYCONTAINER_IMPL(MolecularGraphWrapper) 	

		MolecularGraph::SharedPointer clone() const {
			return this->get_override("clone")();
		}
	};
}


void CDPLPythonChem::exportMolecularGraph()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<MolecularGraphWrapper, MolecularGraphWrapper::SharedPointer,
										 python::bases<Chem::AtomContainer, Chem::BondContainer, Base::PropertyContainer>,
										 boost::noncopyable>("MolecularGraph", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("getAtoms", &createAtomSequence<Chem::MolecularGraph>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getBonds", &createBondSequence<Chem::MolecularGraph>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("clone", python::pure_virtual(&Chem::MolecularGraph::clone), python::arg("self"))
		.def(AtomContainerVirtualFunctionsVisitor<MolecularGraphWrapper>())
		.def(BondContainerVirtualFunctionsVisitor())
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<MolecularGraphWrapper>())
		.def(AtomContainerSpecialFunctionsVisitor(true))
		.def(BondContainerSpecialFunctionsVisitor(true))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("atoms", python::make_function(&createAtomSequence<Chem::MolecularGraph>,
													 python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("bonds", python::make_function(&createBondSequence<Chem::MolecularGraph>,
													 python::with_custodian_and_ward_postcall<0, 1>()));

	AtomSequenceExport<Chem::MolecularGraph>("AtomSequence");
	BondSequenceExport<Chem::MolecularGraph>("BondSequence");

	python::register_ptr_to_python<Chem::MolecularGraph::SharedPointer>();
}
