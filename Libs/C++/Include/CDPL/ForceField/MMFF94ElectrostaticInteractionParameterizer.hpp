/* 
 * MMFF94ElectrostaticInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94ElectrostaticInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONPARAMETERIZER_HPP

#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/TopologicalAtomDistanceFunction.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ForceField
    {

        /**
         * \brief Detects and parameterizes the MMFF94 electrostatic interactions of a molecular graph.
         *
         * For every pair of atoms that is at least 1,4-separated (1,4-pairs use a scaling factor of \e 0.75; 1,5
         * and farther pairs use \e 1.0) the parameterizer emits an MMFF94ElectrostaticInteraction instance storing
         * the partial charges, the configured dielectric constant and the configured distance exponent.
         *
         * \see [\ref MMFF94]
         */
        class CDPL_FORCEFIELD_API MMFF94ElectrostaticInteractionParameterizer
        {

          public:
            /**
             * \brief Default value of the distance exponent in the MMFF94 electrostatic potential (\e 1.0 — Coulomb form).
             */
            static constexpr double DEF_DISTANCE_EXPONENT     = 1.0;

            /**
             * \brief Default value of the dielectric constant (\e 1.0 — gas-phase).
             */
            static constexpr double DEF_DIELECTRIC_CONSTANT   = 1.0;

            /**
             * \brief Convenience constant: dielectric constant of bulk water at room temperature (\e 80.0).
             */
            static constexpr double DIELECTRIC_CONSTANT_WATER = 80.0;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94ElectrostaticInteractionParameterizer instances.
             */
            typedef std::shared_ptr<MMFF94ElectrostaticInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94ElectrostaticInteractionParameterizer instance with default settings.
             */
            MMFF94ElectrostaticInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and processes the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to parameterize the electrostatic interactions.
             * \param ia_list Output list receiving the generated MMFF94ElectrostaticInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            MMFF94ElectrostaticInteractionParameterizer(const Chem::MolecularGraph&         molgraph,
                                                        MMFF94ElectrostaticInteractionList& ia_list,
                                                        bool                                strict);

            /**
             * \brief Sets the filter function used to skip atom pairs during parameterization.
             * \param func The new filter function (when it returns \c false for an atom pair, the pair is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction2& func);

            /**
             * \brief Sets the function used to look up the MMFF94 partial charge of an atom.
             * \param func The new atom charge lookup function.
             */
            void setAtomChargeFunction(const MMFF94AtomChargeFunction& func);

            /**
             * \brief Sets the function used to determine the topological distance between two atoms (number of bonds along the shortest path).
             * \param func The new topological distance function.
             */
            void setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func);

            /**
             * \brief Sets the dielectric constant used by the MMFF94 electrostatic potential.
             * \param de_const The new dielectric constant.
             */
            void setDielectricConstant(double de_const);

            /**
             * \brief Sets the exponent of the MMFF94 distance-dependent electrostatic potential.
             * \param dist_expo The new distance exponent.
             */
            void setDistanceExponent(double dist_expo);

            /**
             * \brief Perceives the MMFF94 electrostatic interactions for \a molgraph and outputs the
             *        corresponding parameter data into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the electrostatic interactions.
             * \param ia_list Output list receiving the generated MMFF94ElectrostaticInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94ElectrostaticInteractionList& ia_list, bool strict);

          private:
            InteractionFilterFunction2      filterFunc;
            MMFF94AtomChargeFunction        chargeFunc;
            TopologicalAtomDistanceFunction distFunc;
            double                          deConst;
            double                          distExpo;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONPARAMETERIZER_HPP
