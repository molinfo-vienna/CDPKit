/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureDistanceScore.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Pharm::FeatureDistanceScore.
 */

#ifndef CDPL_PHARM_FEATUREDISTANCESCORE_HPP
#define CDPL_PHARM_FEATUREDISTANCESCORE_HPP

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \brief FeatureDistanceScore.
		 */
		class CDPL_PHARM_API FeatureDistanceScore : public FeatureInteractionScore
		{

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %FeatureDistanceScore instances.
			 */
			typedef boost::shared_ptr<FeatureDistanceScore> SharedPointer;

			typedef boost::function1<double, double> DistanceScoringFunction;

			/**
			 * \brief Constructs a \c %FeatureDistanceScore functor with a 
			 *        minimum feature distance of \a min_dist and maximum distance of \a max_dist.
			 * \param min_dist The minimum feature pair distance.
			 * \param max_dist The maximum feature pair distance.
			 */
			FeatureDistanceScore(double min_dist, double max_dist);

			double getMinDistance() const;

			double getMaxDistance() const;

			void setDistanceScoringFunction(const DistanceScoringFunction& func);

			double operator()(const Feature& ftr1, const Feature& ftr2) const;

			double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const;

		  private:
			double                  minDist;
			double                  maxDist;
			DistanceScoringFunction distScoringFunc;
		};
    }
}

#endif // CDPL_PHARM_FEATUREDISTANCESCORE_HPP
