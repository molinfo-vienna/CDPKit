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
#include "CDPL/Shape/GaussianShape.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeOverlapFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::GaussianShapeOverlapFunction, Shape::GaussianShapeOverlapFunction::SharedPointer>("GaussianShapeOverlapFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShape&, const Shape::GaussianShape&>((python::arg("self"), python::arg("ref_shape"), python::arg("ovl_shape")))
			 [python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3> >()])
		.def(python::init<const Shape::GaussianShapeOverlapFunction&>((python::arg("self"), python::arg("func")))[python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeOverlapFunction>())
		.def("assign", &Shape::GaussianShapeOverlapFunction::operator=, (python::arg("self"), python::arg("func")), python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("setShape", &Shape::GaussianShapeOverlapFunction::setShape, (python::arg("self"), python::arg("shape"), python::arg("is_ref")), python::with_custodian_and_ward<1, 2>())
		.def("getShapeFunction", &Shape::GaussianShapeOverlapFunction::getShapeFunction, (python::arg("self"), python::arg("ref")), python::return_internal_reference<>())
		.def("setMaxOrder", &Shape::GaussianShapeOverlapFunction::setMaxOrder, (python::arg("self"), python::arg("max_order")))
		.def("getMaxOrder", &Shape::GaussianShapeOverlapFunction::getMaxOrder, python::arg("self"))
		.def("setDistanceCutoff", &Shape::GaussianShapeOverlapFunction::setDistanceCutoff, (python::arg("self"), python::arg("cutoff")))
		.def("getDistanceCutoff", &Shape::GaussianShapeOverlapFunction::getDistanceCutoff, python::arg("self"))
		.def("exactCalculations", static_cast<void (Shape::GaussianShapeOverlapFunction::*)(bool)>(&Shape::GaussianShapeOverlapFunction::exactCalculations),
			 (python::arg("self"), python::arg("exact")))
		.def("exactCalculations", static_cast<bool (Shape::GaussianShapeOverlapFunction::*)() const>(&Shape::GaussianShapeOverlapFunction::exactCalculations),
			 python::arg("self"))
		.def("calcOverlap", static_cast<double (Shape::GaussianShapeOverlapFunction::*)() const>(&Shape::GaussianShapeOverlapFunction::calcOverlap),
			 python::arg("self"))
		.def("calcOverlap", static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&)>(&Shape::GaussianShapeOverlapFunction::calcOverlap),
			 (python::arg("self"), python::arg("xform")))
		.def("calcOverlapGradient", static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&, Math::Vector3DArray&)>(
				 &Shape::GaussianShapeOverlapFunction::calcOverlapGradient), (python::arg("self"), python::arg("xform"), python::arg("grad")))
		.add_property("exactCalc", static_cast<bool (Shape::GaussianShapeOverlapFunction::*)() const>(&Shape::GaussianShapeOverlapFunction::exactCalculations),
					  static_cast<void (Shape::GaussianShapeOverlapFunction::*)(bool)>(&Shape::GaussianShapeOverlapFunction::exactCalculations))
		.add_property("maxOrder", &Shape::GaussianShapeOverlapFunction::getMaxOrder, &Shape::GaussianShapeOverlapFunction::setMaxOrder)
		.add_property("distCutoff", &Shape::GaussianShapeOverlapFunction::getDistanceCutoff, &Shape::GaussianShapeOverlapFunction::setDistanceCutoff);
}
