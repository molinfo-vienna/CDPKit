/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Random3DCoordinatesGenerator.cpp 
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

#include <boost/bind.hpp>
#include <boost/math/special_functions.hpp>

#include "CDPL/ConfGen/Random3DCoordinatesGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL;


const unsigned int ConfGen::Random3DCoordinatesGenerator::DEF_FORCE_FIELD_TYPE;
const std::size_t  ConfGen::Random3DCoordinatesGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::Random3DCoordinatesGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::Random3DCoordinatesGenerator::DEF_TIMEOUT;
const double       ConfGen::Random3DCoordinatesGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;


ConfGen::Random3DCoordinatesGenerator::Random3DCoordinatesGenerator(): 
    molGraph(0), maxNumStructGenTrials(DEF_MAX_NUM_STRUCTURE_GEN_TRIALS), maxNumMinSteps(DEF_MAX_NUM_MINIMIZATION_STEPS), 
	minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), timeout(DEF_TIMEOUT),  
	energy(0.0), energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
    rawCoordsGenerator.excludeHydrogens(true);
    rawCoordsGenerator.regardAtomConfiguration(true);
    rawCoordsGenerator.regardBondConfiguration(true);
	rawCoordsGenerator.enablePlanarityConstraints(true);

	hCoordsGenerator.undefinedOnly(true);
	hCoordsGenerator.setAtom3DCoordinatesCheckFunction(boost::bind(&Random3DCoordinatesGenerator::has3DCoordinates, this, _1));

	performStrictAtomTyping(false);
	setForceFieldType(DEF_FORCE_FIELD_TYPE);
}

void ConfGen::Random3DCoordinatesGenerator::regardAtomConfiguration(bool regard)
{
    rawCoordsGenerator.regardAtomConfiguration(regard);
}

bool ConfGen::Random3DCoordinatesGenerator::atomConfigurationRegarded() const
{
    return rawCoordsGenerator.atomConfigurationRegarded();
}

void ConfGen::Random3DCoordinatesGenerator::regardBondConfiguration(bool regard)
{
    rawCoordsGenerator.regardBondConfiguration(regard);
}

bool ConfGen::Random3DCoordinatesGenerator::bondConfigurationRegarded() const
{
    return rawCoordsGenerator.bondConfigurationRegarded();
}

void ConfGen::Random3DCoordinatesGenerator::setMaxNumStructureGenerationTrials(std::size_t max_num)
{
	maxNumStructGenTrials = max_num;
}

std::size_t ConfGen::Random3DCoordinatesGenerator::getMaxNumStructureGenerationTrials() const
{
	return maxNumStructGenTrials;
}

void ConfGen::Random3DCoordinatesGenerator::setMaxNumMinimizationSteps(std::size_t max_num)
{
	maxNumMinSteps = max_num;
}

std::size_t ConfGen::Random3DCoordinatesGenerator::getMaxNumMinimizationSteps() const
{
	return maxNumMinSteps;
}

void ConfGen::Random3DCoordinatesGenerator::setMinimizationStopGradientNorm(double grad_norm)
{
	minStopGradNorm = grad_norm;
}

double ConfGen::Random3DCoordinatesGenerator::getMinimizationStopGradientNorm() const
{
	return minStopGradNorm;
}

void ConfGen::Random3DCoordinatesGenerator::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::Random3DCoordinatesGenerator::getTimeout() const
{
	return timeout;
}

void ConfGen::Random3DCoordinatesGenerator::performStrictAtomTyping(bool strict)
{
	mmff94Parameterizer.performStrictAtomTyping(strict);
}

bool ConfGen::Random3DCoordinatesGenerator::strictAtomTypingPerformed() const
{
	return mmff94Parameterizer.strictAtomTypingPerformed();
}

void ConfGen::Random3DCoordinatesGenerator::setForceFieldType(unsigned int type)
{
	if (type == ForceFieldType::MMFF94 || type == ForceFieldType::MMFF94_NO_ESTAT)
		mmff94Parameterizer.setDynamicParameterDefaults();
	else
		mmff94Parameterizer.setStaticParameterDefaults();

	forceFieldType = type;
}
	
unsigned int ConfGen::Random3DCoordinatesGenerator::getForceFieldType() const
{
	return forceFieldType;
}

unsigned int ConfGen::Random3DCoordinatesGenerator::setup(const Chem::MolecularGraph& molgraph) 
{
	molGraph = 0;

    const unsigned int int_types = (forceFieldType == ForceFieldType::MMFF94 || forceFieldType == ForceFieldType::MMFF94S ?
									ForceField::InteractionType::ALL :
									ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC);

	try {
		mmff94Parameterizer.parameterize(molgraph, mmff94Data, int_types);

	} catch (const ForceField::Error& e) {
		return ReturnCode::FORCEFIELD_SETUP_FAILED;
	}

	mmff94EnergyCalc.setEnabledInteractionTypes(int_types);
    mmff94EnergyCalc.setup(mmff94Data);

	mmff94GradientCalc.setEnabledInteractionTypes(int_types);
    mmff94GradientCalc.setup(mmff94Data, molgraph.getNumAtoms());

    rawCoordsGenerator.setup(molgraph, mmff94Data);
	rawCoordsGenerator.setBoxSize(molgraph.getNumBonds() * 2);

    gradient.resize(molgraph.getNumAtoms());

    molGraph = &molgraph;

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::Random3DCoordinatesGenerator::generate(Math::Vector3DArray& coords)
{
    if (!molGraph)
		return ReturnCode::UNINITIALIZED;

	if (coords.getSize() != molGraph->getNumAtoms())
		coords.resize(molGraph->getNumAtoms());

	if (molGraph->getNumAtoms() < 2)
		return ReturnCode::SUCCESS;

	timer.start();

	for (std::size_t i = 0; i < maxNumStructGenTrials; i++) {
		if (timeoutExceeded())
			return ReturnCode::TIMEOUT_EXCEEDED;

		if (!rawCoordsGenerator.generate(coords)) 
			continue;

		hCoordsGenerator.generate(*molGraph, coords, false);

		energyMinimizer.setup(coords.getData(), gradient);
		energy = 0.0;

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if ((j % 50) == 0 && timeoutExceeded())
				return ReturnCode::TIMEOUT_EXCEEDED;

			if (energyMinimizer.iterate(energy, coords.getData(), gradient) != BFGSMinimizer::SUCCESS) {
				if ((boost::math::isnan)(energy))
					return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

				break;
			}

			if ((boost::math::isnan)(energy))
				return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

			if (minStopGradNorm >= 0.0 && energyMinimizer.getGradientNorm() <= minStopGradNorm)
				break;
		}

		if (rawCoordsGenerator.atomConfigurationRegarded() && !rawCoordsGenerator.checkAtomConfigurations(coords)) 
			continue;
		
		if (rawCoordsGenerator.bondConfigurationRegarded() && !rawCoordsGenerator.checkBondConfigurations(coords)) 
			continue;
		
		return ReturnCode::SUCCESS;
	}

    return ReturnCode::MAX_NUM_TRIALS_EXCEEDED;
}

double ConfGen::Random3DCoordinatesGenerator::getEnergy() const
{
    return energy;
}

bool ConfGen::Random3DCoordinatesGenerator::timeoutExceeded() const
{
	if (timeout == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(timeout) * 1000000));
}

bool ConfGen::Random3DCoordinatesGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return !rawCoordsGenerator.getExcludedHydrogenMask().test(molGraph->getAtomIndex(atom));
}
