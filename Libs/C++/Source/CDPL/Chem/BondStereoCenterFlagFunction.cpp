/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondStereoCenterFlagFunction.cpp 
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

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/HybridizationState.hpp"


using namespace CDPL; 


bool Chem::isStereoCenter(const Bond& bond, const MolecularGraph& molgraph, std::size_t min_ring_size, bool check_cip_sym)
{
    if (getOrder(bond) != 2)
		return false;

	if (getAromaticityFlag(bond))
		return false;

	if (min_ring_size > 0) {
		std::size_t smallest_rsize = getSizeOfSmallestContainingFragment(bond, *getSSSR(molgraph));

		if (smallest_rsize > 0 && smallest_rsize < min_ring_size)
			return false;
	}

    const Atom* bond_atoms[2] = { &bond.getBegin(), &bond.getEnd() };

    for (std::size_t i = 0; i < 2; i++) {
		std::size_t num_bonds = getExplicitBondCount(*bond_atoms[i], molgraph);

		if (num_bonds < 2 || num_bonds > 3)
			return false;

		if (getHybridizationState(*bond_atoms[i]) != HybridizationState::SP2)
			return false;

		if ((num_bonds + getImplicitHydrogenCount(*bond_atoms[i])) > 3)
			return false;

		if (getOrdinaryHydrogenCount(*bond_atoms[i], molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT) > 1)
			return false;

		if (!check_cip_sym)
			continue;

		Atom::ConstAtomIterator atoms_end = bond_atoms[i]->getAtomsEnd();
		Atom::ConstBondIterator b_it = bond_atoms[i]->getBondsBegin();
		std::size_t first_cip_pri = 0;
		bool have_first_nbr = false;

		for (Atom::ConstAtomIterator a_it = bond_atoms[i]->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
			const Bond& nbr_bond = *b_it;

			if (&nbr_bond == &bond)
				continue;

			if (!molgraph.containsBond(nbr_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			std::size_t cip_pri = getCIPPriority(nbr_atom);

			if (!have_first_nbr) {
				have_first_nbr = true;
				first_cip_pri = cip_pri;
			
			} else if (cip_pri == first_cip_pri)
				return false;
		}
    }

    return true;
}
