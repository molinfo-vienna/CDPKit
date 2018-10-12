/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGenerator.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_TIMEOUT;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_RING_CONF_RETRIAL_FACTOR;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;
const double       ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW                   = 5.0;
const double       ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD                        = 0.25;


ConfGen::FragmentConformerGenerator::FragmentConformerGenerator(): 
    maxNumStructGenTrials(DEF_MAX_NUM_STRUCTURE_GEN_TRIALS), maxNumMinSteps(DEF_MAX_NUM_MINIMIZATION_STEPS), 
	minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), timeout(DEF_TIMEOUT), reuseExistingCoords(false),
	eWindow(DEF_ENERGY_WINDOW), ringConfRetrialFact(DEF_RING_CONF_RETRIAL_FACTOR), minRMSD(DEF_MIN_RMSD),
	energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
    rawCoordsGenerator.calculateHydrogenPositions(true);
    rawCoordsGenerator.regardAtomConfiguration(true);
    rawCoordsGenerator.regardBondConfiguration(true);
}

void ConfGen::FragmentConformerGenerator::setMaxNumStructureGenerationTrials(std::size_t max_num)
{
	maxNumStructGenTrials = max_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMaxNumStructureGenerationTrials() const
{
	return maxNumStructGenTrials;
}

void ConfGen::FragmentConformerGenerator::setMaxNumMinimizationSteps(std::size_t max_num)
{
	maxNumMinSteps = max_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMaxNumMinimizationSteps() const
{
	return maxNumMinSteps;
}

void ConfGen::FragmentConformerGenerator::setMinimizationStopGradientNorm(double grad_norm)
{
	minStopGradNorm = grad_norm;
}

double ConfGen::FragmentConformerGenerator::getMinimizationStopGradientNorm() const
{
	return minStopGradNorm;
}

void ConfGen::FragmentConformerGenerator::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::FragmentConformerGenerator::getTimeout() const
{
	return timeout;
}
	
void ConfGen::FragmentConformerGenerator::reuseExistingCoordinates(bool reuse)
{
	reuseExistingCoords = reuse;
}

bool ConfGen::FragmentConformerGenerator::existingCoordinatesReused() const
{
	return reuseExistingCoords;
}

void ConfGen::FragmentConformerGenerator::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::FragmentConformerGenerator::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::FragmentConformerGenerator::setRingConformerRetrialFactor(std::size_t factor)
{
	ringConfRetrialFact = factor;
}

std::size_t ConfGen::FragmentConformerGenerator::getRingConformerRetrialFactor() const
{
	return ringConfRetrialFact;
}

void ConfGen::FragmentConformerGenerator::setMinRMSD(double min_rmsd)
{
	minRMSD = min_rmsd;
}

double ConfGen::FragmentConformerGenerator::getMinRMSD() const
{
	return minRMSD;
}

void ConfGen::FragmentConformerGenerator::generate(const Chem::MolecularGraph& molgraph, 
												   const ForceField::MMFF94InteractionData& ia_data, unsigned int frag_type) 
{
	init();

	switch (frag_type) {

		case FragmentType::FLEXIBLE_RING_SYSTEM:
			generateMultipleConformers(molgraph, ia_data);
			return;

		default:
			generateSingleConformer(molgraph, ia_data);
	}
}

std::size_t ConfGen::FragmentConformerGenerator::getNumConformations() const
{
	return conformers.size();
}

const Math::Vector3DArray& ConfGen::FragmentConformerGenerator::getConformation(std::size_t idx) const
{
	if (idx >= conformers.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return *conformers[idx].second;
}

Math::Vector3DArray& ConfGen::FragmentConformerGenerator::getConformation(std::size_t idx)
{
	if (idx >= conformers.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return *conformers[idx].second;
}

double ConfGen::FragmentConformerGenerator::getConformerEnergy(std::size_t idx) const
{
	if (idx >= conformers.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return conformers[idx].first;
}

bool ConfGen::FragmentConformerGenerator::timeoutExceeded() const
{
	if (timeout == 0)
		return false;

	boost::timer::cpu_times times = timer.elapsed();

	if ((times.system + times.user) > (boost::timer::nanosecond_type(timeout) * 1000000))
		return true;

	return false;
}

void ConfGen::FragmentConformerGenerator::generateSingleConformer(const Chem::MolecularGraph& molgraph, 
																  const ForceField::MMFF94InteractionData& ia_data)
{
	std::size_t num_atoms = molgraph.getNumAtoms();
	Math::Vector3DArray::SharedPointer coords_ptr = allocCoordinatesArray(num_atoms);

/*

    mmff94EnergyCalc.setup(ia_data);
    mmff94GradientCalc.setup(ia_data, num_atoms);

    rawCoordsGenerator.setup(molgraph, ia_data);

    gradient.resize(molgraph.getNumAtoms());

	double energy = 0.0;
	std::size_t i = 0;

	for (; i < maxNumStructGenTrials; i++) {
		if (timeoutExceeded())
			return;

		if (!rawCoordsGenerator.generate(coords)) 
			continue;
		
		energyMinimizer.setup(coords, gradient);

		energy = 0.0;
		bool min_error = false;

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if ((j % 10) == 0 && timeoutExceeded())
				return;

			BFGSMinimizer::Status status = energyMinimizer.iterate(energy, coords, gradient);

			if (status != BFGSMinimizer::SUCCESS) {
				min_error = true;
				break;
			}

			if (minStopGradNorm >= 0.0 && energyMinimizer.getGradientNorm() <= minStopGradNorm)
				break;
		}

		if (min_error)
			continue;

		if (!rawCoordsGenerator.checkAtomConfigurations(coords)) 
			continue;
		
		if (!rawCoordsGenerator.checkBondConfigurations(coords)) 
			continue;
		
		break;
	}

	if (i == maxNumStructGenTrials)
		return;
*/
}

void ConfGen::FragmentConformerGenerator::generateMultipleConformers(const Chem::MolecularGraph& molgraph, 
																	 const ForceField::MMFF94InteractionData& ia_data)
{
}

void ConfGen::FragmentConformerGenerator::init()
{
	for (ConformerArray::const_iterator it = conformers.begin(), end = conformers.end(); it != end; ++it)
		freeCoordinatesArray(it->second);

	conformers.clear();
	timer.start();
}

Math::Vector3DArray::SharedPointer ConfGen::FragmentConformerGenerator::allocCoordinatesArray(std::size_t num_atoms)
{
 	Math::Vector3DArray::SharedPointer coords_ptr;

	if (!coordsArrayCache.empty()) {
		coords_ptr = coordsArrayCache.back();
		coordsArrayCache.pop_back();

	} else
		coords_ptr.reset(new Math::Vector3DArray());

	Math::Vector3DArray::SharedPointer coords();

	coords_ptr->resize(num_atoms);

	return coords_ptr;
}

void ConfGen::FragmentConformerGenerator::freeCoordinatesArray(const Math::Vector3DArray::SharedPointer& coords_ptr)
{
	coordsArrayCache.push_back(coords_ptr);
}
