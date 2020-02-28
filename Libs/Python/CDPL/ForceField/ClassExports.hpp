/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ClassExports.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_FORCEFIELD_CLASSEXPORTS_HPP
#define CDPL_PYTHON_FORCEFIELD_CLASSEXPORTS_HPP


namespace CDPLPythonForceField
{

	void exportMMFF94AromaticSSSRSubset();
	void exportMMFF94AtomTyper();
	void exportMMFF94BondTyper();
	void exportMMFF94ChargeCalculator();

	void exportMMFF94EnergyCalculator();
	void exportMMFF94GradientCalculator();

	void exportMMFF94BondStretchingInteraction();
	void exportMMFF94AngleBendingInteraction();
	void exportMMFF94StretchBendInteraction();
	void exportMMFF94OutOfPlaneBendingInteraction();
	void exportMMFF94TorsionInteraction();
	void exportMMFF94VanDerWaalsInteraction();
	void exportMMFF94ElectrostaticInteraction();

	void exportMMFF94BondStretchingInteractionData();
	void exportMMFF94AngleBendingInteractionData();
	void exportMMFF94StretchBendInteractionData();
	void exportMMFF94OutOfPlaneBendingInteractionData();
	void exportMMFF94TorsionInteractionData();
	void exportMMFF94VanDerWaalsInteractionData();
	void exportMMFF94ElectrostaticInteractionData();
	void exportMMFF94InteractionData();

	void exportMMFF94BondStretchingInteractionParameterizer();
	void exportMMFF94AngleBendingInteractionParameterizer();
	void exportMMFF94StretchBendInteractionParameterizer();
	void exportMMFF94OutOfPlaneBendingInteractionParameterizer();
	void exportMMFF94TorsionInteractionParameterizer();
	void exportMMFF94VanDerWaalsInteractionParameterizer();
	void exportMMFF94ElectrostaticInteractionParameterizer();
	void exportMMFF94InteractionParameterizer();

	void exportMMFF94SymbolicAtomTypePatternTable();
	void exportMMFF94HeavyToHydrogenAtomTypeMap();
	void exportMMFF94SymbolicToNumericAtomTypeMap();
	void exportMMFF94AromaticAtomTypeDefinitionTable();
	void exportMMFF94AtomTypePropertyTable();
	void exportMMFF94FormalAtomChargeDefinitionTable();
	void exportMMFF94BondChargeIncrementTable();
	void exportMMFF94PartialBondChargeIncrementTable();
	void exportMMFF94PrimaryToParameterAtomTypeMap();
	void exportMMFF94AngleBendingParameterTable();
	void exportMMFF94BondStretchingParameterTable();
	void exportMMFF94BondStretchingRuleParameterTable();
	void exportMMFF94StretchBendParameterTable();
	void exportMMFF94DefaultStretchBendParameterTable();
	void exportMMFF94OutOfPlaneBendingParameterTable();
	void exportMMFF94TorsionParameterTable();
	void exportMMFF94VanDerWaalsParameterTable();

	void exportBoostFunctionWrappers();
}

#endif // CDPL_PYTHON_FORCEFIELD_CLASSEXPORTS_HPP
