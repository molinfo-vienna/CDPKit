/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ForceField.hpp 
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
 * \brief A convenience header including everything that is defined in namespace CDPL::ForceField.
 */

#ifndef CDPL_FORCEFIELD_HPP
#define CDPL_FORCEFIELD_HPP

#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/ForceField/AtomProperty.hpp"
#include "CDPL/ForceField/BondProperty.hpp"
#include "CDPL/ForceField/MolecularGraphProperty.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/TopologicalAtomDistanceFunction.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/GradientVectorTraits.hpp"

#include "CDPL/ForceField/UFFAtomType.hpp"
#include "CDPL/ForceField/UFFAtomTypePropertyTable.hpp"

#include "CDPL/ForceField/MMFF94ParameterSet.hpp"

#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/MMFF94AromaticSSSRSubset.hpp"
#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/ForceField/MMFF94BondTyper.hpp"
#include "CDPL/ForceField/MMFF94ChargeCalculator.hpp"

#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/MMFF94GradientFunctions.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"

#include "CDPL/ForceField/MMFF94BondStretchingInteraction.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteraction.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteraction.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteraction.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteraction.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteraction.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteraction.hpp"

#include "CDPL/ForceField/MMFF94BondStretchingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionData.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionData.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionData.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionData.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"

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

#endif // CDPL_FORCEFIELD_HPP
