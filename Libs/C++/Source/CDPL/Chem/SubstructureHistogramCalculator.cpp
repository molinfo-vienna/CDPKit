/* 
 * SubstructureHistogramCalculator.cpp 
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

#include "CDPL/Chem/SubstructureHistogramCalculator.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::SubstructureHistogramCalculator::Pattern::Pattern(const MolecularGraph::SharedPointer& structure, std::size_t id,
													   std::size_t priority, bool all_matches, bool unique_matches):
    structure(structure), id(id), priority(priority), allMatches(all_matches), uniqueMatches(unique_matches)
{}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureHistogramCalculator::Pattern::getStructure() const
{
    return structure;
}

std::size_t Chem::SubstructureHistogramCalculator::Pattern::getID() const
{
    return id;
}

std::size_t Chem::SubstructureHistogramCalculator::Pattern::getPriority() const
{
    return priority;
}

bool Chem::SubstructureHistogramCalculator::Pattern::processAllMatches() const
{
    return allMatches;
}

bool Chem::SubstructureHistogramCalculator::Pattern::processUniqueMatchesOnly() const
{
    return uniqueMatches;
}


//----------

Chem::SubstructureHistogramCalculator::SubstructureHistogramCalculator() {}

Chem::SubstructureHistogramCalculator::SubstructureHistogramCalculator(const SubstructureHistogramCalculator& calculator):
    patterns(calculator.patterns), matchedSubstructMasks(calculator.matchedSubstructMasks)
{}

void Chem::SubstructureHistogramCalculator::addPattern(const MolecularGraph::SharedPointer& structure, std::size_t id, 
													  std::size_t priority, bool all_matches, bool unique_matches)
{
    addPattern(Pattern(structure, id, priority, all_matches, unique_matches));
}

void Chem::SubstructureHistogramCalculator::addPattern(const Pattern& ptn)
{
    PriorityToAtomBondMaskMap::const_iterator it = matchedSubstructMasks.find(ptn.getPriority());

    if (it == matchedSubstructMasks.end())
		matchedSubstructMasks.insert(PriorityToAtomBondMaskMap::value_type(ptn.getPriority(), AtomBondMask()));

    patterns.push_back(ptn);
}

const Chem::SubstructureHistogramCalculator::Pattern& Chem::SubstructureHistogramCalculator::getPattern(std::size_t idx) const
{
    if (idx >= patterns.size())
		throw Base::IndexError("SubstructureHistogramCalculator: pattern index out of bounds");

    return patterns[idx];
}

void Chem::SubstructureHistogramCalculator::removePattern(std::size_t idx)
{
    if (idx >= patterns.size())
		throw Base::IndexError("SubstructureHistogramCalculator: pattern index out of bounds");

    std::size_t priority = patterns[idx].getPriority();

    patterns.erase(patterns.begin() + idx);

    if (std::find_if(patterns.begin(), patterns.end(),
					 std::bind(std::equal_to<std::size_t>(), priority,
							   std::bind(&Pattern::getPriority, std::placeholders::_1))) == patterns.end())
		matchedSubstructMasks.erase(priority);
}

void Chem::SubstructureHistogramCalculator::clear()
{
    matchedSubstructMasks.clear();
    patterns.clear();
}

std::size_t Chem::SubstructureHistogramCalculator::getNumPatterns() const
{
    return patterns.size();
}

void Chem::SubstructureHistogramCalculator::removePattern(const PatternIterator& ptn_it)
{
    std::size_t idx = ptn_it - patterns.begin();

    if (idx >= patterns.size())
		throw Base::IndexError("SubstructureHistogramCalculator: pattern iterator out of bounds");

    std::size_t priority = ptn_it->getPriority();

    patterns.erase(ptn_it);

    if (std::find_if(patterns.begin(), patterns.end(),
					 std::bind(std::equal_to<std::size_t>(), priority,
							   std::bind(&Pattern::getPriority, std::placeholders::_1))) == patterns.end())
		matchedSubstructMasks.erase(priority);
}

Chem::SubstructureHistogramCalculator::ConstPatternIterator Chem::SubstructureHistogramCalculator::getPatternsBegin() const
{
    return patterns.begin();
}

Chem::SubstructureHistogramCalculator::ConstPatternIterator Chem::SubstructureHistogramCalculator::getPatternsEnd() const
{
    return patterns.end();
}

Chem::SubstructureHistogramCalculator::PatternIterator Chem::SubstructureHistogramCalculator::getPatternsBegin()
{
    return patterns.begin();
}

Chem::SubstructureHistogramCalculator::PatternIterator Chem::SubstructureHistogramCalculator::getPatternsEnd()
{
    return patterns.end();
}

Chem::SubstructureHistogramCalculator::ConstPatternIterator Chem::SubstructureHistogramCalculator::begin() const
{
    return patterns.begin();
}

Chem::SubstructureHistogramCalculator::ConstPatternIterator Chem::SubstructureHistogramCalculator::end() const
{
    return patterns.end();
}

Chem::SubstructureHistogramCalculator::PatternIterator Chem::SubstructureHistogramCalculator::begin()
{
    return patterns.begin();
}

Chem::SubstructureHistogramCalculator::PatternIterator Chem::SubstructureHistogramCalculator::end()
{
    return patterns.end();
}

Chem::SubstructureHistogramCalculator& Chem::SubstructureHistogramCalculator::operator=(const SubstructureHistogramCalculator& calculator)
{
    if (this == &calculator)
		return *this;

    patterns = calculator.patterns;
    matchedSubstructMasks = calculator.matchedSubstructMasks;

    return *this;
}

void Chem::SubstructureHistogramCalculator::doCalculate(const MolecularGraph& molgraph, const HistoUpdateFunction& func)
{
    init(molgraph);

    std::size_t num_ptns = patterns.size();

    for (std::size_t i = 0; i < num_ptns; i++)
		processPattern(patterns[i], func);
}

void Chem::SubstructureHistogramCalculator::init(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;

    if (matchedSubstructMasks.size() <= 1)
		return;

    std::size_t num_atoms = molgraph.getNumAtoms();
    std::size_t num_bonds = molgraph.getNumBonds();

    testingAtomBondMask.first.resize(num_atoms);
    testingAtomBondMask.second.resize(num_bonds);

    for (PriorityToAtomBondMaskMap::iterator it = matchedSubstructMasks.begin(), end = matchedSubstructMasks.end(); it != end; ++it) {
		AtomBondMask& masks = it->second;

		masks.first.resize(num_atoms);
		masks.second.resize(num_bonds);

		masks.first.reset();
		masks.second.reset();
    }
}

void Chem::SubstructureHistogramCalculator::processPattern(const Pattern& ptn, const HistoUpdateFunction& func)
{
    if (!ptn.getStructure())
		return;

    substructSearch.uniqueMappingsOnly(ptn.processUniqueMatchesOnly());
    substructSearch.setQuery(*ptn.getStructure());
    substructSearch.findMappings(*molGraph);

    for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(), end = substructSearch.getMappingsEnd(); it != end; ++it) {
		if (processMatch(*it, ptn, func) && !ptn.processAllMatches())
			return;
    }
}

bool Chem::SubstructureHistogramCalculator::processMatch(const AtomBondMapping& mapping, const Pattern& ptn, const HistoUpdateFunction& func)
{
    if (matchedSubstructMasks.size() <= 1) {
		func(ptn.getID());
		return true;
    }

    testingAtomBondMask.first.reset();
    testingAtomBondMask.second.reset();

    for (AtomMapping::ConstEntryIterator it = mapping.getAtomMapping().getEntriesBegin(), end = mapping.getAtomMapping().getEntriesEnd(); it != end; ++it) {
		const Atom* mpd_atom = it->second;

		if (mpd_atom != 0)
			testingAtomBondMask.first.set(molGraph->getAtomIndex(*mpd_atom));
    }
 
    for (BondMapping::ConstEntryIterator it = mapping.getBondMapping().getEntriesBegin(), end = mapping.getBondMapping().getEntriesEnd(); it != end; ++it) {
		const Bond* mpd_bond = it->second;
	
		if (mpd_bond != 0)
			testingAtomBondMask.second.set(molGraph->getBondIndex(*mpd_bond));
    }

    PriorityToAtomBondMaskMap::iterator it = matchedSubstructMasks.find(ptn.getPriority());
    PriorityToAtomBondMaskMap::iterator end = matchedSubstructMasks.end();

    if (it != end) {
		PriorityToAtomBondMaskMap::iterator it_copy = it;

		for (++it; it != end; ++it) {
			const AtomBondMask& masks = it_copy->second;

			tmpMask = testingAtomBondMask.first;
			tmpMask &= masks.first;

			bool atom_match = (tmpMask == testingAtomBondMask.first);

			tmpMask = testingAtomBondMask.second;
			tmpMask &= masks.second;

			bool bond_match = (tmpMask == testingAtomBondMask.second);

			if (atom_match && bond_match)
				return false;
		} 

		AtomBondMask& masks = it_copy->second;

		masks.first |= testingAtomBondMask.first;
		masks.second |= testingAtomBondMask.second;
    }

    func(ptn.getID());
    return true;
}
