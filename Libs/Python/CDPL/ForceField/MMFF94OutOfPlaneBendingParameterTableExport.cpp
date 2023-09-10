/* 
 * MMFF94OutOfPlaneBendingParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94OutOfPlaneBendingParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94OutOfPlaneBendingParameterTable& table)
    {
        using namespace CDPL;
        using namespace ForceField;

        boost::python::list entries;

        for (MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
            entries.append(boost::ref(*it));

        return entries;
    }
}


void CDPLPythonForceField::exportMMFF94OutOfPlaneBendingParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94OutOfPlaneBendingParameterTable, 
                                         ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer>("MMFF94OutOfPlaneBendingParameterTable", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94OutOfPlaneBendingParameterTable&>((python::arg("self"), python::arg("table"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94OutOfPlaneBendingParameterTable>())    
        .def("addEntry", &ForceField::MMFF94OutOfPlaneBendingParameterTable::addEntry, 
             (python::arg("self"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"), python::arg("oop_atom_type"), python::arg("force_const")))
        .def("removeEntry", static_cast<bool (ForceField::MMFF94OutOfPlaneBendingParameterTable::*)(unsigned int, unsigned int, unsigned int, unsigned int)>(
                 &ForceField::MMFF94OutOfPlaneBendingParameterTable::removeEntry), 
             (python::arg("self"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"), python::arg("oop_atom_type"))) 
        .def("getEntry", &ForceField::MMFF94OutOfPlaneBendingParameterTable::getEntry, 
             (python::arg("self"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"), python::arg("oop_atom_type")), python::return_internal_reference<>()) 
        .def("clear", &ForceField::MMFF94OutOfPlaneBendingParameterTable::clear, python::arg("self")) 
        .def("getNumEntries", &ForceField::MMFF94OutOfPlaneBendingParameterTable::getNumEntries, python::arg("self")) 
        .def("getEntries", &getEntries, python::arg("self")) 
        .def("load", &ForceField::MMFF94OutOfPlaneBendingParameterTable::load, (python::arg("self"), python::arg("is"))) 
        .def("loadDefaults", &ForceField::MMFF94OutOfPlaneBendingParameterTable::loadDefaults, (python::arg("self"), python::arg("param_set"))) 
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94OutOfPlaneBendingParameterTable>(), 
             (python::arg("self"), python::arg("table")), python::return_self<>())
        .add_property("numEntries", &ForceField::MMFF94OutOfPlaneBendingParameterTable::getNumEntries)
        .add_property("entries", python::make_function(&getEntries))
        .def("set", &ForceField::MMFF94OutOfPlaneBendingParameterTable::set, (python::arg("table"), python::arg("param_set")))
        .staticmethod("set")
        .def("get", &ForceField::MMFF94OutOfPlaneBendingParameterTable::get, python::arg("param_set"),
             python::return_value_policy<python::copy_const_reference>())
        .staticmethod("get");

    python::class_<ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry>("Entry", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
        .def(python::init<unsigned int, unsigned int, unsigned int, unsigned int, double>(
                 (python::arg("self"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
                  python::arg("term_atom2_type"), python::arg("oop_atom_type"), python::arg("force_const"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry>())    
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry>(),
             (python::arg("self"), python::arg("entry")), python::return_self<>())
        .def("getTerminalAtom1Type", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getTerminalAtom1Type, python::arg("self"))
        .def("getCenterAtomType", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getCenterAtomType, python::arg("self"))
        .def("getTerminalAtom2Type", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getTerminalAtom2Type, python::arg("self"))
        .def("getOutOfPlaneAtomType", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getOutOfPlaneAtomType, python::arg("self"))
        .def("getForceConstant", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getForceConstant, python::arg("self"))
        .def("__nonzero__", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::operator bool, python::arg("self"))
        .def("__bool__", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::operator bool, python::arg("self"))
        .add_property("termAtom1Type", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getTerminalAtom1Type)
        .add_property("ctrAtomType", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getCenterAtomType)
        .add_property("termAtom2Type", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getTerminalAtom2Type)
        .add_property("oopAtomType", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getOutOfPlaneAtomType)
        .add_property("forceConstant", &ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getForceConstant);
}
