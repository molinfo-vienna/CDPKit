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
#include "CDPL/ConfGen/ReturnCode.hpp"
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
#include "CDPL/ForceField/Exceptions.hpp"


namespace
{

	const std::size_t MIN_MACROCYCLE_SIZE         = 10;
	const std::size_t MAX_VECTOR_ARRAY_CACHE_SIZE = 5000;
}


using namespace CDPL;


const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_OUTPUT_CONFORMERS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MIN_NUM_RING_CONFORMER_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_RING_CONFORMER_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_TIMEOUT;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_RING_CONFORMER_TRIAL_FACTOR;
const unsigned int ConfGen::FragmentConformerGenerator::DEF_FORCEFIELD_TYPE;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.1;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_ENERGY_DELTA  = 0.001;
const double       ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW                   = 4.0;
const double       ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD                        = 0.1;


ConfGen::FragmentConformerGenerator::FragmentConformerGenerator(): 
	vecArrayCache(MAX_VECTOR_ARRAY_CACHE_SIZE),
    maxNumStructGenTrials(DEF_MAX_NUM_STRUCTURE_GEN_TRIALS), maxNumMinSteps(DEF_MAX_NUM_MINIMIZATION_STEPS), 
	maxNumOutputConfs(DEF_MAX_NUM_OUTPUT_CONFORMERS), minStopGradNorm(DEF_MINIMIZATION_STOP_GRADIENT_NORM), 
	minStopEnergyDelta(DEF_MINIMIZATION_STOP_ENERGY_DELTA), timeout(DEF_TIMEOUT), reuseExistingCoords(false), 
	eWindow(DEF_ENERGY_WINDOW), ringConfTrialFactor(DEF_RING_CONFORMER_TRIAL_FACTOR), 
	minNumRingConfTrials(DEF_MIN_NUM_RING_CONFORMER_TRIALS), maxNumRingConfTrials(DEF_MAX_NUM_RING_CONFORMER_TRIALS),
	minRMSD(DEF_MIN_RMSD), forceFieldType(DEF_FORCEFIELD_TYPE), energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
	using namespace Chem;

    dgStructGen.excludeHydrogens(true);
    dgStructGen.regardAtomConfiguration(true);
    dgStructGen.regardBondConfiguration(true);
	dgStructGen.enablePlanarityConstraints(true);

	hCoordsGen.undefinedOnly(true);

	symMappingSearch.includeIdentityMapping(false);
	symMappingSearch.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | 
										  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY |
										  AtomPropertyFlag::EXPLICIT_BOND_COUNT | AtomPropertyFlag::HYBRIDIZATION_STATE);

	mmff94Parameterizer.performStrictAtomTyping(true);
}

void ConfGen::FragmentConformerGenerator::setMaxNumStructureGenerationTrials(std::size_t max_num)
{
	maxNumStructGenTrials = max_num;
}

std::size_t ConfGen::FragmentConformerGenerator::getMaxNumStructureGenerationTrials() const
{
	return maxNumStructGenTrials;
}

void ConfGen::FragmentConformerGenerator::setForceFieldType(unsigned int type)
{
	if (type == ForceFieldType::MMFF94 || type == ForceFieldType::MMFF94_NO_ESTAT)
		mmff94Parameterizer.setDynamicParameterDefaults();
	else
		mmff94Parameterizer.setStaticParameterDefaults();

	forceFieldType = type;
}
	    
unsigned int ConfGen::FragmentConformerGenerator::getForceFieldType() const
{
	return forceFieldType;
}

void ConfGen::FragmentConformerGenerator::performStrictAtomTyping(bool strict)
{
	mmff94Parameterizer.performStrictAtomTyping(strict);
}

bool ConfGen::FragmentConformerGenerator::strictAtomTypingPerformed() const
{
	return mmff94Parameterizer.strictAtomTypingPerformed();
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

unsigned int ConfGen::FragmentConformerGenerator::generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type) 
{
	init(molgraph);

	if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
		return generateFlexibleRingConformers();
	
	return generateSingleConformer();
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

unsigned int ConfGen::FragmentConformerGenerator::generateSingleConformer()
{
	ConfData conf;

	if (reuseExistingCoords && outputExistingCoordinates(conf)) {
		outputConfs.push_back(conf);

		if (progCallback)
			progCallback();

		return ReturnCode::SUCCESS;
	}

	if (!initRandomConformerGeneration())
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	dgStructGen.setBoxSize(ordHDepleteAtomMask.count() * 2);

	unsigned int ret_code = generateRandomConformer(conf, true);
		
	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	outputConfs.push_back(conf);

	if (progCallback)
		progCallback();

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::FragmentConformerGenerator::generateFlexibleRingConformers()
{
	if (!initRandomConformerGeneration())
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	dgStructGen.setBoxSize(ordHDepleteAtomMask.count());

	getRingAtomIndices();
	getSymmetryMappings();

	double e_window = eWindow;
	std::size_t num_trials = 0;

	if (isMacrocyclicRingSystem()) {
		e_window = calcMacrocyclicRingSystemEnergyWindow();
		num_trials = calcMacrocyclicRingSystemConformerTrials();

	} else 
		num_trials = calcStandardRingSystemConformerTrials();
	
	num_trials = std::max(minNumRingConfTrials, std::min(maxNumRingConfTrials, num_trials));

	double min_energy = 0.0;
	unsigned int ret_code = ReturnCode::SUCCESS;

	for (std::size_t i = 0; i < num_trials; i++) {
		if (timeoutExceeded()) {
			ret_code = ReturnCode::TIMEOUT_EXCEEDED;
			break;
		}

		if (progCallback && !progCallback())
			break;

		ConfData conf;

		if (generateRandomConformer(conf, false) != ReturnCode::SUCCESS) 
			continue;

		if (workingConfs.empty())
			min_energy = conf.first;

		else if (conf.first > (min_energy + e_window))
			continue;

		if (conf.first < min_energy)
			min_energy = conf.first;

		workingConfs.push_back(conf);
	}

	if (workingConfs.empty()) {
		if (ret_code != ReturnCode::SUCCESS)
			return ret_code;

		return ReturnCode::MAX_NUM_TRIALS_EXCEEDED;
	}

	std::sort(workingConfs.begin(), workingConfs.end(), 
			  boost::bind(std::less<double>(), boost::bind(&ConfData::first, _1), boost::bind(&ConfData::first, _2)));

	double max_energy = workingConfs.front().first + e_window;

	for (ConfDataArray::iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		ConfData& conf = *it;

		if (outputConfs.size() >= maxNumOutputConfs) 
			return ReturnCode::SUCCESS;

		if (conf.first > max_energy)
			return ReturnCode::SUCCESS;

		if (!checkRMSD(conf)) {
			conf.second.reset();
			continue;
		}

		outputConfs.push_back(conf);

		const Math::Vector3DArray& coords = *conf.second;

		for (std::size_t mapping_offs = 0, mappings_size = symMappings.size(); 
			 mapping_offs < mappings_size && outputConfs.size() < maxNumOutputConfs; mapping_offs += numAtoms) {

			ConfData sym_conf;

			allocVectorArray(sym_conf);

			Math::Vector3DArray& sym_coords = *sym_conf.second;

			sym_coords.resize(numAtoms);

			for (std::size_t k = 0; k < numAtoms; k++)
				sym_coords[symMappings[mapping_offs + k]].assign(coords[k]);

			if (!checkRMSD(sym_conf))
				continue;

			sym_conf.first = conf.first;

			outputConfs.push_back(sym_conf);
		}
	}

	return ReturnCode::SUCCESS;
}

void ConfGen::FragmentConformerGenerator::init(const Chem::MolecularGraph& molgraph)
{
	outputConfs.clear();
	workingConfs.clear();
	ringAtomCoords.clear();

	timer.start();

	molGraph = &molgraph;
	numAtoms = molgraph.getNumAtoms();
}

bool ConfGen::FragmentConformerGenerator::initRandomConformerGeneration()
{
	const unsigned int ia_types = (forceFieldType == ForceFieldType::MMFF94 || forceFieldType == ForceFieldType::MMFF94S ?
								   ForceField::InteractionType::ALL :
								   ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC);

	try {
		mmff94Parameterizer.parameterize(*molGraph, mmff94Data, ia_types);

	} catch (const ForceField::Error&) {
		return false;
	}

	dgStructGen.setup(*molGraph, mmff94Data);

	ordHDepleteAtomMask.resize(numAtoms);
	ordHDepleteAtomMask = dgStructGen.getExcludedHydrogenMask();
	ordHDepleteAtomMask.flip();

	hCoordsGen.setAtom3DCoordinatesCheckFunction(boost::bind(&FragmentConformerGenerator::has3DCoordinates, this, _1));
	hCoordsGen.setup(*molGraph);

	mmff94EnergyCalc.setup(mmff94Data);
	mmff94GradientCalc.setup(mmff94Data, numAtoms);

    gradient.resize(numAtoms);

	return true;
}

bool ConfGen::FragmentConformerGenerator::outputExistingCoordinates(ConfData& conf)
{
	using namespace Chem;

	allocVectorArray(conf);

	if (getExistingCoordinates(*molGraph, *conf.second)) 
		return true;
	
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
		hCoordsGen.setAtom3DCoordinatesCheckFunction(&Chem::has3DCoordinates);
		hCoordsGen.generate(molgraph, coords, false);
	}

	return true;
}

unsigned int ConfGen::FragmentConformerGenerator::generateRandomConformer(ConfData& conf, bool best_opt)
{
	allocVectorArray(conf);

	Math::Vector3DArray& coords = *conf.second;

	for (std::size_t i = 0; i < maxNumStructGenTrials; i++) {
		if (!dgStructGen.generate(coords)) 
			continue;

		hCoordsGen.generate(coords, false);
		energyMinimizer.setup(coords.getData(), gradient);

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if (energyMinimizer.iterate(conf.first, coords.getData(), gradient) != BFGSMinimizer::SUCCESS) {
				if ((boost::math::isnan)(conf.first))
					return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

				break;
			}

			if ((boost::math::isnan)(conf.first))
				return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;
		
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

		if (!dgStructGen.checkAtomConfigurations(coords)) 
			continue;
		
		if (!dgStructGen.checkBondConfigurations(coords)) 
			continue;

		return ReturnCode::SUCCESS;
	}

	return ReturnCode::MAX_NUM_TRIALS_EXCEEDED;
}

bool ConfGen::FragmentConformerGenerator::checkRMSD(const ConfData& conf)
{
	VectorArrayPtr conf_ha_coords_ptr = getRingAtomCoordinates(conf);
	Math::Vector3DArray& conf_ha_coords = *conf_ha_coords_ptr;
	Math::Matrix4D conf_xform;

	for (VectorArrayList::const_reverse_iterator it = ringAtomCoords.rbegin(), end = ringAtomCoords.rend(); it != end; ++it) {
		const Math::Vector3DArray& prev_conf_ha_coords = **it;

		if (!alignmentCalc.calculate(prev_conf_ha_coords, conf_ha_coords, false))
			return false;

		conf_xform.assign(alignmentCalc.getTransform());

		double rmsd = calcRMSD(prev_conf_ha_coords, conf_ha_coords, conf_xform);

		if (rmsd < minRMSD)
			return false;
	}

	ringAtomCoords.push_back(conf_ha_coords_ptr);

	return true;
}

bool ConfGen::FragmentConformerGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return ordHDepleteAtomMask.test(molGraph->getAtomIndex(atom));
}

ConfGen::FragmentConformerGenerator::VectorArrayPtr ConfGen::FragmentConformerGenerator::getRingAtomCoordinates(const ConfData& conf)
{
	VectorArrayPtr ha_coords_ptr = vecArrayCache.get();
	Math::Vector3DArray& ha_coords = *ha_coords_ptr;
	const Math::Vector3DArray& coords = *conf.second;
	Math::Vector3D ctr;
	std::size_t num_ring_atoms = ringAtomIndices.size();

	ha_coords.resize(num_ring_atoms);

	for (std::size_t i = 0; i < num_ring_atoms; i++) {
		const Math::Vector3D& pos = coords[ringAtomIndices[i]];

		ctr += pos;
		ha_coords[i] = pos;
	}

	ctr /= num_ring_atoms;

	for (Math::Vector3DArray::ElementIterator it = ha_coords.getElementsBegin(), end = ha_coords.getElementsEnd(); it != end; ++it)
		*it -= ctr;

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

void ConfGen::FragmentConformerGenerator::getSymmetryMappings()
{
	using namespace Chem;

	symMappingSearchMolGraph.clear();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (ordHDepleteAtomMask.test(molGraph->getAtomIndex(bond.getBegin())) && ordHDepleteAtomMask.test(molGraph->getAtomIndex(bond.getEnd())))
			symMappingSearchMolGraph.addBond(bond);
	}

	symMappingSearch.findMappings(symMappingSearchMolGraph);
	symMappings.resize(symMappingSearch.getNumMappings() * numAtoms);

	std::size_t mapping_offs = 0;

	for (AutomorphismGroupSearch::ConstMappingIterator it = symMappingSearch.getMappingsBegin(), 
			 end = symMappingSearch.getMappingsEnd(); it != end; ++it) {

		const AtomMapping& am = it->getAtomMapping();
		AtomMapping::ConstEntryIterator am_end = am.getEntriesEnd();
		bool keep_mapping = false;

		for (AtomMapping::ConstEntryIterator am_it = am.getEntriesBegin(); am_it != am_end; ++am_it) {
			const Atom& first_atom = *am_it->first;
			const Atom& second_atom = *am_it->second;

			symMappings[mapping_offs + molGraph->getAtomIndex(first_atom)] = molGraph->getAtomIndex(second_atom);

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
				symMappings[mapping_offs + molGraph->getAtomIndex(*nbrHydrogens1[i])] = molGraph->getAtomIndex(*nbrHydrogens2[i]);
		}

		if (keep_mapping)
			mapping_offs += numAtoms;
	}

	symMappings.resize(mapping_offs);
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

void ConfGen::FragmentConformerGenerator::allocVectorArray(ConfData& conf_data)
{
	conf_data.second = vecArrayCache.get();
}
