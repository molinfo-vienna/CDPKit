/* 
 * MMFF94ChargeCalculatorExport.cpp 
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

#include "CDPL/ForceField/MMFF94ChargeCalculator.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94ChargeCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94ChargeCalculator, ForceField::MMFF94ChargeCalculator::SharedPointer>("MMFF94ChargeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ForceField::MMFF94ChargeCalculator&>((python::arg("self"), python::arg("calc"))))
		.def(python::init<const Chem::MolecularGraph&, Util::DArray&, bool>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("charges"), python::arg("strict"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94ChargeCalculator>())	
		.def("setAromaticRingSetFunction", &ForceField::MMFF94ChargeCalculator::setAromaticRingSetFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setNumericAtomTypeFunction", &ForceField::MMFF94ChargeCalculator::setNumericAtomTypeFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setSymbolicAtomTypeFunction", &ForceField::MMFF94ChargeCalculator::setSymbolicAtomTypeFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setBondTypeIndexFunction", &ForceField::MMFF94ChargeCalculator::setBondTypeIndexFunction, 
			 (python::arg("self"), python::arg("func"))) 
		.def("setAtomTypePropertyTable", &ForceField::MMFF94ChargeCalculator::setAtomTypePropertyTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setFormalChargeDefinitionTable", &ForceField::MMFF94ChargeCalculator::setFormalChargeDefinitionTable, 
			 (python::arg("self"), python::arg("table")))
		.def("setBondChargeIncrementTable", &ForceField::MMFF94ChargeCalculator::setBondChargeIncrementTable,
			 (python::arg("self"), python::arg("table")))
		.def("setPartialBondChargeIncrementTable", &ForceField::MMFF94ChargeCalculator::setPartialBondChargeIncrementTable, 
			 (python::arg("self"), python::arg("table")))
		.def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94ChargeCalculator::operator=),
			 (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
		.def("calculate", &ForceField::MMFF94ChargeCalculator::calculate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("charges"), python::arg("strict")))
		.def("getFormalCharges", &ForceField::MMFF94ChargeCalculator::getFormalCharges, python::arg("self"),
			 python::return_internal_reference<>())
		.def("formalCharges", python::make_function(&ForceField::MMFF94ChargeCalculator::getFormalCharges,
													python::return_internal_reference<>()));
}
