/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SliceExport.cpp 
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

#include "CDPL/Math/Slice.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMath::exportSlice()
{
	using namespace boost;
	using namespace CDPL;

	typedef Math::Slice<std::size_t, std::ptrdiff_t> SliceType;
	typedef SliceType::SizeType SizeType;
	typedef SliceType::DifferenceType DifferenceType;

	python::class_<SliceType>("Slice", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const SliceType&>((python::arg("self"), python::arg("s"))))
		.def(python::init<SizeType, DifferenceType, SizeType>(
				 (python::arg("self"), python::arg("start"), python::arg("stride"), python::arg("size"))))
		.def("getStart", &SliceType::getStart, python::arg("self"))
		.def("getStride", &SliceType::getStride, python::arg("self"))
		.def("getSize", &SliceType::getSize, python::arg("self"))
		.def("isEmpty", &SliceType::isEmpty, python::arg("self"))
		.def("getIndex", &SliceType::operator(), (python::arg("self"), python::arg("i")))
		.def("assign", CDPLPythonBase::copyAssOp(&SliceType::operator=), (python::arg("self"), python::arg("s")), python::return_self<>())
		.def("swap", static_cast<void (SliceType::*)(SliceType&)>(&SliceType::swap), (python::arg("self"), python::arg("s")))
		.def("__eq__", &SliceType::operator==, (python::arg("self"), python::arg("s")))
		.def("__ne__", &SliceType::operator!=, (python::arg("self"), python::arg("s")))
		.def("__call__", &SliceType::operator(), (python::arg("self"), python::arg("i")))
		.def("__getitem__", &SliceType::operator(), (python::arg("self"), python::arg("i")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<SliceType>())
		.add_property("start", &SliceType::getStart)
		.add_property("stride", &SliceType::getStride)
		.add_property("size", &SliceType::getSize);

	python::def("slice", &Math::slice, (python::arg("start"), python::arg("stride"), python::arg("size")));
}
