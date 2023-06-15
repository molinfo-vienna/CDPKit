/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionRuleMatcher.cpp 
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

#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


ConfGen::TorsionRuleMatcher::TorsionRuleMatcher(): uniqueMappingsOnly(true), stopAtFirstRule(true) 
{
	findAllRuleMappings(false);
	
	subSearch.uniqueMappingsOnly(false);
}

ConfGen::TorsionRuleMatcher::TorsionRuleMatcher(const TorsionLibrary::SharedPointer& lib):
	torLib(lib), uniqueMappingsOnly(true), stopAtFirstRule(true)
{
	findAllRuleMappings(false);

	subSearch.uniqueMappingsOnly(false);
}

void ConfGen::TorsionRuleMatcher::findUniqueMappingsOnly(bool unique)
{
	uniqueMappingsOnly = unique;
}

bool ConfGen::TorsionRuleMatcher::findUniqueMappingsOnly() const
{
	return uniqueMappingsOnly;
}

void ConfGen::TorsionRuleMatcher::findAllRuleMappings(bool all)
{
	if (all)
		subSearch.setMaxNumMappings(0);
	else
		subSearch.setMaxNumMappings(1);
}

bool ConfGen::TorsionRuleMatcher::findAllRuleMappings() const
{
	return (subSearch.getMaxNumMappings() == 0);
}

void ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule(bool stop)
{
	stopAtFirstRule = stop;
}

bool ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule() const
{
	return stopAtFirstRule;
}

void ConfGen::TorsionRuleMatcher::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
    torLib = lib;
}

const ConfGen::TorsionLibrary::SharedPointer& ConfGen::TorsionRuleMatcher::getTorsionLibrary() const
{
    return torLib;
}

std::size_t ConfGen::TorsionRuleMatcher::getNumMatches() const
{
	return matches.size();
}
		
const ConfGen::TorsionRuleMatch& ConfGen::TorsionRuleMatcher::getMatch(std::size_t idx) const
{
	if (idx >= matches.size())
		throw Base::IndexError("TorsionRuleMatcher: torsion rule match index out of bounds");

	return matches[idx];
}

ConfGen::TorsionRuleMatcher::ConstMatchIterator ConfGen::TorsionRuleMatcher::getMatchesBegin() const
{
	return matches.begin();
}

ConfGen::TorsionRuleMatcher::ConstMatchIterator ConfGen::TorsionRuleMatcher::getMatchesEnd() const
{
	return matches.end();
}

bool ConfGen::TorsionRuleMatcher::findMatches(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, 
											  bool append)
{
    if (!append)
		matches.clear();

	if (!torLib)
		return false;

	return findMatchingRules(*torLib, bond, molgraph);
}

bool ConfGen::TorsionRuleMatcher::findMatchingRules(const TorsionCategory& cat, const Chem::Bond& bond, 
													const Chem::MolecularGraph& molgraph)
{
	if (&cat != torLib.get() && !matchesCategory(cat, bond, molgraph)) 
		return false;

	bool have_matches = false;

// category rules first

	for (TorsionCategory::ConstRuleIterator it = cat.getRulesBegin(), end = cat.getRulesEnd(); it != end; ++it) {
		if (getRuleMatches(*it, bond, molgraph)) {
			if (stopAtFirstRule)
				return true;

			have_matches = true;
		}
	}

// subcategories second

	for (TorsionCategory::ConstCategoryIterator it = cat.getCategoriesBegin(), end = cat.getCategoriesEnd(); it != end; ++it) {
		if (findMatchingRules(*it, bond, molgraph)) {
			if (stopAtFirstRule)
				return true;

			have_matches = true;
		}
	}

	return have_matches;
}

bool ConfGen::TorsionRuleMatcher::getRuleMatches(const TorsionRule& rule, const Chem::Bond& bond, 
												 const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	const MolecularGraph& ptn = *rule.getMatchPattern();
	std::size_t ctr_bond_idx = getCentralBondIndex(ptn);

	if (ctr_bond_idx == ptn.getNumBonds())
		return false;

	subSearch.clearBondMappingConstraints();
	subSearch.addBondMappingConstraint(ctr_bond_idx, molgraph.getBondIndex(bond));
	subSearch.setQuery(ptn);
	
	if (!subSearch.findMappings(molgraph)) 
		return false;

	std::size_t old_num_matches = matches.size();

	std::for_each(subSearch.getMappingsBegin(), subSearch.getMappingsEnd(), 
				  std::bind(&TorsionRuleMatcher::outputMatch, this, std::placeholders::_1,
							std::ref(bond), std::ref(rule))); 

	return (matches.size() > old_num_matches);
}

void ConfGen::TorsionRuleMatcher::outputMatch(const Chem::AtomBondMapping& ab_mapping, const Chem::Bond& bond, 
											  const TorsionRule& rule)
{
	using namespace Chem;

	const Atom* atoms[4] = { 0 };
	const AtomMapping& atm_mpg = ab_mapping.getAtomMapping();
	std::size_t mpd_atom_cnt = 0;

	for (AtomMapping::ConstEntryIterator it = atm_mpg.getEntriesBegin(), end = atm_mpg.getEntriesEnd(); it != end; ++it) {
		const Atom* ptn_atom = it->first;
		std::size_t am_id = getAtomMappingID(*ptn_atom);

		if (am_id == 0 || am_id > 4)
			continue;

		if (!atoms[am_id - 1])
			mpd_atom_cnt++;

		atoms[am_id - 1] = it->second;
	}
	
	if (mpd_atom_cnt < 3)
		return;

	if (uniqueMappingsOnly) {
		for (ConstMatchIterator it = matches.begin(), end = matches.end(); it != end; ++it) {
			const TorsionRuleMatch& match = *it;

			if (&match.getRule() != &rule)
				continue;

			if (&match.getBond() != &bond)
				continue;

			const Chem::Atom* const* mpd_atoms = match.getAtoms();

			if ((mpd_atoms[0] == atoms[0] && mpd_atoms[1] == atoms[1] && mpd_atoms[2] == atoms[2] && mpd_atoms[3] == atoms[3]) ||
				(mpd_atoms[3] == atoms[0] && mpd_atoms[2] == atoms[1] && mpd_atoms[1] == atoms[2] && mpd_atoms[0] == atoms[3]))
				return;
		}
	}

	matches.push_back(TorsionRuleMatch(rule, bond, atoms[0], atoms[1], atoms[2], atoms[3]));
}

bool ConfGen::TorsionRuleMatcher::matchesCategory(const TorsionCategory& cat, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	if (cat.getMatchPattern()) {
		const MolecularGraph& ptn = *cat.getMatchPattern();

		if (ptn.getNumBonds() > 0) {
			std::size_t ctr_bond_idx = getCentralBondIndex(ptn);

			if (ctr_bond_idx == ptn.getNumBonds())
				ctr_bond_idx = 0;

			subSearch.clearBondMappingConstraints();
			subSearch.addBondMappingConstraint(ctr_bond_idx, molgraph.getBondIndex(bond));
			subSearch.setQuery(ptn);
		
			return subSearch.mappingExists(molgraph);
		}
	}

	unsigned int atom1_type = getType(bond.getBegin());
	unsigned int atom2_type = getType(bond.getEnd());

	return ((atomTypesMatch(cat.getBondAtom1Type(), atom1_type) && atomTypesMatch(cat.getBondAtom2Type(), atom2_type)) ||
			 (atomTypesMatch(cat.getBondAtom1Type(), atom2_type) && atomTypesMatch(cat.getBondAtom2Type(), atom1_type)));
}

std::size_t ConfGen::TorsionRuleMatcher::getCentralBondIndex(const Chem::MolecularGraph& ptn) const
{
	using namespace Chem;

	std::size_t num_bonds = ptn.getNumBonds();

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = ptn.getBond(i);
		std::size_t am_id1 = getAtomMappingID(bond.getBegin());
		std::size_t am_id2 = getAtomMappingID(bond.getEnd());

		if ((am_id1 == 2 && am_id2 == 3) || (am_id1 == 3 && am_id2 == 2))
			return i;
	}

	return num_bonds;
}
