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

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportChEMBLStandardizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::ChEMBLStandardizer, Chem::ChEMBLStandardizer::SharedPointer> cl("ChEMBLStandardizer", python::no_init);
    python::scope scope = cl;

	python::enum_<Chem::ChEMBLStandardizer::ChangeFlags>("ChangeFlags")
		.value("NONE", Chem::ChEMBLStandardizer::NONE)
		.value("EXCLUDED", Chem::ChEMBLStandardizer::EXCLUDED)
		.value("EXPLICIT_H_REMOVED", Chem::ChEMBLStandardizer::EXPLICIT_H_REMOVED)
		.value("UNKNOWN_STEREO_STANDARDIZED", Chem::ChEMBLStandardizer::UNKNOWN_STEREO_STANDARDIZED)
		.value("BONDS_KEKULIZED", Chem::ChEMBLStandardizer::BONDS_KEKULIZED)
		.value("STRUCTURE_NORMALIZED", Chem::ChEMBLStandardizer::STRUCTURE_NORMALIZED)
		.value("CHARGES_REMOVED", Chem::ChEMBLStandardizer::CHARGES_REMOVED)
		.value("TARTRATE_STEREO_CLEARED", Chem::ChEMBLStandardizer::TARTRATE_STEREO_CLEARED)
		.value("STRUCTURE_2D_CORRECTED", Chem::ChEMBLStandardizer::STRUCTURE_2D_CORRECTED)
		.value("ISOTOPE_INFO_CLEARED", Chem::ChEMBLStandardizer::ISOTOPE_INFO_CLEARED)
		.value("SALT_COMPONENTS_REMOVED", Chem::ChEMBLStandardizer::SALT_COMPONENTS_REMOVED)
		.value("SOLVENT_COMPONENTS_REMOVED", Chem::ChEMBLStandardizer::SOLVENT_COMPONENTS_REMOVED)
		.export_values();

    cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::ChEMBLStandardizer>((python::arg("self"), python::arg("standardizer"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ChEMBLStandardizer>())	
		.def("assign", &Chem::ChEMBLStandardizer::operator=, 
			 (python::arg("self"), python::arg("standardizer")), python::return_self<>())
		.def("standardize", static_cast<Chem::ChEMBLStandardizer::ChangeFlags (Chem::ChEMBLStandardizer::*)(Chem::Molecule&, bool)>
			 (&Chem::ChEMBLStandardizer::standardize),
			 (python::arg("self"), python::arg("mol"), python::arg("proc_excld") = false))
		.def("standardize", static_cast<Chem::ChEMBLStandardizer::ChangeFlags (Chem::ChEMBLStandardizer::*)(const Chem::Molecule&, Chem::Molecule&, bool)>
			 (&Chem::ChEMBLStandardizer::standardize),
			 (python::arg("self"), python::arg("mol"), python::arg("std_mol"), python::arg("proc_excluded") = false))
		.def("getParent", static_cast<Chem::ChEMBLStandardizer::ChangeFlags (Chem::ChEMBLStandardizer::*)(Chem::Molecule&, bool, bool)>
			 (&Chem::ChEMBLStandardizer::getParent), (python::arg("self"), python::arg("mol"),
													  python::arg("neutralize") = true, python::arg("check_exclusion") = true))
		.def("getParent", static_cast<Chem::ChEMBLStandardizer::ChangeFlags (Chem::ChEMBLStandardizer::*)(const Chem::Molecule&, Chem::Molecule&, bool, bool)>
			 (&Chem::ChEMBLStandardizer::getParent), (python::arg("self"), python::arg("mol"), python::arg("parent_mol"),
													  python::arg("neutralize") = true, python::arg("check_exclusion") = true));
}
