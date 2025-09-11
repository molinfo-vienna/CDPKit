/* 
 * GeneralizedBellAtomDensity.hpp 
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
 * \brief Definition of class CDPL::GRAIL::GeneralizedBellAtomDensity.
 */

#ifndef CDPL_GRAIL_GENERALIZEDBELLATOMDENSITY_HPP
#define CDPL_GRAIL_GENERALIZEDBELLATOMDENSITY_HPP

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
    }

    namespace GRAIL
    {

        /**
         * \brief GeneralizedBellAtomDensity.
         */
        class CDPL_GRAIL_API GeneralizedBellAtomDensity
        {

          public:
            static constexpr double DEF_PROBE_RADIUS          = 0.0;
            static constexpr double DEF_RADIUS_SCALING_FACTOR = 1.0;

            GeneralizedBellAtomDensity(double probe_radius = DEF_PROBE_RADIUS, double rad_scaling_factor = DEF_RADIUS_SCALING_FACTOR):
                probeRadius(probe_radius), radiusScalingFactor(rad_scaling_factor) {}

            double getProbeRadius() const;

            double getRadiusScalingFactor() const;

            double operator()(const Math::Vector3D& pos, const Math::Vector3D& atom_pos, const Chem::Atom& atom) const;

          private:
            double probeRadius;
            double radiusScalingFactor;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_GENERALIZEDBELLATOMDENSITY_HPP
