/* 
 * KuvekPocketDescriptorCalculator.hpp 
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
 * \brief Definition of class CDPL::Descr::KuvekPocketDescriptorCalculator.
 */

#ifndef CDPL_DESCR_BURIEDNESSSCORE_HPP
#define CDPL_DESCR_BURIEDNESSSCORE_HPP

#include <cstddef>
#include <vector>
#include <functional>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
    }

    namespace Descr
    {

        /**
         * \brief Implements the calculation of receptor binding pocket shape and electrostatics descriptors
         *        according to the method devised by Kuvek et al. [\ref KBPD].
         * \since 1.3
         */
        class CDPL_DESCR_API KuvekPocketDescriptorCalculator
        {

          public:
            static constexpr double DEF_PROBE_RADIUS                 = 20.0;
            static constexpr double DEF_MAX_ATOM_TO_SPHERE_SURF_DIST = 2.0;
            static constexpr std::size_t DEF_NUM_TEST_VECTORS        = 492;

            typedef std::function<double(const Chem::Atom&)> AtomChargeFunction;
            
            KuvekPocketDescriptorCalculator(double sphere_radius = DEF_PROBE_RADIUS,
                                            double max_atom_to_sphr_surf_dist = DEF_MAX_ATOM_TO_SPHERE_SURF_DIST,
                                            std::size_t num_test_vecs = DEF_NUM_TEST_VECTORS);

            void setSphereRadius(double radius);

            double getSphereRadius() const;

            void setMaxAtomToSphereSurfaceDistance(double dist);

            double getMaxAtomToSphereSurfaceDistance() const;

            void setNumTestVectors(std::size_t num_vectors);

            std::size_t getNumTestVectors() const;

            /**
             * \brief Specifies a function for the retrieval of atom 3D-coordinates.
             * \param func The atom 3D-coordinates function.
             */
            void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

            const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

            void calculate(const Math::Vector3D& pos, const Chem::AtomContainer& atoms, Math::DVector& descr);

          private:
            void genSphereSurfacePoints();

            typedef std::vector<Math::Vector3D> PointList;

            double                          sphereRadius;
            double                          maxAtomToSphereSurfDist;
            std::size_t                     numTestVectors;
            Chem::Atom3DCoordinatesFunction coordsFunc;
            AtomChargeFunction              chargeFunc;
            PointList                       sphereSurfPoints;
        };
    } // namespace DESCR
} // namespace CDPL

#endif // CDPL_DESCR_BURIEDNESSSCORE_HPP
