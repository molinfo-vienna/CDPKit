/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomStructureGenerator.cpp 
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

#include "CDPL/ConfGen/RandomStructureGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL;


ConfGen::RandomStructureGenerator::RandomStructureGenerator(): 
    molGraph(0), energy(0.0), energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
    dgStructGen.getSettings().excludeHydrogens(true);
 	dgStructGen.getSettings().enablePlanarityConstraints(true);

	hCoordsGen.undefinedOnly(true);
	hCoordsGen.setAtom3DCoordinatesCheckFunction(boost::bind(&RandomStructureGenerator::has3DCoordinates, this, _1));
}

ConfGen::RandomStructureGeneratorSettings& ConfGen::RandomStructureGenerator::getSettings()
{
	return settings;
}

const ConfGen::RandomStructureGeneratorSettings& ConfGen::RandomStructureGenerator::getSettings() const
{
	return settings;
}

unsigned int ConfGen::RandomStructureGenerator::setup(const Chem::MolecularGraph& molgraph) 
{
	molGraph = 0;

	mmff94Parameterizer.strictParameterization(settings.strictForceFieldParameterization());

	try {
		parameterizeMMFF94Interactions(molgraph, mmff94Parameterizer, mmff94Data, settings.getForceFieldType());

	} catch (const ForceField::Error& e) {
		return ReturnCode::FORCEFIELD_SETUP_FAILED;
	}

    mmff94EnergyCalc.setup(mmff94Data);
    mmff94GradientCalc.setup(mmff94Data, molgraph.getNumAtoms());

	dgStructGen.getSettings().regardAtomConfiguration(settings.regardAtomConfiguration());
    dgStructGen.getSettings().regardBondConfiguration(settings.regardBondConfiguration());
	dgStructGen.getSettings().setBoxSize(molgraph.getNumBonds() * 2);

    dgStructGen.setup(molgraph, mmff94Data);

    gradient.resize(molgraph.getNumAtoms());

    molGraph = &molgraph;

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::RandomStructureGenerator::generate(Math::Vector3DArray& coords)
{
    if (!molGraph)
		return ReturnCode::UNINITIALIZED;

	if (coords.getSize() != molGraph->getNumAtoms())
		coords.resize(molGraph->getNumAtoms());

	if (molGraph->getNumAtoms() < 2)
		return ReturnCode::SUCCESS;

	timer.start();

	double stop_grad = settings.getRefinementStopGradient();

	for (std::size_t i = 0, max_trials = settings.getMaxNumStructureGenerationTrials(); i < max_trials; i++) {
		if (timeoutExceeded())
			return ReturnCode::TIMEOUT;

		if (!dgStructGen.generate(coords)) 
			continue;

		hCoordsGen.generate(*molGraph, coords, false);

		energyMinimizer.setup(coords.getData(), gradient);
		energy = 0.0;

		for (std::size_t j = 0, max_iters = settings.getMaxNumRefinementIterations(); max_iters == 0 || j < max_iters; j++) {
			if ((j % 50) == 0 && timeoutExceeded())
				return ReturnCode::TIMEOUT;

			if (energyMinimizer.iterate(energy, coords.getData(), gradient) != BFGSMinimizer::SUCCESS) {
				if ((boost::math::isnan)(energy))
					return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

				break;
			}

			if ((boost::math::isnan)(energy))
				return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

			if (stop_grad >= 0.0 && energyMinimizer.getGradientNorm() <= stop_grad)
				break;
		}

		if (settings.regardAtomConfiguration() && !dgStructGen.checkAtomConfigurations(coords)) 
			continue;
		
		if (settings.regardBondConfiguration() && !dgStructGen.checkBondConfigurations(coords)) 
			continue;
		
		return ReturnCode::SUCCESS;
	}

    return ReturnCode::ERROR;
}

double ConfGen::RandomStructureGenerator::getEnergy() const
{
    return energy;
}

bool ConfGen::RandomStructureGenerator::timeoutExceeded() const
{
	if (settings.getTimeout() == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(settings.getTimeout()) * 1000000));
}

bool ConfGen::RandomStructureGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return !dgStructGen.getExcludedHydrogenMask().test(molGraph->getAtomIndex(atom));
}
