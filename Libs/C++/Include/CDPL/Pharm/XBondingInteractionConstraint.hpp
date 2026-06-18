/* 
 * XBondingInteractionConstraint.hpp 
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
 * \brief Definition of class CDPL::Pharm::XBondingInteractionConstraint.
 */

#ifndef CDPL_PHARM_XBONDINGINTERACTIONCONSTRAINT_HPP
#define CDPL_PHARM_XBONDINGINTERACTIONCONSTRAINT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief Constraint functor that tests whether a halogen-bond donor/acceptor feature pair satisfies the geometric
         *        criteria for a halogen bond (halogen-acceptor distance plus the two characteristic angles).
         */
        class CDPL_PHARM_API XBondingInteractionConstraint
        {

          public:
            /**
             * \brief Default minimum halogen-acceptor distance in &Aring;ngstrom.
             */
            static constexpr double DEF_MIN_AX_DISTANCE = 1.6;

            /**
             * \brief Default maximum halogen-acceptor distance in &Aring;ngstrom.
             */
            static constexpr double DEF_MAX_AX_DISTANCE = 3.75;

            /**
             * \brief Default minimum acceptor-halogen-bound-atom angle in degrees.
             */
            static constexpr double DEF_MIN_AXB_ANGLE   = 135.0;

            /**
             * \brief Default maximum deviation from the acceptor's preferred X-bonding direction in degrees.
             */
            static constexpr double DEF_MAX_ACC_ANGLE   = 45.0;

            /**
             * \brief Constructs a \c %XBondingInteractionConstraint functor with the specified constraints.
             * \param don_acc \c true if the first feature argument represents the donor- and the second one
             *                the acceptor-feature, and \c false otherwise.
             * \param min_ax_dist The minimum allowed distance between the halogen-atom and the acceptor-feature.
             * \param max_ax_dist The maximum allowed distance between the halogen-atom and the acceptor-feature.
             * \param min_axb_ang The minimum allowed angle between the vectors halogen->acceptor snd halogen->bound atom.
             * \param max_acc_ang The maximum allowed angle deviation from the acceptor's preferred X-bonding direction.
             */
            XBondingInteractionConstraint(bool don_acc, double min_ax_dist = DEF_MIN_AX_DISTANCE, double max_ax_dist = DEF_MAX_AX_DISTANCE,
                                          double min_axb_ang = DEF_MIN_AXB_ANGLE, double max_acc_ang = DEF_MAX_ACC_ANGLE):
                donAccOrder(don_acc),
                minAXDist(min_ax_dist), maxAXDist(max_ax_dist), minAXBAngle(min_axb_ang), maxAccAngle(max_acc_ang) {}

            /**
             * \brief Returns the currently configured minimum halogen-acceptor distance.
             * \return The minimum AX distance.
             */
            double getMinAXDistance() const;

            /**
             * \brief Returns the currently configured maximum halogen-acceptor distance.
             * \return The maximum AX distance.
             */
            double getMaxAXDistance() const;

            /**
             * \brief Returns the currently configured minimum acceptor-halogen-bound-atom angle.
             * \return The minimum AXB angle in degrees.
             */
            double getMinAXBAngle() const;

            /**
             * \brief Returns the currently configured maximum deviation from the acceptor's preferred X-bonding direction.
             * \return The maximum acceptor angle in degrees.
             */
            double getMaxAcceptorAngle() const;

            /**
             * \brief Tests whether \a ftr1 and \a ftr2 satisfy the geometric halogen-bond criteria.
             * \param ftr1 The first feature (donor or acceptor, depending on the constructor flag).
             * \param ftr2 The second feature.
             * \return \c true if the constraint is satisfied, and \c false otherwise.
             */
            bool operator()(const Feature& ftr1, const Feature& ftr2) const;

          private:
            bool   donAccOrder;
            double minAXDist;
            double maxAXDist;
            double minAXBAngle;
            double maxAccAngle;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_XBONDINGINTERACTIONCONSTRAINT_HPP
