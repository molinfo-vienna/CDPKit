/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResonanceStructureGenerator.cpp 
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

#include <iterator>

#include <boost/bind.hpp>

#include "CDPL/Chem/ResonanceStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const std::size_t MAX_RES_STRUCT_DATA_CACHE_SIZE = 5000;
}


using namespace CDPL;


Chem::ResonanceStructureGenerator::ResonanceStructureGenerator():
	resStructDataCache(MAX_RES_STRUCT_DATA_CACHE_SIZE)
{}

Chem::ResonanceStructureGenerator::ResonanceStructureGenerator(const ResonanceStructureGenerator& gen):
	resStructDataCache(MAX_RES_STRUCT_DATA_CACHE_SIZE)
{}

Chem::ResonanceStructureGenerator& Chem::ResonanceStructureGenerator::operator=(const ResonanceStructureGenerator& gen) 
{
	if (this == &gen)
		return *this;

	return *this;
}

void Chem::ResonanceStructureGenerator::generate(const MolecularGraph& molgraph)
{
	init(molgraph);

	genStartResStructs();
	genOutputResStructs();
}

std::size_t Chem::ResonanceStructureGenerator::getNumStructures() const
{
	return outputResStructs.size();
}

const Chem::ResonanceStructureGenerator::StructureData& Chem::ResonanceStructureGenerator::getStructureData(std::size_t idx) const
{
	if (idx >= outputResStructs.size())
		throw Base::IndexError("ResonanceStructureGenerator: structure data index out of bounds");

	return *outputResStructs[idx];
}

Chem::ResonanceStructureGenerator::ConstStructureDataIterator Chem::ResonanceStructureGenerator::getStructureDataBegin() const
{
	return outputResStructs.begin();
}

Chem::ResonanceStructureGenerator::ConstStructureDataIterator Chem::ResonanceStructureGenerator::getStructureDataEnd() const
{
	return outputResStructs.end();
}

void Chem::ResonanceStructureGenerator::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;
	
	createInputResStructData();
	extractResBonds();
}

void Chem::ResonanceStructureGenerator::createInputResStructData()
{
	std::size_t num_atoms = molGraph->getNumAtoms();
		
	inputResStruct.atomCharges.resize(num_atoms);
	atomData.resize(num_atoms);
	
	for (std::size_t i = 0; i < num_atoms; i++) 
		inputResStruct.atomCharges[i] = atomData[i].init(molGraph->getAtom(i), *molGraph, i);
	
	inputResStruct.bondOrders.clear();

	std::transform(molGraph->getBondsBegin(), molGraph->getBondsEnd(), std::back_inserter(inputResStruct.bondOrders.getData()),
				   boost::bind(&getOrder, _1));
}

void Chem::ResonanceStructureGenerator::extractResBonds()
{
	resBonds.clear();
	tmpBitMask.resize(molGraph->getNumBonds());
	tmpBitMask.reset();

	for (AtomDataArray::iterator it = atomData.begin(), end = atomData.end(); it != end; ++it) {
		AtomData& atom_data = *it;

		if (!atom_data.getVisitedFlag() && atom_data.canShiftElectrons())
			extractResBonds(atom_data);
	}
}

void Chem::ResonanceStructureGenerator::extractResBonds(AtomData& atom_data)
{
	atom_data.setVisitedFlag();

	for (std::size_t i = 0, num_bonds = atom_data.getNumBonds(); i < num_bonds; i++) {
		std::size_t nbr_bond_idx = atom_data.getBondIndex(i);

		if (tmpBitMask.test(nbr_bond_idx))
			continue;

		tmpBitMask.set(nbr_bond_idx);

		std::size_t nbr_atom_idx = atom_data.getAtomIndex(i);

		if (atomData[nbr_atom_idx].canShiftElectrons()) {
			resBonds.push_back({ atom_data.getIndex(), nbr_atom_idx, nbr_bond_idx});
			
			if (!atomData[nbr_atom_idx].getVisitedFlag())
				extractResBonds(atomData[nbr_atom_idx]);
		}
	}
}

void Chem::ResonanceStructureGenerator::genStartResStructs()
{
	startResStructs.clear();

	// TODO
}

void Chem::ResonanceStructureGenerator::genOutputResStructs()
{
	outputResStructs.clear();

/*
	StructureDataPtr new_res_struct_ptr;

	for (BondDataList::const_iterator it = resBonds.begin(), end = resBonds.end(); it != end; ++it) {
		const BondData& res_bond = *it;
		const AtomData& atom1_data = atomData[res_bond.atom1Index];
		const AtomData& atom2_data = atomData[res_bond.atom2Index];

		std::size_t bond_order = res_struct.bondOrders[res_bond.bondIndex];
		
		if (bond_order > 1) {
			double atom1_eneg = atom1_data.getElectronegativity();
			double atom2_eneg = atom2_data.getElectronegativity();

			if (atom1_eneg >= atom2_eneg && atom1_data.checkValenceState(res_struct, -1, -1) && atom2_data.checkValenceState(res_struct, -1, 1)) {
				if (!genNewResStruct(res_struct, new_res_struct_ptr, res_bond, -1, -1, 1))
					return false;
			}

			if (atom1_eneg <= atom2_eneg && atom1_data.checkValenceState(res_struct, -1, 1) && atom2_data.checkValenceState(res_struct, -1, -1)) {
				if (!genNewResStruct(res_struct, new_res_struct_ptr, res_bond, -1, 1, -1))
					return false;
			}
		}

		if (bond_order < 3) {
			if (atom1_data.checkValenceState(res_struct, 1, -1) && atom2_data.checkValenceState(res_struct, 1, 1)) {
				if (!genNewResStruct(res_struct, new_res_struct_ptr, res_bond, 1, -1, 1))
					return false;
			}

			if (atom1_data.checkValenceState(res_struct, 1, 1) && atom2_data.checkValenceState(res_struct, 1, -1)) {
				if (!genNewResStruct(res_struct, new_res_struct_ptr, res_bond, 1, 1, -1))
					return false;
			}
		}
	}
	
	return true;
*/
}

void Chem::ResonanceStructureGenerator::modifyResStruct(StructureData& res_struct, const BondData& res_bond,
														long bond_order_diff, long atom1_chg_diff, long atom2_chg_diff) const
{
	res_struct.bondOrders[res_bond.bondIndex] += bond_order_diff;
	res_struct.atomCharges[res_bond.atom1Index] += atom1_chg_diff;
	res_struct.atomCharges[res_bond.atom2Index] += atom2_chg_diff;
}

//---------

const Util::LArray& Chem::ResonanceStructureGenerator::StructureData::getAtomCharges() const
{
	return atomCharges;
}

const Util::STArray& Chem::ResonanceStructureGenerator::StructureData::getBondOrders() const
{
	return bondOrders;
}

//---------

long Chem::ResonanceStructureGenerator::AtomData::init(const Atom& atom, const MolecularGraph& molgraph, std::size_t idx)
{
	canShiftElecs = false;
	visited = false;
	index = idx;

	atomType = getType(atom);
	
	long form_charge = getFormalCharge(atom);
	std::size_t iupac_grp = AtomDictionary::getIUPACGroup(atomType);

	if (iupac_grp < 14 || iupac_grp > 16)
		return form_charge;

	bondIndices.clear();

	std::size_t exp_val = 0;
	bool unsat = getAromaticityFlag(atom);
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom))
			continue;
		
		const Bond& nbr_bond = *b_it;

		if (!molgraph.containsBond(nbr_bond))
			continue;

		bondIndices.push_back(molgraph.getBondIndex(nbr_bond));
		atomIndices.push_back(molgraph.getAtomIndex(nbr_atom));

		std::size_t order = getOrder(nbr_bond);

		exp_val += order;
		unsat |= (order > 1);
	}

	if (bondIndices.empty())
		return form_charge;
	
	valElecCount = AtomDictionary::getNumValenceElectrons(atomType);
	unprdElecCount = getUnpairedElectronCount(atom);
	implHCount = calcImplicitHydrogenCount(atom, molgraph);

	if (form_charge == 0 && !unsat && (valElecCount - unprdElecCount - implHCount - exp_val) < 2)
		return form_charge;

	enegativity = AtomDictionary::getAllredRochowElectronegativity(atomType);
	canShiftElecs = true;
	
	return form_charge;
}

bool Chem::ResonanceStructureGenerator::AtomData::canShiftElectrons() const
{
	return canShiftElecs;
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getIndex() const
{
	return index;
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getNumBonds() const
{
	return bondIndices.size();
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getBondIndex(std::size_t list_idx) const
{
	return bondIndices[list_idx];
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getAtomIndex(std::size_t list_idx) const
{
	return atomIndices[list_idx];
}

double Chem::ResonanceStructureGenerator::AtomData::getElectronegativity() const
{
	return enegativity;
}

bool Chem::ResonanceStructureGenerator::AtomData::getVisitedFlag() const
{
	return visited;
}

void Chem::ResonanceStructureGenerator::AtomData::setVisitedFlag()
{
	visited = true;
}

bool Chem::ResonanceStructureGenerator::AtomData::checkValenceState(const StructureData& res_struct, long val_diff, long charge_diff) const
{
	long elec_cnt = valElecCount - charge_diff - res_struct.atomCharges[index];

	if (elec_cnt > 8)
		return false;

	long val = implHCount + unprdElecCount + val_diff;

	for (IndexArray::const_iterator it = bondIndices.begin(), end = bondIndices.end(); it != end; ++it)
		val += res_struct.bondOrders[*it];

	if (atomType <= AtomType::O) {
		if (val > 4 || val > elec_cnt)
			return false;

		return ((val + elec_cnt) <= 8);
	}
	
	return (val <= elec_cnt);
}
