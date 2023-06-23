/* 
 * DGConstraintGeneratorSettingsExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/DGConstraintGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportDGConstraintGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (ConfGen::DGConstraintGeneratorSettings::*SetBoolFunc)(bool);
	typedef bool (ConfGen::DGConstraintGeneratorSettings::*GetBoolFunc)() const;

	python::class_<ConfGen::DGConstraintGeneratorSettings>("DGConstraintGeneratorSettings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::DGConstraintGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::DGConstraintGeneratorSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::DGConstraintGeneratorSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("excludeHydrogens", SetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::excludeHydrogens), 
			 (python::arg("self"), python::arg("exclude")))
		.def("excludeHydrogens", GetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::excludeHydrogens), 
			 python::arg("self"))
		.def("regardAtomConfiguration", SetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardAtomConfiguration), 
			 (python::arg("self"), python::arg("regard")))
		.def("regardAtomConfiguration", GetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardAtomConfiguration), 
			 python::arg("self"))
		.def("regardBondConfiguration", SetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardBondConfiguration), 
			 (python::arg("self"), python::arg("regard")))
		.def("regardBondConfiguration", GetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardBondConfiguration), 
			 python::arg("self"))
		.def_readonly("DEFAULT", ConfGen::DGConstraintGeneratorSettings::DEFAULT)
		.add_property("exclHydrogens", GetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::excludeHydrogens), 
					  SetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::excludeHydrogens))
		.add_property("regardAtomConfig", GetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardAtomConfiguration), 
					  SetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardAtomConfiguration))
		.add_property("regardBondConfig", GetBoolFunc(&ConfGen::DGConstraintGeneratorSettings::regardBondConfiguration), 
					  SetBoolFunc( &ConfGen::DGConstraintGeneratorSettings::regardBondConfiguration));
}
