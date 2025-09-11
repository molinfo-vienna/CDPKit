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

        class CDPL_FORCEFIELD_API MMFF94InteractionParameterizer
        {

          public:
            typedef std::shared_ptr<MMFF94InteractionParameterizer> SharedPointer;

            MMFF94InteractionParameterizer(unsigned int param_set = MMFF94ParameterSet::STATIC);

            MMFF94InteractionParameterizer(const MMFF94InteractionParameterizer& parameterizer);

            void setBondStretchingFilterFunction(const InteractionFilterFunction2& func);

            void setAngleBendingFilterFunction(const InteractionFilterFunction3& func);

            void setStretchBendFilterFunction(const InteractionFilterFunction3& func);

            void setOutOfPlaneBendingFilterFunction(const InteractionFilterFunction4& func);

            void setTorsionFilterFunction(const InteractionFilterFunction4& func);

            void setElectrostaticFilterFunction(const InteractionFilterFunction2& func);

            void setVanDerWaalsFilterFunction(const InteractionFilterFunction2& func);

            void clearFilterFunctions();

            void setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable::SharedPointer& table);

            void setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer& map);

            void setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap::SharedPointer& map);

            void setAromaticAtomTypeDefinitionTable(const MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& table);

            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            void setFormalAtomChargeDefinitionTable(const MMFF94FormalAtomChargeDefinitionTable::SharedPointer& table);

            void setBondChargeIncrementTable(const MMFF94BondChargeIncrementTable::SharedPointer& table);

            void setPartialBondChargeIncrementTable(const MMFF94PartialBondChargeIncrementTable::SharedPointer& table);

            void setPrimaryToParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

            void setAngleBendingParameterTable(const MMFF94AngleBendingParameterTable::SharedPointer& table);

            void setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table);

            void setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table);

            void setStretchBendParameterTable(const MMFF94StretchBendParameterTable::SharedPointer& table);

            void setDefaultStretchBendParameterTable(const MMFF94DefaultStretchBendParameterTable::SharedPointer& table);

            void setOutOfPlaneBendingParameterTable(const MMFF94OutOfPlaneBendingParameterTable::SharedPointer& table);

            void setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table);

            void setVanDerWaalsParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table);

            void setDielectricConstant(double de_const);

            void setDistanceExponent(double dist_expo);

            void setParameterSet(unsigned int param_set);

            MMFF94InteractionParameterizer& operator=(const MMFF94InteractionParameterizer& parameterizer);

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
