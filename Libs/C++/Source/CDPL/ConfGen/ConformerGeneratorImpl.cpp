/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorImpl.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/RMSDConformerSelector.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/ForceField/Exceptions.hpp"

#include "ConformerGeneratorImpl.hpp"
#include "FragmentTreeNode.hpp"


using namespace CDPL;


namespace
{
	
	bool compareConformerEnergy(const ConfGen::ConformerData::SharedPointer& conf_data1, 
								const ConfGen::ConformerData::SharedPointer& conf_data2)
	{
		return (conf_data1->getEnergy() < conf_data2->getEnergy());
	} 

	const std::size_t MAX_CONF_DATA_CACHE_SIZE              = 20000;
	const std::size_t MAX_FRAG_CONF_DATA_CACHE_SIZE         = 100;
	const std::size_t MAX_FRAG_CONF_COMBINATION_CACHE_SIZE  = 10000;
}


ConfGen::ConformerGeneratorImpl::ConformerGeneratorImpl():
	confDataCache(MAX_CONF_DATA_CACHE_SIZE), fragConfDataCache(MAX_FRAG_CONF_DATA_CACHE_SIZE),
	fragConfCombCache(MAX_FRAG_CONF_COMBINATION_CACHE_SIZE)
{
	fragAssembler.setTimeoutCallback(boost::bind(&ConformerGeneratorImpl::timedout, this));
	fragAssembler.setBondLengthFunction(boost::bind(&ConformerGeneratorImpl::getMMFF94BondLength, this, _1, _2));

	torDriver.setTimeoutCallback(boost::bind(&ConformerGeneratorImpl::timedout, this));

	TorsionDriverSettings& td_settings = torDriver.getSettings();

	td_settings.sampleHeteroAtomHydrogens(false);
	td_settings.orderByEnergy(false);

	fragConfDataCache.setCleanupFunction(boost::bind(&FragmentConfData::clear, _1));
} 

ConfGen::ConformerGeneratorImpl::~ConformerGeneratorImpl() {}

ConfGen::ConformerGeneratorSettings& ConfGen::ConformerGeneratorImpl::getSettings()
{
	return settings;
}

void ConfGen::ConformerGeneratorImpl::clearFragmentLibraries()
{
	fragAssembler.clearFragmentLibraries();
}

void ConfGen::ConformerGeneratorImpl::addFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragAssembler.addFragmentLibrary(lib);
}

void ConfGen::ConformerGeneratorImpl::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	torDriver.setTorsionLibrary(lib);
}

const ConfGen::TorsionLibrary::SharedPointer& ConfGen::ConformerGeneratorImpl::getTorsionLibrary() const
{
	return torDriver.getTorsionLibrary();
}

void ConfGen::ConformerGeneratorImpl::setAbortCallback(const CallbackFunction& func)
{
	abortCallback = func;

	fragAssembler.setAbortCallback(func);
	torDriver.setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::ConformerGeneratorImpl::getAbortCallback() const
{
	return abortCallback;
}

void ConfGen::ConformerGeneratorImpl::setTimeoutCallback(const CallbackFunction& func)
{
	timeoutCallback = func;
}

const ConfGen::CallbackFunction& ConfGen::ConformerGeneratorImpl::getTimeoutCallback() const
{
	return timeoutCallback;
}

unsigned int ConfGen::ConformerGeneratorImpl::generate(const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	splitIntoTorsionFragments();

	if (!setupMMFF94Parameters())
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	unsigned int ret_code = generateFragmentConformers();

	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	generateFragmentConformerCombinations();

	if ((ret_code = invokeCallbacks()) != ReturnCode::SUCCESS)
		return ret_code;

	calcFragmentConformerChangeFrequencies();

	setupTorsionDriver();

	if ((ret_code = generateConformers()) != ReturnCode::SUCCESS)
		return ret_code;

	return selectOutputConformers();
}

std::size_t ConfGen::ConformerGeneratorImpl::getNumConformers() const
{
	return outputConfs.size();
}

ConfGen::ConformerData& ConfGen::ConformerGeneratorImpl::getConformer(std::size_t idx)
{
	return *outputConfs[idx];
}

ConfGen::ConformerGeneratorImpl::ConstConformerIterator ConfGen::ConformerGeneratorImpl::getConformersBegin() const
{
	return outputConfs.begin();
}

ConfGen::ConformerGeneratorImpl::ConstConformerIterator ConfGen::ConformerGeneratorImpl::getConformersEnd() const
{
	return outputConfs.end();
}

void ConfGen::ConformerGeneratorImpl::init(const Chem::MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	torFragConfDataList.clear();
	torFragConfCombList.clear();

	fragConfDataCache.putAll();
	fragConfCombCache.putAll();

	workingConfs.clear();
	tmpWorkingConfs.clear();
	outputConfs.clear();

	timer.start();
}

void ConfGen::ConformerGeneratorImpl::splitIntoTorsionFragments()
{
	using namespace Chem;

	std::size_t num_bonds = molGraph->getNumBonds();

	tmpBitSet.resize(num_bonds);
	tmpBitSet.reset();
	torDriveBonds.clear();

	bool sample_het_hs = settings.sampleHeteroAtomHydrogens();

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molGraph->getBond(i);

		if (!isFragmentLinkBond(bond, *molGraph))
			continue;

		if (!isRotatableBond(bond, *molGraph, sample_het_hs))
			continue;

		tmpBitSet.set(i);
		torDriveBonds.push_back(&bond);
	}

	Chem::splitIntoFragments(*molGraph, fragments, tmpBitSet, false);

	for (FragmentList::BaseType::ConstElementIterator it = fragments.FragmentList::BaseType::getElementsBegin(), 
			 end = fragments.FragmentList::BaseType::getElementsEnd(); it != end; ++it) {

		FragmentConfData* frag_conf_data = fragConfDataCache.getRaw();

		frag_conf_data->fragment = *it;

		torFragConfDataList.push_back(frag_conf_data);
	}
}

bool ConfGen::ConformerGeneratorImpl::setupMMFF94Parameters()
{
	mmff94Parameterizer.strictParameterization(settings.strictForceFieldParameterization());

	try {
		if (parameterizeMMFF94Interactions(*molGraph, mmff94Parameterizer, mmff94Data, settings.getForceFieldType()) == ReturnCode::SUCCESS) {
			mmff94InteractionMask.setup(mmff94Data);
			return true;
		}

	} catch (const ForceField::Error&) {}

	return false;
}

unsigned int ConfGen::ConformerGeneratorImpl::generateFragmentConformers()
{
	using namespace Chem;

	FragmentAssemblerSettings& fa_settings = fragAssembler.getSettings();

	fa_settings.getFragmentBuildSettings() = settings.getFragmentBuildSettings();
	fa_settings.enumerateRings(settings.enumerateRings());
	fa_settings.setNitrogenEnumerationMode(settings.getNitrogenEnumerationMode());

	for (FragmentConfDataList::const_iterator it = torFragConfDataList.begin(), end = torFragConfDataList.end(); it != end; ++it) {
		FragmentConfData* frag_conf_data = *it;
		const Fragment& frag = *frag_conf_data->fragment;
		unsigned int ret_code = fragAssembler.assemble(frag, *molGraph);

		if (ret_code != ReturnCode::SUCCESS)
			return ret_code;

		std::size_t num_bonds = frag.getNumBonds();
	
		tmpBitSet.resize(num_bonds);
		tmpBitSet.reset();
		fragSplitBonds.clear();

		for (std::size_t i = 0; i < num_bonds; i++) {
			const Bond& bond = frag.getBond(i);

			if (!isRotatableBond(bond, frag, false))
				continue;

			tmpBitSet.set(i);
			fragSplitBonds.push_back(&bond);
		}

		if (fragSplitBonds.empty()) {
			fragments.clear();
			fragments.addElement(frag_conf_data->fragment);

		} else 
			Chem::splitIntoFragments(frag, fragments, tmpBitSet, false);

		torDriver.setup(fragments, *molGraph, fragSplitBonds.begin(), fragSplitBonds.end());
		torDriver.setMMFF94Parameters(mmff94Data, mmff94InteractionMask);

		if (fragSplitBonds.empty()) {
			const FragmentTreeNode& frag_node = torDriver.getFragmentNode(0);

			for (FragmentAssemblerImpl::ConstConformerIterator conf_it = fragAssembler.getConformersBegin(), conf_end = fragAssembler.getConformersEnd();
				 conf_it != conf_end; ++conf_it) {

				ConformerData& conf_data = **conf_it;
				ConformerData::SharedPointer final_conf_data = confDataCache.get();

				final_conf_data->swap(conf_data);
				final_conf_data->setEnergy(frag_node.calcMMFF94Energy(*final_conf_data));
				frag_conf_data->conformers.push_back(final_conf_data);
			}

		} else {
			for (FragmentAssemblerImpl::ConstConformerIterator fa_conf_it = fragAssembler.getConformersBegin(), fa_conf_end = fragAssembler.getConformersEnd();
				 fa_conf_it != fa_conf_end; ++fa_conf_it) {

				ConformerData& fa_conf_data = **fa_conf_it;

				torDriver.setInputCoordinates(fa_conf_data);

				ret_code = torDriver.generateConformers();

				if (ret_code != ReturnCode::SUCCESS) {
					if (ret_code == ReturnCode::TORSION_DRIVING_FAILED) {
						ConformerData::SharedPointer final_conf_data = confDataCache.get();

						final_conf_data->swap(fa_conf_data);
						frag_conf_data->conformers.push_back(final_conf_data);
						continue;
					}

					return ret_code;
				}

				for (TorsionDriverImpl::ConstConformerIterator td_conf_it = torDriver.getConformersBegin(), td_conf_end = torDriver.getConformersEnd();
					 td_conf_it != td_conf_end; ++td_conf_it) {

					ConformerData& td_conf_data = **td_conf_it;
					ConformerData::SharedPointer final_conf_data = confDataCache.get();

					final_conf_data->swap(td_conf_data);
					frag_conf_data->conformers.push_back(final_conf_data);
				}
			}
		}

		std::sort(frag_conf_data->conformers.begin(), frag_conf_data->conformers.end(), &compareConformerEnergy); 

		frag_conf_data->lastConfIdx = frag_conf_data->conformers.size();
	}

	return ReturnCode::SUCCESS;
}
			
void ConfGen::ConformerGeneratorImpl::generateFragmentConformerCombinations()
{
	currConfComb.clear();

	generateFragmentConformerCombinations(0, 0.0);

	std::sort(torFragConfCombList.begin(), torFragConfCombList.end(), &compFragmentConfCombinationEnergy);
}

void ConfGen::ConformerGeneratorImpl::generateFragmentConformerCombinations(std::size_t frag_idx, double comb_energy)
{
	if (torFragConfDataList.size() <= frag_idx) {
		FragmentConfCombination* frag_conf_comb = fragConfCombCache.getRaw();

		frag_conf_comb->valid = true;
		frag_conf_comb->energy = comb_energy;
		frag_conf_comb->confIndices = currConfComb;

		torFragConfCombList.push_back(frag_conf_comb);
		return;
	}

	const FragmentConfData* frag_conf_data = torFragConfDataList[frag_idx];

	for (std::size_t i = 0, num_confs = frag_conf_data->conformers.size(); i < num_confs; i++) {
		currConfComb.push_back(i);

		generateFragmentConformerCombinations(frag_idx + 1, comb_energy + frag_conf_data->conformers[i]->getEnergy());
		
		currConfComb.pop_back();
	}
}

void ConfGen::ConformerGeneratorImpl::calcFragmentConformerChangeFrequencies() const
{
	for (std::size_t i = 0, num_frags = torFragConfDataList.size(); i < num_frags; i++)
		torFragConfDataList[i]->confChangeFreq = calcFragmentConformerChangeFrequency(i);
}

std::size_t ConfGen::ConformerGeneratorImpl::calcFragmentConformerChangeFrequency(std::size_t frag_idx) const
{
	std::size_t freq = 0;
	std::size_t last_conf_idx = 0;

	for (FragmentConfCombinationList::const_iterator it = torFragConfCombList.begin(), end = torFragConfCombList.end(); it != end; ++it) {
		if (freq == 0 || (*it)->confIndices[frag_idx] != last_conf_idx) {
			last_conf_idx = (*it)->confIndices[frag_idx];
			freq++;
		}
	}

	return freq;
}

void ConfGen::ConformerGeneratorImpl::setupTorsionDriver()
{
	fragments.clear();
	sortedTorFragConfDataList.clear();

	sortedTorFragConfDataList = torFragConfDataList;

	std::sort(sortedTorFragConfDataList.begin(), sortedTorFragConfDataList.end(), &compFragmentConfChangeFrequency);

	for (std::size_t i = 0, num_frags = sortedTorFragConfDataList.size(); i < num_frags; i++) {
		sortedTorFragConfDataList[i]->torDriverFragIdx = i;
		fragments.addElement(sortedTorFragConfDataList[i]->fragment);
	}

	torDriver.setup(fragments, *molGraph, torDriveBonds.begin(), torDriveBonds.end());
	torDriver.setMMFF94Parameters(mmff94Data, mmff94InteractionMask);
}

unsigned int ConfGen::ConformerGeneratorImpl::generateConformers()
{
	double min_energy = 0.0;
	double min_comb_energy = 0.0;
	double e_window = settings.getEnergyWindow();

	std::size_t num_frags = torFragConfDataList.size();

	for (FragmentConfCombinationList::const_iterator comb_it = torFragConfCombList.begin(), combs_end = torFragConfCombList.end(); comb_it != combs_end; ++comb_it) {
		const FragmentConfCombination* comb = *comb_it;

		if (!workingConfs.empty() && comb->energy > (min_comb_energy + e_window))
			break;

		//std::cerr << "Next combination: " << comb->energy << std::endl;

		for (std::size_t i = 0; i < num_frags; i++) {
			FragmentConfData* conf_data = torFragConfDataList[i];
			std::size_t next_conf_idx = comb->confIndices[i];

			if (conf_data->lastConfIdx != next_conf_idx) {
				torDriver.setInputCoordinates(conf_data->conformers[next_conf_idx], conf_data->torDriverFragIdx);

				conf_data->lastConfIdx = next_conf_idx;
			}
		}

		unsigned int ret_code = torDriver.generateConformers();

		if (ret_code == ReturnCode::TIMEOUT || ret_code == ReturnCode::ABORTED)
			return ret_code;

		if (ret_code != ReturnCode::SUCCESS)
			continue;

		bool new_min_energy = false;

		//std::cerr << "Generated " << torDriver.getNumConformers() << " confs." << std::endl;

		for (TorsionDriverImpl::ConstConformerIterator conf_it = torDriver.getConformersBegin(), confs_end = torDriver.getConformersEnd();
			 conf_it != confs_end; ++conf_it) {
			
			ConformerData& conf_data = **conf_it;
			double energy = conf_data.getEnergy();
			
			if (workingConfs.empty() || energy < min_energy) {
				min_energy = energy;
				min_comb_energy = comb->energy;
				new_min_energy = !workingConfs.empty();

			} else if (energy > (min_energy + e_window))
				continue;
			  
			ConformerData::SharedPointer conf_data_copy = confDataCache.get();

			conf_data_copy->swap(conf_data);
			workingConfs.push_back(conf_data_copy);
		}

		if (!new_min_energy)
			continue;

		for (ConformerDataArray::const_iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
			const ConformerData::SharedPointer& conf_data = *it;

			if (conf_data->getEnergy() > (min_energy + e_window))
				continue;

			tmpWorkingConfs.push_back(conf_data);
		} 

		workingConfs.swap(tmpWorkingConfs);
		tmpWorkingConfs.clear();
	}

	return (workingConfs.empty() ? ReturnCode::CONF_GEN_FAILED : ReturnCode::SUCCESS);
}

unsigned int ConfGen::ConformerGeneratorImpl::selectOutputConformers()
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

	tmpBitSet.resize(num_atoms);
	tmpBitSet.reset();

// TODO >
	for (std::size_t i = 0; i < num_atoms; i++)
		if (getType(molGraph->getAtom(i)) != AtomType::H)
			tmpBitSet.set(i);

	if (!confSelector.get())
		confSelector.reset(new RMSDConformerSelector());

	confSelector->setup(*molGraph, tmpBitSet);
// < TODO

	confSelector->setMinRMSD(settings.getMinRMSD());

	std::sort(workingConfs.begin(), workingConfs.end(), &compareConformerEnergy); 
	
	double max_energy = workingConfs.front()->getEnergy() + settings.getEnergyWindow();
	std::size_t max_num_confs = settings.getMaxNumOutputConformers();

	for (ConformerDataArray::const_iterator it = workingConfs.begin(), end = workingConfs.end(); 
		 it != end && outputConfs.size() < max_num_confs; ++it) {

		const ConformerData::SharedPointer& conf_data = *it;

		if (conf_data->getEnergy() > max_energy)
			break;

		if (confSelector->selected(*conf_data))
			outputConfs.push_back(conf_data);
	}

	return invokeCallbacks();
}

double ConfGen::ConformerGeneratorImpl::getMMFF94BondLength(std::size_t atom1_idx, std::size_t atom2_idx) const
{
	using namespace ForceField;

	const MMFF94BondStretchingInteractionData& bs_ia_data = mmff94Data.getBondStretchingInteractions();

	for (MMFF94BondStretchingInteractionData::ConstElementIterator it = bs_ia_data.getElementsBegin(), 
			 end = bs_ia_data.getElementsEnd(); it != end; ++it) { 

		const MMFF94BondStretchingInteraction& params = *it;

		if ((params.getAtom1Index() == atom1_idx && params.getAtom2Index() == atom2_idx) ||
			(params.getAtom1Index() == atom2_idx && params.getAtom2Index() == atom1_idx)) 
			return params.getReferenceLength();
	}

	return 0.0;
}

bool ConfGen::ConformerGeneratorImpl::compFragmentConfCombinationEnergy(const FragmentConfCombination* comb1, 
																		const FragmentConfCombination* comb2)
{
	return (comb1->energy < comb2->energy);
}

bool ConfGen::ConformerGeneratorImpl::compFragmentConfChangeFrequency(const FragmentConfData* conf_data1, 
																	  const FragmentConfData* conf_data2)
{
	return (conf_data1->confChangeFreq < conf_data2->confChangeFreq);
}

unsigned int ConfGen::ConformerGeneratorImpl::invokeCallbacks() const
{
	if (abortCallback && abortCallback())
		return ReturnCode::ABORTED;

	if (timedout())
		return ReturnCode::TIMEOUT;	

	return ReturnCode::SUCCESS;
}

bool ConfGen::ConformerGeneratorImpl::timedout() const
{
	if (timeoutCallback && timeoutCallback())
		return true;

	std::size_t timeout = settings.getTimeout();

	if (timeout == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(timeout) * 1000000));
}
