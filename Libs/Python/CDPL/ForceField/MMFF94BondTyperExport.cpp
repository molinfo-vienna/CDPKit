/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondTyperExport.cpp 
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

#include "CDPL/ForceField/MMFF94BondTyper.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94BondTyper()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94BondTyper>("MMFF94BondTyper", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94BondTyper&>((python::arg("self"), python::arg("typer"))))
		.def(python::init<const Chem::MolecularGraph&, Util::UIArray&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("types"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94BondTyper>())	
		.def("setAtomTypeFunction", &ForceField::MMFF94BondTyper::setAtomTypeFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAromaticRingSetFunction", &ForceField::MMFF94BondTyper::setAromaticRingSetFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAtomTypePropertyTable", &ForceField::MMFF94BondTyper::setAtomTypePropertyTable, 
			 (python::arg("self"), python::arg("table")))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94BondTyper::operator=),
			 (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
		.def("perceiveTypes", &ForceField::MMFF94BondTyper::perceiveTypes, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("types")));
}
