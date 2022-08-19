/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomBondCountFunctions.cpp 
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
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


std::size_t Chem::getExplicitBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
	if (&atom.getMolecule() == &molgraph)
		return atom.getNumAtoms();

	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it))
			count++;

	return count;
}

std::size_t Chem::getBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
    return (getExplicitBondCount(atom, molgraph) + getImplicitHydrogenCount(atom));
}

std::size_t Chem::getExplicitBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order)
{
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getOrder(*b_it) == order)
			count++;

	return count;
}

std::size_t Chem::getBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order)
{
	std::size_t count = getExplicitBondCount(atom, molgraph, order);

    if (order == 1)
		count += getImplicitHydrogenCount(atom);

    return count;
}

std::size_t Chem::getExplicitBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict)
{
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) &&
			getOrder(*b_it) == order && (strict ? type == getType(*a_it) : atomTypesMatch(type, getType(*a_it))))
			count++;

    return count;
}

std::size_t Chem::getBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict)
{
    std::size_t count = getExplicitBondCount(atom, molgraph, order, type, strict);
 
    if (order == 1 && (strict ? type == AtomType::H : atomTypesMatch(type, AtomType::H)))
		count += getImplicitHydrogenCount(atom);

    return count;
}

std::size_t Chem::getExplicitChainBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
    std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && !getRingFlag(*b_it))
			count++;

    return count;
}

std::size_t Chem::getChainBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
	return (getExplicitChainBondCount(atom, molgraph) + getImplicitHydrogenCount(atom));
}

std::size_t Chem::getRingBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getRingFlag(*b_it))
			count++;

    return count;
}

std::size_t Chem::getAromaticBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getAromaticityFlag(*b_it))
			count++;

    return count;
}

std::size_t Chem::getHeavyBondCount(const Atom& atom, const MolecularGraph& molgraph)
{
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && !isHydrogenBond(*b_it))
			count++;

    return count;
}

std::size_t Chem::getRotatableBondCount(const Atom& atom, const MolecularGraph& molgraph, bool inc_h_rotors, bool inc_amide_bonds)
{
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && isRotatable(*b_it, molgraph, inc_h_rotors, inc_amide_bonds))
			count++;

    return count;
}
