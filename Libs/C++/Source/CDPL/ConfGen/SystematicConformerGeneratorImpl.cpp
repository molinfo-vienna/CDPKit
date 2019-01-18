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

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"

#include "SystematicConformerGeneratorImpl.hpp"

//#include <iostream>
using namespace CDPL;


ConfGen::SystematicConformerGeneratorImpl::SystematicConformerGeneratorImpl()
{
	fragConfGen.reuseExistingCoordinates(false);
}

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
	init();

	buildTree(molgraph);
	setFragmentCoordinates();

	return Status::ERROR;
}

void ConfGen::SystematicConformerGeneratorImpl::init()
{
	timer.start();	

	freeCoordArrays = allocCoordArrays;
}

bool ConfGen::SystematicConformerGeneratorImpl::timeoutExceeded() const
{
	if (settings.getTimeout() == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(settings.getTimeout()) * 1000000));
}

void ConfGen::SystematicConformerGeneratorImpl::buildTree(const Chem::MolecularGraph& molgraph)
{
	getFragmentLinkBonds(molgraph);

	fragTree.splitRecursive(molgraph, bonds); // build tree according to build fragment link bonds

	buildFragNodes.clear();
	fragTree.getLeafNodes(buildFragNodes);    // get build fragment nodes

	genChainBuildFragmentSubtrees();
/*
	std::cerr << "digraph FragmentTree" << std::endl;
	std::cerr << '{' << std::endl;

	fragTree.printTree(std::cerr);

	std::cerr << '}' << std::endl;
*/
}

bool ConfGen::SystematicConformerGeneratorImpl::setFragmentCoordinates()
{
	for (NodeList::const_iterator it = buildFragNodes.begin(), end = buildFragNodes.end(); it != end; ++it) {
		FragmentTreeNode* node = *it;

		if (settings.existingCoordinatesReused() && 
			(!settings.ringsEnumerated() || node->getFragmentType() != FragmentType::FLEXIBLE_RING_SYSTEM) && 
			applyExistingCoordinates(*node))
			continue;
		
		if (applyFragmentLibraryCoordinates(*node))
			continue;

		if (!generateFragmentCoordinates(*node))
			return false;
	}

	return timeoutExceeded();
}

bool ConfGen::SystematicConformerGeneratorImpl::applyExistingCoordinates(FragmentTreeNode& node)
{
	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::applyFragmentLibraryCoordinates(FragmentTreeNode& node)
{
	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::generateFragmentCoordinates(FragmentTreeNode& node)
{
	return false;
}

void ConfGen::SystematicConformerGeneratorImpl::genChainBuildFragmentSubtrees()
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

		if (!bonds.empty())
			node->splitRecursive(frag, bonds);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getFragmentLinkBonds(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	bonds.clear();	

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

			if (!h_rotors)
				continue;
		}

		bonds.push_back(&bond);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getRotatableBonds(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	bonds.clear();	

	bool h_rotors = settings.hydrogenRotorsEnabled();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
	
		if (isRotatable(bond, molgraph, h_rotors, false, true)) 
			bonds.push_back(&bond);
	}
}

Math::Vector3DArray::SharedPointer ConfGen::SystematicConformerGeneratorImpl::allocVector3DArray()
{
	return Math::Vector3DArray::SharedPointer();
}

void ConfGen::SystematicConformerGeneratorImpl::freeVector3DArray(const Math::Vector3DArray::SharedPointer& vec_array)
{
	freeCoordArrays.push_back(vec_array);
}
