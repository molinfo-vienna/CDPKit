/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ArrayExport.cpp 
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

#include "CDPL/Util/Array.hpp"

#include "ArrayVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonUtil::exportArrays()
{
	using namespace boost;
	using namespace CDPL;
	
	python::class_<Util::UIArray, Util::UIArray::SharedPointer>("UIArray", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Util::UIArray&>((python::arg("self"), python::arg("array"))))
		.def(ArrayVisitor<Util::UIArray, 
			 python::return_value_policy<python::return_by_value>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("__eq__", &Util::UIArray::operator==, (python::arg("self"), python::arg("array")))
		.def("__ne__", &Util::UIArray::operator!=, (python::arg("self"), python::arg("array")))
		.def("__le__", &Util::UIArray::operator<=, (python::arg("self"), python::arg("array")))
		.def("__ge__", &Util::UIArray::operator>=, (python::arg("self"), python::arg("array")))
		.def("__lt__", &Util::UIArray::operator<, (python::arg("self"), python::arg("array")))
		.def("__gt__", &Util::UIArray::operator>, (python::arg("self"), python::arg("array")));

	python::class_<Util::STArray, Util::STArray::SharedPointer>("STArray", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Util::STArray&>((python::arg("self"), python::arg("array"))))
		.def(ArrayVisitor<Util::STArray, 
			 python::return_value_policy<python::return_by_value>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("__eq__", &Util::STArray::operator==, (python::arg("self"), python::arg("array")))
		.def("__ne__", &Util::STArray::operator!=, (python::arg("self"), python::arg("array")))
		.def("__le__", &Util::STArray::operator<=, (python::arg("self"), python::arg("array")))
		.def("__ge__", &Util::STArray::operator>=, (python::arg("self"), python::arg("array")))
		.def("__lt__", &Util::STArray::operator<, (python::arg("self"), python::arg("array")))
		.def("__gt__", &Util::STArray::operator>, (python::arg("self"), python::arg("array")));

	python::class_<Util::DArray, Util::DArray::SharedPointer>("DArray", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Util::DArray&>((python::arg("self"), python::arg("array"))))
		.def(ArrayVisitor<Util::DArray, 
			 python::return_value_policy<python::return_by_value>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("__eq__", &Util::DArray::operator==, (python::arg("self"), python::arg("array")))
		.def("__ne__", &Util::DArray::operator!=, (python::arg("self"), python::arg("array")))
		.def("__le__", &Util::DArray::operator<=, (python::arg("self"), python::arg("array")))
		.def("__ge__", &Util::DArray::operator>=, (python::arg("self"), python::arg("array")))
		.def("__lt__", &Util::DArray::operator<, (python::arg("self"), python::arg("array")))
		.def("__gt__", &Util::DArray::operator>, (python::arg("self"), python::arg("array")));

	python::class_<Util::SArray, Util::SArray::SharedPointer>("SArray", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Util::SArray&>((python::arg("self"), python::arg("array"))))
		.def(ArrayVisitor<Util::SArray, 
			 python::return_value_policy<python::return_by_value>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("__eq__", &Util::SArray::operator==, (python::arg("self"), python::arg("array")))
		.def("__ne__", &Util::SArray::operator!=, (python::arg("self"), python::arg("array")))
		.def("__le__", &Util::SArray::operator<=, (python::arg("self"), python::arg("array")))
		.def("__ge__", &Util::SArray::operator>=, (python::arg("self"), python::arg("array")))
		.def("__lt__", &Util::SArray::operator<, (python::arg("self"), python::arg("array")))
		.def("__gt__", &Util::SArray::operator>, (python::arg("self"), python::arg("array")));

	python::class_<Util::BitSetArray, Util::BitSetArray::SharedPointer>("BitSetArray", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Util::BitSetArray&>((python::arg("self"), python::arg("array"))))
		.def(ArrayVisitor<Util::BitSetArray, 
			 python::return_value_policy<python::return_by_value>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("__eq__", &Util::BitSetArray::operator==, (python::arg("self"), python::arg("array")))
		.def("__ne__", &Util::BitSetArray::operator!=, (python::arg("self"), python::arg("array")))
		.def("__le__", &Util::BitSetArray::operator<=, (python::arg("self"), python::arg("array")))
		.def("__ge__", &Util::BitSetArray::operator>=, (python::arg("self"), python::arg("array")))
		.def("__lt__", &Util::BitSetArray::operator<, (python::arg("self"), python::arg("array")))
		.def("__gt__", &Util::BitSetArray::operator>, (python::arg("self"), python::arg("array")));
}
