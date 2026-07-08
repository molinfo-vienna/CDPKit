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
         * \brief Implements the algorithm devised by Kuvek et al. [\ref KBPD] for the calculation of receptor 
         *        binding pocket shape and surface electrostatics descriptors.
         * \since 1.3
         */
        class CDPL_DESCR_API KuvekPocketDescriptorCalculator
        {

          public:
            /**
             * \brief Default radius of the probe sphere centered at the query position.
             */
            static constexpr double DEF_PROBE_RADIUS                 = 20.0;

            /**
             * \brief Default maximum distance between an atom and the probe sphere surface for the atom to contribute.
             */
            static constexpr double DEF_MAX_ATOM_TO_SPHERE_SURF_DIST = 2.0;

            /**
             * \brief Default number of test vectors used to sample the probe sphere surface.
             */
            static constexpr std::size_t DEF_NUM_TEST_VECTORS        = 492;

            /**
             * \brief Type of the generic functor used to retrieve the partial charge of an atom.
             */
            typedef std::function<double(const Chem::Atom&)> AtomChargeFunction;

            /**
             * \brief Constructs a \c %KuvekPocketDescriptorCalculator instance with the given configuration.
             * \param sphere_radius The probe sphere radius.
             * \param num_test_vecs The number of test vectors used to sample the probe sphere surface.
             * \param max_atom_to_sphr_surf_dist The maximum distance between an atom and the probe sphere surface for the atom to contribute.
             */
            KuvekPocketDescriptorCalculator(double sphere_radius = DEF_PROBE_RADIUS,
                                            std::size_t num_test_vecs = DEF_NUM_TEST_VECTORS,
                                            double max_atom_to_sphr_surf_dist = DEF_MAX_ATOM_TO_SPHERE_SURF_DIST);

            /**
             * \brief Sets the probe sphere radius.
             * \param radius The probe sphere radius.
             */
            void setSphereRadius(double radius);

            /**
             * \brief Returns the currently configured probe sphere radius.
             * \return The configured probe sphere radius.
             */
            double getSphereRadius() const;

            /**
             * \brief Sets the maximum distance between an atom and the probe sphere surface for the atom to contribute.
             * \param dist The maximum distance to the probe sphere surface.
             */
            void setMaxAtomToSphereSurfaceDistance(double dist);

            /**
             * \brief Returns the currently configured maximum atom-to-sphere-surface distance.
             * \return The configured maximum distance.
             */
            double getMaxAtomToSphereSurfaceDistance() const;

            /**
             * \brief Sets the number of test vectors used to sample the probe sphere surface.
             * \param num_vectors The number of test vectors.
             */
            void setNumTestVectors(std::size_t num_vectors);

            /**
             * \brief Returns the currently configured number of test vectors.
             * \return The configured number of test vectors.
             */
            std::size_t getNumTestVectors() const;

            /**
             * \brief Returns the test vector at index \a idx (generated on demand).
             * \param idx The test vector index.
             * \return A \c const reference to the test vector.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumTestVectors()).
             */
            const Math::Vector3D& getTestVector(std::size_t idx);

            /**
             * \brief Specifies a function for the retrieval of atom 3D-coordinates.
             * \param func The atom 3D-coordinates function.
             */
            void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

            /**
             * \brief Returns the function used for the retrieval of atom 3D-coordinates.
             * \return The configured atom 3D-coordinates function.
             */
            const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

            /**
             * \brief Specifies a function for the retrieval of atom charges.
             * \param func The atom charge retrieval function.
             * \note By default, formal charges will be used.
             */
            void setAtomChargeFunction(const AtomChargeFunction& func);

            /**
             * \brief Returns the function used for the retrieval of atom charges.
             * \return The configured atom charge function.
             */
            const AtomChargeFunction& getAtomChargeFunction() const;

            /**
             * \brief Calculates the Kuvek pocket descriptor at the given query position.
             * \param sphere_ctr The 3D position of the probe sphere center.
             * \param atoms The atoms used as the environment for the calculation.
             * \param descr The output descriptor vector.
             */
            void calculate(const Math::Vector3D& sphere_ctr, const Chem::AtomContainer& atoms, Math::DVector& descr);

          private:
            void genTestVectors();
          
            typedef std::vector<Math::Vector3D> PointList;

            double                          sphereRadius;
            std::size_t                     numTestVectors;
            double                          maxAtomToSphereSurfDist;
            Chem::Atom3DCoordinatesFunction coordsFunc;
            AtomChargeFunction              chargeFunc;
            PointList                       testVectors;
        };
    } // namespace DESCR
} // namespace CDPL

#endif // CDPL_DESCR_BURIEDNESSSCORE_HPP
