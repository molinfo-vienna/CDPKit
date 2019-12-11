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
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/Exceptions.hpp"

#include "TorsionDriverImpl.hpp"
#include "FragmentTreeNode.hpp"
#include "FallbackTorsionLibrary.hpp"

//#include <iostream>
using namespace CDPL;


namespace
{

	struct SymmetryPattern
	{

		Chem::MolecularGraph::SharedPointer pattern;
		std::size_t                         symmetry;
	};

	SymmetryPattern SYMMETRY_PATTERN_LIST[] = {
  	    { Chem::parseSMARTS("[*:1]-[c:1]1[cH1][cH1][c](-[*,#1;X1])[cH1][cH1]1"), 2 },
	    { Chem::parseSMARTS("[*:1]-[*X2:1]#[*X2]-[*,#1;X1]"), 360 },
	    { Chem::parseSMARTS("[*:1]-[*X2:1]#[*X1]"), 360 }
	};

	double normalizeAngle(double angle)
	{
		// normalize angle to range [0, 360)

		if (angle < 0.0)
			return std::fmod(angle, 360.0) + 360.0;

		return std::fmod(angle, 360.0);
	}

	const double MIN_TORSION_ANGLE_DISTANCE = 20.0;

	bool containsCloseTorsionAngle(double angle, const ConfGen::TorsionRule& rule)
	{
		for (ConfGen::TorsionRule::ConstAngleEntryIterator it = rule.getAnglesBegin(), end = rule.getAnglesEnd(); it != end; ++it) {
			double rule_angle = normalizeAngle(it->getAngle());
			double MIN_TORSION_ANGLE_DISTANCE = it->getTolerance1();

			if (angle < rule_angle) {
				if ((rule_angle - angle) < MIN_TORSION_ANGLE_DISTANCE)
					return true;
				
				if ((angle + 360.0 - rule_angle) < MIN_TORSION_ANGLE_DISTANCE)
					return true;
				
			} else {
				if ((angle - rule_angle) < MIN_TORSION_ANGLE_DISTANCE)
					return true;
				
				if ((rule_angle + 360.0 - angle) < MIN_TORSION_ANGLE_DISTANCE)
					return true;
			}
		}

		return false;
	}

	const std::size_t MAX_CONF_DATA_CACHE_SIZE = 10000;
}


ConfGen::TorsionDriverImpl::TorsionDriverImpl(): 
	torLib(TorsionLibrary::get()), fragTree(MAX_CONF_DATA_CACHE_SIZE)
{
	torRuleMatcher.findUniqueMappingsOnly(true);
	torRuleMatcher.findAllRuleMappings(true);
	torRuleMatcher.stopAtFirstMatchingRule(true);
} 

ConfGen::TorsionDriverImpl::~TorsionDriverImpl() {}

ConfGen::TorsionDriverSettings& ConfGen::TorsionDriverImpl::getSettings()
{
	return settings;
}
			
void ConfGen::TorsionDriverImpl::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	torLib = lib;
}

const ConfGen::TorsionLibrary::SharedPointer& ConfGen::TorsionDriverImpl::getTorsionLibrary() const
{
	return torLib;
}

void ConfGen::TorsionDriverImpl::setup(const Chem::MolecularGraph& molgraph)
{
	std::size_t num_bonds = molgraph.getNumBonds();
	
	rotBondMask.resize(num_bonds);
	rotBondMask.reset();
	rotBonds.clear();

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Chem::Bond& bond = molgraph.getBond(i);

		if (isRotatableBond(bond, molgraph, settings.sampleHeteroAtomHydrogens())) {
			rotBonds.push_back(&bond);
			rotBondMask.set(i);
		}
	}

	splitIntoFragments(molgraph, fragments, rotBondMask, false);
	setup(fragments, molgraph, rotBonds.begin(), rotBonds.end());
}

void ConfGen::TorsionDriverImpl::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask)
{
	rotBonds.clear();

	for (Util::BitSet::size_type i = bond_mask.find_first(); i != Util::BitSet::npos; i = bond_mask.find_next(i))
		rotBonds.push_back(&molgraph.getBond(i));

	splitIntoFragments(molgraph, fragments, bond_mask, false);
	setup(fragments, molgraph, rotBonds.begin(), rotBonds.end());
}

void ConfGen::TorsionDriverImpl::setMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data, ForceFieldInteractionMask& ia_mask)
{
	fragTree.getRoot()->distMMFF94Parameters(ia_data, ia_mask);
}

void ConfGen::TorsionDriverImpl::setMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data)
{
	mmff94InteractionMask.setup(ia_data);

	fragTree.getRoot()->distMMFF94Parameters(ia_data, mmff94InteractionMask);
}

bool ConfGen::TorsionDriverImpl::setMMFF94Parameters()
{
	using namespace ForceField;

	const Chem::MolecularGraph& molgraph = *fragTree.getMolecularGraph();

	if (!mmff94Parameterizer.get())
		mmff94Parameterizer.reset(new MMFF94InteractionParameterizer());

	if (!mmff94Data.get())
		mmff94Data.reset(new MMFF94InteractionData());

	try {
		if (parameterizeMMFF94Interactions(molgraph, *mmff94Parameterizer, *mmff94Data, settings.getForceFieldType(),
										   settings.strictForceFieldParameterization()) != ReturnCode::SUCCESS)
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

void ConfGen::TorsionDriverImpl::setInputCoordinates(const Math::Vector3DArray& coords)
{
	fragTree.getRoot()->clearConformersDownwards();

	for (std::size_t i = 0, num_frags = fragTree.getNumFragments(); i < num_frags; i++) {
		FragmentTreeNode* node = fragTree.getFragmentNode(i);

		node->addConformer(coords);
	}
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx)
{
	doAddInputCoordinates(coords, frag_idx);
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx)
{
	doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx)
{
	doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx)
{
	fragTree.getFragmentNode(frag_idx)->clearConformers();

	doAddInputCoordinates(coords, frag_idx);
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx)
{
	fragTree.getFragmentNode(frag_idx)->clearConformers();

	doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx)
{
	fragTree.getFragmentNode(frag_idx)->clearConformers();

	doAddInputCoordinates(conf_data, frag_idx);
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
	unsigned int ret_code = fragTree.getRoot()->generateConformers();

	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	if (settings.orderByEnergy())
		fragTree.getRoot()->orderConformersByEnergy();
	
	return ReturnCode::SUCCESS;
}

std::size_t ConfGen::TorsionDriverImpl::getNumConformers() const
{
	return fragTree.getRoot()->getNumConformers();
}

ConfGen::ConformerData& ConfGen::TorsionDriverImpl::getConformer(std::size_t idx)
{
	return fragTree.getRoot()->getConformer(idx);
}

ConfGen::TorsionDriverImpl::ConstConformerIterator ConfGen::TorsionDriverImpl::getConformersBegin() const
{
    return fragTree.getRoot()->getConformers().begin();
}

ConfGen::TorsionDriverImpl::ConstConformerIterator ConfGen::TorsionDriverImpl::getConformersEnd() const
{
    return fragTree.getRoot()->getConformers().end();
}

template <typename ConfData>
void ConfGen::TorsionDriverImpl::doAddInputCoordinates(const ConfData& conf_data, std::size_t frag_idx) const
{
	FragmentTreeNode* node = fragTree.getFragmentNode(frag_idx);

	node->addConformer(conf_data);
		
	if (node->getParent())
		node->getParent()->clearConformersUpwards();
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
	const TorsionRuleMatch* match = getTorsionRuleAngles(*bond, node);

	if (match && node->getNumTorsionAngles() != 0) {
		const Atom* const* match_atoms = match->getAtoms();
				
		if (match_atoms[1] == bond_atoms[0])
			node->setTorsionReferenceAtoms(match_atoms[0], match_atoms[3]);
		else
			node->setTorsionReferenceAtoms(match_atoms[3], match_atoms[0]);
	}
		
	if (node->getNumTorsionAngles() == 0) {
		// fallback: rotation in 30° steps

		std::size_t rot_sym = getRotationalSymmetry(*bond);

		for (std::size_t i = 0, num_angles = 12 / rot_sym; i < num_angles; i++) 
			node->addTorsionAngle(i * 30.0, 0.0);

		node->setTorsionReferenceAtoms(getFirstNeighborAtom(bond_atoms[0], bond_atoms[1], node), 
									   getFirstNeighborAtom(bond_atoms[1], bond_atoms[0], node));

		if (!node->getTorsionReferenceAtoms()[0] || !node->getTorsionReferenceAtoms()[1])
			node->setTorsionReferenceAtoms(0, 0);

	} else if (node->getNumTorsionAngles() > 1) 
		node->pruneTorsionAngles(getRotationalSymmetry(*bond));
}

const ConfGen::TorsionRuleMatch* ConfGen::TorsionDriverImpl::getTorsionRuleAngles(const Chem::Bond& bond, FragmentTreeNode* node)
{
	using namespace Chem;

	const MolecularGraph& molgraph = *fragTree.getMolecularGraph();
	bool have_matches = false;

	if (torLib) {
		torRuleMatcher.setTorsionLibrary(torLib);

		have_matches = torRuleMatcher.findMatches(bond, molgraph, false);
	}

	if (!have_matches) {
		torRuleMatcher.setTorsionLibrary(getFallbackTorsionLibrary());

		have_matches = torRuleMatcher.findMatches(bond, molgraph, false); 
	}
	
	if (!have_matches)
		return 0;

	bool alter_120 = false;
	bool alter_180 = false;

	const TorsionRuleMatch& match = torRuleMatcher.getMatch(0);
	const TorsionRule& rule = match.getRule();

	if (torRuleMatcher.getNumMatches() > 1) {
		for (std::size_t i = 0; i < 2; i++) {
			const Atom& atom = bond.getAtom(i);

			if (haveUniqueTorsionReferenceAtom(atom))
				continue;

			switch (getTorsionAngleIncrement(atom)) {

				case 120:
					alter_120 = true;
					continue;

				case 180:
					alter_180 = true;

				default:
					continue;
			}
		}
	}

	for (TorsionRule::ConstAngleEntryIterator it = rule.getAnglesBegin(), end = rule.getAnglesEnd(); it != end; ++it) {
		double angle = normalizeAngle(it->getAngle());
		double tol = it->getTolerance1();
			
		node->addTorsionAngle(angle, tol);

		if (alter_120) {
			double alt_ang = std::fmod(angle + 120.0, 360.0);

			if (!containsCloseTorsionAngle(alt_ang, rule))
				node->addTorsionAngle(alt_ang, tol);

			alt_ang = std::fmod(angle + 240.0, 360.0);

			if (!containsCloseTorsionAngle(alt_ang, rule))
				node->addTorsionAngle(alt_ang, tol);
		}

		if (alter_180) {
			double alt_ang = std::fmod(angle + 180.0, 360.0);

			if (!containsCloseTorsionAngle(alt_ang, rule))
				node->addTorsionAngle(alt_ang, tol);
		}
	}
/*
	std::cerr << rule.getMatchPatternString() << ": ";

	for (std::size_t i = 0; i < node->getNumTorsionAngles(); i++) 
		std::cerr << node->getTorsionAngles()[i].first << " ";
		
	std::cerr << std::endl;
*/	
	return &match; 
}

bool ConfGen::TorsionDriverImpl::haveUniqueTorsionReferenceAtom(const Chem::Atom& atom) const
{
	using namespace Chem;

	const Atom* ref_atom = 0;

	for (TorsionRuleMatcher::ConstMatchIterator it = torRuleMatcher.getMatchesBegin(), end = torRuleMatcher.getMatchesEnd(); it != end; ++it) {
		const TorsionRuleMatch& match = *it;

		if (match.getAtoms()[1] == &atom) {
			if (ref_atom && match.getAtoms()[0] != ref_atom)
				return false;

			ref_atom = match.getAtoms()[0];

		} else {
			if (ref_atom && match.getAtoms()[3] != ref_atom)
				return false;

			ref_atom = match.getAtoms()[3];
		}
	}

	return true;
}

std::size_t ConfGen::TorsionDriverImpl::getTorsionAngleIncrement(const Chem::Atom& atom) const
{
	using namespace Chem;

	if (getAromaticityFlag(atom))
		return 180;

	switch (getHybridizationState(atom)) {

		case HybridizationState::SP3:
			if (getType(atom) == AtomType::N && isPlanarNitrogen(atom, *fragTree.getMolecularGraph()))
				return 180;

			return 120;

		case HybridizationState::SP2:
			return 180;

		default:
			break;
	}

	return 0;
}

std::size_t ConfGen::TorsionDriverImpl::getRotationalSymmetry(const Chem::Bond& bond)
{
	using namespace Chem;

	std::size_t simple_sym = std::max(getRotationalSymmetry(bond.getBegin(), bond),
									  getRotationalSymmetry(bond.getEnd(), bond));
	if (simple_sym > 1)
		return simple_sym;

	const MolecularGraph& molgraph = *fragTree.getMolecularGraph();
	std::size_t node_bond_idx = molgraph.getBondIndex(bond);

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
	
		if (subSearch.findMappings(molgraph))
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

	const MolecularGraph& molgraph = *fragTree.getMolecularGraph();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& nbr_bond = *b_it;
	
		if (&nbr_bond == &bond)
			continue;

		if (!molgraph.containsBond(nbr_bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom))
			continue;

		if (getExplicitBondCount(nbr_atom, molgraph) != 1)
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
