/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunctionExport.cpp 
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

#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeOverlapFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::GaussianShapeOverlapFunction, Shape::GaussianShapeOverlapFunction::SharedPointer>("GaussianShapeOverlapFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShapeFunction&, const Shape::GaussianShapeFunction&>
			 ((python::arg("self"), python::arg("ref_shape_func"), python::arg("ovl_shape_func")))
			 [python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3> >()])
		.def(python::init<const Shape::GaussianShapeOverlapFunction&>((python::arg("self"), python::arg("func")))[python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeOverlapFunction>())
		.def("assign", &Shape::GaussianShapeOverlapFunction::operator=, (python::arg("self"), python::arg("func")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("setShapeFunction", &Shape::GaussianShapeOverlapFunction::setShapeFunction,
			 (python::arg("self"), python::arg("func"), python::arg("is_ref")), python::with_custodian_and_ward<1, 2>())
		.def("getShapeFunction", &Shape::GaussianShapeOverlapFunction::getShapeFunction,
			 (python::arg("self"), python::arg("ref")), python::return_internal_reference<>())
		.def("enableProximityOptimization", &Shape::GaussianShapeOverlapFunction::enableProximityOptimization, (python::arg("self"), python::arg("enable")))
		.def("proximityOptimizationEnabled", &Shape::GaussianShapeOverlapFunction::proximityOptimizationEnabled, python::arg("self"))
		.def("useFastExpFunction", &Shape::GaussianShapeOverlapFunction::useFastExpFunction, (python::arg("self"), python::arg("use")))
		.def("fastExpFunctionUsed", &Shape::GaussianShapeOverlapFunction::fastExpFunctionUsed, python::arg("self"))
		.def("calcSelfOverlap", &Shape::GaussianShapeOverlapFunction::calcSelfOverlap, (python::arg("self"), python::arg("ref")))
		.def("calcOverlap", static_cast<double (Shape::GaussianShapeOverlapFunction::*)() const>(&Shape::GaussianShapeOverlapFunction::calcOverlap),
			 python::arg("self"))
		.def("calcOverlap", static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&)>(&Shape::GaussianShapeOverlapFunction::calcOverlap),
			 (python::arg("self"), python::arg("xform")))
		.def("calcOverlapGradient", static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&, Math::Vector3DArray&)>(
				 &Shape::GaussianShapeOverlapFunction::calcOverlapGradient), (python::arg("self"), python::arg("xform"), python::arg("grad")))
		.add_property("proximityOptimization", &Shape::GaussianShapeOverlapFunction::proximityOptimizationEnabled, &Shape::GaussianShapeOverlapFunction::enableProximityOptimization)
		.add_property("fastExpFunction", &Shape::GaussianShapeOverlapFunction::fastExpFunctionUsed, &Shape::GaussianShapeOverlapFunction::useFastExpFunction);
}
