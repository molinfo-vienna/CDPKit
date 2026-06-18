/* 
 * CationPiInteractionConstraint.hpp 
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
 * \brief Definition of class CDPL::Pharm::CationPiInteractionConstraint.
 */

#ifndef CDPL_PHARM_CATIONPIINTERACTIONCONSTRAINT_HPP
#define CDPL_PHARM_CATIONPIINTERACTIONCONSTRAINT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief Constraint functor that tests whether an aromatic/cationic feature pair satisfies the geometric
         *        criteria for a cation-&pi; interaction (center distance plus cation-to-ring-plane-normal angle).
         */
        class CDPL_PHARM_API CationPiInteractionConstraint
        {

          public:
            /**
             * \brief Default minimum cation-to-aromatic-center distance in &Aring;ngstrom.
             */
            static constexpr double DEF_MIN_DISTANCE = 3.5;

            /**
             * \brief Default maximum cation-to-aromatic-center distance in &Aring;ngstrom.
             */
            static constexpr double DEF_MAX_DISTANCE = 5.5;

            /**
             * \brief Default maximum angle between cation displacement and aromatic-ring plane normal in degrees.
             */
            static constexpr double DEF_MAX_ANGLE    = 45.0;

            /**
             * \brief Constructs a \c %CationPiInteractionConstraint functor with the specified constraints.
             * \param aro_cat \c true if the first feature argument represents the aromatic- and the second one
             *                the cationic-feature, and \c false otherwise.
             * \param min_dist The minimum allowed distance between the cationic- and aromatic-feature centers.
             * \param max_dist The maximum allowed distance between the cationic- and aromatic-feature centers.
             * \param max_ang The maximum allowed angle between the cationic- and aromatic-feature plane normal.
             */
            CationPiInteractionConstraint(bool aro_cat, double min_dist = DEF_MIN_DISTANCE, double max_dist = DEF_MAX_DISTANCE,
                                          double max_ang = DEF_MAX_ANGLE):
                aroCatOrder(aro_cat),
                minDist(min_dist), maxDist(max_dist), maxAngle(max_ang) {}

            /**
             * \brief Returns the currently configured minimum cation-aromatic distance.
             * \return The minimum distance.
             */
            double getMinDistance() const;

            /**
             * \brief Returns the currently configured maximum cation-aromatic distance.
             * \return The maximum distance.
             */
            double getMaxDistance() const;

            /**
             * \brief Returns the currently configured maximum angle between cation displacement and aromatic-plane normal.
             * \return The maximum angle in degrees.
             */
            double getMaxAngle() const;

            /**
             * \brief Tests whether \a ftr1 and \a ftr2 satisfy the geometric cation-&pi; criteria.
             * \param ftr1 The first feature (aromatic or cationic, depending on the constructor flag).
             * \param ftr2 The second feature.
             * \return \c true if the constraint is satisfied, and \c false otherwise.
             */
            bool operator()(const Feature& ftr1, const Feature& ftr2) const;

          private:
            bool   aroCatOrder;
            double minDist;
            double maxDist;
            double maxAngle;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_CATIONPIINTERACTIONCONSTRAINT_HPP
