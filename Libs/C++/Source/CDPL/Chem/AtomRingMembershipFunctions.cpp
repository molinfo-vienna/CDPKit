/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomRingMembershipFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


namespace
{

    bool checkIsInRingOfSize(const Chem::Atom& start_atom, const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
							 std::size_t size, Util::BitSet& vis_atoms, std::size_t path_len)
    {
		using namespace Chem;

		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		vis_atoms.set(atom_idx);
		path_len++;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator it = atom.getAtomsBegin(), end = atom.getAtomsEnd(); it != end; ++it, ++b_it) {
			const Atom& nbr_atom = *it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			if (!molgraph.containsBond(*b_it))
				continue;

			if (vis_atoms.test(molgraph.getAtomIndex(nbr_atom))) {
				if (&nbr_atom == &start_atom && path_len == size)
					return true;

				continue;
			}

			if (nbr_atom.getNumAtoms() < 2)
				continue;

			if (path_len < size) 
				if (checkIsInRingOfSize(start_atom, nbr_atom, molgraph, size, vis_atoms, path_len))
					return true;
		}

		path_len--;
		vis_atoms.reset(atom_idx);

		return false;
    }

    bool checkIsInRing(const Chem::Atom& start_atom, const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Util::BitSet& vis_atoms, std::size_t path_len)
    {
		using namespace Chem;

		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		vis_atoms.set(atom_idx);
		path_len++;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator it = atom.getAtomsBegin(), end = atom.getAtomsEnd(); it != end; ++it, ++b_it) {
			const Chem::Atom& nbr_atom = *it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			if (!molgraph.containsBond(*b_it))
				continue;

			if (vis_atoms.test(molgraph.getAtomIndex(nbr_atom))) { 
				if (&nbr_atom == &start_atom && path_len > 2)
					return true;

				continue;
			}

			if (nbr_atom.getNumAtoms() < 2)
				continue;

			if (checkIsInRing(start_atom, nbr_atom, molgraph, vis_atoms, path_len))
				return true;
		}

		path_len--;
		vis_atoms.reset(atom_idx);

		return false;
    }
}


bool Chem::isInRing(const Atom& atom, const MolecularGraph& molgraph)
{
    if (atom.getNumAtoms() < 2)
		return false;

    Util::BitSet vis_atoms(molgraph.getNumAtoms());

    return checkIsInRing(atom, atom, molgraph, vis_atoms, 0);
}

bool Chem::isInRingOfSize(const Atom& atom, const MolecularGraph& molgraph, std::size_t size)
{
    if (size < 3)
		return false;

    if (atom.getNumAtoms() < 2)
		return false;

    Util::BitSet vis_atoms(molgraph.getNumAtoms());

    return checkIsInRingOfSize(atom, atom, molgraph, size, vis_atoms, 0);
}

std::size_t Chem::getNumContainingSSSRRings(const Atom& atom, const MolecularGraph& molgraph)
{
	return getNumContainingFragments(atom, *getSSSR(molgraph));
}
