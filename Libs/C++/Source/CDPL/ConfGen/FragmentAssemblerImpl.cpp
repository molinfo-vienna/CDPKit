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

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/Exceptions.hpp"

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
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssemblerImpl::getAbortCallback() const
{
	return abortCallback;
}

void ConfGen::FragmentAssemblerImpl::setTimeoutCallback(const CallbackFunction& func)
{
	timeoutCallback = func;

	fragTree.setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssemblerImpl::getTimeoutCallback() const
{
	return timeoutCallback;
}

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph)
{
	if (!mmff94Parameterizer.get())
		mmff94Parameterizer.reset(new ForceField::MMFF94InteractionParameterizer());

	if (!mmff94Data.get())
		mmff94Data.reset(new ForceField::MMFF94InteractionData());

	mmff94Parameterizer->strictParameterization(settings.strictForceFieldParameterization());

	try {
		if (parameterizeMMFF94Interactions(molgraph, *mmff94Parameterizer, *mmff94Data, settings.getForceFieldType()) != ReturnCode::SUCCESS)
			return ReturnCode::FORCEFIELD_SETUP_FAILED;

	} catch (const ForceField::Error&) {
		return ReturnCode::FORCEFIELD_SETUP_FAILED;
	}

	return assemble(molgraph, *mmff94Data);
}

unsigned int ConfGen::FragmentAssemblerImpl::assemble(const Chem::MolecularGraph& molgraph, 
					  const ForceField::MMFF94InteractionData& ia_data)
{
	clear();

	buildFragmentTree(molgraph);
	extractBuildFragments(fragTree.getRoot());
	setBuildFragmentMMFF94Parameters(ia_data);
	setFragmentLinkBondLengths(fragTree.getRoot(), ia_data);

	if (abortCallback && abortCallback())
		return ReturnCode::ABORTED;

	if (timeoutCallback && timeoutCallback())
		return ReturnCode::TIMEOUT_EXCEEDED;

	return ReturnCode::SUCCESS;
}

std::size_t ConfGen::FragmentAssemblerImpl::getNumStructures() const
{
	return structures.size();
}

ConfGen::ConformerData& ConfGen::FragmentAssemblerImpl::getStructure(std::size_t idx)
{
	return *structures[idx];
}

ConfGen::FragmentAssemblerImpl::ConstStructureIterator ConfGen::FragmentAssemblerImpl::getStructuresBegin() const
{
	return structures.begin();
}

ConfGen::FragmentAssemblerImpl::ConstStructureIterator ConfGen::FragmentAssemblerImpl::getStructuresEnd() const
{
	return structures.end();
}

ConfGen::FragmentTree& ConfGen::FragmentAssemblerImpl::getFragmentTree()
{
	return fragTree;
}

void ConfGen::FragmentAssemblerImpl::clear()
{
	structures.clear();
	buildFrags.clear();

	confDataCache.putAll();
	buildFragDataCache.putAll();
}

void ConfGen::FragmentAssemblerImpl::buildFragmentTree(const Chem::MolecularGraph& molgraph)
{
	buildFragmentLinkBondMask(molgraph, fragLinkBondMask, true);
	
	fragTree.build(molgraph, molgraph, fragLinkBondMask);
}

void ConfGen::FragmentAssemblerImpl::extractBuildFragments(FragmentTreeNode* node)
{
	if (node->hasChildren()) {
		extractBuildFragments(node->getLeftChild());
		extractBuildFragments(node->getRightChild());
		return;
	}

	BuildFragmentData* frag_data = buildFragDataCache.getRaw();

	frag_data->treeNode = node;
	frag_data->conformers.clear();

	buildFrags.push_back(frag_data);
}

void ConfGen::FragmentAssemblerImpl::setBuildFragmentMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data)
{
	mmff94InteractionMask.setup(ia_data);

	for (BuildFragmentList::iterator it = buildFrags.begin(), end = buildFrags.end(); it != end; ++it)
		(*it)->treeNode->distMMFF94Parameters(ia_data, mmff94InteractionMask);
}

void ConfGen::FragmentAssemblerImpl::setFragmentLinkBondLengths(FragmentTreeNode* node, 
																const ForceField::MMFF94InteractionData& ia_data)
{
	using namespace ForceField;

	if (!node->hasChildren()) 
		return;

	std::size_t atom1_idx = node->getRootMolecularGraph()->getAtomIndex(*node->getSplitBondAtoms()[0]);
	std::size_t atom2_idx = node->getRootMolecularGraph()->getAtomIndex(*node->getSplitBondAtoms()[1]);

	const MMFF94BondStretchingInteractionData& bs_ia_data = ia_data.getBondStretchingInteractions();

	for (Util::BitSet::size_type i = mmff94InteractionMask.bondStretching.find_first(); i != Util::BitSet::npos; 
		 i = mmff94InteractionMask.bondStretching.find_next(i)) {

		const MMFF94BondStretchingInteraction& params = bs_ia_data[i];

		if ((params.getAtom1Index() == atom1_idx && params.getAtom2Index() == atom2_idx) ||
			(params.getAtom1Index() == atom2_idx && params.getAtom2Index() == atom1_idx)) {

			node->setSplitBondLength(params.getReferenceLength());
			mmff94InteractionMask.bondStretching.reset(i);
			break;
		}
	}

	setFragmentLinkBondLengths(node->getLeftChild(), ia_data);
	setFragmentLinkBondLengths(node->getRightChild(), ia_data);
}
