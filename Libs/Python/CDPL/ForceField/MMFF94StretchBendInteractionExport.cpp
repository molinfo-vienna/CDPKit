/* 
 * MMFF94StretchBendInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94StretchBendInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94StretchBendInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94StretchBendInteraction>("MMFF94StretchBendInteraction", python::no_init)
        .def(python::init<const ForceField::MMFF94StretchBendInteraction&>((python::arg("self"), python::arg("iactn"))))
        .def(python::init<std::size_t, std::size_t, std::size_t, unsigned int, double, double, double, double, double>(
                 (python::arg("self"), python::arg("term_atom1_idx"), python::arg("ctr_atom_idx"), python::arg("term_atom2_idx"),
                  python::arg("sb_type_idx"), python::arg("ref_angle"), python::arg("ref_length1"), python::arg("ref_length2"),
                  python::arg("ijk_force_const"), python::arg("kji_force_const"))))
        .def("getTerminalAtom1Index", &ForceField::MMFF94StretchBendInteraction::getTerminalAtom1Index, python::arg("self"))
        .def("getTerminalAtom2Index", &ForceField::MMFF94StretchBendInteraction::getTerminalAtom2Index, python::arg("self"))
        .def("getCenterAtomIndex", &ForceField::MMFF94StretchBendInteraction::getCenterAtomIndex, python::arg("self"))
        .def("getAtom1Index", &ForceField::MMFF94StretchBendInteraction::getAtom1Index, python::arg("self"))
        .def("getAtom2Index", &ForceField::MMFF94StretchBendInteraction::getAtom2Index, python::arg("self"))
        .def("getAtom3Index", &ForceField::MMFF94StretchBendInteraction::getAtom3Index, python::arg("self"))
        .def("getStretchBendTypeIndex", &ForceField::MMFF94StretchBendInteraction::getStretchBendTypeIndex, python::arg("self"))
        .def("getIJKForceConstant", &ForceField::MMFF94StretchBendInteraction::getIJKForceConstant, python::arg("self"))
        .def("getKJIForceConstant", &ForceField::MMFF94StretchBendInteraction::getKJIForceConstant, python::arg("self"))
        .def("getReferenceAngle", &ForceField::MMFF94StretchBendInteraction::getReferenceAngle, python::arg("self"))
        .def("setReferenceAngle", &ForceField::MMFF94StretchBendInteraction::setReferenceAngle, 
             (python::arg("self"), python::arg("angle")))
        .def("getReferenceLength1", &ForceField::MMFF94StretchBendInteraction::getReferenceLength1, python::arg("self"))
        .def("setReferenceLength1", &ForceField::MMFF94StretchBendInteraction::setReferenceLength2, 
             (python::arg("self"), python::arg("length")))
        .def("getReferenceLength2", &ForceField::MMFF94StretchBendInteraction::getReferenceLength2, python::arg("self"))
        .def("setReferenceLength2", &ForceField::MMFF94StretchBendInteraction::setReferenceLength2, 
             (python::arg("self"), python::arg("length")))
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94StretchBendInteraction>(),
             (python::arg("self"), python::arg("iactn")), python::return_self<>())
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94StretchBendInteraction>())
        .add_property("termAtom1Index", &ForceField::MMFF94StretchBendInteraction::getTerminalAtom1Index) 
        .add_property("termAtom2Index", &ForceField::MMFF94StretchBendInteraction::getTerminalAtom2Index)
        .add_property("ctrAtomIndex", &ForceField::MMFF94StretchBendInteraction::getCenterAtomIndex)
        .add_property("atom1Index", &ForceField::MMFF94StretchBendInteraction::getAtom1Index) 
        .add_property("atom2Index", &ForceField::MMFF94StretchBendInteraction::getAtom2Index)
        .add_property("atom3Index", &ForceField::MMFF94StretchBendInteraction::getAtom3Index)
        .add_property("stretchBendTypeIndex", &ForceField::MMFF94StretchBendInteraction::getStretchBendTypeIndex)
        .add_property("referenceAngle", &ForceField::MMFF94StretchBendInteraction::getReferenceAngle,
                      &ForceField::MMFF94StretchBendInteraction::setReferenceAngle)
        .add_property("referenceLength1", &ForceField::MMFF94StretchBendInteraction::getReferenceLength1, 
                      &ForceField::MMFF94StretchBendInteraction::setReferenceLength1)
        .add_property("referenceLength2", &ForceField::MMFF94StretchBendInteraction::getReferenceLength2, 
                      &ForceField::MMFF94StretchBendInteraction::setReferenceLength2)
        .add_property("ijkForceConstant", &ForceField::MMFF94StretchBendInteraction::getIJKForceConstant)
        .add_property("kjiForceConstant", &ForceField::MMFF94StretchBendInteraction::getKJIForceConstant);
}
