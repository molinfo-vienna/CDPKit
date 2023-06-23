/* 
 * MMFF94ElectrostaticInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94ElectrostaticInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94ElectrostaticInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94ElectrostaticInteraction>("MMFF94ElectrostaticInteraction", python::no_init)
		.def(python::init<const ForceField::MMFF94ElectrostaticInteraction&>((python::arg("self"), python::arg("iactn"))))
		.def(python::init<std::size_t, std::size_t, double, double, double, double, double>(
				 (python::arg("self"), python::arg("atom1_idx"), python::arg("atom2_idx"), python::arg("atom1_chg"),
				  python::arg("atom2_chg"), python::arg("scale_fact"), python::arg("de_const"), python::arg("dist_expo"))))
		.def("getAtom1Index", &ForceField::MMFF94ElectrostaticInteraction::getAtom1Index, python::arg("self"))
		.def("getAtom2Index", &ForceField::MMFF94ElectrostaticInteraction::getAtom2Index, python::arg("self"))
		.def("getAtom1Charge", &ForceField::MMFF94ElectrostaticInteraction::getAtom1Charge, python::arg("self"))
		.def("getAtom2Charge", &ForceField::MMFF94ElectrostaticInteraction::getAtom2Charge, python::arg("self"))
		.def("getScalingFactor", &ForceField::MMFF94ElectrostaticInteraction::getScalingFactor, python::arg("self"))
		.def("getDielectricConstant", &ForceField::MMFF94ElectrostaticInteraction::getDielectricConstant, python::arg("self"))
		.def("getDistanceExponent", &ForceField::MMFF94ElectrostaticInteraction::getDistanceExponent, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94ElectrostaticInteraction::operator=),
			 (python::arg("self"), python::arg("iactn")), python::return_self<>())
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94ElectrostaticInteraction>())
		.add_property("atom1Index", &ForceField::MMFF94ElectrostaticInteraction::getAtom1Index) 
		.add_property("atom2Index", &ForceField::MMFF94ElectrostaticInteraction::getAtom2Index)
		.add_property("atom1Charge", &ForceField::MMFF94ElectrostaticInteraction::getAtom1Charge)
		.add_property("atom2Charge", &ForceField::MMFF94ElectrostaticInteraction::getAtom2Charge)
		.add_property("scalingFactor", &ForceField::MMFF94ElectrostaticInteraction::getScalingFactor)
		.add_property("dielectricConstant", &ForceField::MMFF94ElectrostaticInteraction::getDielectricConstant)
		.add_property("distanceExponent", &ForceField::MMFF94ElectrostaticInteraction::getDistanceExponent);
}
