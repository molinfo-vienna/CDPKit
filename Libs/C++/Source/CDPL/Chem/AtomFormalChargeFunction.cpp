/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFormalChargeFunction.cpp 
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

#include <cmath>

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


long Chem::calcFormalCharge(const Atom& atom, const MolecularGraph& molgraph)
{
	unsigned int atom_type = getType(atom);
	long valence = Internal::calcValence(atom, molgraph) + getUnpairedElectronCount(atom);

	if ((atom_type == AtomType::C || atom_type == AtomType::N) && getImplicitHydrogenCount(atom) == 0) {
		switch (Internal::getExplicitBondCount(atom, molgraph)) {

			case 1:
				if ((atom_type == AtomType::C && valence == 3) || (atom_type == AtomType::N && valence == 2))
					return -1;
                break;

			case 2:
				if (atom_type == AtomType::N && valence == 2)
					return -1;

			default:
				break;
		}
	}

	const Util::STArray& val_states = AtomDictionary::getValenceStates(atom_type);
	long nearest_val_state = -1;

	for (std::size_t i = 0; i < val_states.getSize(); i++)
		if (i == 0 || (std::abs(long(val_states[i]) - valence) < std::abs(nearest_val_state - valence)))
			nearest_val_state = val_states[i];

	if (nearest_val_state == -1)
		return 0;

	switch (AtomDictionary::getIUPACGroup(atom_type)) {
		
		case 1: 
		case 2:
		case 13:
		case 14:
			return (nearest_val_state - valence);

		case 15:
		case 16:
		case 17: 
			return (valence - nearest_val_state);

		default:
			return 0;
	}
}
