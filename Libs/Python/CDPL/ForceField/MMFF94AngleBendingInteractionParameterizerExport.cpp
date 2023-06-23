/* 
 * MMFF94AngleBendingInteractionParameterizerExport.cpp 
 *
 * This file is part of the Chemical Parameterizer Processing Toolkit
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

#include "CDPL/ForceField/MMFF94AngleBendingInteractionParameterizer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94AngleBendingInteractionParameterizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94AngleBendingInteractionParameterizer, 
				   ForceField::MMFF94AngleBendingInteractionParameterizer::SharedPointer>("MMFF94AngleBendingInteractionParameterizer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94AngleBendingInteractionParameterizer&>((python::arg("self"), python::arg("parameterizer"))))
		.def(python::init<const Chem::MolecularGraph&, ForceField::MMFF94AngleBendingInteractionData&, bool>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("strict"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AngleBendingInteractionParameterizer>())	
		.def("setFilterFunction", &ForceField::MMFF94AngleBendingInteractionParameterizer::setFilterFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAtomTypeFunction", &ForceField::MMFF94AngleBendingInteractionParameterizer::setAtomTypeFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setBondTypeIndexFunction", &ForceField::MMFF94AngleBendingInteractionParameterizer::setBondTypeIndexFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAromaticRingSetFunction", &ForceField::MMFF94AngleBendingInteractionParameterizer::setAromaticRingSetFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAngleBendingParameterTable", &ForceField::MMFF94AngleBendingInteractionParameterizer::setAngleBendingParameterTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setBondStretchingParameterTable", &ForceField::MMFF94AngleBendingInteractionParameterizer::setBondStretchingParameterTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setBondStretchingRuleParameterTable", &ForceField::MMFF94AngleBendingInteractionParameterizer::setBondStretchingRuleParameterTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setAtomTypePropertyTable", &ForceField::MMFF94AngleBendingInteractionParameterizer::setAtomTypePropertyTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setParameterAtomTypeMap", &ForceField::MMFF94AngleBendingInteractionParameterizer::setParameterAtomTypeMap, 
			 (python::arg("self"), python::arg("map")))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AngleBendingInteractionParameterizer::operator=),
			 (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
		.def("parameterize", &ForceField::MMFF94AngleBendingInteractionParameterizer::parameterize, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("strict")));
}
