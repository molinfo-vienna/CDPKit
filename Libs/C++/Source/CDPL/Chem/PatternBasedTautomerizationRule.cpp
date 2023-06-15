/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedTautomerizationRule.cpp 
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

#include <functional>

#include "CDPL/Chem/PatternBasedTautomerizationRule.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


namespace
{

	const std::size_t MAX_BITSET_CACHE_SIZE = 1000;
}


using namespace CDPL;


Chem::PatternBasedTautomerizationRule::	PatternBasedTautomerizationRule(unsigned int rule_id): 
	ruleID(rule_id), parentMolGraph(0), currPatternIdx(0), currMappingIdx(0), bitSetCache(MAX_BITSET_CACHE_SIZE)
{}

Chem::PatternBasedTautomerizationRule::PatternBasedTautomerizationRule(const PatternBasedTautomerizationRule& rule):
	ruleID(rule.ruleID), structPatterns(rule.structPatterns), excludePatterns(rule.excludePatterns), 
	patternBondChangeLists(rule.patternBondChangeLists), parentMolGraph(0), currPatternIdx(rule.structPatterns.size()),
	currMappingIdx(0), bitSetCache(MAX_BITSET_CACHE_SIZE)
{
	for (StructPatternList::const_iterator it = structPatterns.begin(), end = structPatterns.end(); it != end; ++it)
		patternSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(**it)));

	for (StructPatternList::const_iterator it = excludePatterns.begin(), end = excludePatterns.end(); it != end; ++it)
		excludeSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(**it)));
}

Chem::PatternBasedTautomerizationRule& Chem::PatternBasedTautomerizationRule::operator=(const PatternBasedTautomerizationRule& rule)
{
	if (this == &rule)
		return *this;

	ruleID = rule.ruleID;
	structPatterns = rule.structPatterns;
	excludePatterns = rule.excludePatterns;
	patternBondChangeLists = rule.patternBondChangeLists;
	parentMolGraph = 0;
	currPatternIdx = structPatterns.size();
	currMappingIdx = 0;

	patternSubSearchList.clear();

	for (StructPatternList::const_iterator it = structPatterns.begin(), end = structPatterns.end(); it != end; ++it)
		patternSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(**it)));

	excludeSubSearchList.clear();

	for (StructPatternList::const_iterator it = excludePatterns.begin(), end = excludePatterns.end(); it != end; ++it)
		excludeSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(**it)));

	return *this;
}

void Chem::PatternBasedTautomerizationRule::addExcludePattern(const MolecularGraph::SharedPointer& pattern)
{
	excludePatterns.push_back(pattern);
	excludeSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(*pattern)));
}

void Chem::PatternBasedTautomerizationRule::addExcludePatterns(const PatternBasedTautomerizationRule& rule)
{
	excludePatterns.insert(excludePatterns.end(), rule.structPatterns.begin(), rule.structPatterns.end());

	for (StructPatternList::const_iterator it = rule.structPatterns.begin(), end = rule.structPatterns.end(); it != end; ++it)
		excludeSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(**it)));
}

void Chem::PatternBasedTautomerizationRule::clearExcludePatterns()
{
	excludeSubSearchList.clear();
	excludePatterns.clear();
}

Chem::TautomerizationRule::SharedPointer Chem::PatternBasedTautomerizationRule::clone() const
{
	return SharedPointer(new PatternBasedTautomerizationRule(*this));
}

bool Chem::PatternBasedTautomerizationRule::setup(MolecularGraph& parent_molgraph)
{
	using namespace std::placeholders;
		
    std::for_each(patternSubSearchList.begin(), patternSubSearchList.end(), std::bind(&SubstructureSearch::findMappings, _1, std::ref(parent_molgraph)));

	parentMolGraph = &parent_molgraph;
	currPatternIdx = 0;
	currMappingIdx = 0;

    if (std::find_if(patternSubSearchList.begin(), patternSubSearchList.end(), std::bind(&SubstructureSearch::getNumMappings, _1)) == patternSubSearchList.end())
		return false;

	if (excludePatterns.empty()) 
		return true;

	bitSetCache.putAll();

	std::size_t num_parent_bonds = parent_molgraph.getNumBonds();

	bondMask.resize(num_parent_bonds);
	excludeMatches.clear();

	for (SubstructureSearchList::const_iterator it = excludeSubSearchList.begin(), end = excludeSubSearchList.end(); it != end; ++it) {
		const SubstructureSearch::SharedPointer& subsearch = *it;

		if (!subsearch->findMappings(parent_molgraph))
			continue;

		for (SubstructureSearch::ConstMappingIterator m_it = subsearch->getMappingsBegin(), m_end = subsearch->getMappingsEnd(); m_it != m_end; ++m_it) {
			Util::BitSet* bond_mask = bitSetCache.getRaw();

			bond_mask->resize(num_parent_bonds);

			createMatchedBondMask(m_it->getBondMapping(), *bond_mask);
			excludeMatches.push_back(bond_mask);
		}
	}

	return true;
}

unsigned int Chem::PatternBasedTautomerizationRule::getID() const
{
    return ruleID;
}

bool Chem::PatternBasedTautomerizationRule::generate(Molecule& tautomer)
{
	for ( ; currPatternIdx < structPatterns.size(); currPatternIdx++) {
		while (currMappingIdx < patternSubSearchList[currPatternIdx]->getNumMappings()) {
			if (applyTransformation(tautomer)) {
				currMappingIdx++;
				return true;
			}

			currMappingIdx++;
		}

		currMappingIdx = 0;
	}

    return false;
}

bool Chem::PatternBasedTautomerizationRule::applyTransformation(Molecule& tautomer)
{
	const AtomBondMapping& mapping = patternSubSearchList[currPatternIdx]->getMapping(currMappingIdx);

	if (!excludePatterns.empty()) { 
		createMatchedBondMask(mapping.getBondMapping(), bondMask);

		for (BitSetList::const_iterator it = excludeMatches.begin(), end = excludeMatches.end(); it != end; ++it)
			if ((*it)->is_subset_of(bondMask))
				return false;
	}

	tautomer.clear();

	for (MolecularGraph::ConstAtomIterator it = parentMolGraph->getAtomsBegin(), end = parentMolGraph->getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		Atom& atom_copy = tautomer.addAtom();

		setType(atom_copy, getType(atom));
		setFormalCharge(atom_copy, getFormalCharge(atom));
		setUnpairedElectronCount(atom_copy, getUnpairedElectronCount(atom));
		setIsotope(atom_copy, getIsotope(atom));
		setImplicitHydrogenCount(atom_copy, 0);

		if (has3DCoordinates(atom))
			set3DCoordinates(atom_copy, get3DCoordinates(atom));

		if (has2DCoordinates(atom))
			set2DCoordinates(atom_copy, get2DCoordinates(atom));
	}

	for (MolecularGraph::ConstBondIterator it = parentMolGraph->getBondsBegin(), end = parentMolGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		Bond& bond_copy = tautomer.addBond(parentMolGraph->getAtomIndex(bond.getBegin()), parentMolGraph->getAtomIndex(bond.getEnd()));

		setOrder(bond_copy, getOrder(bond));
		set2DStereoFlag(bond_copy, get2DStereoFlag(bond));
	}

	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	for (BondOrderChangeList::const_iterator it = patternBondChangeLists[currPatternIdx].begin(), end = patternBondChangeLists[currPatternIdx].end(); it != end; ++it) {
		const BondOrderChange& bond_chg_data = *it;

		Atom* atom1 = getTautomerAtom(tautomer, bond_chg_data.atom2ID, atom_mapping);

		if (!atom1)
			return false;

		const Atom* atom2 = getTautomerAtom(tautomer, bond_chg_data.atom1ID, atom_mapping);

		if (!atom2)
			return false;

		Bond* bond = atom1->findBondToAtom(*atom2);

		if (!bond) {
			if (bond_chg_data.orderChange > 0) 
				setOrder(tautomer.addBond(atom1->getIndex(), atom2->getIndex()), bond_chg_data.orderChange);

			continue;
		}

		long res_order = long(getOrder(*bond)) + bond_chg_data.orderChange;

		if (res_order <= 0) {
			tautomer.removeBond(bond->getIndex());
			continue;
		}
			
		setOrder(*bond, res_order);
	}

	return true;
}

Chem::Atom* Chem::PatternBasedTautomerizationRule::getTautomerAtom(Molecule& tautomer, std::size_t ptn_atom_id, const AtomMapping& mapping) const
{
	for (MolecularGraph::ConstAtomIterator it = structPatterns[currPatternIdx]->getAtomsBegin(), end = structPatterns[currPatternIdx]->getAtomsEnd(); it != end; ++it) {
		const Atom& ptn_atom = *it;

		if (getAtomMappingID(ptn_atom) != ptn_atom_id)
			continue;

		const Atom* tgt_atom = mapping[&ptn_atom];

		if (!tgt_atom)
			return 0;

		std::size_t tgt_atom_idx = parentMolGraph->getAtomIndex(*tgt_atom);

		return &tautomer.getAtom(tgt_atom_idx);
	}

	return 0;
}

void Chem::PatternBasedTautomerizationRule::createMatchedBondMask(const Chem::BondMapping& mapping, Util::BitSet& bond_mask) const
{
	bond_mask.reset();

	for (BondMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it)
		bond_mask.set(parentMolGraph->getBondIndex(*it->second));
}
