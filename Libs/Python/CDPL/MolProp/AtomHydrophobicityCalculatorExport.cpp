/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomHydrophobicityCalculatorExport.cpp 
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

#include "CDPL/MolProp/AtomHydrophobicityCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportAtomHydrophobicityCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<MolProp::AtomHydrophobicityCalculator, boost::noncopyable>("AtomHydrophobicityCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const MolProp::AtomHydrophobicityCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<const Chem::MolecularGraph&, Util::DArray&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("hyd_table"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MolProp::AtomHydrophobicityCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&MolProp::AtomHydrophobicityCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("calculate", &MolProp::AtomHydrophobicityCalculator::calculate, (python::arg("self"), python::arg("molgraph"), python::arg("hyd_table")));
}
