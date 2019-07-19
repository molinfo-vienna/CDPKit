/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGeneratorImpl.cpp 
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
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "SystematicConformerGeneratorImpl.hpp"

//#include <iostream>
using namespace CDPL;


ConfGen::SystematicConformerGeneratorImpl::SystematicConformerGeneratorImpl()
{
	fragConfGen.reuseExistingCoordinates(false);
}

ConfGen::SystematicConformerGeneratorImpl::~SystematicConformerGeneratorImpl() {}

void ConfGen::SystematicConformerGeneratorImpl::applySettings(const Settings& settings)
{
	this->settings = settings;
}

const ConfGen::SystematicConformerGeneratorImpl::Settings& 
ConfGen::SystematicConformerGeneratorImpl::getSettings() const
{
	return settings;
}

ConfGen::SystematicConformerGeneratorImpl::Status 
ConfGen::SystematicConformerGeneratorImpl::generate(const Chem::MolecularGraph& molgraph)
{
	timer.start();	

	freeVector3DArrays();
	buildTree(molgraph);
	buildAtomIndexMaps(fragTree);
	clearFragmentConformers(fragTree);

	if (timeoutExceeded())
		return Status::TIMEOUT_EXCEEDED;
	
	if (!setBuildFragmentCoordinates()) {
		if (timeoutExceeded())
			return Status::TIMEOUT_EXCEEDED;

		return Status::ERROR;
	}

	return Status::SUCCESS;
}

void ConfGen::SystematicConformerGeneratorImpl::freeVector3DArrays()
{
	freeCoordArrays.clear();

	std::for_each(allocCoordArrays.begin(), allocCoordArrays.end(), 
				  boost::bind(&SystematicConformerGeneratorImpl::freeVector3DArray, this, 
							  boost::bind<Math::Vector3DArray*>(&Math::Vector3DArray::SharedPointer::get, _1)));
}

bool ConfGen::SystematicConformerGeneratorImpl::timeoutExceeded() const
{
	if (settings.getTimeout() == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(settings.getTimeout()) * 1000000));
}

void ConfGen::SystematicConformerGeneratorImpl::buildTree(const Chem::MolecularGraph& molgraph)
{
	buildFragNodes.clear();

	getFragmentLinkBonds(molgraph);

	fragTree.splitRecursive(molgraph, bondList); // build tree according to build fragment link bonds

	getBuildFragmentNodes(fragTree);

	generateChainBuildFragmentSubtrees();

/*
	std::cerr << "digraph FragmentTree" << std::endl;
	std::cerr << '{' << std::endl;

	fragTree.printTree(std::cerr);

	std::cerr << '}' << std::endl;
*/
}

void ConfGen::SystematicConformerGeneratorImpl::getBuildFragmentNodes(FragmentTreeNode& node)
{
	if (!node.hasChildren()) {
		buildFragNodes.push_back(&node);
		return;
	}

	getBuildFragmentNodes(*node.getLeftChild());
	getBuildFragmentNodes(*node.getRightChild());
}

void ConfGen::SystematicConformerGeneratorImpl::clearFragmentConformers(FragmentTreeNode& node) const
{
	node.clearConformers();

	if (!node.hasChildren())
		return;

	clearFragmentConformers(*node.getLeftChild());
	clearFragmentConformers(*node.getRightChild());
}

bool ConfGen::SystematicConformerGeneratorImpl::setBuildFragmentCoordinates()
{
	for (NodeList::const_iterator it = buildFragNodes.begin(), end = buildFragNodes.end(); it != end; ++it) {
		FragmentTreeNode* node = *it;

		if (settings.existingCoordinatesReused() && 
			(!settings.ringsEnumerated() || node->getFragmentType() != FragmentType::FLEXIBLE_RING_SYSTEM) && 
			setExistingCoordinates(*node))
			continue;
		
		fragLibEntry.create(node->getFragment());

		if (setFragmentLibraryCoordinates(*node))
			continue;

		if (!generateFragmentCoordinates(*node))
			return false;
	}

	return true;
}

bool ConfGen::SystematicConformerGeneratorImpl::setExistingCoordinates(FragmentTreeNode& node)
{
	using namespace Chem;

	try {
		Math::Vector3DArray* coords = allocVector3DArray();
		Vec3DArrayDeallocator dealloc_guard(this, coords);

		const MolecularGraph& frag = node.getFragment();
		const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();

		for (std::size_t i = 0, num_atoms = frag.getNumAtoms(); i < num_atoms; i++) {
			const Atom& atom = frag.getAtom(i);

			(*coords)[atom_idx_map[i]] = get3DCoordinates(atom);
		}

		if (node.getFragmentType() == FragmentType::CHAIN && node.hasChildren())
			distChainBuildFragmentCoordinates(node, *coords, false);

		else {
			node.addConformer(coords);
			dealloc_guard.release();
		}

		return true;

	} catch (const Base::ItemNotFound& e) {}

	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::setFragmentLibraryCoordinates(FragmentTreeNode& node)
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

	if (num_confs < 1)
		return false;

	switch (node.getFragmentType()) {

		case FragmentType::CHAIN: {
			Math::Vector3DArray* coords = allocVector3DArray();
			Vec3DArrayDeallocator dealloc_guard(this, coords);

			getLibraryFragmentConformation(node, *entry_ptr, 0, *coords);

			if (node.hasChildren())
				distChainBuildFragmentCoordinates(node, *coords, true);

			else {
				node.addConformer(coords);
				dealloc_guard.release();
			}

			return true;
		}

		case FragmentType::RIGID_RING_SYSTEM:
			num_confs = 1;

		case FragmentType::FLEXIBLE_RING_SYSTEM: {
			extractAromRingSubstituentBonds(node);

			for (std::size_t  i = 0; i < num_confs; i++) {
				Math::Vector3DArray* coords = allocVector3DArray();
				Vec3DArrayDeallocator dealloc_guard(this, coords);

				getLibraryFragmentConformation(node, *entry_ptr, i, *coords);
				fixAromRingSubstituentBondLengths(*coords);

				node.addConformer(coords);
				dealloc_guard.release();
			}

			return true;
		}
	}

	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::generateFragmentCoordinates(FragmentTreeNode& node)
{
	std::size_t frag_build_to = settings.getMaxFragmentBuildTime();

	if (settings.getTimeout() > 0) {
		std::size_t elapsed_time = timer.elapsed().wall / 1000000;

		if (elapsed_time >= settings.getTimeout())
			return false;

		if (frag_build_to > 0)
			frag_build_to = std::min(frag_build_to, settings.getTimeout() - elapsed_time);
		else
			frag_build_to = settings.getTimeout() - elapsed_time;
	}

	fragConfGen.setTimeout(frag_build_to);

	return true;
}

void ConfGen::SystematicConformerGeneratorImpl::distChainBuildFragmentCoordinates(FragmentTreeNode& node, const Math::Vector3DArray& coords, 
																				  bool fix_stereo)
{
	if (node.hasChildren()) {
		distChainBuildFragmentCoordinates(*node.getLeftChild(), coords, fix_stereo);
		distChainBuildFragmentCoordinates(*node.getRightChild(), coords, fix_stereo);
		return;
	}

	const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();

	Math::Vector3DArray* node_coords = allocVector3DArray();
	Vec3DArrayDeallocator dealloc_guard(this, node_coords);

	for (AtomIndexMap::const_iterator idx_it = atom_idx_map.begin(), idx_end = atom_idx_map.end(); idx_it != idx_end; ++idx_it) {
		std::size_t atom_idx = *idx_it;

		(*node_coords)[atom_idx] = coords[atom_idx];
	}
		
	node.addConformer(node_coords);
	dealloc_guard.release();

	if (fix_stereo)
		fixAtomAndBondConfigurations(node);
}

void ConfGen::SystematicConformerGeneratorImpl::generateChainBuildFragmentSubtrees()
{
	using namespace Chem;

	for (NodeList::const_iterator it = buildFragNodes.begin(), end = buildFragNodes.end(); it != end; ++it) {
		FragmentTreeNode* node = *it;
		const MolecularGraph& frag = node->getFragment();
		unsigned int frag_type = perceiveFragmentType(frag);

		node->setFragmentType(frag_type);

		if (frag_type != FragmentType::CHAIN)
			continue;

		getRotatableBonds(frag);

		if (!bondList.empty())
			node->splitRecursive(frag, bondList);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getLibraryFragmentConformation(FragmentTreeNode& node, const Chem::MolecularGraph& lib_frag, 
																			   std::size_t conf_idx, Math::Vector3DArray& coords) const
{
	// TODO
}

void ConfGen::SystematicConformerGeneratorImpl::fixAtomAndBondConfigurations(FragmentTreeNode& node) const
{
	// TODO
}

void ConfGen::SystematicConformerGeneratorImpl::extractAromRingSubstituentBonds(FragmentTreeNode& node) const
{
	// TODO
}

void ConfGen::SystematicConformerGeneratorImpl::fixAromRingSubstituentBondLengths(Math::Vector3DArray& coords) const
{
	// TODO
}

void ConfGen::SystematicConformerGeneratorImpl::buildAtomIndexMaps(FragmentTreeNode& node) const
{
	node.buildAtomIndexMap();

	if (!node.hasChildren())
		return;

	buildAtomIndexMaps(*node.getLeftChild());
	buildAtomIndexMaps(*node.getRightChild());
}

void ConfGen::SystematicConformerGeneratorImpl::getFragmentLinkBonds(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	bondList.clear();	

	bool h_rotors = settings.hydrogenRotorsEnabled();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (!isFragmentLinkBond(bond, molgraph))
			continue;

		if (isHydrogenRotor(bond, molgraph)) {
			const Atom& atom1 = bond.getBegin();
			const Atom& atom2 = bond.getEnd();

			if (!getRingFlag(atom1) && !getRingFlag(atom2))
				continue;

			if (!h_rotors && !getAromaticityFlag(atom1) && !getAromaticityFlag(atom2)) 
				continue;
		}

		bondList.push_back(&bond);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getRotatableBonds(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	bondList.clear();	

	bool h_rotors = settings.hydrogenRotorsEnabled();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
	
		if (isRotatable(bond, molgraph, h_rotors, false, true)) 
			bondList.push_back(&bond);
	}
}

Math::Vector3DArray* ConfGen::SystematicConformerGeneratorImpl::allocVector3DArray()
{
	if (!freeCoordArrays.empty()) {
		Math::Vector3DArray* vec_array = freeCoordArrays.back();

		vec_array->resize(fragTree.getFragment().getNumAtoms());
		freeCoordArrays.pop_back();

		return vec_array;
	}

	Math::Vector3DArray::SharedPointer vec_array(new Math::Vector3DArray());

	vec_array->resize(fragTree.getFragment().getNumAtoms());
	allocCoordArrays.push_back(vec_array);

	return vec_array.get();
}

void ConfGen::SystematicConformerGeneratorImpl::freeVector3DArray(Math::Vector3DArray* vec_array)
{
	freeCoordArrays.push_back(vec_array);
}
