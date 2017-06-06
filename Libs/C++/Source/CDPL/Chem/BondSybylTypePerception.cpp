/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondSybylTypePerception.cpp 
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
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/SybylBondType.hpp"


using namespace CDPL; 


namespace
{

    bool isAmideBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph)
    {
		using namespace Chem;

		const Atom* c_atom = 0;
		const Atom* n_atom = 0;

		for (std::size_t i = 0; i < 2; i++) {

			switch (getType(bond.getAtom(i))) {

				case AtomType::C:
					c_atom = &bond.getAtom(i);
					break;

				case AtomType::N:
					n_atom = &bond.getAtom(i);
					break;

				default:
					return false;
			}
		}

		if (!c_atom || !n_atom)
			return false;

		if (getBondCount(*n_atom, molgraph) != 3)
			return false;

		if ((getBondCount(*n_atom, molgraph, 1, AtomType::C) + getBondCount(*n_atom, molgraph, 1, AtomType::H)) != 3)
			return false;

		if (getBondCount(*c_atom, molgraph) != 3)
			return false;

		if (getBondCount(*c_atom, molgraph, 1, AtomType::N) != 1)
			return false;

		if (getBondCount(*c_atom, molgraph, 2, AtomType::O) != 1)
			return false;

		if (getBondCount(*c_atom, molgraph, 1, AtomType::H) == 1 ||
			getBondCount(*c_atom, molgraph, 1, AtomType::C) == 1)
			return true;

		return false;
    }
}

	
unsigned int Chem::perceiveSybylType(const Bond& bond, const MolecularGraph& molgraph)
{
    if (getAromaticityFlag(bond))
		return SybylBondType::AROMATIC;

    switch (getOrder(bond)) {

		case 1:
			if (isAmideBond(bond, molgraph))
				return SybylBondType::AMIDE;

			return SybylBondType::SINGLE;

		case 2:
			return SybylBondType::DOUBLE;

		case 3:
			return SybylBondType::TRIPLE;

    }

    return SybylBondType::UNKNOWN;
}
