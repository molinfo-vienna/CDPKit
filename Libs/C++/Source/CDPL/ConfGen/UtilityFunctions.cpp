/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp 
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

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL; 


namespace
{

    bool isSplitHeteroAtom(unsigned int type)
    {
		using namespace Chem;

		switch (type) {

			case AtomType::N:
			case AtomType::O:
			case AtomType::S:
			case AtomType::Se:
			case AtomType::P:
				return true;

			default: 
				break;
		}

		return false;
    }

    bool hasOnlyCarbonOrHydrogenNeighbors(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, const Chem::Bond& x_bond)
    {
		using namespace Chem;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Bond& nbr_bond = *b_it;

			if (&nbr_bond == &x_bond)
				continue;

			if (!molgraph.containsBond(nbr_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;
 
			switch (getType(nbr_atom)) {

				case AtomType::H:
				case AtomType::C:
					continue;

				default:
					return false;
			}
		}

		return true;
    }
}


bool ConfGen::isFragmentLinkBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    if (getRingFlag(bond))
		return false;

    const Atom& atom1 = bond.getBegin();
	unsigned int atom1_type = getType(atom1);

	if (atom1_type == AtomType::H)
		return false;

    const Atom& atom2 = bond.getEnd();
    unsigned int atom2_type = getType(atom2);
 
	if (atom2_type == AtomType::H)
		return false;

    if (getRingFlag(atom1)) 
		return (getBondCount(atom2, molgraph) > 1);

    if (getRingFlag(atom2))
		return (getBondCount(atom1, molgraph) > 1);

    if (getOrder(bond) != 1)
		return false;

    if (atom1_type == AtomType::C) {
		if (!isSplitHeteroAtom(atom2_type))
			return false;

		return hasOnlyCarbonOrHydrogenNeighbors(atom1, molgraph, bond);
    }

    if (atom2_type == AtomType::C) {
		if (!isSplitHeteroAtom(atom1_type))
			return false;

		return hasOnlyCarbonOrHydrogenNeighbors(atom2, molgraph, bond);
	}

    return false;
} 

unsigned int ConfGen::perceiveFragmentType(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

	bool has_rigid_ring_bonds = false;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (getRingFlag(bond)) {
			if (getOrder(bond) != 1 || getAromaticityFlag(bond))
				has_rigid_ring_bonds = true;
			else
				return FragmentType::FLEXIBLE_RING_SYSTEM;
		}
	}

	if (has_rigid_ring_bonds)
		return FragmentType::RIGID_RING_SYSTEM;
	
	return FragmentType::CHAIN;
}

void ConfGen::prepareForConformerGeneration(Chem::Molecule& mol)
{
	using namespace Chem;

	calcImplicitHydrogenCounts(mol, false);
	perceiveHybridizationStates(mol, false);

	perceiveSSSR(mol, false);
	setRingFlags(mol, false);
	setAromaticityFlags(mol, false);

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		if (!isStereoCenter(atom, mol, false)) 
			setStereoDescriptor(atom, StereoDescriptor(AtomConfiguration::NONE));

		else if ((!hasStereoDescriptor(atom) || getStereoDescriptor(atom).getConfiguration() == AtomConfiguration::UNDEF) && !isInvertibleNitrogen(atom, mol)) 
			setStereoDescriptor(atom, calcStereoDescriptor(atom, mol, 1));
	}

	for (Molecule::BondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) {
		Bond& bond = *it;

		if (!isStereoCenter(bond, mol, false)) 
			setStereoDescriptor(bond, StereoDescriptor(BondConfiguration::NONE));
		
		else if (!hasStereoDescriptor(bond) || getStereoDescriptor(bond).getConfiguration() == AtomConfiguration::UNDEF)
			setStereoDescriptor(bond, calcStereoDescriptor(bond, mol, 1));
	}

	if (makeHydrogenComplete(mol)) {
		calcImplicitHydrogenCounts(mol, true);
		perceiveComponents(mol, true);
		calcTopologicalDistanceMatrix(mol, true);

	} else {
		perceiveComponents(mol, false);
		calcTopologicalDistanceMatrix(mol, false);
	}
}
