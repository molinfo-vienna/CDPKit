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

#include <cmath>
#include <algorithm>
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_RING_CONFORMERS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_TIMEOUT;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_RING_CONF_RETRIAL_FACTOR;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;
const double       ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW                   = 4.0;
const double       ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD                        = 0.1;


ConfGen::FragmentConformerGenerator::FragmentConformerGenerator(): 
    maxNumStructGenTrials(DEF_MAX_NUM_STRUCTURE_GEN_TRIALS), maxNumMinSteps(DEF_MAX_NUM_MINIMIZATION_STEPS), 
	maxNumRingConfs(DEF_MAX_NUM_RING_CONFORMERS), minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), 
	timeout(DEF_TIMEOUT), reuseExistingCoords(false), eWindow(DEF_ENERGY_WINDOW), 
	ringConfRetrialFact(DEF_RING_CONF_RETRIAL_FACTOR), minRMSD(DEF_MIN_RMSD),
	energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
    rawCoordsGenerator.excludeHydrogens(true);
    rawCoordsGenerator.regardAtomConfiguration(true);
    rawCoordsGenerator.regardBondConfiguration(true);
	rawCoordsGenerator.enablePlanarityConstraints(true);

	hCoordsGenerator.undefinedOnly(true);
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

void ConfGen::FragmentConformerGenerator::setMaxNumRingConformers(std::size_t max_num)
{
	maxNumRingConfs = max_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMaxNumRingConformers() const
{
	return maxNumRingConfs;
}

std::size_t ConfGen::FragmentConformerGenerator::generate(const Chem::MolecularGraph& molgraph, 
														  const ForceField::MMFF94InteractionData& ia_data,
														  unsigned int frag_type) 
{
	init(molgraph, ia_data);

	if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
		generateFlexibleRingConformers();
	else
		generateSingleConformer();

	return outputConfs.size();
}

std::size_t ConfGen::FragmentConformerGenerator::getNumConformers() const
{
	return outputConfs.size();
}

const Math::Vector3DArray& ConfGen::FragmentConformerGenerator::getCoordinates(std::size_t conf_idx) const
{
	if (conf_idx >= outputConfs.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return *outputConfs[conf_idx].second;
}

Math::Vector3DArray& ConfGen::FragmentConformerGenerator::getCoordinates(std::size_t conf_idx)
{
	if (conf_idx >= outputConfs.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return *outputConfs[conf_idx].second;
}

double ConfGen::FragmentConformerGenerator::getEnergy(std::size_t conf_idx) const
{
	if (conf_idx >= outputConfs.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return outputConfs[conf_idx].first;
}

void ConfGen::FragmentConformerGenerator::generateSingleConformer()
{
	ConfData conf;

	if (reuseExistingCoords && extractExistingCoordinates(conf)) {
		outputConfs.push_back(conf);
		return;
	}

	initRandomConformerGeneration();

	rawCoordsGenerator.setBoxSize(numAtoms * 2);

	if (!generateRandomConformer(conf))
		return;

	outputConfs.push_back(conf);
}

void ConfGen::FragmentConformerGenerator::generateFlexibleRingConformers()
{
	initRandomConformerGeneration();

	rawCoordsGenerator.setBoxSize(std::sqrt(double(numAtoms)) * 4);

	getHeavyAtomIndices();

	double e_window = eWindow;
	std::size_t num_retrials = 0;

	if (isMacrocyclicRingSystem()) {
		std::size_t num_rot_bonds = getNumRotatableRingBonds();

		e_window = num_rot_bonds * e_window;
		num_retrials = std::pow(2, num_rot_bonds);

	} else {
		num_retrials = getSSSR(*molGraph)->getSize() * ringConfRetrialFact;
	}

	num_retrials = std::min(maxNumRingConfs * 2, num_retrials); 
	num_retrials = std::max(ringConfRetrialFact * 2, num_retrials); 

	double min_energy = 0.0;

	for (std::size_t i = 0; i < num_retrials; i++) {
		std::cerr << '.';

		ConfData conf;

		if (!generateRandomConformer(conf)) {
			std::cerr << "random coords gen failed at trial " << i << " " <<  num_retrials << std::endl;
			break;
		}

		CoordsDeallocator dealloc_guard(this, conf);

		if (workingConfs.empty())
			min_energy = conf.first;

		else if (conf.first > min_energy + e_window)
			continue;

		if (conf.first < min_energy)
			min_energy = conf.first;

		workingConfs.push_back(conf);
		dealloc_guard.release();
	}
	std::cerr << std::endl;
	if (workingConfs.empty())
		return;

	std::sort(workingConfs.begin(), workingConfs.end(), 
			  boost::bind(std::less<double>(), boost::bind(&ConfData::first, _1), boost::bind(&ConfData::first, _2)));

	double max_energy = workingConfs.front().first + e_window;

	for (ConfDataArray::const_iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		const ConfData& conf = *it;
		CoordsDeallocator dealloc_guard(this, conf);

		if (outputConfs.size() >= maxNumRingConfs) 
			continue;

		if (conf.first > max_energy || !checkRMSD(conf))
			continue;
	
		outputConfs.push_back(conf);
		dealloc_guard.release();
	}
}

void ConfGen::FragmentConformerGenerator::init(const Chem::MolecularGraph& molgraph, 
											   const ForceField::MMFF94InteractionData& ia_data)
{
	std::for_each(outputConfs.begin(), outputConfs.end(), 
				  boost::bind(static_cast<void (FragmentConformerGenerator::*)(const ConfData&)>(
								  &FragmentConformerGenerator::freeCoordinates), this, _1));

	std::for_each(heavyAtomCoords.begin(), heavyAtomCoords.end(), 
				  boost::bind(static_cast<void (FragmentConformerGenerator::*)(const Math::Vector3DArray::SharedPointer&)>(
								  &FragmentConformerGenerator::freeCoordinates), this, _1));

	outputConfs.clear();
	workingConfs.clear();
	heavyAtomCoords.clear();

	timer.start();

	molGraph = &molgraph;
	mmff94Interactions = &ia_data;
	numAtoms = molgraph.getNumAtoms();
}

void ConfGen::FragmentConformerGenerator::initRandomConformerGeneration()
{
	rawCoordsGenerator.setup(*molGraph, *mmff94Interactions);

	heavyAtomMask.resize(numAtoms);
	heavyAtomMask = rawCoordsGenerator.getExcludedHydrogenMask();
	heavyAtomMask.flip();

	hCoordsGenerator.setAtom3DCoordinatesCheckFunction(boost::bind(&FragmentConformerGenerator::has3DCoordinates, this, _1));
	hCoordsGenerator.setup(*molGraph);

	mmff94EnergyCalc.setup(*mmff94Interactions);
	mmff94GradientCalc.setup(*mmff94Interactions, numAtoms);

    gradient.resize(numAtoms);
}

bool ConfGen::FragmentConformerGenerator::extractExistingCoordinates(ConfData& conf)
{
	using namespace Chem;

	allocCoordinates(conf);

	CoordsDeallocator dealloc_guard(this, conf);
	Math::Vector3DArray& coords = *conf.second;
	bool have_h_atom_coords = true;

	coords.resize(numAtoms);

	for (std::size_t i = 0; i < numAtoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		try {
			coords[i] = get3DCoordinates(atom);

		} catch (const Base::ItemNotFound& e) {
			if (getType(atom) != AtomType::H) 
				return false;
			
			have_h_atom_coords = false;
		}
	}

	if (!have_h_atom_coords) { 
		hCoordsGenerator.setAtom3DCoordinatesCheckFunction(&Chem::has3DCoordinates);
		hCoordsGenerator.generate(*molGraph, coords, false);
	}

	dealloc_guard.release();

	return true;
}

bool ConfGen::FragmentConformerGenerator::generateRandomConformer(ConfData& conf)
{
	if (timeoutExceeded()) {
		std::cerr << "TIMEOUT" << std::endl;
		return false;
	}

	allocCoordinates(conf);

	CoordsDeallocator dealloc_guard(this, conf);
	Math::Vector3DArray& coords = *conf.second;
	std::size_t i = 0;

	for ( ; i < maxNumStructGenTrials; i++) {
		if (!rawCoordsGenerator.generate(coords)) 
			continue;

		hCoordsGenerator.generate(coords, false);
		energyMinimizer.setup(coords.getData(), gradient);

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if (energyMinimizer.iterate(conf.first, coords.getData(), gradient) != BFGSMinimizer::SUCCESS)
				break;
		
			if (energyMinimizer.getFunctionDelta() < 0.0025) // TODO
				break;

			if (minStopGradNorm >= 0.0 && energyMinimizer.getGradientNorm() <= minStopGradNorm)
				break;
		}

		if (!rawCoordsGenerator.checkAtomConfigurations(coords)) 
			continue;
		
		if (rawCoordsGenerator.checkBondConfigurations(coords)) 
			break;
	}

	if (i >= maxNumStructGenTrials) 
		return false;

	dealloc_guard.release();

	return true;
}

bool ConfGen::FragmentConformerGenerator::checkRMSD(const ConfData& conf)
{
	Math::Vector3DArray::SharedPointer conf_ha_coords_ptr = getHeavyAtomCoordinates(conf);

	CoordsDeallocator dealloc_guard(this, conf_ha_coords_ptr);
	Math::Vector3DArray& conf_ha_coords = *conf_ha_coords_ptr;
	Math::Matrix4D conf_xform;

	for (CoordsDataArray::iterator it = heavyAtomCoords.begin(), end = heavyAtomCoords.end(); it != end; ++it) {
		const Math::Vector3DArray& prev_conf_ha_coords = **it;

		if (!alignmentCalc.calculate(prev_conf_ha_coords, conf_ha_coords, false))
			return false;

		conf_xform.assign(alignmentCalc.getTransform());

		double rmsd = calcRMSD(prev_conf_ha_coords, conf_ha_coords, conf_xform);

		if (rmsd < minRMSD)
			return false;
	}

	heavyAtomCoords.push_back(conf_ha_coords_ptr);
	dealloc_guard.release();

	return true;
}


bool ConfGen::FragmentConformerGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return heavyAtomMask.test(molGraph->getAtomIndex(atom));
}

Math::Vector3DArray::SharedPointer ConfGen::FragmentConformerGenerator::getHeavyAtomCoordinates(const ConfData& conf)
{
	Math::Vector3DArray::SharedPointer ha_coords_ptr = allocCoordinates();
	
	CoordsDeallocator dealloc_guard(this, ha_coords_ptr);
	const Math::Vector3DArray& coords = *conf.second;
	Math::Vector3DArray& ha_coords = *ha_coords_ptr;
	Math::Vector3D ctr;

	ha_coords.clear();

	for (IndexList::const_iterator it = heavyAtomIndices.begin(), end = heavyAtomIndices.end(); it != end; ++it) {
		const Math::Vector3D& pos = coords[*it];

		ctr += pos;

		ha_coords.addElement(pos);
	}

	ctr /= heavyAtomIndices.size();

	for (Math::Vector3DArray::ElementIterator it = ha_coords.getElementsBegin(), end = ha_coords.getElementsEnd(); it != end; ++it)
		*it -= ctr;

	dealloc_guard.release();

	return ha_coords_ptr;
}

void ConfGen::FragmentConformerGenerator::getHeavyAtomIndices()
{
	using namespace Chem;

	heavyAtomIndices.clear();

	for (std::size_t i = 0; i < numAtoms; i++)
		if (getType(molGraph->getAtom(i)) != AtomType::H)
			heavyAtomIndices.push_back(i);
}

bool ConfGen::FragmentConformerGenerator::isMacrocyclicRingSystem() const
{
	using namespace Chem;

	const Chem::FragmentList& sssr = *getSSSR(*molGraph);

	return (std::find_if(sssr.getElementsBegin(), sssr.getElementsEnd(),
						 boost::bind(std::greater<std::size_t>(), boost::bind(&Fragment::getNumAtoms, _1), 10)) !=
			sssr.getElementsEnd());
}

std::size_t ConfGen::FragmentConformerGenerator::getNumRotatableRingBonds() const
{
	using namespace Chem;

	std::size_t count = 0;

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (getRingFlag(bond) && !getAromaticityFlag(bond) && getOrder(bond) == 1)
			count++;
	}

	return count;
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

void ConfGen::FragmentConformerGenerator::freeCoordinates(const ConfData& conf)
{
	freeCoordinates(conf.second);
}

void ConfGen::FragmentConformerGenerator::allocCoordinates(ConfData& conf)
{
	conf.second = allocCoordinates();
}

void ConfGen::FragmentConformerGenerator::freeCoordinates(const Math::Vector3DArray::SharedPointer& coords_ptr)
{
	coordsCache.push_back(coords_ptr);
}

Math::Vector3DArray::SharedPointer ConfGen::FragmentConformerGenerator::allocCoordinates()
{
	if (!coordsCache.empty()) {
		Math::Vector3DArray::SharedPointer coords_ptr = coordsCache.back();

		coordsCache.pop_back();

		return coords_ptr;
	} 

	return Math::Vector3DArray::SharedPointer(new Math::Vector3DArray());
}
