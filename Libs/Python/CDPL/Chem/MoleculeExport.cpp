/* 
 * MoleculeExport.cpp 
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


#include <memory>

#include <boost/python.hpp>

#include "CDPL/Chem/Molecule.hpp"
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

	struct MoleculeWrapper : CDPL::Chem::Molecule, boost::python::wrapper<CDPL::Chem::Molecule> 
	{

		typedef std::shared_ptr<MoleculeWrapper> SharedPointer;

		ATOMCONTAINER_IMPL()
		BONDCONTAINER_IMPL()

		void clear() {
			this->get_override("clear")();
		}

		CDPL::Chem::Atom& addAtom() {
			return this->get_override("addAtom")();
		}

		void removeAtom(std::size_t idx) {
			this->get_override("removeAtom")(idx);
		}

		CDPL::Chem::Bond& addBond(std::size_t atom1_idx, std::size_t atom2_idx) {
			return this->get_override("addBond")(atom1_idx, atom2_idx);
		}

		void removeBond(std::size_t idx) {
			this->get_override("removeBond")(idx);
		}

		void copy(const Molecule& mol) {
			this->get_override("copy")(boost::ref(mol));
		}
	
		void copy(const CDPL::Chem::MolecularGraph& molgraph) {
			this->get_override("copy")(boost::ref(molgraph));
		}

		void append(const Molecule& mol) {
			this->get_override("append")(boost::ref(mol));
		}

		void append(const CDPL::Chem::MolecularGraph& molgraph) {
			this->get_override("append")(boost::ref(molgraph));
		}

		void remove(const CDPL::Chem::MolecularGraph& molgraph) {
			this->get_override("remove")(boost::ref(molgraph));
		}

		void reserveMemoryForAtoms(std::size_t num_atoms) {
			if (boost::python::override f = this->get_override("reserveMemoryForAtoms"))
				f(num_atoms);    
			else
				Molecule::reserveMemoryForAtoms(num_atoms);
		}

		void reserveMemoryForAtomsDef(std::size_t num_atoms) {
			Molecule::reserveMemoryForAtoms(num_atoms);
		}

 		void reserveMemoryForBonds(std::size_t num_bonds) {
			if (boost::python::override f = this->get_override("reserveMemoryForBonds"))
				f(num_bonds);    
			else
				Molecule::reserveMemoryForBonds(num_bonds);
		}

		void reserveMemoryForBondsDef(std::size_t num_bonds) {
			Molecule::reserveMemoryForBonds(num_bonds);
		}

		MolecularGraph::SharedPointer clone() const {
			return this->get_override("clone")();
		}
	};
}


void CDPLPythonChem::exportMolecule()
{
	using namespace boost;
	using namespace CDPL;

	void (Chem::Molecule::*removeAtomFunc)(std::size_t) = &Chem::Molecule::removeAtom;
	void (Chem::Molecule::*removeBondFunc)(std::size_t) = &Chem::Molecule::removeBond;

	void (Chem::Molecule::*copyMolFunc)(const Chem::Molecule&) = &Chem::Molecule::copy;
	void (Chem::Molecule::*copyMolGraphFunc)(const Chem::MolecularGraph&) = &Chem::Molecule::copy;

	void (Chem::Molecule::*appendMolFunc)(const Chem::Molecule&) = &Chem::Molecule::append;
	void (Chem::Molecule::*appendMolGraphFunc)(const Chem::MolecularGraph&) = &Chem::Molecule::append;

	Chem::Molecule& (Chem::Molecule::*assignMolFunc)(const Chem::Molecule&) = &Chem::Molecule::operator=;
	Chem::Molecule& (Chem::Molecule::*assignMolGraphFunc)(const Chem::MolecularGraph&) = &Chem::Molecule::operator=;

	Chem::Molecule& (Chem::Molecule::*addMolFunc)(const Chem::Molecule&) = &Chem::Molecule::operator+=;
	Chem::Molecule& (Chem::Molecule::*addMolGraphFunc)(const Chem::MolecularGraph&) = &Chem::Molecule::operator+=;

	python::scope scope = python::class_<MoleculeWrapper, MoleculeWrapper::SharedPointer, 
		python::bases<Chem::MolecularGraph>,
		boost::noncopyable>("Molecule", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("reserveMemoryForAtoms", &Chem::Molecule::reserveMemoryForAtoms, &MoleculeWrapper::reserveMemoryForAtomsDef,
			 (python::arg("self"), python::arg("num_atoms")))
		.def("reserveMemoryForBonds", &Chem::Molecule::reserveMemoryForBonds, &MoleculeWrapper::reserveMemoryForBondsDef,
			 (python::arg("self"), python::arg("num_bonds")))
		.def("clear",  python::pure_virtual(&Chem::Molecule::clear), python::arg("self"))
		.def("addAtom",  python::pure_virtual(&Chem::Molecule::addAtom), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("addBond",  python::pure_virtual(&Chem::Molecule::addBond), 
			 (python::arg("self"), python::arg("atom1_idx"), python::arg("atom2_idx")),
			 python::return_internal_reference<1>())
		.def("removeAtom", python::pure_virtual(removeAtomFunc), (python::arg("self"), python::arg("idx")))
		.def("removeBond", python::pure_virtual(removeBondFunc), (python::arg("self"), python::arg("idx")))
		.def("copy", python::pure_virtual(copyMolFunc), (python::arg("self"), python::arg("mol")))
		.def("copy", python::pure_virtual(copyMolGraphFunc), (python::arg("self"), python::arg("molgraph")))
		.def("append", python::pure_virtual(appendMolFunc), (python::arg("self"), python::arg("mol")))
		.def("append", python::pure_virtual(appendMolGraphFunc), (python::arg("self"), python::arg("molgraph")))
		.def("remove", python::pure_virtual(&Chem::Molecule::remove), (python::arg("self"), python::arg("molgraph")))
		.def("assign", assignMolFunc, (python::arg("self"), python::arg("mol")), python::return_self<>())
		.def("assign", assignMolGraphFunc, (python::arg("self"), python::arg("molgraph")), python::return_self<>())
		.def("getAtoms", &createMutableAtomSequence<Chem::Molecule>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getBonds", &createMutableBondSequence<Chem::Molecule>, python::arg("self"),
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("__iadd__", addMolFunc, (python::arg("self"), python::arg("mol")), python::return_self<>())
		.def("__iadd__", addMolGraphFunc, (python::arg("self"), python::arg("molgraph")), python::return_self<>())
		.def("__isub__", &Chem::Molecule::operator-=, (python::arg("self"), python::arg("molgraph")), python::return_self<>())
		.def(AtomContainerVirtualFunctionsVisitor<MoleculeWrapper>())
		.def(BondContainerVirtualFunctionsVisitor())
		.def(AtomContainerSpecialFunctionsVisitor(true))
		.def(BondContainerSpecialFunctionsVisitor(true))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("atoms", python::make_function(&createMutableAtomSequence<Chem::Molecule>,
													 python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("bonds", python::make_function(&createMutableBondSequence<Chem::Molecule>,
													 python::with_custodian_and_ward_postcall<0, 1>()));

	MutableAtomSequenceExport<Chem::Molecule>("AtomSequence");
	MutableBondSequenceExport<Chem::Molecule>("BondSequence");

	python::register_ptr_to_python<Chem::Molecule::SharedPointer>();
}
