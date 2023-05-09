/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94PartialBondChargeIncrementTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94PartialBondChargeIncrementTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94PartialBondChargeIncrementTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94PartialBondChargeIncrementTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94PartialBondChargeIncrementTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94PartialBondChargeIncrementTable, 
										 ForceField::MMFF94PartialBondChargeIncrementTable::SharedPointer>("MMFF94PartialBondChargeIncrementTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94PartialBondChargeIncrementTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94PartialBondChargeIncrementTable>())	
		.def("addEntry", &ForceField::MMFF94PartialBondChargeIncrementTable::addEntry, 
			 (python::arg("self"), python::arg("atom_type"), python::arg("part_bond_chg_inc"), python::arg("form_chg_adj_factor")))
		.def("removeEntry", static_cast<bool (ForceField::MMFF94PartialBondChargeIncrementTable::*)(unsigned int)>(
				 &ForceField::MMFF94PartialBondChargeIncrementTable::removeEntry), (python::arg("self"), python::arg("atom_type"))) 
		.def("getEntry", &ForceField::MMFF94PartialBondChargeIncrementTable::getEntry, 
			 (python::arg("self"), python::arg("atom_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94PartialBondChargeIncrementTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94PartialBondChargeIncrementTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94PartialBondChargeIncrementTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94PartialBondChargeIncrementTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94PartialBondChargeIncrementTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94PartialBondChargeIncrementTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94PartialBondChargeIncrementTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94PartialBondChargeIncrementTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94PartialBondChargeIncrementTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94PartialBondChargeIncrementTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, double, double>(
				 (python::arg("self"), python::arg("atom_type"), python::arg("part_bond_chg_inc"), python::arg("form_chg_adj_factor"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94PartialBondChargeIncrementTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94PartialBondChargeIncrementTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomType", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::getAtomType, python::arg("self"))
		.def("getPartialChargeIncrement", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::getPartialChargeIncrement, python::arg("self"))
		.def("getFormalChargeAdjustmentFactor", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::getFormalChargeAdjustmentFactor, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::operator bool, python::arg("self"))
		.add_property("atomType", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::getAtomType)
		.add_property("partialChargeIncrement", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::getPartialChargeIncrement)
		.add_property("formalChargeAdjustmentFactor", &ForceField::MMFF94PartialBondChargeIncrementTable::Entry::getFormalChargeAdjustmentFactor);
}
