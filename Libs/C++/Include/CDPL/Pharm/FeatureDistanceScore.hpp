/* 
 * FeatureDistanceScore.hpp 
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
 * \brief Definition of class CDPL::Pharm::FeatureDistanceScore.
 */

#ifndef CDPL_PHARM_FEATUREDISTANCESCORE_HPP
#define CDPL_PHARM_FEATUREDISTANCESCORE_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief Pharm::FeatureInteractionScore implementation that scores a feature pair based on whether their 3D-position
         *        distance falls within a configured [min, max] interval.
         */
        class CDPL_PHARM_API FeatureDistanceScore : public FeatureInteractionScore
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureDistanceScore instances.
             */
            typedef std::shared_ptr<FeatureDistanceScore> SharedPointer;

            /** \brief Type of the function mapping a raw feature-pair distance to a score contribution. */
            typedef std::function<double(double)> DistanceScoringFunction;

            /**
             * \brief Constructs a \c %FeatureDistanceScore functor with a
             *        minimum feature distance of \a min_dist and maximum distance of \a max_dist.
             * \param min_dist The minimum feature pair distance.
             * \param max_dist The maximum feature pair distance.
             */
            FeatureDistanceScore(double min_dist, double max_dist);

            /**
             * \brief Returns the currently configured minimum feature pair distance.
             * \return The minimum distance.
             */
            double getMinDistance() const;

            /**
             * \brief Returns the currently configured maximum feature pair distance.
             * \return The maximum distance.
             */
            double getMaxDistance() const;

            /**
             * \brief Specifies the function that maps a feature-pair distance to its score contribution.
             * \param func The distance-scoring function.
             */
            void setDistanceScoringFunction(const DistanceScoringFunction& func);

            /**
             * \brief Evaluates the distance-based interaction score between features \a ftr1 and \a ftr2.
             * \param ftr1 The first feature.
             * \param ftr2 The second feature.
             * \return The distance-based interaction score.
             */
            double operator()(const Feature& ftr1, const Feature& ftr2) const;

            /**
             * \brief Evaluates the distance-based interaction score with the first feature represented only by its 3D position \a ftr1_pos.
             * \param ftr1_pos The 3D position of the first feature.
             * \param ftr2 The second feature.
             * \return The distance-based interaction score.
             */
            double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const;

          private:
            double                  minDist;
            double                  maxDist;
            DistanceScoringFunction distScoringFunc;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREDISTANCESCORE_HPP
