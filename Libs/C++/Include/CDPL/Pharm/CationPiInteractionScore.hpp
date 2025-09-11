/* 
 * CationPiInteractionScore.hpp 
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
 * \brief Definition of class CDPL::Pharm::CationPiInteractionScore.
 */

#ifndef CDPL_PHARM_CATIONPIINTERACTIONSCORE_HPP
#define CDPL_PHARM_CATIONPIINTERACTIONSCORE_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief CationPiInteractionScore.
         */
        class CDPL_PHARM_API CationPiInteractionScore : public FeatureInteractionScore
        {

          public:
            static constexpr double DEF_MIN_DISTANCE = 3.5;
            static constexpr double DEF_MAX_DISTANCE = 5.5;
            static constexpr double DEF_MAX_ANGLE    = 30.0;

            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CationPiInteractionScore instances.
             */
            typedef std::shared_ptr<CationPiInteractionScore> SharedPointer;

            typedef std::function<double(double)> DistanceScoringFunction;
            typedef std::function<double(double)> AngleScoringFunction;

            /**
             * \brief Constructs a \c %CationPiInteractionScore functor with the specified constraints.
             * \param aro_cat \c true if the first feature argument represents the aromatic- and the second one
             *                the cationic-feature, and \c false otherwise.
             * \param min_dist The minimum allowed distance between the cationic- and aromatic-feature centers.
             * \param max_dist The maximum allowed distance between the cationic- and aromatic-feature centers.
             * \param max_ang The maximum allowed angle between the cationic- and aromatic-feature plane normal.
             */
            CationPiInteractionScore(bool aro_cat, double min_dist = DEF_MIN_DISTANCE, double max_dist = DEF_MAX_DISTANCE,
                                     double max_ang = DEF_MAX_ANGLE);

            double getMinDistance() const;

            double getMaxDistance() const;

            double getMaxAngle() const;

            void setDistanceScoringFunction(const DistanceScoringFunction& func);

            void setAngleScoringFunction(const AngleScoringFunction& func);

            double operator()(const Feature& ftr1, const Feature& ftr2) const;

            double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const;

          private:
            bool                    aroCatOrder;
            double                  minDist;
            double                  maxDist;
            double                  maxAngle;
            DistanceScoringFunction distScoringFunc;
            AngleScoringFunction    angleScoringFunc;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_CATIONPIINTERACTIONSCORE_HPP
