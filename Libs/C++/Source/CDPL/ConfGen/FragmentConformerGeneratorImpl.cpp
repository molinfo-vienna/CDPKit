/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorImpl.cpp 
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

#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"

#include "FragmentConformerGeneratorImpl.hpp"


namespace
{

	const std::size_t MAX_CONF_DATA_CACHE_SIZE     = 5000;
	const std::size_t MAX_NUM_STRUCTURE_GEN_TRIALS = 10;
}


using namespace CDPL;



ConfGen::FragmentConformerGeneratorImpl::FragmentConformerGeneratorImpl(): 
	confDataCache(MAX_CONF_DATA_CACHE_SIZE),
	energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
	using namespace Chem;

    dgStructGen.getSettings().excludeHydrogens(true);
    dgStructGen.getSettings().regardAtomConfiguration(true);
    dgStructGen.getSettings().regardBondConfiguration(true);
	dgStructGen.getSettings().enablePlanarityConstraints(true);

	hCoordsGen.undefinedOnly(true);
	hCoordsGen.setAtom3DCoordinatesCheckFunction(boost::bind(&FragmentConformerGeneratorImpl::has3DCoordinates, this, _1));

	symMappingSearch.includeIdentityMapping(false);
	symMappingSearch.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | 
										  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY |
										  AtomPropertyFlag::EXPLICIT_BOND_COUNT | AtomPropertyFlag::HYBRIDIZATION_STATE);
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentConformerGeneratorImpl::getSettings()
{
	return settings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentConformerGeneratorImpl::getSettings() const
{
	return settings;
}

void ConfGen::FragmentConformerGeneratorImpl::setAbortCallback(const CallbackFunction& func)
{
	abortCallback = func;
}

const ConfGen::CallbackFunction& ConfGen::FragmentConformerGeneratorImpl::getAbortCallback() const
{
	return abortCallback;
}

void ConfGen::FragmentConformerGeneratorImpl::setTimeoutCallback(const CallbackFunction& func)
{
	timeoutCallback = func;
}

const ConfGen::CallbackFunction& ConfGen::FragmentConformerGeneratorImpl::getTimeoutCallback() const
{
	return abortCallback;
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type) 
{
	if (!init(molgraph))
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
		return generateFlexibleRingConformers();
	
	return generateSingleConformer();
}

std::size_t ConfGen::FragmentConformerGeneratorImpl::getNumConformers() const
{
	return outputConfs.size();
}

ConfGen::ConformerData& ConfGen::FragmentConformerGeneratorImpl::getConformer(std::size_t idx)
{
	return *outputConfs[idx];
}

ConfGen::FragmentConformerGeneratorImpl::ConstConformerIterator ConfGen::FragmentConformerGeneratorImpl::getConformersBegin() const
{
    return outputConfs.begin();
}

ConfGen::FragmentConformerGeneratorImpl::ConstConformerIterator ConfGen::FragmentConformerGeneratorImpl::getConformersEnd() const
{
    return outputConfs.end();
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateSingleConformer()
{
	dgStructGen.getSettings().setBoxSize(ordHDepleteAtomMask.count() * 2);

	ConformerDataPtr conf_data = allocConformerData();
	unsigned int ret_code = generateRandomConformer(*conf_data);
		
	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	outputConfs.push_back(conf_data);

	if (abortCallback && abortCallback())
		return ReturnCode::ABORTED;

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateFlexibleRingConformers()
{
	dgStructGen.getSettings().setBoxSize(ordHDepleteAtomMask.count());

	getRingAtomIndices();
	getSymmetryMappings();

	std::size_t num_conf_samples = 0;
	const FragmentConformerGeneratorSettings::RingFragmentSettings* rsys_settings = 0;

	if (containsFragmentWithMinSize(*getSSSR(*molGraph), settings.getMinMacrocycleSize())) {
		rsys_settings = &settings.getMacrocycleSettings();
		num_conf_samples = calcNumMacrocyclicRingSystemConfSamples();

	} else {
		rsys_settings = &settings.getSmallRingSystemSettings();
		num_conf_samples = calcNumSmallRingSystemConfSamples();
	}

	num_conf_samples = std::max(rsys_settings->getMinNumSampledConformers(), std::min(rsys_settings->getMaxNumSampledConformers(), num_conf_samples));

	std::size_t timeout = rsys_settings->getTimeout();
	double e_window = rsys_settings->getEnergyWindow();
	double min_energy = 0.0;
	unsigned int ret_code = ReturnCode::SUCCESS;

	for (std::size_t i = 0; i < num_conf_samples; i++) {
		if (timedout(timeout)) {
			ret_code = ReturnCode::TIMEOUT_EXCEEDED;
			break;
		}

		if (abortCallback && abortCallback())
			return ReturnCode::ABORTED;

		ConformerDataPtr conf_data = allocConformerData();

		if (generateRandomConformer(*conf_data) != ReturnCode::SUCCESS) 
			continue;

		double energy = conf_data->getEnergy();

		if (workingConfs.empty())
			min_energy = energy;

		else if (energy > (min_energy + e_window))
			continue;

		if (energy < min_energy)
			min_energy = energy;

		workingConfs.push_back(conf_data);
	}

	if (workingConfs.empty()) {
		if (ret_code != ReturnCode::SUCCESS)
			return ret_code;

		return ReturnCode::MAX_NUM_TRIALS_EXCEEDED;
	}

	std::sort(workingConfs.begin(), workingConfs.end(), 
			  boost::bind(std::less<double>(), boost::bind(&ConformerData::getEnergy, _1), boost::bind(&ConformerData::getEnergy, _2)));

	double max_energy = min_energy + e_window;
	double rmsd = rsys_settings->getMinRMSD();
	std::size_t max_num_out_confs = rsys_settings->getMaxNumOutputConformers();

	for (ConformerDataArray::iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
		ConformerDataPtr& conf_data = *it;
		Math::Vector3DArray& conf_coords = *conf_data;

		if (outputConfs.size() >= max_num_out_confs) 
			return ret_code;

		if (conf_data->getEnergy() > max_energy)
			return ret_code;

		if (!checkRMSD(conf_coords, rmsd)) {
			conf_data.reset();
			continue;
		}

		outputConfs.push_back(conf_data);

		for (std::size_t mapping_offs = 0, mappings_size = symMappings.size(); 
			 mapping_offs < mappings_size && outputConfs.size() < max_num_out_confs; mapping_offs += numAtoms) {

			ConformerDataPtr sym_conf_data = allocConformerData();
			Math::Vector3DArray& sym_conf_coords = *sym_conf_data;

			sym_conf_coords.resize(numAtoms);

			for (std::size_t k = 0; k < numAtoms; k++)
				sym_conf_coords[symMappings[mapping_offs + k]].assign(conf_coords[k]);

			if (!checkRMSD(sym_conf_coords, rmsd))
				continue;

			sym_conf_data->setEnergy(conf_data->getEnergy());

			outputConfs.push_back(sym_conf_data);
		}
	}

	return ret_code;
}

bool ConfGen::FragmentConformerGeneratorImpl::init(const Chem::MolecularGraph& molgraph)
{
	timer.start();

	molGraph = &molgraph;
	numAtoms = molgraph.getNumAtoms();

	outputConfs.clear();
	workingConfs.clear();
	ringAtomCoords.clear();

	mmff94Parameterizer.strictParameterization(settings.strictForceFieldParameterization());

	try {
		if (parameterizeMMFF94Interactions(molgraph, mmff94Parameterizer, mmff94Data, settings.getForceFieldType()) != ReturnCode::SUCCESS)
			return false;

	} catch (const ForceField::Error&) {
		return false;
	}

	dgStructGen.setup(molgraph, mmff94Data);

	ordHDepleteAtomMask.resize(numAtoms);
	ordHDepleteAtomMask = dgStructGen.getExcludedHydrogenMask();
	ordHDepleteAtomMask.flip();

	hCoordsGen.setup(molgraph);

	mmff94EnergyCalc.setup(mmff94Data);
	mmff94GradientCalc.setup(mmff94Data, numAtoms);

    gradient.resize(numAtoms);

	return true;
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateRandomConformer(ConformerData& conf_data)
{
	std::size_t max_ref_iters = settings.getMaxNumRefinementIterations();
	double stop_grad = settings.getRefinementStopGradient();

	for (std::size_t i = 0; i < MAX_NUM_STRUCTURE_GEN_TRIALS; i++) {
		if (!dgStructGen.generate(conf_data)) 
			continue;

		hCoordsGen.generate(conf_data, false);
		energyMinimizer.setup(conf_data.getData(), gradient);

		double energy = 0.0;		

		for (std::size_t j = 0; max_ref_iters == 0 || j < max_ref_iters; j++) {
			if (energyMinimizer.iterate(energy, conf_data.getData(), gradient) != BFGSMinimizer::SUCCESS) {
				if ((boost::math::isnan)(energy))
					return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

				break;
			}

			if ((boost::math::isnan)(energy))
				return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;
		
			if (stop_grad >= 0.0 && energyMinimizer.getGradientNorm() <= stop_grad)
				break;
		}

		if (!dgStructGen.checkAtomConfigurations(conf_data)) 
			continue;
		
		if (!dgStructGen.checkBondConfigurations(conf_data)) 
			continue;

		conf_data.setEnergy(energy);

		return ReturnCode::SUCCESS;
	}

	return ReturnCode::MAX_NUM_TRIALS_EXCEEDED;
}

bool ConfGen::FragmentConformerGeneratorImpl::checkRMSD(const Math::Vector3DArray& conf_coords, double min_rmsd)
{
	ConformerDataPtr conf_ra_coords_ptr = getRingAtomCoordinates(conf_coords);
	Math::Vector3DArray& conf_ra_coords = *conf_ra_coords_ptr;
	Math::Matrix4D conf_xform;

	for (ConformerDataArray::const_reverse_iterator it = ringAtomCoords.rbegin(), end = ringAtomCoords.rend(); it != end; ++it) {
		const Math::Vector3DArray& prev_conf_ra_coords = **it;

		if (!alignmentCalc.calculate(prev_conf_ra_coords, conf_ra_coords, false))
			return false;

		conf_xform.assign(alignmentCalc.getTransform());

		double rmsd = calcRMSD(prev_conf_ra_coords, conf_ra_coords, conf_xform);

		if (rmsd < min_rmsd)
			return false;
	}

	ringAtomCoords.push_back(conf_ra_coords_ptr);
	return true;
}

bool ConfGen::FragmentConformerGeneratorImpl::has3DCoordinates(const Chem::Atom& atom) const
{
	return ordHDepleteAtomMask.test(molGraph->getAtomIndex(atom));
}

ConfGen::FragmentConformerGeneratorImpl::ConformerDataPtr 
ConfGen::FragmentConformerGeneratorImpl::getRingAtomCoordinates(const Math::Vector3DArray& conf_coords)
{
	ConformerDataPtr ra_coords_ptr = allocConformerData();
	Math::Vector3DArray& ra_coords = *ra_coords_ptr;
	Math::Vector3DArray::StorageType& ra_coords_data = ra_coords.getData();
	Math::Vector3D ctr;
	std::size_t num_ring_atoms = ringAtomIndices.size();

	ra_coords.resize(num_ring_atoms);

	for (std::size_t i = 0; i < num_ring_atoms; i++) {
		const Math::Vector3D& pos = conf_coords[ringAtomIndices[i]];

		ctr.plusAssign(pos);
		ra_coords_data[i].assign(pos);
	}

	ctr /= num_ring_atoms;

	for (Math::Vector3DArray::ElementIterator it = ra_coords.getElementsBegin(), end = ra_coords.getElementsEnd(); it != end; ++it)
		it->minusAssign(ctr);

	return ra_coords_ptr;
}

void ConfGen::FragmentConformerGeneratorImpl::getRingAtomIndices()
{
	using namespace Chem;

	ringAtomIndices.clear();

	for (std::size_t i = 0; i < numAtoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		if (getRingFlag(atom) && getRingBondCount(atom, *molGraph) >= 2)
			ringAtomIndices.push_back(i);
	}
}

void ConfGen::FragmentConformerGeneratorImpl::getSymmetryMappings()
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

void ConfGen::FragmentConformerGeneratorImpl::getNeighborHydrogens(const Chem::Atom& atom, AtomList& nbr_list) const
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

std::size_t ConfGen::FragmentConformerGeneratorImpl::calcNumSmallRingSystemConfSamples() const
{
	using namespace Chem;

	double ring_flex_sum = 0.0;
	const FragmentList& sssr = *getSSSR(*molGraph);

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;

		if (getNumRotatableRingBonds(ring) > 0)
			ring_flex_sum += double(ring.getNumAtoms()) / 6;
	}

	return (ring_flex_sum * settings.getSmallRingSystemSamplingFactor());
}

std::size_t ConfGen::FragmentConformerGeneratorImpl::calcNumMacrocyclicRingSystemConfSamples() const
{
	return std::pow(2, getNumRotatableRingBonds(*molGraph));
}

std::size_t ConfGen::FragmentConformerGeneratorImpl::getNumRotatableRingBonds(const Chem::MolecularGraph& molgraph) const
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

bool ConfGen::FragmentConformerGeneratorImpl::timedout(std::size_t timeout) const
{
	if (timeoutCallback && timeoutCallback())
		return true;

	if (timeout == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(timeout) * 1000000));
}

ConfGen::FragmentConformerGeneratorImpl::ConformerDataPtr ConfGen::FragmentConformerGeneratorImpl::allocConformerData()
{
	ConformerDataPtr conf_data = confDataCache.get();

	conf_data->setEnergy(0.0);

	return conf_data;
}
