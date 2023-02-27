/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Module.cpp 
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


#include <boost/python.hpp>

#include "ClassExports.hpp"
#include "FunctionExports.hpp"
#include "NamespaceExports.hpp"
#include "ConverterRegistration.hpp"
#include "ExceptionTranslatorRegistration.hpp"


BOOST_PYTHON_MODULE(_forcefield)
{
	using namespace CDPLPythonForceField;

	exportInteractionTypes();
	exportUFFAtomTypes();
	exportMMFF94ParameterSets();

	exportAtomProperties();
	exportBondProperties();
	exportMolecularGraphProperties();

	exportMMFF94AromaticSSSRSubset();
	exportMMFF94AtomTyper();
	exportMMFF94BondTyper();
	exportMMFF94ChargeCalculator();

	exportMMFF94EnergyCalculator();
	exportMMFF94GradientCalculator();

	exportMMFF94BondStretchingInteraction();
	exportMMFF94AngleBendingInteraction();
	exportMMFF94StretchBendInteraction();
	exportMMFF94OutOfPlaneBendingInteraction();
	exportMMFF94TorsionInteraction();
	exportMMFF94VanDerWaalsInteraction();
	exportMMFF94ElectrostaticInteraction();

	exportMMFF94BondStretchingInteractionData();
	exportMMFF94AngleBendingInteractionData();
	exportMMFF94StretchBendInteractionData();
	exportMMFF94OutOfPlaneBendingInteractionData();
	exportMMFF94TorsionInteractionData();
	exportMMFF94VanDerWaalsInteractionData();
	exportMMFF94ElectrostaticInteractionData();
	exportMMFF94InteractionData();

	exportMMFF94BondStretchingInteractionParameterizer();
	exportMMFF94AngleBendingInteractionParameterizer();
	exportMMFF94StretchBendInteractionParameterizer();
	exportMMFF94OutOfPlaneBendingInteractionParameterizer();
	exportMMFF94TorsionInteractionParameterizer();
	exportMMFF94VanDerWaalsInteractionParameterizer();
	exportMMFF94ElectrostaticInteractionParameterizer();
	exportMMFF94InteractionParameterizer();

	exportMMFF94SymbolicAtomTypePatternTable();
	exportMMFF94HeavyToHydrogenAtomTypeMap();
	exportMMFF94SymbolicToNumericAtomTypeMap();
	exportMMFF94AromaticAtomTypeDefinitionTable();
	exportMMFF94AtomTypePropertyTable();
	exportMMFF94FormalAtomChargeDefinitionTable();
	exportMMFF94BondChargeIncrementTable();
	exportMMFF94PartialBondChargeIncrementTable();
	exportMMFF94PrimaryToParameterAtomTypeMap();
	exportMMFF94AngleBendingParameterTable();
	exportMMFF94BondStretchingParameterTable();
	exportMMFF94BondStretchingRuleParameterTable();
	exportMMFF94StretchBendParameterTable();
	exportMMFF94DefaultStretchBendParameterTable();
	exportMMFF94OutOfPlaneBendingParameterTable();
	exportMMFF94TorsionParameterTable();
	exportMMFF94VanDerWaalsParameterTable();

	exportUtilityFunctions();
	exportMMFF94EnergyFunctions();
	exportMMFF94GradientFunctions();
	exportAtomFunctions();
	exportBondFunctions();
	exportMolecularGraphFunctions();

	exportBoostFunctionWrappers();

	registerToPythonConverters();
	registerFromPythonConverters();
	registerExceptionTranslators();
}
