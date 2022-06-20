/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * XBondingInteractionConstraint.hpp 
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
 * \brief Definition of the class CDPL::Pharm::XBondingInteractionConstraint.
 */

#ifndef CDPL_PHARM_XBONDINGINTERACTIONCONSTRAINT_HPP
#define CDPL_PHARM_XBONDINGINTERACTIONCONSTRAINT_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief XBondingInteractionConstraint.
		 */
		class CDPL_PHARM_API XBondingInteractionConstraint : public std::binary_function<Feature, Feature, bool>
		{

		  public:
			static const double DEF_MIN_AX_DISTANCE;
			static const double DEF_MAX_AX_DISTANCE;
			static const double DEF_MIN_AXB_ANGLE;
			static const double DEF_ACC_ANGLE_TOLERANCE;

			/**
			 * \brief Constructs a \c %XBondingInteractionConstraint functor with the specified constraints.
			 * \param don_acc \c true if the first feature argument represents the donor- and the second one
			 *                the acceptor-feature, and \c false otherwise.
			 * \param min_ax_dist The minimum allowed distance between the halogen-atom and the acceptor-feature.
			 * \param max_ax_dist The maximum allowed distance between the halogen-atom and the acceptor-feature.
			 * \param min_axb_ang The minimum allowed angle between the vectors halogen->acceptor snd halogen->bound atom.
			 * \param acc_ang_tol The maximum allowed angle deviation from the acceptor's preferred X-bonding direction.
			 */
			XBondingInteractionConstraint(bool don_acc, double min_ax_dist = DEF_MIN_AX_DISTANCE, double max_ax_dist = DEF_MAX_AX_DISTANCE,
										  double min_axb_ang = DEF_MIN_AXB_ANGLE, double acc_ang_tol = DEF_ACC_ANGLE_TOLERANCE): 
				donAccOrder(don_acc), minAXDist(min_ax_dist), maxAXDist(max_ax_dist), minAXBAngle(min_axb_ang), accAngleTol(acc_ang_tol) {}

			double getMinAXDistance() const;

			double getMaxAXDistance() const;

			double getMinAXBAngle() const;

			double getAcceptorAngleTolerance() const;

			bool operator()(const Feature& ftr1, const Feature& ftr2) const;

		  private:
			bool   donAccOrder;
			double minAXDist;
			double maxAXDist;
			double minAXBAngle;
			double accAngleTol;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_XBONDINGINTERACTIONCONSTRAINT_HPP
