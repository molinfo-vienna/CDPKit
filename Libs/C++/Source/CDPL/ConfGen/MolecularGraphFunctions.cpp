/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctions.cpp 
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

#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/BondFunctions.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL; 


std::size_t ConfGen::buildFragmentLinkBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, bool reset)
{
    using namespace Chem;

	std::size_t num_bonds = molgraph.getNumBonds();
	std::size_t num_lnk_bonds = 0;

	if (bond_mask.size() < num_bonds)
		bond_mask.resize(num_bonds);

	if (reset)
		bond_mask.reset();

	for (std::size_t i = 0; i < num_bonds; i++) {
		if (isFragmentLinkBond(molgraph.getBond(i), molgraph)) {
			bond_mask.set(i);
			num_lnk_bonds++;
		}
	}

	return num_lnk_bonds;
}

std::size_t ConfGen::buildRotatableBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, 
											bool het_h_rotors, bool reset)
{
	using namespace Chem;

	std::size_t num_bonds = molgraph.getNumBonds();
	std::size_t num_rot_bonds = 0;

	if (bond_mask.size() < num_bonds)
		bond_mask.resize(num_bonds);

	if (reset) 
		bond_mask.reset();
	
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

	if (bond_mask.size() < num_bonds)
		bond_mask.resize(num_bonds);
	
	if (reset)
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

void ConfGen::setConformers(Chem::MolecularGraph& molgraph, const ConformerDataArray& conf_array)
{
	using namespace Chem;

	std::size_t num_confs = conf_array.size();

	if (num_confs == 0) {
		clearConformations(molgraph);
		clearConformerEnergies(molgraph);
		return;
	}

	Util::DArray::SharedPointer conf_energies(new Util::DArray());
	std::size_t num_atoms = molgraph.getNumAtoms();

	for (std::size_t i = 0; i < num_confs; i++) {
		const ConformerData& conf_data = *conf_array[i];

		for (std::size_t j = 0; j < num_atoms; j++) {
			Atom& atom = molgraph.getAtom(j);
			Math::Vector3DArray::SharedPointer coords_array;
			
			if (i == 0) {
				coords_array.reset(new Math::Vector3DArray());
				set3DCoordinatesArray(atom, coords_array);

			} else 
				coords_array = get3DCoordinatesArray(atom);

			coords_array->addElement(conf_data[j]);
		}
		
		conf_energies->addElement(conf_data.getEnergy());
	}

	setConformerEnergies(molgraph, conf_energies);
}

unsigned int ConfGen::parameterizeMMFF94Interactions(const Chem::MolecularGraph& molgraph, ForceField::MMFF94InteractionParameterizer& parameterizer,
													 ForceField::MMFF94InteractionData& param_data, unsigned int ff_type, bool strict)
{
	using namespace ForceField;

	unsigned int int_types = InteractionType::ALL;

	switch (ff_type) {

		case ForceFieldType::MMFF94:
			parameterizer.setParameterSet(MMFF94ParameterSet::DYNAMIC);
			break;

		case ForceFieldType::MMFF94S:
			parameterizer.setParameterSet(MMFF94ParameterSet::STATIC);
			break;

		case ForceFieldType::MMFF94_NO_ESTAT:
			parameterizer.setParameterSet(MMFF94ParameterSet::DYNAMIC);
			int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
			break;

		case ForceFieldType::MMFF94S_NO_ESTAT:
			parameterizer.setParameterSet(MMFF94ParameterSet::STATIC);
			int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
			break;

		default:
			return ReturnCode::FORCEFIELD_SETUP_FAILED;
			
	}	

	parameterizer.parameterize(molgraph, param_data, int_types, strict);

	return ReturnCode::SUCCESS;
} 
