/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomClassificationFunctions.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


bool MolProp::isOrdinaryHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	return Internal::isOrdinaryHydrogen(atom, molgraph, flags);
}

bool MolProp::isHeavy(const Chem::Atom& atom)
{
    return (getType(atom) != Chem::AtomType::H);
}

bool MolProp::isUnsaturated(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::isUnsaturated(atom, molgraph);
}

bool MolProp::isHBondAcceptor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
		
    if (getFormalCharge(atom) > 0)
		return false;

    unsigned int atom_type = getType(atom);
    std::size_t valence = calcValence(atom, molgraph);

    switch (atom_type) {

		case AtomType::P: 
		case AtomType::N:
	    	if (valence > 3 || valence == 0)
	     	   return false;
	    	break;

		case AtomType::O:
		case AtomType::S:
	    	if (valence > 2 || valence == 0)
				return false;
	    	break;

		default:
	    	return false;
    }

    if (getAromaticityFlag(atom)) {
		if (atom_type == AtomType::O || atom_type == AtomType::S || atom_type == AtomType::P)
			return false;

		if (getBondCount(atom, molgraph) == 3) // Pyrrole-like N
			return false;
    }

    return true;
}

bool MolProp::isHBondDonor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
    unsigned int atom_type = getType(atom);

    if (atom_type != AtomType::O && atom_type != AtomType::N && atom_type != AtomType::S && atom_type != AtomType::P) 
		return false;

    if (getFormalCharge(atom) < 0)
		return false;

    return (getAtomCount(atom, molgraph, AtomType::H) > 0);
}

bool MolProp::isCarbonylLikeAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	return Internal::isCarbonylLikeAtom(atom, molgraph, c_only, db_o_only);
}

bool MolProp::isAmideCenterAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	return (isCarbonylLikeAtom(atom, molgraph, c_only, db_o_only) && getExplicitBondCount(atom, molgraph, 1, Chem::AtomType::N, true) > 0);
}

bool MolProp::isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	return Internal::isAmideNitrogen(atom, molgraph, c_only, db_o_only);
}

bool MolProp::isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::isInvertibleNitrogen(atom, molgraph);
}

bool MolProp::isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::isPlanarNitrogen(atom, molgraph);
}
