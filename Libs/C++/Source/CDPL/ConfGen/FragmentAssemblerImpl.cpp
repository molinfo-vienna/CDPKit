/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentAssemblerImpl.cpp 
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

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "FragmentAssemblerImpl.hpp"
#include "FragmentTreeNode.hpp"
#include "TorsionLibraryDataReader.hpp"


using namespace CDPL;


namespace
{

	const std::size_t MAX_TREE_CONF_DATA_CACHE_SIZE = 100;
	const std::size_t MAX_CONF_DATA_CACHE_SIZE      = 5000;
}


ConfGen::FragmentAssemblerImpl::FragmentAssemblerImpl():
	confDataCache(MAX_CONF_DATA_CACHE_SIZE), fragTree(MAX_TREE_CONF_DATA_CACHE_SIZE)
{} 

ConfGen::FragmentAssemblerImpl::~FragmentAssemblerImpl() {}

ConfGen::FragmentAssemblerSettings& ConfGen::FragmentAssemblerImpl::getSettings()
{
	return settings;
}

void ConfGen::FragmentAssemblerImpl::setAbortCallback(const CallbackFunction& func)
{
	abortCallback = func;

	fragTree.setAbortCallback(func);
	fragConfGen.setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssemblerImpl::getAbortCallback() const
{
	return abortCallback;
}

void ConfGen::FragmentAssemblerImpl::setTimeoutCallback(const CallbackFunction& func)
{
	timeoutCallback = func;

	fragTree.setTimeoutCallback(func);
	fragConfGen.setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssemblerImpl::getTimeoutCallback() const
{
	return timeoutCallback;
}

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent_molgraph, 
													  const MMFF94InteractionData& ia_data)
{
	parentMolGraph = &parent_molgraph;
	usedMMFF94Data = &ia_data;

	return doAssemble(molgraph);
}

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph)
{
	parentMolGraph = &molgraph;
	usedMMFF94Data = 0;

	return doAssemble(molgraph);
}

std::size_t ConfGen::FragmentAssemblerImpl::getNumConformers() const
{
	return fragTree.getRoot()->getConformers().size();
}

ConfGen::ConformerData& ConfGen::FragmentAssemblerImpl::getConformer(std::size_t idx)
{
	return *fragTree.getRoot()->getConformers()[idx];
}

ConfGen::FragmentAssemblerImpl::ConstConformerIterator ConfGen::FragmentAssemblerImpl::getConformersBegin() const
{
	return fragTree.getRoot()->getConformers().begin();
}

ConfGen::FragmentAssemblerImpl::ConstConformerIterator ConfGen::FragmentAssemblerImpl::getConformersEnd() const
{
	return fragTree.getRoot()->getConformers().end();
}

bool ConfGen::FragmentAssemblerImpl::initialized()
{
	return fragTree.getRoot();
}

void ConfGen::FragmentAssemblerImpl::init()
{
	confDataCache.putAll();
}

unsigned int ConfGen::FragmentAssemblerImpl::doAssemble(const Chem::MolecularGraph& molgraph)
{
	init();
	buildFragmentTree(molgraph);

	try {
		unsigned int ret_code = setupFragmentConformers();
		
		if (ret_code != ReturnCode::SUCCESS)
			return ret_code;

	} catch (const ForceField::Error&) {
		return ReturnCode::FORCEFIELD_SETUP_FAILED;
	}

	assignLinkBondTorsions(fragTree.getRoot());

	return fragTree.getRoot()->generateConformers(false);
}

void ConfGen::FragmentAssemblerImpl::buildFragmentTree(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t num_bonds = molgraph.getNumBonds();

	fragLinkBondMask.resize(num_bonds);
	fragLinkBondMask.reset();
	fragLinkBonds.clear();

	bool enum_n = (settings.getNitrogenEnumerationMode() != NitrogenEnumerationMode::NONE);

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molgraph.getBond(i);

		if (!isFragmentLinkBond(bond, molgraph))
			continue;

		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (!getAromaticityFlag(atom1) && !getAromaticityFlag(atom2) && isHydrogenRotor(bond, molgraph)) {
			if (!enum_n)
				continue;
	
			if (!(getRingFlag(atom1) && getType(atom1) == AtomType::N) && !(getRingFlag(atom2) && getType(atom2) == AtomType::N))
				continue;
		}

		fragLinkBondMask.set(i);
		fragLinkBonds.push_back(&bond);
	}

	splitIntoFragments(molgraph, fragments, fragLinkBondMask, false);

	fragTree.build(fragments, molgraph, fragLinkBonds.begin(), fragLinkBonds.end());
}

unsigned int ConfGen::FragmentAssemblerImpl::setupFragmentConformers() 
{
	using namespace Chem;

	for (std::size_t i = 0, num_frags = fragTree.getNumFragments(); i < num_frags; i++) {
		const Fragment& frag = *fragTree.getFragment(i); 
		FragmentTreeNode* frag_node = fragTree.getFragmentNode(i); 
		unsigned int frag_type = perceiveFragmentType(frag);
		
		if (!(!settings.generateCoordinates() && 
			  (!settings.enumerateRings() || frag_type != FragmentType::FLEXIBLE_RING_SYSTEM) && 
			  transferInputCoordinates(frag, frag_node))) {

			fragLibEntry.create(frag);
			buildFragmentLibraryEntryAtomIndexMap(frag, frag_node);

			if (!fetchConformersFromFragmentLibrary(frag_type, frag_node)) {
				unsigned int ret_code = generateFragmentConformers(frag_type, frag_node);

				if (ret_code != ReturnCode::SUCCESS)
					return ret_code;
			}

			fixBondLengths(frag, frag_node);
		}

		if (abortCallback && abortCallback())
			return ReturnCode::ABORTED;

		if (timeoutCallback && timeoutCallback())
			return ReturnCode::TIMEOUT;	
	}

	return ReturnCode::SUCCESS;
}

bool ConfGen::FragmentAssemblerImpl::transferInputCoordinates(const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	ConformerData::SharedPointer coords = allocConformerData();
	Math::Vector3DArray::StorageType& coords_data = coords->getData();

	try {
		FragmentTreeNode::IndexArray atom_inds = node->getAtomIndices();

		for (std::size_t i = 0, num_atoms = atom_inds.size(); i < num_atoms; i++)
			coords_data[atom_inds[i]].assign(get3DCoordinates(frag.getAtom(i)));

		node->getConformers().push_back(coords);
		return true;

	} catch (const Base::ItemNotFound& e) {
		confDataCache.put();
	}

	return false;
}

bool ConfGen::FragmentAssemblerImpl::fetchConformersFromFragmentLibrary(unsigned int frag_type, FragmentTreeNode* node)
{
	using namespace Chem;

	if (!settings.getFragmentLibrary())
		return false;

	const MolecularGraph::SharedPointer& entry_ptr = settings.getFragmentLibrary()->getEntry(fragLibEntry.getHashCode());

	if (!entry_ptr)
		return false;

	if (entry_ptr->getNumAtoms() != fragLibEntry.getNumAtoms())  // sanity check
		return false;

	std::size_t num_confs = getNumConformations(*entry_ptr);

	if (num_confs == 0)
		return false;

	if (frag_type == FragmentType::CHAIN)
		num_confs = 1;

	for (std::size_t i = 0; i < num_confs; i++) {
		ConformerData::SharedPointer conf_data = allocConformerData();
		Math::Vector3DArray::StorageType& conf_coords_data = conf_data->getData();

		for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
			const IndexPair& idx_mapping = *it;

			conf_coords_data[idx_mapping.second].assign(get3DCoordinatesArray(entry_ptr->getAtom(idx_mapping.first))->getData()[i]);
		}

		node->getConformers().push_back(conf_data);
	}

	return true;
}

unsigned int ConfGen::FragmentAssemblerImpl::generateFragmentConformers(unsigned int frag_type, FragmentTreeNode* node)
{
	if (!fragSSSR)
		fragSSSR.reset(new Chem::SmallestSetOfSmallestRings());

	fragSSSR->perceive(fragLibEntry);
	setSSSR(fragLibEntry, fragSSSR);

	unsigned int ret_code = fragConfGen.generate(fragLibEntry, frag_type);

	if (ret_code != ReturnCode::SUCCESS && ret_code != ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT) 
		return ret_code;

	for (std::size_t i = 0, num_confs = fragConfGen.getNumConformers(); i < num_confs; i++) {
		ConformerData::SharedPointer conf_data = allocConformerData();
		Math::Vector3DArray::StorageType& conf_coords_data = conf_data->getData();
		const Math::Vector3DArray::StorageType& gen_conf_coords_data = fragConfGen.getConformer(i).getData();

		for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
			const IndexPair& idx_mapping = *it;

			conf_coords_data[idx_mapping.second].assign(gen_conf_coords_data[idx_mapping.first]);
		}

		node->getConformers().push_back(conf_data);
	}

	return ReturnCode::SUCCESS;
}

void ConfGen::FragmentAssemblerImpl::fixBondLengths(const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	const Util::BitSet& core_atom_mask = node->getCoreAtomMask();

	ConformerDataArray::iterator confs_beg = node->getConformers().begin();
	ConformerDataArray::iterator confs_end = node->getConformers().end();

	for (Fragment::ConstBondIterator it = frag.getBondsBegin(), end = frag.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		
		if (getRingFlag(bond))
			continue;

		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();
		std::size_t atom1_idx = parentMolGraph->getAtomIndex(atom1);
		std::size_t atom2_idx = parentMolGraph->getAtomIndex(atom2);

		if (getAromaticityFlag(atom2) && getType(atom1) != AtomType::H && getAromaticBondCount(atom2, frag) == 2 && getExplicitBondCount(atom1, frag) == 1) {
			std::swap(atom1_idx, atom2_idx);

		} else if (!(getAromaticityFlag(atom1) && getType(atom2) != AtomType::H && getAromaticBondCount(atom1, frag) == 2 && getExplicitBondCount(atom2, frag) == 1)) {
			if (core_atom_mask.test(atom1_idx)) {
				if (core_atom_mask.test(atom2_idx))
					continue;

			} else if (!core_atom_mask.test(atom2_idx))
				continue;
			else
				std::swap(atom1_idx, atom2_idx);
		}

		double bond_len = getMMFF94BondLength(atom1_idx, atom2_idx);

		if (bond_len <= 0.0)
			continue;

		for (ConformerDataArray::iterator conf_it = confs_beg; conf_it != confs_end; ++conf_it) {
			Math::Vector3DArray::StorageType& conf_coords_data = (*conf_it)->getData();

			conf_coords_data[atom2_idx].minusAssign(conf_coords_data[atom1_idx]);
			conf_coords_data[atom2_idx] *= bond_len / length(conf_coords_data[atom2_idx]);
			conf_coords_data[atom2_idx].plusAssign(conf_coords_data[atom1_idx]);
		}
	}
}

void ConfGen::FragmentAssemblerImpl::buildFragmentLibraryEntryAtomIndexMap(const Chem::Fragment& frag, const FragmentTreeNode* frag_node)
{
	const FragmentTreeNode::IndexArray& atom_inds = frag_node->getAtomIndices();
	const FragmentLibraryEntry::AtomMapping& entry_atom_map = fragLibEntry.getAtomMapping();

	fragLibEntryAtomIdxMap.clear();

	for (std::size_t i = 0, num_atoms = frag.getNumAtoms(); i < num_atoms; i++)
		fragLibEntryAtomIdxMap.push_back(IndexPair(fragLibEntry.getAtomIndex(*entry_atom_map[i]), atom_inds[i]));
}

void ConfGen::FragmentAssemblerImpl::assignLinkBondTorsions(FragmentTreeNode* node) 
{
	// TODO
}

const ForceField::MMFF94InteractionData* ConfGen::FragmentAssemblerImpl::getMMFF94Parameters()
{
	using namespace ForceField;

	if (usedMMFF94Data)
		return usedMMFF94Data;

	if (!mmff94Parameterizer.get())
		mmff94Parameterizer.reset(new MMFF94InteractionParameterizer());

	if (!mmff94Data.get())
		mmff94Data.reset(new MMFF94InteractionData());

	mmff94Parameterizer->strictParameterization(settings.getFragmentBuildSettings().strictForceFieldParameterization());
	mmff94Parameterizer->parameterize(*parentMolGraph, *mmff94Data, InteractionType::BOND_STRETCHING);

	usedMMFF94Data = mmff94Data.get();

	return usedMMFF94Data;
}

double ConfGen::FragmentAssemblerImpl::getMMFF94BondLength(std::size_t atom1_idx, std::size_t atom2_idx)
{
	using namespace ForceField;

	const MMFF94BondStretchingInteractionData& bs_ia_data = getMMFF94Parameters()->getBondStretchingInteractions();

	for (MMFF94BondStretchingInteractionData::ConstElementIterator it = bs_ia_data.getElementsBegin(), end = bs_ia_data.getElementsEnd(); it != end; ++it) { 
		const MMFF94BondStretchingInteraction& params = *it;

		if ((params.getAtom1Index() == atom1_idx && params.getAtom2Index() == atom2_idx) ||
			(params.getAtom1Index() == atom2_idx && params.getAtom2Index() == atom1_idx)) 
			return params.getReferenceLength();
	}

	return 0.0;
}

ConfGen::ConformerData::SharedPointer ConfGen::FragmentAssemblerImpl::allocConformerData()
{
	ConformerData::SharedPointer conf_data = confDataCache.get();

	conf_data->resize(parentMolGraph->getNumAtoms());
	conf_data->setEnergy(0.0);

	return conf_data;
}
