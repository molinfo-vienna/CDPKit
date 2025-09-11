/* 
 * IonicInteractionConstraint.hpp 
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
 * \brief Definition of class CDPL::Pharm::IonicInteractionConstraint.
 */

#ifndef CDPL_PHARM_IONICINTERACTIONCONSTRAINT_HPP
#define CDPL_PHARM_IONICINTERACTIONCONSTRAINT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureDistanceConstraint.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief IonicInteractionConstraint.
         */
        class CDPL_PHARM_API IonicInteractionConstraint : public FeatureDistanceConstraint
        {

          public:
            static constexpr double DEF_MIN_DISTANCE = 1.5;
            static constexpr double DEF_MAX_DISTANCE = 5.5;

            /**
             * \brief Constructs a \c %IonicInteractionConstraint functor with a 
             *        minimum ionic-feature pair distance of \a min_dist and a maximum distance of \a max_dist.
             * \param min_dist The minimum allowed feature pair distance.
             * \param max_dist The maximum allowed feature pair distance.
             */
            IonicInteractionConstraint(double min_dist = DEF_MIN_DISTANCE, double max_dist = DEF_MAX_DISTANCE):
                FeatureDistanceConstraint(min_dist, max_dist) {}
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_IONICINTERACTIONCONSTRAINT_HPP
