/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridSetCalculatorExport.cpp 
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

#include "CDPL/GRAIL/InteractionScoreGridSetCalculator.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAIL::exportInteractionScoreGridSetCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::class_<GRAIL::InteractionScoreGridSetCalculator, boost::noncopyable>("InteractionScoreGridSetCalculator", python::no_init)
		//.def(python::init<const GRAIL::InteractionScoreGridSetCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::InteractionScoreGridSetCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&GRAIL::InteractionScoreGridSetCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setScoringFunction", &GRAIL::InteractionScoreGridSetCalculator::setScoringFunction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("func")))
		.def("removeScoringFunction", &GRAIL::InteractionScoreGridSetCalculator::removeScoringFunction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
		.def("getScoringFunction", &GRAIL::InteractionScoreGridSetCalculator::getScoringFunction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")),
			 python::return_internal_reference<>())
		.def("enableInteraction", &GRAIL::InteractionScoreGridSetCalculator::enableInteraction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("enable")))
		.def("isInteractionEnabled", &GRAIL::InteractionScoreGridSetCalculator::isInteractionEnabled, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
		.def("clearEnabledInteractions", &GRAIL::InteractionScoreGridSetCalculator::isInteractionEnabled, python::arg("self"))
		.def("setScoreCombinationFunction", &GRAIL::InteractionScoreGridSetCalculator::setScoreCombinationFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getScoreCombinationFunction", &GRAIL::InteractionScoreGridSetCalculator::getScoreCombinationFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("normalizeScores", &GRAIL::InteractionScoreGridSetCalculator::normalizeScores, (python::arg("self"), python::arg("normalize")))
		.def("scoresNormalized", &GRAIL::InteractionScoreGridSetCalculator::scoresNormalized, python::arg("self"))
		.add_property("normalizedScores", &GRAIL::InteractionScoreGridSetCalculator::scoresNormalized,
					  &GRAIL::InteractionScoreGridSetCalculator::normalizeScores)
		.add_property("scoreCombinationFunction", python::make_function(&GRAIL::InteractionScoreGridSetCalculator::getScoreCombinationFunction, python::return_internal_reference<>()),
					  &GRAIL::InteractionScoreGridSetCalculator::setScoreCombinationFunction);
}
