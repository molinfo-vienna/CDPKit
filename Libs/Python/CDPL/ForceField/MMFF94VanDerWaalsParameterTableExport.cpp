/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94VanDerWaalsParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94VanDerWaalsParameterTable& table)
    {
		using namespace CDPL;
		using namespace ForceField;

		boost::python::list entries;

		for (MMFF94VanDerWaalsParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
    }
}


void CDPLPythonForceField::exportMMFF94VanDerWaalsParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94VanDerWaalsParameterTable, 
										 ForceField::MMFF94VanDerWaalsParameterTable::SharedPointer>("MMFF94VanDerWaalsParameterTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94VanDerWaalsParameterTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94VanDerWaalsParameterTable>())	
		.def("addEntry", &ForceField::MMFF94VanDerWaalsParameterTable::addEntry, 
			 (python::arg("self"), python::arg("atom_type"), python::arg("atom_pol"), python::arg("eff_el_num"), python::arg("fact_a"),
			  python::arg("fact_g"), python::arg("don_acc_type"))) 
		.def("removeEntry", static_cast<bool (ForceField::MMFF94VanDerWaalsParameterTable::*)(unsigned int)>(
				 &ForceField::MMFF94VanDerWaalsParameterTable::removeEntry), (python::arg("self"), python::arg("atom_type"))) 
		.def("getEntry", &ForceField::MMFF94VanDerWaalsParameterTable::getEntry, 
			 (python::arg("self"), python::arg("atom_type")), python::return_internal_reference<>()) 
		.def("clear", &ForceField::MMFF94VanDerWaalsParameterTable::clear, python::arg("self")) 
		.def("getNumEntries", &ForceField::MMFF94VanDerWaalsParameterTable::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("load", &ForceField::MMFF94VanDerWaalsParameterTable::load, (python::arg("self"), python::arg("is"))) 
		.def("loadDefaults", &ForceField::MMFF94VanDerWaalsParameterTable::loadDefaults, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94VanDerWaalsParameterTable::operator=), 
			 (python::arg("self"), python::arg("table")), python::return_self<>())
		.add_property("numEntries", &ForceField::MMFF94VanDerWaalsParameterTable::getNumEntries)
		.add_property("entries", python::make_function(&getEntries))
		.def("setExponent", &ForceField::MMFF94VanDerWaalsParameterTable::setExponent, (python::arg("self"), python::arg("value")))
		.def("setBeta", &ForceField::MMFF94VanDerWaalsParameterTable::setBeta, (python::arg("self"), python::arg("value")))
		.def("setFactorB", &ForceField::MMFF94VanDerWaalsParameterTable::setFactorB, (python::arg("self"), python::arg("value")))
		.def("setFactorDARAD", &ForceField::MMFF94VanDerWaalsParameterTable::setFactorDARAD, (python::arg("self"), python::arg("value")))
		.def("setFactorDAEPS", &ForceField::MMFF94VanDerWaalsParameterTable::setFactorDAEPS, (python::arg("self"), python::arg("value")))
		.def("getExponent", &ForceField::MMFF94VanDerWaalsParameterTable::getExponent, python::arg("self"))
		.def("getFactorB", &ForceField::MMFF94VanDerWaalsParameterTable::getFactorB, python::arg("self"))
		.def("getBeta", &ForceField::MMFF94VanDerWaalsParameterTable::getBeta, python::arg("self"))
		.def("getFactorDARAD", &ForceField::MMFF94VanDerWaalsParameterTable::getFactorDARAD, python::arg("self"))
		.def("getFactorDAEPS", &ForceField::MMFF94VanDerWaalsParameterTable::getFactorDAEPS, python::arg("self"))
		.def("set", &ForceField::MMFF94VanDerWaalsParameterTable::set, python::arg("table"))
		.staticmethod("set")
		.def("get", &ForceField::MMFF94VanDerWaalsParameterTable::get, python::return_value_policy<python::copy_const_reference>())
		.staticmethod("get")
		.add_property("exponent", &ForceField::MMFF94VanDerWaalsParameterTable::getExponent, &ForceField::MMFF94VanDerWaalsParameterTable::setExponent) 
		.add_property("beta", &ForceField::MMFF94VanDerWaalsParameterTable::getBeta, &ForceField::MMFF94VanDerWaalsParameterTable::setBeta) 
		.add_property("factorB", &ForceField::MMFF94VanDerWaalsParameterTable::getFactorB, &ForceField::MMFF94VanDerWaalsParameterTable::setFactorB) 
		.add_property("factorDARAD", &ForceField::MMFF94VanDerWaalsParameterTable::getFactorDARAD, &ForceField::MMFF94VanDerWaalsParameterTable::setFactorDARAD) 
		.add_property("factorDAEPS", &ForceField::MMFF94VanDerWaalsParameterTable::getFactorDAEPS, &ForceField::MMFF94VanDerWaalsParameterTable::setFactorDAEPS);

    python::class_<ForceField::MMFF94VanDerWaalsParameterTable::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94VanDerWaalsParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<unsigned int, double, double, double, double, ForceField::MMFF94VanDerWaalsInteraction::HDonorAcceptorType>(
				 (python::arg("self"), python::arg("atom_type"), python::arg("atom_pol"), python::arg("eff_el_num"), python::arg("fact_a"),
				  python::arg("fact_g"), python::arg("don_acc_type"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94VanDerWaalsParameterTable::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94VanDerWaalsParameterTable::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAtomType", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getAtomType, python::arg("self"))
		.def("getAtomicPolarizability", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getAtomicPolarizability, python::arg("self"))
		.def("getEffectiveElectronNumber", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getEffectiveElectronNumber, python::arg("self"))
		.def("getFactorA", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getFactorA, python::arg("self"))
		.def("getFactorG", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getFactorG, python::arg("self"))
		.def("getHDonorAcceptorType", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getHDonorAcceptorType, python::arg("self"))
		.def("__nonzero__", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::operator bool, python::arg("self"))
		.def("__bool__", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::operator bool, python::arg("self"))
		.add_property("atomType", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getAtomType)
		.add_property("atomicPolarizability", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getAtomicPolarizability)
		.add_property("effElectronNumber", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getEffectiveElectronNumber)
		.add_property("factorA", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getFactorA)
		.add_property("factorG", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getFactorG)
		.add_property("hDonorAcceptorType", &ForceField::MMFF94VanDerWaalsParameterTable::Entry::getHDonorAcceptorType);
}
