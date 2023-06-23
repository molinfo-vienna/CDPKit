/* 
 * MolecularGraphTotalWalkCountFunction.cpp 
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

#include <numeric>
#include <vector>

#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


std::size_t Descr::calcTotalWalkCount(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	typedef std::vector<std::size_t> ECValueArray;

	std::size_t num_atoms = molgraph.getNumAtoms();

	ECValueArray ec_values(num_atoms);
	ECValueArray new_ec_values(num_atoms);

	std::size_t num_graph_atoms = 0;

	MolecularGraph::ConstAtomIterator atoms_beg = molgraph.getAtomsBegin();
	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = atoms_beg; it != atoms_end; ++it) {
		const Atom& atom = *it;
		unsigned int atom_type = getType(atom);

		if (atom_type == AtomType::H)
			continue;

		ec_values[molgraph.getAtomIndex(atom)] = 1;
		num_graph_atoms++;
	}

    std::size_t twc = 0;

	for (std::size_t i = 1; i < num_graph_atoms; i++) {
		for (MolecularGraph::ConstAtomIterator it = atoms_beg; it != atoms_end; ++it) {
			const Atom& atom = *it;
			std::size_t atom_idx = molgraph.getAtomIndex(atom);

			if (ec_values[atom_idx] == 0)
				continue;

			new_ec_values[atom_idx] = 0;

			Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
			Atom::ConstBondIterator nbr_b_it = atom.getBondsBegin();

			for (Atom::ConstAtomIterator nbr_a_it = atom.getAtomsBegin(); nbr_a_it != nbr_atoms_end; ++nbr_a_it, ++nbr_b_it) {
				if (!molgraph.containsBond(*nbr_b_it))
					continue;

				const Atom& nbr_atom = *nbr_a_it;

				if (!molgraph.containsAtom(nbr_atom))
					continue;

				std::size_t nbr_atom_idx = molgraph.getAtomIndex(nbr_atom);

				new_ec_values[atom_idx] += ec_values[nbr_atom_idx];
			}
		}

		ec_values.swap(new_ec_values);

		twc = std::accumulate(ec_values.begin(), ec_values.end(), twc);
	}

	return twc;
}
