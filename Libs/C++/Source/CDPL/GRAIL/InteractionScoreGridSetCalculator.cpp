/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridSetCalculator.cpp 
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

 
#include "StaticInit.hpp"

#include <functional>

#include <boost/bind.hpp>

#include "CDPL/GRAIL/InteractionScoreGridSetCalculator.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"  


using namespace CDPL;


namespace
{

	const GRAIL::FeatureInteractionScoreGridCalculator::ScoringFunction NO_SCORING_FUNC;
}


void GRAIL::InteractionScoreGridSetCalculator::enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable)
{
    if (enable)
		enabledInteractions.insert(FeatureTypePair(ftr_type, tgt_ftr_type));
    else
		enabledInteractions.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}

bool GRAIL::InteractionScoreGridSetCalculator::isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
    return (enabledInteractions.find(FeatureTypePair(ftr_type, tgt_ftr_type)) != enabledInteractions.end());
}

void GRAIL::InteractionScoreGridSetCalculator::clearEnabledInteractions()
{
    enabledInteractions.clear();
}

void GRAIL::InteractionScoreGridSetCalculator::setScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const ScoringFunction& func)
{
    scoringFuncMap[FeatureTypePair(ftr_type, tgt_ftr_type)] = func;
}

const GRAIL::InteractionScoreGridSetCalculator::ScoringFunction& 
GRAIL::InteractionScoreGridSetCalculator::getScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
    ScoringFuncMap::const_iterator it = scoringFuncMap.find(FeatureTypePair(ftr_type, tgt_ftr_type));

    return (it == scoringFuncMap.end() ? NO_SCORING_FUNC : it->second);
}

void GRAIL::InteractionScoreGridSetCalculator::removeScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type)
{
    scoringFuncMap.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}

void GRAIL::InteractionScoreGridSetCalculator::setScoreCombinationFunction(const ScoreCombinationFunction& func)
{
    gridCalculator.setScoreCombinationFunction(func);
}

const GRAIL::InteractionScoreGridSetCalculator::ScoreCombinationFunction& GRAIL::InteractionScoreGridSetCalculator::getScoreCombinationFunction() const
{
    return gridCalculator.getScoreCombinationFunction();
}

void GRAIL::InteractionScoreGridSetCalculator::normalizeScores(bool normalize)
{
	gridCalculator.normalizeScores(normalize);
}

bool GRAIL::InteractionScoreGridSetCalculator::scoresNormalized() const
{
	return gridCalculator.scoresNormalized();
}

void GRAIL::InteractionScoreGridSetCalculator::calculate(const Pharm::FeatureContainer& tgt_ftrs) 
{
    for (ScoringFuncMap::const_iterator it = scoringFuncMap.begin(), end = scoringFuncMap.end(); it != end; ++it) {
		if (!it->second)
			continue;

		if (enabledInteractions.find(it->first) == enabledInteractions.end())
			continue;

		unsigned int ftr_type = it->first.first;
		unsigned int tgt_ftr_type = it->first.second;

		Grid::DSpatialGrid::SharedPointer grid_ptr = createGrid(ftr_type, tgt_ftr_type);

		gridCalculator.setScoringFunction(it->second);
		gridCalculator.setFeatureSelectionPredicate(boost::bind(std::equal_to<unsigned int>(), boost::bind(&Pharm::getType, _1), tgt_ftr_type));
		gridCalculator.calculate(tgt_ftrs, *grid_ptr); 
    }
}
