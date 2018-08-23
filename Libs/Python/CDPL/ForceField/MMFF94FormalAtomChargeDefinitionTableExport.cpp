/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94FormalAtomChargeDefinitionTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94FormalAtomChargeDefinitionTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94FormalAtomChargeDefinitionTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94FormalAtomChargeDefinitionTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94FormalAtomChargeDefinitionTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94FormalAtomChargeDefinitionTable, 
										 ForceField::MMFF94FormalAtomChargeDefinitionTable::SharedPointer>("MMFF94FormalAtomChargeDefinitionTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94FormalAtomChargeDefinitionTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94FormalAtomChargeDefinitionTable>())	
		.def("addEntry", &ForceField::MMFF94FormalAtomChargeDefinitionTable::addEntry, 
			 (python::arg("self"), python::arg("atom_type"), python::arg("ass_mode"), python::arg("charge"), python::arg("type_list")))
		.def("removeEntry", static_cast<bool (ForceField::MMFF94FormalAtomChargeDefinitionTable::*)(const std::string&)>(
				 &ForceField::MMFF94FormalAtomChargeDefinitionTable::removeEntry), (python::arg("self"), python::arg("atom_type"))) 
		.def("getEntry", &ForceField::MMFF94FormalAtomChargeDefinitionTable::getEntry, 
			 (python::arg("self"), python::arg("atom_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94FormalAtomChargeDefinitionTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94FormalAtomChargeDefinitionTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94FormalAtomChargeDefinitionTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94FormalAtomChargeDefinitionTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94FormalAtomChargeDefinitionTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94FormalAtomChargeDefinitionTable::getNumEntries)
		.add_property("entries", &getEntries)
		.def("set", &ForceField::MMFF94FormalAtomChargeDefinitionTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94FormalAtomChargeDefinitionTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, std::size_t, double, const std::string&>(
				 (python::arg("self"), python::arg("atom_type"), python::arg("ass_mode"), python::arg("charge"), python::arg("type_list"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomType", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getAtomType, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("getAssignmentMode", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getAssignmentMode, python::arg("self"))
		.def("getFormalCharge", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getFormalCharge, python::arg("self"))
		.def("getAtomTypeList", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getAtomTypeList, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("__nonzero__", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::operator bool, python::arg("self"))
		.add_property("atomType", python::make_function(&ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getAtomType, 
														python::return_value_policy<python::copy_const_reference>()))
		.add_property("assignmentMode", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getAssignmentMode)
		.add_property("formalCharge", &ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getFormalCharge)
		.add_property("atomTypeList", python::make_function(&ForceField::MMFF94FormalAtomChargeDefinitionTable::Entry::getAtomTypeList, 
															python::return_value_policy<python::copy_const_reference>()));
}
