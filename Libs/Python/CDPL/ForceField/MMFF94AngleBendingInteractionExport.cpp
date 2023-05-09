/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AngleBendingInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94AngleBendingInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94AngleBendingInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94AngleBendingInteraction>("MMFF94AngleBendingInteraction", python::no_init)
		.def(python::init<const ForceField::MMFF94AngleBendingInteraction&>((python::arg("self"), python::arg("iactn"))))
		.def(python::init<std::size_t, std::size_t, std::size_t, unsigned int, bool, double, double>(
				 (python::arg("self"), python::arg("term_atom1_idx"), python::arg("ctr_atom_idx"), python::arg("term_atom2_idx"),
				  python::arg("angle_type_idx"), python::arg("linear"), python::arg("force_const"), python::arg("ref_angle"))))
		.def("getTerminalAtom1Index", &ForceField::MMFF94AngleBendingInteraction::getTerminalAtom1Index, python::arg("self"))
		.def("getTerminalAtom2Index", &ForceField::MMFF94AngleBendingInteraction::getTerminalAtom2Index, python::arg("self"))
		.def("getCenterAtomIndex", &ForceField::MMFF94AngleBendingInteraction::getCenterAtomIndex, python::arg("self"))
		.def("getAtom1Index", &ForceField::MMFF94AngleBendingInteraction::getAtom1Index, python::arg("self"))
		.def("getAtom2Index", &ForceField::MMFF94AngleBendingInteraction::getAtom2Index, python::arg("self"))
		.def("getAtom3Index", &ForceField::MMFF94AngleBendingInteraction::getAtom3Index, python::arg("self"))
		.def("getAngleTypeIndex", &ForceField::MMFF94AngleBendingInteraction::getAngleTypeIndex, python::arg("self"))
		.def("isLinearAngle", &ForceField::MMFF94AngleBendingInteraction::isLinearAngle, python::arg("self"))
		.def("getForceConstant", &ForceField::MMFF94AngleBendingInteraction::getForceConstant, python::arg("self"))
		.def("getReferenceAngle", &ForceField::MMFF94AngleBendingInteraction::getReferenceAngle, python::arg("self"))
		.def("setReferenceAngle", &ForceField::MMFF94AngleBendingInteraction::setReferenceAngle, 
			 (python::arg("self"), python::arg("angle")))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AngleBendingInteraction::operator=),
			 (python::arg("self"), python::arg("iactn")), python::return_self<>())
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AngleBendingInteraction>())
		.add_property("termAtom1Index", &ForceField::MMFF94AngleBendingInteraction::getTerminalAtom1Index) 
		.add_property("termAtom2Index", &ForceField::MMFF94AngleBendingInteraction::getTerminalAtom2Index)
		.add_property("ctrAtomIndex", &ForceField::MMFF94AngleBendingInteraction::getCenterAtomIndex)
		.add_property("atom1Index", &ForceField::MMFF94AngleBendingInteraction::getAtom1Index) 
		.add_property("atom2Index", &ForceField::MMFF94AngleBendingInteraction::getAtom2Index)
		.add_property("atom3Index", &ForceField::MMFF94AngleBendingInteraction::getAtom3Index)
		.add_property("angleTypeIndex", &ForceField::MMFF94AngleBendingInteraction::getAngleTypeIndex)
		.add_property("linear", &ForceField::MMFF94AngleBendingInteraction::isLinearAngle)
		.add_property("forceConstant", &ForceField::MMFF94AngleBendingInteraction::getForceConstant)
		.add_property("referenceAngle", &ForceField::MMFF94AngleBendingInteraction::getReferenceAngle,
					  &ForceField::MMFF94AngleBendingInteraction::setReferenceAngle);
}
