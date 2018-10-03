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


using namespace CDPL;


const std::size_t ConfGen::RandomConformerGenerator::DEF_MAX_NUM_TRIALS;
const std::size_t ConfGen::RandomConformerGenerator::DEF_MAX_NUM_NINIMIZATION_STEPS;
const std::size_t ConfGen::RandomConformerGenerator::DEF_TIMEOUT;
const double      ConfGen::RandomConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;


ConfGen::RandomConformerGenerator::RandomConformerGenerator(): 
    molGraph(0), maxNumTrials(DEF_MAX_NUM_TRIALS), maxNumMinSteps(DEF_MAX_NUM_NINIMIZATION_STEPS), 
	minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), timeout(DEF_TIMEOUT), elstaticMMFF94Terms(false), 
	energy(0.0), energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
    raw3DStructureGen.calculateHydrogenPositions(true);
    raw3DStructureGen.regardAtomConfiguration(true);
    raw3DStructureGen.regardBondConfiguration(true);
}

void ConfGen::RandomConformerGenerator::regardAtomConfiguration(bool regard)
{
    raw3DStructureGen.regardAtomConfiguration(regard);
}

bool ConfGen::RandomConformerGenerator::atomConfigurationRegarded() const
{
    return raw3DStructureGen.atomConfigurationRegarded();
}

void ConfGen::RandomConformerGenerator::regardBondConfiguration(bool regard)
{
    raw3DStructureGen.regardBondConfiguration(regard);
}

bool ConfGen::RandomConformerGenerator::bondConfigurationRegarded() const
{
    return raw3DStructureGen.bondConfigurationRegarded();
}

void ConfGen::RandomConformerGenerator::setMaxNumTrials(std::size_t max_num)
{
	maxNumTrials = max_num;
}

std::size_t ConfGen::RandomConformerGenerator::getMaxNumTrials() const
{
	return maxNumTrials;
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
	mmff94Parameterizer.performStrictAtomTyping(strict);
}

bool ConfGen::RandomConformerGenerator::strictMMFF94AtomTypingPerformed() const
{
	return mmff94Parameterizer.strictAtomTypingPerformed();
}

void ConfGen::RandomConformerGenerator::useDynamicMMFF94Parameters()
{
	mmff94Parameterizer.setDynamicParameterDefaults();
}

void ConfGen::RandomConformerGenerator::useStaticMMFF94Parameters()
{
	mmff94Parameterizer.setStaticParameterDefaults();
}

void ConfGen::RandomConformerGenerator::enableElectrostaticMMFF94Terms(bool enable)
{
	elstaticMMFF94Terms = enable;
}
	
bool ConfGen::RandomConformerGenerator::electrostaticMMFF94TermsEnabled() const
{
	return elstaticMMFF94Terms;
}
	
void ConfGen::RandomConformerGenerator::setup(const Chem::MolecularGraph& molgraph) 
{
    molGraph = &molgraph;
    
    mmff94Parameterizer.parameterize(molgraph, mmff94ParamData, 
									 elstaticMMFF94Terms ? ForceField::InteractionType::ALL :
									 ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC);
    mmff94EnergyCalc.setup(mmff94ParamData);
    mmff94GradientCalc.setup(mmff94ParamData, molgraph.getNumAtoms());

    raw3DStructureGen.setup(molgraph, mmff94ParamData);

    gradient.resize(molgraph.getNumAtoms());
}

ConfGen::RandomConformerGenerator::Status ConfGen::RandomConformerGenerator::generate(Math::Vector3DArray& coords)
{
    if (!molGraph)
		return UNINITIALIZED;

	timer.start();

	for (std::size_t i = 0; i < maxNumTrials; i++) {
		if (timeoutExceeded())
			return TIMEOUT_EXCEEDED;

		if (!raw3DStructureGen.generate(coords)) 
			continue;
		
		energyMinimizer.setup(coords, gradient);
		energy = 0.0;

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if (timeoutExceeded())
				return TIMEOUT_EXCEEDED;

			BFGSMinimizer::Status status = energyMinimizer.iterate(energy, coords, gradient);

			if (status != BFGSMinimizer::SUCCESS) 
				return MINIMIZATION_ERROR;
			
			if (minStopGradNorm >= 0.0 && energyMinimizer.getGradientNorm() <= minStopGradNorm)
				break;
		}

		if (raw3DStructureGen.atomConfigurationRegarded() && !raw3DStructureGen.checkAtomConfigurations(coords)) 
			continue;
		
		if (raw3DStructureGen.bondConfigurationRegarded() && !raw3DStructureGen.checkBondConfigurations(coords)) 
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
