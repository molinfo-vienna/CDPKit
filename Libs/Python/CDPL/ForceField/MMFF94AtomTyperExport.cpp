/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AtomTyperExport.cpp 
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

#include "CDPL/ForceField/MMFF94AtomTyper.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94AtomTyper()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94AtomTyper, ForceField::MMFF94AtomTyper::SharedPointer>("MMFF94AtomTyper", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94AtomTyper&>((python::arg("self"), python::arg("typer"))))
		.def(python::init<const Chem::MolecularGraph&, Util::SArray&, Util::UIArray&, bool>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("sym_types"), 
				  python::arg("num_types"), python::arg("strict"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94AtomTyper>())	
		.def("setSymbolicAtomTypePatternTable", &ForceField::MMFF94AtomTyper::setSymbolicAtomTypePatternTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setAromaticAtomTypeDefinitionTable", &ForceField::MMFF94AtomTyper::setAromaticAtomTypeDefinitionTable,
			 (python::arg("self"), python::arg("table")))
		.def("setHeavyToHydrogenAtomTypeMap", &ForceField::MMFF94AtomTyper::setHeavyToHydrogenAtomTypeMap, 
			 (python::arg("self"), python::arg("map")))
		.def("setSymbolicToNumericAtomTypeMap", &ForceField::MMFF94AtomTyper::setSymbolicToNumericAtomTypeMap, 
			 (python::arg("self"), python::arg("map")))
		.def("setAtomTypePropertyTable", &ForceField::MMFF94AtomTyper::setAtomTypePropertyTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setAromaticRingSetFunction", &ForceField::MMFF94AtomTyper::setAromaticRingSetFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94AtomTyper::operator=),
			 (python::arg("self"), python::arg("typer")), python::return_self<>())
		.def("perceiveTypes", &ForceField::MMFF94AtomTyper::perceiveTypes, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("sym_types"), 
			  python::arg("num_types"), python::arg("strict")));
}
