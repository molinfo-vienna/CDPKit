/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TPSACalculatorExport.cpp 
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

#include "CDPL/MolProp/TPSACalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportTPSACalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolProp::TPSACalculator, boost::noncopyable>("TPSACalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const MolProp::TPSACalculator&>((python::arg("self"), python::arg("calc"))))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MolProp::TPSACalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&MolProp::TPSACalculator::operator=), 
			 (python::arg("self"), python::arg("calc")), python::return_self<>())
		.def("calculate", &MolProp::TPSACalculator::calculate, (python::arg("self"), python::arg("molgraph")))
		.def("getResult", &MolProp::TPSACalculator::getResult, python::arg("self"))
		.add_property("result", &MolProp::TPSACalculator::getResult);
}
