/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Pharm::InteractionScoreGridCalculator.
 */

#ifndef CDPL_PHARM_INTERACTIONSCOREGRIDCALCULATOR_HPP
#define CDPL_PHARM_INTERACTIONSCOREGRIDCALCULATOR_HPP

#include <vector>
#include <cstddef>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"


namespace CDPL 
{

	namespace Internal 
	{

		template <typename PT, typename CT, typename ST> class Octree;
	}

    namespace Pharm
    {

		class FeatureContainer;
		class Feature;

		/**
		 * \addtogroup CDPL_PHARM_INTERACTION_SCORE_GRID_CALCULATION
		 * @{
		 */

		/**
		 * \brief InteractionScoreGridCalculator.
		 */
		class CDPL_PHARM_API InteractionScoreGridCalculator
		{

		  public:
			static const double DEF_DISTANCE_CUTOFF;
			
			typedef boost::shared_ptr<InteractionScoreGridCalculator> SharedPointer;

			typedef boost::function1<bool, const Feature&> FeaturePredicate;
			typedef boost::function2<double, const Math::Vector3D&, const Feature&> ScoringFunction;
			typedef boost::function1<double, const Math::DVector&> ScoreCombinationFunction;

			struct MaxScoreFunctor {

				double operator()(const Math::DVector& scores) const {
					return normInf(scores);
				}
			};

			struct ScoreSumFunctor {

				double operator()(const Math::DVector& scores) const {
					return sum(scores);
				}
			};

			InteractionScoreGridCalculator();

			InteractionScoreGridCalculator(const ScoringFunction& func);

			InteractionScoreGridCalculator(const ScoringFunction& scoring_func, const ScoreCombinationFunction& comb_func); 

			InteractionScoreGridCalculator(const InteractionScoreGridCalculator& calc);

			~InteractionScoreGridCalculator();

			void normalizeScores(bool normalize);

			bool scoresNormalized() const;

			void setScoringFunction(const ScoringFunction& func);

			const ScoringFunction& getScoringFunction() const;

			void setScoreCombinationFunction(const ScoreCombinationFunction& func);

			const ScoreCombinationFunction& getScoreCombinationFunction() const;

			void setDistanceCutoff(double dist);

			double getDistanceCutoff() const;

			void calculate(const FeatureContainer& features, Grid::DSpatialGrid& grid, const FeaturePredicate& tgt_ftr_pred);
	
			void calculate(const FeatureContainer& features, Grid::DSpatialGrid& grid);

			InteractionScoreGridCalculator& operator=(const InteractionScoreGridCalculator& calc);

		  private:
			typedef std::vector<const Feature*> FeatureList;
			typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
			typedef boost::shared_ptr<Octree> OctreePtr;
			typedef std::vector<std::size_t> FeatureIndexList;

			FeatureList              tgtFeatures;
			Math::DVector            partialScores;
			ScoringFunction          scoringFunc;
			ScoreCombinationFunction scoreCombinationFunc;
			double                   distCutoff;
			OctreePtr                octree;
			Math::Vector3DArray      featureCoords;
			FeatureIndexList         featureIndices;
			bool                     normScores;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_INTERACTIONSCOREGRIDCALCULATOR_HPP
