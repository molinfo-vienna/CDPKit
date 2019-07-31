/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94InteractionDataExport.cpp 
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

#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94InteractionData()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94InteractionData, ForceField::MMFF94InteractionData::SharedPointer>("MMFF94InteractionData", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94InteractionData&>((python::arg("self"), python::arg("ia_data"))))
		.def("clear", &ForceField::MMFF94InteractionData::clear, python::arg("self"))
		.def("getBondStretchingInteractions", 
			 static_cast<ForceField::MMFF94BondStretchingInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getBondStretchingInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("getAngleBendingInteractions", 
			 static_cast<ForceField::MMFF94AngleBendingInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getAngleBendingInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("getStretchBendInteractions", 
			 static_cast<ForceField::MMFF94StretchBendInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getStretchBendInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("getOutOfPlaneBendingInteractions", 
			 static_cast<ForceField::MMFF94OutOfPlaneBendingInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getOutOfPlaneBendingInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("getTorsionInteractions", 
			 static_cast<ForceField::MMFF94TorsionInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getTorsionInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("getElectrostaticInteractions", 
			 static_cast<ForceField::MMFF94ElectrostaticInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getElectrostaticInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("getVanDerWaalsInteractions", 
			 static_cast<ForceField::MMFF94VanDerWaalsInteractionData& (ForceField::MMFF94InteractionData::*)()>(
				 &ForceField::MMFF94InteractionData::getVanDerWaalsInteractions), python::arg("self"),
			 python::return_internal_reference<>())
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94InteractionData::operator=),
			 (python::arg("self"), python::arg("ia_data")), python::return_self<>())
		.def("swap", &ForceField::MMFF94InteractionData::swap, (python::arg("self"), python::arg("ia_data")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94InteractionData>())
		.add_property("bondStretchingInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94BondStretchingInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getBondStretchingInteractions), python::return_internal_reference<>()))
		.add_property("angleBendingInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94AngleBendingInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getAngleBendingInteractions), python::return_internal_reference<>()))
		.add_property("stretchBendInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94StretchBendInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getStretchBendInteractions), python::return_internal_reference<>()))
		.add_property("outOfPlaneBendingInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94OutOfPlaneBendingInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getOutOfPlaneBendingInteractions), python::return_internal_reference<>()))
		.add_property("torsionInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94TorsionInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getTorsionInteractions), python::return_internal_reference<>()))
		.add_property("electrostaticInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94ElectrostaticInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getElectrostaticInteractions), python::return_internal_reference<>()))
		.add_property("vanDerWaalsInteractions", 
					  python::make_function(static_cast<ForceField::MMFF94VanDerWaalsInteractionData& (ForceField::MMFF94InteractionData::*)()>(
												&ForceField::MMFF94InteractionData::getVanDerWaalsInteractions), python::return_internal_reference<>()));
}
