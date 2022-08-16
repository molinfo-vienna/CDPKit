/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphZagrebIndexFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


std::size_t Descr::calcZagrebIndex1(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	Util::BitSet h_mask(molgraph.getNumAtoms());
	buildAtomTypeMask(molgraph, h_mask, AtomType::H);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	std::size_t index1 = 0;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;

		if (h_mask.test(molgraph.getAtomIndex(atom)))
			continue;

		std::size_t hvy_bond_count = 0;

		Atom::ConstBondIterator nbr_bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator nbr_a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator nbr_b_it = atom.getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++nbr_a_it) {
			const Atom& nbr_atom= *nbr_a_it;

			if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*nbr_b_it))
				continue;

			if (!h_mask.test(molgraph.getAtomIndex(nbr_atom)))
				hvy_bond_count++;
		}

		index1 += hvy_bond_count * hvy_bond_count;
	}

	return index1;
}

std::size_t Descr::calcZagrebIndex2(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	Util::BitSet h_mask(molgraph.getNumAtoms());
	buildAtomTypeMask(molgraph, h_mask, AtomType::H);

	std::size_t index2 = 0;

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
		const Atom* atoms[2] = { &bond.getBegin(), &bond.getEnd() };

		if (!molgraph.containsAtom(*atoms[0]) || !molgraph.containsAtom(*atoms[1]))
			continue;

		if (h_mask.test(molgraph.getAtomIndex(*atoms[0])) || h_mask.test(molgraph.getAtomIndex(*atoms[1])))
			continue;

		std::size_t bond_counts[2] = { 0, 0 };

		for (std::size_t i = 0; i < 2; i++) {
			Atom::ConstBondIterator nbr_bonds_end = atoms[i]->getBondsEnd();
			Atom::ConstAtomIterator nbr_a_it = atoms[i]->getAtomsBegin();

			for (Atom::ConstBondIterator nbr_b_it = atoms[i]->getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++nbr_a_it) {
				const Atom& nbr_atom= *nbr_a_it;

				if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*nbr_b_it))
					continue;

				if (!h_mask.test(molgraph.getAtomIndex(nbr_atom)))
					bond_counts[i]++;
			}
		}

		index2 += bond_counts[0] * bond_counts[1];
	}

	return index2;
}
