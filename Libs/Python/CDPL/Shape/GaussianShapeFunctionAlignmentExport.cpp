/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctionAlignmentExport.cpp 
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

#include "CDPL/Shape/GaussianShapeFunctionAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeFunctionAlignment()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Shape::GaussianShapeFunctionAlignment, Shape::GaussianShapeFunctionAlignment::SharedPointer, boost::noncopyable>(
		"GaussianShapeFunctionAlignment", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShapeFunction&, unsigned int>((python::arg("self"), python::arg("ref_shape_func"), python::arg("sym_class")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeFunctionAlignment>())
		.def("setOverlapFunction", &Shape::GaussianShapeFunctionAlignment::setOverlapFunction,
			 (python::arg("self"), python::arg("func")), python::with_custodian_and_ward<1, 2>())
		.def("getOverlapFunction", &Shape::GaussianShapeFunctionAlignment::getOverlapFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setReferenceShapeFunction", &Shape::GaussianShapeFunctionAlignment::setReferenceShapeFunction,
			 (python::arg("self"), python::arg("func"), python::arg("sym_class")), python::with_custodian_and_ward<1, 2>())
		.def("getReferenceShapeFunction", &Shape::GaussianShapeFunctionAlignment::getReferenceShapeFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setStartGenerator", &Shape::GaussianShapeFunctionAlignment::setStartGenerator,
			 (python::arg("self"), python::arg("gen")), python::with_custodian_and_ward<1, 2>())
		.def("getStartGenerator", &Shape::GaussianShapeFunctionAlignment::getStartGenerator,
			 python::arg("self"), python::return_internal_reference<>())
		.def("align", &Shape::GaussianShapeFunctionAlignment::align, (python::arg("self"), python::arg("func"), python::arg("sym_class")))
		.def("getNumResults", &Shape::GaussianShapeFunctionAlignment::getNumResults, python::arg("self"))
		.def("__len__", &Shape::GaussianShapeFunctionAlignment::getNumResults, python::arg("self"))
		.def("getResult", &Shape::GaussianShapeFunctionAlignment::getResult,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", &Shape::GaussianShapeFunctionAlignment::getResult,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.add_property("numResults", &Shape::GaussianShapeFunctionAlignment::getNumResults)
		.add_property("overlapFunction",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getOverlapFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setOverlapFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("refShapeFunction",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getReferenceShapeFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setReferenceShapeFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("startGenerator",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getStartGenerator,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setStartGenerator,
											python::with_custodian_and_ward<1, 2>()));

	python::class_<Shape::GaussianShapeFunctionAlignment::Result>("Result", python::no_init)
		.def(python::init<const Math::Matrix4D&, double>((python::arg("self"), python::arg("transform"), python::arg("overlap"))))
		.def("getTransform", &Shape::GaussianShapeFunctionAlignment::Result::getTransform, python::arg("self"), python::return_internal_reference<>())
		.def("getOverlap", &Shape::GaussianShapeFunctionAlignment::Result::getOverlap, python::arg("self"))
		.add_property("transform", python::make_function(&Shape::GaussianShapeFunctionAlignment::Result::getTransform, python::return_internal_reference<>()))
		.add_property("overlap", &Shape::GaussianShapeFunctionAlignment::Result::getOverlap);
}
