/* 
 * MMFF94BondStretchingInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94BondStretchingInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTIONPARAMETERIZER_HPP

#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Bond;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief Detects and parameterizes the MMFF94 bond-stretching interactions of a molecular graph.
         *
         * For every non-filtered bond the parameterizer looks up the matching MMFF94 bond type-specific
         * parameters from the supplied tables (falling back to the rule-based table when no exact match is
         * available) and appends an MMFF94BondStretchingInteraction instance to the output list.
         */
        class CDPL_FORCEFIELD_API MMFF94BondStretchingInteractionParameterizer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94BondStretchingInteractionParameterizer instances. */
            typedef std::shared_ptr<MMFF94BondStretchingInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94BondStretchingInteractionParameterizer instance using the default MMFF94 parameter tables.
             */
            MMFF94BondStretchingInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and processes the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to parameterize the bond-stretching interactions.
             * \param ia_list Output list receiving the generated MMFF94BondStretchingInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            MMFF94BondStretchingInteractionParameterizer(const Chem::MolecularGraph&          molgraph,
                                                         MMFF94BondStretchingInteractionList& ia_list,
                                                         bool                                 strict);

            /**
             * \brief Sets the filter function used to skip bonds during parameterization.
             * \param func The new filter function (when it returns \c false for a bond pair, the bond is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction2& func);

            /**
             * \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
             * \param func The new numeric atom type lookup function.
             */
            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Sets the function used to look up the MMFF94 bond type index of a bond.
             * \param func The new bond type index lookup function.
             */
            void setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func);

            /**
             * \brief Sets the function used to obtain the set of MMFF94 aromatic rings of the input molecular graph.
             * \param func The new aromatic ring set retrieval function.
             */
            void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

            /**
             * \brief Sets the primary table providing bond type-specific bond-stretching parameters.
             * \param table The new bond-stretching parameter table.
             */
            void setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the fallback table providing rule-based bond-stretching parameters.
             * \param table The new bond-stretching rule parameter table.
             */
            void setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table);

            /**
             * \brief Sets the table providing MMFF94 numeric atom type property data (used by the empirical fallback).
             * \param table The new atom type property table.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Perceives the MMFF94 bond-stretching interactions for \a molgraph and outputs the
             *        corresponding parameter data into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the bond-stretching interactions.
             * \param ia_list Output list receiving the generated MMFF94BondStretchingInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94BondStretchingInteractionList& ia_list, bool strict);

            /**
             * \brief Looks up the MMFF94 bond-stretching parameters for a single bond.
             * \param molgraph The molecular graph the bond belongs to.
             * \param bond The bond whose parameters are queried.
             * \param bond_type_idx Output variable receiving the MMFF94 bond type index.
             * \param force_const Output variable receiving the bond-stretching force constant.
             * \param ref_length Output variable receiving the reference bond length \f$ r_0 \f$.
             * \param strict If \c true, missing parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond,
                               unsigned int& bond_type_idx, double& force_const, double& ref_length, bool strict) const;

          private:
            typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;

            void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond,
                               unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type,
                               double& force_const, double& ref_length) const;

            double calcReferenceBondLength(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond,
                                           const AtomTypePropEntry& type1_prop_entry,
                                           const AtomTypePropEntry& type2_prop_entry) const;

            InteractionFilterFunction2                            filterFunc;
            MMFF94NumericAtomTypeFunction                         atomTypeFunc;
            MMFF94BondTypeIndexFunction                           bondTypeIdxFunc;
            MMFF94RingSetFunction                                 aromRingSetFunc;
            MMFF94BondStretchingParameterTable::SharedPointer     paramTable;
            MMFF94BondStretchingRuleParameterTable::SharedPointer ruleParamTable;
            MMFF94AtomTypePropertyTable::SharedPointer            typePropTable;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTIONPARAMETERIZER_HPP
