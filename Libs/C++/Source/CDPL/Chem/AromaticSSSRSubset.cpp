/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AromaticSSSRSubset.cpp 
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

#include <algorithm>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#include "CDPL/Chem/AromaticSSSRSubset.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"



using namespace CDPL;


Chem::AromaticSSSRSubset::AromaticSSSRSubset(const MolecularGraph& molgraph)
{
	extract(molgraph);
}

void Chem::AromaticSSSRSubset::extract(const MolecularGraph& molgraph)
{
	clear();

	if (molgraph.getNumAtoms() == 0 || molgraph.getNumBonds() == 0)
		return;

	init(molgraph);
	findAromaticRings();
}

void Chem::AromaticSSSRSubset::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	std::size_t num_bonds = molgraph.getNumBonds();

	if (!aromBondMask.empty())
		aromBondMask.clear();

	aromBondMask.resize(num_bonds);

	for (std::size_t i = 0; i < num_bonds; i++)
		if (getAromaticityFlag(molgraph.getBond(i)))
			aromBondMask.set(i);
}

void Chem::AromaticSSSRSubset::findAromaticRings()
{
	const FragmentList::BaseType& sssr = *getSSSR(*molGraph);
	FragmentList::BaseType::ConstElementIterator sssr_end = sssr.getElementsEnd();

	for (FragmentList::BaseType::ConstElementIterator it = sssr.getElementsBegin(); it != sssr_end; ++it) {
		const Fragment::SharedPointer& ring_ptr = *it;

		std::size_t num_ring_bonds = ring_ptr->getNumBonds();

		if (num_ring_bonds == 0 || num_ring_bonds != ring_ptr->getNumAtoms()) // sanity check
			continue;

		if (Chem::isAromatic(*ring_ptr, *molGraph, aromBondMask))
			addElement(ring_ptr);
	}
}
