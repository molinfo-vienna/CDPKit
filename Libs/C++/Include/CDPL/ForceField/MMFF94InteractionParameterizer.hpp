/* 
 * MMFF94InteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94InteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94INTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94INTERACTIONPARAMETERIZER_HPP

#include <string>
#include <cstddef>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94ParameterSet.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94SymbolicAtomTypePatternTable.hpp"
#include "CDPL/ForceField/MMFF94HeavyToHydrogenAtomTypeMap.hpp"
#include "CDPL/ForceField/MMFF94SymbolicToNumericAtomTypeMap.hpp"
#include "CDPL/ForceField/MMFF94AromaticAtomTypeDefinitionTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94FormalAtomChargeDefinitionTable.hpp"
#include "CDPL/ForceField/MMFF94BondChargeIncrementTable.hpp"
#include "CDPL/ForceField/MMFF94PartialBondChargeIncrementTable.hpp"
#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"
#include "CDPL/ForceField/MMFF94StretchBendParameterTable.hpp"
#include "CDPL/ForceField/MMFF94DefaultStretchBendParameterTable.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AromaticSSSRSubset.hpp"
#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/ForceField/MMFF94BondTyper.hpp"
#include "CDPL/ForceField/MMFF94ChargeCalculator.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class Bond;
    } // namespace Chem

    namespace ForceField
    {

        class MMFF94InteractionData;

        /**
         * \brief One-stop MMFF94 parameterizer that combines atom typing, bond typing, partial-charge
         *        assignment and per-interaction-type parameter look-up into a single \c parameterize() call.
         *
         * The constructor installs default parameter tables and atom-/bond-typing helpers for the
         * selected ForceField::MMFF94ParameterSet variant (\c STATIC, \c DYNAMIC, etc.); every table,
         * map and filter function can be overridden via the corresponding setter. Calling parameterize()
         * runs atom typing, bond typing, formal/partial-charge assignment, aromaticity perception and
         * topological-distance calculation, then dispatches to the seven per-interaction
         * MMFF94*InteractionParameterizer members and stores the resulting interaction lists in the
         * supplied ForceField::MMFF94InteractionData object.
         */
        class CDPL_FORCEFIELD_API MMFF94InteractionParameterizer
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94InteractionParameterizer instances.
             */
            typedef std::shared_ptr<MMFF94InteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs the parameterizer with the default tables for the chosen MMFF94 parameter set.
             * \param param_set The parameter-set variant (see namespace ForceField::MMFF94ParameterSet).
             */
            MMFF94InteractionParameterizer(unsigned int param_set = MMFF94ParameterSet::STATIC);

            /**
             * \brief Constructs a copy of the parameterizer \a parameterizer.
             * \param parameterizer The parameterizer to copy.
             */
            MMFF94InteractionParameterizer(const MMFF94InteractionParameterizer& parameterizer);

            /**
             * \brief Installs a filter that decides whether a candidate bond-stretching interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setBondStretchingFilterFunction(const InteractionFilterFunction2& func);

            /**
             * \brief Installs a filter that decides whether a candidate angle-bending interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setAngleBendingFilterFunction(const InteractionFilterFunction3& func);

            /**
             * \brief Installs a filter that decides whether a candidate stretch-bend interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setStretchBendFilterFunction(const InteractionFilterFunction3& func);

            /**
             * \brief Installs a filter that decides whether a candidate out-of-plane bending interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setOutOfPlaneBendingFilterFunction(const InteractionFilterFunction4& func);

            /**
             * \brief Installs a filter that decides whether a candidate torsion interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setTorsionFilterFunction(const InteractionFilterFunction4& func);

            /**
             * \brief Installs a filter that decides whether a candidate electrostatic interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setElectrostaticFilterFunction(const InteractionFilterFunction2& func);

            /**
             * \brief Installs a filter that decides whether a candidate van-der-Waals interaction is kept.
             * \param func The filter functor (returns \c true to keep the interaction).
             */
            void setVanDerWaalsFilterFunction(const InteractionFilterFunction2& func);

            /**
             * \brief Removes every previously installed interaction-filter function.
             */
            void clearFilterFunctions();

            /**
             * \brief Sets the symbolic-atom-type pattern table to use during atom typing.
             * \param table The new symbolic-atom-type pattern table.
             */
            void setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable::SharedPointer& table);

            /**
             * \brief Sets the heavy-to-hydrogen atom-type map used to derive hydrogen atom types from their non-hydrogen neighbors.
             * \param map The new heavy-to-hydrogen atom-type map.
             */
            void setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer& map);

            /**
             * \brief Sets the symbolic-to-numeric atom-type map used to convert symbolic types to numeric ones.
             * \param map The new symbolic-to-numeric atom-type map.
             */
            void setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap::SharedPointer& map);

            /**
             * \brief Sets the aromatic-atom-type definition table used to override types of aromatic atoms.
             * \param table The new aromatic-atom-type definition table.
             */
            void setAromaticAtomTypeDefinitionTable(const MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& table);

            /**
             * \brief Sets the atom-type property table used to resolve per-numeric-type properties.
             * \param table The new atom-type property table.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Sets the formal-atomic-charge definition table used during charge assignment.
             * \param table The new formal-atomic-charge definition table.
             */
            void setFormalAtomChargeDefinitionTable(const MMFF94FormalAtomChargeDefinitionTable::SharedPointer& table);

            /**
             * \brief Sets the bond charge-increment table used during partial-charge calculation.
             * \param table The new bond-charge-increment table.
             */
            void setBondChargeIncrementTable(const MMFF94BondChargeIncrementTable::SharedPointer& table);

            /**
             * \brief Sets the partial bond charge-increment table used during partial-charge calculation.
             * \param table The new partial-bond-charge-increment table.
             */
            void setPartialBondChargeIncrementTable(const MMFF94PartialBondChargeIncrementTable::SharedPointer& table);

            /**
             * \brief Sets the primary-to-parameter atom-type map used by the parameter look-ups.
             * \param map The new primary-to-parameter atom-type map.
             */
            void setPrimaryToParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

            /**
             * \brief Sets the angle-bending parameter table to use.
             * \param table The new angle-bending parameter table.
             */
            void setAngleBendingParameterTable(const MMFF94AngleBendingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the bond-stretching parameter table to use.
             * \param table The new bond-stretching parameter table.
             */
            void setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the bond-stretching rule parameter table used as a fallback when no explicit
             *        bond-stretching entry is available.
             * \param table The new bond-stretching rule parameter table.
             */
            void setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table);

            /**
             * \brief Sets the stretch-bend parameter table to use.
             * \param table The new stretch-bend parameter table.
             */
            void setStretchBendParameterTable(const MMFF94StretchBendParameterTable::SharedPointer& table);

            /**
             * \brief Sets the default stretch-bend parameter table used as a periodic-row fallback.
             * \param table The new default stretch-bend parameter table.
             */
            void setDefaultStretchBendParameterTable(const MMFF94DefaultStretchBendParameterTable::SharedPointer& table);

            /**
             * \brief Sets the out-of-plane bending parameter table to use.
             * \param table The new out-of-plane bending parameter table.
             */
            void setOutOfPlaneBendingParameterTable(const MMFF94OutOfPlaneBendingParameterTable::SharedPointer& table);

            /**
             * \brief Sets the torsion parameter table to use.
             * \param table The new torsion parameter table.
             */
            void setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table);

            /**
             * \brief Sets the van-der-Waals parameter table to use.
             * \param table The new van-der-Waals parameter table.
             */
            void setVanDerWaalsParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table);

            /**
             * \brief Sets the dielectric constant used by the electrostatic interaction parameterizer.
             * \param de_const The new dielectric constant.
             */
            void setDielectricConstant(double de_const);

            /**
             * \brief Sets the distance exponent used by the electrostatic interaction parameterizer.
             * \param dist_expo The new distance exponent.
             */
            void setDistanceExponent(double dist_expo);

            /**
             * \brief Switches the active MMFF94 parameter-set variant and reinstalls the matching default tables.
             * \param param_set The new parameter-set variant (see namespace ForceField::MMFF94ParameterSet).
             */
            void setParameterSet(unsigned int param_set);

            /**
             * \brief Copies the state of \a parameterizer.
             * \param parameterizer The parameterizer to copy.
             * \return A reference to itself.
             */
            MMFF94InteractionParameterizer& operator=(const MMFF94InteractionParameterizer& parameterizer);

            /**
             * \brief Parameterizes the MMFF94 force field interactions for \a molgraph and stores them in \a ia_data.
             * \param molgraph The molecular graph to parameterize.
             * \param ia_data The output container receiving the perceived interactions.
             * \param ia_types A bitmask of ForceField::InteractionType flags selecting which interaction types are parameterized.
             * \param strict If \c true, the parameterization fails when any required parameter is missing; otherwise
             *               fallback strategies (rule-based parameters, default values) are used.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94InteractionData& ia_data,
                              unsigned int ia_types = InteractionType::ALL, bool strict = true);

          private:
            void setPropertyFunctions();

            unsigned int getBondTypeIndex(const Chem::Bond& bond) const;

            unsigned int getNumericAtomType(const Chem::Atom& atom) const;

            const std::string& getSymbolicAtomType(const Chem::Atom& atom) const;

            double getAtomCharge(const Chem::Atom& atom) const;

            const Chem::FragmentList::SharedPointer& getAromaticRings(const Chem::MolecularGraph& molgraph) const;

            std::size_t getTopologicalDistance(const Chem::Atom& atom1, const Chem::Atom& atom2,
                                               const Chem::MolecularGraph& molgraph) const;

            void setup(const Chem::MolecularGraph& molgraph, unsigned int ia_types, bool strict);

            void setupAromaticRingSet();
            void setupAtomTypes(bool strict);
            void setupBondTypeIndices(bool strict);
            void setupAtomCharges(bool strict);
            void setupTopDistances();

            MMFF94BondStretchingInteractionParameterizer    bondStretchingParameterizer;
            MMFF94AngleBendingInteractionParameterizer      angleBendingParameterizer;
            MMFF94StretchBendInteractionParameterizer       stretchBendParameterizer;
            MMFF94OutOfPlaneBendingInteractionParameterizer outOfPlaneParameterizer;
            MMFF94TorsionInteractionParameterizer           torsionParameterizer;
            MMFF94VanDerWaalsInteractionParameterizer       vanDerWaalsParameterizer;
            MMFF94ElectrostaticInteractionParameterizer     electrostaticParameterizer;
            MMFF94AtomTyper                                 atomTyper;
            MMFF94BondTyper                                 bondTyper;
            MMFF94ChargeCalculator                          chargeCalculator;
            MMFF94AromaticSSSRSubset::SharedPointer         aromRings;
            Chem::FragmentList::SharedPointer               usedAromRings;
            Math::ULMatrix::SharedPointer                   topDistMatrix;
            Math::ULMatrix::SharedPointer                   usedTopDistMatrix;
            Util::UIArray                                   numAtomTypes;
            Util::SArray                                    symAtomTypes;
            Util::UIArray                                   bondTypeIndices;
            Util::DArray                                    atomCharges;
            const Chem::MolecularGraph*                     molGraph;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94INTERACTIONPARAMETERIZER_HPP
