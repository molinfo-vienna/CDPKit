/* 
 * FeatureDistanceConstraint.hpp 
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
 * \brief Definition of class CDPL::Pharm::FeatureDistanceConstraint.
 */

#ifndef CDPL_PHARM_FEATUREDISTANCECONSTRAINT_HPP
#define CDPL_PHARM_FEATUREDISTANCECONSTRAINT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief FeatureDistanceConstraint.
         */
        class CDPL_PHARM_API FeatureDistanceConstraint
        {

          public:
            /**
             * \brief Constructs a \c %FeatureDistanceConstraint functor with a 
             *        minimum feature distance of \a min_dist and maximum distance of \a max_dist.
             * \param min_dist The minimum feature pair distance.
             * \param max_dist The maximum feature pair distance.
             */
            FeatureDistanceConstraint(double min_dist, double max_dist):
                minDist(min_dist), maxDist(max_dist) {}

            double getMinDistance() const;

            double getMaxDistance() const;

            bool operator()(const Feature& ftr1, const Feature& ftr2) const;

          private:
            double minDist;
            double maxDist;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREDISTANCECONSTRAINT_HPP
