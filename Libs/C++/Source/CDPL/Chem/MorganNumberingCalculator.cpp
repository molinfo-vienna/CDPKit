/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MorganNumberingGenerator.cpp 
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

#include <iterator>
#include <functional>
#include <algorithm>
#include <map>
#include <cstdint>

#include <boost/bind.hpp>

#include "CDPL/Chem/MorganNumberingCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL;


namespace
{

	class SymClassCountPred
	{

	public:
		SymClassCountPred(): currEC(~std::uint64_t(0)) {}

		bool operator()(std::uint64_t ec) {
			if (ec != currEC) {
				currEC = ec;
				return true;
			}

			return false;
		}
		 
	private:
		std::uint64_t currEC;
	};
}


Chem::MorganNumberingCalculator::MorganNumberingCalculator(): 
	numbering(&symClassIDs, &atomSymbols, &atomCharges, &atomIsotopes, &bondMatrix) {}

Chem::MorganNumberingCalculator::MorganNumberingCalculator(const MolecularGraph& molgraph, Util::STArray& output): 
	numbering(&symClassIDs, &atomSymbols, &atomCharges, &atomIsotopes, &bondMatrix)
{
	numbering.calculate(molgraph, output);
}

void Chem::MorganNumberingCalculator::calculate(const MolecularGraph& molgraph, Util::STArray& output) 
{
	numbering.calculate(molgraph, output);
}

void Chem::MorganNumberingCalculator::NumberingState::calculate(const MolecularGraph& molgraph, Util::STArray& output) 
{
	init(molgraph);

	perceiveSymClasses();
	distributeNumbers(output);
}

void Chem::MorganNumberingCalculator::NumberingState::init(const MolecularGraph& molgraph) 
{
	centerAtomNumber = 1;
	nextAtomNumber   = 1;
	sortRCList       = false;
	molGraph         = &molgraph; 
	
	buildBondMatrix(molgraph, *bondMatrix);
	
	indexLookupTable.clear();
	atomNumbering.clear();
	ringClosures.clear();
	fromList.clear();
	lineValues.clear();
	nodeValues.clear();
	modifications.clear();
}

void Chem::MorganNumberingCalculator::NumberingState::perceiveSymClasses()
{
	std::size_t num_atoms = molGraph->getNumAtoms();

	atomSymbols->reserve(num_atoms);
	atomCharges->reserve(num_atoms);
	atomIsotopes->reserve(num_atoms);

	MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();
	MolecularGraph::ConstAtomIterator atoms_beg = molGraph->getAtomsBegin();

	typedef std::vector<std::uint64_t> UI64Array; 

	UI64Array ec_values;

	for (MolecularGraph::ConstAtomIterator it = atoms_beg; it != atoms_end; ++it) {
		const Atom& atom = *it;
 
		ec_values.push_back(Internal::getExplicitBondCount(atom, *molGraph));

		atomSymbols->push_back(getSymbol(atom));
		atomCharges->push_back(getFormalCharge(atom));
		atomIsotopes->push_back(getIsotope(atom));
	}

	std::size_t num_classes = 0;

	UI64Array new_ec_values(num_atoms);

	while (true) {
		UI64Array::iterator it1 = new_ec_values.begin();

		for (MolecularGraph::ConstAtomIterator it2 = atoms_beg; it2 != atoms_end; ++it1, ++it2) {
			std::uint64_t new_ec_value = 0;

			const Atom& atom = *it2;
			Atom::ConstAtomIterator nbrs_end = atom.getAtomsEnd();
			Atom::ConstBondIterator b_it = atom.getBondsBegin();
			
			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbrs_end; ++a_it, ++b_it) {
				if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
					continue;

				new_ec_value += ec_values[molGraph->getAtomIndex(*a_it)];
			}

			*it1 = new_ec_value;
		}

		ec_values = new_ec_values;
		std::sort(new_ec_values.begin(), new_ec_values.end()); 

		std::size_t num_new_classes = std::count_if(new_ec_values.begin(), new_ec_values.end(), SymClassCountPred());

		if (num_new_classes <= num_classes)
			break;

		num_classes = num_new_classes;
	}

	std::map<std::uint64_t, std::size_t> ec_to_sym_class_id_map;
	std::uint64_t last_ec_value = ~std::uint64_t(0);
	std::size_t last_sym_class_id = 0;

	for (UI64Array::const_iterator it = new_ec_values.begin(), end = new_ec_values.end(); it != end; ++it) {
		std::uint64_t ec_value = *it;

		if (last_ec_value != ec_value) {
			ec_to_sym_class_id_map[ec_value] = ++last_sym_class_id;
			last_ec_value = ec_value;
		}
	}

	atomNumbering.reserve(num_atoms);
	symClassIDs->reserve(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++) {
		std::size_t sym_class_id = ec_to_sym_class_id_map[ec_values[i]];

		atomNumbering.push_back(STPair(sym_class_id, 0));
		symClassIDs->push_back(STPair(sym_class_id, i));
	}

	std::sort(symClassIDs->begin(), symClassIDs->end(), boost::bind(std::greater<std::size_t>(), 
																	boost::bind(&STPair::first, _1),
																	boost::bind(&STPair::first, _2)));
	lastSymClass = symClassIDs->begin();
}

void Chem::MorganNumberingCalculator::NumberingState::distributeNumbers(Util::STArray& output)
{
	STArray atom_indices;	

	NumberingState saved_state;
	NumberingState test_state;

	getNextAtomIndices(atom_indices);

	while (!atom_indices.empty()) {
		STArray::const_iterator it = atom_indices.begin();
		std::size_t atom_idx = *it;

		if (atom_indices.size() > 1) {
			saved_state = *this;
			STArray::const_iterator indices_end = atom_indices.end();

			addListEntriesForAtom(atom_idx, atom_idx);
			distributeNumbers(atom_idx);

			// Find best choice out of equiv. atoms

			for (++it; it != indices_end; ++it) { 
 				test_state = saved_state;

				test_state.addListEntriesForAtom(*it, *it);
				test_state.distributeNumbers(*it);

				copy(test_state);
			}

		} else {
			addListEntriesForAtom(atom_idx, atom_idx);
			distributeNumbers(atom_idx);
		}

		atom_indices.clear();
		getNextAtomIndices(atom_indices);
	}

	output.clear();
	output.reserve(molGraph->getNumAtoms());

	std::for_each(atomNumbering.begin(), atomNumbering.end(), boost::bind(&Util::STArray::addElement, 
																		  boost::ref(output),
																		  boost::bind(&STPair::second, _1)));
}

void Chem::MorganNumberingCalculator::NumberingState::distributeNumbers(std::size_t atom_idx)
{
	// Extract not numbered connected atoms and detect ring closures

	const Atom& atom = molGraph->getAtom(atom_idx);
	Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	STPairArray not_numbered_nbrs;

	for (Atom::ConstAtomIterator it = atom.getAtomsBegin(); it != nbr_atoms_end; ++it, ++b_it) {
		if (!molGraph->containsAtom(*it) || !molGraph->containsBond(*b_it))
			continue;

		std::size_t nbr_atom_idx = molGraph->getAtomIndex(*it);
		std::size_t nbr_atom_number = atomNumbering[nbr_atom_idx].second;

		if (nbr_atom_number == 0) 
			not_numbered_nbrs.push_back(STPair(atomNumbering[nbr_atom_idx].first, nbr_atom_idx));

		else if (nbr_atom_number != fromList[centerAtomNumber - 1]) {
			ringClosures.push_back(std::min(nbr_atom_number, centerAtomNumber) << (sizeof(std::size_t) * 4) 
								   | std::max(nbr_atom_number, centerAtomNumber));
			sortRCList = true;
		} 
	}

	std::size_t num_not_numbered_nbrs = not_numbered_nbrs.size();

	if (num_not_numbered_nbrs == 0) {
		if (centerAtomNumber < indexLookupTable.size()) 
			distributeNumbers(indexLookupTable[centerAtomNumber++]);

		return;
	}

	std::sort(not_numbered_nbrs.begin(), not_numbered_nbrs.end(), boost::bind(std::greater<std::size_t>(), 
																			  boost::bind(&STPair::first, _1),
																			  boost::bind(&STPair::first, _2)));
	// Create all possible permutations if more than one neighbor 
	// belongs to the same symmetry class

	STArray nbr_perms;

	std::transform(not_numbered_nbrs.begin(), not_numbered_nbrs.end(), std::back_inserter(nbr_perms), 
				   boost::bind(&STPair::second, _1));

	std::size_t num_perms = 1;

	for (std::size_t i = 0; i < num_not_numbered_nbrs; ) {
		std::size_t eq_range_sym_class_id = not_numbered_nbrs[i].first;
		std::size_t eq_range_start = i;

		for (i++; i < num_not_numbered_nbrs && eq_range_sym_class_id == not_numbered_nbrs[i].first; i++);
		
		std::size_t eq_range_len = i - eq_range_start;

		if (eq_range_len < 2)
			continue;

		std::size_t num_range_perms = Math::factorial<std::size_t>(eq_range_len);

		nbr_perms.reserve(num_range_perms * nbr_perms.size());

		STArray::const_iterator nbr_perms_beg = nbr_perms.begin();
		STArray::const_iterator nbr_perms_end = nbr_perms.end();		
		
		for (std::size_t j = 1; j < num_range_perms; j++) {
			std::copy(nbr_perms_beg, nbr_perms_end, std::back_inserter(nbr_perms));

			std::size_t perm_idx1 = eq_range_start;
			std::size_t perm_idx2 = eq_range_start + eq_range_len;

			for (std::size_t k = 0; k < num_perms; k++, perm_idx1 += num_not_numbered_nbrs, perm_idx2 += num_not_numbered_nbrs)
				std::next_permutation(&nbr_perms[perm_idx1], &nbr_perms[perm_idx2]);
		}

		num_perms *= num_range_perms;
	}

	// Number neighbor atoms starting with 'nextAtomNumber'
	// and then continue with the next layer
 
	STArray::const_iterator nbr_perms_end = nbr_perms.end();
	STArray::const_iterator it = nbr_perms.begin();

	if (num_perms > 1) {
		NumberingState saved_state(*this);

		for (std::size_t i = 0; i < num_not_numbered_nbrs; i++, ++it) 
			addListEntriesForAtom(atom_idx, *it);

		distributeNumbers(indexLookupTable[centerAtomNumber++]);

		NumberingState test_state;

		for (std::size_t i = 1; i < num_perms; i++) {
			test_state = saved_state;

			for (std::size_t k = 0; k < num_not_numbered_nbrs; k++, ++it) 
				test_state.addListEntriesForAtom(atom_idx, *it);

			test_state.distributeNumbers(test_state.indexLookupTable[test_state.centerAtomNumber++]);

			copy(test_state);
		}

	} else {
		for ( ; it != nbr_perms_end; ++it) 
			addListEntriesForAtom(atom_idx, *it);

		distributeNumbers(indexLookupTable[centerAtomNumber++]);
	}
}

void Chem::MorganNumberingCalculator::NumberingState::getNextAtomIndices(STArray& indices)
{
	STPairArrayIterator table_end = symClassIDs->end();

	for ( ; lastSymClass != table_end; ++lastSymClass) {
		std::size_t atom_idx = lastSymClass->second;

		if (atomNumbering[atom_idx].second == 0) {
			indices.push_back(atom_idx);
			break;
		}
	}

	if (lastSymClass == table_end)
		return;

	std::size_t sym_class_id = lastSymClass->first;

	// Get indices of not numbered equiv. atoms

	for (STPairArrayIterator it = lastSymClass + 1; it != table_end && sym_class_id == it->first; ++it) {
		std::size_t atom_idx = it->second;

		if (atomNumbering[atom_idx].second == 0) 
			indices.push_back(atom_idx);
	}
}

void Chem::MorganNumberingCalculator::NumberingState::addListEntriesForAtom(std::size_t from_idx, std::size_t atom_idx)
{
	fromList.push_back(from_idx == atom_idx ? 0 : centerAtomNumber);

	lineValues.push_back((*bondMatrix)(from_idx, atom_idx));

	nodeValues.append((*atomSymbols)[atom_idx]); 

	modifications.push_back((*atomCharges)[atom_idx]);
	modifications.push_back((*atomIsotopes)[atom_idx]);

	indexLookupTable.push_back(atom_idx);
	atomNumbering[atom_idx].second = nextAtomNumber++;
}

void Chem::MorganNumberingCalculator::NumberingState::copy(NumberingState& state)
{
	if (std::lexicographical_compare(state.fromList.begin(), state.fromList.end(),
									 fromList.begin(), fromList.end())) {
		operator=(state);
		return;
	}

	if (std::lexicographical_compare(fromList.begin(), fromList.end(),
									 state.fromList.begin(), state.fromList.end()))
		return; // state's fromList sorts higher

	if (sortRCList) {
		std::sort(ringClosures.begin(), ringClosures.end()); 
		sortRCList = false;
	}

	if (state.sortRCList) {
		std::sort(state.ringClosures.begin(), state.ringClosures.end()); 
		state.sortRCList = false;
	}

	if (std::lexicographical_compare(state.ringClosures.begin(), state.ringClosures.end(),
									 ringClosures.begin(), ringClosures.end())) {
		operator=(state);
		return;
	}

	if (std::lexicographical_compare(ringClosures.begin(), ringClosures.end(),
									 state.ringClosures.begin(), state.ringClosures.end()))
		return;

	if (std::lexicographical_compare(state.nodeValues.begin(), state.nodeValues.end(),
									 nodeValues.begin(), nodeValues.end())) {
		operator=(state);
		return;
	}

	if (std::lexicographical_compare(nodeValues.begin(), nodeValues.end(),
									 state.nodeValues.begin(), state.nodeValues.end()))
		return;

	if (std::lexicographical_compare(state.lineValues.begin(), state.lineValues.end(),
									 lineValues.begin(), lineValues.end())) {
		operator=(state);
		return;
	}

	if (std::lexicographical_compare(lineValues.begin(), lineValues.end(),
									 state.lineValues.begin(), state.lineValues.end()))
		return;

	if (std::lexicographical_compare(state.modifications.begin(), state.modifications.end(),
									 modifications.begin(), modifications.end())) 
		operator=(state);
}

