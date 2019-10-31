/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94TorsionParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94TorsionParameterTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94TorsionParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94TorsionParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94TorsionParameterTable, 
										 ForceField::MMFF94TorsionParameterTable::SharedPointer>("MMFF94TorsionParameterTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94TorsionParameterTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94TorsionParameterTable>())	
		.def("addEntry", &ForceField::MMFF94TorsionParameterTable::addEntry, 
			 (python::arg("self"), python::arg("tor_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom1_type"),
			  python::arg("ctr_atom2_type"), python::arg("term_atom2_type"), python::arg("tor_param1"), python::arg("tor_param2"), 
			  python::arg("tor_param3")))
		.def("removeEntry", static_cast<bool (ForceField::MMFF94TorsionParameterTable::*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int)>(
				 &ForceField::MMFF94TorsionParameterTable::removeEntry), 
			 (python::arg("self"), python::arg("tor_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom1_type"),
			  python::arg("ctr_atom2_type"), python::arg("term_atom2_type"))) 
		.def("getEntry", &ForceField::MMFF94TorsionParameterTable::getEntry, 
			 (python::arg("self"), python::arg("tor_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom1_type"),
			  python::arg("ctr_atom2_type"), python::arg("term_atom2_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94TorsionParameterTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94TorsionParameterTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94TorsionParameterTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94TorsionParameterTable::loadDefaults, (python::arg("self"), python::arg("param_set"))) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94TorsionParameterTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94TorsionParameterTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94TorsionParameterTable::set, (python::arg("table"), python::arg("param_set")))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94TorsionParameterTable::get, python::arg("param_set"),
			 python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94TorsionParameterTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94TorsionParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, double, double, double>(
				 (python::arg("self"), python::arg("tor_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom1_type"),
				  python::arg("ctr_atom2_type"), python::arg("term_atom2_type"), python::arg("tor_param1"), python::arg("tor_param2"), 
				  python::arg("tor_param3"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94TorsionParameterTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94TorsionParameterTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getTorsionTypeIndex", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionTypeIndex, python::arg("self"))
		.def("getTerminalAtom1Type", &ForceField::MMFF94TorsionParameterTable::Entry::getTerminalAtom1Type, python::arg("self"))
		.def("getCenterAtom1Type", &ForceField::MMFF94TorsionParameterTable::Entry::getCenterAtom1Type, python::arg("self"))
		.def("getCenterAtom2Type", &ForceField::MMFF94TorsionParameterTable::Entry::getCenterAtom2Type, python::arg("self"))
		.def("getTerminalAtom2Type", &ForceField::MMFF94TorsionParameterTable::Entry::getTerminalAtom2Type, python::arg("self"))
		.def("getTorsionParameter1", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter1, python::arg("self"))
		.def("getTorsionParameter2", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter2, python::arg("self"))
		.def("getTorsionParameter3", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter3, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94TorsionParameterTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::MMFF94TorsionParameterTable::Entry::operator bool, python::arg("self"))
		.add_property("torTypeIndex", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionTypeIndex)
		.add_property("termAtom1Type", &ForceField::MMFF94TorsionParameterTable::Entry::getTerminalAtom1Type)
		.add_property("ctrAtom1Type", &ForceField::MMFF94TorsionParameterTable::Entry::getCenterAtom1Type)
		.add_property("ctrAtom2Type", &ForceField::MMFF94TorsionParameterTable::Entry::getCenterAtom2Type)
		.add_property("termAtom2Type", &ForceField::MMFF94TorsionParameterTable::Entry::getTerminalAtom2Type)
		.add_property("torsionParam1", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter1)
		.add_property("torsionParam2", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter2)
		.add_property("torsionParam3", &ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter3);
}
