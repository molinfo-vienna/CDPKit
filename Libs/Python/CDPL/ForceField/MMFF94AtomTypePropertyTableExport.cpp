/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AtomTypePropertyTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94AtomTypePropertyTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94AtomTypePropertyTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94AtomTypePropertyTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94AtomTypePropertyTable, 
										 ForceField::MMFF94AtomTypePropertyTable::SharedPointer>("MMFF94AtomTypePropertyTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94AtomTypePropertyTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AtomTypePropertyTable>())	
		.def("addEntry", &ForceField::MMFF94AtomTypePropertyTable::addEntry, 
			 (python::arg("self"), python::arg("atom_type"), python::arg("atomic_no"), python::arg("num_nbrs"), python::arg("valence"), 
			  python::arg("has_pi_lp"), python::arg("mltb_desig"), python::arg("is_arom"), python::arg("lin_bnd_ang"), python::arg("has_mb_or_sb"))) 
		.def("removeEntry", static_cast<bool (ForceField::MMFF94AtomTypePropertyTable::*)(unsigned int)>(
				 &ForceField::MMFF94AtomTypePropertyTable::removeEntry), (python::arg("self"), python::arg("atom_type"))) 
		.def("getEntry", &ForceField::MMFF94AtomTypePropertyTable::getEntry, 
			 (python::arg("self"), python::arg("atom_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94AtomTypePropertyTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94AtomTypePropertyTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94AtomTypePropertyTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94AtomTypePropertyTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AtomTypePropertyTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94AtomTypePropertyTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::MMFF94AtomTypePropertyTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94AtomTypePropertyTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::MMFF94AtomTypePropertyTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94AtomTypePropertyTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, unsigned int, std::size_t, std::size_t, bool, unsigned int, bool, bool, bool>(
				 (python::arg("self"), python::arg("atom_type"), python::arg("atomic_no"), python::arg("num_nbrs"), python::arg("valence"), 
				  python::arg("has_pi_lp"), python::arg("mltb_desig"), python::arg("is_arom"), python::arg("lin_bnd_ang"), python::arg("has_mb_or_sb"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AtomTypePropertyTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AtomTypePropertyTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomType", &ForceField::MMFF94AtomTypePropertyTable::Entry::getAtomType, python::arg("self"))
		.def("getAtomicNumber", &ForceField::MMFF94AtomTypePropertyTable::Entry::getAtomicNumber, python::arg("self"))
		.def("getNumNeighbors", &ForceField::MMFF94AtomTypePropertyTable::Entry::getNumNeighbors, python::arg("self"))
		.def("getValence", &ForceField::MMFF94AtomTypePropertyTable::Entry::getValence, python::arg("self"))
		.def("hasPiLonePair", &ForceField::MMFF94AtomTypePropertyTable::Entry::hasPiLonePair, python::arg("self"))
		.def("getMultiBondDesignator", &ForceField::MMFF94AtomTypePropertyTable::Entry::getMultiBondDesignator, python::arg("self"))
		.def("isAromaticAtomType", &ForceField::MMFF94AtomTypePropertyTable::Entry::isAromaticAtomType, python::arg("self"))
		.def("formsLinearBondAngle", &ForceField::MMFF94AtomTypePropertyTable::Entry::formsLinearBondAngle, python::arg("self"))
		.def("formsMultiOrSingleBonds", &ForceField::MMFF94AtomTypePropertyTable::Entry::formsMultiOrSingleBonds, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94AtomTypePropertyTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::MMFF94AtomTypePropertyTable::Entry::operator bool, python::arg("self"))
		.add_property("atomType", &ForceField::MMFF94AtomTypePropertyTable::Entry::getAtomType)
		.add_property("atomicNumber", &ForceField::MMFF94AtomTypePropertyTable::Entry::getAtomicNumber)
		.add_property("numNeighbors", &ForceField::MMFF94AtomTypePropertyTable::Entry::getNumNeighbors)
		.add_property("valence", &ForceField::MMFF94AtomTypePropertyTable::Entry::getValence)
		.add_property("piLonePair", &ForceField::MMFF94AtomTypePropertyTable::Entry::hasPiLonePair)
		.add_property("multiBondDesignator", &ForceField::MMFF94AtomTypePropertyTable::Entry::getMultiBondDesignator)
		.add_property("aromAtomType", &ForceField::MMFF94AtomTypePropertyTable::Entry::isAromaticAtomType)
		.add_property("linearBondAngle", &ForceField::MMFF94AtomTypePropertyTable::Entry::formsLinearBondAngle)
		.add_property("multiOrSingleBonds", &ForceField::MMFF94AtomTypePropertyTable::Entry::formsMultiOrSingleBonds);
}
