/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomConformerGenerator.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

 
#include "StaticInit.hpp"

#include "CDPL/ConfGen/RandomConformerGenerator.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL;


const unsigned int ConfGen::RandomConformerGenerator::DEF_FORCE_FIELD_TYPE;
const std::size_t  ConfGen::RandomConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::RandomConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::RandomConformerGenerator::DEF_TIMEOUT;
const double       ConfGen::RandomConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;


ConfGen::RandomConformerGenerator::RandomConformerGenerator(): 
    molGraph(0), maxNumStructGenTrials(DEF_MAX_NUM_STRUCTURE_GEN_TRIALS), maxNumMinSteps(DEF_MAX_NUM_MINIMIZATION_STEPS), 
	minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), timeout(DEF_TIMEOUT), forceFieldType(DEF_FORCE_FIELD_TYPE), 
	strictAtomTyping(true), energy(0.0), energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
    rawCoordsGenerator.excludeHydrogens(true);
    rawCoordsGenerator.regardAtomConfiguration(true);
    rawCoordsGenerator.regardBondConfiguration(true);
	rawCoordsGenerator.enablePlanarityConstraints(false);

	hCoordsGenerator.undefinedOnly(false);
}

void ConfGen::RandomConformerGenerator::regardAtomConfiguration(bool regard)
{
    rawCoordsGenerator.regardAtomConfiguration(regard);
}

bool ConfGen::RandomConformerGenerator::atomConfigurationRegarded() const
{
    return rawCoordsGenerator.atomConfigurationRegarded();
}

void ConfGen::RandomConformerGenerator::regardBondConfiguration(bool regard)
{
    rawCoordsGenerator.regardBondConfiguration(regard);
}

bool ConfGen::RandomConformerGenerator::bondConfigurationRegarded() const
{
    return rawCoordsGenerator.bondConfigurationRegarded();
}

void ConfGen::RandomConformerGenerator::setMaxNumStructureGenerationTrials(std::size_t max_num)
{
	maxNumStructGenTrials = max_num;
}

std::size_t ConfGen::RandomConformerGenerator::getMaxNumStructureGenerationTrials() const
{
	return maxNumStructGenTrials;
}

void ConfGen::RandomConformerGenerator::setMaxNumMinimizationSteps(std::size_t max_num)
{
	maxNumMinSteps = max_num;
}

std::size_t ConfGen::RandomConformerGenerator::getMaxNumMinimizationSteps() const
{
	return maxNumMinSteps;
}

void ConfGen::RandomConformerGenerator::setMinimizationStopGradientNorm(double grad_norm)
{
	minStopGradNorm = grad_norm;
}

double ConfGen::RandomConformerGenerator::getMinimizationStopGradientNorm() const
{
	return minStopGradNorm;
}

void ConfGen::RandomConformerGenerator::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::RandomConformerGenerator::getTimeout() const
{
	return timeout;
}

void ConfGen::RandomConformerGenerator::performStrictMMFF94AtomTyping(bool strict)
{
	strictAtomTyping = strict;
}

bool ConfGen::RandomConformerGenerator::strictMMFF94AtomTypingPerformed() const
{
	return strictAtomTyping;
}

void ConfGen::RandomConformerGenerator::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	
unsigned int ConfGen::RandomConformerGenerator::getForceFieldType() const
{
	return forceFieldType;
}

void ConfGen::RandomConformerGenerator::setup(const Chem::MolecularGraph& molgraph) 
{
    molGraph = &molgraph;

	if (forceFieldType == ForceFieldType::MMFF94 || forceFieldType == ForceFieldType::MMFF94_NO_ESTAT)
		mmff94Parameterizer.setDynamicParameterDefaults();
	else
		mmff94Parameterizer.setStaticParameterDefaults();

	mmff94Parameterizer.performStrictAtomTyping(strictAtomTyping);
	mmff94Parameterizer.parameterize(molgraph, mmff94ParamData, 
									 forceFieldType == ForceFieldType::MMFF94 || forceFieldType == ForceFieldType::MMFF94S ?
									 ForceField::InteractionType::ALL :
									 ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC);

    unsigned int int_types = (forceFieldType == ForceFieldType::MMFF94 || forceFieldType == ForceFieldType::MMFF94S ?
							  ForceField::InteractionType::ALL :
							  ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC);

	mmff94EnergyCalc.setEnabledInteractionTypes(int_types);
    mmff94EnergyCalc.setup(mmff94ParamData);

	mmff94GradientCalc.setEnabledInteractionTypes(int_types);
    mmff94GradientCalc.setup(mmff94ParamData, molgraph.getNumAtoms());

    rawCoordsGenerator.setup(molgraph, mmff94ParamData);

    gradient.resize(molgraph.getNumAtoms());
}

ConfGen::RandomConformerGenerator::Status ConfGen::RandomConformerGenerator::generate(Math::Vector3DArray& coords)
{
    if (!molGraph)
		return UNINITIALIZED;

	timer.start();

	for (std::size_t i = 0; i < maxNumStructGenTrials; i++) {
		if (timeoutExceeded())
			return TIMEOUT_EXCEEDED;

		if (!rawCoordsGenerator.generate(coords)) 
			continue;

		hCoordsGenerator.generate(*molGraph, coords, false);

		energyMinimizer.setup(coords, gradient);
		energy = 0.0;

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if ((j % 10) == 0 && timeoutExceeded())
				return TIMEOUT_EXCEEDED;

			if (energyMinimizer.iterate(energy, coords, gradient) != BFGSMinimizer::SUCCESS) 
				break;
			
			if (minStopGradNorm >= 0.0 && energyMinimizer.getGradientNorm() <= minStopGradNorm)
				break;
		}

		if (rawCoordsGenerator.atomConfigurationRegarded() && !rawCoordsGenerator.checkAtomConfigurations(coords)) 
			continue;
		
		if (rawCoordsGenerator.bondConfigurationRegarded() && !rawCoordsGenerator.checkBondConfigurations(coords)) 
			continue;
		
		return SUCCESS;
	}

    return MAX_NUM_TRIALS_EXCEEDED;
}

double ConfGen::RandomConformerGenerator::getEnergy() const
{
    return energy;
}

bool ConfGen::RandomConformerGenerator::timeoutExceeded() const
{
	if (timeout == 0)
		return false;

	boost::timer::cpu_times times = timer.elapsed();

	if ((times.system + times.user) > (boost::timer::nanosecond_type(timeout) * 1000000))
		return true;

	return false;
}
