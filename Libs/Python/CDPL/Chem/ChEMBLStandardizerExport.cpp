/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ChEMBLStandardizerExport.cpp 
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

#include "CDPL/Chem/ChEMBLStandardizer.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportChEMBLStandardizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::ChEMBLStandardizer, Chem::ChEMBLStandardizer::SharedPointer> cl("ChEMBLStandardizer", python::no_init);
    python::scope scope = cl;

	python::enum_<Chem::ChEMBLStandardizer::Result>("Result")
		.value("NO_CHANGES", Chem::ChEMBLStandardizer::NO_CHANGES)
		.value("EXCLUDED", Chem::ChEMBLStandardizer::EXCLUDED)
		.value("H_REMOVED", Chem::ChEMBLStandardizer::H_REMOVED)
		.export_values();

    cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::ChEMBLStandardizer>((python::arg("self"), python::arg("standardizer"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ChEMBLStandardizer>())	
		.def("assign", &Chem::ChEMBLStandardizer::operator=, 
			 (python::arg("self"), python::arg("standardizer")), python::return_self<>())
		.def("ignoreExcludedFlag",  &Chem::ChEMBLStandardizer::ignoreExcludedFlag, (python::arg("self"), python::arg("ignore")))
		.def("excludedFlagIgnored",  &Chem::ChEMBLStandardizer::excludedFlagIgnored, python::arg("self"))
		.def("standardize", static_cast<Chem::ChEMBLStandardizer::Result (Chem::ChEMBLStandardizer::*)(Chem::Molecule&)>
			 (&Chem::ChEMBLStandardizer::standardize), (python::arg("self"), python::arg("mol")))
		.def("standardize", static_cast<Chem::ChEMBLStandardizer::Result (Chem::ChEMBLStandardizer::*)(const Chem::Molecule&, Chem::Molecule&)>
			 (&Chem::ChEMBLStandardizer::standardize), (python::arg("self"), python::arg("mol"), python::arg("std_mol")))
		.def("getParent", static_cast<bool (Chem::ChEMBLStandardizer::*)(Chem::Molecule&)>
			 (&Chem::ChEMBLStandardizer::getParent), (python::arg("self"), python::arg("mol")))
		.def("getParent", static_cast<bool (Chem::ChEMBLStandardizer::*)(const Chem::Molecule&, Chem::Molecule&)>
			 (&Chem::ChEMBLStandardizer::getParent), (python::arg("self"), python::arg("mol"), python::arg("parent_mol")))
		.add_property("ignoreExclFlag", &Chem::ChEMBLStandardizer::excludedFlagIgnored, &Chem::ChEMBLStandardizer::ignoreExcludedFlag)
		;
}
