/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94OutOfPlaneBendingInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94OutOfPlaneBendingInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94OutOfPlaneBendingInteraction>("MMFF94OutOfPlaneBendingInteraction", python::no_init)
		.def(python::init<const ForceField::MMFF94OutOfPlaneBendingInteraction&>((python::arg("self"), python::arg("iactn"))))
		.def(python::init<std::size_t, std::size_t, std::size_t, std::size_t, double>(
				 (python::arg("self"), python::arg("term_atom1_idx"), python::arg("ctr_atom_idx"), python::arg("term_atom2_idx"),
				  python::arg("oop_atom_idx"), python::arg("force_const"))))
		.def("getTerminalAtom1Index", &ForceField::MMFF94OutOfPlaneBendingInteraction::getTerminalAtom1Index, python::arg("self"))
		.def("getTerminalAtom2Index", &ForceField::MMFF94OutOfPlaneBendingInteraction::getTerminalAtom2Index, python::arg("self"))
		.def("getCenterAtomIndex", &ForceField::MMFF94OutOfPlaneBendingInteraction::getCenterAtomIndex, python::arg("self"))
		.def("getOutOfPlaneAtomIndex", &ForceField::MMFF94OutOfPlaneBendingInteraction::getOutOfPlaneAtomIndex, python::arg("self"))
		.def("getForceConstant", &ForceField::MMFF94OutOfPlaneBendingInteraction::getForceConstant, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94OutOfPlaneBendingInteraction::operator=),
			 (python::arg("self"), python::arg("iactn")), python::return_self<>())
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94OutOfPlaneBendingInteraction>())
		.add_property("termAtom1Index", &ForceField::MMFF94OutOfPlaneBendingInteraction::getTerminalAtom1Index) 
		.add_property("termAtom2Index", &ForceField::MMFF94OutOfPlaneBendingInteraction::getTerminalAtom2Index)
		.add_property("ctrAtomIndex", &ForceField::MMFF94OutOfPlaneBendingInteraction::getCenterAtomIndex)
		.add_property("oopAtomIndex", &ForceField::MMFF94OutOfPlaneBendingInteraction::getOutOfPlaneAtomIndex)
		.add_property("forceConstant", &ForceField::MMFF94OutOfPlaneBendingInteraction::getForceConstant);
}
