/* 
 * ProtonationStateStandardizerExport.cpp 
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

#include "CDPL/Chem/ProtonationStateStandardizer.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportProtonationStateStandardizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::ProtonationStateStandardizer, Chem::ProtonationStateStandardizer::SharedPointer> cl("ProtonationStateStandardizer", python::no_init);
	python::scope scope = cl;

	python::enum_<Chem::ProtonationStateStandardizer::Flavor>("Flavor")
		.value("MIN_CHARGED_ATOM_COUNT", Chem::ProtonationStateStandardizer::MIN_CHARGED_ATOM_COUNT)
		.value("PHYSIOLOGICAL_CONDITION_STATE", Chem::ProtonationStateStandardizer::PHYSIOLOGICAL_CONDITION_STATE)
		.value("MAX_CHARGE_COMPENSATION", Chem::ProtonationStateStandardizer::MAX_CHARGE_COMPENSATION)
		.export_values();

  	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<Chem::ProtonationStateStandardizer>((python::arg("self"), python::arg("standardizer"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ProtonationStateStandardizer>())	
		.def("assign", &Chem::ProtonationStateStandardizer::operator=, 
			 (python::arg("self"), python::arg("standardizer")), python::return_self<>())
		.def("standardize", static_cast<bool (Chem::ProtonationStateStandardizer::*)(Chem::Molecule&, Chem::ProtonationStateStandardizer::Flavor)>
			 (&Chem::ProtonationStateStandardizer::standardize), (python::arg("self"), python::arg("mol"), python::arg("flavor")))
		.def("standardize", static_cast<bool (Chem::ProtonationStateStandardizer::*)(const Chem::Molecule&, Chem::Molecule&, Chem::ProtonationStateStandardizer::Flavor)>
			 (&Chem::ProtonationStateStandardizer::standardize), (python::arg("self"), python::arg("mol"), python::arg("std_mol"), python::arg("flavor")));
}
