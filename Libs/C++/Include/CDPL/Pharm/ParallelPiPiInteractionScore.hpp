/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::Pharm::ParallelPiPiInteractionScore.
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
		 * \brief ParallelPiPiInteractionScore.
		 */
		class CDPL_PHARM_API ParallelPiPiInteractionScore : public FeatureInteractionScore
		{

		  public:
			static constexpr double DEF_MAX_H_DISTANCE = 2.8;
			static constexpr double DEF_MIN_V_DISTANCE = 3.0;
			static constexpr double DEF_MAX_V_DISTANCE = 5.5;
			static constexpr double DEF_MAX_ANGLE      = 20.0;
	
			/**	
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ParallelPiPiInteractionScore instances.
			 */
			typedef std::shared_ptr<ParallelPiPiInteractionScore> SharedPointer;

			typedef std::function<double(double)> DistanceScoringFunction;
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

			double getMinVDistance() const;

			double getMaxVDistance() const;

			double getMaxHDistance() const;

			double getMaxAngle() const;

			void setDistanceScoringFunction(const DistanceScoringFunction& func);

			void setAngleScoringFunction(const AngleScoringFunction& func);

			double operator()(const Feature& ftr1, const Feature& ftr2) const;

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
    }
}

#endif // CDPL_PHARM_PARALLELPIPIINTERACTIONSCORE_HPP
