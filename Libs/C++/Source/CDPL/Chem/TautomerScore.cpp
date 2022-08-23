/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerScore.cpp 
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
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/TautomerScore.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


Chem::TautomerScore::TautomerScore() {}

Chem::TautomerScore::TautomerScore(const TautomerScore& ts) {}

double Chem::TautomerScore::operator()(const MolecularGraph& molgraph)
{
	double score = 0.0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
	
		if (getOrder(bond) < 2)
			continue;

		score += std::max(getAtomTypeScoreIncrement(getType(bond.getBegin())), getAtomTypeScoreIncrement(getType(bond.getEnd())));
		score += std::max(getUnsaturatedNeighborCount(bond.getBegin(), bond, molgraph), getUnsaturatedNeighborCount(bond.getEnd(), bond, molgraph));
		score += getExocyclicBondIncrement(bond);
	}

	const FragmentList& sssr = *getSSSR(molgraph);

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;

		if (std::find_if(ring.getBondsBegin(), ring.getBondsEnd(), 
						 boost::bind(std::equal_to<bool>(), false,
									 boost::bind(static_cast<bool (*)(const Bond&)>(&getAromaticityFlag), _1))) != ring.getBondsEnd())
			continue;
	
		if (isLactim(ring, molgraph))
			continue;

		score += ring.getNumBonds() * 5.0;
	}
	
    return score;
}

Chem::TautomerScore& Chem::TautomerScore::operator=(const TautomerScore& ts)
{
	return *this;
}

double Chem::TautomerScore::getAtomTypeScoreIncrement(unsigned int type) const
{
	switch (type) {

		case AtomType::O:
			return 5.0;

		case AtomType::N:
			return 1.0;

		case AtomType::S:
			return 3.0;

		default:
			return 0.0;
	}
}

double Chem::TautomerScore::getExocyclicBondIncrement(const Bond& bond) const 
{
	bool ring_flag1 = getRingFlag(bond.getBegin());
	bool ring_flag2 = getRingFlag(bond.getEnd());

	if (ring_flag1 && !ring_flag2) {
		if (getType(bond.getEnd()) == AtomType::C && getOrder(bond) == 1)
			return 1.0;

	} else if (!ring_flag1 && ring_flag2) {
		if (getType(bond.getBegin()) == AtomType::C && getOrder(bond) == 1)
			return 1.0;
	}

	return 0.0;
}

std::size_t Chem::TautomerScore::getUnsaturatedNeighborCount(const Atom& atom, const Bond& bond, const MolecularGraph& molgraph) const
{
	std::size_t count = 0;
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& nbr_bond = *b_it;

		if (&nbr_bond == &bond)
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
			continue;
	
		if (Internal::isUnsaturated(nbr_atom, molgraph))
			count++;
	}

	return count;
}

bool Chem::TautomerScore::isLactim(const Fragment& ring, const MolecularGraph& molgraph) const
{
	std::size_t cn_bond_cnt = 0;
	std::size_t lactim_cnt = 0;

	for (Fragment::ConstBondIterator it = ring.getBondsBegin(), end = ring.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		unsigned int atom1_type = getType(bond.getBegin());
		unsigned int atom2_type = getType(bond.getEnd());

		if (atom1_type == AtomType::C && atom2_type == AtomType::N) {
			if (hasExocyclicOH(bond.getBegin(), molgraph))
				lactim_cnt++;

			cn_bond_cnt++;

		} else if (atom1_type == AtomType::N && atom2_type == AtomType::C) {
			if (hasExocyclicOH(bond.getEnd(), molgraph))
				lactim_cnt++;

			cn_bond_cnt++;
		}
	}

	if (cn_bond_cnt == 0)
		return false;

	return ((lactim_cnt * 2) >= cn_bond_cnt); 
}

bool Chem::TautomerScore::hasExocyclicOH(const Atom& atom, const MolecularGraph& molgraph) const
{
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& nbr_bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
			continue;

		if (getRingFlag(nbr_bond))
			continue;

		if (getType(nbr_atom) != AtomType::O)
			continue;

		if (Internal::getHeavyAtomCount(nbr_atom, molgraph) != 1)
			continue;

		return true;
	}

	return false;
}


