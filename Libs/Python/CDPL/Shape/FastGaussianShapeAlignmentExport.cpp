/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FastGaussianShapeAlignmentExport.cpp 
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

#include "CDPL/Shape/FastGaussianShapeAlignment.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportFastGaussianShapeAlignment()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::FastGaussianShapeAlignment::*SetBoolFunc)(bool);
	typedef bool (Shape::FastGaussianShapeAlignment::*GetBoolFunc)() const;

    python::class_<Shape::FastGaussianShapeAlignment, Shape::FastGaussianShapeAlignment::SharedPointer, boost::noncopyable>(
		"FastGaussianShapeAlignment", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShape&>((python::arg("self"), python::arg("ref_shape")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(python::init<const Shape::GaussianShapeSet&>((python::arg("self"), python::arg("ref_shapes")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::FastGaussianShapeAlignment>())
		.def("setResultCompareFunction", &Shape::FastGaussianShapeAlignment::setResultCompareFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getResultCompareFunction", &Shape::FastGaussianShapeAlignment::getResultCompareFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setScoringFunction", &Shape::FastGaussianShapeAlignment::setScoringFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoringFunction", &Shape::FastGaussianShapeAlignment::getScoringFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setResultSelectionMode", &Shape::FastGaussianShapeAlignment::setResultSelectionMode,
			 (python::arg("self"), python::arg("mode")))
		.def("getResultSelectionMode", &Shape::FastGaussianShapeAlignment::getResultSelectionMode,
			 python::arg("self"))
		.def("setMaxNumOptimizationIterations", &Shape::FastGaussianShapeAlignment::setMaxNumOptimizationIterations,
			 (python::arg("self"), python::arg("max_iter")))
		.def("getMaxNumOptimizationIterations", &Shape::FastGaussianShapeAlignment::getMaxNumOptimizationIterations,
			 python::arg("self"))
		.def("setOptimizationStopGradient", &Shape::FastGaussianShapeAlignment::setOptimizationStopGradient,
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getOptimizationStopGradient", &Shape::FastGaussianShapeAlignment::getOptimizationStopGradient,
			 python::arg("self"))
		.def("performAlignment", SetBoolFunc(&Shape::FastGaussianShapeAlignment::performAlignment),
			 (python::arg("self"), python::arg("perf_align")))
		.def("performAlignment", GetBoolFunc(&Shape::FastGaussianShapeAlignment::performAlignment),
			 python::arg("self"))
		.def("optimizeOverlap", SetBoolFunc(&Shape::FastGaussianShapeAlignment::optimizeOverlap),
			 (python::arg("self"), python::arg("optimize")))
		.def("optimizeOverlap", GetBoolFunc(&Shape::FastGaussianShapeAlignment::optimizeOverlap),
			 python::arg("self"))
		.def("greedyOptimization", SetBoolFunc(&Shape::FastGaussianShapeAlignment::greedyOptimization),
			 (python::arg("self"), python::arg("greedy")))
		.def("greedyOptimization", GetBoolFunc(&Shape::FastGaussianShapeAlignment::greedyOptimization),
			 python::arg("self"))
		.def("setSymmetryThreshold", &Shape::FastGaussianShapeAlignment::setSymmetryThreshold,
			 (python::arg("self"), python::arg("thresh")))
		.def("getSymmetryThreshold", &Shape::FastGaussianShapeAlignment::getSymmetryThreshold, python::arg("self"))
		.def("genShapeCenterStarts", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genShapeCenterStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genShapeCenterStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genShapeCenterStarts),
			 python::arg("self"))
		.def("genColorCenterStarts", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genColorCenterStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genColorCenterStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genColorCenterStarts),
			 python::arg("self"))
		.def("genNonColorCenterStarts", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genNonColorCenterStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genNonColorCenterStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genNonColorCenterStarts),
			 python::arg("self"))
		.def("genRandomStarts", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genRandomStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genRandomStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genRandomStarts),
			 python::arg("self"))
		.def("genForAlignedShapeCenters", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genForAlignedShapeCenters),
			 (python::arg("self"), python::arg("generate")))
		.def("genForAlignedShapeCenters", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genForAlignedShapeCenters),
			 python::arg("self"))
		.def("genForReferenceShapeCenters", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genForReferenceShapeCenters),
			 (python::arg("self"), python::arg("generate")))
		.def("genForReferenceShapeCenters", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genForReferenceShapeCenters),
			 python::arg("self"))
		.def("genForLargerShapeCenters", SetBoolFunc(&Shape::FastGaussianShapeAlignment::genForLargerShapeCenters),
			 (python::arg("self"), python::arg("generate")))
		.def("genForLargerShapeCenters", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genForLargerShapeCenters),
			 python::arg("self"))
		.def("setMaxRandomTranslation", &Shape::FastGaussianShapeAlignment::setMaxRandomTranslation,
			 (python::arg("self"), python::arg("max_trans")))
		.def("getMaxRandomTranslation", &Shape::FastGaussianShapeAlignment::getMaxRandomTranslation, python::arg("self"))
		.def("setNumRandomStarts", &Shape::FastGaussianShapeAlignment::setNumRandomStarts,
			 (python::arg("self"), python::arg("num_starts")))
		.def("getNumRandomStarts", &Shape::FastGaussianShapeAlignment::getNumRandomStarts, python::arg("self"))
		.def("setRandomSeed", &Shape::FastGaussianShapeAlignment::setRandomSeed,
			 (python::arg("self"), python::arg("seed")))
		.def("clearReferenceShapes", &Shape::FastGaussianShapeAlignment::clearReferenceShapes,
			 python::arg("self"))
		.def("addReferenceShape", &Shape::FastGaussianShapeAlignment::addReferenceShape,
			 (python::arg("self"), python::arg("shape"), python::arg("new_set") = true), python::with_custodian_and_ward<1, 2>())
		.def("addReferenceShapes", &Shape::FastGaussianShapeAlignment::addReferenceShapes,
			 (python::arg("self"), python::arg("shapes"), python::arg("new_set") = true), python::with_custodian_and_ward<1, 2>())
		.def("getNumReferenceShapes", &Shape::FastGaussianShapeAlignment::getNumReferenceShapes, 
			 python::arg("self"))
		.def("align", static_cast<bool (Shape::FastGaussianShapeAlignment::*)(const Shape::GaussianShape&)>(&Shape::FastGaussianShapeAlignment::align), 
			 (python::arg("self"), python::arg("shape")))
		.def("align", static_cast<bool (Shape::FastGaussianShapeAlignment::*)(const Shape::GaussianShapeSet&)>(&Shape::FastGaussianShapeAlignment::align), 
			 (python::arg("self"), python::arg("shapes")))
		.def("getNumResults", &Shape::FastGaussianShapeAlignment::getNumResults, python::arg("self"))
		.def("__len__", &Shape::FastGaussianShapeAlignment::getNumResults, python::arg("self"))
		.def("getResult", static_cast<Shape::AlignmentResult& (Shape::FastGaussianShapeAlignment::*)(std::size_t)>(&Shape::FastGaussianShapeAlignment::getResult),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", static_cast<Shape::AlignmentResult& (Shape::FastGaussianShapeAlignment::*)(std::size_t)>(&Shape::FastGaussianShapeAlignment::getResult),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def_readonly("DEF_OPTIMIZATION_STOP_GRADIENT", Shape::FastGaussianShapeAlignment::DEF_OPTIMIZATION_STOP_GRADIENT)
		.def_readonly("DEF_MAX_OPTIMIZATION_ITERATIONS", Shape::FastGaussianShapeAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS)
		.def_readonly("DEF_RESULT_SELECTION_MODE", &Shape::FastGaussianShapeAlignment::DEF_RESULT_SELECTION_MODE)
		.def_readonly("DEF_SYMMETRY_THRESHOLD", Shape::FastGaussianShapeAlignment::DEF_SYMMETRY_THRESHOLD)
		.def_readonly("DEF_NUM_RANDOM_STARTS", Shape::FastGaussianShapeAlignment::DEF_NUM_RANDOM_STARTS)
		.def_readonly("DEF_MAX_RANDOM_TRANSLATION", Shape::FastGaussianShapeAlignment::DEF_MAX_RANDOM_TRANSLATION)
		.add_property("numResults", &Shape::FastGaussianShapeAlignment::getNumResults)
		.add_property("resultCompareFunction", python::make_function(&Shape::FastGaussianShapeAlignment::getResultCompareFunction,
																   python::return_internal_reference<>()),
					  &Shape::FastGaussianShapeAlignment::setResultCompareFunction)
		.add_property("scoringFunction", python::make_function(&Shape::FastGaussianShapeAlignment::getScoringFunction,
																   python::return_internal_reference<>()),
					  &Shape::FastGaussianShapeAlignment::setScoringFunction)
		.add_property("resultSelectionMode", &Shape::FastGaussianShapeAlignment::getResultSelectionMode,
					  &Shape::FastGaussianShapeAlignment::setResultSelectionMode)
		.add_property("maxNumOptIterations", &Shape::FastGaussianShapeAlignment::getMaxNumOptimizationIterations,
					  &Shape::FastGaussianShapeAlignment::setMaxNumOptimizationIterations)
		.add_property("optStopGradient", &Shape::FastGaussianShapeAlignment::getOptimizationStopGradient,
					  &Shape::FastGaussianShapeAlignment::setOptimizationStopGradient)
		.add_property("perfAlignment", GetBoolFunc(&Shape::FastGaussianShapeAlignment::performAlignment),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::performAlignment))
		.add_property("optOverlap", GetBoolFunc(&Shape::FastGaussianShapeAlignment::optimizeOverlap),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::optimizeOverlap))
		.add_property("greedyOpt", GetBoolFunc(&Shape::FastGaussianShapeAlignment::greedyOptimization),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::greedyOptimization))
		.add_property("numReferenceShapes", &Shape::FastGaussianShapeAlignment::getNumReferenceShapes)	
		.add_property("symmetryThreshold", &Shape::FastGaussianShapeAlignment::getSymmetryThreshold,
					  &Shape::FastGaussianShapeAlignment::setSymmetryThreshold)
		.add_property("maxRandomTranslation", &Shape::FastGaussianShapeAlignment::getMaxRandomTranslation,
					  &Shape::FastGaussianShapeAlignment::setMaxRandomTranslation)
		.add_property("numRandomStarts", &Shape::FastGaussianShapeAlignment::getNumRandomStarts,
					  &Shape::FastGaussianShapeAlignment::setNumRandomStarts)
		.add_property("shapeCenterStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genShapeCenterStarts),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genShapeCenterStarts))
		.add_property("colorCenterStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genColorCenterStarts),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genColorCenterStarts))
		.add_property("nonColorCenterStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genNonColorCenterStarts),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genNonColorCenterStarts))
		.add_property("randomStarts", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genRandomStarts),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genRandomStarts))
		.add_property("genForAlignedShapeCtrs", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genForAlignedShapeCenters),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genForAlignedShapeCenters))
		.add_property("genForReferenceShapeCrs", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genForReferenceShapeCenters),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genForReferenceShapeCenters))
		.add_property("genForLargerShapeCtrs", GetBoolFunc(&Shape::FastGaussianShapeAlignment::genForLargerShapeCenters),
					  SetBoolFunc(&Shape::FastGaussianShapeAlignment::genForLargerShapeCenters));

}
