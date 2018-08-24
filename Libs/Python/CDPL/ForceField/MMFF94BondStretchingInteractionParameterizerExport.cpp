/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingInteractionParameterizerExport.cpp 
 *
 * This file is part of the Chemical Parameterizer Processing Toolkit
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

#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94BondStretchingInteractionParameterizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94BondStretchingInteractionParameterizer, 
				   ForceField::MMFF94BondStretchingInteractionParameterizer::SharedPointer>("MMFF94BondStretchingInteractionParameterizer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94BondStretchingInteractionParameterizer&>((python::arg("self"), python::arg("parameterizer"))))
		.def(python::init<const Chem::MolecularGraph&, ForceField::MMFF94BondStretchingInteractionData&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondStretchingInteractionParameterizer>())	
		.def("setFilterFunction", &ForceField::MMFF94BondStretchingInteractionParameterizer::setFilterFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAtomTypeFunction", &ForceField::MMFF94BondStretchingInteractionParameterizer::setAtomTypeFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setBondTypeIndexFunction", &ForceField::MMFF94BondStretchingInteractionParameterizer::setBondTypeIndexFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAromaticRingSetFunction", &ForceField::MMFF94BondStretchingInteractionParameterizer::setAromaticRingSetFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setBondStretchingParameterTable", &ForceField::MMFF94BondStretchingInteractionParameterizer::setBondStretchingParameterTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setBondStretchingRuleParameterTable", &ForceField::MMFF94BondStretchingInteractionParameterizer::setBondStretchingRuleParameterTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setAtomTypePropertyTable", &ForceField::MMFF94BondStretchingInteractionParameterizer::setAtomTypePropertyTable, 
			 (python::arg("self"), python::arg("table")))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94BondStretchingInteractionParameterizer::operator=),
			 (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
		.def("parameterize", &ForceField::MMFF94BondStretchingInteractionParameterizer::parameterize, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data")));
}
