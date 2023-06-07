/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ParallelPiPiInteractionConstraint.hpp 
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
 * \brief Definition of the class CDPL::Pharm::ParallelPiPiInteractionConstraint.
 */

#ifndef CDPL_PHARM_PARALLELPIPIINTERACTIONCONSTRAINT_HPP
#define CDPL_PHARM_PARALLELPIPIINTERACTIONCONSTRAINT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \brief ParallelPiPiInteractionConstraint.
		 */
		class CDPL_PHARM_API ParallelPiPiInteractionConstraint
		{

		  public:
			static constexpr double DEF_MAX_H_DISTANCE = 2.8;
			static constexpr double DEF_MIN_V_DISTANCE = 3.0;
			static constexpr double DEF_MAX_V_DISTANCE = 5.5;
			static constexpr double DEF_MAX_ANGLE      = 30.0;
	
			/**
			 * \brief Constructs a \c %ParallelPiPiInteractionConstraint functor with the specified constraints.
			 * \param min_v_dist The minimum allowed distance of the two feature-positions orthogonal to the ring-planes.
			 * \param max_v_dist The maximum allowed distance of the two feature-positions orthogonal to the ring-planes.
			 * \param max_h_dist The maximum allowed distance of the feature-position along the their ring-planes.
			 * \param max_ang The maximum allowed angle deviation from 0° of the two ring-plane orientation vectors.
			 */
			ParallelPiPiInteractionConstraint(double min_v_dist = DEF_MIN_V_DISTANCE, double max_v_dist = DEF_MAX_V_DISTANCE,
											  double max_h_dist = DEF_MAX_H_DISTANCE, double max_ang = DEF_MAX_ANGLE):
				minVDist(min_v_dist), maxVDist(max_v_dist),  maxHDist(max_h_dist), maxAngle(max_ang) {}

			double getMinVDistance() const;

			double getMaxVDistance() const;

			double getMaxHDistance() const;

			double getMaxAngle() const;

			bool operator()(const Feature& ftr1, const Feature& ftr2) const;

		  private:
			double minVDist;
			double maxVDist;
			double maxHDist;
			double maxAngle;
		};
    }
}

#endif // CDPL_PHARM_PARALLELPIPIINTERACTIONCONSTRAINT_HPP
