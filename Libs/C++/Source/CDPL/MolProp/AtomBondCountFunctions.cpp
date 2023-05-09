/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomBondCountFunctions.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


std::size_t MolProp::getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::getExplicitBondCount(atom, molgraph);
}

std::size_t MolProp::getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::getBondCount(atom, molgraph);
}

std::size_t MolProp::getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order)
{
	return Internal::getExplicitBondCount(atom, molgraph, order);
}

std::size_t MolProp::getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order)
{
	return Internal::getBondCount(atom, molgraph, order);
}

std::size_t MolProp::getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict)
{
	return Internal::getExplicitBondCount(atom, molgraph, order, type, strict);
}

std::size_t MolProp::getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict)
{
	return Internal::getBondCount(atom, molgraph, order, type, strict);
}

std::size_t MolProp::getExplicitChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
    std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && !getRingFlag(*b_it))
			count++;

    return count;
}

std::size_t MolProp::getChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return (getExplicitChainBondCount(atom, molgraph) + getImplicitHydrogenCount(atom));
}

std::size_t MolProp::getRingBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::getRingBondCount(atom, molgraph);
}

std::size_t MolProp::getAromaticBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getAromaticityFlag(*b_it))
			count++;

    return count;
}

std::size_t MolProp::getHeavyBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::getHeavyBondCount(atom, molgraph);
}

std::size_t MolProp::getRotatableBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool h_rotors, bool ring_bonds, bool amide_bonds)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && isRotatable(*b_it, molgraph, h_rotors, ring_bonds, amide_bonds))
			count++;

    return count;
}
