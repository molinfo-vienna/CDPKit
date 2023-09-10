/* 
 * MMFF94AngleBendingParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94AngleBendingParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94AngleBendingParameterTable& table)
    {
        using namespace CDPL;
        using namespace ForceField;

        boost::python::list entries;

        for (MMFF94AngleBendingParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
            entries.append(boost::ref(*it));

        return entries;
    }
}


void CDPLPythonForceField::exportMMFF94AngleBendingParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94AngleBendingParameterTable, 
                                         ForceField::MMFF94AngleBendingParameterTable::SharedPointer>("MMFF94AngleBendingParameterTable", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94AngleBendingParameterTable&>((python::arg("self"), python::arg("table"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AngleBendingParameterTable>())    
        .def("addEntry", &ForceField::MMFF94AngleBendingParameterTable::addEntry, 
             (python::arg("self"), python::arg("angle_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"), python::arg("force_const"), python::arg("ref_angle")))
        .def("removeEntry", static_cast<bool (ForceField::MMFF94AngleBendingParameterTable::*)(unsigned int, unsigned int, unsigned int, unsigned int)>(
                 &ForceField::MMFF94AngleBendingParameterTable::removeEntry), 
             (python::arg("self"), python::arg("angle_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"))) 
        .def("getEntry", &ForceField::MMFF94AngleBendingParameterTable::getEntry, 
             (python::arg("self"), python::arg("angle_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type")), python::return_internal_reference<>()) 
        .def("clear", &ForceField::MMFF94AngleBendingParameterTable::clear, python::arg("self")) 
        .def("getNumEntries", &ForceField::MMFF94AngleBendingParameterTable::getNumEntries, python::arg("self")) 
        .def("getEntries", &getEntries, python::arg("self")) 
        .def("load", &ForceField::MMFF94AngleBendingParameterTable::load, (python::arg("self"), python::arg("is"))) 
        .def("loadDefaults", &ForceField::MMFF94AngleBendingParameterTable::loadDefaults, python::arg("self")) 
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94AngleBendingParameterTable>(), 
             (python::arg("self"), python::arg("table")), python::return_self<>())
        .add_property("numEntries", &ForceField::MMFF94AngleBendingParameterTable::getNumEntries)
        .add_property("entries", python::make_function(&getEntries))
        .def("set", &ForceField::MMFF94AngleBendingParameterTable::set, python::arg("table"))
        .staticmethod("set")
        .def("get", &ForceField::MMFF94AngleBendingParameterTable::get, python::return_value_policy<python::copy_const_reference>())
        .staticmethod("get");

    python::class_<ForceField::MMFF94AngleBendingParameterTable::Entry>("Entry", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94AngleBendingParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
        .def(python::init<unsigned int, unsigned int, unsigned int, unsigned int, double, double>(
                 (python::arg("self"), python::arg("angle_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
                  python::arg("term_atom2_type"), python::arg("force_const"), python::arg("ref_angle"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AngleBendingParameterTable::Entry>())    
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94AngleBendingParameterTable::Entry>(),
             (python::arg("self"), python::arg("entry")), python::return_self<>())
        .def("getAngleTypeIndex", &ForceField::MMFF94AngleBendingParameterTable::Entry::getAngleTypeIndex, python::arg("self"))
        .def("getTerminalAtom1Type", &ForceField::MMFF94AngleBendingParameterTable::Entry::getTerminalAtom1Type, python::arg("self"))
        .def("getCenterAtomType", &ForceField::MMFF94AngleBendingParameterTable::Entry::getCenterAtomType, python::arg("self"))
        .def("getTerminalAtom2Type", &ForceField::MMFF94AngleBendingParameterTable::Entry::getTerminalAtom2Type, python::arg("self"))
        .def("getForceConstant", &ForceField::MMFF94AngleBendingParameterTable::Entry::getForceConstant, python::arg("self"))
        .def("getReferenceAngle", &ForceField::MMFF94AngleBendingParameterTable::Entry::getReferenceAngle, python::arg("self"))
        .def("__nonzero__", &ForceField::MMFF94AngleBendingParameterTable::Entry::operator bool, python::arg("self"))
        .def("__bool__", &ForceField::MMFF94AngleBendingParameterTable::Entry::operator bool, python::arg("self"))
        .add_property("angleTypeIndex", &ForceField::MMFF94AngleBendingParameterTable::Entry::getAngleTypeIndex)
        .add_property("termAtom1Type", &ForceField::MMFF94AngleBendingParameterTable::Entry::getTerminalAtom1Type)
        .add_property("ctrAtomType", &ForceField::MMFF94AngleBendingParameterTable::Entry::getCenterAtomType)
        .add_property("termAtom2Type", &ForceField::MMFF94AngleBendingParameterTable::Entry::getTerminalAtom2Type)
        .add_property("forceConstant", &ForceField::MMFF94AngleBendingParameterTable::Entry::getForceConstant)
        .add_property("referenceAngle", &ForceField::MMFF94AngleBendingParameterTable::Entry::getReferenceAngle);
}
