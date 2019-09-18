/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MaxCommonAtomSubstructureSearch.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/MaxCommonAtomSubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{
	
	const std::size_t MAX_NODE_CACHE_SIZE    = 10000;
	const std::size_t MAX_EDGE_CACHE_SIZE    = 10000;
	const std::size_t MAX_MAPPING_CACHE_SIZE = 1000;
}


using namespace CDPL;


Chem::MaxCommonAtomSubstructureSearch::MaxCommonAtomSubstructureSearch(): 
	query(0), nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE), 
	mappingCache(MAX_MAPPING_CACHE_SIZE), queryChanged(true), initQueryData(true), 
	uniqueMatches(false), currNumNullNodes(0), maxNumMappings(0), minSubstructureSize(0) 
{
	mappingCache.setCleanupFunction(&AtomBondMapping::clear);
}

Chem::MaxCommonAtomSubstructureSearch::MaxCommonAtomSubstructureSearch(const MolecularGraph& query): 
	nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE), mappingCache(MAX_MAPPING_CACHE_SIZE), 
	uniqueMatches(false), currNumNullNodes(0), maxNumMappings(0), minSubstructureSize(0)
{
	mappingCache.setCleanupFunction(&AtomBondMapping::clear);

	setQuery(query);
}

Chem::MaxCommonAtomSubstructureSearch::~MaxCommonAtomSubstructureSearch() {}

bool Chem::MaxCommonAtomSubstructureSearch::mappingExists(const MolecularGraph& target)
{
	clearMappings();

	if (!init(target))
		return false;

	saveMappings = false;

	return findAssocGraphCliques(0);
}

bool Chem::MaxCommonAtomSubstructureSearch::findAllMappings(const MolecularGraph& target)
{
	clearMappings();

	if (!init(target))
		return false;

	saveMappings = true;
	maxBondMappingsOnly = false;

	findAssocGraphCliques(0);

	return !foundMappings.empty();
}

bool Chem::MaxCommonAtomSubstructureSearch::findMaxBondMappings(const MolecularGraph& target)
{
	clearMappings();

	if (!init(target))
		return false;

	saveMappings = true;
	maxBondMappingsOnly = true;

	findAssocGraphCliques(0);

	return !foundMappings.empty();
}

std::size_t Chem::MaxCommonAtomSubstructureSearch::getNumMappings() const
{
	return foundMappings.size();
}

Chem::AtomBondMapping& Chem::MaxCommonAtomSubstructureSearch::getMapping(std::size_t idx)
{
	if (idx >= foundMappings.size())
		throw Base::IndexError("MaxCommonAtomSubstructureSearch: mapping index out of bounds");

	return *foundMappings[idx];
}

const Chem::AtomBondMapping& Chem::MaxCommonAtomSubstructureSearch::getMapping(std::size_t idx) const
{
	if (idx >= foundMappings.size())
		throw Base::IndexError("MaxCommonAtomSubstructureSearch: mapping index out of bounds");

	return *foundMappings[idx];
}

Chem::MaxCommonAtomSubstructureSearch::MappingIterator Chem::MaxCommonAtomSubstructureSearch::getMappingsBegin()
{
	return foundMappings.begin();
}

Chem::MaxCommonAtomSubstructureSearch::ConstMappingIterator Chem::MaxCommonAtomSubstructureSearch::getMappingsBegin() const
{
	return foundMappings.begin();
}

Chem::MaxCommonAtomSubstructureSearch::MappingIterator Chem::MaxCommonAtomSubstructureSearch::getMappingsEnd()
{
	return foundMappings.end();
}

Chem::MaxCommonAtomSubstructureSearch::ConstMappingIterator Chem::MaxCommonAtomSubstructureSearch::getMappingsEnd() const
{
	return foundMappings.end();
}

void Chem::MaxCommonAtomSubstructureSearch::uniqueMappingsOnly(bool unique)
{
	uniqueMatches = unique;
}

bool Chem::MaxCommonAtomSubstructureSearch::uniqueMappingsOnly() const
{
	return uniqueMatches;
}

void Chem::MaxCommonAtomSubstructureSearch::setMaxNumMappings(std::size_t max_num_mappings)
{
	maxNumMappings = max_num_mappings;
}

std::size_t Chem::MaxCommonAtomSubstructureSearch::getMaxNumMappings() const
{
	return maxNumMappings;
}

void Chem::MaxCommonAtomSubstructureSearch::setMinSubstructureSize(std::size_t min_size)
{
	minSubstructureSize = min_size;
}

std::size_t Chem::MaxCommonAtomSubstructureSearch::getMinSubstructureSize() const
{
	return minSubstructureSize;
}

void Chem::MaxCommonAtomSubstructureSearch::setQuery(const MolecularGraph& query)
{
	this->query = &query;
	queryChanged = true;
	initQueryData = true;
}

bool Chem::MaxCommonAtomSubstructureSearch::init(const MolecularGraph& tgt)
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
	
	if (buildAssocGraph()) {
		if (initQueryData) {
			mappingMask.initQueryAtomMask(numQueryAtoms);
			mappingMask.initQueryBondMask(numQueryBonds);

			initQueryData = false;
		}

		mappingMask.initTargetAtomMask(numTargetAtoms);
		mappingMask.initTargetBondMask(numTargetBonds);
			
		return true;
	}

	return false;
}

void Chem::MaxCommonAtomSubstructureSearch::initMatchExpressions()
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

bool Chem::MaxCommonAtomSubstructureSearch::buildAssocGraph()
{
	if (!(*molGraphMatchExpr)(*query, *target, Base::Variant()))
		return false;

	if (numQueryAtoms == 0)
		return true;

	freeAssocGraph();

	if (nodeMatrix.size() < numQueryAtoms)
		nodeMatrix.resize(numQueryAtoms);

	MolecularGraph::ConstAtomIterator query_atoms_end = query->getAtomsEnd();
	MolecularGraph::ConstAtomIterator target_atoms_beg = target->getAtomsBegin();
	MolecularGraph::ConstAtomIterator target_atoms_end = target->getAtomsEnd();

	AtomMatchExprTable::const_iterator ame_it = atomMatchExprTable.begin();
	AGraphNodeMatrix::iterator nl_it = nodeMatrix.begin();

	bool equiv_atoms_found = false;

	for (MolecularGraph::ConstAtomIterator pa_it = query->getAtomsBegin(); pa_it != query_atoms_end; ++pa_it, ++nl_it, ++ame_it) {
		const Atom& query_atom = *pa_it;
		const MatchExpression<Atom, MolecularGraph>& expr = **ame_it;
		AGraphNodeList& node_list = *nl_it;

		node_list.clear();

		for (MolecularGraph::ConstAtomIterator ta_it = target_atoms_beg; ta_it != target_atoms_end; ++ta_it) {
			const Atom& target_atom = *ta_it;

			if (expr(query_atom, *query, target_atom, *target, Base::Variant())) {
				AGNode* node = allocAGNode(&query_atom, &target_atom);

				node_list.push_back(node);
				equiv_atoms_found = true;
			}
		}
	}

	if (!equiv_atoms_found)
		return false;

	nl_it = nodeMatrix.begin();

	for (MolecularGraph::ConstAtomIterator pa_it1 = query->getAtomsBegin(); pa_it1 != query_atoms_end; ) {
		const Atom& query_atom1 = *pa_it1;

		AGraphNodeList& node_list1 = *nl_it;

		AGraphNodeList::iterator node_list1_beg = node_list1.begin();
		AGraphNodeList::iterator node_list1_end = node_list1.end();

		AGraphNodeMatrix::iterator nl_it2 = ++nl_it;

		for (MolecularGraph::ConstAtomIterator pa_it2 = ++pa_it1; pa_it2 != query_atoms_end; ++pa_it2, ++nl_it2) {
			const Atom& query_atom2 = *pa_it2;

			AGraphNodeList& node_list2 = *nl_it2;

			AGraphNodeList::iterator node_list2_beg = node_list2.begin();
			AGraphNodeList::iterator node_list2_end = node_list2.end();
		
			const Bond* query_bond = query_atom1.findBondToAtom(query_atom2);

			const MatchExpression<Bond, MolecularGraph>* expr = (query_bond && query->containsBond(*query_bond) ?
																 bondMatchExprTable[query->getBondIndex(*query_bond)].get() : 0);

			for (AGraphNodeList::iterator n_it1 = node_list1_beg; n_it1 != node_list1_end; ++n_it1) {
				AGNode* node1 = *n_it1;
				const Atom* assoc_atom1 = node1->getAssocAtom();

				for (AGraphNodeList::iterator n_it2 = node_list2_beg; n_it2 != node_list2_end; ++n_it2) {
					AGNode* node2 = *n_it2;
					const Atom* assoc_atom2 = node2->getAssocAtom();

					if (assoc_atom1 == assoc_atom2)
						continue;

					AGEdge* edge;					

					if (query_bond) {
						const Bond* target_bond = assoc_atom1->findBondToAtom(*assoc_atom2);
					
						if (target_bond && target->containsBond(*target_bond) && 
							(*expr)(*query_bond, *query, *target_bond, *target, Base::Variant()))
							edge = allocAGEdge(query_bond, target_bond);
						else
							edge = allocAGEdge(0, 0);

					} else 
						edge = allocAGEdge(0, 0);

					edge->setNode1(node1);
					edge->setNode2(node2);

					node1->addEdge(edge);
					node2->addEdge(edge);
				}
			}
		}
	}

	return true;
}

// Durand-Pasari Algorithm

bool Chem::MaxCommonAtomSubstructureSearch::findAssocGraphCliques(std::size_t level)
{
	if (currNumNullNodes > minNumNullNodes)
		return false;

	if (level == numQueryAtoms) {
		minNumNullNodes = currNumNullNodes;

		return mappingFound();
	}

	const AGraphNodeList& level_nodes = nodeMatrix[level];
	AGraphNodeList::const_iterator nodes_end = level_nodes.end();

	for (AGraphNodeList::const_iterator it = level_nodes.begin(); it != nodes_end; ++it) {
		AGNode* node = *it;

		std::size_t old_num_edges = cliqueEdges.size();

		if (!isLegal(node))
			continue;

		cliqueNodes.push_back(node);

		bool exit = findAssocGraphCliques(level + 1);

		cliqueNodes.pop_back();
		cliqueEdges.erase(cliqueEdges.begin() + old_num_edges, cliqueEdges.end());

		if (exit)
			return true;
	}

	currNumNullNodes++;

	bool exit = findAssocGraphCliques(level + 1);

	currNumNullNodes--;

	return exit;
}

bool Chem::MaxCommonAtomSubstructureSearch::isLegal(const AGNode* node)
{
	AGraphNodeList::const_iterator it = cliqueNodes.begin();
	AGraphNodeList::const_iterator clq_nodes_end = cliqueNodes.end();

	for (std::size_t num_bond_edges = 0; it != clq_nodes_end; ++it) {
		const AGNode* clq_node = *it;
 
		if (!node->isConnected(clq_node)) {
			if (num_bond_edges > 0)
				cliqueEdges.erase(cliqueEdges.end() - num_bond_edges, cliqueEdges.end());

			return false;
		}

		const AGEdge* edge = node->findEdge(clq_node);

		if (edge) {
			cliqueEdges.push_back(edge);
			num_bond_edges++;
		}
	}

	return true;
}

bool Chem::MaxCommonAtomSubstructureSearch::mappingFound()
{
	std::size_t num_mpd_atoms = cliqueNodes.size();

	if (num_mpd_atoms < minSubstructureSize)
		return false;

	if (!hasPostMappingMatchExprs()) {
		if (!saveMappings)
			return true;

		assert(num_mpd_atoms >= maxAtomSubstructureSize);

		std::size_t num_mpd_bonds = cliqueEdges.size();

		if (maxBondMappingsOnly && num_mpd_atoms == maxAtomSubstructureSize && num_mpd_bonds < maxBondSubstructureSize)
			return false;

		if (num_mpd_atoms > maxAtomSubstructureSize || (maxBondMappingsOnly && num_mpd_bonds > maxBondSubstructureSize)) {
			maxAtomSubstructureSize = num_mpd_atoms;
			maxBondSubstructureSize = num_mpd_bonds;

			freeAtomBondMappings();
		}

		if (uniqueMatches && !foundMappingUnique())
			return false;

		foundMappings.push_back(createAtomBondMapping());

		return (foundMappings.size() == maxNumMappings);
	}

	assert(num_mpd_atoms >= maxAtomSubstructureSize);

	std::size_t num_mpd_bonds = cliqueEdges.size();

	if (maxBondMappingsOnly && num_mpd_atoms == maxAtomSubstructureSize && num_mpd_bonds < maxBondSubstructureSize)
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

	if (num_mpd_atoms > maxAtomSubstructureSize || (maxBondMappingsOnly && num_mpd_bonds > maxBondSubstructureSize)) {
		maxAtomSubstructureSize = num_mpd_atoms;
		maxBondSubstructureSize = num_mpd_bonds;

		freeAtomBondMappings();
	}

	if (uniqueMatches && !foundMappingUnique()) {
		freeAtomBondMapping();
		return false;
	}

	foundMappings.push_back(mapping);

	return (foundMappings.size() == maxNumMappings);
}

bool Chem::MaxCommonAtomSubstructureSearch::hasPostMappingMatchExprs() const
{
	return (molGraphMatchExpr->requiresAtomBondMapping() || !postMappingMatchAtoms.empty() ||
			!postMappingMatchBonds.empty());
}

bool Chem::MaxCommonAtomSubstructureSearch::foundMappingMatches(const AtomBondMapping* mapping) const
{
	if (molGraphMatchExpr->requiresAtomBondMapping() && 
		!((*molGraphMatchExpr)(*query, *target, *mapping, Base::Variant())))
		return false;

	const AtomMapping& atom_mapping = mapping->getAtomMapping();

	AtomList::const_iterator post_map_atoms_end = postMappingMatchAtoms.end();

	for (AtomList::const_iterator it = postMappingMatchAtoms.begin(); it != post_map_atoms_end; ++it) {
		const Atom* query_atom = *it;
		const Atom* target_atom = atom_mapping[query_atom];

		if (!target_atom)
			continue;

		if (!(*atomMatchExprTable[query->getAtomIndex(*query_atom)])(*query_atom, *query, *target_atom, *target, 
																	 *mapping, Base::Variant()))
			return false;
	}

	const BondMapping& bond_mapping = mapping->getBondMapping();

	BondList::const_iterator post_map_bonds_end = postMappingMatchBonds.end();

	for (BondList::const_iterator it = postMappingMatchBonds.begin(); it != post_map_bonds_end; ++it) {
		const Bond* query_bond = *it;
		const Bond* target_bond = bond_mapping[query_bond];

		if (!target_bond)
			continue;

		if (!(*bondMatchExprTable[query->getBondIndex(*query_bond)])(*query_bond, *query, *target_bond, *target, 
																	 *mapping, Base::Variant()))
			return false;
	}

	return true;
}

bool Chem::MaxCommonAtomSubstructureSearch::foundMappingUnique()
{
	mappingMask.reset();

	AGraphNodeList::const_iterator clq_nodes_end = cliqueNodes.end();

	for (AGraphNodeList::const_iterator it = cliqueNodes.begin(); it != clq_nodes_end; ++it) {
		const AGNode* node = *it;

		mappingMask.setQueryAtomBit(query->getAtomIndex(*node->getQueryAtom()));
		mappingMask.setTargetAtomBit(target->getAtomIndex(*node->getAssocAtom()));
	}

	AGraphEdgeList::const_iterator clq_edges_end = cliqueEdges.end();

	for (AGraphEdgeList::const_iterator it = cliqueEdges.begin(); it != clq_edges_end; ++it) {
		const AGEdge* edge = *it;

		mappingMask.setQueryBondBit(query->getBondIndex(*edge->getQueryBond()));
		mappingMask.setTargetBondBit(target->getBondIndex(*edge->getAssocBond()));
	}

	return uniqueMappings.insert(mappingMask).second;
}

void Chem::MaxCommonAtomSubstructureSearch::clearMappings()
{
	freeAtomBondMappings();

	maxAtomSubstructureSize = 0;
	maxBondSubstructureSize = 0;

	minNumNullNodes = numQueryAtoms;
}

Chem::AtomBondMapping* Chem::MaxCommonAtomSubstructureSearch::createAtomBondMapping()
{
	AtomBondMapping* mapping = mappingCache.getRaw();
	AtomMapping& atom_mapping = mapping->getAtomMapping();
	BondMapping& bond_mapping = mapping->getBondMapping();

	AGraphNodeList::const_iterator clq_nodes_end = cliqueNodes.end();

	for (AGraphNodeList::const_iterator it = cliqueNodes.begin(); it != clq_nodes_end; ++it) {
		const AGNode* node = *it;

		atom_mapping.insertEntry(node->getQueryAtom(), node->getAssocAtom());
	}

	AGraphEdgeList::const_iterator clq_edges_end = cliqueEdges.end();

	for (AGraphEdgeList::const_iterator it = cliqueEdges.begin(); it != clq_edges_end; ++it) {
		const AGEdge* edge = *it;

		bond_mapping.insertEntry(edge->getQueryBond(), edge->getAssocBond());
	}

	return mapping;
}

void Chem::MaxCommonAtomSubstructureSearch::freeAtomBondMapping()
{
	mappingCache.put();
}

Chem::MaxCommonAtomSubstructureSearch::AGNode* Chem::MaxCommonAtomSubstructureSearch::allocAGNode(const Atom* query_atom, const Atom* assoc_atom)
{
	AGNode* node = nodeCache.getRaw();

	node->setQueryAtom(query_atom);
	node->setAssocAtom(assoc_atom);
	node->clear();
	node->setIndex(currNodeIdx++);

	return node;
}

Chem::MaxCommonAtomSubstructureSearch::AGEdge* Chem::MaxCommonAtomSubstructureSearch::allocAGEdge(const Bond* query_bond, const Bond* assoc_bond)
{
	AGEdge* edge = edgeCache.getRaw();

	edge->setQueryBond(query_bond);
	edge->setAssocBond(assoc_bond);

	return edge;
}

void Chem::MaxCommonAtomSubstructureSearch::freeAssocGraph() 
{
	nodeCache.putAll();
	edgeCache.putAll();

	currNodeIdx = 0;
}

void Chem::MaxCommonAtomSubstructureSearch::freeAtomBondMappings() 
{
	mappingCache.putAll();
	foundMappings.clear();

	if (uniqueMatches)
		uniqueMappings.clear();
}


void Chem::MaxCommonAtomSubstructureSearch::AGNode::setQueryAtom(const Atom* atom)
{
	queryAtom = atom;
}

const Chem::Atom* Chem::MaxCommonAtomSubstructureSearch::AGNode::getQueryAtom() const
{
	return queryAtom;
}
			
void Chem::MaxCommonAtomSubstructureSearch::AGNode::setAssocAtom(const Atom* atom)
{
	assocAtom = atom;
}

const Chem::Atom* Chem::MaxCommonAtomSubstructureSearch::AGNode::getAssocAtom() const
{
	return assocAtom;
}
				
void Chem::MaxCommonAtomSubstructureSearch::AGNode::addEdge(const AGEdge* edge)
{
	if (edge->getQueryBond())
		bondEdges.push_back(edge);

	std::size_t conn_node_idx = edge->getOther(this)->index;

	if (conn_node_idx >= connNodes.size())
		connNodes.resize(conn_node_idx + 1);

	connNodes.set(conn_node_idx);
}

bool Chem::MaxCommonAtomSubstructureSearch::AGNode::isConnected(const AGNode* node) const
{
	if (this == node)
		return true;

	std::size_t node_idx = node->index;

	if (node_idx >= connNodes.size())
		return false;

	return connNodes.test(node_idx);
}

const Chem::MaxCommonAtomSubstructureSearch::AGEdge* Chem::MaxCommonAtomSubstructureSearch::AGNode::findEdge(const AGNode* node) const
{
	AGraphEdgeList::const_iterator it = std::find_if(bondEdges.begin(), bondEdges.end(),
													 boost::bind(std::equal_to<const AGNode*>(), 
																 node, boost::bind(&AGEdge::getOther, _1, this)));  

	return (it == bondEdges.end() ? 0 : *it);
}

void Chem::MaxCommonAtomSubstructureSearch::AGNode::setIndex(std::size_t idx)
{
	index = idx;
}
	
void Chem::MaxCommonAtomSubstructureSearch::AGNode::clear()
{
	bondEdges.clear();
	connNodes.reset();
}


void Chem::MaxCommonAtomSubstructureSearch::AGEdge::setQueryBond(const Bond* bond)
{
	queryBond = bond;
}

const Chem::Bond* Chem::MaxCommonAtomSubstructureSearch::AGEdge::getQueryBond() const
{
	return queryBond;
}

void Chem::MaxCommonAtomSubstructureSearch::AGEdge::setAssocBond(const Bond* bond)
{
	assocBond = bond;
}

const Chem::Bond* Chem::MaxCommonAtomSubstructureSearch::AGEdge::getAssocBond() const
{
	return assocBond;
}
				
void Chem::MaxCommonAtomSubstructureSearch::AGEdge::setNode1(const AGNode* node)
{
	node1 = node;
}

void Chem::MaxCommonAtomSubstructureSearch::AGEdge::setNode2(const AGNode* node)
{
	node2 = node;
}
				
const Chem::MaxCommonAtomSubstructureSearch::AGNode* Chem::MaxCommonAtomSubstructureSearch::AGEdge::getNode1() const
{
	return node1;
}

const Chem::MaxCommonAtomSubstructureSearch::AGNode* Chem::MaxCommonAtomSubstructureSearch::AGEdge::getNode2() const
{
	return node1;
}

const Chem::MaxCommonAtomSubstructureSearch::AGNode* Chem::MaxCommonAtomSubstructureSearch::AGEdge::getOther(const AGNode* node) const
{
	return (node1 == node ? node2 : node1); 
}


void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::initQueryAtomMask(std::size_t num_atoms)
{
	if (queryAtomMask.size() < num_atoms)
		queryAtomMask.resize(num_atoms);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::initTargetAtomMask(std::size_t num_atoms)
{
	if (targetAtomMask.size() < num_atoms)
		targetAtomMask.resize(num_atoms);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::initQueryBondMask(std::size_t num_bonds)
{
	if (queryBondMask.size() < num_bonds)
		queryBondMask.resize(num_bonds);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::initTargetBondMask(std::size_t num_bonds)
{
	if (targetBondMask.size() < num_bonds)
		targetBondMask.resize(num_bonds);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::setQueryAtomBit(std::size_t atom_idx)
{
	queryAtomMask.set(atom_idx);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::setTargetAtomBit(std::size_t atom_idx)
{
	targetAtomMask.set(atom_idx);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::setQueryBondBit(std::size_t bond_idx)
{
	queryBondMask.set(bond_idx);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::setTargetBondBit(std::size_t bond_idx)
{
	targetBondMask.set(bond_idx);
}

void Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::reset()
{
	queryAtomMask.reset();
	targetAtomMask.reset();
	queryBondMask.reset();
	targetBondMask.reset();
}

bool Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::operator<(const ABMappingMask& mask) const
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

bool Chem::MaxCommonAtomSubstructureSearch::ABMappingMask::operator>(const ABMappingMask& mask) const
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
