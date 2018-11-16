/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomStereoCenterFlagFunction.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/HybridizationState.hpp"


using namespace CDPL; 


bool Chem::isStereoCenter(const Atom& atom, const MolecularGraph& molgraph, bool check_cip_sym)
{
	if (getAromaticityFlag(atom))
		return false;

    if (getHybridizationState(atom) != HybridizationState::SP3)
		return false;

	std::size_t num_bonds = getExplicitBondCount(atom, molgraph);

    if (num_bonds < 3 || num_bonds > 4)
		return false;

	if ((num_bonds + getImplicitHydrogenCount(atom)) > 4)
		return false;

	if (getOrdinaryHydrogenCount(atom, molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT) > 1)
	    return false;

	if (isPlanarNitrogen(atom, molgraph))
		return false;

	if (!check_cip_sym)
		return true;

    std::size_t cip_priorities[4];

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	num_bonds = 0;

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
			cip_priorities[num_bonds] = getCIPPriority(*a_it);

			for (std::size_t j = 0; j < num_bonds; j++)
				if (cip_priorities[j] == cip_priorities[num_bonds])
					return false;

			num_bonds++;
		}
    }

    return true;
}
