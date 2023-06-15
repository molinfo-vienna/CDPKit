/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentGenerator.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
#include <functional>

#include "CDPL/Chem/FragmentGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::FragmentGenerator::FragmentationRule::FragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int id):
	matchPtn(match_ptn), id(id)
{}

const Chem::MolecularGraph::SharedPointer& Chem::FragmentGenerator::FragmentationRule::getMatchPattern() const
{
	return matchPtn;
}

void Chem::FragmentGenerator::FragmentationRule::setMatchPattern(const MolecularGraph::SharedPointer& ptn)
{
	matchPtn = ptn;
}

unsigned int Chem::FragmentGenerator::FragmentationRule::getID() const
{
	return id;
}

void Chem::FragmentGenerator::FragmentationRule::setID(unsigned int id)
{
	this->id = id;
}
	
	
Chem::FragmentGenerator::ExcludePattern::ExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id):
	matchPtn(match_ptn), ruleID(rule_id), generic(false)
{}

Chem::FragmentGenerator::ExcludePattern::ExcludePattern(const MolecularGraph::SharedPointer& match_ptn):
	matchPtn(match_ptn), ruleID(0), generic(true)
{}

const Chem::MolecularGraph::SharedPointer& Chem::FragmentGenerator::ExcludePattern::getMatchPattern() const
{
	return matchPtn;
}

void Chem::FragmentGenerator::ExcludePattern::setMatchPattern(const MolecularGraph::SharedPointer& ptn)
{
	matchPtn = ptn;
}

unsigned int Chem::FragmentGenerator::ExcludePattern::getRuleID() const
{
	return ruleID;
}

void Chem::FragmentGenerator::ExcludePattern::setRuleID( unsigned int id)
{
	ruleID = id;
}

bool Chem::FragmentGenerator::ExcludePattern::isGeneric() const
{
	return generic;
}

void Chem::FragmentGenerator::ExcludePattern::setGeneric(bool gen)
{
	generic = gen;
}
				
		
Chem::FragmentGenerator::FragmentLink::FragmentLink(std::size_t frag1_idx, std::size_t frag2_idx, const Bond& bond,
													unsigned int rule_id, unsigned int atom1_label, unsigned int atom2_label):
	frag1Idx(frag1_idx), frag2Idx(frag2_idx), bond(&bond), ruleID(rule_id), atom1Label(atom1_label), atom2Label(atom2_label)
{}

std::size_t Chem::FragmentGenerator::FragmentLink::getFragment1Index() const
{
	return frag1Idx;
}

std::size_t Chem::FragmentGenerator::FragmentLink::getFragment2Index() const
{
	return frag2Idx;
}
				
const Chem::Bond& Chem::FragmentGenerator::FragmentLink::getBond() const
{
	return *bond;
}
				
unsigned int Chem::FragmentGenerator::FragmentLink::getRuleID() const
{
	return ruleID;
}

unsigned int Chem::FragmentGenerator::FragmentLink::getAtom1Label() const
{
	return atom1Label;
}

unsigned int Chem::FragmentGenerator::FragmentLink::getAtom2Label() const
{
	return atom2Label;
}
			   
	
Chem::FragmentGenerator::FragmentGenerator(): incSplitBonds(true)
{
	subSearch.uniqueMappingsOnly(false);
}

Chem::FragmentGenerator::FragmentGenerator(const FragmentGenerator& gen):
	fragRules(gen.fragRules), exclPatterns(gen.exclPatterns), fragLinks(gen.fragLinks),
	incSplitBonds(gen.incSplitBonds), fragFilterFunc(gen.fragFilterFunc)
{
	subSearch.uniqueMappingsOnly(false);
}

Chem::FragmentGenerator& Chem::FragmentGenerator::operator=(const FragmentGenerator& gen)
{
	if (this == &gen)
		return *this;
	
	fragRules = gen.fragRules;
	exclPatterns = gen.exclPatterns;
	fragLinks = gen.fragLinks;
	incSplitBonds = gen.incSplitBonds;
	fragFilterFunc = gen.fragFilterFunc;
	
	return *this;
}

void Chem::FragmentGenerator::addFragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id)
{
	fragRules.push_back(FragmentationRule(match_ptn, rule_id));
}

void Chem::FragmentGenerator::addFragmentationRule(const FragmentationRule& rule)
{
	fragRules.push_back(rule);
}

const Chem::FragmentGenerator::FragmentationRule& Chem::FragmentGenerator::getFragmentationRule(std::size_t idx) const
{
	if (idx >= fragRules.size())
		throw Base::IndexError("FragmentGenerator: fragmentation rule index out of bounds");

	return fragRules[idx];
}

Chem::FragmentGenerator::FragmentationRule& Chem::FragmentGenerator::getFragmentationRule(std::size_t idx)
{
	if (idx >= fragRules.size())
		throw Base::IndexError("FragmentGenerator: fragmentation rule index out of bounds");

	return fragRules[idx];
}

Chem::FragmentGenerator::ConstFragmentationRuleIterator Chem::FragmentGenerator::getFragmentationRulesBegin() const
{
	return fragRules.begin();
}

Chem::FragmentGenerator::ConstFragmentationRuleIterator Chem::FragmentGenerator::getFragmentationRulesEnd() const
{
	return fragRules.end();
}

Chem::FragmentGenerator::FragmentationRuleIterator Chem::FragmentGenerator::getFragmentationRulesBegin()
{
	return fragRules.begin();
}

Chem::FragmentGenerator::FragmentationRuleIterator Chem::FragmentGenerator::getFragmentationRulesEnd()
{
	return fragRules.end();
}

void Chem::FragmentGenerator::removeFragmentationRule(std::size_t idx)
{
	if (idx >= fragRules.size())
		throw Base::IndexError("FragmentGenerator: fragmentation rule index out of bounds");

	fragRules.erase(fragRules.begin() + idx);
}

std::size_t Chem::FragmentGenerator::getNumFragmentationRules() const
{
	return fragRules.size();
}

void Chem::FragmentGenerator::clearFragmentationRules()
{
	fragRules.clear();
}

void Chem::FragmentGenerator::addExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id)
{
	exclPatterns.push_back(ExcludePattern(match_ptn, rule_id));
}

void Chem::FragmentGenerator::addExcludePattern(const MolecularGraph::SharedPointer& match_ptn)
{
	exclPatterns.push_back(ExcludePattern(match_ptn));
}

void Chem::FragmentGenerator::addExcludePattern(const ExcludePattern& excl_ptn)
{
	exclPatterns.push_back(excl_ptn);
}

const Chem::FragmentGenerator::ExcludePattern& Chem::FragmentGenerator::getExcludePattern(std::size_t idx) const
{
	if (idx >= exclPatterns.size())
		throw Base::IndexError("FragmentGenerator: exclude pattern index out of bounds");

	return exclPatterns[idx];
}

Chem::FragmentGenerator::ExcludePattern& Chem::FragmentGenerator::getExcludePattern(std::size_t idx)
{
	if (idx >= exclPatterns.size())
		throw Base::IndexError("FragmentGenerator: exclude pattern index out of bounds");

	return exclPatterns[idx];
}

Chem::FragmentGenerator::ConstExcludePatternIterator Chem::FragmentGenerator::getExcludePatternsBegin() const
{
	return exclPatterns.begin();
}

Chem::FragmentGenerator::ConstExcludePatternIterator Chem::FragmentGenerator::getExcludePatternsEnd() const
{
	return exclPatterns.end();
}

Chem::FragmentGenerator::ExcludePatternIterator Chem::FragmentGenerator::getExcludePatternsBegin()
{
	return exclPatterns.begin();
}

Chem::FragmentGenerator::ExcludePatternIterator Chem::FragmentGenerator::getExcludePatternsEnd()
{
	return exclPatterns.end();
}

void Chem::FragmentGenerator::removeExcludePattern(std::size_t idx)
{
	if (idx >= exclPatterns.size())
		throw Base::IndexError("FragmentGenerator: exclude pattern index out of bounds");

	exclPatterns.erase(exclPatterns.begin() + idx);
}

std::size_t Chem::FragmentGenerator::getNumExcludePatterns() const
{
	return exclPatterns.size();
}

void Chem::FragmentGenerator::clearExcludePatterns()
{
	exclPatterns.clear();
}

bool Chem::FragmentGenerator::includeSplitBonds() const
{
	return incSplitBonds;
}

void Chem::FragmentGenerator::includeSplitBonds(bool include)
{
	incSplitBonds = include;
}

const Chem::FragmentGenerator::FragmentFilterFunction& Chem::FragmentGenerator::getFragmentFilterFunction() const
{
	return fragFilterFunc;
}

void Chem::FragmentGenerator::setFragmentFilterFunction(const FragmentFilterFunction& func)
{
	fragFilterFunc = func;
}

void Chem::FragmentGenerator::generate(const MolecularGraph& molgraph, FragmentList& frag_list, bool append)
{
	using namespace std::placeholders;
	
	init(molgraph);

	std::for_each(fragRules.begin(), fragRules.end(),
				  std::bind(&Chem::FragmentGenerator::processFragRuleMatches, this, std::ref(molgraph), _1));
	std::for_each(exclPatterns.begin(), exclPatterns.end(),
				  std::bind(&Chem::FragmentGenerator::processExcludePatternMatches, this, std::ref(molgraph), _1));

	splitIntoFragments(molgraph, frag_list, append);
}

std::size_t Chem::FragmentGenerator::getNumFragmentLinks() const
{
	return fragLinks.size();
}

const Chem::FragmentGenerator::FragmentLink& Chem::FragmentGenerator::getFragmentLink(std::size_t idx) const
{
	if (idx >= fragLinks.size())
		throw Base::IndexError("FragmentGenerator: fragment links index out of bounds");

	return fragLinks[idx];
}

Chem::FragmentGenerator::ConstFragmentLinkIterator Chem::FragmentGenerator::getFragmentLinksBegin() const
{
	return fragLinks.begin();
}

Chem::FragmentGenerator::ConstFragmentLinkIterator Chem::FragmentGenerator::getFragmentLinksEnd() const
{
	return fragLinks.end();
}

void Chem::FragmentGenerator::init(const MolecularGraph& molgraph)
{
	fragLinks.clear();

	std::size_t num_bonds = molgraph.getNumBonds();

	splitBondMask.resize(num_bonds);
	splitBondMask.reset();

	if (splitBondData.size() < num_bonds)
		splitBondData.resize(num_bonds);
}

void Chem::FragmentGenerator::processFragRuleMatches(const MolecularGraph& molgraph, const FragmentationRule& rule)
{
	if (!rule.getMatchPattern()) // sanity check
		return;
	
	subSearch.setQuery(*rule.getMatchPattern());

	if (!subSearch.findMappings(molgraph))
		return;

	unsigned int rule_id = rule.getID();
	
	for (SubstructureSearch::ConstMappingIterator it1 = subSearch.getMappingsBegin(), end1 = subSearch.getMappingsEnd(); it1 != end1; ++it1) {
		const AtomBondMapping& mapping = *it1;
		const AtomMapping& atom_mapping = mapping.getAtomMapping();
		const BondMapping& bond_mapping = mapping.getBondMapping();
		
		for (BondMapping::ConstEntryIterator it2 = bond_mapping.getEntriesBegin(), end2 = bond_mapping.getEntriesEnd(); it2 != end2; ++it2) {
			const BondMapping::Entry& bond_mpg_entry = *it2;

			if (!bond_mpg_entry.second) // sanity check
				continue;
			
			const Atom* ptn_atom1 = &bond_mpg_entry.first->getBegin();
			const Atom* ptn_atom2 = &bond_mpg_entry.first->getEnd();
			
			if (!hasAtomMappingID(*ptn_atom1) || !hasAtomMappingID(*ptn_atom2))
				continue;

			unsigned int atom1_label = getAtomMappingID(*ptn_atom1);
			unsigned int atom2_label = getAtomMappingID(*ptn_atom2);
		
			const Atom* mpd_atom1 = atom_mapping[ptn_atom1];

			if (!mpd_atom1) // sanity check
				continue;
		
			const Atom* mpd_atom2 = atom_mapping[ptn_atom2];

			if (!mpd_atom2) // sanity check
				continue;

			std::size_t mpd_bond_idx = molgraph.getBondIndex(*bond_mpg_entry.second);

			if (&bond_mpg_entry.second->getBegin() == mpd_atom1 && &bond_mpg_entry.second->getEnd() == mpd_atom2) {
				splitBondData[mpd_bond_idx].atom1Label = atom1_label;
				splitBondData[mpd_bond_idx].atom2Label = atom2_label;
			
			} else if (&bond_mpg_entry.second->getEnd() == mpd_atom1 && &bond_mpg_entry.second->getBegin() == mpd_atom2) {
				splitBondData[mpd_bond_idx].atom1Label = atom2_label;
				splitBondData[mpd_bond_idx].atom2Label = atom1_label;

			} else
				continue;

			splitBondMask.set(mpd_bond_idx);

			splitBondData[mpd_bond_idx].bond = bond_mpg_entry.second;
			splitBondData[mpd_bond_idx].ruleID = rule_id;
		}
	}
}

void Chem::FragmentGenerator::processExcludePatternMatches(const MolecularGraph& molgraph, const ExcludePattern& ptn)
{
	if (!ptn.getMatchPattern()) // sanity check
		return;
	
	subSearch.setQuery(*ptn.getMatchPattern());

	if (!subSearch.findMappings(molgraph))
		return;

	unsigned int rule_id = ptn.getRuleID();
	bool generic = ptn.isGeneric();
	
	for (SubstructureSearch::ConstMappingIterator it1 = subSearch.getMappingsBegin(), end1 = subSearch.getMappingsEnd(); it1 != end1; ++it1) {
		const AtomBondMapping& mapping = *it1;
		const BondMapping& bond_mapping = mapping.getBondMapping();
		bool found_marked_bonds = false;

		for (BondMapping::ConstEntryIterator it2 = bond_mapping.getEntriesBegin(), end2 = bond_mapping.getEntriesEnd(); it2 != end2; ++it2) {
			const BondMapping::Entry& bond_mpg_entry = *it2;

			if (!bond_mpg_entry.second) // sanity check
				continue;
			
			if (!hasAtomMappingID(bond_mpg_entry.first->getBegin()) || !hasAtomMappingID(bond_mpg_entry.first->getEnd()))
				continue;

			std::size_t mpd_bond_idx = molgraph.getBondIndex(*bond_mpg_entry.second);

			if (generic || (splitBondMask.test(mpd_bond_idx) && splitBondData[mpd_bond_idx].ruleID == rule_id))
				splitBondMask.reset(mpd_bond_idx);

			found_marked_bonds = true;
		}
		
		if (found_marked_bonds)
			continue;
		
		for (BondMapping::ConstEntryIterator it2 = bond_mapping.getEntriesBegin(), end2 = bond_mapping.getEntriesEnd(); it2 != end2; ++it2) {
			const BondMapping::Entry& bond_mpg_entry = *it2;

			if (!bond_mpg_entry.second) // sanity check
				continue;
			
			std::size_t mpd_bond_idx = molgraph.getBondIndex(*bond_mpg_entry.second);

			if (generic || (splitBondMask.test(mpd_bond_idx) && splitBondData[mpd_bond_idx].ruleID == rule_id))
				splitBondMask.reset(mpd_bond_idx);
		}
	}
}

void Chem::FragmentGenerator::splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list, bool append)
{
	if (!append)
		frag_list.clear();

	std::size_t new_frags_start_idx = frag_list.getSize();
	std::size_t num_atoms = molgraph.getNumAtoms();

    visAtomMask.resize(num_atoms);
	visAtomMask.reset();
	
    for (std::size_t i = 0; i < num_atoms; i++) {
		if (!visAtomMask.test(i)) {
			Fragment::SharedPointer frag_ptr(new Fragment());
			const Atom& atom = molgraph.getAtom(i);

			frag_ptr->addAtom(atom);

			visAtomMask.set(i);

			growFragment(atom, molgraph, *frag_ptr);

			if (fragFilterFunc && !fragFilterFunc(*frag_ptr))
				continue;
				
			frag_list.addElement(frag_ptr);
		}
    }

	std::size_t frag_list_size = frag_list.getSize();
	
	for (Util::BitSet::size_type bond_idx = splitBondMask.find_first(); bond_idx != Util::BitSet::npos; bond_idx = splitBondMask.find_next(bond_idx)) {
		const Bond& bond = *splitBondData[bond_idx].bond;
		std::size_t frag1_idx = findContainingFragment(bond.getBegin(), frag_list, new_frags_start_idx);
		std::size_t frag2_idx = findContainingFragment(bond.getEnd(), frag_list, new_frags_start_idx);

		fragLinks.push_back(FragmentLink(frag1_idx, frag2_idx, bond, splitBondData[bond_idx].ruleID,
										 splitBondData[bond_idx].atom1Label, splitBondData[bond_idx].atom2Label));
	}

	if (!incSplitBonds)
		return;

	for (ConstFragmentLinkIterator it = fragLinks.begin(), end = fragLinks.end(); it != end; ++it) {
		const FragmentLink& link = *it;

		if (link.getFragment1Index() < frag_list_size) 
			frag_list[link.getFragment1Index()].addBond(link.getBond());

		if (link.getFragment2Index() < frag_list_size) 
			frag_list[link.getFragment2Index()].addBond(link.getBond());
	}
}

void Chem::FragmentGenerator::growFragment(const Atom& atom, const MolecularGraph& molgraph, Fragment& frag)
{
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (frag.containsBond(bond))
			continue;

		if (!molgraph.containsBond(bond))
			continue;

		if (splitBondMask.test(molgraph.getBondIndex(bond)))
			continue;
	
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom))
			continue;
		
		frag.addBond(bond);

		std::size_t nbr_atom_idx = molgraph.getAtomIndex(nbr_atom);

		if (!visAtomMask.test(nbr_atom_idx)) { 
			visAtomMask.set(nbr_atom_idx);
			
			growFragment(nbr_atom, molgraph, frag);
		}
	}
}

std::size_t Chem::FragmentGenerator::findContainingFragment(const Chem::Atom& atom, const FragmentList& frag_list,
															std::size_t start_idx) const
{
	std::size_t num_frags = frag_list.getSize();
	
	for (std::size_t i = start_idx; i < num_frags; i++) {
		const Fragment& frag = frag_list.getElement(i);

		if (frag.containsAtom(atom))
			return i;
	}
	
	return num_frags;
}
