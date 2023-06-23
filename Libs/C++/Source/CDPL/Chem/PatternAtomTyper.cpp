/* 
 * PatternAtomTyper.cpp 
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

#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::PatternAtomTyper::Pattern::Pattern(const MolecularGraph::SharedPointer& structure, std::size_t atom_label, std::size_t priority, 
										 bool all_matches, bool unique_matches):
	structure(structure), priority(priority), atomLabel(atom_label), allMatches(all_matches), uniqueMatches(unique_matches)
{
	if (!structure)
		return;

	for (MolecularGraph::ConstAtomIterator it = structure->getAtomsBegin(), end = structure->getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (hasAtomMappingID(atom))
			labeledAtoms.push_back(AtomLabelPair(&atom, getAtomMappingID(atom)));
	}
}

const Chem::MolecularGraph::SharedPointer& Chem::PatternAtomTyper::Pattern::getStructure() const
{
	return structure;
}

std::size_t Chem::PatternAtomTyper::Pattern::getPriority() const
{
	return priority;
}

std::size_t Chem::PatternAtomTyper::Pattern::getAtomLabel() const
{
	return atomLabel;
}

bool Chem::PatternAtomTyper::Pattern::processAllMatches() const
{
	return allMatches;
}

bool Chem::PatternAtomTyper::Pattern::processUniqueMatchesOnly() const
{
	return uniqueMatches;
}

const Chem::PatternAtomTyper::Pattern::LabeledAtomList& Chem::PatternAtomTyper::Pattern::getLabeledAtoms() const
{
	return labeledAtoms;
}


//----------

Chem::PatternAtomTyper::PatternAtomTyper() {}

Chem::PatternAtomTyper::PatternAtomTyper(const PatternAtomTyper& typer):
	patterns(typer.patterns), atomLabeling(typer.atomLabeling), 
	matchingPatternIndices(typer.matchingPatternIndices) 
{}

void Chem::PatternAtomTyper::addPattern(const MolecularGraph::SharedPointer& structure, std::size_t atom_label, 
										std::size_t priority, bool all_matches, bool unique_matches)
{
	addPattern(Pattern(structure, atom_label, priority, all_matches, unique_matches));
}

void Chem::PatternAtomTyper::addPattern(const Pattern& ptn)
{
	patterns.push_back(ptn);
}

const Chem::PatternAtomTyper::Pattern& Chem::PatternAtomTyper::getPattern(std::size_t idx) const
{
	if (idx >= patterns.size())
		throw Base::IndexError("PatternAtomTyper: pattern index out of bounds");

	return patterns[idx];
}

void Chem::PatternAtomTyper::removePattern(std::size_t idx)
{
	if (idx >= patterns.size())
		throw Base::IndexError("PatternAtomTyper: pattern index out of bounds");

	patterns.erase(patterns.begin() + idx);
}

void Chem::PatternAtomTyper::clear()
{
	patterns.clear();
}

std::size_t Chem::PatternAtomTyper::getNumPatterns() const
{
	return patterns.size();
}

void Chem::PatternAtomTyper::removePattern(const PatternIterator& ptn_it)
{
	std::size_t idx = ptn_it - patterns.begin();

	if (idx >= patterns.size())
		throw Base::IndexError("PatternAtomTyper: pattern iterator out of bounds");

	patterns.erase(ptn_it);
}

Chem::PatternAtomTyper::ConstPatternIterator Chem::PatternAtomTyper::getPatternsBegin() const
{
	return patterns.begin();
}

Chem::PatternAtomTyper::ConstPatternIterator Chem::PatternAtomTyper::getPatternsEnd() const
{
	return patterns.end();
}

Chem::PatternAtomTyper::PatternIterator Chem::PatternAtomTyper::getPatternsBegin()
{
	return patterns.begin();
}

Chem::PatternAtomTyper::PatternIterator Chem::PatternAtomTyper::getPatternsEnd()
{
	return patterns.end();
}

Chem::PatternAtomTyper::ConstPatternIterator Chem::PatternAtomTyper::begin() const
{
	return patterns.begin();
}

Chem::PatternAtomTyper::ConstPatternIterator Chem::PatternAtomTyper::end() const
{
	return patterns.end();
}

Chem::PatternAtomTyper::PatternIterator Chem::PatternAtomTyper::begin()
{
	return patterns.begin();
}

Chem::PatternAtomTyper::PatternIterator Chem::PatternAtomTyper::end()
{
	return patterns.end();
}

std::size_t Chem::PatternAtomTyper::getAtomLabel(std::size_t idx) const
{
	if (idx >= atomLabeling.size())
		throw Base::IndexError("PatternAtomTyper: atom index out of bounds");
	
	return atomLabeling[idx];
}

std::size_t Chem::PatternAtomTyper::getPatternIndex(std::size_t idx) const
{
	if (idx >= matchingPatternIndices.size())
		throw Base::IndexError("PatternAtomTyper: atom index out of bounds");
	
	return matchingPatternIndices[idx];
}

bool Chem::PatternAtomTyper::hasAtomLabel(std::size_t idx) const
{
	if (idx >= labeledAtomMask.size())
		throw Base::IndexError("PatternAtomTyper: atom index out of bounds");
	
	return labeledAtomMask.test(idx);
}

Chem::PatternAtomTyper& Chem::PatternAtomTyper::operator=(const PatternAtomTyper& typer)
{
	if (this == &typer)
		return *this;

	patterns = typer.patterns;
	atomLabeling = typer.atomLabeling;
	matchingPatternIndices = typer.matchingPatternIndices;

	return *this;
}

void Chem::PatternAtomTyper::execute(const MolecularGraph& molgraph)
{
	init(molgraph);

	std::size_t num_ptns = patterns.size();

	for (std::size_t i = 0; i < num_ptns; i++)
		processPattern(patterns[i], i);
}

void Chem::PatternAtomTyper::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();

	atomLabeling.assign(num_atoms, 0);
	matchingPatternIndices.assign(num_atoms, 0);

	if (labeledAtomMask.size() < num_atoms)
		labeledAtomMask.resize(num_atoms);

	labeledAtomMask.reset();
}

void Chem::PatternAtomTyper::processPattern(const Pattern& ptn, std::size_t ptn_idx)
{
	if (!ptn.getStructure())
		return;

	substructSearch.uniqueMappingsOnly(ptn.processUniqueMatchesOnly());
	substructSearch.setQuery(*ptn.getStructure());
	substructSearch.findMappings(*molGraph);

	for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(), end = substructSearch.getMappingsEnd(); it != end; ++it) {
		if (processMatch(it->getAtomMapping(), ptn, ptn_idx) && !ptn.processAllMatches())
			return;
	}
}

bool Chem::PatternAtomTyper::processMatch(const AtomMapping& mapping, const Pattern& ptn, std::size_t ptn_idx)
{
	const Pattern::LabeledAtomList lbld_ptn_atoms = ptn.getLabeledAtoms();
	std::size_t priority = ptn.getPriority();
	bool changes = false;

	if (!lbld_ptn_atoms.empty()) {
		for (Pattern::LabeledAtomList::const_iterator it = lbld_ptn_atoms.begin(), end = lbld_ptn_atoms.end(); it != end; ++it) {
			const Atom* mpd_atom = mapping[it->first];

			if (!mpd_atom)
				continue;

			std::size_t atom_idx = molGraph->getAtomIndex(*mpd_atom);

			if (!labeledAtomMask.test(atom_idx) || (patterns[matchingPatternIndices[atom_idx]].getPriority() <= priority)) {
				matchingPatternIndices[atom_idx] = ptn_idx;
				atomLabeling[atom_idx] = it->second;
				labeledAtomMask.set(atom_idx);
				changes = true;
			}
		}

	} else {
		std::size_t atom_label = ptn.getAtomLabel();

		for (AtomMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it) {
			const Atom* mpd_atom = it->second;

			if (!mpd_atom)
				continue;

			std::size_t atom_idx = molGraph->getAtomIndex(*mpd_atom);

			if (!labeledAtomMask.test(atom_idx) || (patterns[matchingPatternIndices[atom_idx]].getPriority() <= priority)) {
				matchingPatternIndices[atom_idx] = ptn_idx;
				atomLabeling[atom_idx] = atom_label;
				labeledAtomMask.set(atom_idx);
				changes = true;
			}
		}
	}

	return changes;
}
