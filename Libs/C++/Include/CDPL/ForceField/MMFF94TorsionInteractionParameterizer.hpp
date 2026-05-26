/* 
 * MMFF94TorsionInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94TorsionInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94TORSIONINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94TORSIONINTERACTIONPARAMETERIZER_HPP

#include <vector>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"
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
         * \brief Generates the MMFF94 torsion interactions for the atom quadruplets defined by the bonds of a molecular graph.
         *
         * For every non-filtered atom quadruplet (\e i-\e j-\e k-\e l) consisting of a central bond \e j-\e k
         * and one neighbor each on \e j and \e k the parameterizer looks up the matching MMFF94 torsion-type-specific
         * parameters \f$ V_1, V_2, V_3 \f$ from the supplied parameter table, falling back to the primary-to-parameter
         * atom-type map for atoms with no exact parameter entry, and emits an MMFF94TorsionInteraction record.
         */
        class CDPL_FORCEFIELD_API MMFF94TorsionInteractionParameterizer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94TorsionInteractionParameterizer instances. */
            typedef std::shared_ptr<MMFF94TorsionInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94TorsionInteractionParameterizer instance using the default MMFF94 parameter tables.
             */
            MMFF94TorsionInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and immediately processes \a molgraph into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the torsion interactions.
             * \param ia_list Output list receiving the generated MMFF94TorsionInteraction records.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             */
            MMFF94TorsionInteractionParameterizer(const Chem::MolecularGraph&   molgraph,
                                                  MMFF94TorsionInteractionList& ia_list,
                                                  bool                          strict);

            /**
             * \brief Sets the filter function used to skip atom quadruplets during parameterization.
             * \param func The new four-atom filter function (when it returns \c false, the quadruplet is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction4& func);

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
             * \brief Sets the primary table providing torsion-type-specific \f$ V_1/V_2/V_3 \f$ parameters.
             * \param table The new torsion parameter table.
             */
            void setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table);

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
             * \brief Generates the MMFF94 torsion interactions for \a molgraph and writes them to \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the torsion interactions.
             * \param ia_list Output list receiving the generated MMFF94TorsionInteraction records.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94TorsionInteractionList& ia_list, bool strict);

          private:
            typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;
            typedef std::vector<const Chem::Atom*>     AtomList;
            typedef std::vector<const Chem::Bond*>     BondList;

            bool getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1,
                               const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
                               unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                               unsigned int term_atom2_type, unsigned int tor_type_idx, const AtomTypePropEntry& ctr_atom1_prop_entry,
                               const AtomTypePropEntry& ctr_atom2_prop_entry, double& tor_param1, double& tor_param2,
                               double& tor_param3) const;

            unsigned int getTorsionTypeIndex(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1,
                                             const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
                                             unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                                             unsigned int term_atom2_type, unsigned int term_bond1_type_idx, unsigned int ctr_bond_type_idx,
                                             unsigned int term_bond2_type_idx) const;

            bool isInSecondPTERow(unsigned int atomic_no) const;

            InteractionFilterFunction4                         filterFunc;
            MMFF94NumericAtomTypeFunction                      atomTypeFunc;
            MMFF94BondTypeIndexFunction                        bondTypeIdxFunc;
            MMFF94RingSetFunction                              aromRingSetFunc;
            MMFF94TorsionParameterTable::SharedPointer         paramTable;
            MMFF94AtomTypePropertyTable::SharedPointer         typePropTable;
            MMFF94PrimaryToParameterAtomTypeMap::SharedPointer paramTypeMap;
            AtomList                                           nbrAtoms1;
            AtomList                                           nbrAtoms2;
            BondList                                           nbrBonds1;
            BondList                                           nbrBonds2;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94TORSIONINTERACTIONPARAMETERIZER_HPP
