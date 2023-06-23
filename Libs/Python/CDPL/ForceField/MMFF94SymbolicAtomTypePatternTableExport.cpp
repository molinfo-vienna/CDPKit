/* 
 * MMFF94SymbolicAtomTypePatternTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94SymbolicAtomTypePatternTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94SymbolicAtomTypePatternTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94SymbolicAtomTypePatternTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94SymbolicAtomTypePatternTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94SymbolicAtomTypePatternTable, 
										 ForceField::MMFF94SymbolicAtomTypePatternTable::SharedPointer>("MMFF94SymbolicAtomTypePatternTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94SymbolicAtomTypePatternTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94SymbolicAtomTypePatternTable>())	
		.def("addEntry", &ForceField::MMFF94SymbolicAtomTypePatternTable::addEntry, 
			 (python::arg("self"), python::arg("ptn"), python::arg("sym_type"), python::arg("fallback"))) 
		.def("removeEntry", static_cast<void (ForceField::MMFF94SymbolicAtomTypePatternTable::*)(std::size_t)>(
				 &ForceField::MMFF94SymbolicAtomTypePatternTable::removeEntry), (python::arg("self"), python::arg("idx"))) 
		.def("getEntry", &ForceField::MMFF94SymbolicAtomTypePatternTable::getEntry, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94SymbolicAtomTypePatternTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94SymbolicAtomTypePatternTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94SymbolicAtomTypePatternTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94SymbolicAtomTypePatternTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94SymbolicAtomTypePatternTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94SymbolicAtomTypePatternTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94SymbolicAtomTypePatternTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94SymbolicAtomTypePatternTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94SymbolicAtomTypePatternTable::Entry>("Entry", python::no_init)
		.def(python::init<const ForceField::MMFF94SymbolicAtomTypePatternTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const Chem::MolecularGraph::SharedPointer&, const std::string&, bool>(
				 (python::arg("self"), python::arg("ptn"), python::arg("sym_type"), python::arg("fallback"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94SymbolicAtomTypePatternTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getPattern", &ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::getPattern, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("getSymbolicType", &ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::getSymbolicType, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("isFallbackType", &ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::isFallbackType, python::arg("self"))
		.add_property("symbolicType", python::make_function(&ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::getSymbolicType,
															python::return_value_policy<python::copy_const_reference>()))
		.add_property("pattern", python::make_function(&ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::getPattern,
													   python::return_value_policy<python::copy_const_reference>()))
		.add_property("isFallbackType", &ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::isFallbackType);
}
