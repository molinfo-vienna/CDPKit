/* 
 * MMFF94OutOfPlaneBendingInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTIONPARAMETERIZER_HPP

#include <vector>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief Detects and parameterizes the MMFF94 out-of-plane bending interactions of a molecular graph.
         *
         * For every atom \e j with exactly three neighbors that is a trigonal center (per the MMFF94 atom type
         * properties) the parameterizer generates three out-of-plane parameter sets - one for each permutation of the
         * three neighbors as the out-of-plane atom \e l with the remaining two as in-plane terminal atoms.
         * The required out-of-plane force constants are taken from the parameter table, falling back through
         * the primary-to-parameter atom type map when no exact entry is available.
         */
        class CDPL_FORCEFIELD_API MMFF94OutOfPlaneBendingInteractionParameterizer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94OutOfPlaneBendingInteractionParameterizer instances. */
            typedef std::shared_ptr<MMFF94OutOfPlaneBendingInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94OutOfPlaneBendingInteractionParameterizer instance using the default MMFF94 parameter tables.
             */
            MMFF94OutOfPlaneBendingInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and processes the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to parameterize the out-of-plane bending interactions.
             * \param ia_list Output list receiving the generated MMFF94OutOfPlaneBendingInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            MMFF94OutOfPlaneBendingInteractionParameterizer(const Chem::MolecularGraph&             molgraph,
                                                            MMFF94OutOfPlaneBendingInteractionList& ia_list,
                                                            bool                                    strict);

            /**
             * \brief Sets the filter function used to skip atom quadruplets during parameterization.
             * \param func The new four-atom filter function (when it returns \c false, the quadruplet is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction4& func);

            /**
             * \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
             * \param func The new numeric atom type lookup function.
             */
            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Sets the table providing the out-of-plane bending force constants.
             * \param table The new out-of-plane bending parameter table.
             */
            void setOutOfPlaneBendingParameterTable(const MMFF94OutOfPlaneBendingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the table providing MMFF94 numeric atom type property data (used to identify trigonal centers).
             * \param table The new atom type property table.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Sets the map used to translate primary atom types into their corresponding parameter atom types.
             * \param map The new primary-to-parameter atom type map.
             */
            void setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

            /**
             * \brief Perceives the MMFF94 out-of-plane bending interactions for \a molgraph and outputs the
             *        corresponding parameter data into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the out-of-plane bending interactions.
             * \param ia_list Output list receiving the generated MMFF94OutOfPlaneBendingInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94OutOfPlaneBendingInteractionList& ia_list, bool strict);

          private:
            typedef std::vector<const Chem::Atom*> AtomList;

            double getForceConstant(const Chem::MolecularGraph& molgraph, unsigned int ctr_atom_type,
                                    std::size_t ctr_atom_idx, const AtomList& nbr_atoms, bool strict) const;

            double getForceConstant(const Chem::MolecularGraph& molgraph, unsigned int ctr_atom_type,
                                    std::size_t ctr_atom_idx, unsigned int nbr_atom_types[3], const AtomList& nbr_atoms) const;

            InteractionFilterFunction4                           filterFunc;
            MMFF94NumericAtomTypeFunction                        atomTypeFunc;
            MMFF94OutOfPlaneBendingParameterTable::SharedPointer paramTable;
            MMFF94AtomTypePropertyTable::SharedPointer           typePropTable;
            MMFF94PrimaryToParameterAtomTypeMap::SharedPointer   paramTypeMap;
            AtomList                                             nbrAtoms;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTIONPARAMETERIZER_HPP
