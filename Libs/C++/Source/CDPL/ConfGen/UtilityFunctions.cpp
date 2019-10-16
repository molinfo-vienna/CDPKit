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
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
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

std::size_t ConfGen::buildFragmentLinkBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, bool reset)
{
    using namespace Chem;

	bond_mask.resize(molgraph.getNumBonds());

	if (reset)
		bond_mask.reset();

	std::size_t i = 0;
	std::size_t num_bonds = 0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it, i++) {
		const Bond& bond = *it;
		
		if (isFragmentLinkBond(bond, molgraph)) {
			bond_mask.set(i);
			num_bonds++;
		}
	}

	return num_bonds;
}

bool ConfGen::isRotatableBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool het_h_rotors)
{
	using namespace Chem;

    if (getOrder(bond) != 1)
		return false;

	if (getRingFlag(bond))
		return false;

    const Atom& atom1 = bond.getBegin();
	const Atom& atom2 = bond.getEnd();

	if (getHybridizationState(atom1) == HybridizationState::SP && getHybridizationState(atom2) == HybridizationState::SP)
		return false;

	if (getExplicitBondCount(atom1, molgraph) < 2 ) 
		return false;

	if (getExplicitBondCount(atom2, molgraph) < 2)
		return false;

	bool atom1_is_h_rot = (getHeavyBondCount(atom1, molgraph) < 2);
	bool atom2_is_h_rot = (getHeavyBondCount(atom2, molgraph) < 2);
		
	if (!atom1_is_h_rot && !atom2_is_h_rot)
		return true;

	if (!het_h_rotors)
		return false;

 	return ((atom1_is_h_rot && getType(atom1) != AtomType::C) || (atom2_is_h_rot && getType(atom1) != AtomType::C));
}

std::size_t ConfGen::buildRotatableBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, 
											bool het_h_rotors, bool reset)
{
	using namespace Chem;

	std::size_t num_bonds = molgraph.getNumBonds();
	std::size_t num_rot_bonds = 0;

	if (reset) {
		bond_mask.resize(num_bonds);
		bond_mask.reset();
	}

	for (std::size_t i = 0; i < num_bonds; i++) {
		if (isRotatableBond(molgraph.getBond(i), molgraph, het_h_rotors)) {
			bond_mask.set(i);
			num_rot_bonds++;
		}
	} 

	return num_rot_bonds;
}

std::size_t ConfGen::buildRotatableBondMask(const Chem::MolecularGraph& molgraph, const Util::BitSet& excl_bond_mask, 
											Util::BitSet& bond_mask, bool het_h_rotors, bool reset)
{
	using namespace Chem;

	std::size_t num_bonds = molgraph.getNumBonds();
	std::size_t num_rot_bonds = 0;

	bond_mask.resize(num_bonds);
	bond_mask.reset();

	for (std::size_t i = 0; i < num_bonds; i++) {
		if (excl_bond_mask.test(i))
			continue;

		if (isRotatableBond(molgraph.getBond(i), molgraph, het_h_rotors)) {
			bond_mask.set(i);
			num_rot_bonds++;
		}
	} 

	return num_rot_bonds;
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

	if (makeHydrogenComplete(mol, true)) {
		if (hasComponents(mol))
			perceiveComponents(mol, true);

		calcTopologicalDistanceMatrix(mol, true);

	} else {
		//perceiveComponents(mol, false);
		calcTopologicalDistanceMatrix(mol, false);
	}
}

unsigned int ConfGen::parameterizeMMFF94Interactions(const Chem::MolecularGraph& molgraph, ForceField::MMFF94InteractionParameterizer& parameterizer,
											 ForceField::MMFF94InteractionData& param_data, unsigned int ff_type)
{
	unsigned int int_types = ForceField::InteractionType::ALL;

	switch (ff_type) {

		case ForceFieldType::MMFF94:
			parameterizer.setDynamicParameterDefaults();
			break;

		case ForceFieldType::MMFF94S:
			parameterizer.setStaticParameterDefaults();
			break;

		case ForceFieldType::MMFF94_NO_ESTAT:
			parameterizer.setDynamicParameterDefaults();
			int_types = ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC;
			break;

		case ForceFieldType::MMFF94S_NO_ESTAT:
			parameterizer.setStaticParameterDefaults();
			int_types = ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC;
			break;

		default:
			return ReturnCode::FORCEFIELD_SETUP_FAILED;
			
	}	

	parameterizer.parameterize(molgraph, param_data, int_types);

	return ReturnCode::SUCCESS;
} 
