/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedTautomerizationRuleExport.cpp 
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


#include <vector>

#include <boost/python.hpp>

#include "CDPL/Chem/PatternBasedTautomerizationRule.hpp"

#include "ClassExports.hpp"


namespace
{

    void addTransformationPattern(CDPL::Chem::PatternBasedTautomerizationRule& rule, const CDPL::Chem::MolecularGraph::SharedPointer& pattern, PyObject* iterable)
    {
		using namespace CDPL;
		using namespace Chem;
		using namespace boost;

		PyObject *iter = PyObject_GetIter(iterable);

		if (!iter) {
			PyErr_SetString(PyExc_TypeError, "PatternBasedTautomerizationRule: iterable object expected as 2nd argument");

			python::throw_error_already_set();
		}
	
		python::handle<> iter_handle(python::borrowed(iter)); Py_DECREF(iter);
		PyObject *item;
		std::vector<PatternBasedTautomerizationRule::BondOrderChange> order_chgs;

		while ((item = PyIter_Next(iter))) {
			python::handle<> item_handle(python::borrowed(item)); Py_DECREF(item);

			if (!python::extract<PatternBasedTautomerizationRule::BondOrderChange>(item).check()) {
				PyErr_SetString(PyExc_TypeError, "PatternBasedTautomerizationRule: BondOrderChange sequence expected as 2nd argument");

				python::throw_error_already_set();
			}

			order_chgs.push_back(python::extract<PatternBasedTautomerizationRule::BondOrderChange>(item)());
		}

		rule.addTransformationPattern(pattern, order_chgs.begin(), order_chgs.end());
    }
}


void CDPLPythonChem::exportPatternBasedTautomerizationRule()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::PatternBasedTautomerizationRule, Chem::PatternBasedTautomerizationRule::SharedPointer, 
				   python::bases<Chem::TautomerizationRule>, boost::noncopyable> cl("PatternBasedTautomerizationRule", python::no_init);

	python::scope scope = cl;
 
	python::class_<Chem::PatternBasedTautomerizationRule::BondOrderChange, boost::noncopyable>("BondOrderChange", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::PatternBasedTautomerizationRule::BondOrderChange&>((python::arg("self"), python::arg("bond_chg"))))
		.def("assign", &Chem::PatternBasedTautomerizationRule::BondOrderChange::operator=, 
			 (python::arg("self"), python::arg("bond_chg")), python::return_self<>())
		.add_property("atom1ID", &Chem::PatternBasedTautomerizationRule::BondOrderChange::atom1ID)
		.add_property("atom2ID", &Chem::PatternBasedTautomerizationRule::BondOrderChange::atom2ID)
		.add_property("orderChange", &Chem::PatternBasedTautomerizationRule::BondOrderChange::orderChange);
 
    cl
		.def(python::init<unsigned int>((python::arg("self"), python::arg("id"))))
		.def(python::init<const Chem::PatternBasedTautomerizationRule&>((python::arg("self"), python::arg("rule"))))
		.def("setCustomSetupFunction", &Chem::PatternBasedTautomerizationRule::setCustomSetupFunction, (python::arg("self"), python::arg("func")))
		.def("addTransformationPattern", &addTransformationPattern, (python::arg("self"), python::arg("pattern"), python::arg("bond_chgs")))
		.def("addExcludePattern", &Chem::PatternBasedTautomerizationRule::addExcludePattern, (python::arg("self"), python::arg("pattern")))
		.def("addExcludePatterns", &Chem::PatternBasedTautomerizationRule::addExcludePatterns, (python::arg("self"), python::arg("rule")))
		.def("clearExcludePatterns", &Chem::PatternBasedTautomerizationRule::clearExcludePatterns, python::arg("self"))
		.def("assign", &Chem::PatternBasedTautomerizationRule::operator=, 
			 (python::arg("self"), python::arg("rule")), python::return_self<>());
}
