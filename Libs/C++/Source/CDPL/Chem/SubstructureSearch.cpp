/* 
 * SubstructureSearch.cpp 
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

#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{
    
    const std::size_t MAX_MAPPING_CACHE_SIZE = 1000;
}

using namespace CDPL;


Chem::SubstructureSearch::SubstructureSearch():
    query(0), 
    atomMatchExprFunc(static_cast<const AtomMatchExprPtr& (*)(const Atom&)>(&getMatchExpression)), 
    bondMatchExprFunc(static_cast<const BondMatchExprPtr& (*)(const Bond&)>(&getMatchExpression)), 
    molGraphMatchExprFunc(static_cast<const MolGraphMatchExprPtr& (*)(const MolecularGraph&)>(&getMatchExpression)),
    mappingCache(MAX_MAPPING_CACHE_SIZE), queryChanged(true), initQueryData(true), uniqueMatches(false), 
    exitSearch(false), numMappedAtoms(0), maxNumMappings(0) 
{
    mappingCache.setCleanupFunction(&AtomBondMapping::clear);
}

Chem::SubstructureSearch::SubstructureSearch(const MolecularGraph& query): 
    atomMatchExprFunc(static_cast<const AtomMatchExprPtr& (*)(const Atom&)>(&getMatchExpression)), 
    bondMatchExprFunc(static_cast<const BondMatchExprPtr& (*)(const Bond&)>(&getMatchExpression)), 
    molGraphMatchExprFunc(static_cast<const MolGraphMatchExprPtr& (*)(const MolecularGraph&)>(&getMatchExpression)),
    mappingCache(MAX_MAPPING_CACHE_SIZE), uniqueMatches(false), exitSearch(false), numMappedAtoms(0), maxNumMappings(0)
{
    mappingCache.setCleanupFunction(&AtomBondMapping::clear);

    setQuery(query);
}

Chem::SubstructureSearch::~SubstructureSearch() {}

void Chem::SubstructureSearch::setAtomMatchExpressionFunction(const AtomMatchExpressionFunction& func)
{
    atomMatchExprFunc = func;
}

void Chem::SubstructureSearch::setBondMatchExpressionFunction(const BondMatchExpressionFunction& func)
{
    bondMatchExprFunc = func;
}

void Chem::SubstructureSearch::setMolecularGraphMatchExpressionFunction(const MolecularGraphMatchExpressionFunction& func)
{
    molGraphMatchExprFunc = func;
}

bool Chem::SubstructureSearch::mappingExists(const MolecularGraph& target)
{
    freeAtomBondMappings();

    if (!init(target)) 
        return false;

    saveMappings = false;
    
    return mapAtoms();
}

bool Chem::SubstructureSearch::findMappings(const MolecularGraph& target)
{
    freeAtomBondMappings();

    if (!init(target))
        return false;

    saveMappings = true;
    mapAtoms();

    return !foundMappings.empty();
}

void Chem::SubstructureSearch::stopSearch()
{
    exitSearch = true;
}

std::size_t Chem::SubstructureSearch::getNumMappings() const
{
    return foundMappings.size();
}

Chem::AtomBondMapping& Chem::SubstructureSearch::getMapping(std::size_t idx)
{
    if (idx >= foundMappings.size())
        throw Base::IndexError("SubstructureSearch: mapping index out of bounds");

    return *foundMappings[idx];
}

const Chem::AtomBondMapping& Chem::SubstructureSearch::getMapping(std::size_t idx) const
{
    if (idx >= foundMappings.size())
        throw Base::IndexError("SubstructureSearch: mapping index out of bounds");

    return *foundMappings[idx];
}

Chem::SubstructureSearch::MappingIterator Chem::SubstructureSearch::getMappingsBegin()
{
    return foundMappings.begin();
}

Chem::SubstructureSearch::ConstMappingIterator Chem::SubstructureSearch::getMappingsBegin() const
{
    return foundMappings.begin();
}

Chem::SubstructureSearch::MappingIterator Chem::SubstructureSearch::getMappingsEnd()
{
    return foundMappings.end();
}

Chem::SubstructureSearch::ConstMappingIterator Chem::SubstructureSearch::getMappingsEnd() const
{
    return foundMappings.end();
}

Chem::SubstructureSearch::MappingIterator Chem::SubstructureSearch::begin()
{
    return foundMappings.begin();
}

Chem::SubstructureSearch::ConstMappingIterator Chem::SubstructureSearch::begin() const
{
    return foundMappings.begin();
}

Chem::SubstructureSearch::MappingIterator Chem::SubstructureSearch::end()
{
    return foundMappings.end();
}

Chem::SubstructureSearch::ConstMappingIterator Chem::SubstructureSearch::end() const
{
    return foundMappings.end();
}

void Chem::SubstructureSearch::uniqueMappingsOnly(bool unique)
{
    uniqueMatches = unique;
}

bool Chem::SubstructureSearch::uniqueMappingsOnly() const
{
    return uniqueMatches;
}

void Chem::SubstructureSearch::setMaxNumMappings(std::size_t max_num_mappings)
{
    maxNumMappings = max_num_mappings;
}

std::size_t Chem::SubstructureSearch::getMaxNumMappings() const
{
    return maxNumMappings;
}

void Chem::SubstructureSearch::addAtomMappingConstraint(std::size_t query_atom_idx, std::size_t target_atom_idx)
{
    atomMappingConstrs.insert(MappingConstraintMap::value_type(query_atom_idx, target_atom_idx));
}

void Chem::SubstructureSearch::clearAtomMappingConstraints()
{
    atomMappingConstrs.clear();
}

void Chem::SubstructureSearch::addBondMappingConstraint(std::size_t query_bond_idx, std::size_t target_bond_idx)
{
    bondMappingConstrs.insert(MappingConstraintMap::value_type(query_bond_idx, target_bond_idx));

}

void Chem::SubstructureSearch::clearBondMappingConstraints()
{
    bondMappingConstrs.clear();
}

void Chem::SubstructureSearch::setQuery(const MolecularGraph& query)
{
    this->query = &query;
    initQueryData = true;
    queryChanged = true;
}
    
bool Chem::SubstructureSearch::init(const MolecularGraph& tgt)
{
    if (!query)
        return false;

    exitSearch = false;
    numTargetAtoms = tgt.getNumAtoms();
    numTargetBonds = tgt.getNumBonds();
    target = &tgt;
    
    if (queryChanged) {
        numQueryAtoms = query->getNumAtoms();
        numQueryBonds = query->getNumBonds();

        initMatchExpressions();

        queryChanged = false;
    }

    if ((*molGraphMatchExpr)(*query, tgt, Base::Any()) && findEquivAtoms() && findEquivBonds()) {
        if (initQueryData) {
            queryMappingMask.reset();

            if (queryAtomMapping.size() < numQueryAtoms) 
                queryMappingMask.resize(numQueryAtoms);
                
            queryAtomMapping.assign(numQueryAtoms, 0);
            queryBondMapping.assign(numQueryBonds, 0);

            initQueryData = false;
        }

        targetMappingMask.initAtomMask(numTargetAtoms);
        targetMappingMask.initBondMask(numTargetBonds);

        return true;
    }

    return false;
}

void Chem::SubstructureSearch::initMatchExpressions()
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
        const MatchExpression<Atom, MolecularGraph>::SharedPointer& expr = atomMatchExprFunc(*atom);

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

        const MatchExpression<Bond, MolecularGraph>::SharedPointer& expr = bondMatchExprFunc(*bond);

        if (expr->requiresAtomBondMapping())
            postMappingMatchBonds.push_back(bond);
        
        bondMatchExprTable.push_back(expr);
    }

    molGraphMatchExpr = molGraphMatchExprFunc(*query);
}

bool Chem::SubstructureSearch::findEquivAtoms()
{    
    if (atomEquivMatrix.size() < numQueryAtoms)
        atomEquivMatrix.resize(numQueryAtoms);

    AtomMatchExprTable::const_iterator ame_it = atomMatchExprTable.begin();
    BitMatrix::iterator tem_it = atomEquivMatrix.begin();

    for (std::size_t i = 0; i < numQueryAtoms; i++, ++tem_it, ++ame_it) {
        Util::BitSet& equiv_mask = *tem_it;

        equiv_mask.resize(numTargetAtoms);
        equiv_mask.reset();

        const Atom& query_atom = query->getAtom(i);
        const MatchExpression<Atom, MolecularGraph>& expr = **ame_it;
        bool no_equiv_atoms = true;

        for (std::size_t j = 0; j < numTargetAtoms; j++) {
            if (!checkAtomMappingConstraints(i, j))
                continue;
            const Atom& target_atom = target->getAtom(j);

            if (expr(query_atom, *query, target_atom, *target, Base::Any())) {
                equiv_mask.set(j);
                no_equiv_atoms = false;
            }
        }

        if (no_equiv_atoms)
            return false;
    }

    return true;
}

bool Chem::SubstructureSearch::findEquivBonds()
{
    if (bondEquivMatrix.size() < numQueryBonds)
        bondEquivMatrix.resize(numQueryBonds);

    BondMatchExprTable::const_iterator bme_it = bondMatchExprTable.begin();
    BitMatrix::iterator tem_it = bondEquivMatrix.begin();

    for (std::size_t i = 0; i < numQueryBonds; i++, ++tem_it, ++bme_it) {
        Util::BitSet& equiv_mask = *tem_it;

        equiv_mask.resize(numTargetBonds);
        equiv_mask.reset();

        if (!*bme_it)
            continue;

        const Bond& query_bond = query->getBond(i);
        const MatchExpression<Bond, MolecularGraph>& expr = **bme_it;
        bool no_equiv_bonds = true;

        for (std::size_t j = 0; j < numTargetBonds; j++) {
            if (!checkBondMappingConstraints(i, j))
                continue;
 
            const Bond& target_bond = target->getBond(j);

            if (!target->containsAtom(target_bond.getBegin()) || !target->containsAtom(target_bond.getEnd()))
                continue;

            if (expr(query_bond, *query, target_bond, *target, Base::Any())) {
                equiv_mask.set(j);
                no_equiv_bonds = false;
            }
        }

        if (no_equiv_bonds)
            return false;
    }

    return true;
}

bool Chem::SubstructureSearch::mapAtoms()
{
    if (exitSearch)
        return true;
    
    if (numMappedAtoms == numQueryAtoms)
        return mappingFound();

    std::size_t query_atom_idx = nextQueryAtom();

    for (std::size_t target_atom_idx = 0, target_atom_nbr_idx = 0; nextTargetAtom(query_atom_idx, target_atom_idx, target_atom_nbr_idx); 
         target_atom_idx++, target_atom_nbr_idx++) {

        if (mapAtoms(query_atom_idx, target_atom_idx))
            return true;
    }

    return false;
}

std::size_t Chem::SubstructureSearch::nextQueryAtom() const
{
    std::size_t idx = numQueryAtoms;

    if (!termQueryAtoms.empty()) 
        idx = termQueryAtoms.front();
    else {
        std::size_t min_num_equiv_tgt_atoms = std::numeric_limits<std::size_t>::max();
        
        for (std::size_t i = 0; i < numQueryAtoms; i++) {
            if (queryAtomMapping[i])
                continue;

            std::size_t num_equiv_atoms = atomEquivMatrix[i].count();

            if (num_equiv_atoms < min_num_equiv_tgt_atoms) {
                idx = i;
                min_num_equiv_tgt_atoms = num_equiv_atoms;
            }
        }
    }

    assert(queryMappingMask.test(idx) == false);
    assert(idx < numQueryAtoms);

    return idx;
}

bool Chem::SubstructureSearch::nextTargetAtom(std::size_t query_atom_idx, std::size_t& target_atom_idx, 
                                              std::size_t& target_atom_nbr_idx) const
{
    if (!termQueryAtoms.empty()) {
        const Atom* prev_target_atom = queryAtomMapping[query_atom_idx];
        std::size_t num_target_atom_nbrs = prev_target_atom->getNumBonds();

        for ( ; target_atom_nbr_idx < num_target_atom_nbrs; target_atom_nbr_idx++) {
            const Atom& target_atom = prev_target_atom->getAtom(target_atom_nbr_idx);

            if (!target->containsAtom(target_atom))
                continue;

            if (!target->containsBond(prev_target_atom->getBond(target_atom_nbr_idx)))
                continue;

            target_atom_idx = target->getAtomIndex(target_atom);

            if (!atomMappingAllowed(query_atom_idx, target_atom_idx))
                continue;

            return true;
        }

        return false;
    }

    for ( ; target_atom_idx < numTargetAtoms && !atomMappingAllowed(query_atom_idx, target_atom_idx); target_atom_idx++);

    return (target_atom_idx < numTargetAtoms);
}

bool Chem::SubstructureSearch::atomMappingAllowed(std::size_t query_atom_idx, std::size_t target_atom_idx) const
{
    if (targetMappingMask.testAtomBit(target_atom_idx) || !atomEquivMatrix[query_atom_idx].test(target_atom_idx))
        return false;

    return true;
}

bool Chem::SubstructureSearch::checkAtomMappingConstraints(std::size_t query_atom_idx, std::size_t target_atom_idx) const
{
    if (atomMappingConstrs.empty())
        return true;

    std::pair<MappingConstraintMap::const_iterator, MappingConstraintMap::const_iterator> eq_range = atomMappingConstrs.equal_range(query_atom_idx);

    if (eq_range.first == eq_range.second)
        return true;

    for ( ; eq_range.first != eq_range.second; ++eq_range.first)
        if (eq_range.first->second == target_atom_idx)
            return true;

    return false;
}

bool Chem::SubstructureSearch::checkBondMappingConstraints(std::size_t query_bond_idx, std::size_t target_bond_idx) const
{
    if (bondMappingConstrs.empty())
        return true;

    std::pair<MappingConstraintMap::const_iterator, MappingConstraintMap::const_iterator> eq_range = bondMappingConstrs.equal_range(query_bond_idx);

    if (eq_range.first == eq_range.second)
        return true;

    for ( ; eq_range.first != eq_range.second; ++eq_range.first)
        if (eq_range.first->second == target_bond_idx)
            return true;

    return false;
}

bool Chem::SubstructureSearch::mapBonds(std::size_t query_atom_idx, std::size_t target_atom_idx)
{
    const Atom& query_atom = query->getAtom(query_atom_idx);
    const Atom& target_atom = target->getAtom(target_atom_idx);

    Atom::ConstAtomIterator atoms_end = query_atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = query_atom.getBondsBegin();

    std::size_t unmapped_query_nbrs = 0;

    for (Atom::ConstAtomIterator a_it = query_atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        if (!query->containsAtom(*a_it) || !query->containsBond(*b_it))
            continue;

        std::size_t nbr_atom_idx = query->getAtomIndex(*a_it);

        if (queryMappingMask.test(nbr_atom_idx)) {
            const Atom* mapped_target_atom = queryAtomMapping[nbr_atom_idx];
            const Bond* target_nbr_bond = target_atom.findBondToAtom(*mapped_target_atom);

            if (!target_nbr_bond || !target->containsBond(*target_nbr_bond))
                return false;

            std::size_t bond_idx = query->getBondIndex(*b_it);

            if (!bondEquivMatrix[bond_idx].test(target->getBondIndex(*target_nbr_bond)))
                return false;

            queryBondMapping[bond_idx] = target_nbr_bond;

        } else
            unmapped_query_nbrs++;
    }

    atoms_end = target_atom.getAtomsEnd();
    b_it = target_atom.getBondsBegin();

    std::size_t unmapped_target_nbrs = 0;

    for (Atom::ConstAtomIterator a_it = target_atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        if (!target->containsAtom(*a_it) || !target->containsBond(*b_it))
            continue;

        std::size_t nbr_atom_idx = target->getAtomIndex(*a_it);

        if (!targetMappingMask.testAtomBit(nbr_atom_idx))
            unmapped_target_nbrs++;
    }

    return (unmapped_query_nbrs <= unmapped_target_nbrs);
}

bool Chem::SubstructureSearch::mapAtoms(std::size_t query_atom_idx, std::size_t target_atom_idx)
{
    if (exitSearch)
        return true;

    if (!mapBonds(query_atom_idx, target_atom_idx))
        return false;

    bool had_term_atoms;

    if ((had_term_atoms = !termQueryAtoms.empty()))
        termQueryAtoms.pop_front();        

    const Atom& query_atom = query->getAtom(query_atom_idx);
    const Atom& target_atom = target->getAtom(target_atom_idx);

    const Atom* prev_mapping = queryAtomMapping[query_atom_idx];

    queryAtomMapping[query_atom_idx] = &target_atom;

    queryMappingMask.set(query_atom_idx);
    targetMappingMask.setAtomBit(target_atom_idx);

    Atom::ConstAtomIterator atoms_end = query_atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = query_atom.getBondsBegin();

    std::size_t num_term_atoms = 0;

    for (Atom::ConstAtomIterator a_it = query_atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        if (!query->containsAtom(*a_it) || !query->containsBond(*b_it))
            continue;

        std::size_t nbr_atom_idx = query->getAtomIndex(*a_it);

        if (!queryAtomMapping[nbr_atom_idx]) {
            queryAtomMapping[nbr_atom_idx] = &target_atom;

            termQueryAtoms.push_back(nbr_atom_idx);
            num_term_atoms++;
        }
    }

    numMappedAtoms++;

    bool exit = mapAtoms();

    numMappedAtoms--;

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

bool Chem::SubstructureSearch::mappingFound()
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

bool Chem::SubstructureSearch::hasPostMappingMatchExprs() const
{
    return (molGraphMatchExpr->requiresAtomBondMapping() || !postMappingMatchAtoms.empty() ||
            !postMappingMatchBonds.empty());
}

bool Chem::SubstructureSearch::foundMappingMatches(const AtomBondMapping* mapping) const
{
    if (molGraphMatchExpr->requiresAtomBondMapping() && 
        !((*molGraphMatchExpr)(*query, *target, *mapping, Base::Any())))
        return false;

    AtomList::const_iterator post_map_atoms_end = postMappingMatchAtoms.end();

    for (AtomList::const_iterator it = postMappingMatchAtoms.begin(); it != post_map_atoms_end; ++it) {
        const Atom& atom = **it;
        std::size_t atom_idx = query->getAtomIndex(atom);

        if (!(*atomMatchExprTable[atom_idx])(atom, *query, *queryAtomMapping[atom_idx], 
                                             *target, *mapping, Base::Any()))
            return false;
    }

    BondList::const_iterator post_map_bonds_end = postMappingMatchBonds.end();

    for (BondList::const_iterator it = postMappingMatchBonds.begin(); it != post_map_bonds_end; ++it) {
        const Bond& bond = **it;
        std::size_t bond_idx = query->getBondIndex(bond);

        if (!(*bondMatchExprTable[bond_idx])(bond, *query, *queryBondMapping[bond_idx], 
                                             *target, *mapping, Base::Any()))
            return false;
    }

    return true;
}

bool Chem::SubstructureSearch::foundMappingUnique()
{
    targetMappingMask.resetBondMask();

    for (std::size_t i = 0; i < numQueryBonds; i++) {
        if (!bondMatchExprTable[i])
            continue;

        targetMappingMask.setBondBit(target->getBondIndex(*queryBondMapping[i]));
    }

    return uniqueMappings.insert(targetMappingMask).second;
}

void Chem::SubstructureSearch::freeAtomBondMappings()
{
    foundMappings.clear();
    mappingCache.putAll();

    if (uniqueMatches)
        uniqueMappings.clear();
}

void Chem::SubstructureSearch::freeAtomBondMapping()
{
    mappingCache.put();
}

Chem::AtomBondMapping* Chem::SubstructureSearch::createAtomBondMapping()
{
    AtomBondMapping* mapping = mappingCache.get();
    AtomMapping& atom_mapping = mapping->getAtomMapping();
    BondMapping& bond_mapping = mapping->getBondMapping();

    MolecularGraph::ConstAtomIterator atoms_end = query->getAtomsEnd();
    AtomMappingTable::const_iterator am_it = queryAtomMapping.begin();

    for (MolecularGraph::ConstAtomIterator a_it = query->getAtomsBegin(); a_it != atoms_end; ++a_it, ++am_it)
        atom_mapping.insertEntry(&*a_it, *am_it);

    MolecularGraph::ConstBondIterator bonds_end = query->getBondsEnd();
    BondMappingTable::const_iterator bm_it = queryBondMapping.begin();

    std::size_t i = 0;

    for (MolecularGraph::ConstBondIterator b_it = query->getBondsBegin(); b_it != bonds_end; ++b_it, ++bm_it, i++) {
        if (!bondMatchExprTable[i])
            continue;

        bond_mapping.insertEntry(&*b_it, *bm_it);
    }

    return mapping;
}


void Chem::SubstructureSearch::ABMappingMask::initAtomMask(std::size_t num_atoms)
{
    atomMask.reset();

    if (atomMask.size() < num_atoms)
        atomMask.resize(num_atoms);
}

void Chem::SubstructureSearch::ABMappingMask::initBondMask(std::size_t num_bonds)
{
    if (bondMask.size() < num_bonds)
        bondMask.resize(num_bonds);
}

void Chem::SubstructureSearch::ABMappingMask::setAtomBit(std::size_t atom_idx)
{
    atomMask.set(atom_idx);
}

void Chem::SubstructureSearch::ABMappingMask::resetAtomBit(std::size_t atom_idx)
{
    atomMask.reset(atom_idx);
}

bool Chem::SubstructureSearch::ABMappingMask::testAtomBit(std::size_t atom_idx) const
{
    return atomMask.test(atom_idx);
}

void Chem::SubstructureSearch::ABMappingMask::setBondBit(std::size_t bond_idx)
{
    bondMask.set(bond_idx);
}

void Chem::SubstructureSearch::ABMappingMask::resetBondMask()
{
    bondMask.reset();
}

bool Chem::SubstructureSearch::ABMappingMask::operator<(const ABMappingMask& mask) const
{
    if (atomMask == mask.atomMask)
        return (bondMask < mask.bondMask);

    return (atomMask < mask.atomMask);
}

bool Chem::SubstructureSearch::ABMappingMask::operator>(const ABMappingMask& mask) const
{
    if (atomMask == mask.atomMask)
        return (bondMask > mask.bondMask);

    return (atomMask > mask.atomMask);
}
