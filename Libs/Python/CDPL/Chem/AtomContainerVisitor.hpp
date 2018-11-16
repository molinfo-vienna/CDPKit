/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerVisitor.hpp 
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


#ifndef CDPL_PYTHON_CHEM_ATOMCONTAINERVISITOR_HPP
#define CDPL_PYTHON_CHEM_ATOMCONTAINERVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define ATOMCONTAINER_IMPL()                                         \
	void orderAtoms(const CDPL::Chem::AtomCompareFunction& func) {   \
		this->get_override("orderAtoms")(boost::ref(func));          \
	}                                                                \
                                                                     \
	std::size_t getNumAtoms() const {                                \
		return this->get_override("getNumAtoms")();                  \
	}                                                                \
                                                                     \
	const CDPL::Chem::Atom& getAtom(std::size_t idx) const {         \
		return this->get_override("getAtom")(idx);                   \
	}                                                                \
                                                                     \
	bool containsAtom(const CDPL::Chem::Atom& atom) const {          \
		return this->get_override("containsAtom")(boost::ref(atom)); \
	}                                                                \
                                                                     \
	std::size_t getAtomIndex(const CDPL::Chem::Atom& atom) const {   \
		return this->get_override("getAtomIndex")(boost::ref(atom)); \
	}                                                                \
                                                                     \
	CDPL::Chem::Atom& getAtom(std::size_t idx)  {                    \
		return this->get_override("getAtom")(idx);                   \
	}                                                                \
                                                                     \
	std::size_t getNumEntities() const {                             \
		if (boost::python::override f = this->get_override("getNumEntities")) \
            return f();                                                       \
                                                                              \
		return CDPL::Chem::AtomContainer::getNumEntities();                   \
	}                                                                \
                                                                     \
	std::size_t getNumEntitiesDef() const {                          \
		return CDPL::Chem::AtomContainer::getNumEntities();          \
	}                                                                \
                                                                     \
	const CDPL::Chem::Entity3D& getEntity(std::size_t idx) const {   \
		if (boost::python::override f = this->get_override("getEntity")) \
            return f(idx);                                               \
                                                                         \
		return CDPL::Chem::AtomContainer::getEntity(idx);                \
	}                                                                \
                                                                     \
	CDPL::Chem::Entity3D& getEntity(std::size_t idx) {               \
		if (boost::python::override f = this->get_override("getEntity")) \
            return f(idx);                                               \
                                                                         \
		return CDPL::Chem::AtomContainer::getEntity(idx);                \
	}                                                                \
                                                                     \
	CDPL::Chem::Entity3D& getEntityDef(std::size_t idx) {            \
		return CDPL::Chem::AtomContainer::getEntity(idx);            \
	}


namespace CDPLPythonChem
{

	class AtomContainerVisitorBase
	{

	protected:
		static bool containsAtom(CDPL::Chem::AtomContainer& cntnr, CDPL::Chem::Atom& atom) {
			return cntnr.containsAtom(atom);
		}
	};

	template <typename Wrapper>
	class AtomContainerVirtualFunctionsVisitor : private AtomContainerVisitorBase, 
												 public boost::python::def_visitor<AtomContainerVirtualFunctionsVisitor<Wrapper> >
	{

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl	
				.def("getAtom", python::pure_virtual(static_cast<Chem::Atom& (Chem::AtomContainer::*)(std::size_t)>(&Chem::AtomContainer::getAtom)), 
					 (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
				.def("containsAtom", python::pure_virtual(&this->containsAtom), (python::arg("self"), python::arg("atom")))
				.def("getAtomIndex", python::pure_virtual(&getAtomIndex), (python::arg("self"), python::arg("atom")))
				.def("getNumAtoms", python::pure_virtual(&Chem::AtomContainer::getNumAtoms), python::arg("self"))
				.def("orderAtoms", python::pure_virtual(&Chem::AtomContainer::orderAtoms), (python::arg("self"), python::arg("func")))
				.def("getEntity", static_cast<Chem::Entity3D& (Chem::AtomContainer::*)(std::size_t)>(&Chem::AtomContainer::getEntity), 
					 &Wrapper::getEntityDef, (python::arg("self"), python::arg("idx")),
					 python::return_internal_reference<1>())
				.def("getNumEntities", &Chem::AtomContainer::getNumEntities, &Wrapper::getNumEntitiesDef, python::arg("self"));
		}

		static std::size_t getAtomIndex(CDPL::Chem::AtomContainer& cntnr, CDPL::Chem::Atom& atom) {
			return cntnr.getAtomIndex(atom);
		}
	};

	class AtomContainerSpecialFunctionsVisitor : private AtomContainerVisitorBase, 
												 public boost::python::def_visitor<AtomContainerSpecialFunctionsVisitor>
	{

		friend class boost::python::def_visitor_access;

	public:
		AtomContainerSpecialFunctionsVisitor(bool contains_only): containsOnly(contains_only) {}

	private:
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl.def("__contains__", &this->containsAtom, (python::arg("self"), python::arg("atom")));

			if (containsOnly)
				return;

			cl
				.def("__getitem__", static_cast<Chem::Atom& (Chem::AtomContainer::*)(std::size_t)>(&Chem::AtomContainer::getAtom),
					 (python::arg("self"), python::arg("idx")),
					 python::return_internal_reference<1>())
				.def("__len__", &Chem::AtomContainer::getNumAtoms, python::arg("self"));
		}

		bool containsOnly;
	};
}

#endif // CDPL_PYTHON_CHEM_ATOMCONTAINERVISITOR_HPP
