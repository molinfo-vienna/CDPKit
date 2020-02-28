/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionExport.cpp 
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
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/ReactionRole.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct ComponentSequence
	{

		ComponentSequence(CDPL::Chem::Reaction& rxn, unsigned int role): reaction(rxn), role(role) {}

		std::size_t getNumComponents() const {
			if (role == CDPL::Chem::ReactionRole::NONE)
				return reaction.getNumComponents();

			return reaction.getNumComponents(role);
		}

		const CDPL::Chem::Molecule& getComponent(std::size_t idx) const {
			if (role == CDPL::Chem::ReactionRole::NONE)
				return reaction.getComponent(idx);

			return reaction.getComponent(idx, role);
		}

		void removeComponent(std::size_t idx) const {
			if (role == CDPL::Chem::ReactionRole::NONE)
				reaction.removeComponent(idx);
			else
				reaction.removeComponent(idx, role);
		}

		bool containsComponent(const CDPL::Chem::Molecule& mol) const {
			if (role == CDPL::Chem::ReactionRole::NONE)
				return reaction.containsComponent(mol);
			
			return (reaction.getComponentRole(mol) == role);
		}

		CDPL::Chem::Reaction& reaction;
		unsigned int          role;
	};

	template <unsigned int Role>
	ComponentSequence createComponentSequence(CDPL::Chem::Reaction& rxn)
	{
		return ComponentSequence(rxn, Role);
	}

	template <unsigned int Role>
	std::size_t getNumComponents(const CDPL::Chem::Reaction& rxn)
	{
		return rxn.getNumComponents(Role);
	}

	struct ReactionWrapper : CDPL::Chem::Reaction, boost::python::wrapper<CDPL::Chem::Reaction> 
	{

		typedef boost::shared_ptr<ReactionWrapper> SharedPointer;

		PROPERTYCONTAINER_IMPL(ReactionWrapper) 

		unsigned int getComponentRole(const CDPL::Chem::Molecule& mol) const {
			return this->get_override("getComponentRole")(boost::ref(mol));
		}

		std::size_t getComponentIndex(const CDPL::Chem::Molecule& mol) const {
			return this->get_override("getComponentIndex")(boost::ref(mol));
		}

		bool containsComponent(const CDPL::Chem::Molecule& mol) const {
			return this->get_override("containsComponent")(boost::ref(mol));
		}

		void clear() {
			this->get_override("clear")();
		}

		std::size_t getNumComponents() const {
			return this->get_override("getNumComponents")();
		}

		std::size_t getNumComponents(unsigned int role) const {
			return this->get_override("getNumComponents")(role);
		}

		CDPL::Chem::Molecule& addComponent(unsigned int role) {
			return this->get_override("addComponent")(role);
		}

		// CDPL::Chem::Molecule& addComponent(unsigned int role, const CDPL::Chem::Molecule& mol) {
		// 	return this->get_override("addComponent")(role, boost::ref(mol));
		// }

		void removeComponents(unsigned int role) {
			this->get_override("removeComponents")(role);
		}

		void removeComponent(std::size_t idx) {
			this->get_override("removeComponent")(idx);
		}

		void removeComponent(std::size_t idx, unsigned int role) {
			this->get_override("removeComponent")(idx, role);
		}

		CDPL::Chem::Molecule& getComponent(std::size_t idx) {
			return this->get_override("getComponent")(idx);
		}

		CDPL::Chem::Molecule& getComponent(std::size_t idx, unsigned int role) {
			return this->get_override("getComponent")(idx, role);
		}
	
		const CDPL::Chem::Molecule& getComponent(std::size_t idx) const {
			return this->get_override("getComponent")(idx);
		}

		const CDPL::Chem::Molecule& getComponent(std::size_t idx, unsigned int role) const {
			return this->get_override("getComponent")(idx, role);
		}

		void swapComponentRoles(unsigned int role1, unsigned int role2) {
			this->get_override("swapComponentRoles")(role1, role2);
		}

		void copy(const Reaction& rxn) {
			this->get_override("copy")(boost::ref(rxn));
		}

		Reaction::SharedPointer clone() const {
			return this->get_override("clone")();
		}
	};
}


void CDPLPythonChem::exportReaction()
{
	using namespace boost;
	using namespace CDPL;

	Chem::Molecule& (Chem::Reaction::*addComponentFunc)(unsigned int) = &Chem::Reaction::addComponent;
	//Chem::Molecule& (Chem::Reaction::*addComponentCopyFunc)(unsigned int, const Chem::Molecule&) = &Chem::Reaction::addComponent;

	std::size_t (Chem::Reaction::*getNumComponentsFunc)() const = &Chem::Reaction::getNumComponents;
	std::size_t (Chem::Reaction::*getNumRoleComponentsFunc)(unsigned int) const = &Chem::Reaction::getNumComponents;

	Chem::Molecule& (Chem::Reaction::*getComponentFunc)(std::size_t) = &Chem::Reaction::getComponent;
	Chem::Molecule& (Chem::Reaction::*getRoleComponentFunc)(std::size_t, unsigned int) = &Chem::Reaction::getComponent;

	void (Chem::Reaction::*removeComponentFunc)(std::size_t) = &Chem::Reaction::removeComponent;
	void (Chem::Reaction::*removeRoleComponentFunc)(std::size_t, unsigned int) = &Chem::Reaction::removeComponent;

	python::scope scope = python::class_<ReactionWrapper, ReactionWrapper::SharedPointer,
		python::bases<Base::PropertyContainer>, boost::noncopyable>("Reaction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("clear", python::pure_virtual(&Chem::Reaction::clear), python::arg("self"))
		.def("addComponent", python::pure_virtual(addComponentFunc), 
			 (python::arg("self"), python::arg("role")), python::return_internal_reference<1>())
		// .def("addComponent", python::pure_virtual(addComponentCopyFunc), 
		// 	 (python::arg("self"), python::arg("role"), python::arg("mol")), 
		// 	 python::return_internal_reference<1>())
		.def("containsComponent", python::pure_virtual(&Chem::Reaction::containsComponent), 
		 	 (python::arg("self"), python::arg("mol"))) 
		.def("getComponentRole", python::pure_virtual(&Chem::Reaction::getComponentRole), 
		 	 (python::arg("self"), python::arg("mol"))) 
		.def("getComponentIndex", python::pure_virtual(&Chem::Reaction::getComponentIndex), 
		 	 (python::arg("self"), python::arg("mol"))) 
		.def("getNumComponents", python::pure_virtual(getNumRoleComponentsFunc), 
			 (python::arg("self"), python::arg("role")))
		.def("getNumComponents", python::pure_virtual(getNumComponentsFunc), python::arg("self"))
		.def("getComponent", python::pure_virtual(getRoleComponentFunc), 
			 (python::arg("self"), python::arg("idx"), python::arg("role")), 
			 python::return_internal_reference<1>())
		.def("getComponent", python::pure_virtual(getComponentFunc), 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
		.def("removeComponents", python::pure_virtual(&Chem::Reaction::removeComponents), 
			 (python::arg("self"), python::arg("role")))
		.def("removeComponent", python::pure_virtual(removeRoleComponentFunc), 
			 (python::arg("self"), python::arg("idx"), python::arg("role")))
		.def("removeComponent", python::pure_virtual(removeComponentFunc), 
			 (python::arg("self"), python::arg("idx")))
		.def("swapComponentRoles", python::pure_virtual(&Chem::Reaction::swapComponentRoles), 
			 (python::arg("self"), python::arg("role1"), python::arg("role2")))
		.def("clone", python::pure_virtual(&Chem::Reaction::clone), python::arg("self"))
		.def("copy", python::pure_virtual(&Chem::Reaction::copy), 
			 (python::arg("self"), python::arg("rxn")))
		.def("assign", &Chem::Reaction::operator=, (python::arg("self"), python::arg("rxn")), 
			 python::return_self<>())
		.def("getReactants", &createComponentSequence<Chem::ReactionRole::REACTANT>, python::arg("self"), 
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getAgents", &createComponentSequence<Chem::ReactionRole::AGENT>, python::arg("self"), 
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getProducts", &createComponentSequence<Chem::ReactionRole::PRODUCT>, python::arg("self"), 
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("__getitem__", getComponentFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__delitem__", removeComponentFunc, (python::arg("self"), python::arg("idx")))
		.def("__contains__", &Chem::Reaction::containsComponent, (python::arg("self"), python::arg("mol"))) 
		//.def("__len__", getNumComponentsFunc, python::arg("self"))
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<ReactionWrapper>())
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("reactants", python::make_function(&createComponentSequence<Chem::ReactionRole::REACTANT>, 
														 python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("agents", python::make_function(&createComponentSequence<Chem::ReactionRole::AGENT>, 
													  python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("products", python::make_function(&createComponentSequence<Chem::ReactionRole::PRODUCT>, 
														python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("numComponents", getNumComponentsFunc)
		.add_property("numReactants", &getNumComponents<Chem::ReactionRole::REACTANT>)
		.add_property("numAgents", &getNumComponents<Chem::ReactionRole::AGENT>)
		.add_property("numProducts", &getNumComponents<Chem::ReactionRole::PRODUCT>);

	python::class_<ComponentSequence>("ComponentSequence", python::no_init)
		.def("__contains__", &ComponentSequence::containsComponent, (python::arg("self"), python::arg("mol")))
		.def("__len__", &ComponentSequence::getNumComponents, python::arg("self"))
		.def("__delitem__", &ComponentSequence::removeComponent, 
			 (python::arg("self"), python::arg("idx")))
		.def("__getitem__", &ComponentSequence::getComponent, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>());

	python::register_ptr_to_python<Chem::Reaction::SharedPointer>();
}
