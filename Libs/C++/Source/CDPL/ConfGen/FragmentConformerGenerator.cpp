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
#include <boost/math/special_functions.hpp>

#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/AtomType.hpp"
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


namespace
{

	const std::size_t MIN_MACROCYCLE_SIZE = 10;
}


using namespace CDPL;


const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_OUTPUT_CONFORMERS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MIN_NUM_RING_CONFORMER_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_RING_CONFORMER_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_TIMEOUT;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_RING_CONFORMER_TRIAL_FACTOR;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_ENERGY_DELTA  = 0.001;
const double       ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW                   = 4.0;
const double       ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD                        = 0.1;


ConfGen::FragmentConformerGenerator::FragmentConformerGenerator(): 
    maxNumStructGenTrials(DEF_MAX_NUM_STRUCTURE_GEN_TRIALS), maxNumMinSteps(DEF_MAX_NUM_MINIMIZATION_STEPS), 
	maxNumOutputConfs(DEF_MAX_NUM_OUTPUT_CONFORMERS), minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), 
	minStopEnergyDelta(DEF_MINIMIZATION_STOP_ENERGY_DELTA), timeout(DEF_TIMEOUT), reuseExistingCoords(false), 
	eWindow(DEF_ENERGY_WINDOW), ringConfTrialFactor(DEF_RING_CONFORMER_TRIAL_FACTOR), 
	minNumRingConfTrials(DEF_MIN_NUM_RING_CONFORMER_TRIALS), maxNumRingConfTrials(DEF_MAX_NUM_RING_CONFORMER_TRIALS),
	minRMSD(DEF_MIN_RMSD), energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
	using namespace Chem;

    rawCoordsGenerator.excludeHydrogens(true);
    rawCoordsGenerator.regardAtomConfiguration(true);
    rawCoordsGenerator.regardBondConfiguration(true);
	rawCoordsGenerator.enablePlanarityConstraints(true);

	hCoordsGenerator.undefinedOnly(true);

	automorphGroupSearch.includeIdentityMapping(false);
	automorphGroupSearch.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | 
											  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY |
											  AtomPropertyFlag::EXPLICIT_BOND_COUNT | AtomPropertyFlag::HYBRIDIZATION_STATE);
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

void ConfGen::FragmentConformerGenerator::setMinimizationStopEnergyDelta(double e_delta)
{
	minStopEnergyDelta = e_delta;
}

double ConfGen::FragmentConformerGenerator::getMinimizationStopEnergyDelta() const
{
	return minStopEnergyDelta;
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

void ConfGen::FragmentConformerGenerator::setRingConformerTrialFactor(std::size_t factor)
{
	ringConfTrialFactor = factor;
}

std::size_t ConfGen::FragmentConformerGenerator::getRingConformerTrialFactor() const
{
	return ringConfTrialFactor;
}

void ConfGen::FragmentConformerGenerator::setMinNumRingConformerTrials(std::size_t min_num)
{
	minNumRingConfTrials = min_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMinNumRingConformerTrials() const
{
	return minNumRingConfTrials;
}

void ConfGen::FragmentConformerGenerator::setMaxNumRingConformerTrials(std::size_t max_num)
{
	maxNumRingConfTrials = max_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMaxNumRingConformerTrials() const
{
	return maxNumRingConfTrials;
}

void ConfGen::FragmentConformerGenerator::setMinRMSD(double min_rmsd)
{
	minRMSD = min_rmsd;
}

double ConfGen::FragmentConformerGenerator::getMinRMSD() const
{
	return minRMSD;
}

void ConfGen::FragmentConformerGenerator::setMaxNumOutputConformers(std::size_t max_num)
{
	maxNumOutputConfs = max_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMaxNumOutputConformers() const
{
	return maxNumOutputConfs;
}

void ConfGen::FragmentConformerGenerator::setProgressCallback(const ProgressCallbackFunction& func)
{
	progCallback = func;
}

const ConfGen::FragmentConformerGenerator::ProgressCallbackFunction& 
ConfGen::FragmentConformerGenerator::getProgressCallback() const
{
	return progCallback;
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

	if (reuseExistingCoords && outputExistingCoordinates(conf)) {
		outputConfs.push_back(conf);

		if (progCallback)
			progCallback();

		return;
	}

	initRandomConformerGeneration();

	rawCoordsGenerator.setBoxSize(ordHDepleteAtomMask.count() * 2);

	if (!generateRandomConformer(conf, true))
		return;

	outputConfs.push_back(conf);

	if (progCallback)
		progCallback();
}

void ConfGen::FragmentConformerGenerator::generateFlexibleRingConformers()
{
	initRandomConformerGeneration();

	rawCoordsGenerator.setBoxSize(ordHDepleteAtomMask.count());

	getRingAtomIndices();
	getAtomSymmetryMappings();

	double e_window = eWindow;
	std::size_t num_trials = 0;

	if (isMacrocyclicRingSystem()) {
		e_window = calcMacrocyclicRingSystemEnergyWindow();
		num_trials = calcMacrocyclicRingSystemConformerTrials();

	} else 
		num_trials = calcStandardRingSystemConformerTrials();
	
	num_trials = std::max(minNumRingConfTrials, std::min(maxNumRingConfTrials, num_trials));

	double min_energy = 0.0;

	for (std::size_t i = 0; i < num_trials; i++) {
		if (timeoutExceeded()) 
			break;

		if (progCallback && !progCallback())
			break;

		ConfData conf;

		if (!generateRandomConformer(conf, false)) 
			continue;

		Vec3DArrayDeallocator dealloc_guard(this, conf);

		if (workingConfs.empty())
			min_energy = conf.first;

		else if (conf.first > (min_energy + e_window))
			continue;

		if (conf.first < min_energy)
			min_energy = conf.first;

		workingConfs.push_back(conf);
		dealloc_guard.release();
	}

	if (workingConfs.empty())
		return;

	std::sort(workingConfs.begin(), workingConfs.end(), 
			  boost::bind(std::less<double>(), boost::bind(&ConfData::first, _1), boost::bind(&ConfData::first, _2)));

	double max_energy = workingConfs.front().first + e_window;

	for (ConfDataArray::const_iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		const ConfData& conf = *it;
		Vec3DArrayDeallocator dealloc_guard(this, conf);

		if (outputConfs.size() >= maxNumOutputConfs) 
			continue;

		if (conf.first > max_energy || !checkRMSD(conf))
			continue;

		outputConfs.push_back(conf);
		dealloc_guard.release();

		const Math::Vector3DArray& coords = *conf.second;

		for (std::size_t mapping_offs = 0, mappings_size = atomSymmetryMappings.size(); 
			 mapping_offs < mappings_size && outputConfs.size() < maxNumOutputConfs; mapping_offs += numAtoms) {

			ConfData sym_conf;

			allocVector3DArray(sym_conf);

			Vec3DArrayDeallocator dealloc_guard(this, sym_conf);
			Math::Vector3DArray& sym_coords = *sym_conf.second;

			sym_coords.resize(numAtoms);

			for (std::size_t k = 0; k < numAtoms; k++)
				sym_coords[atomSymmetryMappings[mapping_offs + k]].assign(coords[k]);

			if (!checkRMSD(sym_conf))
				continue;

			sym_conf.first = conf.first;

			outputConfs.push_back(sym_conf);
			dealloc_guard.release();
		}
	}
}

void ConfGen::FragmentConformerGenerator::init(const Chem::MolecularGraph& molgraph, 
											   const ForceField::MMFF94InteractionData& ia_data)
{
	std::for_each(outputConfs.begin(), outputConfs.end(), 
				  boost::bind(static_cast<void (FragmentConformerGenerator::*)(const ConfData&)>(
								  &FragmentConformerGenerator::freeVector3DArray), this, _1));

	std::for_each(ringAtomCoords.begin(), ringAtomCoords.end(), 
				  boost::bind(static_cast<void (FragmentConformerGenerator::*)(const Math::Vector3DArray::SharedPointer&)>(
								  &FragmentConformerGenerator::freeVector3DArray), this, _1));

	outputConfs.clear();
	workingConfs.clear();
	ringAtomCoords.clear();

	timer.start();

	molGraph = &molgraph;
	mmff94Interactions = &ia_data;
	numAtoms = molgraph.getNumAtoms();
}

void ConfGen::FragmentConformerGenerator::initRandomConformerGeneration()
{
	rawCoordsGenerator.setup(*molGraph, *mmff94Interactions);

	ordHDepleteAtomMask.resize(numAtoms);
	ordHDepleteAtomMask = rawCoordsGenerator.getExcludedHydrogenMask();
	ordHDepleteAtomMask.flip();

	hCoordsGenerator.setAtom3DCoordinatesCheckFunction(boost::bind(&FragmentConformerGenerator::has3DCoordinates, this, _1));
	hCoordsGenerator.setup(*molGraph);

	mmff94EnergyCalc.setup(*mmff94Interactions);
	mmff94GradientCalc.setup(*mmff94Interactions, numAtoms);

    gradient.resize(numAtoms);
}

bool ConfGen::FragmentConformerGenerator::outputExistingCoordinates(ConfData& conf)
{
	using namespace Chem;

	allocVector3DArray(conf);

	Vec3DArrayDeallocator dealloc_guard(this, conf);
	Math::Vector3DArray& coords = *conf.second;

	if (getExistingCoordinates(*molGraph, coords)) {
		dealloc_guard.release();
		
		return true;
	}
	
	return false;
}

bool ConfGen::FragmentConformerGenerator::getExistingCoordinates(const Chem::MolecularGraph& molgraph, Math::Vector3DArray& coords)
{
	using namespace Chem;

	std::size_t num_atoms = molgraph.getNumAtoms();
	bool have_h_atom_coords = true;

	coords.resize(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = molgraph.getAtom(i);

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
		hCoordsGenerator.generate(molgraph, coords, false);
	}

	return true;
}

bool ConfGen::FragmentConformerGenerator::generateRandomConformer(ConfData& conf, bool best_opt)
{
	allocVector3DArray(conf);

	Vec3DArrayDeallocator dealloc_guard(this, conf);
	Math::Vector3DArray& coords = *conf.second;
	std::size_t i = 0;

	for ( ; i < maxNumStructGenTrials; i++) {
		if (!rawCoordsGenerator.generate(coords)) 
			continue;

		hCoordsGenerator.generate(coords, false);
		energyMinimizer.setup(coords.getData(), gradient);

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if (energyMinimizer.iterate(conf.first, coords.getData(), gradient) != BFGSMinimizer::SUCCESS) {
				if ((boost::math::isnan)(conf.first))
					return false;

				break;
			}

			if ((boost::math::isnan)(conf.first))
				return false;
		
			if (best_opt && minStopEnergyDelta >= 0.0 && minStopGradNorm >= 0.0) {
				if (energyMinimizer.getFunctionDelta() <= minStopEnergyDelta && energyMinimizer.getGradientNorm() <= minStopGradNorm)
					break;

				continue;
			}

			if (minStopEnergyDelta >= 0.0 && energyMinimizer.getFunctionDelta() <= minStopEnergyDelta)
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
	Math::Vector3DArray::SharedPointer conf_ha_coords_ptr = getRingAtomCoordinates(conf);

	Vec3DArrayDeallocator dealloc_guard(this, conf_ha_coords_ptr);
	Math::Vector3DArray& conf_ha_coords = *conf_ha_coords_ptr;
	Math::Matrix4D conf_xform;

	for (Vector3DArrayList::const_reverse_iterator it = ringAtomCoords.rbegin(), end = ringAtomCoords.rend(); it != end; ++it) {
		const Math::Vector3DArray& prev_conf_ha_coords = **it;

		if (!alignmentCalc.calculate(prev_conf_ha_coords, conf_ha_coords, false))
			return false;

		conf_xform.assign(alignmentCalc.getTransform());

		double rmsd = calcRMSD(prev_conf_ha_coords, conf_ha_coords, conf_xform);

		if (rmsd < minRMSD)
			return false;
	}

	ringAtomCoords.push_back(conf_ha_coords_ptr);
	dealloc_guard.release();

	return true;
}

bool ConfGen::FragmentConformerGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return ordHDepleteAtomMask.test(molGraph->getAtomIndex(atom));
}

Math::Vector3DArray::SharedPointer ConfGen::FragmentConformerGenerator::getRingAtomCoordinates(const ConfData& conf)
{
	Math::Vector3DArray::SharedPointer ha_coords_ptr = allocVector3DArray();
	
	Vec3DArrayDeallocator dealloc_guard(this, ha_coords_ptr);
	const Math::Vector3DArray& coords = *conf.second;
	Math::Vector3DArray& ha_coords = *ha_coords_ptr;
	Math::Vector3D ctr;

	ha_coords.clear();

	for (IndexList::const_iterator it = ringAtomIndices.begin(), end = ringAtomIndices.end(); it != end; ++it) {
		const Math::Vector3D& pos = coords[*it];

		ctr += pos;

		ha_coords.addElement(pos);
	}

	ctr /= ringAtomIndices.size();

	for (Math::Vector3DArray::ElementIterator it = ha_coords.getElementsBegin(), end = ha_coords.getElementsEnd(); it != end; ++it)
		*it -= ctr;

	dealloc_guard.release();

	return ha_coords_ptr;
}

void ConfGen::FragmentConformerGenerator::getRingAtomIndices()
{
	using namespace Chem;

	ringAtomIndices.clear();

	for (std::size_t i = 0; i < numAtoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		if (getRingFlag(atom) && getRingBondCount(atom, *molGraph) >= 2)
			ringAtomIndices.push_back(i);
	}
}

void ConfGen::FragmentConformerGenerator::getAtomSymmetryMappings()
{
	using namespace Chem;

	ordHDepleteMolGraph.clear();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (ordHDepleteAtomMask.test(molGraph->getAtomIndex(bond.getBegin())) && ordHDepleteAtomMask.test(molGraph->getAtomIndex(bond.getEnd())))
			ordHDepleteMolGraph.addBond(bond);
	}

	automorphGroupSearch.findMappings(ordHDepleteMolGraph);
	atomSymmetryMappings.resize(automorphGroupSearch.getNumMappings() * numAtoms);

	std::size_t mapping_offs = 0;

	for (AutomorphismGroupSearch::ConstMappingIterator it = automorphGroupSearch.getMappingsBegin(), 
			 end = automorphGroupSearch.getMappingsEnd(); it != end; ++it) {

		const AtomMapping& am = it->getAtomMapping();
		AtomMapping::ConstEntryIterator am_end = am.getEntriesEnd();
		bool keep_mapping = false;

		for (AtomMapping::ConstEntryIterator am_it = am.getEntriesBegin(); am_it != am_end; ++am_it) {
			const Atom& first_atom = *am_it->first;
			const Atom& second_atom = *am_it->second;

			atomSymmetryMappings[mapping_offs + molGraph->getAtomIndex(first_atom)] = molGraph->getAtomIndex(second_atom);

			if (getType(first_atom) == AtomType::H)
				continue;

			if (&first_atom != &second_atom && 
				(getAromaticityFlag(first_atom) || 
				 (getRingFlag(first_atom) && getRingBondCount(first_atom, *molGraph) < getHeavyBondCount(first_atom, *molGraph))))
				keep_mapping = true;

			getNeighborHydrogens(first_atom, nbrHydrogens1);
			getNeighborHydrogens(second_atom, nbrHydrogens2);

			bool bad_mapping = false;

			for (std::size_t i = 0; i < nbrHydrogens1.size(); ) {
				AtomMapping::ConstEntryIterator am_it2 = am.getEntry(nbrHydrogens1[i]);

				if (am_it2 == am_end) {
					i++;
					continue;
				}

				nbrHydrogens1.erase(nbrHydrogens1.begin() + i);

				AtomList::iterator al_it = std::find(nbrHydrogens2.begin(), nbrHydrogens2.end(), am_it2->second);

				if (al_it == nbrHydrogens2.end()) {
					bad_mapping = true;
					break;
				}
				
				nbrHydrogens2.erase(al_it);
			}

			if (bad_mapping || (nbrHydrogens1.size() != nbrHydrogens2.size())) { 
				keep_mapping = false;
				break;
			}

			for (std::size_t i = 0; i < nbrHydrogens1.size(); i++)
				atomSymmetryMappings[mapping_offs + molGraph->getAtomIndex(*nbrHydrogens1[i])] = molGraph->getAtomIndex(*nbrHydrogens2[i]);
		}

		if (keep_mapping)
			mapping_offs += numAtoms;
	}

	atomSymmetryMappings.resize(mapping_offs);
}

void ConfGen::FragmentConformerGenerator::getNeighborHydrogens(const Chem::Atom& atom, AtomList& nbr_list) const
{
	using namespace Chem;

	nbr_list.clear();

	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		if (!molGraph->containsBond(*b_it))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		if (getType(nbr_atom) != AtomType::H)
			continue;

		nbr_list.push_back(&nbr_atom);
	}
}

bool ConfGen::FragmentConformerGenerator::isMacrocyclicRingSystem() const
{
	using namespace Chem;

	const FragmentList& sssr = *getSSSR(*molGraph);

	return (std::find_if(sssr.getElementsBegin(), sssr.getElementsEnd(),
						 boost::bind(std::greater<std::size_t>(), boost::bind(&Fragment::getNumAtoms, _1), MIN_MACROCYCLE_SIZE)) !=
			sssr.getElementsEnd());
}

std::size_t ConfGen::FragmentConformerGenerator::calcStandardRingSystemConformerTrials() const
{
	using namespace Chem;

	double ring_flex_sum = 0.0;
	const FragmentList& sssr = *getSSSR(*molGraph);

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;

		if (getNumRotatableRingBonds(ring) > 0)
			ring_flex_sum += double(ring.getNumAtoms()) / 6;
	}

	return (ring_flex_sum * ringConfTrialFactor);
}

std::size_t ConfGen::FragmentConformerGenerator::calcMacrocyclicRingSystemConformerTrials() const
{
	return std::pow(2, getNumRotatableRingBonds(*molGraph));
}

double ConfGen::FragmentConformerGenerator::calcMacrocyclicRingSystemEnergyWindow() const
{
	return (getNumRotatableRingBonds(*molGraph) * eWindow);
}

std::size_t ConfGen::FragmentConformerGenerator::getNumRotatableRingBonds(const Chem::MolecularGraph& molgraph) const
{
	using namespace Chem;

	std::size_t count = 0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
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

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(timeout) * 1000000));
}

void ConfGen::FragmentConformerGenerator::freeVector3DArray(const ConfData& conf)
{
	freeVector3DArray(conf.second);
}

void ConfGen::FragmentConformerGenerator::allocVector3DArray(ConfData& conf)
{
	conf.second = allocVector3DArray();
}

void ConfGen::FragmentConformerGenerator::freeVector3DArray(const Math::Vector3DArray::SharedPointer& coords_ptr)
{
	coordArrayCache.push_back(coords_ptr);
}

Math::Vector3DArray::SharedPointer ConfGen::FragmentConformerGenerator::allocVector3DArray()
{
	if (!coordArrayCache.empty()) {
		Math::Vector3DArray::SharedPointer coords_ptr = coordArrayCache.back();

		coordArrayCache.pop_back();

		return coords_ptr;
	} 

	return Math::Vector3DArray::SharedPointer(new Math::Vector3DArray());
}
