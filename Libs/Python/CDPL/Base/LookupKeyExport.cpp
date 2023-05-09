/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LookupKeyExport.cpp 
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


#include <sstream>

#include <boost/python.hpp>

#include "CDPL/Base/LookupKey.hpp"

#include "CopyAssOp.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	std::string toString(const CDPL::Base::LookupKey& key)
	{
		std::ostringstream oss;

		oss << "CDPL.Base.LookupKey(id=" << key.getID() << ", name='" << key.getName() << "')";

		return oss.str();
	}
}


void CDPLPythonBase::exportLookupKey()
{
	using namespace boost;
	using namespace CDPL;

    python::class_<Base::LookupKey>("LookupKey", python::no_init)
		.def(python::init<const Base::LookupKey&>((python::arg("self"), python::arg("key"))))
		.def("create", &Base::LookupKey::create, python::arg("name"))
		.staticmethod("create")
		.def("getID", &Base::LookupKey::getID, python::arg("self"))    
		.def("assign", copyAssOp(&Base::LookupKey::operator=), (python::arg("self"), python::arg("key")), python::return_self<>())
		.def("getName", &Base::LookupKey::getName, python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setName", &Base::LookupKey::setName, (python::arg("self"), python::arg("name")))
		.def(ObjectIdentityCheckVisitor<Base::LookupKey>())
        .add_property("numericID", &Base::LookupKey::getID)    
        .add_property("name", python::make_function(&Base::LookupKey::getName, 
													python::return_value_policy<python::copy_const_reference>()),
					  &Base::LookupKey::setName)    
        .def_readonly("NONE", &Base::LookupKey::NONE)    
		.def("__lt__", &Base::LookupKey::operator<, (python::arg("self"), python::arg("key")))    
        .def("__eq__", &Base::LookupKey::operator==, (python::arg("self"), python::arg("key")))
        .def("__ne__", &Base::LookupKey::operator!=, (python::arg("self"), python::arg("key")))
		.def("__str__", &toString, python::arg("self"));
}
