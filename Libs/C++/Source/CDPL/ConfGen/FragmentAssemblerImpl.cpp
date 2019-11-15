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
#include "CDPL/Math/Quaternion.hpp"

#include "FragmentAssemblerImpl.hpp"
#include "FragmentTreeNode.hpp"
#include "TorsionLibraryDataReader.hpp"
#include "FallbackTorsionLibrary.hpp"


using namespace CDPL;


namespace
{

   const char* ASSEMBLER_TORSION_RULES = 
	   " <library name=\"FragmentAssemblerRules\">"
	   "  <category name=\"GG\" atomType1=\"*\" atomType2=\"*\">"
	   "   <rule pattern=\"[*,#1:1]~[*X3:2]=[*X2:3]=[*X3]~[*,#1:4]\">"
	   "    <torsions>"
	   "     <angle value=\"90.0\" tolerance1=\"0.0\" tolerance2=\"0.0\" score=\"0.0\"/>"
	   "    </torsions>"
	   "   </rule>"
	   "   <rule pattern=\"[*,#1:1]~[*X3:2]=[*X2:3]=[*X2]=[*X3]~[*,#1:4]\">"
	   "    <torsions>"
	   "     <angle value=\"0.0\" tolerance1=\"0.0\" tolerance2=\"0.0\" score=\"0.0\"/>"
	   "    </torsions>"
	   "   </rule>"
	   "  </category"
	   " </library>";

    ConfGen::TorsionLibrary::SharedPointer assemblerTorLib(new ConfGen::TorsionLibrary());

	struct Init {

		Init() {
			ConfGen::TorsionLibraryDataReader().read(ASSEMBLER_TORSION_RULES, *assemblerTorLib);
		}
	};

	const std::size_t MAX_TREE_CONF_DATA_CACHE_SIZE       = 10000;
	const std::size_t MAX_CHAIN_TREE_CONF_DATA_CACHE_SIZE = 100;
	const std::size_t MAX_CONF_DATA_CACHE_SIZE            = 5000;

	const double MAX_PLANAR_ATOM_GEOM_OOP_ANGLE     = 15.0 / 180.0 * M_PI;
}


ConfGen::FragmentAssemblerImpl::FragmentAssemblerImpl():
	confDataCache(MAX_CONF_DATA_CACHE_SIZE), fragTree(MAX_TREE_CONF_DATA_CACHE_SIZE), 
	chainFragTree(MAX_CHAIN_TREE_CONF_DATA_CACHE_SIZE)
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
													  const MMFF94InteractionData& ia_data,
													  bool recalc_subst_blks)
{
	usedMMFF94Data = &ia_data;
	recalcSubstBlks = recalc_subst_blks;

	return doAssemble(molgraph, parent_molgraph);
}

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph)
{
	usedMMFF94Data = 0;
	recalcSubstBlks = true;

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

void ConfGen::FragmentAssemblerImpl::init(const Chem::MolecularGraph& parent_molgraph)
{
	fragConfGen.getSettings() = settings.getFragmentBuildSettings();

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
		unsigned int ret_code = getFragmentConformers();
		
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

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molgraph.getBond(i);

		if (!isFragmentLinkBond(bond, molgraph))
			continue;

		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (!getAromaticityFlag(atom1) && !getAromaticityFlag(atom2) && isHydrogenRotor(bond, molgraph))
			continue;
		
		fragSplitBondMask.set(i);
		fragSplitBonds.push_back(&bond);
	}

	splitIntoFragments(molgraph, fragments, fragSplitBondMask, false);

	fragTree.build(fragments, parent_molgraph, fragSplitBonds.begin(), fragSplitBonds.end());
}

unsigned int ConfGen::FragmentAssemblerImpl::getFragmentConformers() 
{
	using namespace Chem;

	for (std::size_t i = 0, num_frags = fragTree.getNumFragments(); i < num_frags; i++) {
		const Fragment& frag = *fragTree.getFragment(i); 
		FragmentTreeNode* frag_node = fragTree.getFragmentNode(i); 
		unsigned int frag_type = perceiveFragmentType(frag);

		if (!(!settings.generateCoordinatesFromScratch() && 
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

		else if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM && !settings.enumerateRings()) {
			if (hasConformerEnergies(*entry_ptr)) {
				const Math::DVector& energies = *getConformerEnergies(*entry_ptr);
				double lowest_e = energies[0];

				for (std::size_t i = 1; i < num_confs; i++) {
					if (energies[i] > lowest_e) {
						num_confs = i;
						break;
					}
				}

			} else
				num_confs = 1;
		}

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
	std::size_t num_confs = fragConfGen.getNumConformers();

	if (frag_type == FragmentType::FLEXIBLE_RING_SYSTEM && !settings.enumerateRings()) {
		double lowest_e = fragConfGen.getConformer(0).getEnergy();

		for (std::size_t i = 1; i < num_confs; i++) {
			if (fragConfGen.getConformer(i).getEnergy() > lowest_e) {
				num_confs = i;
				break;
			}
		}
	}

	for (std::size_t i = 0; i < num_confs; i++) {
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
	using namespace Chem;

	fragSplitBonds.clear();
	fragSplitBondMask.resize(frag.getNumBonds());
	fragSplitBondMask.reset();

	bool have_inv_n = (getInvertibleNitrogens(frag, node) > 0);
	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();
	
	if (have_inv_n)
		for (Util::BitSet::size_type i = invertedNMask.find_first(); i != Util::BitSet::npos; i = invertedNMask.find_next(i))
			getNeighborSplitBonds(parent_molgraph.getAtom(i), frag);

	bool need_atom_config_changes = false;
	bool need_bond_config_changes = false;

	if (fix_stereo)
		need_atom_config_changes = checkChainAtomConfigurations(have_inv_n, frag, node);

	if (fix_stereo || opt_db_stereo) 
		need_bond_config_changes = checkChainBondConfigurations(fix_stereo, opt_db_stereo, frag, node);

	if (fragSplitBonds.empty()) {
		if (need_atom_config_changes)
			mirrorCoordinates(*node->getConformers().front(), node);

		else if (have_inv_n)
			copyAndMirrorCoordinates(*node->getConformers().front(), node);

		return;
	}

	splitIntoFragments(frag, fragments, fragSplitBondMask, false);
	chainFragTree.build(fragments, parent_molgraph, fragSplitBonds.begin(), fragSplitBonds.end());

	const ConformerData::SharedPointer& conf = node->getConformers().front();

	for (std::size_t i = 0, num_frags = chainFragTree.getNumFragments(); i < num_frags; i++) {
		FragmentTreeNode* frag_node = chainFragTree.getFragmentNode(i); 

		if (need_atom_config_changes) {
			tmpBitSet = frag_node->getCoreAtomMask();
			tmpBitSet &= atomConfigChgMask;

			if (tmpBitSet.any()) {
				copyAndMirrorCoordinates(*conf, frag_node);
				continue;
			}
		} 

		if (have_inv_n) {
			tmpBitSet = frag_node->getCoreAtomMask();
			tmpBitSet &= invertedNMask;

			if (tmpBitSet.any()) {
				frag_node->addConformer(*conf);
				copyAndMirrorCoordinates(*conf, frag_node);
				continue;
			}
		}

		frag_node->addConformer(*conf);
	}

	assignChainSplitBondTorsions(need_bond_config_changes, *conf, chainFragTree.getRoot());

	chainFragTree.getRoot()->generateConformers(false);

	bool first_conf = true;

	for (std::size_t i = 0, num_gen_confs = chainFragTree.getRoot()->getNumConformers(); i < num_gen_confs; i++) {
		const ConformerData::SharedPointer& gen_conf = chainFragTree.getRoot()->getConformers()[i];

		if (first_conf) {
			conf->swap(*gen_conf);
			first_conf = false;
			continue;
		}

		ConformerData::SharedPointer new_conf = allocConformerData();

		new_conf->swap(*gen_conf);
		node->addConformer(new_conf);
	}
}

bool ConfGen::FragmentAssemblerImpl::checkChainAtomConfigurations(bool have_inv_n, const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	const Math::Vector3DArray& coords = *node->getConformers().front();
	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();
	bool need_config_changes = false;

	atomConfigChgMask.resize(parent_molgraph.getNumAtoms());
	atomConfigChgMask.reset();

	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();

	for (std::size_t i = 0, num_atoms = frag.getNumAtoms(); i < num_atoms; i++) {
		if (have_inv_n && invertedNMask.test(atom_inds[i]))
			continue;

		const Atom& atom = frag.getAtom(i);
				
		if (!isStereoCenter(atom, frag, false))
			continue;

		const StereoDescriptor& descr = getStereoDescriptor(atom);
		unsigned int config = descr.getConfiguration();

		if (config != AtomConfiguration::R && config != AtomConfiguration::S)
			continue;

		if (!descr.isValid(atom))
			continue;

		std::size_t num_ref_atoms = descr.getNumReferenceAtoms();
		const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();
		bool descr_valid = true;

		for (std::size_t i = 0; i < num_ref_atoms; i++) {
			if (!frag.containsAtom(*ref_atoms[i])) {
				descr_valid = false;
				break;
			}
		}

		if (!descr_valid)
			continue;

		if (calcAtomConfiguration(atom, parent_molgraph, descr, coords) == config) 
			continue;
			
		atomConfigChgMask.set(atom_inds[i]);
		need_config_changes = true;

		getNeighborSplitBonds(atom, frag);
	}

	return need_config_changes;
}

bool ConfGen::FragmentAssemblerImpl::checkChainBondConfigurations(bool check_stereo, bool opt_stereo, 
																  const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	const Math::Vector3DArray& coords = *node->getConformers().front();
	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();
	bool need_config_changes = false;

	bondConfigChgMask.resize(parent_molgraph.getNumBonds());
	bondConfigChgMask.reset();

	for (std::size_t i = 0, num_bonds = frag.getNumBonds(); i < num_bonds; i++) {
		const Bond& bond = frag.getBond(i);

		if (!isStereoCenter(bond, frag, false, 0))
			continue;

		const StereoDescriptor& descr = getStereoDescriptor(bond);
		unsigned int config = descr.getConfiguration();

		if ((config == BondConfiguration::CIS || config == BondConfiguration::TRANS) && descr.isValid(bond)) {
			const Atom* const* ref_atoms = descr.getReferenceAtoms();
			bool descr_valid = true;
	
			for (std::size_t i = 0; i < 4; i++) {
				if (!frag.containsAtom(*ref_atoms[i])) {
					descr_valid = false;
					break;
				}
			}

			if (descr_valid) {
				if (check_stereo) {
					if (calcBondConfiguration(bond, parent_molgraph, descr, coords) == config)
						continue;

					fragSplitBonds.push_back(&bond);
					fragSplitBondMask.set(i);
					bondConfigChgMask.set(parent_molgraph.getBondIndex(bond));
					need_config_changes = true;
				}

				continue;
			}
		} 

		if (!opt_stereo)
			continue;

		// choose trans config of bulkiest substituents

		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();
	
		const Atom* subst1_atom = getBulkiestDoubleBondSubstituent(atom1, atom2, frag);

		if (!subst1_atom)
			continue;

		const Atom* subst2_atom = getBulkiestDoubleBondSubstituent(atom2, atom1, frag);

		if (!subst2_atom)
			continue;

		if (calcBondConfiguration(bond, parent_molgraph, 
								  StereoDescriptor(BondConfiguration::TRANS, *subst1_atom, atom1, atom2, *subst2_atom), 
								  coords) == BondConfiguration::TRANS)
			continue;

		fragSplitBonds.push_back(&bond);
		fragSplitBondMask.set(i);
		bondConfigChgMask.set(parent_molgraph.getBondIndex(bond));
		need_config_changes = true;
	}

	return need_config_changes;
}

void ConfGen::FragmentAssemblerImpl::getNeighborSplitBonds(const Chem::Atom& atom, const Chem::Fragment& frag)
{
	using namespace Chem;

	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
			continue;

		if (getHeavyBondCount(nbr_atom, frag) < 2)
			continue;

		fragSplitBonds.push_back(&bond);
		fragSplitBondMask.set(frag.getBondIndex(bond));
	} 
}

const Chem::Atom* ConfGen::FragmentAssemblerImpl::getBulkiestDoubleBondSubstituent(const Chem::Atom& atom, const Chem::Atom& db_nbr_atom, 
																				   const Chem::Fragment& frag)
{
	using namespace Chem;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	const Atom* bkst_subst = 0;
	std::size_t bkst_subst_bks = 0;
	std::size_t bond_cnt = 0;

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (&nbr_atom == &db_nbr_atom)
			continue;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(*b_it))
			continue;

		if (++bond_cnt > 2)
			return 0;

		std::size_t nbr_bks = getSubstituentBulkiness(nbr_atom);

		if (!bkst_subst || nbr_bks > bkst_subst_bks) {
			bkst_subst = &nbr_atom;
			bkst_subst_bks = nbr_bks;

		} else if (bkst_subst_bks == nbr_bks)
			return 0;
	}

	return bkst_subst;
}

const Chem::Atom* ConfGen::FragmentAssemblerImpl::getBulkiestSubstituent(const Chem::Atom& atom, const Chem::Atom& excl_atom, 
																		 FragmentTreeNode* node)
{
	using namespace Chem;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();

	const Atom* bkst_subst = 0;
	std::size_t bkst_subst_bks = 0;

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (&nbr_atom == &excl_atom)
			continue;

		if (!node->containsAtom(nbr_atom))
			continue;

		if (!parent_molgraph.containsBond(*b_it))
			continue;

		std::size_t nbr_bks = getSubstituentBulkiness(nbr_atom);

		if (!bkst_subst || nbr_bks > bkst_subst_bks) {
			bkst_subst = &nbr_atom;
			bkst_subst_bks = nbr_bks;

		} else if (bkst_subst_bks == nbr_bks)
			return 0;
	}

	return bkst_subst;
}

std::size_t ConfGen::FragmentAssemblerImpl::getSubstituentBulkiness(const Chem::Atom& atom)
{
	const Chem::MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();

	if (recalcSubstBlks) {
		substBulkCalc.calculate(parent_molgraph);
		recalcSubstBlks = false;
	}

	return substBulkCalc[parent_molgraph.getAtomIndex(atom)];
}

void ConfGen::FragmentAssemblerImpl::mirrorCoordinates(Math::Vector3DArray& coords, FragmentTreeNode* node) const
{
	Math::Vector3DArray::StorageType& coords_data = coords.getData();
	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();

	for (FragmentTreeNode::IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) 
		coords_data[*it].getData()[2] *= -1.0;
}

void ConfGen::FragmentAssemblerImpl::copyAndMirrorCoordinates(const Math::Vector3DArray& coords, FragmentTreeNode* node)
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();

	ConformerData::SharedPointer mirr_coords = allocConformerData();
	Math::Vector3DArray::StorageType& mirr_coords_data = mirr_coords->getData();

	for (FragmentTreeNode::IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		std::size_t idx = *it;
		Math::Vector3D::ConstPointer pos_data = coords_data[idx].getData();
		Math::Vector3D::Pointer mirr_pos_data = mirr_coords_data[idx].getData();

		mirr_pos_data[0] = pos_data[0];
		mirr_pos_data[1] = pos_data[1];
		mirr_pos_data[2] = -pos_data[2];
	}

	node->addConformer(mirr_coords);
}

void ConfGen::FragmentAssemblerImpl::assignChainSplitBondTorsions(bool bond_config_changes, const Math::Vector3DArray& coords, 
																  FragmentTreeNode* node) const
{
	using namespace Chem;

	if (!node->hasChildren())
		return;

	assignChainSplitBondTorsions(bond_config_changes, coords, node->getLeftChild());
	assignChainSplitBondTorsions(bond_config_changes, coords, node->getRightChild());

	const Bond* bond = node->getSplitBond();

	if (!bond)
		return;

	const Atom* const* bond_atoms = node->getSplitBondAtoms();
	const Atom* ref_atom1 = getFirstNeighborAtom(bond_atoms[0], bond_atoms[1], node);

	if (!ref_atom1)
		return;

	const Atom* ref_atom2 = getFirstNeighborAtom(bond_atoms[1], bond_atoms[0], node);

	if (!ref_atom2)
		return;

	node->setTorsionReferenceAtoms(ref_atom1, ref_atom2);

	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();

	double tor_angle = std::acos(ForceField::calcDihedralAngleCos<double>(coords_data[parent_molgraph.getAtomIndex(*ref_atom1)].getData(),
																		  coords_data[parent_molgraph.getAtomIndex(*bond_atoms[0])].getData(), 
																		  coords_data[parent_molgraph.getAtomIndex(*bond_atoms[1])].getData(), 
																		  coords_data[parent_molgraph.getAtomIndex(*ref_atom2)].getData()));

	FragmentTreeNode::TorsionAngleArray& tor_angles = node->getTorsionAngles();

	if (bond_config_changes && bondConfigChgMask.test(parent_molgraph.getBondIndex(*bond)))
		tor_angles.push_back(tor_angle * 180.0 / M_PI + 180.0);
	else
		tor_angles.push_back(-tor_angle * 180.0 / M_PI + 180.0);
}

const Chem::Atom* ConfGen::FragmentAssemblerImpl::getFirstNeighborAtom(const Chem::Atom* ctr_atom, const Chem::Atom* excl_atom,
																	   const FragmentTreeNode* node) const
{
	using namespace Chem;

	Atom::ConstBondIterator b_it = ctr_atom->getBondsBegin();
	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();

	for (Atom::ConstAtomIterator a_it = ctr_atom->getAtomsBegin(), a_end = ctr_atom->getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (excl_atom == &nbr_atom)
			continue;

		if (!parent_molgraph.containsBond(*b_it))
			continue;

		if (node->containsAtom(nbr_atom))
			return &nbr_atom;
	}

	return 0;
}

void ConfGen::FragmentAssemblerImpl::enumRingFragmentNitrogens(const Chem::Fragment& frag, FragmentTreeNode* node)
{
	using namespace Chem;

	if (getInvertibleNitrogens(frag, node) == 0) 
		return;

	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();
	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();

	Math::Vector3D ring_atom1_vec;
	Math::Vector3D ring_atom2_vec;
	Math::Vector3D subst_atom_vec;
	Math::Vector3D plane_normal;
	Math::Vector3D rot_axis;
	Math::DQuaternion rot_quat;
	std::size_t num_atoms = atom_inds.size();

	tmpBitSet.resize(num_atoms);

	for (Util::BitSet::size_type i = invertedNMask.find_first(); i != Util::BitSet::npos; i = invertedNMask.find_next(i)) {
		const Atom& atom = parent_molgraph.getAtom(i);
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

		std::size_t atom_idx = frag.getAtomIndex(atom);

		tmpBitSet.reset();
		tmpBitSet.set(atom_idx);

		markReachableAtoms(*subst_nbr, frag, tmpBitSet, false);

		tmpBitSet.reset(atom_idx);

		std::size_t ring_nbr1_idx = parent_molgraph.getAtomIndex(*ring_nbr1);
		std::size_t ring_nbr2_idx = parent_molgraph.getAtomIndex(*ring_nbr2);
		std::size_t subst_nbr_idx = parent_molgraph.getAtomIndex(*subst_nbr);

		for (std::size_t j = 0, num_confs = node->getNumConformers(); j < num_confs; j++) {
			const Math::Vector3DArray::StorageType& conf_coords_data = node->getConformers()[j]->getData();
			const Math::Vector3D& ctr_atom_pos = conf_coords_data[i];
			
			ring_atom1_vec.assign(conf_coords_data[ring_nbr1_idx] - ctr_atom_pos);
			ring_atom2_vec.assign(conf_coords_data[ring_nbr2_idx] - ctr_atom_pos);
			plane_normal.assign(crossProd(ring_atom1_vec, ring_atom2_vec));

			double plane_normal_norm = length(plane_normal);

			if (plane_normal_norm == 0.0) // sanity check
				continue;

			subst_atom_vec.assign(conf_coords_data[subst_nbr_idx] - ctr_atom_pos);

			double subst_atom_vec_norm = length(subst_atom_vec);

			if (subst_atom_vec_norm == 0.0) // sanity check
				continue;

			double oop_angle = M_PI * 0.5 - std::acos(angleCos(subst_atom_vec, plane_normal, plane_normal_norm * subst_atom_vec_norm, true));

			rot_axis.assign(crossProd(subst_atom_vec, plane_normal));

			double rot_axis_norm = length(rot_axis);

			if (rot_axis_norm == 0.0) // sanity check
				continue;

			double cos_w2 = std::cos(-oop_angle);
			double sin_w2 = std::sin(-oop_angle);

			rot_quat.set(cos_w2, sin_w2 * rot_axis[0] / rot_axis_norm, sin_w2 * rot_axis[1] / rot_axis_norm, 
						 sin_w2 * rot_axis[2] / rot_axis_norm); // rotate by -2 * oop_angle

			ConformerData::SharedPointer inv_n_conf = allocConformerData();
			Math::Vector3DArray::StorageType& inv_n_conf_coords_data = inv_n_conf->getData();

			for (std::size_t k = 0; k < num_atoms; k++) {
				atom_idx = atom_inds[k];

				if (!tmpBitSet.test(k)) {
					inv_n_conf_coords_data[atom_idx].assign(conf_coords_data[atom_idx]);
					continue;
				}

				const Math::Vector3D& subst_atom_pos = conf_coords_data[atom_idx];

				subst_atom_vec.assign(subst_atom_pos - ctr_atom_pos);

				inv_n_conf_coords_data[atom_idx].assign(rotate(rot_quat, subst_atom_vec) + ctr_atom_pos);
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

	const Math::Vector3DArray::StorageType& coords_data = node->getConformers().front()->getData();
	const Util::BitSet& core_atom_mask = node->getCoreAtomMask();
	const FragmentTreeNode::IndexArray& atom_inds = node->getAtomIndices();
	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();

	invertedNMask.resize(parent_molgraph.getNumAtoms());
	invertedNMask.reset();

	std::size_t inv_n_cnt = 0;

	for (std::size_t i = 0, num_atoms = frag.getNumAtoms(); i < num_atoms; i++) {
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

			if (getRingFlag(bond) && ++ring_bond_count > 2)
				break;

			if (getType(nbr_atom) == AtomType::H && (++h_bond_count > 1))
				break;

			nbr_atom_indices[j++] = parent_molgraph.getAtomIndex(nbr_atom);
		}

		if (j != 3)
			continue;

		double oop_angle = ForceField::calcOutOfPlaneAngle<double>(coords_data[nbr_atom_indices[0]].getData(), coords_data[parent_atom_idx].getData(),
																   coords_data[nbr_atom_indices[1]].getData(), coords_data[nbr_atom_indices[2]].getData());

		if (std::abs(oop_angle) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE) 
			continue;

		invertibleNMask.set(parent_atom_idx);

		if (n_enum_mode == NitrogenEnumerationMode::UNSPECIFIED_STEREO) {
			const StereoDescriptor& descr = getStereoDescriptor(atom);
			unsigned int config = descr.getConfiguration();

			if (descr.isValid(atom) && (config == AtomConfiguration::R || config == AtomConfiguration::S)) {
				std::size_t num_ref_atoms = descr.getNumReferenceAtoms();
				const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();
				bool descr_valid = true;

				for (std::size_t j = 0; j < num_ref_atoms; j++) {
					if (!frag.containsAtom(*ref_atoms[j])) {
						descr_valid = false;
						break;
					}
				}

				if (descr_valid)
					continue;
			}
		}

		invertedNMask.set(parent_atom_idx);
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
	using namespace Chem;

	if (!node->hasChildren())
		return;

	assignLinkBondTorsions(node->getLeftChild());
	assignLinkBondTorsions(node->getRightChild());

	const Bond* bond = node->getSplitBond();

	if (!bond)
		return;

	const Atom* const* bond_atoms = node->getSplitBondAtoms();
	FragmentTreeNode::TorsionAngleArray& tor_angles = node->getTorsionAngles();

	const TorsionRuleMatch* match = getMatchingTorsionRule(*bond);

	if (match && match->getRule().getNumAngles() > 0) {
		tor_angles.push_back(match->getRule().getAngle(0).getAngle());

		const Atom* const* match_atoms = match->getAtoms();
				
		if (match_atoms[1] == bond_atoms[0])
			node->setTorsionReferenceAtoms(match_atoms[0], match_atoms[3]);
		else
			node->setTorsionReferenceAtoms(match_atoms[3], match_atoms[0]);
	
		return;
	}

	const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();

	if (isStereoCenter(*bond, parent_molgraph, false, 0)) {
		// torsion setup for stereo double bonds

		const StereoDescriptor& descr = getStereoDescriptor(*bond);
		const Atom* const* ref_atoms = descr.getReferenceAtoms();
		unsigned int config = descr.getConfiguration();
		bool descr_valid = true;

		if ((config == BondConfiguration::CIS || config == BondConfiguration::TRANS) && descr.isValid(*bond)) {
			for (std::size_t i = 0; i < 4; i++) {
				if (!node->containsAtom(*ref_atoms[i])) {
					descr_valid = false;
					break;
				}
			}
		
			if (descr_valid) {
				// choose angle that results in desired configuration

				if (ref_atoms[1] == bond_atoms[0])
					node->setTorsionReferenceAtoms(ref_atoms[0], ref_atoms[3]);
				else
					node->setTorsionReferenceAtoms(ref_atoms[3], ref_atoms[0]);

				tor_angles.push_back(config == BondConfiguration::CIS ? 0.0 : 180.0);
				return;
			}
		} 
	}

	// choose trans configuration of bulkiest substituents

	const Atom* ref_atom1 = getBulkiestSubstituent(*bond_atoms[0], *bond_atoms[1], node);

	if (!ref_atom1)
		return;

	const Atom* ref_atom2 = getBulkiestSubstituent(*bond_atoms[1], *bond_atoms[0], node);

	if (!ref_atom2)
		return;

	node->setTorsionReferenceAtoms(ref_atom1, ref_atom2);
	tor_angles.push_back(180.0);
}

const ConfGen::TorsionRuleMatch* ConfGen::FragmentAssemblerImpl::getMatchingTorsionRule(const Chem::Bond& bond)
{
	const Chem::MolecularGraph& molgraph = *fragTree.getMolecularGraph();

	torRuleMatcher.setTorsionLibrary(assemblerTorLib);

	if (torRuleMatcher.findMatches(bond, molgraph, false)) 
		return &torRuleMatcher.getMatch(0); 
	
	torRuleMatcher.setTorsionLibrary(getFallbackTorsionLibrary());

	if (torRuleMatcher.findMatches(bond, molgraph, false)) 
		return &torRuleMatcher.getMatch(0); 

	return 0;
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
