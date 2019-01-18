/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondClassificationFunction.cpp 
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
#include "CDPL/Chem/BondContainerFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


bool Chem::isAmideBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	using namespace Chem;

	if (getOrder(bond) != 1)
		return false;

	const Atom& atom1 = bond.getBegin();
	const Atom& atom2 = bond.getEnd();

	if (getType(atom1) == AtomType::N)
		return isCarbonylLikeAtom(atom2, molgraph, c_only, db_o_only);

	if (getType(atom2) == AtomType::N)
		return isCarbonylLikeAtom(atom1, molgraph, c_only, db_o_only);

	return false;
}

bool Chem::isHydrogenRotor(const Bond& bond, const MolecularGraph& molgraph)
{
	if (getOrder(bond) != 1)
		return false;

	const Atom& atom1 = bond.getBegin();
	const Atom& atom2 = bond.getEnd();

	if (getBondCount(atom1, molgraph) < 2 ) 
		return false;

	if (getBondCount(atom2, molgraph) < 2)
		return false;

	return (getHeavyBondCount(atom1, molgraph) < 2 || getHeavyBondCount(atom2, molgraph) < 2);
}

bool Chem::isRotatable(const Bond& bond, const MolecularGraph& molgraph, bool h_rotors, bool ring_bonds, bool amide_bonds)
{
    if (getOrder(bond) != 1)
		return false;

	if (ring_bonds) {
		if (getAromaticityFlag(bond))
			return false;

	} else if (getRingFlag(bond))
		return false;

    const Atom& atom1 = bond.getBegin();
	const Atom& atom2 = bond.getEnd();

	if (getBondCount(atom1, molgraph) < 2 ) 
		return false;

	if (getBondCount(atom2, molgraph) < 2)
		return false;

	if (!h_rotors && (getHeavyBondCount(atom1, molgraph) < 2 || getHeavyBondCount(atom2, molgraph) < 2))
		return false;

	if (amide_bonds)
		return true;

	return !isAmideBond(bond, molgraph, true, true); 
}
 
bool Chem::isHydrogenBond(const Bond& bond)
{
	return (getType(bond.getBegin()) == AtomType::H || getType(bond.getEnd()) == AtomType::H);
}
 
