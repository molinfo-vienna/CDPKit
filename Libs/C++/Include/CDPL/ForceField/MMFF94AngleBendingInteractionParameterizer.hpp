/* 
 * MMFF94AngleBendingInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94AngleBendingInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTIONPARAMETERIZER_HPP

#include <vector>
#include <cstddef>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief Generates the MMFF94 angle-bending interactions for the atom triplets defined by the bonds of a molecular graph.
         *
         * For every non-filtered atom triplet (\e i-\e j-\e k) consisting of a central atom \e j and two of its
         * neighbors the parameterizer determines the MMFF94 angle-type index (0-8, accounting for ring membership
         * and double-bond character), looks up the matching MMFF94 angle-bending parameters, falls back to the
         * empirical rule when no exact entry is found and emits an MMFF94AngleBendingInteraction record.
         */
        class CDPL_FORCEFIELD_API MMFF94AngleBendingInteractionParameterizer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94AngleBendingInteractionParameterizer instances. */
            typedef std::shared_ptr<MMFF94AngleBendingInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94AngleBendingInteractionParameterizer instance using the default MMFF94 tables.
             */
            MMFF94AngleBendingInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and immediately processes \a molgraph into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the angle-bending interactions.
             * \param ia_list Output list receiving the generated MMFF94AngleBendingInteraction records.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             */
            MMFF94AngleBendingInteractionParameterizer(const Chem::MolecularGraph&        molgraph,
                                                       MMFF94AngleBendingInteractionList& ia_list,
                                                       bool                               strict);

            /**
             * \brief Sets the filter function used to skip atom triplets during parameterization.
             * \param func The new three-atom filter function (when it returns \c false, the triplet is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction3& func);

            /**
             * \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
             * \param func The new numeric-atom-type lookup function.
             */
            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Sets the function used to look up the MMFF94 bond-type index of a bond.
             * \param func The new bond-type-index lookup function.
             */
            void setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func);

            /**
             * \brief Sets the function used to obtain the set of MMFF94-aromatic rings of the input molecular graph.
             * \param func The new aromatic-ring-set function.
             */
            void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

            /**
             * \brief Sets the primary bond-stretching parameter table (used to retrieve reference bond lengths in the empirical-rule fallback).
             * \param table The new bond-stretching parameter table.
             */
            void setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the fallback bond-stretching rule-parameter table (used in the empirical-rule fallback).
             * \param table The new bond-stretching rule-parameter table.
             */
            void setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table);

            /**
             * \brief Sets the primary table providing angle-type-specific angle-bending parameters.
             * \param table The new angle-bending parameter table.
             */
            void setAngleBendingParameterTable(const MMFF94AngleBendingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the table providing per-numeric-atom-type property data (used by the empirical fallback).
             * \param table The new atom-type property table.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Sets the map used to translate primary atom types into their corresponding parameter-atom types.
             * \param map The new primary-to-parameter atom-type map.
             */
            void setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

            /**
             * \brief Generates the MMFF94 angle-bending interactions for \a molgraph and writes them to \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the angle-bending interactions.
             * \param ia_list Output list receiving the generated MMFF94AngleBendingInteraction records.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94AngleBendingInteractionList& ia_list, bool strict);

          private:
            void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom,
                               const Chem::Atom& term_atom2, const Chem::Bond& term_atom1_bnd, const Chem::Bond& term_atom2_bnd,
                               unsigned int& angle_type_idx, bool& linear, double& force_const, double& ref_angle, bool strict) const;

            void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, unsigned int term_atom1_type, const Chem::Atom& ctr_atom,
                               unsigned int ctr_atom_type, const Chem::Atom& term_atom2, unsigned int term_atom2_type, const Chem::Bond& term_atom1_bnd,
                               const Chem::Bond& term_atom2_bnd, unsigned int& angle_type_idx, bool& linear, double& force_const, double& ref_angle, bool strict) const;

            std::size_t getSizeOfContaining3Or4Ring(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1,
                                                    const Chem::Atom& ctr_atom, const Chem::Atom& term_atom2) const;

            /**
             * \brief Returns the angle type index. 
             *
             * The angle-bending parameters employ angle type indices ATIJK ranging between 0 and 8. 
             * Their meanings are as defined below:
             * 
             * ATIJK Structural significance
             * ---------------------------------------------------------------------------
             * 0 The angle i-j-k is a "normal" bond angle
             * 1 Either bond i-j or bond j-k has a bond type of 1
             * 2 Both i-j and j-k have bond types of 1; the sum is 2
             * 3 The angle occurs in a three-membered ring
             * 4 The angle occurs in a four-membered ring 
             * 5 Is in a three-membered ring and the sum of the bond types is 1
             * 6 Is in a three-membered ring and the sum of the bond types is 2
             * 7 Is in a four-membered ring and the sum of the bond types is 1
             * 8 Is in a four-membered ring and the sum of the bond types is 2
             * 
             * \param bond1 The first bond defining the angle.
             * \param bond2 The second bond defining the angle.
             * \param r_size The size of the ring the two bonds are a member of.
             * \return The angle type index.
             */
            unsigned int getAngleTypeIndex(const Chem::Bond& bond1, const Chem::Bond& bond2, std::size_t r_size) const;

            typedef std::vector<const Chem::Atom*> AtomList;
            typedef std::vector<const Chem::Bond*> BondList;

            InteractionFilterFunction3                         filterFunc;
            MMFF94NumericAtomTypeFunction                      atomTypeFunc;
            MMFF94BondTypeIndexFunction                        bondTypeIdxFunc;
            MMFF94AngleBendingParameterTable::SharedPointer    paramTable;
            MMFF94AtomTypePropertyTable::SharedPointer         typePropTable;
            MMFF94PrimaryToParameterAtomTypeMap::SharedPointer paramTypeMap;
            MMFF94BondStretchingInteractionParameterizer       bsParameterizer;
            AtomList                                           nbrAtoms;
            BondList                                           nbrBonds;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTIONPARAMETERIZER_HPP
