/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomClassificationFunctions.cpp 
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
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"


using namespace CDPL; 


bool Chem::isOrdinaryHydrogen(const Atom& atom, const MolecularGraph& molgraph, unsigned int flags)
{
    if (getType(atom) != AtomType::H)
		return false;
 
	if (flags == AtomPropertyFlag::DEFAULT)
		flags = AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT;

	bool first_bond = true;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;
		
		if (!first_bond)
			return false;

		if (getOrder(bond) != 1)
			return false;

		first_bond = false;
	}

	if (first_bond)
		return false;

    if ((flags & AtomPropertyFlag::ISOTOPE) && getIsotope(atom) > 1)
		return false;

    if ((flags & AtomPropertyFlag::FORMAL_CHARGE) && getFormalCharge(atom) != 0)
		return false;

    if ((flags & AtomPropertyFlag::H_COUNT) && getImplicitHydrogenCount(atom) != 0)
		return false;

    return true;
}

bool Chem::isHeavy(const Atom& atom)
{
    return (getType(atom) != AtomType::H);
}

bool Chem::isUnsaturated(const Atom& atom, const MolecularGraph& molgraph)
{
 	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;

		if (!molgraph.containsAtom(*a_it) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) > 1) 
			return true;
	}

	return false;
}

bool Chem::isHydrogenAcceptor(const Atom& atom, const MolecularGraph& molgraph)
{
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

bool Chem::isHydrogenDonor(const Atom& atom, const MolecularGraph& molgraph)
{
    unsigned int atom_type = getType(atom);

    if (atom_type != AtomType::O && atom_type != AtomType::N && atom_type != AtomType::S && atom_type != AtomType::P) 
		return false;

    if (getFormalCharge(atom) < 0)
		return false;

    return (getAtomCount(atom, molgraph, AtomType::H) > 0);
}

bool Chem::isCarbonylLikeAtom(const Atom& atom, const MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	unsigned int type = getType(atom);

	switch (type) {

		case AtomType::C:
			break;

		case AtomType::S:
		case AtomType::P:
			if (!c_only)
				break;

		default:
			return false;
	}

	if (getExplicitBondCount(atom, molgraph, 2, AtomType::O, true) > 0)
		return true;

	if (db_o_only)
		return false;

	if (type != AtomType::S && getExplicitBondCount(atom, molgraph, 2, AtomType::S, true) > 0)
		return true;

	return false;
}

bool Chem::isAmideCenterAtom(const Atom& atom, const MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	return (isCarbonylLikeAtom(atom, molgraph, c_only, db_o_only) && getExplicitBondCount(atom, molgraph, 1, AtomType::N, true) > 0);
}

bool Chem::isAmideNitrogen(const Atom& atom, const MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	if (getType(atom) != AtomType::N)
		return false;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) != 1)
			continue;

		if (isCarbonylLikeAtom(nbr_atom, molgraph, c_only, db_o_only))
			return true;
	}

	return false;
}

bool Chem::isInvertibleNitrogen(const Atom& atom, const MolecularGraph& molgraph)
{
	if (getType(atom) != AtomType::N)
		return false;

	std::size_t bond_count = 0;
	std::size_t ring_bond_count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) != 1)
			return false;

		if (getRingFlag(bond) && (++ring_bond_count > 2))
			return false;

		if (hasAromaticityFlag(nbr_atom) && getAromaticityFlag(nbr_atom))
			return false;

		if (hasHybridizationState(nbr_atom)) {
			switch (getHybridizationState(nbr_atom)) {

				case HybridizationState::SP2:
				case HybridizationState::SP:
					return false;

				default:
					break;
			}
		} 

		if (isUnsaturated(nbr_atom, molgraph))
			return false;

		bond_count++;
	}

	return ((bond_count + getImplicitHydrogenCount(atom)) == 3);
}

bool Chem::isPlanarNitrogen(const Atom& atom, const MolecularGraph& molgraph)
{
	if (getType(atom) != AtomType::N)
		return false;

	if (hasAromaticityFlag(atom) && getAromaticityFlag(atom))
		return true;

	std::size_t bond_count = 0;
	bool unsat_nbrs = false;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) > 1)
			return true;

		if (hasAromaticityFlag(nbr_atom) && getAromaticityFlag(nbr_atom)) {
			unsat_nbrs = true;

		} else if (hasHybridizationState(nbr_atom)) {
			switch (getHybridizationState(nbr_atom)) {

				case HybridizationState::SP2:
				case HybridizationState::SP:
					unsat_nbrs = true;
					break;

				default:
					if (isUnsaturated(nbr_atom, molgraph))
						unsat_nbrs = true;
					break;
			}

		} else if (isUnsaturated(nbr_atom, molgraph))
			unsat_nbrs = true;

		bond_count++;
	}

	if (getImplicitHydrogenCount(atom) + bond_count  > 3)
		return false;

	return unsat_nbrs;
}
