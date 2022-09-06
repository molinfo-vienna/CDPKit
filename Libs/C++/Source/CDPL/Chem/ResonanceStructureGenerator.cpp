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

#include <limits>

#include "CDPL/Chem/ResonanceStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/SHA1.hpp"


namespace
{

	const std::size_t MAX_RES_STRUCT_DATA_CACHE_SIZE = 5000;
}


using namespace CDPL;


Chem::ResonanceStructureGenerator::ResonanceStructureGenerator():
	resStructDataCache(MAX_RES_STRUCT_DATA_CACHE_SIZE), minNonCCharge(-1),
	maxNonCCharge(1), minCCharge(-1), maxCCharge(1), rep12Charges(false),
	cc12Charges(false), maxChgdAtomCount(std::numeric_limits<std::size_t>::max()),
	maxChgdNonCCount(std::numeric_limits<std::size_t>::max()),
	maxChgdCCount(std::numeric_limits<std::size_t>::max())
{}

Chem::ResonanceStructureGenerator::ResonanceStructureGenerator(const ResonanceStructureGenerator& gen):
	resStructDataCache(MAX_RES_STRUCT_DATA_CACHE_SIZE),
	callbackFunc(gen.callbackFunc), minNonCCharge(gen.minNonCCharge),
	maxNonCCharge(gen.maxNonCCharge), minCCharge(gen.minCCharge), maxCCharge(gen.maxCCharge),
	rep12Charges(gen.rep12Charges),	cc12Charges(gen.cc12Charges), maxChgdAtomCount(gen.maxChgdAtomCount),
	maxChgdNonCCount(gen.maxChgdNonCCount),	maxChgdCCount(gen.maxChgdCCount)
{}

Chem::ResonanceStructureGenerator& Chem::ResonanceStructureGenerator::operator=(const ResonanceStructureGenerator& gen) 
{
	if (this == &gen)
		return *this;

	callbackFunc = gen.callbackFunc;
	minNonCCharge = gen.minNonCCharge;
	maxNonCCharge = gen.maxNonCCharge;
	minCCharge = gen.minCCharge;
	maxCCharge = gen.maxCCharge;
	rep12Charges = gen.rep12Charges;
	cc12Charges = gen.cc12Charges;
	maxChgdAtomCount = gen.maxChgdAtomCount;
	maxChgdNonCCount = gen.maxChgdNonCCount;
	maxChgdCCount = gen.maxChgdCCount;

	return *this;
}

void Chem::ResonanceStructureGenerator::setCallbackFunction(const CallbackFunction& func)
{
    callbackFunc = func;
}

const Chem::ResonanceStructureGenerator::CallbackFunction& Chem::ResonanceStructureGenerator::getCallbackFunction() const
{
    return callbackFunc;
}

void Chem::ResonanceStructureGenerator::setMaxNonCarbonCharge(long max_charge)
{
	maxNonCCharge = max_charge;
}

long Chem::ResonanceStructureGenerator::getMaxNonCarbonCharge() const
{
	return maxNonCCharge;
}

void Chem::ResonanceStructureGenerator::setMaxCarbonCharge(long max_charge)
{
	maxCCharge = max_charge;
}

long Chem::ResonanceStructureGenerator::getMaxCarbonCharge() const
{
	return maxCCharge;
}

void Chem::ResonanceStructureGenerator::setMinNonCarbonCharge(long min_charge)
{
	minNonCCharge = min_charge;
}

long Chem::ResonanceStructureGenerator::getMinNonCarbonCharge() const
{
	return minNonCCharge;
}

void Chem::ResonanceStructureGenerator::setMinCarbonCharge(long min_charge)
{
	minCCharge = min_charge;
}

long Chem::ResonanceStructureGenerator::getMinCarbonCharge() const
{
	return minCCharge;
}

void Chem::ResonanceStructureGenerator::allowRepulsive12Charges(bool allow)
{
	rep12Charges = allow;
}

bool Chem::ResonanceStructureGenerator::repulsive12ChargesAllowed() const
{
	return rep12Charges;
}

void Chem::ResonanceStructureGenerator::allowCarbonCarbonBond12Charges(bool allow)
{
	cc12Charges = allow;
}

bool Chem::ResonanceStructureGenerator::carbonCarbonBond12ChargesAllowed() const
{
	return cc12Charges;
}

void Chem::ResonanceStructureGenerator::setMaxChargedAtomCount(std::size_t max_count)
{
	maxChgdAtomCount = max_count;
}

std::size_t Chem::ResonanceStructureGenerator::getMaxChargedAtomCount() const
{
	return maxChgdAtomCount;
}

void Chem::ResonanceStructureGenerator::setMaxChargedCarbonCount(std::size_t max_count)
{
	maxChgdCCount = max_count;
}

std::size_t Chem::ResonanceStructureGenerator::getMaxChargedCarbonCount() const
{
	return maxChgdCCount;
}

void Chem::ResonanceStructureGenerator::setMaxChargedNonCarbonCount(std::size_t max_count)
{
	maxChgdNonCCount = max_count;
}

std::size_t Chem::ResonanceStructureGenerator::getMaxChargedNonCarbonCount() const
{
	return maxChgdNonCCount;
}
			
void Chem::ResonanceStructureGenerator::generate(const MolecularGraph& molgraph)
{
	if (!callbackFunc)
		return;

	if (!init(molgraph))
		return;

	while (!nextGeneration.empty()) {
		currGeneration.swap(nextGeneration);

		while (!currGeneration.empty()) {
			ResStructDataPtr res_struct_ptr = currGeneration.back(); currGeneration.pop_back();

			if (!shiftCharges(*res_struct_ptr))
				return;
		}
	}
}

bool Chem::ResonanceStructureGenerator::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	currGeneration.clear();
	nextGeneration.clear();
	resStructHashCodes.clear();
	
	return genStartResStruct();
}

bool Chem::ResonanceStructureGenerator::genStartResStruct()
{
	ResStructDataPtr start_res_struct_ptr = resStructDataCache.get();
	ResStructData& start_res_struct = *start_res_struct_ptr;
	std::size_t num_atoms = molGraph->getNumAtoms();
	
	start_res_struct.atomCharges.resize(num_atoms);

	atomData.resize(num_atoms);
	
	for (std::size_t i = 0; i < num_atoms; i++) 
		start_res_struct.atomCharges[i] = atomData[i].init(molGraph->getAtom(i), *molGraph, i);
	
	start_res_struct.bondOrders.reserve(molGraph->getNumBonds());
	start_res_struct.bondOrders.clear();

	resBonds.clear();

	std::size_t i = 0;
	
	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it, i++) {
		const Bond& bond = *it;

		start_res_struct.bondOrders.addElement(getOrder(bond));

		const Atom& atom1 = bond.getBegin();

		if (!molGraph->containsAtom(atom1))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molGraph->containsAtom(atom2))
			continue;

		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);

		if (!atomData[atom1_idx].canShiftElectrons())
			continue;

		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

		if (!atomData[atom2_idx].canShiftElectrons())
			continue;

		resBonds.push_back({ atom1_idx, atom2_idx, i });
	}

	addNewResStruct(start_res_struct_ptr);
	
	return outputResStruct(start_res_struct);
}

bool Chem::ResonanceStructureGenerator::shiftCharges(const ResStructData& res_struct)
{
	ResStructDataPtr new_res_struct_ptr;

	for (ResBondList::const_iterator it = resBonds.begin(), end = resBonds.end(); it != end; ++it) {
		const ResBond& res_bond = *it;
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
}

bool Chem::ResonanceStructureGenerator::genNewResStruct(const ResStructData& res_struct, ResStructDataPtr& new_res_struct_ptr, const ResBond& res_bond,
														long bond_order_diff, long atom1_chg_diff, long atom2_chg_diff)
{
	allocResStructData(res_struct, new_res_struct_ptr);

	new_res_struct_ptr->bondOrders[res_bond.bondIndex] += bond_order_diff;
	new_res_struct_ptr->atomCharges[res_bond.atom1Index] += atom1_chg_diff;
	new_res_struct_ptr->atomCharges[res_bond.atom2Index] += atom2_chg_diff;

	if (addNewResStruct(new_res_struct_ptr)) {
		if (!outputResStruct(*new_res_struct_ptr))
			return false;
					
		new_res_struct_ptr.reset();
					
	} else
		restoreState(res_struct, *new_res_struct_ptr, res_bond);

	return true;
}

bool Chem::ResonanceStructureGenerator::addNewResStruct(const ResStructDataPtr& res_struct_ptr)
{
	const ResStructData& res_struct = *res_struct_ptr;

	if (!resStructHashCodes.insert(calcResStructHashCode(res_struct)).second)
		return false;
	
	nextGeneration.push_back(res_struct_ptr);
	
	return true;
}

Base::uint64 Chem::ResonanceStructureGenerator::calcResStructHashCode(const ResStructData& res_struct) const
{
	Internal::SHA1 sha;
	Base::uint8 sha_hash[Internal::SHA1::HASH_SIZE];

	sha.input(res_struct.atomCharges.getElementsBegin(), res_struct.atomCharges.getElementsEnd());
	sha.input(res_struct.bondOrders.getElementsBegin(), res_struct.bondOrders.getElementsEnd());
	sha.getResult(&sha_hash[0]);

	Base::uint64 hash_code = 0;

	for (std::size_t i = 0; i < Internal::SHA1::HASH_SIZE; i++) 
		hash_code = hash_code ^ (Base::uint64(sha_hash[i]) << ((i % 8) * 8));

	return hash_code;
}

bool Chem::ResonanceStructureGenerator::outputResStruct(const ResStructData& res_struct) const
{
	if (!validateOutputResStruct(res_struct))
		return true;

	return callbackFunc(res_struct.atomCharges, res_struct.bondOrders);
}

bool Chem::ResonanceStructureGenerator::validateOutputResStruct(const ResStructData& res_struct) const
{
	for (ResBondList::const_iterator it = resBonds.begin(), end = resBonds.end(); it != end; ++it) {
		const ResBond& res_bond = *it;
		long atom1_chg = res_struct.atomCharges[res_bond.atom1Index];
		long atom2_chg = res_struct.atomCharges[res_bond.atom2Index];

		if (!rep12Charges && ((atom1_chg < 0 && atom2_chg < 0) || (atom1_chg > 0 && atom2_chg > 0)))
			return false;

		if (!cc12Charges && atom1_chg != 0 && atom2_chg != 0 &&
			atomData[res_bond.atom1Index].isCarbon() && atomData[res_bond.atom2Index].isCarbon())
			return false;
	}

	std::size_t chgd_atom_count = 0;
	std::size_t chgd_c_count = 0;
	std::size_t chgd_non_c_count = 0;
	
	for (std::size_t i = 0, num_atoms = atomData.size(); i < num_atoms; i++) {
		long charge = res_struct.atomCharges[i];
		bool is_carbon = atomData[i].isCarbon();
		
		if (charge != 0) {
			if (++chgd_atom_count > maxChgdAtomCount)
				return false;
			
			if (is_carbon) {
				if (++chgd_c_count > maxChgdCCount)
					return false;
				
			} else {
				if (++chgd_non_c_count > maxChgdNonCCount)
					return false;
			}
		}

		if (is_carbon) {
			if (charge < minCCharge || charge > maxCCharge)
				return false;
			
		} else {
			if (charge < minNonCCharge || charge > maxNonCCharge)
				return false;
		}
	}
	
	return true;
}

void Chem::ResonanceStructureGenerator::restoreState(const ResStructData& src_res_struct, ResStructData& tgt_res_struct, const ResBond& res_bond) const
{
	tgt_res_struct.atomCharges[res_bond.atom1Index] = src_res_struct.atomCharges[res_bond.atom1Index];
	tgt_res_struct.atomCharges[res_bond.atom2Index] = src_res_struct.atomCharges[res_bond.atom2Index];
	tgt_res_struct.bondOrders[res_bond.bondIndex] = src_res_struct.bondOrders[res_bond.bondIndex];
}

void Chem::ResonanceStructureGenerator::allocResStructData(const ResStructData& src_res_struct, ResStructDataPtr& alloc_res_struct_ptr)
{
	if (alloc_res_struct_ptr)
		return;

	alloc_res_struct_ptr = resStructDataCache.get();
	alloc_res_struct_ptr->atomCharges = src_res_struct.atomCharges;
	alloc_res_struct_ptr->bondOrders = src_res_struct.bondOrders;
}

//---------

long Chem::ResonanceStructureGenerator::AtomData::init(const Atom& atom, const MolecularGraph& molgraph, std::size_t atom_idx)
{
	canShiftElecs = false;
	atomType = getType(atom);
	
	long form_charge = getFormalCharge(atom);
	std::size_t iupac_grp = AtomDictionary::getIUPACGroup(atomType);

	if (iupac_grp < 14 || iupac_grp > 16)
		return form_charge;

	bondIndices.clear();

	std::size_t exp_val = 0;
	bool unsat = false;
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom))
			continue;
		
		const Bond& nbr_bond = *b_it;

		if (!molgraph.containsBond(nbr_bond))
			continue;

		bondIndices.push_back(molgraph.getBondIndex(nbr_bond));

		std::size_t order = getOrder(nbr_bond);

		exp_val += order;
		unsat |= (order > 1) || getAromaticityFlag(nbr_bond);
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
	atomIndex = atom_idx;
	
	return form_charge;
}

bool Chem::ResonanceStructureGenerator::AtomData::canShiftElectrons() const
{
	return canShiftElecs;
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getNumBonds() const
{
	return bondIndices.size();
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getBondIndex(std::size_t list_idx) const
{
	return bondIndices[list_idx];
}

double Chem::ResonanceStructureGenerator::AtomData::getElectronegativity() const
{
	return enegativity;
}

bool Chem::ResonanceStructureGenerator::AtomData::checkValenceState(const ResStructData& res_struct, long val_diff, long charge_diff) const
{
	long elec_cnt = valElecCount - charge_diff - res_struct.atomCharges[atomIndex];

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

bool Chem::ResonanceStructureGenerator::AtomData::isCarbon() const
{
	return (atomType == AtomType::C);
}
