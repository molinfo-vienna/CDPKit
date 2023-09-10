/* 
 * MMFF94BondStretchingInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94BondStretchingInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94BondStretchingInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94BondStretchingInteraction>("MMFF94BondStretchingInteraction", python::no_init)
        .def(python::init<const ForceField::MMFF94BondStretchingInteraction&>((python::arg("self"), python::arg("iactn"))))
        .def(python::init<std::size_t, std::size_t, unsigned int, double, double>(
                 (python::arg("self"), python::arg("atom1_idx"), python::arg("atom2_idx"), python::arg("bond_type_idx"),
                  python::arg("force_const"), python::arg("ref_length"))))
        .def("getAtom1Index", &ForceField::MMFF94BondStretchingInteraction::getAtom1Index, python::arg("self"))
        .def("getAtom2Index", &ForceField::MMFF94BondStretchingInteraction::getAtom2Index, python::arg("self"))
        .def("getBondTypeIndex", &ForceField::MMFF94BondStretchingInteraction::getBondTypeIndex, python::arg("self"))
        .def("getForceConstant", &ForceField::MMFF94BondStretchingInteraction::getForceConstant, python::arg("self"))
        .def("getReferenceLength", &ForceField::MMFF94BondStretchingInteraction::getReferenceLength, python::arg("self"))
        .def("setReferenceLength", &ForceField::MMFF94BondStretchingInteraction::setReferenceLength, 
             (python::arg("self"), python::arg("length")))
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94BondStretchingInteraction>(),
             (python::arg("self"), python::arg("iactn")), python::return_self<>())
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondStretchingInteraction>())
        .add_property("atom1Index", &ForceField::MMFF94BondStretchingInteraction::getAtom1Index) 
        .add_property("atom2Index", &ForceField::MMFF94BondStretchingInteraction::getAtom2Index)
        .add_property("bondTypeIndex", &ForceField::MMFF94BondStretchingInteraction::getBondTypeIndex)
        .add_property("forceConstant", &ForceField::MMFF94BondStretchingInteraction::getForceConstant)
        .add_property("referenceLength", &ForceField::MMFF94BondStretchingInteraction::getReferenceLength,
                      &ForceField::MMFF94BondStretchingInteraction::setReferenceLength);
}
