/* 
 * MMFF94StretchBendParameterTableExport.cpp 
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

#include "CDPL/ForceField/MMFF94StretchBendParameterTable.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ForceField::MMFF94StretchBendParameterTable& table)
    {
        using namespace CDPL;
        using namespace ForceField;

        boost::python::list entries;

        for (MMFF94StretchBendParameterTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it)
            entries.append(boost::ref(*it));

        return entries;
    }
}


void CDPLPythonForceField::exportMMFF94StretchBendParameterTable()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ForceField::MMFF94StretchBendParameterTable, 
                                         ForceField::MMFF94StretchBendParameterTable::SharedPointer>("MMFF94StretchBendParameterTable", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94StretchBendParameterTable&>((python::arg("self"), python::arg("table"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94StretchBendParameterTable>())    
        .def("addEntry", &ForceField::MMFF94StretchBendParameterTable::addEntry, 
             (python::arg("self"), python::arg("sb_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"), python::arg("ijk_force_const"), python::arg("kji_force_const")))
        .def("removeEntry", static_cast<bool (ForceField::MMFF94StretchBendParameterTable::*)(unsigned int, unsigned int, unsigned int, unsigned int)>(
                 &ForceField::MMFF94StretchBendParameterTable::removeEntry), 
             (python::arg("self"), python::arg("sb_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type"))) 
        .def("getEntry", &ForceField::MMFF94StretchBendParameterTable::getEntry, 
             (python::arg("self"), python::arg("sb_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
              python::arg("term_atom2_type")), python::return_internal_reference<>()) 
        .def("clear", &ForceField::MMFF94StretchBendParameterTable::clear, python::arg("self")) 
        .def("getNumEntries", &ForceField::MMFF94StretchBendParameterTable::getNumEntries, python::arg("self")) 
        .def("getEntries", &getEntries, python::arg("self")) 
        .def("load", &ForceField::MMFF94StretchBendParameterTable::load, (python::arg("self"), python::arg("is"))) 
        .def("loadDefaults", &ForceField::MMFF94StretchBendParameterTable::loadDefaults, python::arg("self")) 
        .def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94StretchBendParameterTable::operator=), 
             (python::arg("self"), python::arg("table")), python::return_self<>())
        .add_property("numEntries", &ForceField::MMFF94StretchBendParameterTable::getNumEntries)
        .add_property("entries", python::make_function(&getEntries))
        .def("set", &ForceField::MMFF94StretchBendParameterTable::set, python::arg("table"))
        .staticmethod("set")
        .def("get", &ForceField::MMFF94StretchBendParameterTable::get, python::return_value_policy<python::copy_const_reference>())
        .staticmethod("get");

    python::class_<ForceField::MMFF94StretchBendParameterTable::Entry>("Entry", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94StretchBendParameterTable::Entry&>((python::arg("self"), python::arg("entry"))))
        .def(python::init<unsigned int, unsigned int, unsigned int, unsigned int, double, double>(
                 (python::arg("self"), python::arg("sb_type_idx"), python::arg("term_atom1_type"), python::arg("ctr_atom_type"),
                  python::arg("term_atom2_type"), python::arg("ijk_force_const"), python::arg("kji_force_const"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94StretchBendParameterTable::Entry>())    
        .def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94StretchBendParameterTable::Entry::operator=),
             (python::arg("self"), python::arg("entry")), python::return_self<>())
        .def("getStretchBendTypeIndex", &ForceField::MMFF94StretchBendParameterTable::Entry::getStretchBendTypeIndex, python::arg("self"))
        .def("getTerminalAtom1Type", &ForceField::MMFF94StretchBendParameterTable::Entry::getTerminalAtom1Type, python::arg("self"))
        .def("getCenterAtomType", &ForceField::MMFF94StretchBendParameterTable::Entry::getCenterAtomType, python::arg("self"))
        .def("getTerminalAtom2Type", &ForceField::MMFF94StretchBendParameterTable::Entry::getTerminalAtom2Type, python::arg("self"))
        .def("getIJKForceConstant", &ForceField::MMFF94StretchBendParameterTable::Entry::getIJKForceConstant, python::arg("self"))
        .def("getKJIForceConstant", &ForceField::MMFF94StretchBendParameterTable::Entry::getKJIForceConstant, python::arg("self"))
        .def("__nonzero__", &ForceField::MMFF94StretchBendParameterTable::Entry::operator bool, python::arg("self"))
        .def("__bool__", &ForceField::MMFF94StretchBendParameterTable::Entry::operator bool, python::arg("self"))
        .add_property("stretchhBendTypeIndex", &ForceField::MMFF94StretchBendParameterTable::Entry::getStretchBendTypeIndex)
        .add_property("termAtom1Type", &ForceField::MMFF94StretchBendParameterTable::Entry::getTerminalAtom1Type)
        .add_property("ctrAtomType", &ForceField::MMFF94StretchBendParameterTable::Entry::getCenterAtomType)
        .add_property("termAtom2Type", &ForceField::MMFF94StretchBendParameterTable::Entry::getTerminalAtom2Type)
        .add_property("ijkForceConstant", &ForceField::MMFF94StretchBendParameterTable::Entry::getIJKForceConstant)
        .add_property("kjiForceConstant", &ForceField::MMFF94StretchBendParameterTable::Entry::getKJIForceConstant);
}
