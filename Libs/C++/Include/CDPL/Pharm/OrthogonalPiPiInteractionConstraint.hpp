/* 
 * OrthogonalPiPiInteractionConstraint.hpp 
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
 * \brief Definition of the class CDPL::Pharm::OrthogonalPiPiInteractionConstraint.
 */

#ifndef CDPL_PHARM_ORTHOGONALPIPIINTERACTIONCONSTRAINT_HPP
#define CDPL_PHARM_ORTHOGONALPIPIINTERACTIONCONSTRAINT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief OrthogonalPiPiInteractionConstraint.
         */
        class CDPL_PHARM_API OrthogonalPiPiInteractionConstraint
        {

          public:
            static constexpr double DEF_MAX_V_DISTANCE  = 1.4;
            static constexpr double DEF_MIN_H_DISTANCE  = 4.0;
            static constexpr double DEF_MAX_H_DISTANCE  = 6.0;
            static constexpr double DEF_MAX_ANGLE       = 30.0;
    
            /**
             * \brief Constructs a \c %OrthogonalPiPiInteractionConstraint functor with the specified constraints.
             * \param min_h_dist The minimum allowed aromatic ring center distance in the plane of the vertically oriented ring.
             * \param max_h_dist The maximum allowed aromatic ring center distance in the plane of the vertically oriented ring.
             * \param max_v_dist The maximum allowed distance distance of the center of the horizontally oriented aromatic ring to the plane of the vertically oriented ring.
             * \param max_ang The maximum allowed angle deviation from 90° of the two ring-plane orientation vectors.
             */
            OrthogonalPiPiInteractionConstraint(double min_h_dist = DEF_MIN_H_DISTANCE, double max_h_dist = DEF_MAX_H_DISTANCE,
                                                double max_v_dist = DEF_MAX_V_DISTANCE,double max_ang = DEF_MAX_ANGLE):
                minHDist(min_h_dist), maxHDist(max_h_dist),  maxVDist(max_v_dist), maxAngle(max_ang) {}

            double getMinHDistance() const;

            double getMaxHDistance() const;

            double getMaxVDistance() const;

            double getMaxAngle() const;

            bool operator()(const Feature& ftr1, const Feature& ftr2) const;

          private:
            bool checkDistances(const Math::Vector3D&, const Math::Vector3D&) const;

            double minHDist;
            double maxHDist;
            double maxVDist;
            double maxAngle;
        };
    }
}

#endif // CDPL_PHARM_ORTHOGONALPIPIINTERACTIONCONSTRAINT_HPP
