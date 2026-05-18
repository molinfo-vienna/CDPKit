/* 
 * AtomDensityGridCalculator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::AtomDensityGridCalculator.
 */

#ifndef CDPL_GRAIL_ATOMDENSITYGRIDCALCULATOR_HPP
#define CDPL_GRAIL_ATOMDENSITYGRIDCALCULATOR_HPP

#include <vector>
#include <cstddef>
#include <memory>
#include <functional>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"


namespace CDPL
{

    // \cond DOC_IMPL_DETAILS
    namespace Internal
    {

        template <typename PT, typename CT, typename ST>
        class Octree;
    }
    // \endcond

    namespace Chem
    {

        class AtomContainer;
    }

    namespace GRAIL
    {

        /**
         * \brief Calculator that fills a spatial grid with combined per-atom density contributions.
         *
         * For each grid cell, the density contributions of all atoms within the configured cutoff
         * distance are evaluated using a user-supplied density function and combined into a single
         * cell value via a user-supplied combination function (defaulting to a sum).
         */
        class CDPL_GRAIL_API AtomDensityGridCalculator
        {

          public:
            /**
             * \brief Default cutoff distance beyond which atoms are not considered.
             */
            static constexpr double DEF_DISTANCE_CUTOFF = 4.5;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %AtomDensityGridCalculator instances.
             */
            typedef std::shared_ptr<AtomDensityGridCalculator> SharedPointer;

            /**
             * \brief Type of the generic functor that evaluates the density contribution of an atom at a query position.
             */
            typedef std::function<double(const Math::Vector3D&, const Math::Vector3D&, const Chem::Atom&)> DensityFunction;

            /**
             * \brief Type of the generic functor that combines per-atom density contributions into a single value.
             */
            typedef std::function<double(const Math::DVector&)>                                            DensityCombinationFunction;

            /**
             * \brief Constructs the \c %AtomDensityGridCalculator instance.
             */
            AtomDensityGridCalculator();

            /**
             * \brief Constructs a copy of the \c %AtomDensityGridCalculator instance \a calc.
             * \param calc The \c %AtomDensityGridCalculator to copy.
             */
            AtomDensityGridCalculator(const AtomDensityGridCalculator& calc);

            /**
             * \brief Constructs the \c %AtomDensityGridCalculator instance with the given density function.
             * \param func The density function.
             */
            AtomDensityGridCalculator(const DensityFunction& func);

            /**
             * \brief Constructs the \c %AtomDensityGridCalculator instance with the given density and density-combination functions.
             * \param density_func The density function.
             * \param comb_func The function used to combine per-atom density contributions.
             */
            AtomDensityGridCalculator(const DensityFunction& density_func, const DensityCombinationFunction& comb_func);

            /**
             * \brief Sets the distance cutoff beyond which atoms are not considered.
             * \param dist The cutoff distance.
             */
            void setDistanceCutoff(double dist);

            /**
             * \brief Returns the currently configured distance cutoff.
             * \return The configured cutoff distance.
             */
            double getDistanceCutoff() const;

            /**
             * \brief Sets the density function used to evaluate per-atom contributions.
             * \param func The density function.
             */
            void setDensityFunction(const DensityFunction& func);

            /**
             * \brief Returns the currently configured density function.
             * \return The configured density function.
             */
            const DensityFunction& getDensityFunction() const;

            /**
             * \brief Sets the function used to combine per-atom density contributions.
             * \param func The density-combination function.
             */
            void setDensityCombinationFunction(const DensityCombinationFunction& func);

            /**
             * \brief Returns the currently configured density-combination function.
             * \return The configured density-combination function.
             */
            const DensityCombinationFunction& getDensityCombinationFunction() const;

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
             * \brief Calculates the combined per-atom density at each cell of \a grid for the given atoms.
             * \param atoms The atoms contributing to the density.
             * \param grid The output grid populated with per-cell density values.
             */
            void calculate(const Chem::AtomContainer& atoms, Grid::DSpatialGrid& grid);

            /**
             * \brief Copy assignment operator.
             * \param calc The other \c %AtomDensityGridCalculator instance.
             * \return A reference to itself.
             */
            AtomDensityGridCalculator& operator=(const AtomDensityGridCalculator& calc);

          private:
            typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
            typedef std::shared_ptr<Octree>                                       OctreePtr;
            typedef std::vector<std::size_t>                                      AtomIndexList;

            Math::DVector                   partialDensities;
            DensityFunction                 densityFunc;
            DensityCombinationFunction      densityCombinationFunc;
            Chem::Atom3DCoordinatesFunction coordsFunc;
            double                          distCutoff;
            OctreePtr                       octree;
            Math::Vector3DArray             atomCoords;
            AtomIndexList                   atomIndices;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_ATOMDENSITYGRIDCALCULATOR_HPP
