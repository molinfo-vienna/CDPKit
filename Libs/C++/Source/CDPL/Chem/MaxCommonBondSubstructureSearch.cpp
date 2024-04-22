/* 
 * MaxCommonBondSubstructureSearch.cpp 
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

#include <cassert>
#include <functional>

#include "CDPL/Chem/MaxCommonBondSubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{
    
    constexpr std::size_t MAX_NODE_CACHE_SIZE    = 10000;
    constexpr std::size_t MAX_EDGE_CACHE_SIZE    = 10000;
    constexpr std::size_t MAX_MAPPING_CACHE_SIZE = 1000;
}


using namespace CDPL;


Chem::MaxCommonBondSubstructureSearch::MaxCommonBondSubstructureSearch(): 
    query(0), nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE), 
    mappingCache(MAX_MAPPING_CACHE_SIZE), queryChanged(true), initQueryData(true),
    uniqueMatches(false), currNumNullNodes(0), maxNumMappings(0), minSubstructureSize(0) 
{
    mappingCache.setCleanupFunction(&AtomBondMapping::clear);
}

Chem::MaxCommonBondSubstructureSearch::MaxCommonBondSubstructureSearch(const MolecularGraph& query): 
    nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE), mappingCache(MAX_MAPPING_CACHE_SIZE), 
    uniqueMatches(false), currNumNullNodes(0), maxNumMappings(0), minSubstructureSize(0) 
{
    mappingCache.setCleanupFunction(&AtomBondMapping::clear);

    setQuery(query);
}

Chem::MaxCommonBondSubstructureSearch::~MaxCommonBondSubstructureSearch() {}

bool Chem::MaxCommonBondSubstructureSearch::mappingExists(const MolecularGraph& target)
{
    if (!init(target))
        return false;

    saveMappings = false;

    clearMappings();
    
    return findAssocGraphCliques(0);
}

bool Chem::MaxCommonBondSubstructureSearch::findMappings(const MolecularGraph& target)
{
    if (!init(target))
        return false;
    
    saveMappings = true;

    clearMappings();
    findAssocGraphCliques(0);

    return !foundMappings.empty();
}

std::size_t Chem::MaxCommonBondSubstructureSearch::getNumMappings() const
{
    return foundMappings.size();
}

Chem::AtomBondMapping& Chem::MaxCommonBondSubstructureSearch::getMapping(std::size_t idx)
{
    if (idx >= foundMappings.size())
        throw Base::IndexError("MaxCommonBondSubstructureSearch: mapping index out of bounds");

    return *foundMappings[idx];
}

const Chem::AtomBondMapping& Chem::MaxCommonBondSubstructureSearch::getMapping(std::size_t idx) const
{
    if (idx >= foundMappings.size())
        throw Base::IndexError("MaxCommonBondSubstructureSearch: mapping index out of bounds");

    return *foundMappings[idx];
}

Chem::MaxCommonBondSubstructureSearch::MappingIterator Chem::MaxCommonBondSubstructureSearch::getMappingsBegin()
{
    return foundMappings.begin();
}

Chem::MaxCommonBondSubstructureSearch::ConstMappingIterator Chem::MaxCommonBondSubstructureSearch::getMappingsBegin() const
{
    return foundMappings.begin();
}

Chem::MaxCommonBondSubstructureSearch::MappingIterator Chem::MaxCommonBondSubstructureSearch::getMappingsEnd()
{
    return foundMappings.end();
}

Chem::MaxCommonBondSubstructureSearch::ConstMappingIterator Chem::MaxCommonBondSubstructureSearch::getMappingsEnd() const
{
    return foundMappings.end();
}

Chem::MaxCommonBondSubstructureSearch::MappingIterator Chem::MaxCommonBondSubstructureSearch::begin()
{
    return foundMappings.begin();
}

Chem::MaxCommonBondSubstructureSearch::ConstMappingIterator Chem::MaxCommonBondSubstructureSearch::begin() const
{
    return foundMappings.begin();
}

Chem::MaxCommonBondSubstructureSearch::MappingIterator Chem::MaxCommonBondSubstructureSearch::end()
{
    return foundMappings.end();
}

Chem::MaxCommonBondSubstructureSearch::ConstMappingIterator Chem::MaxCommonBondSubstructureSearch::end() const
{
    return foundMappings.end();
}

void Chem::MaxCommonBondSubstructureSearch::uniqueMappingsOnly(bool unique)
{
    uniqueMatches = unique;
}

bool Chem::MaxCommonBondSubstructureSearch::uniqueMappingsOnly() const
{
    return uniqueMatches;
}

void Chem::MaxCommonBondSubstructureSearch::setMaxNumMappings(std::size_t max_num_mappings)
{
    maxNumMappings = max_num_mappings;
}

std::size_t Chem::MaxCommonBondSubstructureSearch::getMaxNumMappings() const
{
    return maxNumMappings;
}

void Chem::MaxCommonBondSubstructureSearch::setMinSubstructureSize(std::size_t min_size)
{
    minSubstructureSize = min_size;
}

std::size_t Chem::MaxCommonBondSubstructureSearch::getMinSubstructureSize() const
{
    return minSubstructureSize;
}

void Chem::MaxCommonBondSubstructureSearch::setQuery(const MolecularGraph& query)
{
    this->query = &query;
    queryChanged = true;
    initQueryData = true;
}

bool Chem::MaxCommonBondSubstructureSearch::init(const MolecularGraph& tgt)
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

void Chem::MaxCommonBondSubstructureSearch::initMatchExpressions()
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

bool Chem::MaxCommonBondSubstructureSearch::findEquivAtoms()
{
    if (numQueryAtoms == 0)
        return false;

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

            if (expr(query_atom, *query, target_atom, *target, Base::Any())) {
                equiv_mask.set(target->getAtomIndex(target_atom));
                equiv_atoms_found = true;
            }
        }
    }

    return equiv_atoms_found;
}

bool Chem::MaxCommonBondSubstructureSearch::atomsCompatible(const Bond& query_bond, const Bond& target_bond) const
{
    std::size_t query_beg_atom_idx = query->getAtomIndex(query_bond.getBegin());
    std::size_t query_end_atom_idx = query->getAtomIndex(query_bond.getEnd());
    std::size_t target_beg_atom_idx = target->getAtomIndex(target_bond.getBegin());
    std::size_t target_end_atom_idx = target->getAtomIndex(target_bond.getEnd());

    if ((atomEquivMatrix[query_beg_atom_idx].test(target_beg_atom_idx) && atomEquivMatrix[query_end_atom_idx].test(target_end_atom_idx))
        || (atomEquivMatrix[query_beg_atom_idx].test(target_end_atom_idx) && atomEquivMatrix[query_end_atom_idx].test(target_beg_atom_idx)))
        return true;

    return false;
}

const Chem::Atom* Chem::MaxCommonBondSubstructureSearch::getCommonAtom(const Bond& bond1, const Bond& bond2) const
{
    const Atom* beg_atom1 = &bond1.getBegin();
    const Atom* beg_atom2 = &bond2.getBegin();

    if (beg_atom1 == beg_atom2)
        return beg_atom1;

    const Atom* end_atom2 = &bond2.getEnd();

    if (beg_atom1 == end_atom2)
        return beg_atom1;

    const Atom* end_atom1 = &bond1.getEnd();

    if (end_atom1 == beg_atom2 || end_atom1 == end_atom2)
        return end_atom1;

    return 0;
}

bool Chem::MaxCommonBondSubstructureSearch::buildAssocGraph()
{
    if (!(*molGraphMatchExpr)(*query, *target, Base::Any()))
        return false;

    if (!findEquivAtoms())
        return false;

    freeAssocGraph();

    if (nodeMatrix.size() < numQueryBonds)
        nodeMatrix.resize(numQueryBonds);

    MolecularGraph::ConstBondIterator query_bonds_end = query->getBondsEnd();
    MolecularGraph::ConstBondIterator target_bonds_beg = target->getBondsBegin();
    MolecularGraph::ConstBondIterator target_bonds_end = target->getBondsEnd();

    BondMatchExprTable::const_iterator bme_it = bondMatchExprTable.begin();
    AGraphNodeMatrix::iterator nl_it = nodeMatrix.begin();

    bool equiv_bonds_found = false;

    for (MolecularGraph::ConstBondIterator pb_it = query->getBondsBegin(); pb_it != query_bonds_end; ++pb_it, ++nl_it, ++bme_it) {
        const MatchExpression<Bond, MolecularGraph>::SharedPointer& expr = *bme_it;
        AGraphNodeList& node_list = *nl_it;

        node_list.clear();

        if (!expr)
            continue;

        const Bond& query_bond = *pb_it;

        for (MolecularGraph::ConstBondIterator tb_it = target_bonds_beg; tb_it != target_bonds_end; ++tb_it) {
            const Bond& target_bond = *tb_it;

            if (!target->containsAtom(target_bond.getBegin()) || !target->containsAtom(target_bond.getEnd()))
                continue;

            if ((*expr)(query_bond, *query, target_bond, *target, Base::Any()) && 
                atomsCompatible(query_bond, target_bond)) {
                AGNode* node = allocAGNode(&query_bond, &target_bond);

                node_list.push_back(node);
                equiv_bonds_found = true;
            }
        }
    }

    if (!equiv_bonds_found)
        return false;

    nl_it = nodeMatrix.begin();

    for (MolecularGraph::ConstBondIterator pb_it1 = query->getBondsBegin(); pb_it1 != query_bonds_end; ) {
        const Bond& query_bond1 = *pb_it1;
        AGraphNodeList& node_list1 = *nl_it;

        AGraphNodeList::iterator node_list1_beg = node_list1.begin();
        AGraphNodeList::iterator node_list1_end = node_list1.end();

        AGraphNodeMatrix::iterator nl_it2 = ++nl_it;

        for (MolecularGraph::ConstBondIterator pb_it2 = ++pb_it1; pb_it2 != query_bonds_end; ++pb_it2, ++nl_it2) {
            const Bond& query_bond2 = *pb_it2;
            AGraphNodeList& node_list2 = *nl_it2;

            AGraphNodeList::iterator node_list2_beg = node_list2.begin();
            AGraphNodeList::iterator node_list2_end = node_list2.end();
        
            const Atom* cmn_query_atom = getCommonAtom(query_bond1, query_bond2);
            std::size_t cmn_query_atom_idx = (cmn_query_atom ? query->getAtomIndex(*cmn_query_atom) : 0);

            for (AGraphNodeList::iterator n_it1 = node_list1_beg; n_it1 != node_list1_end; ++n_it1) {
                AGNode* node1 = *n_it1;
                const Bond* assoc_bond1 = node1->getAssocBond();

                for (AGraphNodeList::iterator n_it2 = node_list2_beg; n_it2 != node_list2_end; ++n_it2) {
                    AGNode* node2 = *n_it2;
                    const Bond* assoc_bond2 = node2->getAssocBond();

                    if (assoc_bond1 == assoc_bond2)
                        continue;

                    assert(node1->isConnected(node2) == false);

                    const Atom* cmn_target_atom = getCommonAtom(*assoc_bond1, *assoc_bond2);

                    if (cmn_query_atom) {
                        if (!cmn_target_atom || !atomEquivMatrix[cmn_query_atom_idx].test(target->getAtomIndex(*cmn_target_atom))) 
                            continue;
                        
                    } else if (cmn_target_atom) 
                        continue;

                    AGEdge* edge = allocAGEdge(cmn_query_atom, cmn_target_atom);

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

bool Chem::MaxCommonBondSubstructureSearch::findAssocGraphCliques(std::size_t level)
{
    if (currNumNullNodes > minNumNullNodes)
        return false;

    if (level == numQueryBonds) {
        minNumNullNodes = currNumNullNodes;

        return mappingFound();
    }

    const AGraphNodeList& level_nodes = nodeMatrix[level];
    AGraphNodeList::const_iterator nodes_end = level_nodes.end();

    std::size_t old_num_edges = cliqueEdges.size();

    for (AGraphNodeList::const_iterator it = level_nodes.begin(); it != nodes_end; ++it) {
        AGNode* node = *it;

        if (!isLegal(node))
            continue;

        cliqueNodes.push_back(node);

        bool exit = findAssocGraphCliques(level + 1);

        cliqueNodes.pop_back();
        
        undoAtomMapping(cliqueEdges.size() - old_num_edges);

        if (exit)
            return true;
    }

    currNumNullNodes++;

    bool exit = findAssocGraphCliques(level + 1);

    currNumNullNodes--;

    return exit;
}

bool Chem::MaxCommonBondSubstructureSearch::isLegal(const AGNode* node)
{
    AGraphNodeList::const_iterator it = cliqueNodes.begin();
    AGraphNodeList::const_iterator clq_nodes_end = cliqueNodes.end();

    std::size_t old_num_edges = cliqueEdges.size();

    for (std::size_t num_new_edges = 0; it != clq_nodes_end; ++it) {
        const AGNode* clq_node = *it;
 
        if (!node->isConnected(clq_node)) {
            undoAtomMapping(num_new_edges);
            return false;
        }

        const AGEdge* edge = node->findEdge(clq_node);

        if (!edge)
            continue;
 
        if (num_new_edges > 0) {
            const Atom* query_atom = edge->getQueryAtom();
            const Atom* target_atom = edge->getAssocAtom();

            std::size_t new_num_edges = cliqueEdges.size();

            for (std::size_t i = old_num_edges; i < new_num_edges; i++) { // Check for K3 <-> K1,3 interchange
                const AGEdge* edge2 = cliqueEdges[i];
                const Atom* query_atom2 = edge2->getQueryAtom();
                const Atom* target_atom2 = edge2->getAssocAtom();

                if ((query_atom == query_atom2 && target_atom != target_atom2) || (query_atom != query_atom2 && target_atom == target_atom2)) {
                    undoAtomMapping(num_new_edges);
                    return false;
                }
            }
        }

        cliqueEdges.push_back(edge);
        num_new_edges++;
    }

    return true;
}

void Chem::MaxCommonBondSubstructureSearch::undoAtomMapping(std::size_t count)
{
    cliqueEdges.erase(cliqueEdges.end() - count, cliqueEdges.end());
}

bool Chem::MaxCommonBondSubstructureSearch::mappingFound()
{
    std::size_t num_mpd_bonds = cliqueNodes.size();

    if (num_mpd_bonds < minSubstructureSize)
        return false;

    if (!hasPostMappingMatchExprs()) {
        if (!saveMappings)
            return true;

        assert(num_mpd_bonds >= maxBondSubstructureSize); 

        if (num_mpd_bonds > maxBondSubstructureSize) {
            maxBondSubstructureSize = num_mpd_bonds;

            freeAtomBondMappings();
        }

        if (uniqueMatches && !foundMappingUnique(true))
            return false;

        foundMappings.push_back(createAtomBondMapping(!uniqueMatches));

        return (foundMappings.size() == maxNumMappings);
    }

    assert(num_mpd_bonds >= maxBondSubstructureSize); 

    AtomBondMapping* mapping = createAtomBondMapping(true);

    if (!foundMappingMatches(mapping)) {
        freeAtomBondMapping();
        return false;
    }

    if (!saveMappings) {
        freeAtomBondMapping();
        return true;
    }

    if (num_mpd_bonds > maxBondSubstructureSize) {
        maxBondSubstructureSize = num_mpd_bonds;

        freeAtomBondMappings();
    }

    if (uniqueMatches && !foundMappingUnique(false)) {
        freeAtomBondMapping();
        return false;
    }

    foundMappings.push_back(mapping);

    return (foundMappings.size() == maxNumMappings);
}

bool Chem::MaxCommonBondSubstructureSearch::hasPostMappingMatchExprs() const
{
    return (molGraphMatchExpr->requiresAtomBondMapping() || !postMappingMatchAtoms.empty() ||
            !postMappingMatchBonds.empty());
}

bool Chem::MaxCommonBondSubstructureSearch::foundMappingMatches(const AtomBondMapping* mapping) const
{
    if (molGraphMatchExpr->requiresAtomBondMapping() && 
        !((*molGraphMatchExpr)(*query, *target, *mapping, Base::Any())))
        return false;

    const AtomMapping& atom_mapping = mapping->getAtomMapping();

    AtomList::const_iterator post_map_atoms_end = postMappingMatchAtoms.end();

    for (AtomList::const_iterator it = postMappingMatchAtoms.begin(); it != post_map_atoms_end; ++it) {
        const Atom* query_atom = *it;
        const Atom* target_atom = atom_mapping[query_atom];

        if (!target_atom)
            continue;

        if (!(*atomMatchExprTable[query->getAtomIndex(*query_atom)])(*query_atom, *query, *target_atom, *target, 
                                                                     *mapping, Base::Any()))
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
                                                                     *mapping, Base::Any()))
            return false;
    }

    return true;
}

bool Chem::MaxCommonBondSubstructureSearch::foundMappingUnique(bool init_query_atom_mask)
{
    if (init_query_atom_mask)
        mappingMask.resetQueryAtomBits();

    mappingMask.resetTargetAtomBits();

    AGraphEdgeList::const_iterator clq_edges_end = cliqueEdges.end();

    for (AGraphEdgeList::const_iterator it = cliqueEdges.begin(); it != clq_edges_end; ++it) {
        const AGEdge* edge = *it;

        if (init_query_atom_mask)
            mappingMask.setQueryAtomBit(query->getAtomIndex(*edge->getQueryAtom()));

        mappingMask.setTargetAtomBit(target->getAtomIndex(*edge->getAssocAtom()));
    }

    mappingMask.resetBondBits();

    AGraphNodeList::const_iterator clq_nodes_end = cliqueNodes.end();

    for (AGraphNodeList::const_iterator it = cliqueNodes.begin(); it != clq_nodes_end; ++it) {
        const AGNode* node = *it;

        mappingMask.setQueryBondBit(query->getBondIndex(*node->getQueryBond()));
        mappingMask.setTargetBondBit(target->getBondIndex(*node->getAssocBond()));
    }

    return uniqueMappings.insert(mappingMask).second;
}

void Chem::MaxCommonBondSubstructureSearch::clearMappings()
{
    freeAtomBondMappings();

    maxBondSubstructureSize = 0;
    minNumNullNodes = numQueryBonds;
}

Chem::AtomBondMapping* Chem::MaxCommonBondSubstructureSearch::createAtomBondMapping(bool init_query_atom_mask)
{
    AtomBondMapping* mapping = mappingCache.get();
    AtomMapping& atom_mapping = mapping->getAtomMapping();
    BondMapping& bond_mapping = mapping->getBondMapping();

    if (init_query_atom_mask)
        mappingMask.resetQueryAtomBits();

    AGraphEdgeList::const_iterator clq_edges_end = cliqueEdges.end();

    for (AGraphEdgeList::const_iterator it = cliqueEdges.begin(); it != clq_edges_end; ++it) {
        const AGEdge* edge = *it;
        const Atom* query_atom = edge->getQueryAtom();

        if (init_query_atom_mask)
            mappingMask.setQueryAtomBit(query->getAtomIndex(*query_atom));

        if (atom_mapping.getEntry(query_atom) == atom_mapping.getEntriesEnd())
            atom_mapping.insertEntry(query_atom, edge->getAssocAtom());
    }

    AGraphNodeList::const_iterator clq_nodes_end = cliqueNodes.end();

    for (AGraphNodeList::const_iterator it = cliqueNodes.begin(); it != clq_nodes_end; ++it) {
        const AGNode* node = *it;
        const Bond* query_bond = node->getQueryBond();
        const Bond* target_bond = node->getAssocBond();

        bond_mapping.insertEntry(query_bond, target_bond);

        if (mappingMask.testQueryAtomBit(query->getAtomIndex(query_bond->getBegin()))) {
            if (mappingMask.testQueryAtomBit(query->getAtomIndex(query_bond->getEnd())))
                continue;

            const Atom* mpd_target_atom = atom_mapping[&query_bond->getBegin()];

            assert(mpd_target_atom != 0);

            atom_mapping.insertEntry(&query_bond->getEnd(), &target_bond->getNeighbor(*mpd_target_atom));

        } else if (mappingMask.testQueryAtomBit(query->getAtomIndex(query_bond->getEnd()))) {
            const Atom* mpd_target_atom = atom_mapping[&query_bond->getEnd()];

            assert(mpd_target_atom != 0);

            atom_mapping.insertEntry(&query_bond->getBegin(), &target_bond->getNeighbor(*mpd_target_atom));

        } else {
            if (atomEquivMatrix[query->getAtomIndex(query_bond->getBegin())].test(target->getAtomIndex(target_bond->getBegin()))) {
                atom_mapping.insertEntry(&query_bond->getBegin(), &target_bond->getBegin());
                atom_mapping.insertEntry(&query_bond->getEnd(), &target_bond->getEnd());

            } else {
                atom_mapping.insertEntry(&query_bond->getEnd(), &target_bond->getBegin());
                atom_mapping.insertEntry(&query_bond->getBegin(), &target_bond->getEnd());
            }
        }
    }

    return mapping;
}

void Chem::MaxCommonBondSubstructureSearch::freeAtomBondMapping()
{
    mappingCache.put();
}

Chem::MaxCommonBondSubstructureSearch::AGNode* Chem::MaxCommonBondSubstructureSearch::allocAGNode(const Bond* query_bond, 
                                                                                                  const Bond* assoc_bond)
{
    AGNode* node = nodeCache.get();

    node->setQueryBond(query_bond);
    node->setAssocBond(assoc_bond);
    node->clear();
    node->setIndex(currNodeIdx++);

    return node;
}

Chem::MaxCommonBondSubstructureSearch::AGEdge* Chem::MaxCommonBondSubstructureSearch::allocAGEdge(const Atom* query_atom, 
                                                                                                  const Atom* assoc_atom)
{
    AGEdge* edge = edgeCache.get();

    edge->setQueryAtom(query_atom);
    edge->setAssocAtom(assoc_atom);

    return edge;
}

void Chem::MaxCommonBondSubstructureSearch::freeAssocGraph() 
{
    nodeCache.putAll();
    edgeCache.putAll();

    currNodeIdx = 0;
}

void Chem::MaxCommonBondSubstructureSearch::freeAtomBondMappings() 
{
    mappingCache.putAll();
    foundMappings.clear();

    if (uniqueMatches)
        uniqueMappings.clear();
}

// Implementation of AGNode members

void Chem::MaxCommonBondSubstructureSearch::AGNode::setQueryBond(const Bond* bond)
{
    queryBond = bond;
}

const Chem::Bond* Chem::MaxCommonBondSubstructureSearch::AGNode::getQueryBond() const
{
    return queryBond;
}
            
void Chem::MaxCommonBondSubstructureSearch::AGNode::setAssocBond(const Bond* bond)
{
    assocBond = bond;
}

const Chem::Bond* Chem::MaxCommonBondSubstructureSearch::AGNode::getAssocBond() const
{
    return assocBond;
}
                
void Chem::MaxCommonBondSubstructureSearch::AGNode::addEdge(const AGEdge* edge)
{
    if (edge->getQueryAtom())
        atomEdges.push_back(edge);

    std::size_t conn_node_idx = edge->getOther(this)->index;

    if (conn_node_idx >= connNodes.size())
        connNodes.resize(conn_node_idx + 1);

    connNodes.set(conn_node_idx);
}

bool Chem::MaxCommonBondSubstructureSearch::AGNode::isConnected(const AGNode* node) const
{
    if (this == node)
        return true;

    std::size_t node_idx = node->index;

    if (node_idx >= connNodes.size())
        return false;

    return connNodes.test(node_idx);
}

const Chem::MaxCommonBondSubstructureSearch::AGEdge* Chem::MaxCommonBondSubstructureSearch::AGNode::findEdge(const AGNode* node) const
{
    AGraphEdgeList::const_iterator it = std::find_if(atomEdges.begin(), atomEdges.end(),
                                                     std::bind(std::equal_to<const AGNode*>(), 
                                                               node, std::bind(&AGEdge::getOther, std::placeholders::_1, this)));  

    return (it == atomEdges.end() ? 0 : *it);
}

void Chem::MaxCommonBondSubstructureSearch::AGNode::setIndex(std::size_t idx)
{
    index = idx;
}
            
void Chem::MaxCommonBondSubstructureSearch::AGNode::clear()
{
    atomEdges.clear();
    connNodes.reset();
}

// Implementation of AGEdge members

void Chem::MaxCommonBondSubstructureSearch::AGEdge::setQueryAtom(const Atom* atom)
{
    queryAtom = atom;
}

const Chem::Atom* Chem::MaxCommonBondSubstructureSearch::AGEdge::getQueryAtom() const
{
    return queryAtom;
}

void Chem::MaxCommonBondSubstructureSearch::AGEdge::setAssocAtom(const Atom* atom)
{
    assocAtom = atom;
}

const Chem::Atom* Chem::MaxCommonBondSubstructureSearch::AGEdge::getAssocAtom() const
{
    return assocAtom;
}
                
void Chem::MaxCommonBondSubstructureSearch::AGEdge::setNode1(const AGNode* node)
{
    node1 = node;
}

void Chem::MaxCommonBondSubstructureSearch::AGEdge::setNode2(const AGNode* node)
{
    node2 = node;
}
                
const Chem::MaxCommonBondSubstructureSearch::AGNode* Chem::MaxCommonBondSubstructureSearch::AGEdge::getNode1() const
{
    return node1;
}

const Chem::MaxCommonBondSubstructureSearch::AGNode* Chem::MaxCommonBondSubstructureSearch::AGEdge::getNode2() const
{
    return node1;
}

const Chem::MaxCommonBondSubstructureSearch::AGNode* Chem::MaxCommonBondSubstructureSearch::AGEdge::getOther(const AGNode* node) const
{
    return (node1 == node ? node2 : node1); 
}

// Implementation of ABMappingMask members

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::initQueryAtomMask(std::size_t num_atoms)
{
    if (queryAtomMask.size() < num_atoms)
        queryAtomMask.resize(num_atoms);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::initTargetAtomMask(std::size_t num_atoms)
{
    if (targetAtomMask.size() < num_atoms)
        targetAtomMask.resize(num_atoms);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::initQueryBondMask(std::size_t num_bonds)
{
    if (queryBondMask.size() < num_bonds)
        queryBondMask.resize(num_bonds);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::initTargetBondMask(std::size_t num_bonds)
{
    if (targetBondMask.size() < num_bonds)
        targetBondMask.resize(num_bonds);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::setQueryAtomBit(std::size_t atom_idx)
{
    queryAtomMask.set(atom_idx);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::setTargetAtomBit(std::size_t atom_idx)
{
    targetAtomMask.set(atom_idx);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::resetQueryAtomBit(std::size_t atom_idx)
{
    queryAtomMask.reset(atom_idx);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::resetTargetAtomBit(std::size_t atom_idx)
{
    targetAtomMask.reset(atom_idx);
}

bool Chem::MaxCommonBondSubstructureSearch::ABMappingMask::testQueryAtomBit(std::size_t atom_idx) const
{
    return queryAtomMask.test(atom_idx);
}

bool Chem::MaxCommonBondSubstructureSearch::ABMappingMask::testTargetAtomBit(std::size_t atom_idx) const
{
    return targetAtomMask.test(atom_idx);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::setQueryBondBit(std::size_t bond_idx)
{
    queryBondMask.set(bond_idx);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::setTargetBondBit(std::size_t bond_idx)
{
    targetBondMask.set(bond_idx);
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::resetQueryAtomBits()
{
    queryAtomMask.reset();
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::resetTargetAtomBits()
{
    targetAtomMask.reset();
}

void Chem::MaxCommonBondSubstructureSearch::ABMappingMask::resetBondBits()
{
    queryBondMask.reset();
    targetBondMask.reset();
}

bool Chem::MaxCommonBondSubstructureSearch::ABMappingMask::operator<(const ABMappingMask& mask) const
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

bool Chem::MaxCommonBondSubstructureSearch::ABMappingMask::operator>(const ABMappingMask& mask) const
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

