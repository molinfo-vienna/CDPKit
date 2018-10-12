/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphBondCountFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondContainerFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


std::size_t Chem::getCompleteBondCount(const MolecularGraph& molgraph)
{
	std::size_t count = 0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (molgraph.containsAtom(bond.getBegin()) && molgraph.containsAtom(bond.getEnd()))
			count++;
	}

	return count;
}

std::size_t Chem::getBondCount(const MolecularGraph& molgraph)
{
	return (molgraph.getNumBonds() + getImplicitHydrogenCount(molgraph));
}

std::size_t Chem::getBondCount(const MolecularGraph& molgraph, std::size_t order)
{
	std::size_t count = getExplicitBondCount(molgraph, order);

	if (order == 1)
		count += getImplicitHydrogenCount(molgraph);

	return count;
}

std::size_t Chem::getHydrogenBondCount(const MolecularGraph& molgraph)
{
	return (getExplicitHydrogenBondCount(molgraph) + getImplicitHydrogenCount(molgraph));
}

std::size_t Chem::getChainBondCount(const MolecularGraph& molgraph)
{
	return (getExplicitChainBondCount(molgraph) + getImplicitHydrogenCount(molgraph));
}

std::size_t Chem::getRotatableBondCount(const MolecularGraph& molgraph, bool inc_h_rotors, bool inc_amide_bonds)
{
	std::size_t count = 0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it)
		if (isRotatable(*it, molgraph, inc_h_rotors, inc_amide_bonds))
			count++;

	return count;
}
