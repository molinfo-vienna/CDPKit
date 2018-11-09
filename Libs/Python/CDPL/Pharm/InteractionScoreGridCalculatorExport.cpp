/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculatorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Grid/RegularGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportInteractionScoreGridCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::class_<Pharm::InteractionScoreGridCalculator, Pharm::InteractionScoreGridCalculator::SharedPointer, boost::noncopyable>("InteractionScoreGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::InteractionScoreGridCalculator::ScoringFunction&>(
				 (python::arg("self"), python::arg("func"))))
		.def(python::init<const Pharm::InteractionScoreGridCalculator::ScoringFunction&, const Pharm::InteractionScoreGridCalculator::ScoreCombinationFunction&>(
				 (python::arg("self"), python::arg("scoring_func"), python::arg("comb_func"))))
		.def(python::init<const Pharm::InteractionScoreGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::InteractionScoreGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::InteractionScoreGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setDistanceCutoff", &Pharm::InteractionScoreGridCalculator::setDistanceCutoff,
			 (python::arg("self"), python::arg("dist")))
		.def("getDistanceCutoff", &Pharm::InteractionScoreGridCalculator::getDistanceCutoff,
			 python::arg("self"))
		.def("setScoringFunction", &Pharm::InteractionScoreGridCalculator::setScoringFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoringFunction", &Pharm::InteractionScoreGridCalculator::getScoringFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("setScoreCombinationFunction", &Pharm::InteractionScoreGridCalculator::setScoreCombinationFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoreCombinationFunction", &Pharm::InteractionScoreGridCalculator::getScoreCombinationFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("normalizeScores", &Pharm::InteractionScoreGridCalculator::normalizeScores, (python::arg("self"), python::arg("normalize")))
		.def("scoresNormalized", &Pharm::InteractionScoreGridCalculator::scoresNormalized, python::arg("self"))
		.def("calculate", 
			 static_cast<void (Pharm::InteractionScoreGridCalculator::*)(const Pharm::FeatureContainer&, Grid::DSpatialGrid& grid)>
			 (&Pharm::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("features"), python::arg("grid")))
		.def("calculate", 
			 static_cast<void (Pharm::InteractionScoreGridCalculator::*)(const Pharm::FeatureContainer&, 
																		 Grid::DSpatialGrid& grid, 
																		 const Pharm::InteractionScoreGridCalculator::FeaturePredicate&)>
			 (&Pharm::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("features"), python::arg("grid"), python::arg("tgt_ftr_pred")))
		.add_property("normalizedScores", &Pharm::InteractionScoreGridCalculator::scoresNormalized,
					  &Pharm::InteractionScoreGridCalculator::normalizeScores)
		.add_property("distanceCutoff", &Pharm::InteractionScoreGridCalculator::getDistanceCutoff, &Pharm::InteractionScoreGridCalculator::setDistanceCutoff)
		.add_property("scoringFunction", 
					  python::make_function(&Pharm::InteractionScoreGridCalculator::getScoringFunction, python::return_internal_reference<>()),
					  &Pharm::InteractionScoreGridCalculator::setScoringFunction)
		.add_property("scoreCombinationFunction", 
					  python::make_function(&Pharm::InteractionScoreGridCalculator::getScoreCombinationFunction, python::return_internal_reference<>()),
					  &Pharm::InteractionScoreGridCalculator::setScoreCombinationFunction);

}
