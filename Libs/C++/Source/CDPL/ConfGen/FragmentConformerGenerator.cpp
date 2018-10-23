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
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_STRUCTURE_GEN_TRIALS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_MINIMIZATION_STEPS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_MAX_NUM_RING_CONFORMERS;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_TIMEOUT;
const std::size_t  ConfGen::FragmentConformerGenerator::DEF_RING_CONF_RETRIAL_FACTOR;
const double       ConfGen::FragmentConformerGenerator::DEF_MINIMIZATION_STOP_GRADIENT_NORM = 0.2;
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

void ConfGen::FragmentConformerGenerator::generate(const Chem::MolecularGraph& molgraph, 
												   const ForceField::MMFF94InteractionData& ia_data, unsigned int frag_type) 
{
	init(molgraph, ia_data);

	if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
		generateFlexibleRingConformers();
	else
		generateSingleConformer();
}

std::size_t ConfGen::FragmentConformerGenerator::getNumConformers() const
{
	return outputConfs.size();
}

const Math::Vector3DArray& ConfGen::FragmentConformerGenerator::getCoordinates(std::size_t conf_idx) const
{
	if (conf_idx >= outputConfs.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return *outputConfs[conf_idx].get<1>();
}

Math::Vector3DArray& ConfGen::FragmentConformerGenerator::getCoordinates(std::size_t conf_idx)
{
	if (conf_idx >= outputConfs.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return *outputConfs[conf_idx].get<1>();
}

double ConfGen::FragmentConformerGenerator::getEnergy(std::size_t conf_idx) const
{
	if (conf_idx >= outputConfs.size())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return outputConfs[conf_idx].get<0>();
}

void ConfGen::FragmentConformerGenerator::generateSingleConformer()
{
	Conformation conf;

	if (reuseExistingCoords && extractExistingCoordinates(conf)) {
		workingConfs.insert(ConformerList::value_type(0.0, conf));
		outputConfs.push_back(conf);
		return;
	}

	rawCoordsGenerator.setup(*molGraph, *mmff94Interactions);
	rawCoordsGenerator.enablePlanarityConstraints(true);

	mmff94EnergyCalc.setup(*mmff94Interactions);
	mmff94GradientCalc.setup(*mmff94Interactions, numAtoms);
    gradient.resize(numAtoms);

	if (!generateRandomConformer(conf))
		return;

	workingConfs.insert(ConformerList::value_type(0.0, conf));
	outputConfs.push_back(conf);
}

void ConfGen::FragmentConformerGenerator::generateFlexibleRingConformers()
{
	rawCoordsGenerator.setup(*molGraph, *mmff94Interactions);
	rawCoordsGenerator.enablePlanarityConstraints(false);

	hCoordsGenerator.setAtom3DCoordinatesCheckFunction(boost::bind(&FragmentConformerGenerator::has3DCoordinates, this, _1));

	heavyAtomMask = rawCoordsGenerator.getExcludedHydrogenMask();
	heavyAtomMask.flip();
	
	mmff94InteractionsXH.clear();
	filterInteractions(*mmff94Interactions, mmff94InteractionsXH, heavyAtomMask);

    gradient.resize(numAtoms);

	mmff94GradientCalc.setup(mmff94InteractionsXH, numAtoms);
	mmff94EnergyCalc.setup(mmff94InteractionsXH);

	getHeavyAtomIndices();

	rawCoordsGenerator.setBoxSize(std::sqrt(double(heavyAtomMask.count())) * 2.0);

	double e_window = eWindow;
	std::size_t num_retrials = 0;
	std::size_t num_rot_bonds = getNumRotatableRingBonds();

	if (isMacrocyclicRingSystem()) {
		e_window = num_rot_bonds * e_window;
		num_retrials = std::pow(2, num_rot_bonds);

	} else {
		num_retrials = num_rot_bonds * ringConfRetrialFact;
	}

	num_retrials = std::min(maxNumRingConfs * 4, num_retrials); 

	for (std::size_t i = 0; i < num_retrials; i++) {
		Conformation conf;

		if (!generateRandomConformer(conf))
			break;

		if (!checkEnergyWindow(conf, e_window))
			continue;

		if (checkRMSD(conf))
			addRingConformer(conf, e_window);
	}

	for (ConformerList::const_iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		const Conformation& conf = it->second;

		hCoordsGenerator.generate(*molGraph, *conf.get<1>(), false);
		outputConfs.push_back(conf);
	}
}

void ConfGen::FragmentConformerGenerator::init(const Chem::MolecularGraph& molgraph, 
											   const ForceField::MMFF94InteractionData& ia_data)
{
	for (ConformerList::const_iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		freeCoordinatesArray(it->second.get<1>());
		freeCoordinatesArray(it->second.get<2>());
	}

	outputConfs.clear();
	workingConfs.clear();
	timer.start();

	molGraph = &molgraph;
	mmff94Interactions = &ia_data;
	numAtoms = molgraph.getNumAtoms();
}

bool ConfGen::FragmentConformerGenerator::extractExistingCoordinates(Conformation& conf)
{
	using namespace Chem;

	conf.get<1>() = allocCoordinatesArray();
	Math::Vector3DArray& coords = *conf.get<1>();
	bool have_h_atom_coords = true;

	for (std::size_t i = 0; i < numAtoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		try {
			coords[i] = get3DCoordinates(atom);

		} catch (const Base::ItemNotFound& e) {
			if (getType(atom) != AtomType::H) {
				freeCoordinatesArray(conf.get<1>());
				return false;
			} 
			
			have_h_atom_coords = false;

		} catch (const std::exception& e) {
			freeCoordinatesArray(conf.get<1>());
			throw e;
		}
	}

	if (!have_h_atom_coords) { 
		hCoordsGenerator.setAtom3DCoordinatesCheckFunction(&Chem::has3DCoordinates);
		hCoordsGenerator.generate(*molGraph, coords, false);
	}

	return true;
}

bool ConfGen::FragmentConformerGenerator::generateRandomConformer(Conformation& conf)
{
	if (timeoutExceeded())
		return false;

	conf.get<1>() = allocCoordinatesArray();

	Math::Vector3DArray& coords = *conf.get<1>();
	std::size_t i = 0;

	for ( ; i < maxNumStructGenTrials; i++) {
		if (!rawCoordsGenerator.generate(coords)) 
			continue;
		
		energyMinimizer.setup(coords, gradient);

		for (std::size_t j = 0; maxNumMinSteps == 0 || j < maxNumMinSteps; j++) {
			if (energyMinimizer.iterate(conf.get<0>(), coords, gradient) != BFGSMinimizer::SUCCESS)
				break;

			if (minStopGradNorm >= 0.0 && energyMinimizer.getGradientNorm() <= minStopGradNorm)
				break;
		}

		if (!rawCoordsGenerator.checkAtomConfigurations(coords)) 
			continue;
		
		if (rawCoordsGenerator.checkBondConfigurations(coords)) 
			break;
	}

	if (i < maxNumStructGenTrials) 
		return true;
	
	freeCoordinatesArray(conf.get<1>());
	return false;
}

bool ConfGen::FragmentConformerGenerator::checkRMSD(Conformation& conf)
{
	if (workingConfs.empty()) 
		return true;

	conf.get<2>() = allocCoordinatesArray(false);

	Math::Vector3DArray& new_conf_ha_coords = *conf.get<2>();

	getHeavyAtomCoordinates(*conf.get<1>(), new_conf_ha_coords);

	Math::Matrix4D conf_xform;
	bool rmsd_ok = true;

	for (ConformerList::iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		if (!it->second.get<2>()) {
			it->second.get<2>() = allocCoordinatesArray(false);

			getHeavyAtomCoordinates(*it->second.get<1>(), *it->second.get<2>());
		}

		const Math::Vector3DArray& conf_ha_coords = *it->second.get<2>();

		if (!alignmentCalc.calculate(conf_ha_coords, new_conf_ha_coords, false)) {
			rmsd_ok = false;
			break;
		}

		conf_xform.assign(alignmentCalc.getTransform());

		double rmsd = calcRMSD(conf_ha_coords, new_conf_ha_coords, conf_xform);

		if (rmsd < minRMSD) {
			rmsd_ok = false;
			break;
		}
	}

	if (!rmsd_ok) {
		freeCoordinatesArray(conf.get<1>());
		freeCoordinatesArray(conf.get<2>());

		return false;
	}

	return true;
}

bool ConfGen::FragmentConformerGenerator::checkEnergyWindow(const Conformation& conf, double e_window)
{
	if (workingConfs.empty()) 
		return true;

	double energy = conf.get<0>();

	if ((workingConfs.size() >= maxNumRingConfs && workingConfs.rbegin()->first <= energy) ||
		energy > (workingConfs.begin()->first + e_window)) {

		freeCoordinatesArray(conf.get<1>());
		freeCoordinatesArray(conf.get<2>());

		return false;
	}

	return true;
}

void ConfGen::FragmentConformerGenerator::addRingConformer(const Conformation& conf, double e_window)
{
	double energy = conf.get<0>();

	workingConfs.insert(ConformerList::value_type(energy, conf));

	double max_energy = workingConfs.begin()->first + e_window;

	while (!workingConfs.empty()) {
		ConformerList::reverse_iterator last = workingConfs.rbegin();

		if (workingConfs.size() > maxNumRingConfs || last->first > max_energy) {
			freeCoordinatesArray(last->second.get<1>());
			freeCoordinatesArray(last->second.get<2>());

			workingConfs.erase(--last.base());
			continue;
		} 

		break;
	}
}

bool ConfGen::FragmentConformerGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return heavyAtomMask.test(molGraph->getAtomIndex(atom));
}

void ConfGen::FragmentConformerGenerator::getHeavyAtomCoordinates(const Math::Vector3DArray& coords, Math::Vector3DArray& hvy_atom_coords) const
{
	Math::Vector3D ctr;

	hvy_atom_coords.clear();

	for (IndexList::const_iterator it = heavyAtomIndices.begin(), end = heavyAtomIndices.end(); it != end; ++it) {
		const Math::Vector3D& pos = coords[*it];

		ctr += pos;

		hvy_atom_coords.addElement(pos);
	}

	ctr /= heavyAtomIndices.size();

	for (Math::Vector3DArray::ElementIterator it = hvy_atom_coords.getElementsBegin(), end = hvy_atom_coords.getElementsEnd(); it != end; ++it)
		*it -= ctr;
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

bool ConfGen::FragmentConformerGenerator::inAscendingEnergyOrder(const Conformation& conf1, const Conformation& conf2)
{
	return (conf1.get<0>() <= conf2.get<0>());
}

Math::Vector3DArray::SharedPointer ConfGen::FragmentConformerGenerator::allocCoordinatesArray(bool resize)
{
 	Math::Vector3DArray::SharedPointer coords_ptr;

	if (!coordsArrayCache.empty()) {
		coords_ptr = coordsArrayCache.back();
		coordsArrayCache.pop_back();

	} else

		coords_ptr.reset(new Math::Vector3DArray());

	if (resize)
		coords_ptr->resize(numAtoms);

	return coords_ptr;
}

void ConfGen::FragmentConformerGenerator::freeCoordinatesArray(const Math::Vector3DArray::SharedPointer& coords_ptr)
{
	if (coords_ptr)
		coordsArrayCache.push_back(coords_ptr);
}
