/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculator.cpp 
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

#include <iterator>
#include <limits>
#include <algorithm>

#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"  
#include "CDPL/Pharm/Feature.hpp"  
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Internal/Octree.hpp"  


using namespace CDPL;


const double Pharm::InteractionScoreGridCalculator::DEF_DISTANCE_CUTOFF = 10.0;


Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(): 
	scoreCombinationFunc(MaxScoreFunctor()), distCutoff(DEF_DISTANCE_CUTOFF), normScores(true)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(const ScoringFunction& func): 
	scoringFunc(func), scoreCombinationFunc(MaxScoreFunctor()), distCutoff(DEF_DISTANCE_CUTOFF), normScores(true)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(const ScoringFunction& scoring_func, const ScoreCombinationFunction& comb_func): 
	scoringFunc(scoring_func), scoreCombinationFunc(comb_func), distCutoff(DEF_DISTANCE_CUTOFF), normScores(true)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(const InteractionScoreGridCalculator& calc):
	scoringFunc(calc.scoringFunc), scoreCombinationFunc(calc.scoreCombinationFunc), distCutoff(calc.distCutoff) {}

Pharm::InteractionScoreGridCalculator::~InteractionScoreGridCalculator() {}

void Pharm::InteractionScoreGridCalculator::setDistanceCutoff(double dist)
{
	distCutoff = dist;
}

double Pharm::InteractionScoreGridCalculator::getDistanceCutoff() const
{
	return distCutoff;
}

void Pharm::InteractionScoreGridCalculator::normalizeScores(bool normalize)
{
	normScores = normalize;
}

bool Pharm::InteractionScoreGridCalculator::scoresNormalized() const
{
	return normScores;
}

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

Pharm::InteractionScoreGridCalculator& Pharm::InteractionScoreGridCalculator::operator=(const InteractionScoreGridCalculator& calc) 
{
	if (this == &calc)
		return *this;

	scoringFunc = calc.scoringFunc;
	scoreCombinationFunc = calc.scoreCombinationFunc;
	distCutoff = calc.distCutoff;

	return *this;
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

	std::size_t num_features = tgtFeatures.size();

	if (num_features == 0) {
		for (std::size_t i = 0, num_pts = grid.getNumElements(); i < num_pts; i++)
			grid(i) = 0.0;

		return;
	}
	
	featureCoords.resize(num_features);

	for (std::size_t i = 0; i < num_features; i++)
		featureCoords[i] = get3DCoordinates(*tgtFeatures[i]);

	if (!octree)
		octree.reset(new Octree());

	octree->initialize(featureCoords, 4);

	std::size_t num_pts = grid.getNumElements();
	Math::Vector3D grid_pos;
	double max_score = -std::numeric_limits<double>::max();
	double min_score = std::numeric_limits<double>::max();

    for (std::size_t i = 0; i < num_pts; i++) {
		grid.getCoordinates(i, grid_pos);
		featureIndices.clear();

		octree->radiusNeighbors<Octree::L2Distance>(grid_pos, distCutoff, std::back_inserter(featureIndices));

		std::size_t num_inc_ftrs = featureIndices.size();

		if (num_inc_ftrs == 0) {
			grid(i) = 0.0;

		} else {
			partialScores.resize(num_inc_ftrs, false);

			for (std::size_t j = 0; j < num_inc_ftrs; j++) 
				partialScores[j] = scoringFunc(grid_pos, *tgtFeatures[featureIndices[j]]);

			grid(i) = scoreCombinationFunc(partialScores);
		}

		max_score = std::max(grid(i), max_score);
		min_score = std::min(grid(i), min_score);
	}

	if (!normScores)
		return;

	// normalize to range [0, 1]

	double score_range = max_score - min_score;

	if (score_range > 0.0) {
		for (std::size_t i = 0; i < num_pts; i++)
			grid(i) = (grid(i) - min_score) / (max_score - min_score);

	} else {
		for (std::size_t i = 0; i < num_pts; i++)
			grid(i) = 0.0;
	}
}
