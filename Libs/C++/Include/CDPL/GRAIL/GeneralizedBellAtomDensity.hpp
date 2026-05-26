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
         * \brief Functor for the evaluation of the generalized-bell atom density contribution of an atom
         *        at a query position.
         *
         * The density falls off with distance from the atom according to a generalized bell function
         * parameterized by the atom's Van der Waals radius (scaled by a configurable factor) and the
         * radius of a probe sphere.
         */
        class CDPL_GRAIL_API GeneralizedBellAtomDensity
        {

          public:
            /**
             * \brief Default probe sphere radius.
             */
            static constexpr double DEF_PROBE_RADIUS          = 0.0;

            /**
             * \brief Default scaling factor applied to atom Van der Waals radii.
             */
            static constexpr double DEF_RADIUS_SCALING_FACTOR = 1.0;

            /**
             * \brief Constructs a \c %GeneralizedBellAtomDensity instance with the given configuration.
             * \param probe_radius The probe sphere radius.
             * \param rad_scaling_factor The scaling factor applied to atom Van der Waals radii.
             */
            GeneralizedBellAtomDensity(double probe_radius = DEF_PROBE_RADIUS, double rad_scaling_factor = DEF_RADIUS_SCALING_FACTOR):
                probeRadius(probe_radius), radiusScalingFactor(rad_scaling_factor) {}

            /**
             * \brief Returns the currently configured probe sphere radius.
             * \return The configured probe sphere radius.
             */
            double getProbeRadius() const;

            /**
             * \brief Returns the currently configured Van der Waals radius scaling factor.
             * \return The configured scaling factor.
             */
            double getRadiusScalingFactor() const;

            /**
             * \brief Evaluates the atom density contribution of \a atom at the query position \a pos.
             * \param pos The 3D query position.
             * \param atom_pos The 3D position of \a atom.
             * \param atom The atom whose density contribution is evaluated.
             * \return The calculated atom density value.
             */
            double operator()(const Math::Vector3D& pos, const Math::Vector3D& atom_pos, const Chem::Atom& atom) const;

          private:
            double probeRadius;
            double radiusScalingFactor;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_GENERALIZEDBELLATOMDENSITY_HPP
