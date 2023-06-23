/* 
 * UFFAtomTypePropertyTableExport.cpp 
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

#include "CDPL/ForceField/UFFAtomTypePropertyTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::UFFAtomTypePropertyTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (UFFAtomTypePropertyTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportUFFAtomTypePropertyTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::UFFAtomTypePropertyTable, 
										 ForceField::UFFAtomTypePropertyTable::SharedPointer>("UFFAtomTypePropertyTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::UFFAtomTypePropertyTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::UFFAtomTypePropertyTable>())	
		.def("addEntry", &ForceField::UFFAtomTypePropertyTable::addEntry, 
			 (python::arg("self"), python::arg("atom_type"), python::arg("atom_type_sym"), python::arg("atomic_no"), python::arg("bond_rad"), 
			  python::arg("bond_ang"), python::arg("vdw_dist"), python::arg("vdw_energy"), python::arg("vdw_scale"), python::arg("eff_charge"))) 
		.def("removeEntry", static_cast<bool (ForceField::UFFAtomTypePropertyTable::*)(unsigned int)>(
				 &ForceField::UFFAtomTypePropertyTable::removeEntry), (python::arg("self"), python::arg("atom_type"))) 
		.def("getEntry", &ForceField::UFFAtomTypePropertyTable::getEntry, 
			 (python::arg("self"), python::arg("atom_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::UFFAtomTypePropertyTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::UFFAtomTypePropertyTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("loadDefaults", &ForceField::UFFAtomTypePropertyTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::UFFAtomTypePropertyTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::UFFAtomTypePropertyTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("set", &ForceField::UFFAtomTypePropertyTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::UFFAtomTypePropertyTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get");

    python::class_<ForceField::UFFAtomTypePropertyTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::UFFAtomTypePropertyTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, const std::string&, unsigned int, double, double, double, double, double, double>(
				 (python::arg("self"), python::arg("atom_type"), python::arg("atom_type_sym"), python::arg("atomic_no"), python::arg("bond_rad"), 
				  python::arg("bond_ang"), python::arg("vdw_dist"), python::arg("vdw_energy"), python::arg("vdw_scale"), python::arg("eff_charge"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::UFFAtomTypePropertyTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::UFFAtomTypePropertyTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomType", &ForceField::UFFAtomTypePropertyTable::Entry::getAtomType, python::arg("self"))
		.def("getAtomicNumber", &ForceField::UFFAtomTypePropertyTable::Entry::getAtomicNumber, python::arg("self"))
		.def("getAtomTypeSymbol", &ForceField::UFFAtomTypePropertyTable::Entry::getAtomTypeSymbol, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getBondRadius", &ForceField::UFFAtomTypePropertyTable::Entry::getBondRadius, python::arg("self"))
		.def("getBondAngle", &ForceField::UFFAtomTypePropertyTable::Entry::getBondAngle, python::arg("self"))
		.def("getVdWDistance", &ForceField::UFFAtomTypePropertyTable::Entry::getVdWDistance, python::arg("self"))
		.def("getVdWEnergy", &ForceField::UFFAtomTypePropertyTable::Entry::getVdWEnergy, python::arg("self"))
		.def("getVdWScale", &ForceField::UFFAtomTypePropertyTable::Entry::getVdWScale, python::arg("self"))
		.def("getEffectiveCharge", &ForceField::UFFAtomTypePropertyTable::Entry::getEffectiveCharge, python::arg("self"))
		.def("__nonzero__", &ForceField::UFFAtomTypePropertyTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::UFFAtomTypePropertyTable::Entry::operator bool, python::arg("self"))
		.add_property("atomType", &ForceField::UFFAtomTypePropertyTable::Entry::getAtomType)
		.add_property("atomicNumber", &ForceField::UFFAtomTypePropertyTable::Entry::getAtomicNumber)
		.add_property("atomTypeSymbol", python::make_function(&ForceField::UFFAtomTypePropertyTable::Entry::getAtomTypeSymbol, 
															  python::return_value_policy<python::copy_const_reference>()))
		.add_property("bondRadius", &ForceField::UFFAtomTypePropertyTable::Entry::getBondRadius)
		.add_property("bondAngle", &ForceField::UFFAtomTypePropertyTable::Entry::getBondAngle)
		.add_property("vdwDistance", &ForceField::UFFAtomTypePropertyTable::Entry::getVdWDistance)
		.add_property("vdwEnergy", &ForceField::UFFAtomTypePropertyTable::Entry::getVdWEnergy)
		.add_property("vdwScale", &ForceField::UFFAtomTypePropertyTable::Entry::getVdWScale)
		.add_property("effectiveCharge", &ForceField::UFFAtomTypePropertyTable::Entry::getEffectiveCharge);
}
