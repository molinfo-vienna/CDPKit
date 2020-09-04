/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningSettingsExport.cpp 
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

#include "CDPL/Shape/ScreeningSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportScreeningSettings()
{
    using namespace boost;
    using namespace CDPL;

    typedef void (Shape::ScreeningSettings::*SetBoolFunc)(bool);
    typedef bool (Shape::ScreeningSettings::*GetBoolFunc)() const;

    python::scope scope = python::class_<Shape::ScreeningSettings>("ScreeningSettings", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::ScreeningSettings&>((python::arg("self"), python::arg("settings"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ScreeningSettings>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::ScreeningSettings::operator=),
			 (python::arg("self"), python::arg("settings")), python::return_self<>())
		.def("setScoringFunction", &Shape::ScreeningSettings::setScoringFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoringFunction", &Shape::ScreeningSettings::getScoringFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setScoreThreshold", &Shape::ScreeningSettings::setScoreThreshold,
			 (python::arg("self"), python::arg("thresh")))
		.def("getScoreThreshold", &Shape::ScreeningSettings::getScoreThreshold,
			 python::arg("self"))
		.def("setColorFeatureType", &Shape::ScreeningSettings::setColorFeatureType,
			 (python::arg("self"), python::arg("type")))
		.def("getColorFeatureType", &Shape::ScreeningSettings::getColorFeatureType,
			 python::arg("self"))
		.def("setScreeningMode", &Shape::ScreeningSettings::setScreeningMode,
			 (python::arg("self"), python::arg("mode")))
		.def("getScreeningMode", &Shape::ScreeningSettings::getScreeningMode,
			 python::arg("self"))
		.def("setAlignmentMode", &Shape::ScreeningSettings::setAlignmentMode,
			 (python::arg("self"), python::arg("mode")))
		.def("getAlignmentMode", &Shape::ScreeningSettings::getAlignmentMode,
			 python::arg("self"))
		.def("allCarbonMode", SetBoolFunc(&Shape::ScreeningSettings::allCarbonMode),
			 (python::arg("self"), python::arg("all_c")))
		.def("allCarbonMode", GetBoolFunc(&Shape::ScreeningSettings::allCarbonMode),
			 python::arg("self"))
		.def("setMaxNumOptimizationIterations", &Shape::ScreeningSettings::setMaxNumOptimizationIterations,
			 (python::arg("self"), python::arg("max_iter")))
		.def("getMaxNumOptimizationIterations", &Shape::ScreeningSettings::getMaxNumOptimizationIterations,
			 python::arg("self"))
		.def("setOptimizationStopGradient", &Shape::ScreeningSettings::setOptimizationStopGradient,
			 (python::arg("self"), python::arg("grad_norm")))
		.def("getOptimizationStopGradient", &Shape::ScreeningSettings::getOptimizationStopGradient,
			 python::arg("self"))
		.def("optimizeOverlap", SetBoolFunc(&Shape::ScreeningSettings::optimizeOverlap),
			 (python::arg("self"), python::arg("optimize")))
		.def("optimizeOverlap", GetBoolFunc(&Shape::ScreeningSettings::optimizeOverlap),
			 python::arg("self"))
		.def("greedyOptimization", SetBoolFunc(&Shape::ScreeningSettings::greedyOptimization),
			 (python::arg("self"), python::arg("greedy")))
		.def("greedyOptimization", GetBoolFunc(&Shape::ScreeningSettings::greedyOptimization),
			 python::arg("self"))
		.def_readonly("DEFAULT", Shape::ScreeningSettings::DEFAULT)
		.def_readonly("NO_THRESHOLD", Shape::ScreeningSettings::NO_THRESHOLD)
		.add_property("scoringFunction", python::make_function(&Shape::ScreeningSettings::getScoringFunction,
															   python::return_internal_reference<>()),
					  &Shape::ScreeningSettings::setScoringFunction)
		.add_property("scoreThreshold", &Shape::ScreeningSettings::getScoreThreshold,
					  &Shape::ScreeningSettings::setScoreThreshold)
		.add_property("screeningMode", &Shape::ScreeningSettings::getScreeningMode,
					  &Shape::ScreeningSettings::setScreeningMode)
		.add_property("alignmentMode", &Shape::ScreeningSettings::getAlignmentMode,
					  &Shape::ScreeningSettings::setAlignmentMode)
		.add_property("allCarbon", GetBoolFunc(&Shape::ScreeningSettings::allCarbonMode),
					  SetBoolFunc(&Shape::ScreeningSettings::allCarbonMode))
		.add_property("colorFeatureType", &Shape::ScreeningSettings::getColorFeatureType,
					  &Shape::ScreeningSettings::setColorFeatureType)
		.add_property("maxNumOptIterations", &Shape::ScreeningSettings::getMaxNumOptimizationIterations,
					  &Shape::ScreeningSettings::setMaxNumOptimizationIterations)
		.add_property("optStopGradient", &Shape::ScreeningSettings::getOptimizationStopGradient,
					  &Shape::ScreeningSettings::setOptimizationStopGradient)
		.add_property("optOverlap", GetBoolFunc(&Shape::ScreeningSettings::optimizeOverlap),
					  SetBoolFunc(&Shape::ScreeningSettings::optimizeOverlap))
		.add_property("greedyOpt", GetBoolFunc(&Shape::ScreeningSettings::greedyOptimization),
					  SetBoolFunc(&Shape::ScreeningSettings::greedyOptimization));

	python::enum_<Shape::ScreeningSettings::ScreeningMode>("ScreeningMode")
		.value("BEST_OVERALL_MATCH", Shape::ScreeningSettings::BEST_OVERALL_MATCH)
		.value("BEST_MATCH_PER_QUERY", Shape::ScreeningSettings::BEST_MATCH_PER_QUERY)
		.value("BEST_MATCH_PER_QUERY_CONF", Shape::ScreeningSettings::BEST_MATCH_PER_QUERY_CONF);

	python::enum_<Shape::ScreeningSettings::ColorFeatureType>("ColorFeatureType")
		.value("NO_FEATURES", Shape::ScreeningSettings::NO_FEATURES)
		.value("PHARMACOPHORE_EXL_CHARGES", Shape::ScreeningSettings::PHARMACOPHORE_EXP_CHARGES)
		.value("PHARMACOPHORE_IMP_CHARGES", Shape::ScreeningSettings::PHARMACOPHORE_IMP_CHARGES);

   	python::enum_<Shape::ScreeningSettings::AlignmentMode>("AlignmentMode")
		.value("NO_ALIGNMENT", Shape::ScreeningSettings::NO_ALIGNMENT)
		.value("SHAPE_CENTROID", Shape::ScreeningSettings::SHAPE_CENTROID)
		.value("ATOM_CENTERS", Shape::ScreeningSettings::ATOM_CENTERS)
		.value("COLOR_FEATURE_CENTERS", Shape::ScreeningSettings::COLOR_FEATURE_CENTERS);
}
