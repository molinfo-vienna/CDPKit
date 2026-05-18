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
         * \brief Calculator that fills a spatial grid with per-cell feature-interaction scores against
         *        a set of target pharmacophore features.
         *
         * For each grid cell, the configured scoring function is evaluated against every target
         * feature within the configured cutoff distance and the resulting scores are combined into
         * a single cell value via a user-supplied combination function (defaulting to a sum).
         * The set of considered target features can be filtered by a feature-selection predicate.
         */
        class CDPL_GRAIL_API FeatureInteractionScoreGridCalculator
        {

          public:
            /**
             * \brief Default cutoff distance beyond which target features are not considered.
             */
            static constexpr double DEF_DISTANCE_CUTOFF = 10.0;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureInteractionScoreGridCalculator instances.
             */
            typedef std::shared_ptr<FeatureInteractionScoreGridCalculator> SharedPointer;

            /**
             * \brief Type of the generic functor that decides whether a target feature shall be considered.
             */
            typedef std::function<bool(const Pharm::Feature&)>                          FeaturePredicate;

            /**
             * \brief Type of the generic functor that scores the interaction between a grid cell and a target feature.
             */
            typedef std::function<double(const Math::Vector3D&, const Pharm::Feature&)> ScoringFunction;

            /**
             * \brief Type of the generic functor that combines per-feature scores into a single grid cell value.
             */
            typedef std::function<double(const Math::DVector&)>                         ScoreCombinationFunction;

            /**
             * \brief Score-combination functor returning the maximum (infinity norm) of the per-feature scores.
             */
            struct MaxScoreFunctor
            {

                double operator()(const Math::DVector& scores) const
                {
                    return normInf(scores);
                }
            };

            /**
             * \brief Score-combination functor returning the sum of the per-feature scores.
             */
            struct ScoreSumFunctor
            {

                double operator()(const Math::DVector& scores) const
                {
                    return sum(scores);
                }
            };

            /**
             * \brief Constructs the \c %FeatureInteractionScoreGridCalculator instance.
             */
            FeatureInteractionScoreGridCalculator();

            /**
             * \brief Constructs the \c %FeatureInteractionScoreGridCalculator instance with the given scoring function.
             * \param func The scoring function.
             */
            FeatureInteractionScoreGridCalculator(const ScoringFunction& func);

            /**
             * \brief Constructs the \c %FeatureInteractionScoreGridCalculator instance with the given scoring and score-combination functions.
             * \param scoring_func The scoring function.
             * \param comb_func The function used to combine per-feature scores.
             */
            FeatureInteractionScoreGridCalculator(const ScoringFunction& scoring_func, const ScoreCombinationFunction& comb_func);

            /**
             * \brief Constructs a copy of the \c %FeatureInteractionScoreGridCalculator instance \a calc.
             * \param calc The \c %FeatureInteractionScoreGridCalculator to copy.
             */
            FeatureInteractionScoreGridCalculator(const FeatureInteractionScoreGridCalculator& calc);

            /**
             * \brief Destructor.
             */
            ~FeatureInteractionScoreGridCalculator();

            /**
             * \brief Enables or disables normalization of the combined per-cell scores to the range [0, 1].
             * \param normalize If \c true, the combined scores are normalized.
             */
            void normalizeScores(bool normalize);

            /**
             * \brief Tells whether the combined per-cell scores are normalized.
             * \return \c true if the combined scores are normalized, and \c false otherwise.
             */
            bool scoresNormalized() const;

            /**
             * \brief Sets the scoring function used to score the interaction between a grid cell and a target feature.
             * \param func The scoring function.
             */
            void setScoringFunction(const ScoringFunction& func);

            /**
             * \brief Returns the currently configured scoring function.
             * \return The configured scoring function.
             */
            const ScoringFunction& getScoringFunction() const;

            /**
             * \brief Sets the function used to combine per-feature scores into a single grid cell value.
             * \param func The score-combination function.
             */
            void setScoreCombinationFunction(const ScoreCombinationFunction& func);

            /**
             * \brief Returns the currently configured score-combination function.
             * \return The configured score-combination function.
             */
            const ScoreCombinationFunction& getScoreCombinationFunction() const;

            /**
             * \brief Sets the predicate that decides whether a target feature shall be considered.
             * \param pred The feature-selection predicate.
             */
            void setFeatureSelectionPredicate(const FeaturePredicate& pred);

            /**
             * \brief Returns the currently configured feature-selection predicate.
             * \return The configured feature-selection predicate.
             */
            const FeaturePredicate& getFeatureSelectionPredicate() const;

            /**
             * \brief Sets the cutoff distance beyond which target features are not considered.
             * \param dist The cutoff distance.
             */
            void setDistanceCutoff(double dist);

            /**
             * \brief Returns the currently configured cutoff distance.
             * \return The configured cutoff distance.
             */
            double getDistanceCutoff() const;

            /**
             * \brief Calculates the feature-interaction score at each cell of \a grid against \a tgt_ftrs.
             * \param tgt_ftrs The container with the target features.
             * \param grid The output grid populated with per-cell scores.
             */
            void calculate(const Pharm::FeatureContainer& tgt_ftrs, Grid::DSpatialGrid& grid);

            /**
             * \brief Copy assignment operator.
             * \param calc The other \c %FeatureInteractionScoreGridCalculator instance.
             * \return A reference to itself.
             */
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
