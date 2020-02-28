/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ValueKeyExport.cpp 
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

#include "CDPL/Base/ValueKey.hpp"

#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


void CDPLPythonBase::exportValueKey()
{
	using namespace boost;
	using namespace CDPL;

    python::class_<Base::ValueKey>("ValueKey", python::no_init)
		.def(python::init<const Base::ValueKey&>((python::arg("self"), python::arg("key"))))
		.def("create", &Base::ValueKey::create, python::arg("name"))
		.staticmethod("create")
		.def("getID", &Base::ValueKey::getID, python::arg("self"))    
		.def("assign", &Base::ValueKey::operator=, (python::arg("self"), python::arg("key")), python::return_self<>())
		.def("getName", &Base::ValueKey::getName, python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setName", &Base::ValueKey::setName, (python::arg("self"), python::arg("name")))
		.def(ObjectIdentityCheckVisitor<Base::ValueKey>())
        .add_property("numericID", &Base::ValueKey::getID)    
        .add_property("name", python::make_function(&Base::ValueKey::getName, 
													python::return_value_policy<python::copy_const_reference>()),
					  &Base::ValueKey::setName)    
        .def_readonly("NONE", Base::ValueKey::NONE)    
		.def("__lt__", &Base::ValueKey::operator<, (python::arg("self"), python::arg("key")))    
        .def("__eq__", &Base::ValueKey::operator==, (python::arg("self"), python::arg("key")))
        .def("__ne__", &Base::ValueKey::operator!=, (python::arg("self"), python::arg("key")))
		.def("__str__", &Base::ValueKey::getName, python::arg("self"), python::return_value_policy<python::copy_const_reference>());
}
