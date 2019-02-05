/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingRuleParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94BondStretchingRuleParameterTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94BondStretchingRuleParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94BondStretchingRuleParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94BondStretchingRuleParameterTable, 
										 ForceField::MMFF94BondStretchingRuleParameterTable::SharedPointer>("MMFF94BondStretchingRuleParameterTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94BondStretchingRuleParameterTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondStretchingRuleParameterTable>())	
		.def("addEntry", &ForceField::MMFF94BondStretchingRuleParameterTable::addEntry, 
			 (python::arg("self"), python::arg("atomic_no1"), python::arg("atomic_no2"), python::arg("force_const"), python::arg("ref_length")))
		.def("removeEntry", static_cast<bool (ForceField::MMFF94BondStretchingRuleParameterTable::*)(unsigned int, unsigned int)>(
				 &ForceField::MMFF94BondStretchingRuleParameterTable::removeEntry), 
			 (python::arg("self"), python::arg("atomic_no1"), python::arg("atomic_no2"))) 
		.def("getEntry", &ForceField::MMFF94BondStretchingRuleParameterTable::getEntry, 
			 (python::arg("self"), python::arg("atomic_no1"), python::arg("atomic_no2")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94BondStretchingRuleParameterTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94BondStretchingRuleParameterTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94BondStretchingRuleParameterTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94BondStretchingRuleParameterTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94BondStretchingRuleParameterTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94BondStretchingRuleParameterTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94BondStretchingRuleParameterTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94BondStretchingRuleParameterTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94BondStretchingRuleParameterTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94BondStretchingRuleParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, unsigned int, double, double>(
				 (python::arg("self"), python::arg("atomic_no1"), python::arg("atomic_no2"), python::arg("force_const"), python::arg("ref_length"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondStretchingRuleParameterTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94BondStretchingRuleParameterTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomicNumber1", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getAtomicNumber1, python::arg("self"))
		.def("getAtomicNumber2", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getAtomicNumber2, python::arg("self"))
		.def("getForceConstant", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getForceConstant, python::arg("self"))
		.def("getReferenceLength", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getReferenceLength, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::operator bool, python::arg("self"))
		.add_property("atomicNo1", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getAtomicNumber1)
		.add_property("atomicNo2", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getAtomicNumber2)
		.add_property("forceConstant", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getForceConstant)
		.add_property("referenceLength", &ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getReferenceLength);
}
