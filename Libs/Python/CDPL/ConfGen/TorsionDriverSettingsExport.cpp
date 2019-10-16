/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriverSettingsExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/TorsionDriverSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportTorsionDriverSettings()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (ConfGen::TorsionDriverSettings::*SetBoolFunc)(bool);
	typedef bool (ConfGen::TorsionDriverSettings::*GetBoolFunc)() const;

	python::class_<ConfGen::TorsionDriverSettings>("TorsionDriverSettings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::TorsionDriverSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionDriverSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionDriverSettings::operator=), 
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("enumerateHeteroHydrogenRotors", SetBoolFunc(&ConfGen::TorsionDriverSettings::enumerateHeteroHydrogenRotors), 
			 (python::arg("self"), python::arg("enumerate")))
		.def("enumerateHeteroHydrogenRotors", GetBoolFunc(&ConfGen::TorsionDriverSettings::enumerateHeteroHydrogenRotors), 
			 python::arg("self"))
		.def("setForceFieldType", &ConfGen::TorsionDriverSettings::setForceFieldType, 
			 (python::arg("self"), python::arg("type")))
		.def("getForceFieldType", &ConfGen::TorsionDriverSettings::getForceFieldType, 
			 python::arg("self"))
		.def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::TorsionDriverSettings::strictForceFieldParameterization), 
			 (python::arg("self"), python::arg("strict")))
		.def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::TorsionDriverSettings::strictForceFieldParameterization), 
			 python::arg("self"))
		.def("setTorsionLibrary", &ConfGen::TorsionDriverSettings::setTorsionLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getTorsionLibrary", &ConfGen::TorsionDriverSettings::getTorsionLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def_readonly("DEFAULT", ConfGen::TorsionDriverSettings::DEFAULT)
		.add_property("enumHeteroHRotors", GetBoolFunc(&ConfGen::TorsionDriverSettings::enumerateHeteroHydrogenRotors),
					  SetBoolFunc(&ConfGen::TorsionDriverSettings::enumerateHeteroHydrogenRotors))
		.add_property("forceFieldType", &ConfGen::TorsionDriverSettings::getForceFieldType, 
					  &ConfGen::TorsionDriverSettings::setForceFieldType)
		.add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::TorsionDriverSettings::strictForceFieldParameterization), 
					  SetBoolFunc(&ConfGen::TorsionDriverSettings::strictForceFieldParameterization))
		.add_property("torsionLibrary", 
					  python::make_function(&ConfGen::TorsionDriverSettings::getTorsionLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionDriverSettings::setTorsionLibrary);
}
