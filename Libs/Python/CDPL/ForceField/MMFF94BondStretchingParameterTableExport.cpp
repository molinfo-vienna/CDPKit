/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94BondStretchingParameterTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94BondStretchingParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94BondStretchingParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94BondStretchingParameterTable, 
										 ForceField::MMFF94BondStretchingParameterTable::SharedPointer>("MMFF94BondStretchingParameterTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94BondStretchingParameterTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondStretchingParameterTable>())	
		.def("addEntry", &ForceField::MMFF94BondStretchingParameterTable::addEntry, 
			 (python::arg("self"), python::arg("bond_type_idx"), python::arg("atom1_type"), python::arg("atom2_type"), 
			  python::arg("force_const"), python::arg("ref_length")))
		.def("removeEntry", static_cast<bool (ForceField::MMFF94BondStretchingParameterTable::*)(unsigned int, unsigned int, unsigned int)>(
				 &ForceField::MMFF94BondStretchingParameterTable::removeEntry), 
			 (python::arg("self"), python::arg("bond_type_idx"), python::arg("atom1_type"), python::arg("atom2_type"))) 
		.def("getEntry", &ForceField::MMFF94BondStretchingParameterTable::getEntry, 
			 (python::arg("self"), python::arg("bond_type_idx"), python::arg("atom1_type"), python::arg("atom2_type")),
			 python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94BondStretchingParameterTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94BondStretchingParameterTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94BondStretchingParameterTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94BondStretchingParameterTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94BondStretchingParameterTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94BondStretchingParameterTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94BondStretchingParameterTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94BondStretchingParameterTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94BondStretchingParameterTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94BondStretchingParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, unsigned int, unsigned int, double, double>(
				 (python::arg("self"), python::arg("bond_type_idx"), python::arg("atom1_type"), python::arg("atom2_type"), 
				  python::arg("force_const"), python::arg("ref_length"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondStretchingParameterTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94BondStretchingParameterTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getBondTypeIndex", &ForceField::MMFF94BondStretchingParameterTable::Entry::getBondTypeIndex, python::arg("self"))
		.def("getAtom1Type", &ForceField::MMFF94BondStretchingParameterTable::Entry::getAtom1Type, python::arg("self"))
		.def("getAtom2Type", &ForceField::MMFF94BondStretchingParameterTable::Entry::getAtom2Type, python::arg("self"))
		.def("getForceConstant", &ForceField::MMFF94BondStretchingParameterTable::Entry::getForceConstant, python::arg("self"))
		.def("getReferenceLength", &ForceField::MMFF94BondStretchingParameterTable::Entry::getReferenceLength, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94BondStretchingParameterTable::Entry::operator bool, python::arg("self"))
		.add_property("bondTypeIndex", &ForceField::MMFF94BondStretchingParameterTable::Entry::getBondTypeIndex)
		.add_property("atom1Type", &ForceField::MMFF94BondStretchingParameterTable::Entry::getAtom1Type)
		.add_property("atom2Type", &ForceField::MMFF94BondStretchingParameterTable::Entry::getAtom2Type)
		.add_property("forceConstant", &ForceField::MMFF94BondStretchingParameterTable::Entry::getForceConstant)
		.add_property("referenceLength", &ForceField::MMFF94BondStretchingParameterTable::Entry::getReferenceLength);
}
