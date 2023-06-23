/* 
 * MolecularGraphAtomCountFunctions.cpp 
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

#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


std::size_t MolProp::getAtomCount(const Chem::MolecularGraph& molgraph)
{
	return (molgraph.getNumAtoms() + getImplicitHydrogenCount(molgraph));
}

std::size_t MolProp::getAtomCount(const Chem::MolecularGraph& molgraph, unsigned int type)
{
	using namespace Chem;
	
	std::size_t count = 0;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		unsigned int atm_type = getType(atom);

		if (atm_type == type)
			count++;
	
		if (type == AtomType::H)
			count += getImplicitHydrogenCount(atom);
	}

	return count;
}

std::size_t MolProp::getImplicitHydrogenCount(const Chem::MolecularGraph& molgraph)
{
	std::size_t count = 0;

	for (Chem::MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it)
		count += getImplicitHydrogenCount(*it);
	
	return count;
}

std::size_t MolProp::getOrdinaryHydrogenCount(const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	using namespace Chem;
	
	std::size_t count = 0;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (isOrdinaryHydrogen(atom, molgraph, flags))
			count++;

		count += getImplicitHydrogenCount(atom);
	}

	return count;
}

std::size_t MolProp::getChainAtomCount(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!getRingFlag(atom))
			count++;

		count += getImplicitHydrogenCount(atom);
	}

	return count;
}

std::size_t MolProp::getExplicitOrdinaryHydrogenCount(const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	std::size_t count = 0;

	for (Chem::MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it)
		if (isOrdinaryHydrogen(*it, molgraph, flags))
			count++;

	return count;
}

std::size_t MolProp::getHBondAcceptorAtomCount(const Chem::MolecularGraph& molgraph)
{
	std::size_t count = 0;

	for (Chem::MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it)
		if (isHBondAcceptor(*it, molgraph))
			count++;

	return count;
}

std::size_t MolProp::getHBondDonorAtomCount(const Chem::MolecularGraph& molgraph)
{
	std::size_t count = 0;

	for (Chem::MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it)
		if (isHBondDonor(*it, molgraph))
			count++;

	return count;
}
