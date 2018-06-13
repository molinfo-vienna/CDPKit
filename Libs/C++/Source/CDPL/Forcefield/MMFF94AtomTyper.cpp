/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AtomTyper.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Forcefield/MMFF94AtomTyper.hpp"
#include "CDPL/Forcefield/MMFF94SymbolicAtomTypePatternTable.hpp"
#include "CDPL/Forcefield/MMFF94HeavyToHydrogenAtomTypeMap.hpp"
#include "CDPL/Forcefield/MMFF94SymbolicToNumericAtomTypeMap.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


Forcefield::MMFF94AtomTyper::MMFF94AtomTyper(): strictMode(true), symTypePatternTable(0), hydTypeMap(0), numTypeMap(0), molGraph(0)
{
	setSymbolicAtomTypePatternTable(MMFF94SymbolicAtomTypePatternTable::get());
	setHeavyToHydrogenAtomTypeMap(MMFF94HeavyToHydrogenAtomTypeMap::get());
	setSymbolicToNumericAtomTypeMap(MMFF94SymbolicToNumericAtomTypeMap::get());
}

void Forcefield::MMFF94AtomTyper::setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable& table)
{
	atomTyper.clear();

	std::size_t i = 0;

	for (MMFF94SymbolicAtomTypePatternTable::ConstEntryIterator it = table.getEntriesBegin(), end = table.getEntriesEnd(); it != end; ++it, i++) {
		const MMFF94SymbolicAtomTypePatternTable::Entry entry = *it;

		atomTyper.addPattern(entry.getPattern(), i);
	}

	symTypePatternTable = &table;
}

void Forcefield::MMFF94AtomTyper::setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap& map)
{
	hydTypeMap = &map;
}

void Forcefield::MMFF94AtomTyper::setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap& map)
{
	numTypeMap = &map;
}

void Forcefield::MMFF94AtomTyper::strictAtomTyping(bool strict)
{
	strictMode = strict;
}

bool Forcefield::MMFF94AtomTyper::strictAtomTyping() const
{
	return strictMode;
}

void Forcefield::MMFF94AtomTyper::perceiveTypes(const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	perceiveInitialAtomTypes();
	assignAromaticAtomTypes();
	assignHydrogenAtomTypes();
	assignNumericAtomTypes();
}

const std::string& Forcefield::MMFF94AtomTyper::getSymbolicType(std::size_t idx)
{
	if (idx >= symTypes.size())
		throw Base::IndexError("MMFF94AtomTyper: atom index out of bounds");
	
	return symTypes[idx];
}

unsigned int Forcefield::MMFF94AtomTyper::getNumericType(std::size_t idx)
{
	if (idx >= numTypes.size())
		throw Base::IndexError("MMFF94AtomTyper: atom index out of bounds");
	
	return numTypes[idx];
}

void Forcefield::MMFF94AtomTyper::init(const Chem::MolecularGraph& molgraph)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	symTypes.assign(num_atoms, "");
	numTypes.assign(num_atoms, 0);

	molGraph = &molgraph;
}

void Forcefield::MMFF94AtomTyper::perceiveInitialAtomTypes()
{
	atomTyper.execute(*molGraph);

	std::size_t num_atoms = molGraph->getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++) {
		if (!atomTyper.hasAtomLabel(i))
			continue;

		std::size_t ptn_idx = atomTyper.getPatternIndex(i);

		const MMFF94SymbolicAtomTypePatternTable::Entry& entry = symTypePatternTable->getEntry(ptn_idx);

		if (strictMode && entry.isFallbackType())
			continue;

		symTypes[i] = entry.getSymbolicType();
	}
}

void Forcefield::MMFF94AtomTyper::assignAromaticAtomTypes()
{
}

void Forcefield::MMFF94AtomTyper::assignHydrogenAtomTypes()
{
	using namespace Chem;

	for (std::size_t i = 0, num_atoms = symTypes.size(); i < num_atoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		if (getType(atom) == AtomType::H)
			continue;

		const std::string& h_type = hydTypeMap->getHydrogenType(symTypes[i]);

		if (h_type.empty())
			continue;

		Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;

			if (!molGraph->containsAtom(nbr_atom) || !molGraph->containsBond(*b_it))
				continue;

			if (getType(nbr_atom) != AtomType::H)
				continue;

			std::size_t nbr_idx = molGraph->getAtomIndex(nbr_atom);

			if (symTypes[nbr_idx].empty())
				symTypes[nbr_idx] = h_type;
		}
	}
}

void Forcefield::MMFF94AtomTyper::assignNumericAtomTypes()
{
	std::transform(symTypes.begin(), symTypes.end(), numTypes.begin(), 
				   boost::bind(&MMFF94SymbolicToNumericAtomTypeMap::getNumericType, boost::ref(numTypeMap), _1));
}
