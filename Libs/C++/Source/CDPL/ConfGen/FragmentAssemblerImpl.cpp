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
#include <cmath>

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
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
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

	const double MAX_PLANAR_ATOM_GEOM_OOP_ANGLE     = 15.0 / 180.0 * M_PI;
}


ConfGen::FragmentAssemblerImpl::FragmentAssemblerImpl():
	confDataCache(MAX_CONF_DATA_CACHE_SIZE), fragTree(MAX_TREE_CONF_DATA_CACHE_SIZE)
{
	fragLibs.push_back(FragmentLibrary::get());
} 

ConfGen::FragmentAssemblerImpl::~FragmentAssemblerImpl() {}

ConfGen::FragmentAssemblerSettings& ConfGen::FragmentAssemblerImpl::getSettings()
{
	return settings;
}

void ConfGen::FragmentAssemblerImpl::clearFragmentLibraries()
{
	fragLibs.clear();
}

void ConfGen::FragmentAssemblerImpl::addFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragLibs.push_back(lib);
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

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph, 
													  const Chem::MolecularGraph& parent_molgraph, 
													  const MMFF94InteractionData& ia_data)
{
	usedMMFF94Data = &ia_data;

	return doAssemble(molgraph, parent_molgraph);
}

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph)
{
	usedMMFF94Data = 0;

	return doAssemble(molgraph, molgraph);
}

std::size_t ConfGen::FragmentAssemblerImpl::getNumConformers() const
{
	return fragTree.getRoot()->getNumConformers();
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

void ConfGen::FragmentAssemblerImpl::init(const Chem::MolecularGraph& parent_molgraph)
{
	confDataCache.putAll();

	invertibleNMask.resize(parent_molgraph.getNumAtoms());
	invertibleNMask.reset();
}

unsigned int ConfGen::FragmentAssemblerImpl::doAssemble(const Chem::MolecularGraph& molgraph, 
														const Chem::MolecularGraph& parent_molgraph)
{
	init(parent_molgraph);
	buildFragmentTree(molgraph, parent_molgraph);

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

void ConfGen::FragmentAssemblerImpl::buildFragmentTree(const Chem::MolecularGraph& molgraph, 
													   const Chem::MolecularGraph& parent_molgraph)
{
	using namespace Chem;

	std::size_t num_bonds = molgraph.getNumBonds();

	fragSplitBondMask.resize(num_bonds);
	fragSplitBondMask.reset();
	fragSplitBonds.clear();

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
	
			if (!(getRingFlag(atom1) && getType(atom1) == AtomType::N) &&
				!(getRingFlag(atom2) && getType(atom2) == AtomType::N))
				continue;
		}

		fragSplitBondMask.set(i);
		fragSplitBonds.push_back(&bond);
	}

	splitIntoFragments(molgraph, fragments, fragSplitBondMask, false);

	fragTree.build(fragments, parent_molgraph, fragSplitBonds.begin(), fragSplitBonds.end());
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
			  transferInputCoordinates(frag_type, frag, frag_node))) {

			fragLibEntry.create(frag);
			buildFragmentLibraryEntryAtomIndexMap(frag, frag_node);

			if (!fetchConformersFromFragmentLibrary(frag_type, frag, frag_node)) {
				unsigned int ret_code = generateFragmentConformers(frag_type, frag, frag_node);

				if (ret_code != ReturnCode::SUCCESS)
					return ret_code;
			}
		}

		if (abortCallback && abortCallback())
			return ReturnCode::ABORTED;

		if (timeoutCallback && timeoutCallback())
			return ReturnCode::TIMEOUT;	
	}

	return ReturnCode::SUCCESS;
}

bool ConfGen::FragmentAssemblerImpl::transferInputCoordinates(unsigned int frag_type, const Chem::Fragment& frag, 
															  FragmentTreeNode* node)
{
	using namespace Chem;

	ConformerData::SharedPointer coords = allocConformerData();
	Math::Vector3DArray::StorageType& coords_data = coords->getData();

	try {
		FragmentTreeNode::IndexArray atom_inds = node->getAtomIndices();

		for (std::size_t i = 0, num_atoms = atom_inds.size(); i < num_atoms; i++)
			coords_data[atom_inds[i]].assign(get3DCoordinates(frag.getAtom(i)));

		node->addConformer(coords);

		if (frag_type == FragmentType::CHAIN)
			postprocChainFragment(false, false, frag, node);

		else if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
			enumRingFragmentNitrogens(frag, node);

		return true;

	} catch (const Base::ItemNotFound& e) {
		confDataCache.put();
	}

	return false;
}

bool ConfGen::FragmentAssemblerImpl::fetchConformersFromFragmentLibrary(unsigned int frag_type, const Chem::Fragment& frag, 
																		FragmentTreeNode* node)
{
	using namespace Chem;

	for (FragmentLibraryList::const_iterator it = fragLibs.begin(), end = fragLibs.end(); it != end; ++it) {
		const MolecularGraph::SharedPointer& entry_ptr = (*it)->getEntry(fragLibEntry.getHashCode());

		if (!entry_ptr)
			continue;

		if (entry_ptr->getNumAtoms() != fragLibEntry.getNumAtoms())  // sanity check
			continue;

		std::size_t num_confs = getNumConformations(*entry_ptr);

		if (num_confs == 0)
			continue;

		if (frag_type == FragmentType::CHAIN)
			num_confs = 1;

		ConformerDataArray& node_confs = node->getConformers();

		node_confs.reserve(num_confs);

		for (std::size_t i = 0; i < num_confs; i++)
			node_confs.push_back(allocConformerData());

		for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
			const IndexPair& idx_mapping = *it;
			const Math::Vector3DArray::StorageType& atom_coords_data = get3DCoordinatesArray(entry_ptr->getAtom(idx_mapping.first))->getData();

			for (std::size_t i = 0; i < num_confs; i++)
				node_confs[i]->getData()[idx_mapping.second].assign(atom_coords_data[i]);
		}

		fixBondLengths(frag, node);

		if (frag_type == FragmentType::CHAIN)
			postprocChainFragment(true, true, frag, node);

		else if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
			enumRingFragmentNitrogens(frag, node);

		return true;
	}

	return false;
}

unsigned int ConfGen::FragmentAssemblerImpl::generateFragmentConformers(unsigned int frag_type, const Chem::Fragment& frag, 
																		FragmentTreeNode* node)
{
	if (!fragSSSR)
		fragSSSR.reset(new Chem::SmallestSetOfSmallestRings());

	fragSSSR->perceive(fragLibEntry);
	setSSSR(fragLibEntry, fragSSSR);

	unsigned int ret_code = fragConfGen.generate(fragLibEntry, frag_type);

	if (ret_code != ReturnCode::SUCCESS && ret_code != ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT) 
		return ret_code;

	node->getConformers().reserve(fragConfGen.getNumConformers());

	for (std::size_t i = 0, num_confs = fragConfGen.getNumConformers(); i < num_confs; i++) {
		ConformerData::SharedPointer conf_data = allocConformerData();
		Math::Vector3DArray::StorageType& conf_coords_data = conf_data->getData();
		const Math::Vector3DArray::StorageType& gen_conf_coords_data = fragConfGen.getConformer(i).getData();

		for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
			const IndexPair& idx_mapping = *it;

			conf_coords_data[idx_mapping.second].assign(gen_conf_coords_data[idx_mapping.first]);
		}

		node->addConformer(conf_data);
	}

	fixBondLengths(frag, node);

	if (frag_type == FragmentType::CHAIN)
		postprocChainFragment(false, true, frag, node);

	else if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM)
		enumRingFragmentNitrogens(frag, node);

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
		std::size_t atom1_idx = fragTree.getMolecularGraph()->getAtomIndex(atom1);
		std::size_t atom2_idx = fragTree.getMolecularGraph()->getAtomIndex(atom2);

		if (getAromaticityFlag(atom2) && getType(atom1) != AtomType::H && 
			getAromaticBondCount(atom2, frag) == 2 && getExplicitBondCount(atom1, frag) == 1) {

			std::swap(atom1_idx, atom2_idx);

		} else if (!(getAromaticityFlag(atom1) && getType(atom2) != AtomType::H && 
					 getAromaticBondCount(atom1, frag) == 2 && getExplicitBondCount(atom2, frag) == 1)) {

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

void ConfGen::FragmentAssemblerImpl::postprocChainFragment(bool fix_stereo, bool opt_db_stereo, 
														   const Chem::Fragment& frag, FragmentTreeNode* node)
{
	// TODO
}

void ConfGen::FragmentAssemblerImpl::enumRingFragmentNitrogens(const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	if (getInvertibleNitrogens(frag, node) == 0)
		return;

	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();
	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();

	Math::Vector3D ring_nbr1_vec;
	Math::Vector3D ring_nbr2_vec;
	Math::Vector3D subst_atom_vec;
	Math::Vector3D plane_normal;
	Math::Vector3D::ConstPointer plane_normal_data = plane_normal.getData();

	for (Util::BitSet::size_type i = invertedNMask.find_first(); i != Util::BitSet::npos; i = invertedNMask.find_next(i)) {
		const Atom& atom = frag.getAtom(i);
		const Atom* ring_nbr1 = 0;
		const Atom* ring_nbr2 = 0;
		const Atom* subst_nbr = 0;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;
			const Bond& bond = *b_it;

			if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
				continue;

			if (getRingFlag(bond)) {
				if (!ring_nbr1)
					ring_nbr1 = &nbr_atom;
				else
					ring_nbr2 = &nbr_atom;

			} else 
				subst_nbr = &nbr_atom;
		}

		if (!subst_nbr || !ring_nbr2) // sanity check
			continue;

		std::size_t ctr_atom_idx = atom_inds[i];
		std::size_t ring_nbr1_idx = parent_molgraph.getAtomIndex(*ring_nbr1);
		std::size_t ring_nbr2_idx = parent_molgraph.getAtomIndex(*ring_nbr2);
		std::size_t subst_nbr_idx = parent_molgraph.getAtomIndex(*subst_nbr);

		for (std::size_t j = 0, num_confs = node->getNumConformers(); j < num_confs; j++) {
			const Math::Vector3DArray::StorageType& conf_coords_data = node->getConformers()[j]->getData();
			const Math::Vector3D& ctr_atom_pos = conf_coords_data[ctr_atom_idx];

			ring_nbr1_vec.assign(conf_coords_data[ring_nbr1_idx] - ctr_atom_pos);
			ring_nbr2_vec.assign(conf_coords_data[ring_nbr2_idx] - ctr_atom_pos);
			plane_normal.assign(crossProd(ring_nbr1_vec, ring_nbr2_vec));

			double plane_normal_len = length(plane_normal);

			if (plane_normal_len == 0.0) // sanity check
				continue;

			plane_normal /= plane_normal_len;

			ConformerData::SharedPointer inv_n_conf = allocConformerData();
			Math::Vector3DArray::StorageType& inv_n_conf_coords_data = inv_n_conf->getData();

			for (FragmentTreeNode::IndexArray::const_iterator ai_it = atom_inds.begin(), ai_end = atom_inds.end(); ai_it != ai_end; ++ai_it) {
				std::size_t curr_atom_idx = *ai_it;

				if (curr_atom_idx != subst_nbr_idx) {
					inv_n_conf_coords_data[curr_atom_idx].assign(conf_coords_data[curr_atom_idx]);
					continue;
				}

				const Math::Vector3D& subst_atom_pos = conf_coords_data[curr_atom_idx];

				subst_atom_vec.assign(subst_atom_pos - ctr_atom_pos);

				double plane_dist = innerProd(plane_normal, subst_atom_vec);

				Math::Vector3D::ConstPointer subst_atom_pos_data = subst_atom_pos.getData();
				Math::Vector3D::Pointer inv_n_subst_atom_pos_data = inv_n_conf_coords_data[curr_atom_idx].getData();

				inv_n_subst_atom_pos_data[0] = subst_atom_pos_data[0] - 2.0 * plane_dist * plane_normal_data[0];
				inv_n_subst_atom_pos_data[1] = subst_atom_pos_data[1] - 2.0 * plane_dist * plane_normal_data[1];
				inv_n_subst_atom_pos_data[2] = subst_atom_pos_data[2] - 2.0 * plane_dist * plane_normal_data[2];
			}

			node->addConformer(inv_n_conf);
		}
	}
}

std::size_t ConfGen::FragmentAssemblerImpl::getInvertibleNitrogens(const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	unsigned int n_enum_mode = settings.getNitrogenEnumerationMode();

	if (n_enum_mode == NitrogenEnumerationMode::NONE)
		return 0;

	std::size_t num_atoms = frag.getNumAtoms();

	invertedNMask.resize(num_atoms);
	invertedNMask.reset();

	const Math::Vector3DArray::StorageType& coords_data = node->getConformers().front()->getData();
	const Util::BitSet& core_atom_mask = node->getCoreAtomMask();
	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();

	std::size_t inv_n_cnt = 0;

	for (std::size_t i = 0; i < num_atoms; i++) {
		std::size_t parent_atom_idx = atom_inds[i];

		if (!core_atom_mask.test(parent_atom_idx))
			continue;

		const Atom& atom = frag.getAtom(i);

		if (getType(atom) != AtomType::N)
			continue;

		std::size_t h_bond_count = 0;
		std::size_t ring_bond_count = 0;
		std::size_t nbr_atom_indices[3];
		std::size_t j = 0;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;
			const Bond& bond = *b_it;

			if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
				continue;

			if (j == 3) {
				j = 0;
				break;
			}

			if (getOrder(bond) != 1)
				break;

			if (getRingFlag(bond) && (++ring_bond_count > 2))
				break;

			if (getType(nbr_atom) == AtomType::H && (++h_bond_count > 1))
				break;

			nbr_atom_indices[j++] = fragTree.getMolecularGraph()->getAtomIndex(nbr_atom);
		}

		if (j != 3)
			continue;

		double oop_angle = ForceField::calcOutOfPlaneAngle<double>(coords_data[nbr_atom_indices[0]], coords_data[parent_atom_idx],
																   coords_data[nbr_atom_indices[1]], coords_data[nbr_atom_indices[2]]);

		if (std::abs(oop_angle) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE)
			continue;

		invertibleNMask.set(parent_atom_idx);

		if (n_enum_mode == NitrogenEnumerationMode::UNSPECIFIED_STEREO) {
			const StereoDescriptor& descr = getStereoDescriptor(atom);

			if (descr.isValid(atom) && (descr.getConfiguration() == AtomConfiguration::R || descr.getConfiguration() == AtomConfiguration::S))
				continue;
		}

		invertedNMask.set(i);
		inv_n_cnt++;
	}

	return inv_n_cnt;
}

void ConfGen::FragmentAssemblerImpl::buildFragmentLibraryEntryAtomIndexMap(const Chem::Fragment& frag, 
																		   const FragmentTreeNode* frag_node)
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
	mmff94Parameterizer->parameterize(*fragTree.getMolecularGraph(), *mmff94Data, InteractionType::BOND_STRETCHING);

	usedMMFF94Data = mmff94Data.get();

	return usedMMFF94Data;
}

double ConfGen::FragmentAssemblerImpl::getMMFF94BondLength(std::size_t atom1_idx, std::size_t atom2_idx)
{
	using namespace ForceField;

	const MMFF94BondStretchingInteractionData& bs_ia_data = getMMFF94Parameters()->getBondStretchingInteractions();

	for (MMFF94BondStretchingInteractionData::ConstElementIterator it = bs_ia_data.getElementsBegin(), 
			 end = bs_ia_data.getElementsEnd(); it != end; ++it) { 

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

	conf_data->resize(fragTree.getMolecularGraph()->getNumAtoms());
	conf_data->setEnergy(0.0);

	return conf_data;
}
