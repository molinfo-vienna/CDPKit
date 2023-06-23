/* 
 * GaussianShapeAlignmentExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

    python::class_<Shape::GaussianShapeAlignment, Shape::GaussianShapeAlignment::SharedPointer, boost::noncopyable>(
        "GaussianShapeAlignment", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Shape::GaussianShape&>((python::arg("self"), python::arg("ref_shape")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(python::init<const Shape::GaussianShapeSet&>((python::arg("self"), python::arg("ref_shapes")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeAlignment>())
        .def("setOverlapFunction", &Shape::GaussianShapeAlignment::setOverlapFunction,
             (python::arg("self"), python::arg("func")), python::with_custodian_and_ward<1, 2>())
        .def("getOverlapFunction", &Shape::GaussianShapeAlignment::getOverlapFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("getDefaultOverlapFunction", static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeAlignment::*)()>
             (&Shape::GaussianShapeAlignment::getDefaultOverlapFunction),
             python::arg("self"), python::return_internal_reference<>())
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
        .def("setResultCompareFunction", &Shape::GaussianShapeAlignment::setResultCompareFunction,
             (python::arg("self"), python::arg("func")))
        .def("getResultCompareFunction", &Shape::GaussianShapeAlignment::getResultCompareFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("setScoringFunction", &Shape::GaussianShapeAlignment::setScoringFunction,
             (python::arg("self"), python::arg("func")))
        .def("getScoringFunction", &Shape::GaussianShapeAlignment::getScoringFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("setResultSelectionMode", &Shape::GaussianShapeAlignment::setResultSelectionMode,
             (python::arg("self"), python::arg("mode")))
        .def("getResultSelectionMode", &Shape::GaussianShapeAlignment::getResultSelectionMode,
             python::arg("self"))
        .def("setMaxNumOptimizationIterations", &Shape::GaussianShapeAlignment::setMaxNumOptimizationIterations,
             (python::arg("self"), python::arg("max_iter")))
        .def("getMaxNumOptimizationIterations", &Shape::GaussianShapeAlignment::getMaxNumOptimizationIterations,
             python::arg("self"))
        .def("setOptimizationStopGradient", &Shape::GaussianShapeAlignment::setOptimizationStopGradient,
             (python::arg("self"), python::arg("grad_norm")))
        .def("getOptimizationStopGradient", &Shape::GaussianShapeAlignment::getOptimizationStopGradient,
             python::arg("self"))
        .def("performAlignment", SetBoolFunc(&Shape::GaussianShapeAlignment::performAlignment),
             (python::arg("self"), python::arg("perf_align")))
        .def("performAlignment", GetBoolFunc(&Shape::GaussianShapeAlignment::performAlignment),
             python::arg("self"))
        .def("optimizeOverlap", SetBoolFunc(&Shape::GaussianShapeAlignment::optimizeOverlap),
             (python::arg("self"), python::arg("optimize")))
        .def("optimizeOverlap", GetBoolFunc(&Shape::GaussianShapeAlignment::optimizeOverlap),
             python::arg("self"))
        .def("greedyOptimization", SetBoolFunc(&Shape::GaussianShapeAlignment::greedyOptimization),
             (python::arg("self"), python::arg("greedy")))
        .def("greedyOptimization", GetBoolFunc(&Shape::GaussianShapeAlignment::greedyOptimization),
             python::arg("self"))
        .def("calcColorOverlaps", SetBoolFunc(&Shape::GaussianShapeAlignment::calcColorOverlaps),
             (python::arg("self"), python::arg("calc")))
        .def("calcColorOverlaps", GetBoolFunc(&Shape::GaussianShapeAlignment::calcColorOverlaps),
             python::arg("self"))
        .def("calcSelfOverlaps", SetBoolFunc(&Shape::GaussianShapeAlignment::calcSelfOverlaps), 
             (python::arg("self"), python::arg("calc")))
        .def("calcSelfOverlaps", GetBoolFunc(&Shape::GaussianShapeAlignment::calcSelfOverlaps), 
             python::arg("self"))
        .def("calcColorSelfOverlaps", SetBoolFunc(&Shape::GaussianShapeAlignment::calcColorSelfOverlaps),
             (python::arg("self"), python::arg("calc")))
        .def("calcColorSelfOverlaps", GetBoolFunc(&Shape::GaussianShapeAlignment::calcColorSelfOverlaps),
             python::arg("self"))
        .def("setMaxOrder", &Shape::GaussianShapeAlignment::setMaxOrder, 
             (python::arg("self"), python::arg("max_order")))
        .def("getMaxOrder", &Shape::GaussianShapeAlignment::getMaxOrder, 
             python::arg("self"))
        .def("setDistanceCutoff", &Shape::GaussianShapeAlignment::setDistanceCutoff, 
             (python::arg("self"), python::arg("cutoff")))
        .def("getDistanceCutoff", &Shape::GaussianShapeAlignment::getDistanceCutoff,
             python::arg("self"))
        .def("clearReferenceShapes", &Shape::GaussianShapeAlignment::clearReferenceShapes,
             python::arg("self"))
        .def("addReferenceShape", &Shape::GaussianShapeAlignment::addReferenceShape,
             (python::arg("self"), python::arg("shape"), python::arg("new_set") = true), python::with_custodian_and_ward<1, 2>())
        .def("addReferenceShapes", &Shape::GaussianShapeAlignment::addReferenceShapes,
             (python::arg("self"), python::arg("shapes"), python::arg("new_set") = true), python::with_custodian_and_ward<1, 2>())
        .def("getNumReferenceShapes", &Shape::GaussianShapeAlignment::getNumReferenceShapes, 
             python::arg("self"))
        .def("getReferenceShape", &Shape::GaussianShapeAlignment::getReferenceShape,
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def("align", static_cast<bool (Shape::GaussianShapeAlignment::*)(const Shape::GaussianShape&)>(&Shape::GaussianShapeAlignment::align), 
             (python::arg("self"), python::arg("shape")))
        .def("align", static_cast<bool (Shape::GaussianShapeAlignment::*)(const Shape::GaussianShapeSet&)>(&Shape::GaussianShapeAlignment::align), 
             (python::arg("self"), python::arg("shapes")))
        .def("getNumResults", &Shape::GaussianShapeAlignment::getNumResults, python::arg("self"))
        .def("__len__", &Shape::GaussianShapeAlignment::getNumResults, python::arg("self"))
        .def("getResult", static_cast<Shape::AlignmentResult& (Shape::GaussianShapeAlignment::*)(std::size_t)>(&Shape::GaussianShapeAlignment::getResult),
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def("__getitem__", static_cast<Shape::AlignmentResult& (Shape::GaussianShapeAlignment::*)(std::size_t)>(&Shape::GaussianShapeAlignment::getResult),
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def_readonly("DEF_OPTIMIZATION_STOP_GRADIENT", Shape::GaussianShapeAlignment::DEF_OPTIMIZATION_STOP_GRADIENT)
        .def_readonly("DEF_MAX_OPTIMIZATION_ITERATIONS", Shape::GaussianShapeAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS)
        .def_readonly("DEF_MAX_PRODUCT_ORDER", &Shape::GaussianShapeAlignment::DEF_MAX_PRODUCT_ORDER)
        .def_readonly("DEF_DISTANCE_CUTOFF", &Shape::GaussianShapeAlignment::DEF_DISTANCE_CUTOFF)
        .def_readonly("DEF_RESULT_SELECTION_MODE", &Shape::GaussianShapeAlignment::DEF_RESULT_SELECTION_MODE)
        .add_property("numResults", &Shape::GaussianShapeAlignment::getNumResults)
        .add_property("overlapFunction",
                      python::make_function(&Shape::GaussianShapeAlignment::getOverlapFunction,
                                            python::return_internal_reference<>()),
                      python::make_function(&Shape::GaussianShapeAlignment::setOverlapFunction,
                                            python::with_custodian_and_ward<1, 2>()))
        .add_property("defaultOverlapFunction",
                      python::make_function(static_cast<Shape::FastGaussianShapeOverlapFunction& (Shape::GaussianShapeAlignment::*)()>
                                            (&Shape::GaussianShapeAlignment::getDefaultOverlapFunction),
                                            python::return_internal_reference<>()))
        .add_property("startGenerator",
                      python::make_function(&Shape::GaussianShapeAlignment::getStartGenerator,
                                            python::return_internal_reference<>()),
                      python::make_function(&Shape::GaussianShapeAlignment::setStartGenerator,
                                            python::with_custodian_and_ward<1, 2>()))
        .add_property("defaultStartGenerator",
                      python::make_function(static_cast<Shape::PrincipalAxesAlignmentStartGenerator& (Shape::GaussianShapeAlignment::*)()>
                                            (&Shape::GaussianShapeAlignment::getDefaultStartGenerator),
                                            python::return_internal_reference<>()))
        .add_property("colorMatchFunction", python::make_function(&Shape::GaussianShapeAlignment::getColorMatchFunction,
                                                                  python::return_internal_reference<>()),
                      &Shape::GaussianShapeAlignment::setColorMatchFunction)
        .add_property("colorFilterFunction", python::make_function(&Shape::GaussianShapeAlignment::getColorFilterFunction,
                                                                   python::return_internal_reference<>()),
                      &Shape::GaussianShapeAlignment::setColorFilterFunction)
        .add_property("resultCompareFunction", python::make_function(&Shape::GaussianShapeAlignment::getResultCompareFunction,
                                                                   python::return_internal_reference<>()),
                      &Shape::GaussianShapeAlignment::setResultCompareFunction)
        .add_property("scoringFunction", python::make_function(&Shape::GaussianShapeAlignment::getScoringFunction,
                                                                   python::return_internal_reference<>()),
                      &Shape::GaussianShapeAlignment::setScoringFunction)
        .add_property("resultSelectionMode", &Shape::GaussianShapeAlignment::getResultSelectionMode,
                      &Shape::GaussianShapeAlignment::setResultSelectionMode)
        .add_property("maxNumOptIterations", &Shape::GaussianShapeAlignment::getMaxNumOptimizationIterations,
                      &Shape::GaussianShapeAlignment::setMaxNumOptimizationIterations)
        .add_property("optStopGradient", &Shape::GaussianShapeAlignment::getOptimizationStopGradient,
                      &Shape::GaussianShapeAlignment::setOptimizationStopGradient)
        .add_property("perfAlignment", GetBoolFunc(&Shape::GaussianShapeAlignment::performAlignment),
                      SetBoolFunc(&Shape::GaussianShapeAlignment::performAlignment))
        .add_property("optOverlap", GetBoolFunc(&Shape::GaussianShapeAlignment::optimizeOverlap),
                      SetBoolFunc(&Shape::GaussianShapeAlignment::optimizeOverlap))
        .add_property("greedyOpt", GetBoolFunc(&Shape::GaussianShapeAlignment::greedyOptimization),
                      SetBoolFunc(&Shape::GaussianShapeAlignment::greedyOptimization))
        .add_property("selfOverlaps", GetBoolFunc(&Shape::GaussianShapeAlignment::calcSelfOverlaps),
                      SetBoolFunc(&Shape::GaussianShapeAlignment::calcSelfOverlaps))
        .add_property("colorSelfOverlaps", GetBoolFunc(&Shape::GaussianShapeAlignment::calcColorSelfOverlaps),
                      SetBoolFunc(&Shape::GaussianShapeAlignment::calcColorSelfOverlaps))
        .add_property("colorOverlaps", GetBoolFunc(&Shape::GaussianShapeAlignment::calcColorOverlaps),
                      SetBoolFunc(&Shape::GaussianShapeAlignment::calcColorOverlaps))
        .add_property("maxOrder", &Shape::GaussianShapeFunction::getMaxOrder, 
                      &Shape::GaussianShapeFunction::setMaxOrder)
        .add_property("distCutoff", &Shape::GaussianShapeFunction::getDistanceCutoff, 
                      &Shape::GaussianShapeFunction::setDistanceCutoff)
        .add_property("numReferenceShapes", &Shape::GaussianShapeAlignment::getNumReferenceShapes);

}
