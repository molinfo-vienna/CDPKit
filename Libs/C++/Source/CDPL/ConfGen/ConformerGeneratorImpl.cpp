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
#include <iterator>

#include <boost/bind.hpp>
#include <boost/math/special_functions.hpp>

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
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

	void setNeighborAtomBits(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Util::BitSet& mask)
	{
		using namespace Chem;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Bond& nbr_bond = *b_it;

			if (!molgraph.containsBond(nbr_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			mask.set(molgraph.getAtomIndex(nbr_atom));
		}
	}

	const std::size_t MAX_CONF_DATA_CACHE_SIZE              = 20000;
	const std::size_t MAX_FRAG_CONF_DATA_CACHE_SIZE         = 100;
	const std::size_t MAX_FRAG_CONF_COMBINATION_CACHE_SIZE  = 20000;
	const double      COMP_CONFORMER_SPACING                = 4.0;
	const std::size_t MAX_NUM_STRUCTURE_GEN_TRIALS          = 10;

	const std::size_t CONV_STRUCTURE_GEN_TRIALS             = 100;
}


ConfGen::ConformerGeneratorImpl::ConformerGeneratorImpl():
	confDataCache(MAX_CONF_DATA_CACHE_SIZE), fragConfDataCache(MAX_FRAG_CONF_DATA_CACHE_SIZE),
	confCombDataCache(MAX_FRAG_CONF_COMBINATION_CACHE_SIZE),
	energyMinimizer(boost::ref(mmff94EnergyCalc), boost::ref(mmff94GradientCalc))
{
	fragAssembler.setTimeoutCallback(boost::bind(&ConformerGeneratorImpl::timedout, this));
	fragAssembler.setBondLengthFunction(boost::bind(&ConformerGeneratorImpl::getMMFF94BondLength, this, _1, _2));

	torDriver.setTimeoutCallback(boost::bind(&ConformerGeneratorImpl::timedout, this));

	TorsionDriverSettings& td_settings = torDriver.getSettings();

	td_settings.sampleHeteroAtomHydrogens(false);
	td_settings.orderByEnergy(false);

	fragConfDataCache.setCleanupFunction(boost::bind(&FragmentConfData::clear, _1));

	hCoordsGen.undefinedOnly(true);
	hCoordsGen.setAtom3DCoordinatesCheckFunction(boost::bind(&ConformerGeneratorImpl::has3DCoordinates, this, _1));

	DGStructureGeneratorSettings& dg_settings = dgStructureGen.getSettings();

	dg_settings.excludeHydrogens(true);
    dg_settings.regardAtomConfiguration(true);
    dg_settings.regardBondConfiguration(true);
	dg_settings.enablePlanarityConstraints(true);
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
	using namespace Chem;

	const FragmentList& comps = *getComponents(molgraph);

	if (molgraph.getNumAtoms() == 0 || settings.getMaxNumOutputConformers() == 0 || comps.isEmpty()) {
		outputConfs.clear();

		return ReturnCode::SUCCESS;
	}

	timer.start();
	compConfData.clear();

	if (comps.getSize() == 1) {
		unsigned int ret_code = generateConformers(molgraph);

		if (ret_code != ReturnCode::SUCCESS)
			return ret_code;

		if (selectOutputConformers())
			std::sort(outputConfs.begin(), outputConfs.end(), &compareConformerEnergy);

		return invokeCallbacks();
	}

	return generateConformers(molgraph, comps);
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

unsigned int ConfGen::ConformerGeneratorImpl::generateConformers(const Chem::MolecularGraph& molgraph, const Chem::FragmentList& comps)
{
	using namespace Chem;

	bool have_full_ipt_coords = true;

	for (FragmentList::BaseType::ConstElementIterator it = comps.BaseType::getElementsBegin(), end = comps.BaseType::getElementsEnd(); it != end; ++it) {
		const Fragment::SharedPointer& comp = *it;

		if (comp->getNumAtoms() == 0) // sanity check
			continue;

		unsigned int ret_code = generateConformers(*comp);

		if (ret_code != ReturnCode::SUCCESS) 
			return ret_code;

		FragmentConfDataPtr comp_conf_data = fragConfDataCache.get();

		comp_conf_data->haveInputCoords = selectOutputConformers();
		comp_conf_data->fragment = comp;
		comp_conf_data->conformers.swap(outputConfs);

		have_full_ipt_coords &= comp_conf_data->haveInputCoords;

		compConfData.push_back(comp_conf_data);
	}

	return combineComponentConformers(molgraph, have_full_ipt_coords);
}

unsigned int ConfGen::ConformerGeneratorImpl::combineComponentConformers(const Chem::MolecularGraph& molgraph, bool have_full_ipt_coords)
{
	using namespace Chem;

	outputConfs.clear();
	parentAtomInds.clear();

	std::size_t max_num_confs = 0;

	for (FragmentConfDataList::const_iterator it = compConfData.begin(), end = compConfData.end(); it != end; ++it) {
		FragmentConfData& comp_conf_data = **it;
		const Fragment& comp = *comp_conf_data.fragment;

		std::transform(comp.getAtomsBegin(), comp.getAtomsEnd(), std::back_inserter(parentAtomInds),
					   boost::bind(&MolecularGraph::getAtomIndex, &molgraph, _1));

		if (!have_full_ipt_coords && comp_conf_data.haveInputCoords)
			std::sort(comp_conf_data.conformers.begin(), comp_conf_data.conformers.end(), &compareConformerEnergy);

		if (comp_conf_data.conformers.size() > max_num_confs)
			max_num_confs = comp_conf_data.conformers.size();
	}

	std::size_t num_comps = compConfData.size();
	std::size_t num_atoms = molgraph.getNumAtoms();
	double bbox_min[3];
	double bbox_max[3];

	for (std::size_t i = 0; i < max_num_confs; i++) {
		ConformerData::SharedPointer opt_conf_data = confDataCache.get();
		Math::Vector3DArray::StorageType& opt_conf_coords_data = opt_conf_data->getData();

		opt_conf_data->resize(num_atoms);

		double comp_conf_x_pos = 0.0;
		double total_energy = 0.0;

		for (std::size_t j = 0, l = 0; j < num_comps; j++) {
			FragmentConfData& comp_conf_data = *compConfData[j];
			const ConformerData& conf_data = *comp_conf_data.conformers[std::min(comp_conf_data.conformers.size() - 1, i)];
			const Math::Vector3DArray::StorageType& conf_coords_data = conf_data.getData();

			total_energy += conf_data.getEnergy();

			if (have_full_ipt_coords && i == 0) {
				for (std::size_t k = 0, num_comp_atoms = comp_conf_data.fragment->getNumAtoms(); k < num_comp_atoms; k++, l++) 
					opt_conf_coords_data[parentAtomInds[l]].assign(conf_coords_data[k]);

				continue;
			}

			calcConformerBounds(bbox_min, bbox_max, conf_data);

			double trans_x = comp_conf_x_pos - bbox_min[0];
			double trans_y = -0.5 * (bbox_min[1] + bbox_max[1]);
			double trans_z = -0.5 * (bbox_min[2] + bbox_max[2]);
	
			for (std::size_t k = 0, num_comp_atoms = comp_conf_data.fragment->getNumAtoms(); k < num_comp_atoms; k++, l++) {
				Math::Vector3D::ConstPointer comp_atom_pos = conf_coords_data[k].getData();
				Math::Vector3D::Pointer opt_atom_pos = opt_conf_coords_data[parentAtomInds[l]].getData();

				opt_atom_pos[0] = comp_atom_pos[0] + trans_x;
				opt_atom_pos[1] = comp_atom_pos[1] + trans_y;
				opt_atom_pos[2] = comp_atom_pos[2] + trans_z;
			} 
			
			comp_conf_x_pos += bbox_max[0] - bbox_min[0] + COMP_CONFORMER_SPACING;
		}

		opt_conf_data->setEnergy(total_energy);

		outputConfs.push_back(opt_conf_data);
	}

	if (have_full_ipt_coords)
		std::sort(outputConfs.begin(), outputConfs.end(), &compareConformerEnergy);

	return invokeCallbacks();
}

void ConfGen::ConformerGeneratorImpl::calcConformerBounds(double min[3], double max[3], const Math::Vector3DArray& coords) const
{
	bool init = true;

	for (Math::Vector3DArray::ConstElementIterator it = coords.getElementsBegin(), end = coords.getElementsEnd(); it != end; ++it) {
		Math::Vector3D::ConstPointer atom_pos_data = it->getData();

		if (init) {
			max[0] = atom_pos_data[0];
			max[1] = atom_pos_data[1];
			max[2] = atom_pos_data[2];

			min[0] = atom_pos_data[0];
			min[1] = atom_pos_data[1];
			min[2] = atom_pos_data[2];

			init = false;
			continue;
		}

		if (atom_pos_data[0] > max[0])
			max[0] = atom_pos_data[0];

		else if (atom_pos_data[0] < min[0])
			min[0] = atom_pos_data[0];

		if (atom_pos_data[1] > max[1])
			max[1] = atom_pos_data[1];

		else if (atom_pos_data[1] < min[1])
			min[1] = atom_pos_data[1];

		if (atom_pos_data[2] > max[2])
			max[2] = atom_pos_data[2];
			
		else if (atom_pos_data[2] < min[2])
			min[2] = atom_pos_data[2];
	}
} 

unsigned int ConfGen::ConformerGeneratorImpl::generateConformers(const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	if (molgraph.getNumAtoms() == 0)
		return ReturnCode::SUCCESS;

	if (!setupMMFF94Parameters())
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	if (determineSamplingMode())
		return generateConformersStochastic();

	return generateConformersSystematic();
}

unsigned int ConfGen::ConformerGeneratorImpl::generateConformersSystematic()
{
	splitIntoTorsionFragments();

	unsigned int ret_code = generateFragmentConformers();

	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	if ((ret_code = generateFragmentConformerCombinations()) != ReturnCode::SUCCESS)
		return ret_code;

	return generateOutputConformers();
}

unsigned int ConfGen::ConformerGeneratorImpl::generateConformersStochastic()
{
	std::size_t num_atoms = molGraph->getNumAtoms();

	dgStructureGen.setup(*molGraph, mmff94Data);

	coreAtomMask = dgStructureGen.getExcludedHydrogenMask();
	coreAtomMask.flip();

	dgStructureGen.getSettings().setBoxSize(coreAtomMask.count() * 2);

	hCoordsGen.setup(*molGraph);

	mmff94EnergyCalc.setup(mmff94Data);

	mmff94GradientCalc.setup(mmff94Data, num_atoms);
	mmff94GradientCalc.resetFixedAtomMask();

	energyGradient.resize(num_atoms);

	double e_window = settings.getEnergyWindow();
	double min_energy = 0.0;
	ConformerData::SharedPointer conf_data_ptr;

	std::size_t last_min_iter_count = 0;

	for (std::size_t i = 0, num_conf_samples = settings.getMaxNumSampledConformers(); i < num_conf_samples && last_min_iter_count <= CONV_STRUCTURE_GEN_TRIALS; 
		 i++, last_min_iter_count++) {

		unsigned int ret_code = invokeCallbacks();

		if (ret_code != ReturnCode::SUCCESS) {
			if (ret_code == ReturnCode::TIMEOUT)
				break;

			return ret_code;
		}

		if (!conf_data_ptr) {
			conf_data_ptr = confDataCache.get();
			conf_data_ptr->resize(num_atoms);
		}

		ConformerData& conf_data = *conf_data_ptr;
		bool gen_valid_conf = false;

		for (std::size_t j = 0; j < MAX_NUM_STRUCTURE_GEN_TRIALS; j++) {
			if (!dgStructureGen.generate(conf_data)) 
				continue;

			if (!generateHydrogenCoordsAndMinimize(conf_data))
				continue;

			if (!dgStructureGen.checkAtomConfigurations(conf_data)) 
				continue;

			if (!dgStructureGen.checkBondConfigurations(conf_data)) 
				continue;

			gen_valid_conf = true;
			break;
		}

		if (!gen_valid_conf)
			continue;

		double energy = conf_data.getEnergy();

		if (workingConfs.empty())
			min_energy = energy;

		else if (energy > (min_energy + e_window)) 
			continue;
		
		if (energy < min_energy) { 
			last_min_iter_count = 0;
			min_energy = energy;

			for (ConformerDataArray::const_iterator it = workingConfs.begin(), end = workingConfs.end(); it != end; ++it) {
				const ConformerData::SharedPointer& conf = *it;

				if (conf->getEnergy() > (min_energy + e_window))
					continue;

				tmpWorkingConfs.push_back(conf);
			} 

			workingConfs.swap(tmpWorkingConfs);
			tmpWorkingConfs.clear();
		} else

		workingConfs.push_back(conf_data_ptr);
		conf_data_ptr.reset();	
	}

	return (workingConfs.empty() ? ReturnCode::CONF_GEN_FAILED : ReturnCode::SUCCESS);
}

bool ConfGen::ConformerGeneratorImpl::determineSamplingMode()
{
	switch (settings.getConformerSamplingMode()) {

		case ConformerSamplingMode::STOCHASTIC:
			inStochasticMode = true;
			return true;

		case ConformerSamplingMode::SYSTEMATIC:
			inStochasticMode = false;
			return false;

		default: 
			break;
	}

	return (inStochasticMode = Chem::containsFragmentWithMinSize(*getSSSR(*molGraph), settings.getMinMacrocycleSize()));
}

void ConfGen::ConformerGeneratorImpl::init(const Chem::MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	confCombDataCache.putAll();

	torFragConfData.clear();
	torFragConfCombData.clear();
	workingConfs.clear();
	tmpWorkingConfs.clear();
	outputConfs.clear();

	invertibleNMask.resize(molgraph.getNumAtoms());
	invertibleNMask.reset();
}

bool ConfGen::ConformerGeneratorImpl::generateHydrogenCoordsAndMinimize(ConformerData& conf_data)
{
	hCoordsGen.generate(conf_data, false);

	Math::Vector3DArray::StorageType& conf_coords_data = conf_data.getData();
	std::size_t max_ref_iters = settings.getMaxNumRefinementIterations();
	double stop_grad = settings.getRefinementStopGradient();
	double energy = 0.0;

	energyMinimizer.setup(conf_coords_data, energyGradient);

	for (std::size_t j = 0; max_ref_iters == 0 || j < max_ref_iters; j++) {
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

ConfGen::ConformerData::SharedPointer ConfGen::ConformerGeneratorImpl::getInputCoordinates()
{
	using namespace Chem;

	ConformerData::SharedPointer ipt_coords = confDataCache.get();
	Math::Vector3DArray::StorageType& ipt_coords_data = ipt_coords->getData();
	std::size_t num_atoms = molGraph->getNumAtoms();

	ipt_coords->resize(num_atoms);

	coreAtomMask.resize(num_atoms);
	coreAtomMask.set();

	bool coords_compl = true;

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		try {
			ipt_coords_data[i].assign(get3DCoordinates(atom));

		} catch (const Base::ItemNotFound&) {
			if (getType(atom) != AtomType::H)
				return ConformerData::SharedPointer();

			coreAtomMask.reset(i);
			coords_compl = false;
		}
	} 

	mmff94EnergyCalc.setup(mmff94Data);

	if (!coords_compl) {
		mmff94GradientCalc.setFixedAtomMask(coreAtomMask);
		mmff94GradientCalc.setup(mmff94Data, num_atoms);

		energyGradient.resize(num_atoms);

		hCoordsGen.setup(*molGraph);

		if (!generateHydrogenCoordsAndMinimize(*ipt_coords))
			return ConformerData::SharedPointer();

	} else
		ipt_coords->setEnergy(mmff94EnergyCalc(ipt_coords_data));

	return ipt_coords;
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

		FragmentConfDataPtr frag_conf_data = fragConfDataCache.get();

		frag_conf_data->fragment = *it;

		torFragConfData.push_back(frag_conf_data);
	}
}

bool ConfGen::ConformerGeneratorImpl::setupMMFF94Parameters()
{
	try {
		if (parameterizeMMFF94Interactions(*molGraph, mmff94Parameterizer, mmff94Data, settings.getForceFieldType(), 
										   settings.strictForceFieldParameterization()) == ReturnCode::SUCCESS) {

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
	fa_settings.generateCoordinatesFromScratch(settings.generateCoordinatesFromScratch());

	for (FragmentConfDataList::const_iterator it = torFragConfData.begin(), end = torFragConfData.end(); it != end; ++it) {
		FragmentConfData& frag_conf_data = **it;
		const Fragment& frag = *frag_conf_data.fragment;
		unsigned int ret_code = fragAssembler.assemble(frag, *molGraph);

		if (ret_code != ReturnCode::SUCCESS)
			return ret_code;

		frag_conf_data.isFlexRingSys = fragAssembler.foundFlexibleRingSystem();
		invertibleNMask |= fragAssembler.getInvertibleNitrogenMask();

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
			fragments.addElement(frag_conf_data.fragment);

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

				frag_conf_data.conformers.push_back(final_conf_data);
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
						frag_conf_data.conformers.push_back(final_conf_data);
						continue;
					}

					return ret_code;
				}

				for (TorsionDriverImpl::ConstConformerIterator td_conf_it = torDriver.getConformersBegin(), td_conf_end = torDriver.getConformersEnd();
					 td_conf_it != td_conf_end; ++td_conf_it) {

					ConformerData& td_conf_data = **td_conf_it;
					ConformerData::SharedPointer final_conf_data = confDataCache.get();

					final_conf_data->swap(td_conf_data);
					frag_conf_data.conformers.push_back(final_conf_data);
				}
			}
		}

		std::sort(frag_conf_data.conformers.begin(), frag_conf_data.conformers.end(), &compareConformerEnergy); 

		frag_conf_data.lastConfIdx = frag_conf_data.conformers.size();
	}

	std::sort(torFragConfData.begin(), torFragConfData.end(), &compareFragmentConfCount);

	return ReturnCode::SUCCESS;
}
			
unsigned int ConfGen::ConformerGeneratorImpl::generateFragmentConformerCombinations()
{
	currConfComb.clear();

	generateFragmentConformerCombinations(0, 0.0);

	std::sort(torFragConfCombData.begin(), torFragConfCombData.end(), &compareConfCombinationEnergy);

	return invokeCallbacks();
}

void ConfGen::ConformerGeneratorImpl::generateFragmentConformerCombinations(std::size_t frag_idx, double comb_energy)
{
	if (torFragConfData.size() <= frag_idx) {
		ConfCombinationData* frag_conf_comb = confCombDataCache.getRaw();

		frag_conf_comb->valid = true;
		frag_conf_comb->energy = comb_energy;
		frag_conf_comb->confIndices = currConfComb;

		torFragConfCombData.push_back(frag_conf_comb);
		return;
	}

	const FragmentConfData& frag_conf_data = *torFragConfData[frag_idx];

	for (std::size_t i = 0, num_confs = frag_conf_data.conformers.size(); i < num_confs; i++) {
		currConfComb.push_back(i);

		generateFragmentConformerCombinations(frag_idx + 1, comb_energy + frag_conf_data.conformers[i]->getEnergy());
		
		currConfComb.pop_back();
	}
}

unsigned int ConfGen::ConformerGeneratorImpl::generateOutputConformers()
{
	fragments.clear();

	for (FragmentConfDataList::const_iterator it = torFragConfData.begin(), end = torFragConfData.end(); it != end; ++it) 
		fragments.addElement((*it)->fragment);

	torDriver.setup(fragments, *molGraph, torDriveBonds.begin(), torDriveBonds.end());
	torDriver.setMMFF94Parameters(mmff94Data, mmff94InteractionMask);

	std::size_t num_frags = torFragConfData.size();

	bool lock_flex_rsys = (!settings.enumerateRings() && 
						   (std::find_if(torFragConfData.begin(), torFragConfData.end(), 
										 boost::bind(&FragmentConfData::isFlexRingSys, _1)) != torFragConfData.end()));
	double min_energy = 0.0;
	double min_comb_energy = 0.0;
	double e_window = settings.getEnergyWindow();

	for (ConfCombinationDataList::const_iterator comb_it = torFragConfCombData.begin(), combs_end = torFragConfCombData.end(); comb_it != combs_end; ++comb_it) {
		const ConfCombinationData& comb = **comb_it;

		if (!comb.valid)
			continue;

		if (!workingConfs.empty() && comb.energy > (min_comb_energy + e_window))
			break;

		for (std::size_t i = 0; i < num_frags; i++) {
			FragmentConfData& conf_data = *torFragConfData[i];
			std::size_t next_conf_idx = comb.confIndices[i];

			if (conf_data.lastConfIdx != next_conf_idx) {
				torDriver.setInputCoordinates(conf_data.conformers[next_conf_idx], i);

				conf_data.lastConfIdx = next_conf_idx;
			}
		}

		unsigned int ret_code = torDriver.generateConformers();

		if (ret_code == ReturnCode::TIMEOUT || ret_code == ReturnCode::ABORTED)
			return ret_code;

		if (ret_code != ReturnCode::SUCCESS) 
			continue;

		if (lock_flex_rsys) {
			for (ConfCombinationDataList::const_iterator comb_it2 = comb_it + 1; comb_it2 != combs_end; ++comb_it2) {
				ConfCombinationData& next_comb = **comb_it2;

				for (std::size_t i = 0; i < num_frags; i++) {
					const FragmentConfData& conf_data = *torFragConfData[i];

					if (conf_data.isFlexRingSys && next_comb.confIndices[i] != comb.confIndices[i]) {
						next_comb.valid = false;
						break;
					}
				}
			}

			lock_flex_rsys = false;
		}

		bool new_min_energy = false;

		for (TorsionDriverImpl::ConstConformerIterator conf_it = torDriver.getConformersBegin(), confs_end = torDriver.getConformersEnd();
			 conf_it != confs_end; ++conf_it) {
			
			ConformerData& conf_data = **conf_it;
			double energy = conf_data.getEnergy();
			
			if (workingConfs.empty() || energy < min_energy) {
				min_energy = energy;
				min_comb_energy = comb.energy;
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

bool ConfGen::ConformerGeneratorImpl::selectOutputConformers()
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

	tmpBitSet.resize(num_atoms);
	tmpBitSet.reset();

	fixedAtomConfigMask.resize(num_atoms);
	fixedAtomConfigMask.reset();

	if (inStochasticMode) {
		for (std::size_t i = 0; i < num_atoms; i++) {
			const Atom& atom = molGraph->getAtom(i);

			if (getType(atom) == AtomType::H)
				continue;

			tmpBitSet.set(i);
		}

		for (DGConstraintGenerator::ConstStereoCenterDataIterator it = dgStructureGen.getConstraintGenerator().getAtomStereoCenterDataBegin(),
				 end = dgStructureGen.getConstraintGenerator().getAtomStereoCenterDataEnd(); it != end; ++it) 
			fixedAtomConfigMask.set(it->first);

		if (settings.sampleHeteroAtomHydrogens()) {
			for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
				const Bond& bond = *it;
				const Atom& atom1 = bond.getBegin();
				unsigned int atom1_type = getType(atom1);

				if (atom1_type != AtomType::C && atom1_type != AtomType::H && getExplicitBondCount(atom1, *molGraph) > 1 && getHeavyBondCount(atom1, *molGraph) == 1)
					setNeighborAtomBits(atom1, *molGraph, tmpBitSet);

				const Atom& atom2 = bond.getEnd();
				unsigned int atom2_type = getType(atom2);

				if (atom2_type != AtomType::C && atom2_type != AtomType::H && getExplicitBondCount(atom2, *molGraph) > 1 && getHeavyBondCount(atom2, *molGraph) == 1)
					setNeighborAtomBits(atom2, *molGraph, tmpBitSet);
			}
		}

	} else {
		for (std::size_t i = 0; i < num_atoms; i++) {
			const Atom& atom = molGraph->getAtom(i);

			if (getType(atom) == AtomType::H)
				continue;
 
			tmpBitSet.set(i);

			if (invertibleNMask.test(i)) 
				setNeighborAtomBits(atom, *molGraph, tmpBitSet);

			else if (!getRingFlag(atom)) 
				fixedAtomConfigMask.set(i);
		}

		for (BondList::const_iterator it = torDriveBonds.begin(), end = torDriveBonds.end(); it != end; ++it) {
			const Bond& bond = **it;
			const Atom& atom1 = bond.getBegin();

			if (getHeavyBondCount(atom1, *molGraph) == 1)
				setNeighborAtomBits(atom1, *molGraph, tmpBitSet);

			const Atom& atom2 = bond.getEnd();

			if (getHeavyBondCount(atom2, *molGraph) == 1)
				setNeighborAtomBits(atom2, *molGraph, tmpBitSet);
		}
	}

	std::sort(workingConfs.begin(), workingConfs.end(), &compareConformerEnergy); 

	confSelector.setMinRMSD(settings.getMinRMSD());
	confSelector.setup(*molGraph, tmpBitSet, fixedAtomConfigMask, *workingConfs.front());
	
	double max_energy = workingConfs.front()->getEnergy() + settings.getEnergyWindow();
	std::size_t max_num_confs = settings.getMaxNumOutputConformers();
	bool have_ipt_coords = false;

	if (settings.includeInputCoordinates()) {
		ConformerData::SharedPointer ipt_coords = getInputCoordinates();

		if (ipt_coords) {
			outputConfs.push_back(ipt_coords);
			confSelector.selected(*ipt_coords);

			have_ipt_coords = true;
		}
	}

	for (ConformerDataArray::const_iterator it = workingConfs.begin(), end = workingConfs.end(); 
		 it != end && outputConfs.size() < max_num_confs; ++it) {

		const ConformerData::SharedPointer& conf_data = *it;

		if (conf_data->getEnergy() > max_energy)
			break;

		if (confSelector.selected(*conf_data))
			outputConfs.push_back(conf_data);
	}

	return have_ipt_coords;
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
		
bool ConfGen::ConformerGeneratorImpl::has3DCoordinates(const Chem::Atom& atom) const
{
	return coreAtomMask.test(molGraph->getAtomIndex(atom));
}

bool ConfGen::ConformerGeneratorImpl::compareConfCombinationEnergy(const ConfCombinationData* comb1, 
																   const ConfCombinationData* comb2)
{
	return (comb1->energy < comb2->energy);
}

bool ConfGen::ConformerGeneratorImpl::compareFragmentConfCount(const FragmentConfDataPtr& conf_data1, 
															   const FragmentConfDataPtr& conf_data2)
{
	return (conf_data1->conformers.size() < conf_data2->conformers.size());
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
