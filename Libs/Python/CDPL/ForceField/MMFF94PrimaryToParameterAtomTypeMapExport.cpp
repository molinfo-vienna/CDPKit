/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94PrimaryToParameterAtomTypeMapExport.cpp 
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

#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94PrimaryToParameterAtomTypeMap& map)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94PrimaryToParameterAtomTypeMap::ConstEntryIterator it = map.getEntriesBegin(), end = map.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }

	boost::python::object getParameterAtomTypes(const CDPL::ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry& entry)
    {
		using namespace CDPL;
		using namespace ForceField;

		if (!entry)
			return boost::python::object();

		boost::python::list types;

		for (std::size_t i = 0; i < MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES; i++)
			types.append(entry.getParameterTypes()[i]);

		return types;
    }

	void addEntry(CDPL::ForceField::MMFF94PrimaryToParameterAtomTypeMap& map, unsigned int atom_type, boost::python::object param_types)
	{
		using namespace CDPL;
		using namespace ForceField;
		using namespace boost;

		unsigned int param_type_array[MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES] = { 0 };

		for (int i = 0; i < len(param_types) && i < int(MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES); i++)
			param_type_array[i] = python::extract<unsigned int>(param_types[i]);

		map.addEntry(atom_type, param_type_array);
	}

	CDPL::ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry* makeEntry(unsigned int atom_type, boost::python::object param_types)
	{
		using namespace CDPL;
		using namespace ForceField;
		using namespace boost;

		unsigned int param_type_array[MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES] = { 0 };

		for (int i = 0; i < len(param_types) && i < int(MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES); i++)
			param_type_array[i] = python::extract<unsigned int>(param_types[i]);

		return new MMFF94PrimaryToParameterAtomTypeMap::Entry(atom_type, param_type_array);
	}
}


void CDPLPythonForceField::exportMMFF94PrimaryToParameterAtomTypeMap()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94PrimaryToParameterAtomTypeMap, 
										 ForceField::MMFF94PrimaryToParameterAtomTypeMap::SharedPointer>("MMFF94PrimaryToParameterAtomTypeMap", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94PrimaryToParameterAtomTypeMap&>((python::arg("self"), python::arg("map"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94PrimaryToParameterAtomTypeMap>())	
		.def("addEntry", &addEntry, (python::arg("self"), python::arg("atom_type"), python::arg("param_types"))) 
		.def("removeEntry", static_cast<bool (ForceField::MMFF94PrimaryToParameterAtomTypeMap::*)(unsigned int)>(
				 &ForceField::MMFF94PrimaryToParameterAtomTypeMap::removeEntry), (python::arg("self"), python::arg("atom_type"))) 
		.def("getEntry", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::getEntry, 
			 (python::arg("self"), python::arg("atom_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94PrimaryToParameterAtomTypeMap::operator=), 
			 (python::arg("self"), python::arg("map")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::getNumEntries)
		.add_property("entries", &getEntries)
		.def("set", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::set, python::arg("map"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry&>((python::arg("self"), python::arg("entry"))))
		.def("__init__", python::make_constructor(&makeEntry, python::default_call_policies(), 
												  (python::arg("atom_type"), python::arg("param_types"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomType", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::getAtomType, python::arg("self"))
		.def("getParameterAtomTypes", &getParameterAtomTypes, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::operator bool, python::arg("self"))
		.add_property("atomType", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::getAtomType)
		.add_property("paramAtomTypes", &getParameterAtomTypes)
		.def_readonly("NUM_TYPES", &ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES);
}
