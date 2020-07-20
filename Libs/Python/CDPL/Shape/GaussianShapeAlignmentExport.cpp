/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentExport.cpp 
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

#include "CDPL/Shape/GaussianShapeAlignment.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeAlignment()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::GaussianShapeAlignment::*SetBoolFunc)(bool);
	typedef bool (Shape::GaussianShapeAlignment::*GetBoolFunc)() const;

    python::scope scope = python::class_<Shape::GaussianShapeAlignment, Shape::GaussianShapeAlignment::SharedPointer, boost::noncopyable>(
		"GaussianShapeAlignment", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShape&>((python::arg("self"), python::arg("ref_shape"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeAlignment>())
		.def("setOverlapFunction", &Shape::GaussianShapeAlignment::setOverlapFunction,
			 (python::arg("self"), python::arg("func")), python::with_custodian_and_ward<1, 2>())
		.def("getOverlapFunction", &Shape::GaussianShapeAlignment::getOverlapFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("getDefaultOverlapFunction", static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeAlignment::*)()>
			 (&Shape::GaussianShapeAlignment::getDefaultOverlapFunction),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setReference", &Shape::GaussianShapeAlignment::setReference,
			 (python::arg("self"), python::arg("shape")))
		.def("setReferenceSet", &Shape::GaussianShapeAlignment::setReferenceSet,
			 (python::arg("self"), python::arg("shapes")))
	
		.def("setStartGenerator", &Shape::GaussianShapeAlignment::setStartGenerator,
			 (python::arg("self"), python::arg("gen")), python::with_custodian_and_ward<1, 2>())
		.def("getStartGenerator", &Shape::GaussianShapeAlignment::getStartGenerator,
			 python::arg("self"), python::return_internal_reference<>())
		.def("getDefaultStartGenerator", static_cast<Shape::PrincipalAxesAlignmentStartGenerator& (Shape::GaussianShapeAlignment::*)()>
			 (&Shape::GaussianShapeAlignment::getDefaultStartGenerator),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setColorMatchFunction", &Shape::GaussianShapeAlignment::setColorMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getColorMatchFunction", &Shape::GaussianShapeAlignment::getColorMatchFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setColorFilterFunction", &Shape::GaussianShapeAlignment::setColorFilterFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getColorFilterFunction", &Shape::GaussianShapeAlignment::getColorFilterFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setMaxNumRefinementIterations", &Shape::GaussianShapeAlignment::setMaxNumRefinementIterations,
			 (python::arg("self"), python::arg("max_iter")))
		.def("getMaxNumRefinementIterations", &Shape::GaussianShapeAlignment::getMaxNumRefinementIterations,
			 python::arg("self"))
		.def("setRefinementStopGradient", &Shape::GaussianShapeAlignment::setRefinementStopGradient,
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getRefinementStopGradient", &Shape::GaussianShapeAlignment::getRefinementStopGradient,
			 python::arg("self"))
		.def("refineStartingPoses", SetBoolFunc(&Shape::GaussianShapeAlignment::refineStartingPoses),
			 (python::arg("self"), python::arg("refine")))
		.def("refineStartingPoses", GetBoolFunc(&Shape::GaussianShapeAlignment::refineStartingPoses),
			 python::arg("self"))
		.def("calcSelfOverlaps", SetBoolFunc(&Shape::GaussianShapeAlignment::calcSelfOverlaps), 
			 (python::arg("self"), python::arg("calc")))
		.def("calcColorSelfOverlaps", SetBoolFunc(&Shape::GaussianShapeAlignment::calcColorSelfOverlaps),
			 (python::arg("self"), python::arg("calc")))
		.def("align", static_cast<bool (Shape::GaussianShapeAlignment::*)(const Shape::GaussianShape&)>(&Shape::GaussianShapeAlignment::align), 
			 (python::arg("self"), python::arg("shape")))
		.def("getNumResults", &Shape::GaussianShapeAlignment::getNumResults, python::arg("self"))
		.def("__len__", &Shape::GaussianShapeAlignment::getNumResults, python::arg("self"))
		.def("getResult", &Shape::GaussianShapeAlignment::getResult,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", &Shape::GaussianShapeAlignment::getResult,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def_readonly("DEF_REFINEMENT_STOP_GRADIENT", Shape::GaussianShapeFunctionAlignment::DEF_REFINEMENT_STOP_GRADIENT)
		.def_readonly("DEF_MAX_REFINEMENT_ITERATIONS", Shape::GaussianShapeFunctionAlignment::DEF_MAX_REFINEMENT_ITERATIONS)
		.add_property("numResults", &Shape::GaussianShapeAlignment::getNumResults)
		.add_property("overlapFunction",
					  python::make_function(&Shape::GaussianShapeAlignment::getOverlapFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeAlignment::setOverlapFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defOverlapFunction",
					  python::make_function(static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeAlignment::*)()>
											(&Shape::GaussianShapeAlignment::getDefaultOverlapFunction),
											python::return_internal_reference<>()))
		.add_property("startGenerator",
					  python::make_function(&Shape::GaussianShapeAlignment::getStartGenerator,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeAlignment::setStartGenerator,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defStartGenerator",
					  python::make_function(static_cast<Shape::PrincipalAxesAlignmentStartGenerator& (Shape::GaussianShapeAlignment::*)()>
											(&Shape::GaussianShapeAlignment::getDefaultStartGenerator),
											python::return_internal_reference<>()))
		.add_property("colorMatchFunction", python::make_function(&Shape::GaussianShapeAlignment::getColorMatchFunction,
																  python::return_internal_reference<>()),
					  &Shape::GaussianShapeAlignment::setColorMatchFunction)
		.add_property("colorFilterFunction", python::make_function(&Shape::GaussianShapeAlignment::getColorFilterFunction,
																   python::return_internal_reference<>()),
					  &Shape::GaussianShapeAlignment::setColorFilterFunction)
		.add_property("maxNumRefinementIterations", &Shape::GaussianShapeAlignment::getMaxNumRefinementIterations,
					  &Shape::GaussianShapeAlignment::setMaxNumRefinementIterations)
		.add_property("refinementStopGradient", &Shape::GaussianShapeAlignment::getRefinementStopGradient,
					  &Shape::GaussianShapeAlignment::setRefinementStopGradient)
		.add_property("refineStartPoses", GetBoolFunc(&Shape::GaussianShapeAlignment::refineStartingPoses),
					  SetBoolFunc(&Shape::GaussianShapeAlignment::refineStartingPoses));

	python::class_<Shape::GaussianShapeAlignment::Result>("Result", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("getTransform", &Shape::GaussianShapeAlignment::Result::getTransform, python::arg("self"), python::return_internal_reference<>())
		.def("getOverlap", &Shape::GaussianShapeAlignment::Result::getOverlap, python::arg("self"))
		.def("getColorOverlap", &Shape::GaussianShapeAlignment::Result::getColorOverlap, python::arg("self"))
		.add_property("transform", python::make_function(&Shape::GaussianShapeAlignment::Result::getTransform, python::return_internal_reference<>()))
		.add_property("overlap", &Shape::GaussianShapeAlignment::Result::getOverlap)
		.add_property("colorOverlap", &Shape::GaussianShapeAlignment::Result::getColorOverlap);
}
