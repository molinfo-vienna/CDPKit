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
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeFunctionAlignment()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::GaussianShapeFunctionAlignment::*SetBoolFunc)(bool);
	typedef bool (Shape::GaussianShapeFunctionAlignment::*GetBoolFunc)() const;

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
		.def("getDefaultOverlapFunction", static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeFunctionAlignment::*)()>
			 (&Shape::GaussianShapeFunctionAlignment::getDefaultOverlapFunction),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setReferenceShapeFunction", &Shape::GaussianShapeFunctionAlignment::setReferenceShapeFunction,
			 (python::arg("self"), python::arg("func"), python::arg("sym_class")), python::with_custodian_and_ward<1, 2>())
		.def("getReferenceShapeFunction", &Shape::GaussianShapeFunctionAlignment::getReferenceShapeFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setStartGenerator", &Shape::GaussianShapeFunctionAlignment::setStartGenerator,
			 (python::arg("self"), python::arg("gen")), python::with_custodian_and_ward<1, 2>())
		.def("getStartGenerator", &Shape::GaussianShapeFunctionAlignment::getStartGenerator,
			 python::arg("self"), python::return_internal_reference<>())
		.def("getDefaultStartGenerator", static_cast<Shape::PrincipalAxesAlignmentStartGenerator& (Shape::GaussianShapeFunctionAlignment::*)()>
			 (&Shape::GaussianShapeFunctionAlignment::getDefaultStartGenerator),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setColorMatchFunction", &Shape::GaussianShapeFunctionAlignment::setColorMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getColorMatchFunction", &Shape::GaussianShapeFunctionAlignment::getColorMatchFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setColorFilterFunction", &Shape::GaussianShapeFunctionAlignment::setColorFilterFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getColorFilterFunction", &Shape::GaussianShapeFunctionAlignment::getColorFilterFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setMaxNumRefinementIterations", &Shape::GaussianShapeFunctionAlignment::setMaxNumRefinementIterations,
			 (python::arg("self"), python::arg("max_iter")))
		.def("getMaxNumRefinementIterations", &Shape::GaussianShapeFunctionAlignment::getMaxNumRefinementIterations,
			 python::arg("self"))
		.def("setRefinementStopGradient", &Shape::GaussianShapeFunctionAlignment::setRefinementStopGradient,
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getRefinementStopGradient", &Shape::GaussianShapeFunctionAlignment::getRefinementStopGradient,
			 python::arg("self"))
		.def("refineStartingPoses", SetBoolFunc(&Shape::GaussianShapeFunctionAlignment::refineStartingPoses),
			 (python::arg("self"), python::arg("refine")))
		.def("refineStartingPoses", GetBoolFunc(&Shape::GaussianShapeFunctionAlignment::refineStartingPoses),
			 python::arg("self"))
		.def("setupReferenceShape", &Shape::GaussianShapeFunctionAlignment::setupReferenceShape,
			 (python::arg("self"), python::arg("shape"), python::arg("shape_func"), python::arg("xform")))
		.def("setupAlignedShape", &Shape::GaussianShapeFunctionAlignment::setupAlignedShape, 
			 (python::arg("self"), python::arg("shape"), python::arg("shape_func"), python::arg("xform")))
		.def("calcSelfOverlap", &Shape::GaussianShapeFunctionAlignment::calcSelfOverlap, (python::arg("self"), python::arg("func")))
		.def("calcColorSelfOverlap", &Shape::GaussianShapeFunctionAlignment::calcColorSelfOverlap, (python::arg("self"), python::arg("func")))
		.def("align", &Shape::GaussianShapeFunctionAlignment::align, 
			 (python::arg("self"), python::arg("func"), python::arg("sym_class"), python::arg("calc_col_overlap") = false))
		.def("getNumResults", &Shape::GaussianShapeFunctionAlignment::getNumResults, python::arg("self"))
		.def("__len__", &Shape::GaussianShapeFunctionAlignment::getNumResults, python::arg("self"))
		.def("getResult", &Shape::GaussianShapeFunctionAlignment::getResult,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", &Shape::GaussianShapeFunctionAlignment::getResult,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def_readonly("DEF_REFINEMENT_STOP_GRADIENT", Shape::GaussianShapeFunctionAlignment::DEF_REFINEMENT_STOP_GRADIENT)
		.def_readonly("DEF_MAX_REFINEMENT_ITERATIONS", Shape::GaussianShapeFunctionAlignment::DEF_MAX_REFINEMENT_ITERATIONS)
		.add_property("numResults", &Shape::GaussianShapeFunctionAlignment::getNumResults)
		.add_property("overlapFunction",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getOverlapFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setOverlapFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defOverlapFunction",
					  python::make_function(static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeFunctionAlignment::*)()>
											(&Shape::GaussianShapeFunctionAlignment::getDefaultOverlapFunction),
											python::return_internal_reference<>()))
		.add_property("refShapeFunction",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getReferenceShapeFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setReferenceShapeFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("startGenerator",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getStartGenerator,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setStartGenerator,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defStartGenerator",
					  python::make_function(static_cast<Shape::PrincipalAxesAlignmentStartGenerator& (Shape::GaussianShapeFunctionAlignment::*)()>
											(&Shape::GaussianShapeFunctionAlignment::getDefaultStartGenerator),
											python::return_internal_reference<>()))
		.add_property("colorMatchFunction", python::make_function(&Shape::GaussianShapeFunctionAlignment::getColorMatchFunction,
																  python::return_internal_reference<>()),
					  &Shape::GaussianShapeFunctionAlignment::setColorMatchFunction)
		.add_property("colorFilterFunction", python::make_function(&Shape::GaussianShapeFunctionAlignment::getColorFilterFunction,
																   python::return_internal_reference<>()),
					  &Shape::GaussianShapeFunctionAlignment::setColorFilterFunction)
		.add_property("maxNumRefinementIterations", &Shape::GaussianShapeFunctionAlignment::getMaxNumRefinementIterations,
					  &Shape::GaussianShapeFunctionAlignment::setMaxNumRefinementIterations)
		.add_property("refinementStopGradient", &Shape::GaussianShapeFunctionAlignment::getRefinementStopGradient,
					  &Shape::GaussianShapeFunctionAlignment::setRefinementStopGradient)
		.add_property("refineStartPoses", GetBoolFunc(&Shape::GaussianShapeFunctionAlignment::refineStartingPoses),
					  SetBoolFunc(&Shape::GaussianShapeFunctionAlignment::refineStartingPoses));

	python::class_<Shape::GaussianShapeFunctionAlignment::Result>("Result", python::no_init)
		.def(python::init<const Math::Matrix4D&, double, double>((python::arg("self"), python::arg("transform"), python::arg("overlap"), python::arg("col_overlap"))))
		.def("getTransform", &Shape::GaussianShapeFunctionAlignment::Result::getTransform, python::arg("self"), python::return_internal_reference<>())
		.def("getOverlap", &Shape::GaussianShapeFunctionAlignment::Result::getOverlap, python::arg("self"))
		.def("getColorOverlap", &Shape::GaussianShapeFunctionAlignment::Result::getColorOverlap, python::arg("self"))
		.add_property("transform", python::make_function(&Shape::GaussianShapeFunctionAlignment::Result::getTransform, python::return_internal_reference<>()))
		.add_property("overlap", &Shape::GaussianShapeFunctionAlignment::Result::getOverlap)
		.add_property("colorOverlap", &Shape::GaussianShapeFunctionAlignment::Result::getColorOverlap);
}
