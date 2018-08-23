/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94SymbolicToNumericAtomTypeMapExport.cpp 
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

#include "CDPL/ForceField/MMFF94SymbolicToNumericAtomTypeMap.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94SymbolicToNumericAtomTypeMap& map)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94SymbolicToNumericAtomTypeMap::ConstEntryIterator it = map.getEntriesBegin(), end = map.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94SymbolicToNumericAtomTypeMap()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94SymbolicToNumericAtomTypeMap, 
										 ForceField::MMFF94SymbolicToNumericAtomTypeMap::SharedPointer>("MMFF94SymbolicToNumericAtomTypeMap", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94SymbolicToNumericAtomTypeMap&>((python::arg("self"), python::arg("map"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94SymbolicToNumericAtomTypeMap>())	
		.def("addEntry", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::addEntry, 
			 (python::arg("self"), python::arg("sym_type"), python::arg("num_type"))) 
		.def("removeEntry", static_cast<bool (ForceField::MMFF94SymbolicToNumericAtomTypeMap::*)(const std::string&)>(
				 &ForceField::MMFF94SymbolicToNumericAtomTypeMap::removeEntry), (python::arg("self"), python::arg("sym_type"))) 
		.def("getEntry", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::getEntry, 
			 (python::arg("self"), python::arg("sym_type"))) 
		.def("clear", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94SymbolicToNumericAtomTypeMap::operator=), 
			 (python::arg("self"), python::arg("map")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::getNumEntries)
		.add_property("entries", &getEntries)
		.def("set", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::set, python::arg("map"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94SymbolicToNumericAtomTypeMap::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94SymbolicToNumericAtomTypeMap::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, unsigned int>(
				 (python::arg("self"), python::arg("sym_type"), python::arg("num_type"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94SymbolicToNumericAtomTypeMap::Entry>())	
		.def_readonly("symbolicType", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::Entry::first)
		.def_readonly("numericType", &ForceField::MMFF94SymbolicToNumericAtomTypeMap::Entry::second);
}
