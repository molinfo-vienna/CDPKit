/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriverImpl.cpp 
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
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/Exceptions.hpp"

#include "TorsionDriverImpl.hpp"
#include "FragmentTreeNode.hpp"
#include "FallbackTorsionLibrary.hpp"


using namespace CDPL;


namespace
{

	struct SymmetryPattern
	{

		Chem::MolecularGraph::SharedPointer pattern;
		std::size_t                         symmetry;
	};

	SymmetryPattern SYMMETRY_PATTERN_LIST[] = {
	    { Chem::parseSMARTS("[*:1]-[c:1]1[cH1][cH1][cH1][cH1][c]1-[*,#1;X1]"), 2 }
	};
	
	const std::size_t MAX_CONF_DATA_CACHE_SIZE = 10000;
}


ConfGen::TorsionDriverImpl::TorsionDriverImpl(): 
	fragTree(MAX_CONF_DATA_CACHE_SIZE)
{} 

ConfGen::TorsionDriverImpl::~TorsionDriverImpl() {}

ConfGen::TorsionDriverSettings& ConfGen::TorsionDriverImpl::getSettings()
{
	return settings;
}

void ConfGen::TorsionDriverImpl::setup(const Chem::MolecularGraph& molgraph)
{
	buildRotatableBondMask(molgraph, tmpBitSet, settings.sampleHeteroAtomHydrogens(), true);
	
	setup(molgraph, tmpBitSet);
}

void ConfGen::TorsionDriverImpl::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask)
{
	splitIntoFragments(molgraph, fragments, bond_mask, false);

	setup(fragments, molgraph, bond_mask);
}

void ConfGen::TorsionDriverImpl::setup(const Chem::FragmentList& frags, const Chem::MolecularGraph& molgraph, 
									   const Util::BitSet& bond_mask)
{
	fragTree.build(fragments, molgraph, bond_mask);

	assignTorsionAngles(fragTree.getRoot());
}

void ConfGen::TorsionDriverImpl::setMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data)
{
	mmff94InteractionMask.setup(ia_data);

	fragTree.getRoot()->distMMFF94Parameters(ia_data, mmff94InteractionMask);
}

bool ConfGen::TorsionDriverImpl::setMMFF94Parameters(const Chem::MolecularGraph& molgraph)
{
	using namespace ForceField;

	if (!mmff94Parameterizer.get())
		mmff94Parameterizer.reset(new MMFF94InteractionParameterizer());

	if (!mmff94Data.get())
		mmff94Data.reset(new MMFF94InteractionData());

	mmff94Parameterizer->strictParameterization(settings.strictForceFieldParameterization());

	try {
		if (parameterizeMMFF94Interactions(molgraph, *mmff94Parameterizer, *mmff94Data, settings.getForceFieldType()) != ReturnCode::SUCCESS)
			return false;

	} catch (const Error&) {
		return false;
	}

	setMMFF94Parameters(*mmff94Data);
	return true;
}

void ConfGen::TorsionDriverImpl::clearInputCoordinates()
{
	fragTree.getRoot()->clearConformersDownwards();
}

void ConfGen::TorsionDriverImpl::clearInputCoordinates(std::size_t frag_idx)
{
	fragTree.getFragmentNode(frag_idx)->clearConformersUpwards();
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const Math::Vector3DArray& coords)
{
	for (std::size_t i = 0, num_frags = fragTree.getNumFragments(); i < num_frags; i++) {
		FragmentTreeNode* node = fragTree.getFragmentNode(i);

		node->addConformer(coords);
		
		if (node->getParent())
			node->getParent()->clearConformersUpwards();
	}
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx)
{
	FragmentTreeNode* node = fragTree.getFragmentNode(frag_idx);

	node->addConformer(coords);
		
	if (node->getParent())
		node->getParent()->clearConformersUpwards();
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx)
{
	FragmentTreeNode* node = fragTree.getFragmentNode(frag_idx);

	node->addConformer(conf_data);
		
	if (node->getParent())
		node->getParent()->clearConformersUpwards();
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx)
{
	FragmentTreeNode* node = fragTree.getFragmentNode(frag_idx);

	node->getConformers().push_back(conf_data);
		
	if (node->getParent())
		node->getParent()->clearConformersUpwards();
}

void ConfGen::TorsionDriverImpl::setAbortCallback(const CallbackFunction& func)
{
	fragTree.setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::TorsionDriverImpl::getAbortCallback() const
{
	return fragTree.getAbortCallback();
}

void ConfGen::TorsionDriverImpl::setTimeoutCallback(const CallbackFunction& func)
{
	fragTree.setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::TorsionDriverImpl::getTimeoutCallback() const
{
	return fragTree.getTimeoutCallback();
}

std::size_t ConfGen::TorsionDriverImpl::getNumFragments() const
{
	return fragTree.getNumFragments();
}

const Chem::Fragment& ConfGen::TorsionDriverImpl::getFragment(std::size_t idx) const
{
	return *fragTree.getFragment(idx);
}

ConfGen::FragmentTreeNode& ConfGen::TorsionDriverImpl::getFragmentNode(std::size_t idx) const
{
	return *fragTree.getFragmentNode(idx);
}

unsigned int ConfGen::TorsionDriverImpl::generateConformers()
{
	return fragTree.getRoot()->generateConformers(settings.orderByEnergy());
}

std::size_t ConfGen::TorsionDriverImpl::getNumConformers() const
{
	return fragTree.getRoot()->getConformers().size();
}

ConfGen::ConformerData& ConfGen::TorsionDriverImpl::getConformer(std::size_t idx)
{
	return *fragTree.getRoot()->getConformers()[idx];
}

ConfGen::TorsionDriverImpl::ConstConformerIterator ConfGen::TorsionDriverImpl::getConformersBegin() const
{
    return fragTree.getRoot()->getConformers().begin();
}

ConfGen::TorsionDriverImpl::ConstConformerIterator ConfGen::TorsionDriverImpl::getConformersEnd() const
{
    return fragTree.getRoot()->getConformers().end();
}

bool ConfGen::TorsionDriverImpl::initialized() const
{
	return fragTree.getRoot();
}

void ConfGen::TorsionDriverImpl::assignTorsionAngles(FragmentTreeNode* node)
{
	using namespace Chem;

	if (!node->hasChildren())
		return;

	assignTorsionAngles(node->getLeftChild());
	assignTorsionAngles(node->getRightChild());

	const Bond* bond = node->getSplitBond();

	if (!bond)
		return;

	const Atom* const* bond_atoms = node->getSplitBondAtoms();
	FragmentTreeNode::TorsionAngleArray& tor_angles = node->getTorsionAngles();

	const TorsionRuleMatch* match = getMatchingTorsionRule(*bond);

	if (match) {
		for (TorsionRule::ConstAngleEntryIterator it = match->getRule().getAnglesBegin(), end = match->getRule().getAnglesEnd(); it != end; ++it) {
			double tor_ang = it->getAngle();

			// normalize angle to range [0, 360)

			if (tor_ang < 0.0)
				tor_ang = std::fmod(tor_ang, 360.0) + 360.0;
			else 
				tor_ang = std::fmod(tor_ang, 360.0);

			tor_angles.push_back(tor_ang);
		}

		if (!tor_angles.empty()) {
			const Atom* const* match_atoms = match->getAtoms();
				
			if (match_atoms[1] == bond_atoms[0])
				node->setTorsionReferenceAtoms(match_atoms[0], match_atoms[3]);
			else
				node->setTorsionReferenceAtoms(match_atoms[3], match_atoms[0]);
		}
	}
		
	if (tor_angles.empty()) {
		// fallback: rotation in 30° steps

		std::size_t rot_sym = getRotationalSymmetry(*bond);

		for (std::size_t i = 0, num_angles = 12 / rot_sym; i < num_angles; i++)
			tor_angles.push_back(i * 30.0);

		node->setTorsionReferenceAtoms(getFirstNeighborAtom(bond_atoms[0], bond_atoms[1], node), 
									  getFirstNeighborAtom(bond_atoms[1], bond_atoms[0], node));

	} else if (tor_angles.size() > 1) {
		std::size_t rot_sym = getRotationalSymmetry(*bond);

		if (rot_sym > 1) {	// reduce number of torsion angles due to rotational symmetry
			double ident_rot_ang = 360.0 / rot_sym; 

			for (FragmentTreeNode::TorsionAngleArray::iterator it = tor_angles.begin(), end = tor_angles.end(); it != end; ++it) {
				double& tor_ang = *it;

				tor_ang = std::fmod(tor_ang, ident_rot_ang);
			}

			std::sort(tor_angles.begin(), tor_angles.end());
		
			tor_angles.erase(std::unique(tor_angles.begin(), tor_angles.end()), tor_angles.end());
		}
	}
}

const ConfGen::TorsionRuleMatch* ConfGen::TorsionDriverImpl::getMatchingTorsionRule(const Chem::Bond& bond)
{
	const Chem::MolecularGraph& root_molgraph = *fragTree.getRoot()->getRootMolecularGraph();

	torRuleMatcher.setTorsionLibrary(settings.getTorsionLibrary());

	if (torRuleMatcher.findMatches(bond, root_molgraph, false)) 
		return &torRuleMatcher.getMatch(0); 
	
	torRuleMatcher.setTorsionLibrary(getFallbackTorsionLibrary());

	if (torRuleMatcher.findMatches(bond, root_molgraph, false)) 
		return &torRuleMatcher.getMatch(0); 

	return 0;
}

std::size_t ConfGen::TorsionDriverImpl::getRotationalSymmetry(const Chem::Bond& bond)
{
	using namespace Chem;

	std::size_t simple_sym = std::max(getRotationalSymmetry(bond.getBegin(), bond),
									  getRotationalSymmetry(bond.getEnd(), bond));

	if (simple_sym > 1)
		return simple_sym;

	const MolecularGraph& root_molgraph = *fragTree.getRoot()->getRootMolecularGraph();
	std::size_t node_bond_idx = root_molgraph.getBondIndex(bond);

	for (std::size_t i = 0; i < sizeof(SYMMETRY_PATTERN_LIST) / sizeof(SymmetryPattern); i++) {
		const MolecularGraph& ptn = *SYMMETRY_PATTERN_LIST[i].pattern;
		std::size_t num_ptn_bonds = ptn.getNumBonds();
		std::size_t ptn_bond_idx = 0;

		for ( ; ptn_bond_idx < num_ptn_bonds; ptn_bond_idx++) {
			const Bond& bond = ptn.getBond(ptn_bond_idx);
		
			if (getAtomMappingID(bond.getBegin()) != 0 && getAtomMappingID(bond.getEnd()) != 0)
				break;
		}

		if (ptn_bond_idx == num_ptn_bonds)
			continue;

		subSearch.clearBondMappingConstraints();
		subSearch.addBondMappingConstraint(ptn_bond_idx, node_bond_idx);
		subSearch.setQuery(ptn);
	
		if (subSearch.findMappings(root_molgraph)) 
			return SYMMETRY_PATTERN_LIST[i].symmetry;
	}

	return 1;
}

std::size_t ConfGen::TorsionDriverImpl::getRotationalSymmetry(const Chem::Atom& atom, const Chem::Bond& bond) const
{
	using namespace Chem;

	unsigned int nbr_atom_type = 0;
	std::size_t nbr_bond_order = 0;
	std::size_t nbr_count = 0;
	bool first = true;

	const MolecularGraph& root_molgraph = *fragTree.getRoot()->getRootMolecularGraph();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& nbr_bond = *b_it;
	
		if (&nbr_bond == &bond)
			continue;

		if (!root_molgraph.containsBond(nbr_bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!root_molgraph.containsAtom(nbr_atom))
			continue;

		if (getExplicitBondCount(nbr_atom, root_molgraph) != 1)
			return 1;

		nbr_count++;

		if (first) {
			nbr_atom_type = getType(nbr_atom);
			nbr_bond_order = getOrder(atom.getBondToAtom(nbr_atom));
			first = false;
			continue;
		}

		if (getType(nbr_atom) != nbr_atom_type)
			return 1;

		if (getOrder(atom.getBondToAtom(nbr_atom)) != nbr_bond_order)
			return 1;
	}

	switch (getHybridizationState(atom)) {

		case HybridizationState::SP2:
			if (nbr_count != 2)
				return 1;

			return 2;

		case HybridizationState::SP3:
			if (nbr_count == 3)
				return 3;
 		
		default:
			return 1;
	}
	
	return 1;
}

const Chem::Atom* ConfGen::TorsionDriverImpl::getFirstNeighborAtom(const Chem::Atom* ctr_atom, const Chem::Atom* excl_atom,
																   const FragmentTreeNode* node) const
{
	using namespace Chem;

	const MolecularGraph& root_molgraph = *fragTree.getRoot()->getRootMolecularGraph();

	for (Atom::ConstAtomIterator it = ctr_atom->getAtomsBegin(), end = ctr_atom->getAtomsEnd(); it != end; ++it) {
		const Atom& nbr_atom = *it;

		if (excl_atom == &nbr_atom)
			continue;

		if (node->getAtomMask().test(root_molgraph.getAtomIndex(nbr_atom)))
			return &nbr_atom;
	}

	return 0;
}
