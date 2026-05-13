/* 
 * BuriednessScore.hpp 
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
 * \brief Definition of class CDPL::GRAIL::BuriednessScore.
 */

#ifndef CDPL_GRAIL_BURIEDNESSSCORE_HPP
#define CDPL_GRAIL_BURIEDNESSSCORE_HPP

#include <cstddef>
#include <vector>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
    }

    namespace GRAIL
    {

        /**
         * \brief Functor for the calculation of the \e buriedness of a 3D query position with respect to
         *        the surrounding atoms.
         *
         * The buriedness score is computed by casting a configurable number of test rays evenly distributed
         * over the surface of a probe sphere centered at the query position. For each ray it is checked
         * whether the ray hits an atom of the input container (the van der Waals surface, expanded by a
         * minimum distance) within the probe sphere. The returned score is the fraction of rays that
         * hit an atom and thus reflects how surrounded by the atoms the query position is.
         */
        class CDPL_GRAIL_API BuriednessScore
        {

          public:
            /**
             * \brief Default probe sphere radius.
             */
            static constexpr double DEF_PROBE_RADIUS             = 8.0;

            /**
             * \brief Default minimum required distance between a ray and the van der Waals surface of an atom.
             */
            static constexpr double DEF_MIN_VDW_SURFACE_DISTANCE = 1.0;

            /**
             * \brief Default number of test rays cast from the query position.
             */
            static constexpr std::size_t DEF_NUM_TEST_RAYS       = 200;

            /**
             * \brief Constructs a \c %BuriednessScore instance with the given configuration.
             * \param probe_radius The probe sphere radius.
             * \param min_vdw_surf_dist The minimum distance to the van der Waals surface of an atom.
             * \param num_test_rays The number of rays used in the calculation.
             */
            BuriednessScore(double probe_radius = DEF_PROBE_RADIUS, double min_vdw_surf_dist = DEF_MIN_VDW_SURFACE_DISTANCE,
                            std::size_t num_test_rays = DEF_NUM_TEST_RAYS);

            /**
             * \brief Sets the probe sphere radius.
             * \param radius The probe sphere radius.
             */
            void setProbeRadius(double radius);

            /**
             * \brief Returns the currently configured probe sphere radius.
             * \return The configured probe sphere radius.
             */
            double getProbeRadius() const;

            /**
             * \brief Sets the minimum required distance between a ray and the van der Waals surface of an atom.
             * \param dist The minimum distance to the van der Waals surface.
             */
            void setMinVdWSurfaceDistance(double dist);

            /**
             * \brief Returns the currently configured minimum distance to the van der Waals surface of an atom.
             * \return The configured minimum distance to the van der Waals surface.
             */
            double getMinVdWSurfaceDistance() const;

            /**
             * \brief Sets the number of test rays cast from the query position.
             * \param num_rays The number of test rays.
             */
            void setNumTestRays(std::size_t num_rays);

            /**
             * \brief Returns the currently configured number of test rays.
             * \return The configured number of test rays.
             */
            std::size_t getNumTestRays() const;

            /**
             * \brief Specifies a function for the retrieval of atom 3D-coordinates for buriedness calculation.
             * \param func The atom 3D-coordinates function.
             */
            void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

            /**
             * \brief Returns the function used for the retrieval of atom 3D-coordinates.
             * \return The configured atom 3D-coordinates function.
             */
            const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

            /**
             * \brief Calculates the buriedness score of the query position \a pos with respect to \a atoms.
             * \param pos The 3D position for which to calculate the buriedness score.
             * \param atoms The surrounding atoms used in the calculation.
             * \return The calculated buriedness score, a value in the range <em>[0, 1]</em>.
             */
            double operator()(const Math::Vector3D& pos, const Chem::AtomContainer& atoms);

          private:
            void genSphereSurfacePoints();

            typedef std::vector<Math::Vector3D> PointList;

            double                          probeRadius;
            double                          minVdWSurfaceDist;
            std::size_t                     numTestRays;
            Chem::Atom3DCoordinatesFunction coordsFunc;
            PointList                       probeSurfPoints;
            Util::BitSet                    rayHitsMask;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_BURIEDNESSSCORE_HPP
