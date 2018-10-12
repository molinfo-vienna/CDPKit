/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AromaticAtomTypeDefinitionTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94AromaticAtomTypeDefinitionTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94AromaticAtomTypeDefinitionTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94AromaticAtomTypeDefinitionTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94AromaticAtomTypeDefinitionTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94AromaticAtomTypeDefinitionTable, 
										 ForceField::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer>("MMFF94AromaticAtomTypeDefinitionTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94AromaticAtomTypeDefinitionTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AromaticAtomTypeDefinitionTable>())	
		.def("addEntry", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::addEntry, 
			 (python::arg("self"), python::arg("old_type"), python::arg("aro_type"), python::arg("atomic_no"), 
			  python::arg("ring_size"), python::arg("het_atom_dist"), python::arg("im_cation"), python::arg("n5_anion"))) 
		.def("removeEntry", static_cast<void (ForceField::MMFF94AromaticAtomTypeDefinitionTable::*)(std::size_t)>(
				 &ForceField::MMFF94AromaticAtomTypeDefinitionTable::removeEntry), (python::arg("self"), python::arg("idx"))) 
		.def("getEntry", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::getEntry, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AromaticAtomTypeDefinitionTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry>("Entry", python::no_init)
		.def(python::init<const ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, const std::string&, unsigned int, std::size_t, std::size_t, bool, bool>(
				 (python::arg("self"), python::arg("old_type"), python::arg("aro_type"), python::arg("atomic_no"), 
				  python::arg("ring_size"), python::arg("het_atom_dist"), python::arg("im_cation"), python::arg("n5_anion"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getOldAtomType", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getOldAtomType, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getAromAtomType", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAromAtomType, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getAtomicNumber", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAtomicNumber, python::arg("self"))
		.def("getRingSize", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getRingSize, python::arg("self"))
		.def("getHeteroAtomDistance", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getHeteroAtomDistance, python::arg("self"))
		.def("isImidazoliumCation", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::isImidazoliumCation, python::arg("self"))
		.def("isN5RingAnion", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::isN5RingAnion, python::arg("self"))
		.add_property("oldAtomType", python::make_function(&ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getOldAtomType,
															python::return_value_policy<python::copy_const_reference>()))
		.add_property("aromAtomType", python::make_function(&ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAromAtomType,
													   python::return_value_policy<python::copy_const_reference>()))
		.add_property("atomicNumber", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAtomicNumber)
		.add_property("ringSize", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getRingSize)
		.add_property("heteroAtomDistance", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getHeteroAtomDistance)
		.add_property("imidazoliumCation", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::isImidazoliumCation)
		.add_property("n5RingAnion", &ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::isN5RingAnion);
}
