/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResonanceStructureGeneratorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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

#include "CDPL/Chem/ResonanceStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportResonanceStructureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::ResonanceStructureGenerator, Chem::ResonanceStructureGenerator::SharedPointer> cl("ResonanceStructureGenerator", python::no_init);

	python::scope scope = cl;

	python::class_<Chem::ResonanceStructureGenerator::StructureData>("StructureData", python::no_init)
		.def(python::init<Chem::ResonanceStructureGenerator::StructureData>((python::arg("self"), python::arg("data"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ResonanceStructureGenerator::StructureData>())	
		.def("assign", &Chem::ResonanceStructureGenerator::operator=, 
			 (python::arg("self"), python::arg("data")), python::return_self<>())
		.def("getAtomCharges", &Chem::ResonanceStructureGenerator::StructureData::getAtomCharges, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("getBondOrders", &Chem::ResonanceStructureGenerator::StructureData::getBondOrders, python::arg("self"), 
			 python::return_internal_reference<>())
		.add_property("atomCharges", python::make_function(&Chem::ResonanceStructureGenerator::StructureData::getAtomCharges,
														   python::return_internal_reference<>()))
		.add_property("bondOrders", python::make_function(&Chem::ResonanceStructureGenerator::StructureData::getBondOrders,
														  python::return_internal_reference<>()));

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::ResonanceStructureGenerator>((python::arg("self"), python::arg("gen"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ResonanceStructureGenerator>())	
		.def("assign", &Chem::ResonanceStructureGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("octetRuleViolationsMinimized", &Chem::ResonanceStructureGenerator::octetRuleViolationsMinimized,
			 python::arg("self"))
		.def("minimizeOctetRuleViolations", &Chem::ResonanceStructureGenerator::minimizeOctetRuleViolations,
			 (python::arg("self"), python::arg("minimize")))
		.def("sp1GeometryViolationsMinimized", &Chem::ResonanceStructureGenerator::sp1GeometryViolationsMinimized,
			 python::arg("self"))
		.def("minimizeSP1GeometryViolations", &Chem::ResonanceStructureGenerator::minimizeSP1GeometryViolations,
			 (python::arg("self"), python::arg("minimize")))
		.def("carbonBond12ChargesMinimized", &Chem::ResonanceStructureGenerator::carbonBond12ChargesMinimized,
			 python::arg("self"))
		.def("minimizeCarbonBond12Charges", &Chem::ResonanceStructureGenerator::minimizeCarbonBond12Charges,
			 (python::arg("self"), python::arg("minimize")))
		.def("getOctetRuleCheckAtomTypes", static_cast<Util::BitSet& (Chem::ResonanceStructureGenerator::*)()>(
				 &Chem::ResonanceStructureGenerator::getOctetRuleCheckAtomTypes),
			 python::arg("self"), python::return_internal_reference<>())
		.def("getChargeCountWindow", &Chem::ResonanceStructureGenerator::getChargeCountWindow,
			 python::arg("self"))
		.def("setChargeCountWindow", &Chem::ResonanceStructureGenerator::setChargeCountWindow,
			 (python::arg("self"), python::arg("win_size")))
		.def("generate", &Chem::ResonanceStructureGenerator::generate, 
			 (python::arg("self"), python::arg("molgraph")))
		.def("getNumStructures", &Chem::ResonanceStructureGenerator::getNumStructures, python::arg("self"))
		.def("getStructureData", &Chem::ResonanceStructureGenerator::getStructureData, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", &Chem::ResonanceStructureGenerator::getStructureData, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__len__", &Chem::ResonanceStructureGenerator::getNumStructures, python::arg("self"))
		.add_property("numStructures", &Chem::ResonanceStructureGenerator::getNumStructures)
		.add_property("minOctetRuleViolations", &Chem::ResonanceStructureGenerator::octetRuleViolationsMinimized,
					  &Chem::ResonanceStructureGenerator::minimizeOctetRuleViolations)
		.add_property("minSP1GeometryViolations", &Chem::ResonanceStructureGenerator::sp1GeometryViolationsMinimized,
					  &Chem::ResonanceStructureGenerator::minimizeSP1GeometryViolations)
		.add_property("minCarbonBond12Charges", &Chem::ResonanceStructureGenerator::carbonBond12ChargesMinimized,
					  &Chem::ResonanceStructureGenerator::minimizeCarbonBond12Charges)
		.add_property("octetRuleCheckAtomTypes", python::make_function(static_cast<Util::BitSet& (Chem::ResonanceStructureGenerator::*)()>(
																		   &Chem::ResonanceStructureGenerator::getOctetRuleCheckAtomTypes),
																	   python::return_internal_reference<>()))
		.add_property("chargeCountWindow", &Chem::ResonanceStructureGenerator::getChargeCountWindow,
					  &Chem::ResonanceStructureGenerator::setChargeCountWindow);
}
