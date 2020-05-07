/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentFunctionExport.cpp 
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

#include "CDPL/Shape/GaussianShapeAlignmentFunction.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeAlignmentFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::GaussianShapeAlignmentFunction>("GaussianShapeAlignmentFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<Shape::GaussianShapeOverlapFunction&>((python::arg("self"), python::arg("func"))) [python::with_custodian_and_ward<1, 2>()])
		.def(python::init<const Shape::GaussianShapeAlignmentFunction&>((python::arg("self"), python::arg("func")))[python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeAlignmentFunction>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::GaussianShapeAlignmentFunction::operator=), (python::arg("self"), python::arg("func")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("setQuaternionUnityDeviationPenaltyFactor", &Shape::GaussianShapeAlignmentFunction::setQuaternionUnityDeviationPenaltyFactor,
			 (python::arg("self"), python::arg("factor")))
		.def("getQuaternionUnityDeviationPenaltyFactor", &Shape::GaussianShapeAlignmentFunction::getQuaternionUnityDeviationPenaltyFactor,
			 python::arg("self"))
		.def("setOverlapFunction", &Shape::GaussianShapeAlignmentFunction::setOverlapFunction,
			 (python::arg("self"), python::arg("func")), python::with_custodian_and_ward<1, 2>())
		.def("getOverlapFunction", &Shape::GaussianShapeAlignmentFunction::getOverlapFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("__call__", static_cast<double (Shape::GaussianShapeAlignmentFunction::*)(const Shape::QuaternionTransformation&) const>(&Shape::GaussianShapeAlignmentFunction::operator()),
			 (python::arg("self"), python::arg("xform")))
		.def("__call__", static_cast<double (Shape::GaussianShapeAlignmentFunction::*)(const Shape::QuaternionTransformation&, Shape::QuaternionTransformation&)>(&Shape::GaussianShapeAlignmentFunction::operator()),
			 (python::arg("self"), python::arg("xform"), python::arg("grad")))
		.def_readonly("DEF_QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR", Shape::GaussianShapeAlignmentFunction::DEF_QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR)
		.add_property("overlapFunction",
					  python::make_function(&Shape::GaussianShapeAlignmentFunction::getOverlapFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeAlignmentFunction::setOverlapFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("quatUnityDeviationPenaltyFactor", &Shape::GaussianShapeAlignmentFunction::getQuaternionUnityDeviationPenaltyFactor,
					  &Shape::GaussianShapeAlignmentFunction::setQuaternionUnityDeviationPenaltyFactor);
}
