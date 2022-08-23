/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomAtomCountFunctions.cpp 
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
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


std::size_t MolProp::getExplicitAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict)
{
	return Internal::getExplicitAtomCount(atom, molgraph, type, strict);
}

std::size_t MolProp::getAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict)
{

    return Internal::getAtomCount(atom, molgraph, type, strict);
}

std::size_t MolProp::getExplicitChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
    std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && !getRingFlag(*a_it))
			count++;

	return count;
}

std::size_t MolProp::getChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return (getExplicitChainAtomCount(atom, molgraph) + getImplicitHydrogenCount(atom));
}

std::size_t MolProp::getRingAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getRingFlag(*a_it))
			count++;

	return count;
}

std::size_t MolProp::getAromaticAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getAromaticityFlag(*a_it))
			count++;

	return count;
}

std::size_t MolProp::getHeavyAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return Internal::getHeavyAtomCount(atom, molgraph);
}

std::size_t MolProp::getOrdinaryHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	return Internal::getOrdinaryHydrogenCount(atom, molgraph, flags);
}
