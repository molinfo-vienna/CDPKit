/* 
 * AtomBondMappingExport.cpp 
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

#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportAtomBondMapping()
{
    using namespace boost;
    using namespace CDPL;

    Chem::AtomMapping& (Chem::AtomBondMapping::*getAtomMappingFunc)() = &Chem::AtomBondMapping::getAtomMapping;
    Chem::BondMapping& (Chem::AtomBondMapping::*getBondMappingFunc)() = &Chem::AtomBondMapping::getBondMapping;

    python::class_<Chem::AtomBondMapping, Chem::AtomBondMapping::SharedPointer>("AtomBondMapping", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::AtomBondMapping&>((python::arg("self"), python::arg("mapping")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AtomBondMapping>())    
        .def("assign", CDPLPythonBase::copyAssOp(&Chem::AtomBondMapping::operator=), (python::arg("self"), python::arg("mapping")),
             python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("getAtomMapping", getAtomMappingFunc, python::arg("self"), python::return_internal_reference<>())
        .def("getBondMapping", getBondMappingFunc, python::arg("self"), python::return_internal_reference<>())
        .def("clear", &Chem::AtomBondMapping::clear, python::arg("self"))
        .def("__eq__", &Chem::AtomBondMapping::operator==, (python::arg("self"), python::arg("mapping")))
        .def("__ne__", &Chem::AtomBondMapping::operator!=, (python::arg("self"), python::arg("mapping")))
        .add_property("atomMapping", python::make_function(getAtomMappingFunc, python::return_internal_reference<>()))
        .add_property("bondMapping", python::make_function(getBondMappingFunc, python::return_internal_reference<>()));
}
