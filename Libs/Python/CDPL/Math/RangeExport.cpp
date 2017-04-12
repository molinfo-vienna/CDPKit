/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RangeExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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

#include "CDPL/Math/Range.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMath::exportRange()
{
	using namespace boost;
	using namespace CDPL;

	typedef Math::Range<std::size_t> RangeType;
	typedef RangeType::SizeType SizeType;

	python::class_<RangeType>("Range", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const RangeType&>((python::arg("self"), python::arg("r"))))
		.def(python::init<SizeType, SizeType>((python::arg("self"), python::arg("start"), python::arg("stop"))))
		.def("getStart", &RangeType::getStart, python::arg("self"))
		.def("getStop", &RangeType::getStop, python::arg("self"))
		.def("getSize", &RangeType::getSize, python::arg("self"))
		.def("isEmpty", &RangeType::isEmpty, python::arg("self"))
		.def("getIndex", &RangeType::operator(), (python::arg("self"), python::arg("i")))
		.def("assign", CDPLPythonBase::copyAssOp(&RangeType::operator=), (python::arg("self"), python::arg("r")), python::return_self<>())
		.def("swap", static_cast<void (RangeType::*)(RangeType&)>(&RangeType::swap), (python::arg("self"), python::arg("r")))
		.def("__eq__", &RangeType::operator==, (python::arg("self"), python::arg("r")))
		.def("__ne__", &RangeType::operator!=, (python::arg("self"), python::arg("r")))
		.def("__call__", &RangeType::operator(), (python::arg("self"), python::arg("i")))
		.def("__getitem__", &RangeType::operator(), (python::arg("self"), python::arg("i")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<RangeType>())
		.add_property("start", &RangeType::getStart)
		.add_property("stop", &RangeType::getStop)
		.add_property("size", &RangeType::getSize);

	python::def("range", &Math::range, (python::arg("start"), python::arg("stop")));
}
