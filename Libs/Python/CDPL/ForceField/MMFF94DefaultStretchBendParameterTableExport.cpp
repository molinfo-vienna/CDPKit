/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94DefaultStretchBendParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94DefaultStretchBendParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94DefaultStretchBendParameterTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94DefaultStretchBendParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94DefaultStretchBendParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94DefaultStretchBendParameterTable, 
										 ForceField::MMFF94DefaultStretchBendParameterTable::SharedPointer>("MMFF94DefaultStretchBendParameterTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94DefaultStretchBendParameterTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94DefaultStretchBendParameterTable>())	
		.def("addEntry", &ForceField::MMFF94DefaultStretchBendParameterTable::addEntry, 
			 (python::arg("self"), python::arg("term_atom1_pte_row"), python::arg("ctr_atom_pte_row"),
			  python::arg("term_atom2_pte_row"), python::arg("ijk_force_const"), python::arg("kji_force_const")))
		.def("removeEntry", static_cast<bool (ForceField::MMFF94DefaultStretchBendParameterTable::*)(unsigned int, unsigned int, unsigned int)>(
				 &ForceField::MMFF94DefaultStretchBendParameterTable::removeEntry), 
			 (python::arg("self"), python::arg("term_atom1_pte_row"), python::arg("ctr_atom_pte_row"),
			  python::arg("term_atom2_pte_row"))) 
		.def("getEntry", &ForceField::MMFF94DefaultStretchBendParameterTable::getEntry, 
			 (python::arg("self"), python::arg("term_atom1_pte_row"), python::arg("ctr_atom_pte_row"),
			  python::arg("term_atom2_pte_row")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94DefaultStretchBendParameterTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94DefaultStretchBendParameterTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94DefaultStretchBendParameterTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94DefaultStretchBendParameterTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94DefaultStretchBendParameterTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94DefaultStretchBendParameterTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94DefaultStretchBendParameterTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94DefaultStretchBendParameterTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94DefaultStretchBendParameterTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94DefaultStretchBendParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, unsigned int, unsigned int, double, double>(
				 (python::arg("self"), python::arg("term_atom1_pte_row"), python::arg("ctr_atom_pte_row"),
				  python::arg("term_atom2_pte_row"), python::arg("ijk_force_const"), python::arg("kji_force_const"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94DefaultStretchBendParameterTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94DefaultStretchBendParameterTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getTerminalAtom1PTERow", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getTerminalAtom1PTERow, python::arg("self"))
		.def("getCenterAtomPTERow", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getCenterAtomPTERow, python::arg("self"))
		.def("getTerminalAtom2PTERow", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getTerminalAtom2PTERow, python::arg("self"))
		.def("getIJKForceConstant", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getIJKForceConstant, python::arg("self"))
		.def("getKJIForceConstant", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getKJIForceConstant, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::operator bool, python::arg("self"))
		.add_property("termAtom1PTERow", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getTerminalAtom1PTERow)
		.add_property("ctrAtomPTERow", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getCenterAtomPTERow)
		.add_property("termAtom2PTERow", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getTerminalAtom2PTERow)
		.add_property("ijkForceConstant", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getIJKForceConstant)
		.add_property("kjiForceConstant", &ForceField::MMFF94DefaultStretchBendParameterTable::Entry::getKJIForceConstant);
}
