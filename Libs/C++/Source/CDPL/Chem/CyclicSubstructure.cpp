/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CyclicSubstructure.cpp 
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

#include "CDPL/Chem/CyclicSubstructure.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL;


Chem::CyclicSubstructure::CyclicSubstructure(const MolecularGraph& molgraph)
{
	perceive(molgraph);
}

void Chem::CyclicSubstructure::perceive(const MolecularGraph& molgraph)
{
	clear();

	if (molgraph.getNumAtoms() == 0 || molgraph.getNumBonds() == 0)
		return;

	init(molgraph);
	findRingAtomsAndBonds();
}

void Chem::CyclicSubstructure::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;
	
	visAtomMask.resize(molgraph.getNumAtoms());
	visAtomMask.reset();
	pathAtomMask.resize(molgraph.getNumAtoms());
	pathAtomMask.reset();

	atomStack.clear();
	bondStack.clear();
}

void Chem::CyclicSubstructure::findRingAtomsAndBonds()
{
	std::size_t num_atoms = molGraph->getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++) {
		if (!visAtomMask.test(i))
			findRingAtomsAndBonds(&molGraph->getAtom(i));
	}
}

void Chem::CyclicSubstructure::findRingAtomsAndBonds(const Atom* atom)
{
	std::size_t atom_idx = molGraph->getAtomIndex(*atom);

	if (pathAtomMask.test(atom_idx)) {
		BondStack::const_reverse_iterator b_it = bondStack.rbegin();
		AtomStack::const_reverse_iterator a_it = atomStack.rbegin();

		while (true) {
			const Atom* rng_atom = *a_it;
			const Bond* rng_bond = *b_it;

			addAtom(*rng_atom);
			addBond(*rng_bond);

			if (rng_atom == atom)
				return;

			++a_it;
			++b_it;
		}

		return;
	}

	if (visAtomMask.test(atom_idx))
		return;
	
	atomStack.push_back(atom);
	visAtomMask.set(atom_idx);
	pathAtomMask.set(atom_idx);

	const Bond* prev_bond = (bondStack.empty() ? 0 : bondStack.back());
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(), a_end = atom->getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& nbr_bond = *b_it;

		if (&nbr_bond == prev_bond || !molGraph->containsBond(nbr_bond))
			continue;

		const Atom& nbr_atom = *a_it;
	
		if (!molGraph->containsAtom(nbr_atom))
			continue;

		bondStack.push_back(&nbr_bond);

		findRingAtomsAndBonds(&nbr_atom);

		bondStack.pop_back();
	}

	atomStack.pop_back();
	pathAtomMask.reset(atom_idx);
}

