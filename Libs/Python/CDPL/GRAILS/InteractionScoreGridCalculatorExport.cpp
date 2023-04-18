/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculatorExport.cpp 
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

#include "CDPL/GRAILS/InteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Grid/RegularGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAILS::exportInteractionScoreGridCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<GRAILS::InteractionScoreGridCalculator, GRAILS::InteractionScoreGridCalculator::SharedPointer, 
										 boost::noncopyable>("InteractionScoreGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const GRAILS::InteractionScoreGridCalculator::ScoringFunction&>(
				 (python::arg("self"), python::arg("func"))))
		.def(python::init<const GRAILS::InteractionScoreGridCalculator::ScoringFunction&, const GRAILS::InteractionScoreGridCalculator::ScoreCombinationFunction&>(
				 (python::arg("self"), python::arg("scoring_func"), python::arg("comb_func"))))
		.def(python::init<const GRAILS::InteractionScoreGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAILS::InteractionScoreGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&GRAILS::InteractionScoreGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setDistanceCutoff", &GRAILS::InteractionScoreGridCalculator::setDistanceCutoff,
			 (python::arg("self"), python::arg("dist")))
		.def("getDistanceCutoff", &GRAILS::InteractionScoreGridCalculator::getDistanceCutoff,
			 python::arg("self"))
		.def("setScoringFunction", &GRAILS::InteractionScoreGridCalculator::setScoringFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoringFunction", &GRAILS::InteractionScoreGridCalculator::getScoringFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setScoreCombinationFunction", &GRAILS::InteractionScoreGridCalculator::setScoreCombinationFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoreCombinationFunction", &GRAILS::InteractionScoreGridCalculator::getScoreCombinationFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("normalizeScores", &GRAILS::InteractionScoreGridCalculator::normalizeScores, (python::arg("self"), python::arg("normalize")))
		.def("scoresNormalized", &GRAILS::InteractionScoreGridCalculator::scoresNormalized, python::arg("self"))
		.def("calculate", 
			 static_cast<void (GRAILS::InteractionScoreGridCalculator::*)(const Pharm::FeatureContainer&, Grid::DSpatialGrid& grid)>
			 (&GRAILS::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("features"), python::arg("grid")))
		.def("calculate", 
			 static_cast<void (GRAILS::InteractionScoreGridCalculator::*)(const Pharm::FeatureContainer&, 
																		 Grid::DSpatialGrid& grid, 
																		 const GRAILS::InteractionScoreGridCalculator::FeaturePredicate&)>
			 (&GRAILS::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("features"), python::arg("grid"), python::arg("tgt_ftr_pred")))
		.add_property("normalizedScores", &GRAILS::InteractionScoreGridCalculator::scoresNormalized,
					  &GRAILS::InteractionScoreGridCalculator::normalizeScores)
		.add_property("distanceCutoff", &GRAILS::InteractionScoreGridCalculator::getDistanceCutoff, &GRAILS::InteractionScoreGridCalculator::setDistanceCutoff)
		.add_property("scoringFunction", 
					  python::make_function(&GRAILS::InteractionScoreGridCalculator::getScoringFunction, python::return_internal_reference<>()),
					  &GRAILS::InteractionScoreGridCalculator::setScoringFunction)
		.add_property("scoreCombinationFunction", 
					  python::make_function(&GRAILS::InteractionScoreGridCalculator::getScoreCombinationFunction, python::return_internal_reference<>()),
					  &GRAILS::InteractionScoreGridCalculator::setScoreCombinationFunction);

	python::class_<GRAILS::InteractionScoreGridCalculator::MaxScoreFunctor>("MaxScoreFunctor", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("__call__", &GRAILS::InteractionScoreGridCalculator::MaxScoreFunctor::operator(), (python::arg("self"), python::arg("scores")));

	python::class_<GRAILS::InteractionScoreGridCalculator::ScoreSumFunctor>("ScoreSumFunctor", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("__call__", &GRAILS::InteractionScoreGridCalculator::ScoreSumFunctor::operator(), (python::arg("self"), python::arg("scores")));
}
