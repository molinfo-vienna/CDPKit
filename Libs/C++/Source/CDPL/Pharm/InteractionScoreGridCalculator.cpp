/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculator.cpp 
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

 
#include "StaticInit.hpp"

#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"  
#include "CDPL/Pharm/Feature.hpp"  


using namespace CDPL;


namespace
{

    double maxElement(const Math::DVector& vec)
    {
		return normInf(vec);
    }
}
 

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(): scoreCombinationFunc(&maxElement)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(const ScoringFunction& func): 
	scoringFunc(func), scoreCombinationFunc(&maxElement)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(const ScoringFunction& scoring_func, const ScoreCombinationFunction& comb_func): 
	scoringFunc(scoring_func), scoreCombinationFunc(comb_func)
{}

void Pharm::InteractionScoreGridCalculator::setScoringFunction(const ScoringFunction& func)
{
    scoringFunc = func;
}

const Pharm::InteractionScoreGridCalculator::ScoringFunction& Pharm::InteractionScoreGridCalculator::getScoringFunction() const
{
    return scoringFunc;
}

void Pharm::InteractionScoreGridCalculator::setScoreCombinationFunction(const ScoreCombinationFunction& func)
{
    scoreCombinationFunc = func;
}

const Pharm::InteractionScoreGridCalculator::ScoreCombinationFunction& Pharm::InteractionScoreGridCalculator::getScoreCombinationFunction() const
{
    return scoreCombinationFunc;
}

void Pharm::InteractionScoreGridCalculator::calculate(const FeatureContainer& features, Grid::DSpatialGrid& grid)
{
	calculate(features, grid, FeaturePredicate());
}

void Pharm::InteractionScoreGridCalculator::calculate(const FeatureContainer& features, Grid::DSpatialGrid& grid, const FeaturePredicate& tgt_ftr_pred)
{
	tgtFeatures.clear();

	for (FeatureContainer::ConstFeatureIterator it = features.getFeaturesBegin(), end = features.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		if (!tgt_ftr_pred || tgt_ftr_pred(ftr))
			tgtFeatures.push_back(&ftr);
	}

	partialScores.resize(tgtFeatures.size(), false);

	std::size_t num_pts = grid.getNumElements();
    Math::Vector3D grid_pos;

	for (std::size_t i = 0, l = 0; i < num_pts; i++, l = 0) {
		grid.getCoordinates(i, grid_pos);

		for (FeatureList::const_iterator it = tgtFeatures.begin(), end = tgtFeatures.end(); it != end; ++it)
			partialScores[l++] = scoringFunc(grid_pos, **it);

		if (l == 0)
			grid(i) = 0.0;
		else
			grid(i) = scoreCombinationFunc(partialScores);
	}
}
