/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsInteractionParameterizerExport.cpp 
 *
 * This file is part of the Chemical Parameterizer Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionParameterizer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94VanDerWaalsInteractionParameterizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94VanDerWaalsInteractionParameterizer, 
				   ForceField::MMFF94VanDerWaalsInteractionParameterizer::SharedPointer>("MMFF94VanDerWaalsInteractionParameterizer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94VanDerWaalsInteractionParameterizer&>((python::arg("self"), python::arg("parameterizer"))))
		.def(python::init<const Chem::MolecularGraph&, ForceField::MMFF94VanDerWaalsInteractionData&, bool>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("strict"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94VanDerWaalsInteractionParameterizer>())	
		.def("setFilterFunction", &ForceField::MMFF94VanDerWaalsInteractionParameterizer::setFilterFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAtomTypeFunction", &ForceField::MMFF94VanDerWaalsInteractionParameterizer::setAtomTypeFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setTopologicalDistanceFunction", &ForceField::MMFF94VanDerWaalsInteractionParameterizer::setTopologicalDistanceFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setVanDerWaalsParameterTable", &ForceField::MMFF94VanDerWaalsInteractionParameterizer::setVanDerWaalsParameterTable, 
			 (python::arg("self"), python::arg("table")))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94VanDerWaalsInteractionParameterizer::operator=),
			 (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
		.def("parameterize", &ForceField::MMFF94VanDerWaalsInteractionParameterizer::parameterize, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("strict")));
}
