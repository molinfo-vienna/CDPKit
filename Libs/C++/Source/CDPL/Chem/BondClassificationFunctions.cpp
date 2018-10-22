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


namespace
{

	bool isCarbonylCarbon(const Chem::Atom& atom, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph)
	{
		using namespace Chem;

		Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
			const Bond& att_bond = *b_it;

			if (&att_bond == &bond)
				continue;

			if (!molgraph.containsBond(att_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			if (getType(nbr_atom) != AtomType::O)
				continue;

			if (getOrder(att_bond) == 2)
				return true;	
		}

		return false;
	}

	bool isAmideBond(const Chem::Bond& bond, const Chem::Atom& atom1, const Chem::Atom& atom2, std::size_t bond_count1, 
					 std::size_t bond_count2, const Chem::MolecularGraph& molgraph)
	{
		using namespace Chem;

		unsigned int atom_type1 = getType(atom1);

		if (atom_type1 != AtomType::C && atom_type1 != AtomType::N)
			return false;

		unsigned int atom_type2 = getType(atom2);

		if (bond_count1 == 3 && atom_type1 == AtomType::C && atom_type2 == AtomType::N) 
			return isCarbonylCarbon(atom1, bond, molgraph);

		if (bond_count2 == 3 && atom_type1 == AtomType::N && atom_type2 == AtomType::C) 
			return isCarbonylCarbon(atom2, bond, molgraph);

		return true;
	}
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

	std::size_t bond_count1 = getBondCount(atom1, molgraph);

	if (bond_count1 < 2 ) 
		return false;
		
	std::size_t bond_count2 = getBondCount(atom2, molgraph);

	if (bond_count2 < 2)
		return false;

	if (!h_rotors && (getHeavyBondCount(atom1, molgraph) < 2 || getHeavyBondCount(atom2, molgraph) < 2))
		return false;

	if (amide_bonds)
		return true;

	return !isAmideBond(bond, atom1, atom2, bond_count1, bond_count2, molgraph); 
}
 
bool Chem::isHydrogenBond(const Bond& bond)
{
	return (getType(bond.getBegin()) == AtomType::H || getType(bond.getEnd()) == AtomType::H);
}
 
