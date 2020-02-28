/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionRuleMatchExport.cpp 
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

#include "CDPL/ConfGen/TorsionRuleMatch.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct AtomArray
	{

		AtomArray(const CDPL::ConfGen::TorsionRuleMatch& match): match(match) {}

		std::size_t getNumAtoms() const {
			return 4;
		}

		const CDPL::Chem::Atom* getAtom(std::size_t idx) const {
			if (idx >= 4)
				throw CDPL::Base::IndexError("TorsionRuleMatch: atom index out of bounds");

			return match.getAtoms()[idx];
		}

		bool containsAtom(CDPL::Chem::Atom& atom) const {
			for (std::size_t i = 0; i < 4; i++)
				if (match.getAtoms()[i] == &atom)
					return true;

			return false;
		}

		const CDPL::ConfGen::TorsionRuleMatch& match;
	};

	AtomArray createAtomArray(CDPL::ConfGen::TorsionRuleMatch& match)
	{
		return AtomArray(match);
	}
}


void CDPLPythonConfGen::exportTorsionRuleMatch()
{
    using namespace boost;
    using namespace CDPL;

   	python::scope scope = python::class_<ConfGen::TorsionRuleMatch>("TorsionRuleMatch", python::no_init)
		.def(python::init<const ConfGen::TorsionRuleMatch&>((python::arg("self"), python::arg("match")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(python::init<const ConfGen::TorsionRule&, Chem::Bond&, Chem::Atom*, Chem::Atom*, Chem::Atom*, Chem::Atom*>((python::arg("self"), python::arg("rule"), 
																														 python::arg("bond"), python::arg("atom1"), 
																														 python::arg("atom2"), python::arg("atom3"),
																														 python::arg("atom4")))
			 [python::with_custodian_and_ward<1, 3, python::with_custodian_and_ward<1, 4, python::with_custodian_and_ward<1, 5, 
			  python::with_custodian_and_ward<1, 6, python::with_custodian_and_ward<1, 7> > > > >()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionRuleMatch>())
		.def("getAtoms", &createAtomArray, python::arg("self"), 
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("getBond", &ConfGen::TorsionRuleMatch::getBond, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("getRule", &ConfGen::TorsionRuleMatch::getRule, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionRuleMatch::operator=), 
			 (python::arg("self"), python::arg("match")), python::return_self<python::with_custodian_and_ward<1, 2> >())
			.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionRuleMatch>())
		.add_property("rule", python::make_function(&ConfGen::TorsionRuleMatch::getRule, python::return_internal_reference<>()))
		.add_property("bond", python::make_function(&ConfGen::TorsionRuleMatch::getBond, python::return_internal_reference<>()))
		.add_property("atoms", python::make_function(&createAtomArray, python::with_custodian_and_ward_postcall<0, 1>()));

	python::class_<AtomArray>("AtomArray", python::no_init)
		.def("__len__", &AtomArray::getNumAtoms, python::arg("self"))
		.def("__contains__", &AtomArray::containsAtom, (python::arg("self"), python::arg("atom")))
		.def("__getitem__", &AtomArray::getAtom, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>());
}
