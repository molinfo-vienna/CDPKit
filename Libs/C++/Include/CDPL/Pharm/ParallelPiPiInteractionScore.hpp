/* 
 * ParallelPiPiInteractionScore.hpp 
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
 * \brief Definition of class CDPL::Pharm::ParallelPiPiInteractionScore.
 */

#ifndef CDPL_PHARM_PARALLELPIPIINTERACTIONSCORE_HPP
#define CDPL_PHARM_PARALLELPIPIINTERACTIONSCORE_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief Pharm::FeatureInteractionScore implementation that scores an aromatic feature pair for a parallel
         *        (sandwich/displaced) &pi;-&pi; interaction by combining per-component scores for vertical/horizontal
         *        center separations and ring-plane-normal angle.
         */
        class CDPL_PHARM_API ParallelPiPiInteractionScore : public FeatureInteractionScore
        {

          public:
            /** \brief Default maximum in-plane (horizontal) ring-center displacement in &Aring;ngstrom. */
            static constexpr double DEF_MAX_H_DISTANCE = 2.8;
            /** \brief Default minimum out-of-plane (vertical) ring-center separation in &Aring;ngstrom. */
            static constexpr double DEF_MIN_V_DISTANCE = 3.0;
            /** \brief Default maximum out-of-plane (vertical) ring-center separation in &Aring;ngstrom. */
            static constexpr double DEF_MAX_V_DISTANCE = 5.5;
            /** \brief Default maximum angle deviation from 0&deg; of the two ring-plane normals in degrees. */
            static constexpr double DEF_MAX_ANGLE      = 20.0;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ParallelPiPiInteractionScore instances.
             */
            typedef std::shared_ptr<ParallelPiPiInteractionScore> SharedPointer;

            /** \brief Type of the function mapping a feature-pair distance to its score contribution. */
            typedef std::function<double(double)> DistanceScoringFunction;
            /** \brief Type of the function mapping a ring-plane angle to its score contribution. */
            typedef std::function<double(double)> AngleScoringFunction;

            /**
             * \brief Constructs a \c %ParallelPiPiInteractionScore functor with the specified constraints.
             * \param min_v_dist The minimum allowed distance of the two feature-positions orthogonal to the ring-planes.
             * \param max_v_dist The maximum allowed distance of the two feature-positions orthogonal to the ring-planes.
             * \param max_h_dist The maximum allowed distance of the feature-position along the their ring-planes.
             * \param max_ang The maximum allowed angle deviation from 0° of the two ring-plane orientation vectors.
             */
            ParallelPiPiInteractionScore(double min_v_dist = DEF_MIN_V_DISTANCE, double max_v_dist = DEF_MAX_V_DISTANCE,
                                         double max_h_dist = DEF_MAX_H_DISTANCE, double max_ang = DEF_MAX_ANGLE);

            /**
             * \brief Returns the currently configured minimum out-of-plane ring-center separation.
             * \return The minimum vertical distance.
             */
            double getMinVDistance() const;

            /**
             * \brief Returns the currently configured maximum out-of-plane ring-center separation.
             * \return The maximum vertical distance.
             */
            double getMaxVDistance() const;

            /**
             * \brief Returns the currently configured maximum in-plane ring-center displacement.
             * \return The maximum horizontal distance.
             */
            double getMaxHDistance() const;

            /**
             * \brief Returns the currently configured maximum deviation from a 0&deg; angle between the two ring-plane normals.
             * \return The maximum angle deviation in degrees.
             */
            double getMaxAngle() const;

            /**
             * \brief Specifies the function that maps a feature-pair distance to its score contribution.
             * \param func The distance-scoring function.
             */
            void setDistanceScoringFunction(const DistanceScoringFunction& func);

            /**
             * \brief Specifies the function that maps the ring-plane-normal angle to its score contribution.
             * \param func The angle-scoring function.
             */
            void setAngleScoringFunction(const AngleScoringFunction& func);

            /**
             * \brief Evaluates the parallel &pi;-&pi; interaction score between features \a ftr1 and \a ftr2.
             * \param ftr1 The first aromatic feature.
             * \param ftr2 The second aromatic feature.
             * \return The parallel &pi;-&pi; interaction score.
             */
            double operator()(const Feature& ftr1, const Feature& ftr2) const;

            /**
             * \brief Evaluates the parallel &pi;-&pi; interaction score with the first feature represented only by its 3D position \a ftr1_pos.
             * \param ftr1_pos The 3D position of the first feature.
             * \param ftr2 The second aromatic feature.
             * \return The parallel &pi;-&pi; interaction score.
             */
            double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const;

          private:
            double calcDistanceScore(const Math::Vector3D& orient, const Math::Vector3D& ftr1_ftr2_vec) const;

            double                  minVDist;
            double                  maxVDist;
            double                  maxHDist;
            double                  maxAngle;
            DistanceScoringFunction distScoringFunc;
            AngleScoringFunction    angleScoringFunc;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PARALLELPIPIINTERACTIONSCORE_HPP
