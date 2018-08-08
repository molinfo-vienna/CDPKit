/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CommonConnectedSubstructureSearch.cpp 
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

#include <cassert>

#include "CDPL/Chem/CommonConnectedSubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Internal/RangeGenerator.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::CommonConnectedSubstructureSearch::CommonConnectedSubstructureSearch(): 
	query(0), queryChanged(true), initQueryData(true),
	uniqueMatches(false), numMappedAtoms(0), maxNumMappings(0), minSubstructureSize(0) 
{}

Chem::CommonConnectedSubstructureSearch::CommonConnectedSubstructureSearch(const MolecularGraph& query): 
	uniqueMatches(false), numMappedAtoms(0), maxNumMappings(0), minSubstructureSize(0) 
{
	setQuery(query);
}

Chem::CommonConnectedSubstructureSearch::~CommonConnectedSubstructureSearch() {}

bool Chem::CommonConnectedSubstructureSearch::mappingExists(const MolecularGraph& target)
{
	clearMappings();

	if (!init(target))
		return false;

	saveMappings = false;

	return mapAtoms();
}

bool Chem::CommonConnectedSubstructureSearch::findAllMappings(const MolecularGraph& target)
{
	clearMappings();

	if (!init(target))
		return false;

	saveMappings = true;
	maxMappingsOnly = false;

	mapAtoms();

	return !foundMappings.empty();
}

bool Chem::CommonConnectedSubstructureSearch::findMaxMappings(const MolecularGraph& target)
{
	clearMappings();

	if (!init(target))
		return false;

	saveMappings = true;
	maxMappingsOnly = true;

	mapAtoms();

	return !foundMappings.empty();
}

std::size_t Chem::CommonConnectedSubstructureSearch::getNumMappings() const
{
	return foundMappings.size();
}

Chem::AtomBondMapping& Chem::CommonConnectedSubstructureSearch::getMapping(std::size_t idx)
{
	if (idx >= foundMappings.size())
		throw Base::IndexError("CommonConnectedSubstructureSearch: mapping index out of bounds");

	return *foundMappings[idx];
}

const Chem::AtomBondMapping& Chem::CommonConnectedSubstructureSearch::getMapping(std::size_t idx) const
{
	if (idx >= foundMappings.size())
		throw Base::IndexError("CommonConnectedSubstructureSearch: mapping index out of bounds");

	return *foundMappings[idx];
}

Chem::CommonConnectedSubstructureSearch::MappingIterator Chem::CommonConnectedSubstructureSearch::getMappingsBegin()
{
	return foundMappings.begin();
}

Chem::CommonConnectedSubstructureSearch::ConstMappingIterator Chem::CommonConnectedSubstructureSearch::getMappingsBegin() const
{
	return foundMappings.begin();
}

Chem::CommonConnectedSubstructureSearch::MappingIterator Chem::CommonConnectedSubstructureSearch::getMappingsEnd()
{
	return foundMappings.end();
}

Chem::CommonConnectedSubstructureSearch::ConstMappingIterator Chem::CommonConnectedSubstructureSearch::getMappingsEnd() const
{
	return foundMappings.end();
}

void Chem::CommonConnectedSubstructureSearch::uniqueMappingsOnly(bool unique)
{
	uniqueMatches = unique;
}

bool Chem::CommonConnectedSubstructureSearch::uniqueMappingsOnly() const
{
	return uniqueMatches;
}

void Chem::CommonConnectedSubstructureSearch::setMaxNumMappings(std::size_t max_num_mappings)
{
	maxNumMappings = max_num_mappings;
}

std::size_t Chem::CommonConnectedSubstructureSearch::getMaxNumMappings() const
{
	return maxNumMappings;
}

void Chem::CommonConnectedSubstructureSearch::setMinSubstructureSize(std::size_t min_size)
{
	minSubstructureSize = min_size;
}

std::size_t Chem::CommonConnectedSubstructureSearch::getMinSubstructureSize() const
{
	return minSubstructureSize;
}

void Chem::CommonConnectedSubstructureSearch::setQuery(const MolecularGraph& query)
{
	this->query = &query;
	queryChanged = true;
	initQueryData = true;
}

bool Chem::CommonConnectedSubstructureSearch::init(const MolecularGraph& tgt)
{
	if (!query)
		return false;

	target = &tgt;
	numTargetAtoms = target->getNumAtoms();
	numTargetBonds = target->getNumBonds();
	
	if (queryChanged) {
		numQueryAtoms = query->getNumAtoms();
		numQueryBonds = query->getNumBonds();

		initMatchExpressions();

		queryChanged = false;
	}

	if ((*molGraphMatchExpr)(*query, tgt, Base::Variant()) && findEquivAtoms() && findEquivBonds()) {
		if (initQueryData) {
			hiddenQueryAtomMask.reset();
			termQueryAtomMask.reset();

			if (queryAtomMapping.size() < numQueryAtoms) {
				hiddenQueryAtomMask.resize(numQueryAtoms);
				termQueryAtomMask.resize(numQueryAtoms);
			}

			queryAtomMapping.assign(numQueryAtoms, 0);

			mappingMask.initQueryAtomMask(numQueryAtoms);
			mappingMask.initQueryBondMask(numQueryBonds);

			initQueryData = false;
		}

		if (termTargetAtomMask.size() < numTargetAtoms)
			termTargetAtomMask.resize(numTargetAtoms);

		mappingMask.initTargetAtomMask(numTargetAtoms);
		mappingMask.initTargetBondMask(numTargetBonds);
		
		return true;
	}

	return false;
}

void Chem::CommonConnectedSubstructureSearch::initMatchExpressions()
{
	atomMatchExprTable.clear();
	atomMatchExprTable.reserve(numQueryAtoms);

	bondMatchExprTable.clear();
	bondMatchExprTable.reserve(numQueryBonds);

	postMappingMatchAtoms.clear();
	postMappingMatchBonds.clear();

	MolecularGraph::ConstAtomIterator atoms_end = query->getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = query->getAtomsBegin(); it != atoms_end; ++it) {
		const Atom* atom = &*it;
		const MatchExpression<Atom, MolecularGraph>::SharedPointer& expr = getMatchExpression(*atom);

		if (expr->requiresAtomBondMapping())
			postMappingMatchAtoms.push_back(atom);
		
		atomMatchExprTable.push_back(expr);
	}

	MolecularGraph::ConstBondIterator bonds_end = query->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = query->getBondsBegin(); it != bonds_end; ++it) {
		const Bond* bond = &*it;

		if (!query->containsAtom(bond->getBegin()) || !query->containsAtom(bond->getEnd())) {
			bondMatchExprTable.push_back(MatchExpression<Bond, MolecularGraph>::SharedPointer());
			continue;
		}

		const MatchExpression<Bond, MolecularGraph>::SharedPointer& expr = getMatchExpression(*bond);

		if (expr->requiresAtomBondMapping())
			postMappingMatchBonds.push_back(bond);
		
		bondMatchExprTable.push_back(expr);
	}

	molGraphMatchExpr = getMatchExpression(*query);
}

bool Chem::CommonConnectedSubstructureSearch::findEquivAtoms()
{
	if (numQueryAtoms == 0)
		return true;

	if (atomEquivMatrix.size() < numQueryAtoms)
		atomEquivMatrix.resize(numQueryAtoms);

	MolecularGraph::ConstAtomIterator query_atoms_end = query->getAtomsEnd();
	MolecularGraph::ConstAtomIterator target_atoms_beg = target->getAtomsBegin();
	MolecularGraph::ConstAtomIterator target_atoms_end = target->getAtomsEnd();

	AtomMatchExprTable::const_iterator ame_it = atomMatchExprTable.begin();
	BitMatrix::iterator tem_it = atomEquivMatrix.begin();

	bool equiv_atoms_found = false;

	for (MolecularGraph::ConstAtomIterator pa_it = query->getAtomsBegin(); pa_it != query_atoms_end; ++pa_it, ++tem_it, ++ame_it) {
		const Atom& query_atom = *pa_it;
		const MatchExpression<Atom, MolecularGraph>& expr = **ame_it;
		Util::BitSet& equiv_mask = *tem_it;

		equiv_mask.reset();

		if (equiv_mask.size() < numTargetAtoms)
			equiv_mask.resize(numTargetAtoms);

		for (MolecularGraph::ConstAtomIterator ta_it = target_atoms_beg; ta_it != target_atoms_end; ++ta_it) {
			const Atom& target_atom = *ta_it;

			if (expr(query_atom, *query, target_atom, *target, Base::Variant())) {
				equiv_mask.set(target->getAtomIndex(target_atom));
				equiv_atoms_found = true;
			}
		}
	}

	return equiv_atoms_found;
}

bool Chem::CommonConnectedSubstructureSearch::findEquivBonds()
{
	if (numQueryBonds == 0)
		return true;

	if (bondEquivMatrix.size() < numQueryBonds)
		bondEquivMatrix.resize(numQueryBonds);

	MolecularGraph::ConstBondIterator query_bonds_end = query->getBondsEnd();
	MolecularGraph::ConstBondIterator target_bonds_beg = target->getBondsBegin();
	MolecularGraph::ConstBondIterator target_bonds_end = target->getBondsEnd();

	BondMatchExprTable::const_iterator bme_it = bondMatchExprTable.begin();
	BitMatrix::iterator tem_it = bondEquivMatrix.begin();

	bool equiv_bonds_found = false;

	for (MolecularGraph::ConstBondIterator pb_it = query->getBondsBegin(); pb_it != query_bonds_end; ++pb_it, ++tem_it, ++bme_it) {
		Util::BitSet& equiv_mask = *tem_it;

		equiv_mask.reset();

		if (equiv_mask.size() < numTargetBonds)		
			equiv_mask.resize(numTargetBonds);

		if (!*bme_it)
			continue;

		const Bond& query_bond = *pb_it;
		const MatchExpression<Bond, MolecularGraph>& expr = **bme_it;

		for (MolecularGraph::ConstBondIterator tb_it = target_bonds_beg; tb_it != target_bonds_end; ++tb_it) {
			const Bond& target_bond = *tb_it;

			if (expr(query_bond, *query, target_bond, *target, Base::Variant())) {
				equiv_mask.set(target->getBondIndex(target_bond));
				equiv_bonds_found = true;
			}
		}
	}

	return equiv_bonds_found;
}

bool Chem::CommonConnectedSubstructureSearch::mapAtoms()
{
	if (termQueryAtoms.empty()) {
		if (numMappedAtoms > 0) 
			return mappingFound();

		for (std::size_t num_free_atoms = numQueryAtoms, i = 0; i < numQueryAtoms; i++, num_free_atoms--) {
			if (num_free_atoms < minSubstructureSize || num_free_atoms < currMaxSubstructureSize) 
				return true;

			hiddenQueryAtomMask.set(i);

			if (mapAtoms(i))
				return true;
		}

	} else
		return mapAtoms(termQueryAtoms.front());

	return false; 
}

bool Chem::CommonConnectedSubstructureSearch::mapAtoms(std::size_t query_atom_idx)
{
	bool has_term_atoms = !termQueryAtoms.empty();

	for (std::size_t target_atom_idx = 0, target_atom_list_idx = 0; nextTargetAtom(query_atom_idx, target_atom_idx, target_atom_list_idx); 
		 target_atom_idx++, target_atom_list_idx++) {

		if (has_term_atoms) {
			std::size_t last_idx = termTargetAtoms.back();

			termTargetAtoms[target_atom_list_idx] = last_idx;
			termTargetAtoms.pop_back();

			bool exit = mapAtoms(query_atom_idx, target_atom_idx);

			termTargetAtoms.push_back(last_idx);
			termTargetAtoms[target_atom_list_idx] = target_atom_idx;

			if (exit)
				return true;

		} else if (mapAtoms(query_atom_idx, target_atom_idx))
			return true;
	}

	if (has_term_atoms) {
		termQueryAtoms.pop_front();
		termQueryAtomMask.reset(query_atom_idx);

		bool exit = mapAtoms();

		termQueryAtomMask.set(query_atom_idx);
		termQueryAtoms.push_front(query_atom_idx);

		return exit;
	}

	return false;
}

bool Chem::CommonConnectedSubstructureSearch::mapAtoms(std::size_t query_atom_idx, std::size_t target_atom_idx)
{
	const Atom& query_atom = query->getAtom(query_atom_idx);
	const Atom& target_atom = target->getAtom(target_atom_idx);

	Atom::ConstAtomIterator atoms_end = query_atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = query_atom.getBondsBegin();

	std::size_t num_mapped_bonds = 0;
	bool has_mapped_nbr = false;

	for (Atom::ConstAtomIterator a_it = query_atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!query->containsAtom(*a_it) || !query->containsBond(*b_it))
			continue;

		std::size_t nbr_atom_idx = query->getAtomIndex(*a_it);
		const Atom* mapped_target_atom = queryAtomMapping[nbr_atom_idx];

		if (!mapped_target_atom)
			continue;

		has_mapped_nbr = true;

		const Bond* target_nbr_bond = target_atom.findBondToAtom(*mapped_target_atom);

		if (!target_nbr_bond || !target->containsBond(*target_nbr_bond))
			continue;

		std::size_t query_bond_idx = query->getBondIndex(*b_it);
		std::size_t target_bond_idx = target->getBondIndex(*target_nbr_bond);

		if (!bondEquivMatrix[query_bond_idx].test(target_bond_idx)) 
			continue;

		bondMappingStack.push_back(query_bond_idx);
		bondMappingStack.push_back(target_bond_idx);

		num_mapped_bonds++;
	}

	if (has_mapped_nbr && num_mapped_bonds == 0) 
		return false;

	bool had_term_atoms;

	if ((had_term_atoms = !termQueryAtoms.empty()))
		termQueryAtoms.pop_front();		

	else {
		termQueryAtomMask.set(query_atom_idx);
		termTargetAtomMask.set(target_atom_idx);
	}

	queryAtomMapping[query_atom_idx] = &target_atom;

	mappingMask.setQueryAtomBit(query_atom_idx);
	mappingMask.setTargetAtomBit(target_atom_idx);

	std::size_t num_term_query_atoms = 0;

	b_it = query_atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = query_atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!query->containsAtom(*a_it) || !query->containsBond(*b_it))
			continue;

		std::size_t nbr_atom_idx = query->getAtomIndex(*a_it);

		if (hiddenQueryAtomMask.test(nbr_atom_idx) || termQueryAtomMask.test(nbr_atom_idx))
			continue;

		assert(queryAtomMapping[nbr_atom_idx] == 0);

		termQueryAtoms.push_back(nbr_atom_idx);
		termQueryAtomMask.set(nbr_atom_idx);
		num_term_query_atoms++;
	}

	std::size_t num_term_target_atoms = 0;

	atoms_end = target_atom.getAtomsEnd();
	b_it = target_atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = target_atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!target->containsAtom(*a_it) || !target->containsBond(*b_it))
			continue;

		std::size_t nbr_atom_idx = target->getAtomIndex(*a_it);

		if (termTargetAtomMask.test(nbr_atom_idx))
			continue;

		assert(mappingMask.testTargetAtomBit(nbr_atom_idx) == false);

		termTargetAtoms.push_back(nbr_atom_idx);
		termTargetAtomMask.set(nbr_atom_idx);
		num_term_target_atoms++;
	}

	numMappedAtoms++;

	bool exit = mapAtoms();

	numMappedAtoms--;

	mappingMask.resetQueryAtomBit(query_atom_idx);
	mappingMask.resetTargetAtomBit(target_atom_idx);

	for (std::size_t i = 0; i < num_term_query_atoms; i++) { 
		termQueryAtomMask.reset(termQueryAtoms.back());
		termQueryAtoms.pop_back();
	}

	for (std::size_t i = 0; i < num_term_target_atoms; i++) { 
		termTargetAtomMask.reset(termTargetAtoms.back());
		termTargetAtoms.pop_back();
	}

	if (had_term_atoms)
		termQueryAtoms.push_front(query_atom_idx);

	else {
		termQueryAtomMask.reset(query_atom_idx);
		termTargetAtomMask.reset(target_atom_idx);
	}

	queryAtomMapping[query_atom_idx] = 0;

	bondMappingStack.erase(bondMappingStack.end() - (num_mapped_bonds * 2), bondMappingStack.end());

	return exit;
}

bool Chem::CommonConnectedSubstructureSearch::nextTargetAtom(std::size_t query_atom_idx, std::size_t& target_atom_idx, 
															 std::size_t& target_atom_list_idx) const
{
	if (!termQueryAtoms.empty()) {
		std::size_t target_atom_list_size = termTargetAtoms.size();

		for ( ; target_atom_list_idx < target_atom_list_size; target_atom_list_idx++) {
			target_atom_idx = termTargetAtoms[target_atom_list_idx];

			assert(mappingMask.testTargetAtomBit(target_atom_idx) == false);

			if (!atomEquivMatrix[query_atom_idx].test(target_atom_idx))
				continue;

			return true;
		}

		return false;
	}

	for ( ; target_atom_idx < numTargetAtoms && (mappingMask.testTargetAtomBit(target_atom_idx) ||
												 !atomEquivMatrix[query_atom_idx].test(target_atom_idx)); 
		  target_atom_idx++);

	return (target_atom_idx < numTargetAtoms);
}

bool Chem::CommonConnectedSubstructureSearch::mappingFound()
{
	if (numMappedAtoms < minSubstructureSize)
		return false;

	if (!hasPostMappingMatchExprs()) {
		if (!saveMappings)
			return true;

		if (maxMappingsOnly) {
			std::size_t bond_stack_size = bondMappingStack.size();

			if (numMappedAtoms < currMaxSubstructureSize 
				|| (numMappedAtoms == currMaxSubstructureSize && bond_stack_size < maxBondStackSize))
				return false;

			if (numMappedAtoms > currMaxSubstructureSize || bond_stack_size > maxBondStackSize) {
				currMaxSubstructureSize = numMappedAtoms;
				maxBondStackSize = bond_stack_size;

				freeAtomBondMappings();

				foundMappings.push_back(createAtomBondMapping());

				if (uniqueMatches)
					foundMappingUnique();

				return (foundMappings.size() == maxNumMappings);
			}
		}

		if (uniqueMatches) {
			if (!foundMappingUnique())
				return false;

			foundMappings.push_back(createAtomBondMapping());

		} else {
			AtomBondMapping* mapping = createAtomBondMapping();

			if (mappingAlreadySeen(mapping)) {
				freeAtomBondMapping();
				return false;
			}
	
			foundMappings.push_back(mapping);
		}

		return (foundMappings.size() == maxNumMappings);
	}

	std::size_t bond_stack_size = bondMappingStack.size();

	if (maxMappingsOnly && (numMappedAtoms < currMaxSubstructureSize 
							|| (numMappedAtoms == currMaxSubstructureSize && bond_stack_size < maxBondStackSize)))
		return false;

	AtomBondMapping* mapping = createAtomBondMapping();

	if (!foundMappingMatches(mapping)) {
		freeAtomBondMapping();
		return false;
	}

	if (!saveMappings) {
		freeAtomBondMapping();
		return true;
	}

	if (maxMappingsOnly && (numMappedAtoms > currMaxSubstructureSize || bond_stack_size > maxBondStackSize)) {
		currMaxSubstructureSize = numMappedAtoms;
		maxBondStackSize = bond_stack_size;

		freeAtomBondMappings();

		foundMappings.push_back(mapping);

		if (uniqueMatches)
			foundMappingUnique();

		return (foundMappings.size() == maxNumMappings);
	}

	if (uniqueMatches) {
		if (!foundMappingUnique()) {
			freeAtomBondMapping();
			return false;
		}

	} else if (mappingAlreadySeen(mapping)) {
		freeAtomBondMapping();
		return false;
	}

	foundMappings.push_back(mapping);

	return (foundMappings.size() == maxNumMappings);
}

bool Chem::CommonConnectedSubstructureSearch::hasPostMappingMatchExprs() const
{
	return (molGraphMatchExpr->requiresAtomBondMapping() || !postMappingMatchAtoms.empty() || !postMappingMatchBonds.empty());
}

bool Chem::CommonConnectedSubstructureSearch::foundMappingMatches(const AtomBondMapping* mapping) const
{
	if (molGraphMatchExpr->requiresAtomBondMapping() && 
		!((*molGraphMatchExpr)(*query, *target, *mapping, Base::Variant())))
		return false;

	AtomList::const_iterator post_map_atoms_end = postMappingMatchAtoms.end();

	for (AtomList::const_iterator it = postMappingMatchAtoms.begin(); it != post_map_atoms_end; ++it) {
		const Atom& query_atom = **it;
		std::size_t query_atom_idx = query->getAtomIndex(query_atom);

		const Atom* target_atom = queryAtomMapping[query_atom_idx];

		if (!target_atom)
			continue;

		if (!(*atomMatchExprTable[query_atom_idx])(query_atom, *query, *target_atom, 
												   *target, *mapping, Base::Variant()))
			return false;
	}

	const BondMapping& bond_mapping = mapping->getBondMapping();

	BondList::const_iterator post_map_bonds_end = postMappingMatchBonds.end();

	for (BondList::const_iterator it = postMappingMatchBonds.begin(); it != post_map_bonds_end; ++it) {
		const Bond* query_bond = *it;
		const Bond* target_bond = bond_mapping[query_bond];

		if (!target_bond)
			continue;

		if (!(*bondMatchExprTable[query->getBondIndex(*query_bond)])(*query_bond, *query, *target_bond, 
																	 *target, *mapping, Base::Variant()))
			return false;
	}

	return true;
}

bool Chem::CommonConnectedSubstructureSearch::foundMappingUnique()
{
	mappingMask.resetBondMasks();

	BondMappingStack::const_iterator bond_stack_end = bondMappingStack.end();

	for (BondMappingStack::const_iterator it = bondMappingStack.begin(); it != bond_stack_end; ++it) { 
		std::size_t query_bond_idx = *it;
		std::size_t target_bond_idx = *(++it);

		mappingMask.setQueryBondBit(query_bond_idx);
		mappingMask.setTargetBondBit(target_bond_idx);
	}

	return uniqueMappings.insert(mappingMask).second;
}

bool Chem::CommonConnectedSubstructureSearch::mappingAlreadySeen(const AtomBondMapping* mapping) const
{
	ABMappingList::const_iterator mappings_end = foundMappings.end();

	for (ABMappingList::const_iterator it = foundMappings.begin(); it != mappings_end; ++it)
		if (**it == *mapping) 
			return true;

	return false;
}

void Chem::CommonConnectedSubstructureSearch::clearMappings()
{
	freeAtomBondMappings();

	hiddenQueryAtomMask.reset();

	currMaxSubstructureSize = 0;
	maxBondStackSize = 0;
}

void Chem::CommonConnectedSubstructureSearch::freeAtomBondMappings() 
{
	freeMappingIdx = 0;

	foundMappings.clear();

	if (uniqueMatches)
		uniqueMappings.clear();
}

Chem::AtomBondMapping* Chem::CommonConnectedSubstructureSearch::createAtomBondMapping()
{
	AtomBondMapping* mapping;

	if (freeMappingIdx == allocMappings.size()) {
		AtomBondMapping::SharedPointer mapping_ptr(new AtomBondMapping());
		allocMappings.push_back(mapping_ptr);

		mapping = mapping_ptr.get();
		freeMappingIdx++;

	} else {
		mapping = allocMappings[freeMappingIdx++].get();

		mapping->clear();
	}

	AtomMapping& atom_mapping = mapping->getAtomMapping();
	BondMapping& bond_mapping = mapping->getBondMapping();

	for (std::size_t i = 0; i < numQueryAtoms; i++) {
		const Atom* target_atom = queryAtomMapping[i];

		if (target_atom)
			atom_mapping.insertEntry(&query->getAtom(i), target_atom);
	}

	BondMappingStack::const_iterator bond_maps_end = bondMappingStack.end();

	for (BondMappingStack::const_iterator it = bondMappingStack.begin(); it != bond_maps_end; ++it) {
		const Bond& query_bond = query->getBond(*it);
		const Bond& target_bond = target->getBond(*(++it));

		bond_mapping.insertEntry(&query_bond, &target_bond);
	}

	return mapping;
}

void Chem::CommonConnectedSubstructureSearch::freeAtomBondMapping()
{
	freeMappingIdx--;
}


void Chem::CommonConnectedSubstructureSearch::ABMappingMask::initQueryAtomMask(std::size_t num_atoms)
{
	queryAtomMask.reset();

	if (queryAtomMask.size() < num_atoms)
		queryAtomMask.resize(num_atoms);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::initTargetAtomMask(std::size_t num_atoms)
{
	targetAtomMask.reset();

	if (targetAtomMask.size() < num_atoms)
		targetAtomMask.resize(num_atoms);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::initQueryBondMask(std::size_t num_bonds)
{
	if (queryBondMask.size() < num_bonds)
		queryBondMask.resize(num_bonds);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::initTargetBondMask(std::size_t num_bonds)
{
	if (targetBondMask.size() < num_bonds)
		targetBondMask.resize(num_bonds);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::setQueryAtomBit(std::size_t atom_idx)
{
	queryAtomMask.set(atom_idx);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::setTargetAtomBit(std::size_t atom_idx)
{
	targetAtomMask.set(atom_idx);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::resetQueryAtomBit(std::size_t atom_idx)
{
	queryAtomMask.reset(atom_idx);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::resetTargetAtomBit(std::size_t atom_idx)
{
	targetAtomMask.reset(atom_idx);
}

bool Chem::CommonConnectedSubstructureSearch::ABMappingMask::testTargetAtomBit(std::size_t atom_idx) const
{
	return targetAtomMask.test(atom_idx);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::setQueryBondBit(std::size_t bond_idx)
{
	queryBondMask.set(bond_idx);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::setTargetBondBit(std::size_t bond_idx)
{
	targetBondMask.set(bond_idx);
}

void Chem::CommonConnectedSubstructureSearch::ABMappingMask::resetBondMasks()
{
	queryBondMask.reset();
	targetBondMask.reset();
}

bool Chem::CommonConnectedSubstructureSearch::ABMappingMask::operator<(const ABMappingMask& mask) const
{
	if (queryAtomMask == mask.queryAtomMask) {
		if (queryBondMask == mask.queryBondMask) {
			if (targetAtomMask == mask.targetAtomMask) {
				return (targetBondMask < mask.targetBondMask);
			}

			return (targetAtomMask < mask.targetAtomMask);
		}

		return (queryBondMask < mask.queryBondMask);
	}

	return (queryAtomMask < mask.queryAtomMask);
}

bool Chem::CommonConnectedSubstructureSearch::ABMappingMask::operator>(const ABMappingMask& mask) const
{
	if (queryAtomMask == mask.queryAtomMask) {
		if (queryBondMask == mask.queryBondMask) {
			if (targetAtomMask == mask.targetAtomMask) {
				return (targetBondMask > mask.targetBondMask);
			}

			return (targetAtomMask > mask.targetAtomMask);
		}

		return (queryBondMask > mask.queryBondMask);
	}

	return (queryAtomMask > mask.queryAtomMask);
}
