/* 
 * MMFF94TorsionInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94TorsionInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94TorsionInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94TorsionInteraction>("MMFF94TorsionInteraction", python::no_init)
        .def(python::init<const ForceField::MMFF94TorsionInteraction&>((python::arg("self"), python::arg("iactn"))))
        .def(python::init<std::size_t, std::size_t, std::size_t, std::size_t, unsigned int, double, double, double>(
                 (python::arg("self"), python::arg("term_atom1_idx"), python::arg("ctr_atom1_idx"), python::arg("ctr_atom2_idx"),
                  python::arg("term_atom2_idx"), python::arg("tor_type_idx"), python::arg("tor_param1"), 
                  python::arg("tor_param2"), python::arg("tor_param3"))))
        .def("getTerminalAtom1Index", &ForceField::MMFF94TorsionInteraction::getTerminalAtom1Index, python::arg("self"))
        .def("getTerminalAtom2Index", &ForceField::MMFF94TorsionInteraction::getTerminalAtom2Index, python::arg("self"))
        .def("getCenterAtom1Index", &ForceField::MMFF94TorsionInteraction::getCenterAtom1Index, python::arg("self"))
        .def("getCenterAtom2Index", &ForceField::MMFF94TorsionInteraction::getCenterAtom2Index, python::arg("self"))
        .def("getAtom1Index", &ForceField::MMFF94TorsionInteraction::getAtom1Index, python::arg("self"))
        .def("getAtom2Index", &ForceField::MMFF94TorsionInteraction::getAtom2Index, python::arg("self"))
        .def("getAtom3Index", &ForceField::MMFF94TorsionInteraction::getAtom3Index, python::arg("self"))
        .def("getAtom4Index", &ForceField::MMFF94TorsionInteraction::getAtom4Index, python::arg("self"))
        .def("getTorsionTypeIndex", &ForceField::MMFF94TorsionInteraction::getTorsionTypeIndex, python::arg("self"))
        .def("getTorsionParameter1", &ForceField::MMFF94TorsionInteraction::getTorsionParameter1, python::arg("self"))
        .def("getTorsionParameter2", &ForceField::MMFF94TorsionInteraction::getTorsionParameter2, python::arg("self"))
        .def("getTorsionParameter3", &ForceField::MMFF94TorsionInteraction::getTorsionParameter3, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94TorsionInteraction::operator=),
             (python::arg("self"), python::arg("iactn")), python::return_self<>())
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94TorsionInteraction>())
        .add_property("termAtom1Index", &ForceField::MMFF94TorsionInteraction::getTerminalAtom1Index) 
        .add_property("termAtom2Index", &ForceField::MMFF94TorsionInteraction::getTerminalAtom2Index)
        .add_property("ctrAtom1Index", &ForceField::MMFF94TorsionInteraction::getCenterAtom1Index)
        .add_property("ctrAtom2Index", &ForceField::MMFF94TorsionInteraction::getCenterAtom2Index)
        .add_property("atom1Index", &ForceField::MMFF94TorsionInteraction::getAtom1Index) 
        .add_property("atom2Index", &ForceField::MMFF94TorsionInteraction::getAtom2Index)
        .add_property("atom3Index", &ForceField::MMFF94TorsionInteraction::getAtom3Index)
        .add_property("atom4Index", &ForceField::MMFF94TorsionInteraction::getAtom4Index)
        .add_property("torsionTypeIndex", &ForceField::MMFF94TorsionInteraction::getTorsionTypeIndex)
        .add_property("torsionParam1", &ForceField::MMFF94TorsionInteraction::getTorsionParameter1)
        .add_property("torsionParam2", &ForceField::MMFF94TorsionInteraction::getTorsionParameter2)
        .add_property("torsionParam3", &ForceField::MMFF94TorsionInteraction::getTorsionParameter3);
}
