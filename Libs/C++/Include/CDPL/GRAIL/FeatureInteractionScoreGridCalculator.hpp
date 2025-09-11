/* 
 * FeatureInteractionScoreGridCalculator.hpp 
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

/**
 * \file
 * \brief Definition of class CDPL::GRAIL::FeatureInteractionScoreGridCalculator.
 */

#ifndef CDPL_GRAIL_FEATUREINTERACTIONSCOREGRIDCALCULATOR_HPP
#define CDPL_GRAIL_FEATUREINTERACTIONSCOREGRIDCALCULATOR_HPP

#include <vector>
#include <cstddef>
#include <memory>
#include <functional>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"


namespace CDPL
{

    namespace Internal
    {

        template <typename PT, typename CT, typename ST>
        class Octree;
    }

    namespace Pharm
    {

        class FeatureContainer;
        class Feature;
    } // namespace Pharm

    namespace GRAIL
    {

        /**
         * \brief FeatureInteractionScoreGridCalculator.
         */
        class CDPL_GRAIL_API FeatureInteractionScoreGridCalculator
        {

          public:
            static constexpr double DEF_DISTANCE_CUTOFF = 10.0;

            typedef std::shared_ptr<FeatureInteractionScoreGridCalculator> SharedPointer;

            typedef std::function<bool(const Pharm::Feature&)>                          FeaturePredicate;
            typedef std::function<double(const Math::Vector3D&, const Pharm::Feature&)> ScoringFunction;
            typedef std::function<double(const Math::DVector&)>                         ScoreCombinationFunction;

            struct MaxScoreFunctor
            {

                double operator()(const Math::DVector& scores) const
                {
                    return normInf(scores);
                }
            };

            struct ScoreSumFunctor
            {

                double operator()(const Math::DVector& scores) const
                {
                    return sum(scores);
                }
            };

            FeatureInteractionScoreGridCalculator();

            FeatureInteractionScoreGridCalculator(const ScoringFunction& func);

            FeatureInteractionScoreGridCalculator(const ScoringFunction& scoring_func, const ScoreCombinationFunction& comb_func);

            FeatureInteractionScoreGridCalculator(const FeatureInteractionScoreGridCalculator& calc);

            ~FeatureInteractionScoreGridCalculator();

            void normalizeScores(bool normalize);

            bool scoresNormalized() const;

            void setScoringFunction(const ScoringFunction& func);

            const ScoringFunction& getScoringFunction() const;

            void setScoreCombinationFunction(const ScoreCombinationFunction& func);

            const ScoreCombinationFunction& getScoreCombinationFunction() const;

            void setFeatureSelectionPredicate(const FeaturePredicate& pred);

            const FeaturePredicate& getFeatureSelectionPredicate() const;

            void setDistanceCutoff(double dist);

            double getDistanceCutoff() const;

            void calculate(const Pharm::FeatureContainer& tgt_ftrs, Grid::DSpatialGrid& grid);

            FeatureInteractionScoreGridCalculator& operator=(const FeatureInteractionScoreGridCalculator& calc);

          private:
            typedef std::vector<const Pharm::Feature*>                            FeatureList;
            typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
            typedef std::shared_ptr<Octree>                                       OctreePtr;
            typedef std::vector<std::size_t>                                      FeatureIndexList;

            FeatureList              tgtFeatures;
            Math::DVector            partialScores;
            ScoringFunction          scoringFunc;
            ScoreCombinationFunction scoreCombinationFunc;
            FeaturePredicate         ftrSelectionPred;
            double                   distCutoff;
            OctreePtr                octree;
            Math::Vector3DArray      featureCoords;
            FeatureIndexList         featureIndices;
            bool                     normScores;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_FEATUREINTERACTIONSCOREGRIDCALCULATOR_HPP
