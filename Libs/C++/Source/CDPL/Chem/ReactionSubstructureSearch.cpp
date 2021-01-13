/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionSubstructureSearch.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/ReactionSubstructureSearch.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/AddressOf.hpp"


namespace
{
	
	const std::size_t MAX_MAPPING_CACHE_SIZE = 1000;
}


using namespace CDPL;


Chem::ReactionSubstructureSearch::ReactionSubstructureSearch(): 
	query(0), mappingCache(MAX_MAPPING_CACHE_SIZE), queryChanged(true), initQueryMappingData(true),
	uniqueMatches(false), enabledRxnRoles(ReactionRole::REACTANT | ReactionRole::AGENT | ReactionRole::PRODUCT),
	maxNumMappings(0) 
{
	mappingCache.setCleanupFunction(&AtomBondMapping::clear);
}

Chem::ReactionSubstructureSearch::ReactionSubstructureSearch(const Reaction& query): 
	mappingCache(MAX_MAPPING_CACHE_SIZE), uniqueMatches(false), 
	enabledRxnRoles(ReactionRole::REACTANT | ReactionRole::AGENT | ReactionRole::PRODUCT),
	maxNumMappings(0) 
{
	mappingCache.setCleanupFunction(&AtomBondMapping::clear);

	setQuery(query);
}

Chem::ReactionSubstructureSearch::~ReactionSubstructureSearch() {}

bool Chem::ReactionSubstructureSearch::mappingExists(const Reaction& target)
{
	freeAtomBondMappings();

	if (!init(target)) 
		return false;
	
	saveMappings = false;

	return mapAtoms();
}

bool Chem::ReactionSubstructureSearch::findMappings(const Reaction& target)
{
	freeAtomBondMappings();

	if (!init(target))
		return false;

	saveMappings = true;

	mapAtoms();

	return !foundMappings.empty();
}

std::size_t Chem::ReactionSubstructureSearch::getNumMappings() const
{
	return foundMappings.size();
}

Chem::AtomBondMapping& Chem::ReactionSubstructureSearch::getMapping(std::size_t idx)
{
	if (idx >= foundMappings.size())
		throw Base::IndexError("ReactionSubstructureSearch: mapping index out of bounds");

	return *foundMappings[idx];
}

const Chem::AtomBondMapping& Chem::ReactionSubstructureSearch::getMapping(std::size_t idx) const
{
	if (idx >= foundMappings.size())
		throw Base::IndexError("ReactionSubstructureSearch: mapping index out of bounds");

	return *foundMappings[idx];
}

Chem::ReactionSubstructureSearch::MappingIterator Chem::ReactionSubstructureSearch::getMappingsBegin()
{
	return foundMappings.begin();
}

Chem::ReactionSubstructureSearch::ConstMappingIterator Chem::ReactionSubstructureSearch::getMappingsBegin() const
{
	return foundMappings.begin();
}

Chem::ReactionSubstructureSearch::MappingIterator Chem::ReactionSubstructureSearch::getMappingsEnd()
{
	return foundMappings.end();
}

Chem::ReactionSubstructureSearch::ConstMappingIterator Chem::ReactionSubstructureSearch::getMappingsEnd() const
{
	return foundMappings.end();
}

void Chem::ReactionSubstructureSearch::uniqueMappingsOnly(bool unique)
{
	uniqueMatches = unique;
}

bool Chem::ReactionSubstructureSearch::uniqueMappingsOnly() const
{
	return uniqueMatches;
}

void Chem::ReactionSubstructureSearch::setMaxNumMappings(std::size_t max_num_mappings)
{
	maxNumMappings = max_num_mappings;
}

std::size_t Chem::ReactionSubstructureSearch::getMaxNumMappings() const
{
	return maxNumMappings;
}

void Chem::ReactionSubstructureSearch::setEnabledReactionRoles(unsigned int roles)
{
	enabledRxnRoles = roles;
}

unsigned int Chem::ReactionSubstructureSearch::getEnabledReactionRoles() const
{
	return enabledRxnRoles;
}

void Chem::ReactionSubstructureSearch::setQuery(const Reaction& query)
{
	this->query = &query;
	queryChanged = true;
	initQueryMappingData = true;
}

bool Chem::ReactionSubstructureSearch::init(const Reaction& tgt)
{
	if (!query)
		return false;

	target = &tgt;
	initTargetData();
		
	if (queryChanged) {
		initQueryData();
		queryChanged = false;
	}

	if ((*rxnMatchExpression)(*query, tgt, Base::Variant()) && findEquivAtoms() && findEquivBonds()) {
		if (initQueryMappingData) {
			queryMappingMask.reset();

			if (queryAtomMapping.size() < numQueryAtoms) 
				queryMappingMask.resize(numQueryAtoms);
				
			queryAtomMapping.assign(numQueryAtoms, 0);

			if (queryBondMapping.size() < numQueryBonds)
				queryBondMapping.resize(numQueryBonds);

			initQueryMappingData = false;
		}

		targetMappingMask.initAtomMask(numTargetAtoms);
		targetMappingMask.initBondMask(numTargetBonds);

		return true;
	}

	return false;
}

void Chem::ReactionSubstructureSearch::initQueryData()
{
	numQueryAtoms = 0;
	numQueryBonds = 0;

	queryABIndexOffsets.clear();

	queryAtoms.clear();
	queryBonds.clear();

	Reaction::ConstComponentIterator query_comps_end = query->getComponentsEnd();

	for (Reaction::ConstComponentIterator it = query->getComponentsBegin(); it != query_comps_end; ++it) {
		const Molecule& query_comp = *it;

		queryABIndexOffsets.push_back(IndexOffsetPair(numQueryAtoms, numQueryBonds));

		std::transform(query_comp.getAtomsBegin(), query_comp.getAtomsEnd(), std::back_inserter(queryAtoms),
					   boost::bind(Internal::AddressOf<const Atom>(), _1));

		std::transform(query_comp.getBondsBegin(), query_comp.getBondsEnd(), std::back_inserter(queryBonds),
					   boost::bind(Internal::AddressOf<const Bond>(), _1));

		numQueryAtoms += query_comp.getNumAtoms();
		numQueryBonds += query_comp.getNumBonds();
	}

	atomMatchExprTable.clear();
	atomMatchExprTable.reserve(numQueryAtoms);

	bondMatchExprTable.clear();
	bondMatchExprTable.reserve(numQueryBonds);

	postMappingMatchAtoms.clear();
	postMappingMatchBonds.clear();

	for (std::size_t i = 0; i < numQueryAtoms; i++) {
		const Atom* atom = queryAtoms[i];
		const MatchExpression<Atom, MolecularGraph>::SharedPointer& expr = getMatchExpression(*atom);

		if (expr->requiresAtomBondMapping())
			postMappingMatchAtoms.push_back(i);
		
		atomMatchExprTable.push_back(expr);
	}

	for (std::size_t i = 0; i < numQueryBonds; i++) {
		const Bond* bond = queryBonds[i];
		const MatchExpression<Bond, MolecularGraph>::SharedPointer& expr = getMatchExpression(*bond);

		if (expr->requiresAtomBondMapping())
			postMappingMatchBonds.push_back(i);
		
		bondMatchExprTable.push_back(expr);
	}

	rxnMatchExpression = getMatchExpression(*query);
}

void Chem::ReactionSubstructureSearch::initTargetData()
{
	numTargetAtoms = 0;
	numTargetBonds = 0;

	targetABIndexOffsets.clear();

	targetAtoms.clear();
	targetBonds.clear();

	Reaction::ConstComponentIterator target_comps_end = target->getComponentsEnd();

	for (Reaction::ConstComponentIterator it = target->getComponentsBegin(); it != target_comps_end; ++it) {
		const Molecule& target_comp = *it;

		targetABIndexOffsets.push_back(IndexOffsetPair(numTargetAtoms, numTargetBonds));

		std::transform(target_comp.getAtomsBegin(), target_comp.getAtomsEnd(), std::back_inserter(targetAtoms),
					   boost::bind(Internal::AddressOf<const Atom>(), _1));

		std::transform(target_comp.getBondsBegin(), target_comp.getBondsEnd(), std::back_inserter(targetBonds),
					   boost::bind(Internal::AddressOf<const Bond>(), _1));

		numTargetAtoms += target_comp.getNumAtoms();
		numTargetBonds += target_comp.getNumBonds();
	}
}

bool Chem::ReactionSubstructureSearch::findEquivAtoms()
{
	if (atomEquivMatrix.size() < numQueryAtoms)
		atomEquivMatrix.resize(numQueryAtoms);

	AtomList::const_iterator query_atoms_end = queryAtoms.end();

	AtomMatchExprTable::const_iterator ame_it = atomMatchExprTable.begin();
	BitMatrix::iterator tem_it = atomEquivMatrix.begin();

	for (AtomList::const_iterator qa_it = queryAtoms.begin(); qa_it != query_atoms_end; ++qa_it, ++tem_it, ++ame_it) {
		const Atom& query_atom = **qa_it;
		unsigned int query_atom_rxn_role = query->getComponentRole(query_atom.getMolecule());

		if ((enabledRxnRoles & query_atom_rxn_role) == 0)
			continue;

		const MatchExpression<Atom, MolecularGraph>& expr = **ame_it;
		Util::BitSet& equiv_mask = *tem_it;

		equiv_mask.reset();

		if (equiv_mask.size() < numTargetAtoms)
			equiv_mask.resize(numTargetAtoms);

		bool no_equiv_atoms = true;

		for (std::size_t i = 0; i < numTargetAtoms; i++) {
			const Atom* target_atom = targetAtoms[i];

			if (target->getComponentRole(target_atom->getMolecule()) != query_atom_rxn_role)
				continue;

			if (expr(query_atom, query_atom.getMolecule(), *target_atom, target_atom->getMolecule(), Base::Variant())) {
				equiv_mask.set(i);
				no_equiv_atoms = false;
			}
		}

		if (no_equiv_atoms)
			return false;
	}

	return true;
}

bool Chem::ReactionSubstructureSearch::findEquivBonds()
{
	if (bondEquivMatrix.size() < numQueryBonds)
		bondEquivMatrix.resize(numQueryBonds);

	BondList::const_iterator query_bonds_end = queryBonds.end();

	BondMatchExprTable::const_iterator bme_it = bondMatchExprTable.begin();
	BitMatrix::iterator tem_it = bondEquivMatrix.begin();

	for (BondList::const_iterator qb_it = queryBonds.begin(); qb_it != query_bonds_end; ++qb_it, ++tem_it, ++bme_it) {
		const Bond& query_bond = **qb_it;
		unsigned int query_bond_rxn_role = query->getComponentRole(query_bond.getMolecule());

		if ((enabledRxnRoles & query_bond_rxn_role) == 0)
			continue;

		const MatchExpression<Bond, MolecularGraph>& expr = **bme_it;
		Util::BitSet& equiv_mask = *tem_it;

		equiv_mask.reset();

		if (equiv_mask.size() < numTargetBonds)		
			equiv_mask.resize(numTargetBonds);

		bool no_equiv_bonds = true;

		for (std::size_t i = 0; i < numTargetBonds; i++) {
			const Bond* target_bond = targetBonds[i];

			if (target->getComponentRole(target_bond->getMolecule()) != query_bond_rxn_role)
				continue;

			if (expr(query_bond, query_bond.getMolecule(), *target_bond, target_bond->getMolecule(), Base::Variant())) {
				equiv_mask.set(i);
				no_equiv_bonds = false;
			}
		}

		if (no_equiv_bonds)
			return false;
	}

	return true;
}

bool Chem::ReactionSubstructureSearch::mapAtoms()
{
	std::size_t query_atom_idx = nextQueryAtom();

	if (query_atom_idx == numQueryAtoms)
		return mappingFound();

	unsigned int query_atom_rxn_role = query->getComponentRole(queryAtoms[query_atom_idx]->getMolecule());

	for (std::size_t target_atom_idx = 0, target_atom_nbr_idx = 0; 
		 nextTargetAtom(query_atom_idx, query_atom_rxn_role, target_atom_idx, target_atom_nbr_idx); 
		 target_atom_idx++, target_atom_nbr_idx++) {

		if (mapAtoms(query_atom_idx, target_atom_idx))
			return true;
	}

	return false;
}

std::size_t Chem::ReactionSubstructureSearch::nextQueryAtom() const
{
	std::size_t idx;

	if (!termQueryAtoms.empty()) 
		idx = termQueryAtoms.front();
	else 
		for (idx = 0; 
			 idx < numQueryAtoms && 
				 (queryAtomMapping[idx] || ((query->getComponentRole(queryAtoms[idx]->getMolecule()) & enabledRxnRoles) == 0)); 
			 idx++);

	assert(idx >= numQueryAtoms || !queryMappingMask.test(idx));

	return idx;
}

bool Chem::ReactionSubstructureSearch::nextTargetAtom(std::size_t query_atom_idx, unsigned int query_atom_rxn_role, 
													  std::size_t& target_atom_idx, std::size_t& target_atom_nbr_idx) const
{
	if (!termQueryAtoms.empty()) {
		const Atom* prev_target_atom = queryAtomMapping[query_atom_idx];
		std::size_t num_target_atom_nbrs = prev_target_atom->getNumBonds();
		std::size_t target_comp_idx = target->getComponentIndex(prev_target_atom->getMolecule());

		assert(target_comp_idx < targetABIndexOffsets.size());

		const IndexOffsetPair& target_offsets = targetABIndexOffsets[target_comp_idx];

		for ( ; target_atom_nbr_idx < num_target_atom_nbrs; target_atom_nbr_idx++) {
			const Atom& target_atom = prev_target_atom->getAtom(target_atom_nbr_idx);
			target_atom_idx = target_atom.getMolecule().getAtomIndex(target_atom) + target_offsets.first;

			if (!atomMappingAllowed(query_atom_idx, target_atom_idx))
				continue;

			return true;
		}

		return false;
	}

	for ( ; target_atom_idx < numTargetAtoms && (query_atom_rxn_role != target->getComponentRole(targetAtoms[target_atom_idx]->getMolecule()) 
										   || !atomMappingAllowed(query_atom_idx, target_atom_idx)); target_atom_idx++);

	return (target_atom_idx < numTargetAtoms);
}

bool Chem::ReactionSubstructureSearch::atomMappingAllowed(std::size_t query_atom_idx, std::size_t target_atom_idx) const
{
	return (!targetMappingMask.testAtomBit(target_atom_idx) && atomEquivMatrix[query_atom_idx].test(target_atom_idx));
}

bool Chem::ReactionSubstructureSearch::mapBonds(const Atom* query_atom, const Atom* target_atom, const IndexOffsetPair& query_offsets)
{
	Atom::ConstAtomIterator query_nbrs_end = query_atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = query_atom->getBondsBegin();

	const IndexOffsetPair& target_offsets = targetABIndexOffsets[target->getComponentIndex(target_atom->getMolecule())];

	std::size_t unmapped_query_nbrs = 0;

	for (Atom::ConstAtomIterator a_it = query_atom->getAtomsBegin(); a_it != query_nbrs_end; ++a_it, ++b_it) {
		std::size_t nbr_atom_idx = a_it->getMolecule().getAtomIndex(*a_it) + query_offsets.first;

		if (queryMappingMask.test(nbr_atom_idx)) {
			const Atom* mapped_target_atom = queryAtomMapping[nbr_atom_idx];
			const Bond* target_nbr_bond = target_atom->findBondToAtom(*mapped_target_atom);

			if (!target_nbr_bond)
				return false;

			std::size_t query_bond_idx = b_it->getMolecule().getBondIndex(*b_it) + query_offsets.second;
			std::size_t target_bond_idx = target_nbr_bond->getMolecule().getBondIndex(*target_nbr_bond) + target_offsets.second;

			if (!bondEquivMatrix[query_bond_idx].test(target_bond_idx))
				return false;

			queryBondMapping[query_bond_idx] = target_bond_idx;

		} else
			unmapped_query_nbrs++;
	}

	Atom::ConstAtomIterator target_nbrs_end = target_atom->getAtomsEnd();

	std::size_t unmapped_target_nbrs = 0;

	for (Atom::ConstAtomIterator a_it = target_atom->getAtomsBegin(); a_it != target_nbrs_end; ++a_it) {
		std::size_t nbr_atom_idx = a_it->getMolecule().getAtomIndex(*a_it) + target_offsets.first;

		if (!targetMappingMask.testAtomBit(nbr_atom_idx))
			unmapped_target_nbrs++;
	}

	return (unmapped_query_nbrs <= unmapped_target_nbrs);
}

bool Chem::ReactionSubstructureSearch::mapAtoms(std::size_t query_atom_idx, std::size_t target_atom_idx)
{
	const Atom* query_atom = queryAtoms[query_atom_idx];
	const Atom* target_atom = targetAtoms[target_atom_idx];

	std::size_t query_comp_idx = query->getComponentIndex(query_atom->getMolecule());

	assert(query_comp_idx < queryABIndexOffsets.size());

	const IndexOffsetPair& query_offsets = queryABIndexOffsets[query_comp_idx];

	if (!mapBonds(query_atom, target_atom, query_offsets))
		return false;

	bool had_term_atoms;

	if ((had_term_atoms = !termQueryAtoms.empty()))
		termQueryAtoms.pop_front();		

	const Atom* prev_mapping = queryAtomMapping[query_atom_idx];

	queryAtomMapping[query_atom_idx] = target_atom;

	queryMappingMask.set(query_atom_idx);
	targetMappingMask.setAtomBit(target_atom_idx);

	Atom::ConstAtomIterator atoms_end = query_atom->getAtomsEnd();
	std::size_t num_term_atoms = 0;

	for (Atom::ConstAtomIterator it = query_atom->getAtomsBegin(); it != atoms_end; ++it) {
		std::size_t nbr_atom_idx = it->getMolecule().getAtomIndex(*it) + query_offsets.first;

		if (!queryAtomMapping[nbr_atom_idx]) {
			queryAtomMapping[nbr_atom_idx] = target_atom;

			termQueryAtoms.push_back(nbr_atom_idx);
			num_term_atoms++;
		}
	}

	bool exit = mapAtoms();

	queryMappingMask.reset(query_atom_idx);
	targetMappingMask.resetAtomBit(target_atom_idx);

	for (std::size_t i = 0; i < num_term_atoms; i++) { 
		queryAtomMapping[termQueryAtoms.back()] = 0;
		termQueryAtoms.pop_back();
	}

	if (had_term_atoms)
		termQueryAtoms.push_front(query_atom_idx);

	queryAtomMapping[query_atom_idx] = prev_mapping;

	return exit;
}

bool Chem::ReactionSubstructureSearch::mappingFound()
{
	if (!hasPostMappingMatchExprs()) {
		if (!saveMappings)
			return true;

		if (uniqueMatches && !foundMappingUnique())
			return false;

		foundMappings.push_back(createAtomBondMapping());

		return (foundMappings.size() == maxNumMappings);
	}

	AtomBondMapping* mapping = createAtomBondMapping();

	if (!foundMappingMatches(mapping)) {
		freeAtomBondMapping();
		return false;
	}

	if (!saveMappings) {
		freeAtomBondMapping();
		return true;
	}

	if (uniqueMatches && !foundMappingUnique()) {
		freeAtomBondMapping();
		return false;
	}

	foundMappings.push_back(mapping);

	return (foundMappings.size() == maxNumMappings);
}

bool Chem::ReactionSubstructureSearch::hasPostMappingMatchExprs() const
{
	return (rxnMatchExpression->requiresAtomBondMapping() || 
			!postMappingMatchAtoms.empty() || !postMappingMatchBonds.empty());
}

bool Chem::ReactionSubstructureSearch::foundMappingMatches(const AtomBondMapping* mapping) const
{
	if (rxnMatchExpression->requiresAtomBondMapping() && !((*rxnMatchExpression)(*query, *target, *mapping, enabledRxnRoles)))
		return false;

	IndexList::const_iterator post_map_atoms_end = postMappingMatchAtoms.end();

	for (IndexList::const_iterator it = postMappingMatchAtoms.begin(); it != post_map_atoms_end; ++it) {
		std::size_t atom_idx = *it;
		const Atom& query_atom = *queryAtoms[atom_idx];

		if ((query->getComponentRole(query_atom.getMolecule()) & enabledRxnRoles) == 0)
			continue;

		if (!(*atomMatchExprTable[atom_idx])(query_atom, query_atom.getMolecule(), *queryAtomMapping[atom_idx], 
											 queryAtomMapping[atom_idx]->getMolecule(), *mapping, Base::Variant()))
			return false;
	}

	IndexList::const_iterator post_map_bonds_end = postMappingMatchBonds.end();

	for (IndexList::const_iterator it = postMappingMatchBonds.begin(); it != post_map_bonds_end; ++it) {
		std::size_t bond_idx = *it;
		const Bond& query_bond = *queryBonds[bond_idx];

		if ((query->getComponentRole(query_bond.getMolecule()) & enabledRxnRoles) == 0)
			continue;

		if (!(*bondMatchExprTable[bond_idx])(query_bond, query_bond.getMolecule(), *targetBonds[queryBondMapping[bond_idx]],
											 targetBonds[queryBondMapping[bond_idx]]->getMolecule(), *mapping, Base::Variant()))
			return false;
	}

	return true;
}

bool Chem::ReactionSubstructureSearch::foundMappingUnique()
{
	targetMappingMask.resetBondMask();

	for (std::size_t i = 0; i < numQueryBonds; i++) {
		const Bond& query_bond = *queryBonds[i];

		if ((query->getComponentRole(query_bond.getMolecule()) & enabledRxnRoles) == 0)
			continue;

		targetMappingMask.setBondBit(queryBondMapping[i]);
	}

	return uniqueMappings.insert(targetMappingMask).second;
}

void Chem::ReactionSubstructureSearch::freeAtomBondMappings()
{
	mappingCache.putAll();
	foundMappings.clear();

	if (uniqueMatches)
		uniqueMappings.clear();
}

Chem::AtomBondMapping* Chem::ReactionSubstructureSearch::createAtomBondMapping()
{
	AtomBondMapping* mapping = mappingCache.getRaw();
	AtomMapping& atom_mapping = mapping->getAtomMapping();
	BondMapping& bond_mapping = mapping->getBondMapping();

	AtomList::const_iterator atoms_end = queryAtoms.end();
	AtomMappingTable::const_iterator am_it = queryAtomMapping.begin();

	for (AtomList::const_iterator a_it = queryAtoms.begin(); a_it != atoms_end; ++a_it, ++am_it) {
		const Atom* query_atom = *a_it;

		if ((query->getComponentRole(query_atom->getMolecule()) & enabledRxnRoles) == 0)
			continue;

		atom_mapping.insertEntry(query_atom, *am_it);
	}

	BondList::const_iterator bonds_end = queryBonds.end();
	BondMappingTable::const_iterator bm_it = queryBondMapping.begin();

	for (BondList::const_iterator b_it = queryBonds.begin(); b_it != bonds_end; ++b_it, ++bm_it) {
		const Bond* query_bond = *b_it;

		if ((query->getComponentRole(query_bond->getMolecule()) & enabledRxnRoles) == 0)
			continue;

		bond_mapping.insertEntry(query_bond, targetBonds[*bm_it]);
	}

	return mapping;
}

void Chem::ReactionSubstructureSearch::freeAtomBondMapping()
{
	mappingCache.put();
}


void Chem::ReactionSubstructureSearch::ABMappingMask::initAtomMask(std::size_t num_atoms)
{
	atomMask.reset();

	if (atomMask.size() < num_atoms)
		atomMask.resize(num_atoms);
}

void Chem::ReactionSubstructureSearch::ABMappingMask::initBondMask(std::size_t num_bonds)
{
	if (bondMask.size() < num_bonds)
		bondMask.resize(num_bonds);
}

void Chem::ReactionSubstructureSearch::ABMappingMask::setAtomBit(std::size_t atom_idx)
{
	atomMask.set(atom_idx);
}

void Chem::ReactionSubstructureSearch::ABMappingMask::resetAtomBit(std::size_t atom_idx)
{
	atomMask.reset(atom_idx);
}

bool Chem::ReactionSubstructureSearch::ABMappingMask::testAtomBit(std::size_t atom_idx) const
{
	return atomMask.test(atom_idx);
}

void Chem::ReactionSubstructureSearch::ABMappingMask::setBondBit(std::size_t bond_idx)
{
	bondMask.set(bond_idx);
}

void Chem::ReactionSubstructureSearch::ABMappingMask::resetBondMask()
{
	bondMask.reset();
}

bool Chem::ReactionSubstructureSearch::ABMappingMask::operator<(const ABMappingMask& mask) const
{
	if (atomMask == mask.atomMask)
		return (bondMask < mask.bondMask);

	return (atomMask < mask.atomMask);
}

bool Chem::ReactionSubstructureSearch::ABMappingMask::operator>(const ABMappingMask& mask) const
{
	if (atomMask == mask.atomMask)
		return (bondMask > mask.bondMask);

	return (atomMask > mask.atomMask);
}
