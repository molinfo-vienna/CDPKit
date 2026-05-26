/* 
 * BuriednessGridCalculator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::BuriednessGridCalculator.
 */

#ifndef CDPL_GRAIL_BURIEDNESSGRIDCALCULATOR_HPP
#define CDPL_GRAIL_BURIEDNESSGRIDCALCULATOR_HPP

#include <vector>
#include <cstddef>
#include <memory>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/GRAIL/BuriednessScore.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Internal
    {

        template <typename PT, typename CT, typename ST>
        class Octree;
    }

    namespace GRAIL
    {

        /**
         * \brief Calculator that fills a spatial grid with per-cell buriedness scores derived from
         *        GRAIL::BuriednessScore.
         *
         * For each grid cell, the buriedness score with respect to the surrounding atoms is computed
         * and stored. The configurable parameters (probe radius, minimum Van der Waals surface
         * distance, number of test rays) are forwarded to the underlying BuriednessScore instance.
         */
        class CDPL_GRAIL_API BuriednessGridCalculator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BuriednessGridCalculator instances.
             */
            typedef std::shared_ptr<BuriednessGridCalculator> SharedPointer;

            /**
             * \brief Constructs the \c %BuriednessGridCalculator instance.
             */
            BuriednessGridCalculator();

            /**
             * \brief Constructs a copy of the \c %BuriednessGridCalculator instance \a calc.
             * \param calc The \c %BuriednessGridCalculator to copy.
             */
            BuriednessGridCalculator(const BuriednessGridCalculator& calc);

            /**
             * \brief Sets the probe sphere radius used by the underlying GRAIL::BuriednessScore.
             * \param radius The probe sphere radius.
             */
            void setProbeRadius(double radius);

            /**
             * \brief Returns the currently configured probe sphere radius.
             * \return The configured probe sphere radius.
             */
            double getProbeRadius() const;

            /**
             * \brief Sets the minimum required distance between a ray and the Van der Waals surface of an atom.
             * \param dist The minimum distance to the Van der Waals surface.
             */
            void setMinVdWSurfaceDistance(double dist);

            /**
             * \brief Returns the currently configured minimum distance to the Van der Waals surface of an atom.
             * \return The configured minimum distance to the Van der Waals surface.
             */
            double getMinVdWSurfaceDistance() const;

            /**
             * \brief Sets the number of test rays cast from each grid cell.
             * \param num_rays The number of test rays.
             */
            void setNumTestRays(std::size_t num_rays);

            /**
             * \brief Returns the currently configured number of test rays.
             * \return The configured number of test rays.
             */
            std::size_t getNumTestRays() const;

            /**
             * \brief Specifies a function for the retrieval of atom 3D-coordinates for grid calculation.
             * \param func The atom 3D-coordinates function.
             */
            void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

            /**
             * \brief Returns the function used for the retrieval of atom 3D-coordinates.
             * \return The configured atom 3D-coordinates function.
             */
            const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

            /**
             * \brief Calculates the buriedness value at each cell of \a grid for the given atoms.
             * \param atoms The atoms used as the environment for the buriedness calculation.
             * \param grid The output grid populated with per-cell buriedness scores.
             */
            void calculate(const Chem::AtomContainer& atoms, Grid::DSpatialGrid& grid);

            /**
             * \brief Copy assignment operator.
             * \param calc The other \c %BuriednessGridCalculator instance.
             * \return A reference to itself.
             */
            BuriednessGridCalculator& operator=(const BuriednessGridCalculator& calc);

          private:
            typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
            typedef std::shared_ptr<Octree>                                       OctreePtr;
            typedef std::vector<std::size_t>                                      AtomIndexList;

            BuriednessScore     buriednessScore;
            OctreePtr           octree;
            Math::Vector3DArray atomCoords;
            AtomIndexList       atomIndices;
            Chem::Fragment      atomSubset;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_BURIEDNESSGRIDCALCULATOR_HPP
