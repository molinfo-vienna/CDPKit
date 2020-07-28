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
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeFunctionAlignment()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::GaussianShapeFunctionAlignment::*SetBoolFunc)(bool);
	typedef bool (Shape::GaussianShapeFunctionAlignment::*GetBoolFunc)() const;

    python::class_<Shape::GaussianShapeFunctionAlignment, Shape::GaussianShapeFunctionAlignment::SharedPointer, boost::noncopyable>(
		"GaussianShapeFunctionAlignment", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShapeFunction&, unsigned int>((python::arg("self"), python::arg("ref_func"), python::arg("sym_class")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeFunctionAlignment>())
		.def("setOverlapFunction", &Shape::GaussianShapeFunctionAlignment::setOverlapFunction,
			 (python::arg("self"), python::arg("func")), python::with_custodian_and_ward<1, 2>())
		.def("getOverlapFunction", &Shape::GaussianShapeFunctionAlignment::getOverlapFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("getDefaultOverlapFunction", static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeFunctionAlignment::*)()>
			 (&Shape::GaussianShapeFunctionAlignment::getDefaultOverlapFunction),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setReference", &Shape::GaussianShapeFunctionAlignment::setReference,
			 (python::arg("self"), python::arg("func"), python::arg("sym_class")), python::with_custodian_and_ward<1, 2>())
		.def("getReference", &Shape::GaussianShapeFunctionAlignment::getReference,
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
		.def("setMaxNumOptimizationIterations", &Shape::GaussianShapeFunctionAlignment::setMaxNumOptimizationIterations,
			 (python::arg("self"), python::arg("max_iter")))
		.def("getMaxNumOptimizationIterations", &Shape::GaussianShapeFunctionAlignment::getMaxNumOptimizationIterations,
			 python::arg("self"))
		.def("setOptimizationStopGradient", &Shape::GaussianShapeFunctionAlignment::setOptimizationStopGradient,
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getOptimizationStopGradient", &Shape::GaussianShapeFunctionAlignment::getOptimizationStopGradient,
			 python::arg("self"))
		.def("optimizeOverlap", SetBoolFunc(&Shape::GaussianShapeFunctionAlignment::optimizeOverlap),
			 (python::arg("self"), python::arg("optimize")))
		.def("optimizeOverlap", GetBoolFunc(&Shape::GaussianShapeFunctionAlignment::optimizeOverlap),
			 python::arg("self"))
		.def("rigorousOptimization", SetBoolFunc(&Shape::GaussianShapeFunctionAlignment::rigorousOptimization),
			 (python::arg("self"), python::arg("rigorous")))
		.def("rigorousOptimization", GetBoolFunc(&Shape::GaussianShapeFunctionAlignment::rigorousOptimization),
			 python::arg("self"))
		.def("setupReference", &Shape::GaussianShapeFunctionAlignment::setupReference,
			 (python::arg("self"), python::arg("func"), python::arg("xform")))
		.def("setupAligned", &Shape::GaussianShapeFunctionAlignment::setupAligned, 
			 (python::arg("self"), python::arg("func"), python::arg("xform")))
		.def("calcSelfOverlap", &Shape::GaussianShapeFunctionAlignment::calcSelfOverlap, (python::arg("self"), python::arg("calc")))
		.def("calcColorSelfOverlap", &Shape::GaussianShapeFunctionAlignment::calcColorSelfOverlap, (python::arg("self"), python::arg("calc")))
		.def("align", &Shape::GaussianShapeFunctionAlignment::align, 
			 (python::arg("self"), python::arg("func"), python::arg("sym_class"), python::arg("calc_col_overlap") = false))
		.def("getTransform", &Shape::GaussianShapeFunctionAlignment::getTransform, python::arg("self"), python::return_internal_reference<>())
		.def("getOverlap", &Shape::GaussianShapeFunctionAlignment::getOverlap, python::arg("self"))
		.def("getColorOverlap", &Shape::GaussianShapeFunctionAlignment::getColorOverlap, python::arg("self"))
		.def_readonly("DEF_OPTIMIZATION_STOP_GRADIENT", Shape::GaussianShapeFunctionAlignment::DEF_OPTIMIZATION_STOP_GRADIENT)
		.def_readonly("DEF_MAX_OPTIMIZATION_ITERATIONS", Shape::GaussianShapeFunctionAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS)
		.add_property("transform", python::make_function(&Shape::GaussianShapeFunctionAlignment::getTransform, python::return_internal_reference<>()))
		.add_property("overlap", &Shape::GaussianShapeFunctionAlignment::getOverlap)
		.add_property("colorOverlap", &Shape::GaussianShapeFunctionAlignment::getColorOverlap)
		.add_property("overlapFunction",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getOverlapFunction,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setOverlapFunction,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defaultOverlapFunction",
					  python::make_function(static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeFunctionAlignment::*)()>
											(&Shape::GaussianShapeFunctionAlignment::getDefaultOverlapFunction),
											python::return_internal_reference<>()))
		.add_property("referenceShapeFunction",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getReference,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setReference,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("startGenerator",
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::getStartGenerator,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeFunctionAlignment::setStartGenerator,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defaultStartGenerator",
					  python::make_function(static_cast<Shape::PrincipalAxesAlignmentStartGenerator& (Shape::GaussianShapeFunctionAlignment::*)()>
											(&Shape::GaussianShapeFunctionAlignment::getDefaultStartGenerator),
											python::return_internal_reference<>()))
		.add_property("colorMatchFunction", python::make_function(&Shape::GaussianShapeFunctionAlignment::getColorMatchFunction,
																  python::return_internal_reference<>()),
					  &Shape::GaussianShapeFunctionAlignment::setColorMatchFunction)
		.add_property("colorFilterFunction", python::make_function(&Shape::GaussianShapeFunctionAlignment::getColorFilterFunction,
																   python::return_internal_reference<>()),
					  &Shape::GaussianShapeFunctionAlignment::setColorFilterFunction)
		.add_property("maxNumOptIterations", &Shape::GaussianShapeFunctionAlignment::getMaxNumOptimizationIterations,
					  &Shape::GaussianShapeFunctionAlignment::setMaxNumOptimizationIterations)
		.add_property("optStopGradient", &Shape::GaussianShapeFunctionAlignment::getOptimizationStopGradient,
					  &Shape::GaussianShapeFunctionAlignment::setOptimizationStopGradient)
		.add_property("optOverlap", GetBoolFunc(&Shape::GaussianShapeFunctionAlignment::optimizeOverlap),
					  SetBoolFunc(&Shape::GaussianShapeFunctionAlignment::optimizeOverlap))
		.add_property("rigorousOpt", GetBoolFunc(&Shape::GaussianShapeFunctionAlignment::rigorousOptimization),
					  SetBoolFunc(&Shape::GaussianShapeFunctionAlignment::rigorousOptimization));
}
