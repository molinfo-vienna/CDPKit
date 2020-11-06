/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorImpl.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <limits>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions.hpp>

#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/BondFunctions.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"

#include "FragmentConformerGeneratorImpl.hpp"
#include "UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

	bool compareConformerEnergy(const ConfGen::ConformerData::SharedPointer& conf_data1, 
								const ConfGen::ConformerData::SharedPointer& conf_data2)
	{
		return (conf_data1->getEnergy() < conf_data2->getEnergy());
	} 

	const std::size_t MAX_CONF_DATA_CACHE_SIZE            = 10000;
	const std::size_t MAX_NUM_STRUCTURE_GEN_TRIALS        = 10;
	const std::size_t MAX_NUM_SYM_MAPPINGS                = 64;
	const std::size_t CONF_RMSD_TEST_TIMEOUT_CHECK_THRESH = 1000;
}


ConfGen::FragmentConformerGeneratorImpl::FragmentConformerGeneratorImpl(): 
	confDataCache(MAX_CONF_DATA_CACHE_SIZE),
	energyMinimizer(boost::ref(mmff94GradientCalc), boost::ref(mmff94GradientCalc)),
	settings(FragmentConformerGeneratorSettings::DEFAULT)
{
	using namespace Chem;

	DGStructureGeneratorSettings& dg_settings = dgStructureGen.getSettings();

    dg_settings.excludeHydrogens(true);
    dg_settings.regardAtomConfiguration(true);
    dg_settings.regardBondConfiguration(true);
	dg_settings.enablePlanarityConstraints(true);

	hCoordsGen.undefinedOnly(true);
	hCoordsGen.setAtom3DCoordinatesCheckFunction(boost::bind(&FragmentConformerGeneratorImpl::has3DCoordinates, this, _1));

	symMappingSearch.includeIdentityMapping(false);
	symMappingSearch.setMaxNumMappings(MAX_NUM_SYM_MAPPINGS);
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

void ConfGen::FragmentConformerGeneratorImpl::setLogMessageCallback(const LogMessageCallbackFunction& func)
{
	logCallback = func;
}

const ConfGen::LogMessageCallbackFunction& ConfGen::FragmentConformerGeneratorImpl::getLogMessageCallback() const
{
	return logCallback;
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type) 
{
	init(molgraph);

	unsigned int ret_code = ReturnCode::SUCCESS;

	if (numAtoms == 0) {
		if (logCallback)
			logCallback("Input fragment without atoms!\n");

	} else {
		if (!setupForceField())
			ret_code = ReturnCode::FORCEFIELD_SETUP_FAILED;

		else {
			switch (frag_type) {

				case FragmentType::FLEXIBLE_RING_SYSTEM:
					ret_code = generateFlexibleRingConformers();
					break;
	
				case FragmentType::CHAIN:
					ret_code = generateChainConformer();
					break;

				default:
					ret_code = generateRigidRingConformer();
					break;
			}
		}
	}

	if (logCallback) {
		logCallback("Conformer generation finished with return code " + returnCodeToString(ret_code) + '\n');
		logCallback("Processing time: " + timer.format(3, "%w") + "s\n");
		logCallback("Num. output conformers: " + boost::lexical_cast<std::string>(outputConfs.size()) + '\n');

		if (outputConfs.size() > 1) {
			double min_e = std::numeric_limits<double>::max(), max_e = -std::numeric_limits<double>::max();

			for (ConformerDataArray::iterator it = outputConfs.begin(), end = outputConfs.end(); it != end; ++it) {
				max_e = std::max(max_e, (*it)->getEnergy());
				min_e = std::min(min_e, (*it)->getEnergy());
			}

			logCallback("Energy range: " + (boost::format("%.4f") % (max_e - min_e)).str() + '\n');
		}
	}

	return ret_code;
}

void ConfGen::FragmentConformerGeneratorImpl::setConformers(Chem::MolecularGraph& molgraph) const
{
	ConfGen::setConformers(molgraph, outputConfs);
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

bool ConfGen::FragmentConformerGeneratorImpl::generateConformerFromInputCoordinates(const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	if (!setupForceField())
		return false;

	return generateConformerFromInputCoordinates(outputConfs);
}

void ConfGen::FragmentConformerGeneratorImpl::init(const Chem::MolecularGraph& molgraph)
{
	timer.start();

	molGraph = &molgraph;
	numAtoms = molgraph.getNumAtoms();

	outputConfs.clear();
	workingConfs.clear();
	ringAtomCoords.clear();
}

bool ConfGen::FragmentConformerGeneratorImpl::generateConformerFromInputCoordinates(ConformerDataArray& conf_array)
{
	using namespace Chem;

	ConformerData::SharedPointer ipt_coords = allocConformerData();

	ipt_coords->resize(numAtoms);

	coreAtomMask.resize(numAtoms);
	coreAtomMask.set();

	Math::Vector3DArray::StorageType& ipt_coords_data = ipt_coords->getData();
	bool coords_compl = true;

	for (std::size_t i = 0; i < numAtoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		try {
			ipt_coords_data[i].assign(get3DCoordinates(atom));

		} catch (const Base::ItemNotFound&) {
			if (getType(atom) != AtomType::H)
				return false;

			coreAtomMask.reset(i);
			coords_compl = false;
		}
	} 

	if (!coords_compl) {
		hCoordsGen.setup(*molGraph);
		mmff94GradientCalc.setFixedAtomMask(coreAtomMask);

		if (logCallback)
			logCallback("Reusing fragment input cooordinates, generating missing hydrogen coordinates\n");

		if (!generateHydrogenCoordsAndMinimize(*ipt_coords)) {
			if (logCallback)
				logCallback("Generation of hydrogen coordinates failed!\n");

			return false;
		}

	} else {
		if (logCallback)
			logCallback("Reusing fragment input cooordinates\n");

		ipt_coords->setEnergy(mmff94GradientCalc(ipt_coords_data));
	}

	conf_array.push_back(ipt_coords);

	return true;
}

bool ConfGen::FragmentConformerGeneratorImpl::setupForceField()
{
	try {
		if (parameterizeMMFF94Interactions(*molGraph, mmff94Parameterizer, mmff94Data, settings.getForceFieldType(),
										   settings.strictForceFieldParameterization(), settings.getDielectricConstant(),
										   settings.getDistanceExponent()) != ReturnCode::SUCCESS) {

			if (logCallback)
				logCallback("Force field setup failed!\n");

			return false;
		}

	} catch (const ForceField::Error& e) {
		if (logCallback)
			logCallback("Force field setup failed: " + std::string(e.what()) + '\n');

		return false;
	}

	mmff94GradientCalc.setup(mmff94Data, numAtoms);
    energyGradient.resize(numAtoms);

	return true;
}

void ConfGen::FragmentConformerGeneratorImpl::setupRandomConformerGeneration(bool reg_stereo)
{
	dgStructureGen.getSettings().regardAtomConfiguration(reg_stereo);
	dgStructureGen.getSettings().regardBondConfiguration(reg_stereo);

	dgStructureGen.setup(*molGraph, mmff94Data);

	coreAtomMask = dgStructureGen.getExcludedHydrogenMask();
	coreAtomMask.flip();

	hCoordsGen.setup(*molGraph);

	mmff94GradientCalc.resetFixedAtomMask();
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateRigidRingConformer()
{
	if (!settings.preserveInputBondingGeometries() || !generateConformerFromInputCoordinates(outputConfs)) {
		if (logCallback)
			logCallback("Generating rigid ring system coordinates...\n");

		setupRandomConformerGeneration(true);
		dgStructureGen.getSettings().setBoxSize(coreAtomMask.count());

		ConformerData::SharedPointer conf_data = allocConformerData();
		unsigned int ret_code = generateRandomConformer(*conf_data);

		if (ret_code != ReturnCode::SUCCESS) {
			if (logCallback)
				logCallback("Could not generate any conformers!\n");

			return ret_code;
		}

		outputConfs.push_back(conf_data);
	}

	return invokeCallbacks();
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateChainConformer()
{
	if (settings.preserveInputBondingGeometries() && generateConformerFromInputCoordinates(outputConfs))
		return invokeCallbacks();

	if (logCallback)
		logCallback("Generating chain conformers...\n");

	setupRandomConformerGeneration(false);
	dgStructureGen.getSettings().setBoxSize(coreAtomMask.count() * 2);

	const FragmentConformerGeneratorSettings::FragmentSettings& chain_settings = settings.getChainSettings();

	std::size_t num_conf_samples = calcNumChainConfSamples();

	if (num_conf_samples == 0)
		num_conf_samples = 1;
	else
		num_conf_samples = std::max(chain_settings.getMinNumSampledConformers(), 
									std::min(chain_settings.getMaxNumSampledConformers(), num_conf_samples));

	if (logCallback)
		logCallback("Max. num. sampled conformers: " + boost::lexical_cast<std::string>(num_conf_samples) + '\n');

	std::size_t timeout = chain_settings.getTimeout();
	double min_energy = 0.0;
	unsigned int ret_code = ReturnCode::SUCCESS;
	ConformerData::SharedPointer conf_data;

	for (std::size_t i = 0; i < num_conf_samples; i++) {
		if ((ret_code = invokeCallbacks()) != ReturnCode::SUCCESS)
			return ret_code;

		if (timedout(timeout)) {
			ret_code = ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT;
			break;
		}

		if (!conf_data)
			conf_data = allocConformerData();

		if (generateRandomConformer(*conf_data) != ReturnCode::SUCCESS) 
			continue;
		
		double energy = conf_data->getEnergy();

		if (outputConfs.empty() || energy < min_energy)
			min_energy = energy;

		else continue;

		outputConfs.clear();
		outputConfs.push_back(conf_data);
		conf_data.reset();
	}

	if (outputConfs.empty()) {
		if (logCallback)
			logCallback("Could not generate any conformers!\n");

		return ReturnCode::FRAGMENT_CONF_GEN_FAILED;
	}

	return ret_code;
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateFlexibleRingConformers()
{
	if (settings.preserveInputBondingGeometries())
		generateConformerFromInputCoordinates(outputConfs);

	if (logCallback)
		logCallback("Generating flexible ring system conformers...\n");

	setupRandomConformerGeneration(true);
	dgStructureGen.getSettings().setBoxSize(coreAtomMask.count());

	getRingAtomIndices();
	getSymmetryMappings();

	const FragmentConformerGeneratorSettings::FragmentSettings* rsys_settings = 0;
	std::size_t num_conf_samples = calcNumMacrocyclicRingSystemConfSamples(); 

	if (num_conf_samples > 0) {
		rsys_settings = &settings.getMacrocycleSettings();

		if (logCallback)
			logCallback("Used settings: macrocycle\n");

	} else {
		rsys_settings = &settings.getSmallRingSystemSettings();
		num_conf_samples = calcNumSmallRingSystemConfSamples();

		if (logCallback)
			logCallback("Used settings: small ring system\n");
	}

	num_conf_samples = std::max(rsys_settings->getMinNumSampledConformers(), 
								std::min(rsys_settings->getMaxNumSampledConformers(), num_conf_samples));

	if (logCallback)
		logCallback("Max. num. sampled conformers: " + boost::lexical_cast<std::string>(num_conf_samples) + '\n');

	std::size_t timeout = rsys_settings->getTimeout();
	double e_window = rsys_settings->getEnergyWindow();
	double min_energy = 0.0;
	unsigned int ret_code = ReturnCode::SUCCESS;
	ConformerData::SharedPointer conf_data;

	for (std::size_t i = 0; i < num_conf_samples; i++) {
		if ((ret_code = invokeCallbacks()) != ReturnCode::SUCCESS)
			return ret_code;

		if (timedout(timeout)) {
			ret_code = ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT;
			break;
		}

		if (!conf_data)
			conf_data = allocConformerData();

		if (generateRandomConformer(*conf_data) != ReturnCode::SUCCESS) 
			continue;

		double energy = conf_data->getEnergy();

		if (workingConfs.empty() || energy < min_energy)
			min_energy = energy;

		else if (energy > (min_energy + e_window))
			continue;

		workingConfs.push_back(conf_data);
		conf_data.reset();
	}

	if (workingConfs.empty() && outputConfs.empty()) {
		if (logCallback)
			logCallback("Could not generate any conformers!\n");

		return ReturnCode::FRAGMENT_CONF_GEN_FAILED;
	}

	if (!outputConfs.empty()) {
		workingConfs.push_back(outputConfs.front());
		workingConfs.front().swap(workingConfs.back());
		outputConfs.clear();
		
		std::sort(workingConfs.begin() + 1, workingConfs.end(), &compareConformerEnergy);

	} else
		std::sort(workingConfs.begin(), workingConfs.end(), &compareConformerEnergy);

	std::size_t max_num_out_confs = rsys_settings->getMaxNumOutputConformers();
	double rmsd = rsys_settings->getMinRMSD();
	double max_energy = min_energy + e_window;

	if (logCallback) 
		logCallback("Performing output conformer selection (min. RMSD: " + (boost::format("%.4f") % rmsd).str() + 
					", num. top. sym. mappings: " + boost::lexical_cast<std::string>(symMappings.size() / numAtoms) + ")...\n");
	
	for (ConformerDataArray::iterator it = workingConfs.begin(), end = workingConfs.end(); 
		 it != end && outputConfs.size() < max_num_out_confs; ++it) {

		ConformerData::SharedPointer& conf_data = *it;

		if (!outputConfs.empty() && conf_data->getEnergy() > max_energy)
			break;

		if (checkRMSD(*conf_data, rmsd)) 
			outputConfs.push_back(conf_data);
			
		addSymmetryMappedConformers(*conf_data, rmsd, max_num_out_confs);
		addMirroredConformer(*conf_data, rmsd, max_num_out_confs);

		if ((outputConfs.size() * symMappings.size() / numAtoms) > CONF_RMSD_TEST_TIMEOUT_CHECK_THRESH) {
			if ((ret_code = invokeCallbacks()) != ReturnCode::SUCCESS)
				return ret_code;

			if (timedout(timeout))
				return ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT;
		}
	}

	return ret_code;
}

void ConfGen::FragmentConformerGeneratorImpl::addSymmetryMappedConformers(const ConformerData& conf_data, double rmsd, std::size_t max_num_out_confs)
{
	const Math::Vector3DArray::StorageType& conf_coords_data = conf_data.getData();

	for (std::size_t mapping_offs = 0, mappings_size = symMappings.size(); 
		 mapping_offs < mappings_size && outputConfs.size() < max_num_out_confs; mapping_offs += numAtoms) {

		ConformerData::SharedPointer mpd_conf_data = allocConformerData();
		Math::Vector3DArray::StorageType& mpd_conf_coords_data = mpd_conf_data->getData();

		mpd_conf_data->resize(numAtoms);

		for (std::size_t i = 0; i < numAtoms; i++)
			mpd_conf_coords_data[symMappings[mapping_offs + i]].assign(conf_coords_data[i]);

		if (checkRMSD(*mpd_conf_data, rmsd)) {
			mpd_conf_data->setEnergy(conf_data.getEnergy());

			outputConfs.push_back(mpd_conf_data);
		}

		addMirroredConformer(*mpd_conf_data, rmsd, max_num_out_confs);
	}
}

void ConfGen::FragmentConformerGeneratorImpl::addMirroredConformer(const ConformerData& conf_data, double rmsd, std::size_t max_num_out_confs)
{
	if (dgStructureGen.getNumAtomStereoCenters() != 0 || outputConfs.size() >= max_num_out_confs)
		return;

	ConformerData::SharedPointer mirr_conf_data = allocConformerData();
	Math::Vector3DArray::StorageType& mirr_conf_coords_data = mirr_conf_data->getData();
	const Math::Vector3DArray::StorageType& conf_coords_data = conf_data.getData();

	mirr_conf_data->resize(numAtoms);

	for (std::size_t i = 0; i < numAtoms; i++) {
		Math::Vector3D::Pointer mirr_atom_pos = mirr_conf_coords_data[i].getData();
		Math::Vector3D::ConstPointer orig_atom_pos = conf_coords_data[i].getData();

		mirr_atom_pos[0] = orig_atom_pos[0];
		mirr_atom_pos[1] = orig_atom_pos[1];
		mirr_atom_pos[2] = -orig_atom_pos[2];
	}

	if (!checkRMSD(*mirr_conf_data, rmsd))
		return;

	mirr_conf_data->setEnergy(conf_data.getEnergy());

	outputConfs.push_back(mirr_conf_data);
}

bool ConfGen::FragmentConformerGeneratorImpl::generateHydrogenCoordsAndMinimize(ConformerData& conf_data)
{
	std::size_t max_ref_iters = settings.getMaxNumRefinementIterations();
	double stop_grad = settings.getRefinementStopGradient();
	Math::Vector3DArray::StorageType& conf_coords_data = conf_data.getData();

	hCoordsGen.generate(conf_data, false);
	energyMinimizer.setup(conf_coords_data, energyGradient);

	double energy = 0.0;		

	for (std::size_t i = 0; max_ref_iters == 0 || i < max_ref_iters; i++) {
		if (energyMinimizer.iterate(energy, conf_coords_data, energyGradient) != BFGSMinimizer::SUCCESS) {
			if ((boost::math::isnan)(energy)) 
				return false;

			break;
		}
	
		if ((boost::math::isnan)(energy)) 
			return false;

		if (stop_grad >= 0.0 && energyMinimizer.getGradientNorm() <= stop_grad)
			break;
	}

	conf_data.setEnergy(energy);

	return true;
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::generateRandomConformer(ConformerData& conf_data)
{
	for (std::size_t i = 0; i < MAX_NUM_STRUCTURE_GEN_TRIALS; i++) {
		if (!dgStructureGen.generate(conf_data)) 
			continue;
		
		if (!generateHydrogenCoordsAndMinimize(conf_data))
			return ReturnCode::FORCEFIELD_MINIMIZATION_FAILED;

		if (!dgStructureGen.checkAtomConfigurations(conf_data)) 
			continue;

		if (!dgStructureGen.checkBondConfigurations(conf_data)) 
			continue;

		return ReturnCode::SUCCESS;
	}

	return ReturnCode::FRAGMENT_CONF_GEN_FAILED;
}

bool ConfGen::FragmentConformerGeneratorImpl::checkRMSD(const Math::Vector3DArray& conf_coords, double min_rmsd)
{
	ConformerData::SharedPointer conf_ra_coords_ptr = getRingAtomCoordinates(conf_coords);
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
	return coreAtomMask.test(molGraph->getAtomIndex(atom));
}

ConfGen::ConformerData::SharedPointer 
ConfGen::FragmentConformerGeneratorImpl::getRingAtomCoordinates(const Math::Vector3DArray& conf_coords)
{
	ConformerData::SharedPointer ra_coords_ptr = allocConformerData();
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

		if (coreAtomMask.test(molGraph->getAtomIndex(bond.getBegin())) && coreAtomMask.test(molGraph->getAtomIndex(bond.getEnd())))
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

std::size_t ConfGen::FragmentConformerGeneratorImpl::calcNumChainConfSamples() const
{
	using namespace Chem;

	std::size_t count = 0;

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) 
		if (isRotatableBond(*it, *molGraph, false))
			count++;

	return std::pow(3, count);
}

std::size_t ConfGen::FragmentConformerGeneratorImpl::calcNumSmallRingSystemConfSamples() const
{
	using namespace Chem;

	std::size_t rot_bond_sum = 0;
	const FragmentList& sssr = *getSSSR(*molGraph);

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) 
		rot_bond_sum += getNonAromaticSingleBondCount(*it);

	return (rot_bond_sum * settings.getSmallRingSystemSamplingFactor());
}

std::size_t ConfGen::FragmentConformerGeneratorImpl::calcNumMacrocyclicRingSystemConfSamples() const
{
	std::size_t max_rot_bnd_cnt = getMaxNonAromaticSingleBondCount(*getSSSR(*molGraph));

	if (max_rot_bnd_cnt <= settings.getMacrocycleRotorBondCountThreshold())
		return 0;

	return std::pow(2, max_rot_bnd_cnt);
}

unsigned int ConfGen::FragmentConformerGeneratorImpl::invokeCallbacks() const
{
	if (timeoutCallback && timeoutCallback())
		return ReturnCode::TIMEOUT;

	if (abortCallback && abortCallback())
		return ReturnCode::ABORTED;

	return ReturnCode::SUCCESS;
}

bool ConfGen::FragmentConformerGeneratorImpl::timedout(std::size_t timeout) const
{
	if (timeout == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(timeout) * 1000000));
}

ConfGen::ConformerData::SharedPointer ConfGen::FragmentConformerGeneratorImpl::allocConformerData()
{
	ConformerData::SharedPointer conf_data = confDataCache.get();

	conf_data->setEnergy(0.0);

	return conf_data;
}
