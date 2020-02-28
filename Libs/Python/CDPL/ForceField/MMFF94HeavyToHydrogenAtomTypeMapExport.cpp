/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94HeavyToHydrogenAtomTypeMapExport.cpp 
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

#include "CDPL/ForceField/MMFF94HeavyToHydrogenAtomTypeMap.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94HeavyToHydrogenAtomTypeMap& map)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94HeavyToHydrogenAtomTypeMap::ConstEntryIterator it = map.getEntriesBegin(), end = map.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94HeavyToHydrogenAtomTypeMap()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94HeavyToHydrogenAtomTypeMap, 
										 ForceField::MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer>("MMFF94HeavyToHydrogenAtomTypeMap", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94HeavyToHydrogenAtomTypeMap&>((python::arg("self"), python::arg("map"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94HeavyToHydrogenAtomTypeMap>())	
		.def("addEntry", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::addEntry, 
			 (python::arg("self"), python::arg("parent_type"), python::arg("h_atom_type"))) 
		.def("removeEntry", static_cast<bool (ForceField::MMFF94HeavyToHydrogenAtomTypeMap::*)(const std::string&)>(
				 &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::removeEntry), (python::arg("self"), python::arg("parent_type"))) 
		.def("getEntry", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::getEntry, 
			 (python::arg("self"), python::arg("parent_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94HeavyToHydrogenAtomTypeMap::operator=), 
			 (python::arg("self"), python::arg("map")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::set, python::arg("map"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94HeavyToHydrogenAtomTypeMap::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94HeavyToHydrogenAtomTypeMap::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, const std::string&>(
				 (python::arg("self"), python::arg("parent_type"), python::arg("h_atom_type"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94HeavyToHydrogenAtomTypeMap::Entry>())	
		.def_readonly("parentAtomType", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::Entry::first)
		.def_readonly("hydrogenAtomType", &ForceField::MMFF94HeavyToHydrogenAtomTypeMap::Entry::second);
}
