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
#include <locale>
#include <functional>
#include <iterator>

#include <boost/bind.hpp>

#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


ForceField::MMFF94AtomTyper::MMFF94AtomTyper(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types, bool strict):
	aromRingSetFunc(&getMMFF94AromaticRings) 
{
	setSymbolicAtomTypePatternTable(MMFF94SymbolicAtomTypePatternTable::get());
	setAromaticAtomTypeDefinitionTable(MMFF94AromaticAtomTypeDefinitionTable::get());
	setHeavyToHydrogenAtomTypeMap(MMFF94HeavyToHydrogenAtomTypeMap::get());
	setSymbolicToNumericAtomTypeMap(MMFF94SymbolicToNumericAtomTypeMap::get());
	setAtomTypePropertyTable(MMFF94AtomTypePropertyTable::get());

	perceiveTypes(molgraph, sym_types, num_types, strict);
}

ForceField::MMFF94AtomTyper::MMFF94AtomTyper(): aromRingSetFunc(&getMMFF94AromaticRings) 
{
	setSymbolicAtomTypePatternTable(MMFF94SymbolicAtomTypePatternTable::get());
	setAromaticAtomTypeDefinitionTable(MMFF94AromaticAtomTypeDefinitionTable::get());
	setHeavyToHydrogenAtomTypeMap(MMFF94HeavyToHydrogenAtomTypeMap::get());
	setSymbolicToNumericAtomTypeMap(MMFF94SymbolicToNumericAtomTypeMap::get());
	setAtomTypePropertyTable(MMFF94AtomTypePropertyTable::get());
}

void ForceField::MMFF94AtomTyper::setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable::SharedPointer& table)
{
	atomTyper.clear();

	std::size_t i = 0;

	for (MMFF94SymbolicAtomTypePatternTable::ConstEntryIterator it = table->getEntriesBegin(), end = table->getEntriesEnd(); it != end; ++it, i++) {
		const MMFF94SymbolicAtomTypePatternTable::Entry entry = *it;

		atomTyper.addPattern(entry.getPattern(), i);
	}

	symTypePatternTable = table;
}

void ForceField::MMFF94AtomTyper::setAromaticAtomTypeDefinitionTable(const MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& table)
{
	aromTypeDefTable = table;
}

void ForceField::MMFF94AtomTyper::setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer& map)
{
	hydTypeMap = map;
}

void ForceField::MMFF94AtomTyper::setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap::SharedPointer& map)
{
	numTypeMap = map;
}

void ForceField::MMFF94AtomTyper::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	atomTypePropTable = table;
}

void ForceField::MMFF94AtomTyper::setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func)
{
	aromRingSetFunc = func;
}
		
void ForceField::MMFF94AtomTyper::perceiveTypes(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types, bool strict)
{
	init(molgraph, sym_types, num_types);

	assignProvisionalSymbolicAtomTypes(strict);
	assignAromaticAtomTypes();
	assignHydrogenAtomTypes();
	assignNumericAtomTypes(num_types);
}

void ForceField::MMFF94AtomTyper::init(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types)
{
	std::size_t num_atoms = molgraph.getNumAtoms();
	
	sym_types.assign(num_atoms, "");
	num_types.resize(num_atoms);
	aromRings.clear();

	molGraph = &molgraph;
	symTypes = &sym_types;
}

void ForceField::MMFF94AtomTyper::assignProvisionalSymbolicAtomTypes(bool strict)
{
	atomTyper.execute(*molGraph);

	std::size_t num_atoms = molGraph->getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++) {
		if (!atomTyper.hasAtomLabel(i))
			continue;

		std::size_t ptn_idx = atomTyper.getPatternIndex(i);

		const MMFF94SymbolicAtomTypePatternTable::Entry& entry = symTypePatternTable->getEntry(ptn_idx);

		if (strict && entry.isFallbackType())
			continue;

		(*symTypes)[i] = entry.getSymbolicType();
	}
}

void ForceField::MMFF94AtomTyper::assignAromaticAtomTypes()
{
	using namespace Chem;

	const FragmentList::BaseType::SharedPointer& arom_rings = aromRingSetFunc(*molGraph);

	std::transform(arom_rings->getElementsBegin(), arom_rings->getElementsEnd(), std::back_inserter(aromRings), 
				   boost::bind(&Fragment::SharedPointer::get, _1));
 
	std::sort(aromRings.begin(), aromRings.end(), 
			  boost::bind(std::greater<std::size_t>(), boost::bind(&Fragment::getNumAtoms, _1), boost::bind(&Fragment::getNumAtoms, _2)));

	std::for_each(aromRings.begin(), aromRings.end(), 
				  boost::bind(&ForceField::MMFF94AtomTyper::assignAromaticAtomTypes, this, _1));
}

void ForceField::MMFF94AtomTyper::assignAromaticAtomTypes(const Chem::Fragment* ring)
{
	using namespace Chem;

	std::size_t r_size = ring->getNumAtoms();
	std::size_t het_atom_idx = getUniqueHeteroAtomIndex(*ring);
	bool n5_anion = isN5Anion(*ring);
	bool im_cation = isImidazoliumCation(*ring);

	std::size_t num_arom_atom_defs = aromTypeDefTable->getNumEntries();

	for (std::size_t i = 0; i < r_size; i++) {
		const Atom& atom = ring->getAtom(i);

		unsigned int atomic_no = getType(atom);
		std::size_t atom_idx = molGraph->getAtomIndex(atom);

		const std::string& sym_type = (*symTypes)[atom_idx];
		std::size_t het_atom_dist = calcHeteroAtomDistance(r_size, het_atom_idx, i);
		bool found_entry = false;

		for (std::size_t j = 0; j < 2 && !found_entry; j++) { 
			for (std::size_t k = 0; k < num_arom_atom_defs && !found_entry; k++) {
				const AromTypeDefEntry& entry = aromTypeDefTable->getEntry(k);

				if (matchesAromTypeDefEntry(j != 0, sym_type, atomic_no, r_size, het_atom_dist, im_cation, n5_anion, entry)) {
					(*symTypes)[atom_idx] = entry.getAromAtomType();
					found_entry = true;
				}
			}
		}
	}
}

void ForceField::MMFF94AtomTyper::assignHydrogenAtomTypes()
{
	using namespace Chem;

	for (std::size_t i = 0, num_atoms = symTypes->size(); i < num_atoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		if (getType(atom) == AtomType::H)
			continue;

		const std::string& h_type = hydTypeMap->getEntry((*symTypes)[i]);

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

			if ((*symTypes)[nbr_idx].empty())
				(*symTypes)[nbr_idx] = h_type;
		}
	}
}

void ForceField::MMFF94AtomTyper::assignNumericAtomTypes(Util::UIArray& num_types)
{
	std::transform(symTypes->getElementsBegin(), symTypes->getElementsEnd(), num_types.getElementsBegin(), 
				   boost::bind(&MMFF94SymbolicToNumericAtomTypeMap::getEntry, boost::ref(numTypeMap), _1));
}

std::size_t ForceField::MMFF94AtomTyper::getUniqueHeteroAtomIndex(const Chem::Fragment& ring) const
{
	using namespace Chem;

	std::size_t r_size = ring.getNumAtoms();
	std::size_t het_idx = r_size;

	for (std::size_t i = 0; i < r_size; i++) {
		const std::string& sym_type = (*symTypes)[molGraph->getAtomIndex(ring.getAtom(i))];
		const MMFF94AtomTypePropertyTable::Entry& props = atomTypePropTable->getEntry(numTypeMap->getEntry(sym_type));

		if (!props || !props.hasPiLonePair())
			continue;

		if (het_idx != r_size)
			return r_size;

		het_idx = i;
	} 

	return het_idx;
}

bool ForceField::MMFF94AtomTyper::isN5Anion(const Chem::Fragment& ring) const
{
	using namespace Chem;

	if (ring.getNumAtoms() != 5)
		return false;

	for (Fragment::ConstAtomIterator it = ring.getAtomsBegin(), end = ring.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (getType(atom) == AtomType::N && getFormalCharge(atom) < 0)
			return true;
	} 

	return false;
}

bool ForceField::MMFF94AtomTyper::isImidazoliumCation(const Chem::Fragment& ring) const
{
	using namespace Chem;

	if (ring.getNumAtoms() != 5)
		return false;

	for (Fragment::ConstAtomIterator ra_it = ring.getAtomsBegin(), ra_end = ring.getAtomsEnd(); ra_it != ra_end; ++ra_it) {
		const Atom& atom = *ra_it;

		if (getType(atom) != AtomType::C)
			continue;

		if (getExplicitBondCount(atom, *molGraph) != 3)
			continue;

		bool found_n_db_c1 = false;
		bool found_n_sb_c0 = false;

		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
			const Bond& nbr_bond = *b_it;

			if (!molGraph->containsBond(nbr_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molGraph->containsAtom(nbr_atom))
				continue;

			if (getType(nbr_atom) != AtomType::N)
				continue;

			switch (getOrder(nbr_bond)) {

				case 1:
					if (getFormalCharge(nbr_atom) == 0)
						found_n_sb_c0  = true;
					
					break;

				case 2:
					if (getFormalCharge(nbr_atom) == 1 && getBondCount(nbr_atom, *molGraph, 1, AtomType::O) == 0)
						found_n_db_c1  = true;
					
				default:
					break;
			}
		}

		if (found_n_db_c1 && found_n_sb_c0)
			return true;
	} 

	return false;
}

std::size_t ForceField::MMFF94AtomTyper::calcHeteroAtomDistance(std::size_t r_size, std::size_t het_atom_idx, std::size_t from_atom_idx) const
{
	if (r_size == het_atom_idx)
		return r_size;

	if (from_atom_idx < het_atom_idx)
		return (std::min(het_atom_idx - from_atom_idx, r_size - het_atom_idx + from_atom_idx) + 1);

	return (std::min(from_atom_idx - het_atom_idx, r_size - from_atom_idx + het_atom_idx) + 1);
}
		
bool ForceField::MMFF94AtomTyper::matchesAromTypeDefEntry(bool wc_match, const std::string& sym_type, unsigned int atomic_no, std::size_t r_size, 
														  std::size_t het_dist, bool im_cat, bool n5_anion,
														  const AromTypeDefEntry& entry) const
{
	if (atomic_no != entry.getAtomicNumber())
		return false;

	if (r_size != entry.getRingSize())
		return false;

	std::size_t entry_het_dist = entry.getHeteroAtomDistance();

	if (entry_het_dist != 0 && entry_het_dist <= (r_size / 2 + 1) && het_dist != entry_het_dist)
		return false;

	if (r_size == 5 && !wc_match) {
		if (im_cat != entry.isImidazoliumCation())
			return false;

		if (n5_anion != entry.isN5RingAnion())
			return false;
	}

	if (!wc_match)
		return (sym_type == entry.getOldAtomType());

	std::string::size_type wc_pos = entry.getOldAtomType().find('*');

	if (wc_pos == std::string::npos)
		return false;

	std::string::size_type first_al_char = 0;

	while (!std::isalpha(sym_type[first_al_char], std::locale::classic()) && first_al_char < sym_type.size())
		first_al_char++;

	return (sym_type.find(entry.getOldAtomType().c_str(), first_al_char, wc_pos) == first_al_char);
}
