/* 
 * InteractionScoreGridCalculatorExport.cpp 
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

#include "CDPL/GRAIL/FeatureInteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Grid/RegularGrid.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAIL::exportFeatureInteractionScoreGridCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<GRAIL::FeatureInteractionScoreGridCalculator, GRAIL::FeatureInteractionScoreGridCalculator::SharedPointer, 
                                         boost::noncopyable>("FeatureInteractionScoreGridCalculator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const GRAIL::FeatureInteractionScoreGridCalculator::ScoringFunction&>(
                 (python::arg("self"), python::arg("func"))))
        .def(python::init<const GRAIL::FeatureInteractionScoreGridCalculator::ScoringFunction&, const GRAIL::FeatureInteractionScoreGridCalculator::ScoreCombinationFunction&>(
                 (python::arg("self"), python::arg("scoring_func"), python::arg("comb_func"))))
        .def(python::init<const GRAIL::FeatureInteractionScoreGridCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::FeatureInteractionScoreGridCalculator>())    
        .def("assign", CDPLPythonBase::copyAssOp<GRAIL::FeatureInteractionScoreGridCalculator>(), 
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("setDistanceCutoff", &GRAIL::FeatureInteractionScoreGridCalculator::setDistanceCutoff,
             (python::arg("self"), python::arg("dist")))
        .def("getDistanceCutoff", &GRAIL::FeatureInteractionScoreGridCalculator::getDistanceCutoff,
             python::arg("self"))
        .def("setScoringFunction", &GRAIL::FeatureInteractionScoreGridCalculator::setScoringFunction,
             (python::arg("self"), python::arg("func")))
        .def("getScoringFunction", &GRAIL::FeatureInteractionScoreGridCalculator::getScoringFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("setScoreCombinationFunction", &GRAIL::FeatureInteractionScoreGridCalculator::setScoreCombinationFunction,
             (python::arg("self"), python::arg("func")))
        .def("getScoreCombinationFunction", &GRAIL::FeatureInteractionScoreGridCalculator::getScoreCombinationFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("setFeatureSelectionPredicate", &GRAIL::FeatureInteractionScoreGridCalculator::setFeatureSelectionPredicate,
             (python::arg("self"), python::arg("func")))
        .def("getFeatureSelectionPredicate", &GRAIL::FeatureInteractionScoreGridCalculator::getFeatureSelectionPredicate,
             python::arg("self"), python::return_internal_reference<>())
        .def("normalizeScores", &GRAIL::FeatureInteractionScoreGridCalculator::normalizeScores, (python::arg("self"), python::arg("normalize")))
        .def("scoresNormalized", &GRAIL::FeatureInteractionScoreGridCalculator::scoresNormalized, python::arg("self"))
        .def("calculate", &GRAIL::FeatureInteractionScoreGridCalculator::calculate, (python::arg("self"), python::arg("tgt_ftrs"), python::arg("grid")))
        .add_property("normScores", &GRAIL::FeatureInteractionScoreGridCalculator::scoresNormalized,
                      &GRAIL::FeatureInteractionScoreGridCalculator::normalizeScores)
        .add_property("distanceCutoff", &GRAIL::FeatureInteractionScoreGridCalculator::getDistanceCutoff, &GRAIL::FeatureInteractionScoreGridCalculator::setDistanceCutoff)
        .add_property("scoringFunction", 
                      python::make_function(&GRAIL::FeatureInteractionScoreGridCalculator::getScoringFunction, python::return_internal_reference<>()),
                      &GRAIL::FeatureInteractionScoreGridCalculator::setScoringFunction)
        .add_property("scoreCombinationFunction", 
                      python::make_function(&GRAIL::FeatureInteractionScoreGridCalculator::getScoreCombinationFunction, python::return_internal_reference<>()),
                      &GRAIL::FeatureInteractionScoreGridCalculator::setScoreCombinationFunction)
        .add_property("featureSelectionPredicate", 
                      python::make_function(&GRAIL::FeatureInteractionScoreGridCalculator::getFeatureSelectionPredicate, python::return_internal_reference<>()),
                      &GRAIL::FeatureInteractionScoreGridCalculator::setFeatureSelectionPredicate);

    python::class_<GRAIL::FeatureInteractionScoreGridCalculator::MaxScoreFunctor>("MaxScoreFunctor", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def("__call__", &GRAIL::FeatureInteractionScoreGridCalculator::MaxScoreFunctor::operator(), (python::arg("self"), python::arg("scores")));

    python::class_<GRAIL::FeatureInteractionScoreGridCalculator::ScoreSumFunctor>("ScoreSumFunctor", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def("__call__", &GRAIL::FeatureInteractionScoreGridCalculator::ScoreSumFunctor::operator(), (python::arg("self"), python::arg("scores")));
}
