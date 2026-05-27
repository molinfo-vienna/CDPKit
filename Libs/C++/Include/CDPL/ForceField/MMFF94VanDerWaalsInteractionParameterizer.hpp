/* 
 * MMFF94VanDerWaalsInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94VanDerWaalsInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTIONPARAMETERIZER_HPP

#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/TopologicalAtomDistanceFunction.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsParameterTable.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ForceField
    {

        /**
         * \brief Detects and parameterizes the MMFF94 Van der Waals interactions of a molecular graph.
         *
         * For every pair of atoms separated by at least three bonds the parameterizer looks up the per-atom type
         * Van der Waals parameters and the donor/acceptor classification from the supplied parameter table,
         * applies the MMFF94 combining rules and emits an MMFF94VanDerWaalsInteraction instance.
         */
        class CDPL_FORCEFIELD_API MMFF94VanDerWaalsInteractionParameterizer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94VanDerWaalsInteractionParameterizer instances. */
            typedef std::shared_ptr<MMFF94VanDerWaalsInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94VanDerWaalsInteractionParameterizer instance using the default MMFF94 parameter tables.
             */
            MMFF94VanDerWaalsInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and processes the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to parameterize the Van der Waals interactions.
             * \param ia_list Output list receiving the generated MMFF94VanDerWaalsInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            MMFF94VanDerWaalsInteractionParameterizer(const Chem::MolecularGraph&       molgraph,
                                                      MMFF94VanDerWaalsInteractionList& ia_list,
                                                      bool                              strict);

            /**
             * \brief Sets the filter function used to skip atom pairs during parameterization.
             * \param func The new filter function (when it returns \c false for an atom pair, the pair is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction2& func);

            /**
             * \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
             * \param func The new numeric atom type lookup function.
             */
            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Sets the function used to determine the topological distance between two atoms (number of bonds along the shortest path).
             * \param func The new topological distance function.
             */
            void setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func);

            /**
             * \brief Sets the table providing MMFF94 numeric atom type Van der Waals parameters and donor/acceptor classifications.
             * \param table The new Van der Waals parameter table.
             */
            void setVanDerWaalsParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table);

            /**
             * \brief Perceives the MMFF94 Van der Waals interactions for \a molgraph and outputs the
             *        corresponding parameter data into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the Van der Waals interactions.
             * \param ia_list Output list receiving the generated MMFF94VanDerWaalsInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94VanDerWaalsInteractionList& ia_list, bool strict);

          private:
            InteractionFilterFunction2                     filterFunc;
            MMFF94NumericAtomTypeFunction                  typeFunc;
            TopologicalAtomDistanceFunction                distFunc;
            MMFF94VanDerWaalsParameterTable::SharedPointer paramTable;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTIONPARAMETERIZER_HPP
