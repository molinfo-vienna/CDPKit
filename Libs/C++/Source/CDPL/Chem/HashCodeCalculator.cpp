/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HashCodeCalculator.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>
#include <boost/math/special_functions/prime.hpp>

#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Internal/SHA1.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


namespace 
{

	const std::size_t ATOM_CONFIG_R_IDX           = 0;
	const std::size_t ATOM_CONFIG_S_IDX           = ATOM_CONFIG_R_IDX + 1;
	const std::size_t ATOM_H_COUNT_IDX            = ATOM_CONFIG_S_IDX + 1;
	const std::size_t ATOM_H_COUNT_RANGE          = 10;
	const std::size_t ATOM_NEG_CHARGE_IDX         = ATOM_H_COUNT_IDX + ATOM_H_COUNT_RANGE;
	const std::size_t ATOM_NEG_CHARGE_RANGE       = 10;
	const std::size_t ATOM_POS_CHARGE_IDX         = ATOM_NEG_CHARGE_IDX + ATOM_NEG_CHARGE_RANGE;
	const std::size_t ATOM_POS_CHARGE_RANGE       = 10;
	const std::size_t ATOM_GLOBAL_STEREO_REF_IDX  = ATOM_POS_CHARGE_IDX + ATOM_POS_CHARGE_RANGE;
	const std::size_t ATOM_TYPE_IDX               = ATOM_GLOBAL_STEREO_REF_IDX + 1;
	const std::size_t ATOM_TYPE_RANGE             = Chem::AtomType::MAX_ATOMIC_NO + 1;
	const std::size_t ATOM_ISOTOPE_IDX            = ATOM_TYPE_IDX + ATOM_TYPE_RANGE;
	const std::size_t ATOM_ISOTOPE_RANGE          = 300;
	const std::size_t ATOM_GLOBAL_STEREO_FLAG_IDX = ATOM_ISOTOPE_IDX + ATOM_ISOTOPE_RANGE;
	const std::size_t ATOM_AROMATICITY_IDX        = ATOM_GLOBAL_STEREO_FLAG_IDX + 1;

	const std::size_t BOND_AROM_FLAG_IDX          = 0;
	const std::size_t BOND_RING_FLAG_IDX          = BOND_AROM_FLAG_IDX + 1;
	const std::size_t BOND_CONFIG_E_IDX           = BOND_RING_FLAG_IDX + 1;
	const std::size_t BOND_CONFIG_Z_IDX           = BOND_CONFIG_E_IDX + 1;
	const std::size_t BOND_ORDER_IDX              = BOND_CONFIG_Z_IDX + 1;
	const std::size_t BOND_ORDER_RANGE            = 4;
	const std::size_t BOND_GLOBAL_STEREO_FLAG_IDX = BOND_ORDER_IDX + BOND_ORDER_RANGE;

	const std::size_t NUM_ATOM_HASH_ITERATIONS    = 32;
	const std::size_t NUM_BOND_HASH_ITERATIONS    = 32;

	typedef std::pair<const Chem::Atom*, const Chem::Bond*> Ligand;

	class AtomCIPPGreaterCmpFunc
	{

	public:
		AtomCIPPGreaterCmpFunc() {}

		bool operator()(const Ligand& lig1, const Ligand& lig2) const {
			return (getCIPPriority(*lig1.first) > getCIPPriority(*lig2.first));
		}
	};
}


const unsigned int Chem::HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::HashCodeCalculator::DEF_BOND_PROPERTY_FLAGS;

//-----

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::operator()(const Atom& atom) const
{
	std::uint64_t seed = 1;

	if (flags & AtomPropertyFlag::TYPE)
		seed = getAtomTypeHashSeed(atom);
	
	if (flags & AtomPropertyFlag::ISOTOPE)
		seed *= getAtomIsotopeHashSeed(atom);

	if (flags & AtomPropertyFlag::H_COUNT)
		seed *= getAtomHCountHashSeed(atom);

	if (flags & AtomPropertyFlag::FORMAL_CHARGE)
		seed *= getAtomChargeHashSeed(atom);

	if (flags & AtomPropertyFlag::CIP_CONFIGURATION)
  		seed *= getAtomConfigHashSeed(atom);

	if (flags & AtomPropertyFlag::AROMATICITY)
  		seed *= getAtomAromaticityHashSeed(atom);

	return seed;
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomTypeHashSeed(const Atom& atom) const
{
	return boost::math::prime(ATOM_TYPE_IDX + (getType(atom) % ATOM_TYPE_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomIsotopeHashSeed(const Atom& atom) const
{
	return boost::math::prime(ATOM_ISOTOPE_IDX + (getIsotope(atom) % ATOM_ISOTOPE_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomAromaticityHashSeed(const Atom& atom) const
{
	if (getAromaticityFlag(atom))
		return boost::math::prime(ATOM_AROMATICITY_IDX);

	return 1;
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomChargeHashSeed(const Atom& atom) const
{
	const long charge = getFormalCharge(atom);

	if (charge < 0)
		return boost::math::prime(ATOM_NEG_CHARGE_IDX + ((-charge - 1) % ATOM_NEG_CHARGE_RANGE));
	
	return boost::math::prime(ATOM_POS_CHARGE_IDX + (charge % ATOM_POS_CHARGE_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomHCountHashSeed(const Atom& atom) const
{
	return boost::math::prime(ATOM_H_COUNT_IDX + (Internal::getBondCount(atom, *calculator.molGraph, 1, AtomType::H) % ATOM_H_COUNT_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomConfigHashSeed(const Atom& atom) const
{
	unsigned int config = getCIPConfiguration(atom);

	switch (config) {

		case AtomConfiguration::R: 
			return boost::math::prime(ATOM_CONFIG_R_IDX);

		case AtomConfiguration::S: 
			return boost::math::prime(ATOM_CONFIG_S_IDX);

		default: 
			return 1;
	}
}

//-----

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::operator()(const Bond& bond) const
{
	std::uint64_t seed = 1;
	
	if (flags & (BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY))
		seed = getBondTypeHashSeed(bond);

	if (flags & BondPropertyFlag::CIP_CONFIGURATION)
		seed *= getBondConfigHashSeed(bond);

	if (flags & BondPropertyFlag::TOPOLOGY)
		seed *= getBondTopologyHashSeed(bond);

	return seed;
}

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::getBondTopologyHashSeed(const Bond& bond) const
{
	if (getRingFlag(bond))
		return boost::math::prime(BOND_RING_FLAG_IDX);

	return 1;
}

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::getBondTypeHashSeed(const Bond& bond) const
{
	if ((flags & BondPropertyFlag::AROMATICITY) && getAromaticityFlag(bond))
		return boost::math::prime(BOND_AROM_FLAG_IDX);

	if (flags & BondPropertyFlag::ORDER) 
		return boost::math::prime(BOND_ORDER_IDX + (getOrder(bond) % BOND_ORDER_RANGE));
	return 1;
}

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::getBondConfigHashSeed(const Bond& bond) const
{
	unsigned int config = getCIPConfiguration(bond);

	switch (config) {

		case BondConfiguration::E:
			return boost::math::prime(BOND_CONFIG_E_IDX);

		case BondConfiguration::Z:
			return boost::math::prime(BOND_CONFIG_Z_IDX);

		default:
			return 1;
	}
}

//-----

Chem::HashCodeCalculator::HashCodeCalculator():
	atomHashSeedFunc(DefAtomHashSeedFunctor(*this)), bondHashSeedFunc(DefBondHashSeedFunctor()),
	incGlobalStereoFeatures(true) 
{
	std::fill(shaHashCode, shaHashCode + sizeof(shaHashCode), 0);
}

Chem::HashCodeCalculator::HashCodeCalculator(const MolecularGraph& molgraph):
	atomHashSeedFunc(DefAtomHashSeedFunctor(*this)), bondHashSeedFunc(DefBondHashSeedFunctor()),
	incGlobalStereoFeatures(true)
{
	std::fill(shaHashCode, shaHashCode + sizeof(shaHashCode), 0);

	calculate(molgraph);
}

void Chem::HashCodeCalculator::includeGlobalStereoFeatures(bool include)
{
	incGlobalStereoFeatures = include;
}

bool Chem::HashCodeCalculator::globalStereoFeaturesIncluded() const
{
	return incGlobalStereoFeatures;
}

std::uint64_t Chem::HashCodeCalculator::calculate(const MolecularGraph& molgraph)
{
	init(molgraph);

	perceiveGlobalStereoFeatures();

	calcAtomHashCodes();
	calcBondHashCodes();
	calcSHAHashCode();

	return getResult();
}

std::uint64_t Chem::HashCodeCalculator::getResult() const
{
	std::uint64_t hash_code = 0;

	for (std::size_t i = 0; i < Internal::SHA1::HASH_SIZE; i++) 
		hash_code = hash_code ^ (std::uint64_t(shaHashCode[i]) << ((i % 8) * 8));

	return hash_code;
}

void Chem::HashCodeCalculator::setAtomHashSeedFunction(const AtomHashSeedFunction& func)
{
	atomHashSeedFunc = func;
}

void Chem::HashCodeCalculator::setBondHashSeedFunction(const BondHashSeedFunction& func)
{
	bondHashSeedFunc = func;
}

void Chem::HashCodeCalculator::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();
	std::size_t num_bonds = molgraph.getNumBonds();

	if (atomHashCodes.size() < num_atoms)
		atomHashCodes.resize(num_atoms); 

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		atomHashCodes[atom_idx] = atomHashSeedFunc(atom);
	}

	if (bondHashCodes.size() < num_bonds)
		bondHashCodes.resize(num_bonds); 

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		std::size_t bond_idx = molgraph.getBondIndex(bond);
		
		bondHashCodes[bond_idx] = bondHashSeedFunc(bond);
	}
}

void Chem::HashCodeCalculator::calcAtomHashCodes()
{
	if (incGlobalStereoFeatures) {
		IndexList::const_iterator global_stereo_atoms_end = globalStereoAtoms.end();

		for (IndexList::const_iterator it = globalStereoAtoms.begin(); it != global_stereo_atoms_end; ++it)
			atomHashCodes[*it] *= boost::math::prime(ATOM_GLOBAL_STEREO_FLAG_IDX);
	}

	MolecularGraph::ConstAtomIterator atoms_beg = molGraph->getAtomsBegin();
	MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();
	
	std::size_t num_atoms = molGraph->getNumAtoms();

	if (tmpHashCodes1.size() < num_atoms)
		tmpHashCodes1.resize(num_atoms);

	for (std::size_t i = 0; i < NUM_ATOM_HASH_ITERATIONS; i++) {
		for (MolecularGraph::ConstAtomIterator it1 = atoms_beg; it1 != atoms_end; ++it1) {
			const Atom& atom = *it1;
			std::size_t atom_idx = molGraph->getAtomIndex(atom);

			tmpHashCodes2.clear();

			Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
			Atom::ConstBondIterator it3 = atom.getBondsBegin();

			for (Atom::ConstAtomIterator it2 = atom.getAtomsBegin(); it2 != nbr_atoms_end; ++it2, ++it3) {
				if (!molGraph->containsAtom(*it2) || !molGraph->containsBond(*it3))
					continue;

				std::size_t nbr_atom_idx = molGraph->getAtomIndex(*it2);

				tmpHashCodes2.push_back(atomHashCodes[nbr_atom_idx]);
			}
			
			UInt64Array::iterator nbr_hash_beg = tmpHashCodes2.begin();
			UInt64Array::iterator nbr_hash_end = tmpHashCodes2.end();

			std::sort(nbr_hash_beg, nbr_hash_end);

			std::uint64_t new_hash_code = atomHashCodes[atom_idx];

			for (UInt64Array::const_iterator it2 = nbr_hash_beg; it2 != nbr_hash_end; ++it2) 
				new_hash_code = (new_hash_code << 1) ^ *it2;

			tmpHashCodes1[atom_idx] = new_hash_code;
		}
		
		atomHashCodes.swap(tmpHashCodes1);
	}
}

void Chem::HashCodeCalculator::calcBondHashCodes()
{
	if (incGlobalStereoFeatures) {
		IndexList::const_iterator global_stereo_bonds_end = globalStereoBonds.end();

		for (IndexList::const_iterator it = globalStereoBonds.begin(); it != global_stereo_bonds_end; ++it)
			bondHashCodes[*it] *= boost::math::prime(BOND_GLOBAL_STEREO_FLAG_IDX);

		IndexList::const_iterator ref_atoms_end = globalStereoReferenceAtoms.end();
		IndexList::const_iterator a_it = globalStereoReferenceAtoms.begin();

		for (IndexList::const_iterator b_it = globalStereoReferenceBonds.begin(); a_it != ref_atoms_end; ++a_it, ++b_it) 
			bondHashCodes[*b_it] += atomHashCodes[*a_it];
	}

	MolecularGraph::ConstBondIterator bonds_beg = molGraph->getBondsBegin();
	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = bonds_beg; it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(bond);

		bondHashCodes[bond_idx] ^= atomHashCodes[molGraph->getAtomIndex(bond.getBegin())] + 
			atomHashCodes[molGraph->getAtomIndex(bond.getEnd())];
	}

	std::size_t num_bonds = molGraph->getNumBonds();

	if (tmpHashCodes1.size() < num_bonds)
		tmpHashCodes1.resize(num_bonds);

	for (std::size_t i = 0; i < NUM_BOND_HASH_ITERATIONS; i++) {
		for (MolecularGraph::ConstBondIterator it1 = bonds_beg; it1 != bonds_end; ++it1) {
			const Bond& bond = *it1;

			if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
				continue;

			std::size_t bond_idx = molGraph->getBondIndex(bond);

			tmpHashCodes2.clear();

			Atom::ConstBondIterator nbr_bonds_end = bond.getBegin().getBondsEnd();
			Atom::ConstAtomIterator a_it = bond.getBegin().getAtomsBegin();

			for (Atom::ConstBondIterator it2 = bond.getBegin().getBondsBegin(); it2 != nbr_bonds_end; ++it2, ++a_it) {
				if (!molGraph->containsBond(*it2) || !molGraph->containsAtom(*a_it))
					continue;

				std::size_t nbr_bond_idx = molGraph->getBondIndex(*it2);

				tmpHashCodes2.push_back(bondHashCodes[nbr_bond_idx]);
			}
			
			nbr_bonds_end = bond.getEnd().getBondsEnd();
			a_it = bond.getEnd().getAtomsBegin();

			for (Atom::ConstBondIterator it2 = bond.getEnd().getBondsBegin(); it2 != nbr_bonds_end; ++it2, ++a_it) {
				if (!molGraph->containsBond(*it2) || !molGraph->containsAtom(*a_it))
					continue;

				std::size_t nbr_bond_idx = molGraph->getBondIndex(*it2);

				tmpHashCodes2.push_back(bondHashCodes[nbr_bond_idx]);
			}
			
			UInt64Array::iterator bnd_hash_beg = tmpHashCodes2.begin();
			UInt64Array::iterator bnd_hash_end = tmpHashCodes2.end();

			std::sort(bnd_hash_beg, bnd_hash_end);

			std::uint64_t new_hash_code = bondHashCodes[bond_idx];

			for (UInt64Array::const_iterator it2 = bnd_hash_beg; it2 != bnd_hash_end; ++it2) 
				new_hash_code = (new_hash_code << 1) ^ *it2;

			tmpHashCodes1[bond_idx] = new_hash_code;
		}

		bondHashCodes.swap(tmpHashCodes1);
	}
}

void Chem::HashCodeCalculator::perceiveGlobalStereoFeatures()
{
	globalStereoAtoms.clear();
	globalStereoReferenceAtoms.clear();

	globalStereoBonds.clear();
	globalStereoReferenceBonds.clear();

	if (!incGlobalStereoFeatures)
		return;

	perceiveGlobalStereoReferenceAtoms();
	perceiveGlobalStereoReferenceBonds();
}

void Chem::HashCodeCalculator::perceiveGlobalStereoReferenceAtoms()
{
	std::for_each(molGraph->getAtomsBegin(), molGraph->getAtomsEnd(),
				  boost::bind(&HashCodeCalculator::perceiveGlobalStereoReferenceAtom, this, _1));
}

void Chem::HashCodeCalculator::perceiveGlobalStereoReferenceAtom(const Atom& atom)
{
	std::size_t num_bonds = atom.getNumBonds();

	if (num_bonds < 3 || num_bonds > 4)
		return;

	const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);

	if (stereo_desc.getNumReferenceAtoms() < 3)
		return;

	unsigned int config = stereo_desc.getConfiguration();

	switch (config) {

		case AtomConfiguration::R:
		case AtomConfiguration::S:
			break;

		default:
			return;
	}

	Ligand ligands[4];

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	num_bonds = 0;

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& nbr_bond = *b_it;

		if (!molGraph->containsAtom(nbr_atom) || !molGraph->containsBond(nbr_bond))
			continue;

		ligands[num_bonds++] = Ligand(&nbr_atom, &nbr_bond);
	}

	if (num_bonds < 3)
		return;

	std::sort(ligands, ligands + num_bonds, AtomCIPPGreaterCmpFunc());

	std::size_t cip_priorities[4];

	for (std::size_t i = 0; i < num_bonds; i++)
		cip_priorities[i] = getCIPPriority(*ligands[i].first);

	std::size_t eq_range_idx = 0;

	if (cip_priorities[0] == cip_priorities[1]) {
		if (cip_priorities[1] == cip_priorities[2] || 
			(num_bonds == 4 && cip_priorities[2] == cip_priorities[3]))
			return; 

	} else if (cip_priorities[1] == cip_priorities[2]) {
		if (num_bonds == 4 && cip_priorities[2] == cip_priorities[3])
			return; 

		eq_range_idx = 1;

	} else if (num_bonds == 4 && cip_priorities[2] == cip_priorities[3])
		eq_range_idx = 2;

	else
		return;
 
	unsigned int perm_parity = (num_bonds == 3 ? stereo_desc.getPermutationParity(*ligands[0].first, *ligands[1].first, *ligands[2].first) :
								stereo_desc.getPermutationParity(*ligands[0].first, *ligands[1].first, *ligands[2].first, *ligands[3].first));
	int sign = 0;

	if (perm_parity == 2) 
		sign = (config == AtomConfiguration::R ? 1 : -1);

	else if (perm_parity == 1) {
		config = (config == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R); 
		sign = (config == AtomConfiguration::R ? -1 : 1);

	} else 
		return;

	const Ligand& ref_ligand = (sign > 0 ? ligands[eq_range_idx] : ligands[eq_range_idx + 1]);

	globalStereoAtoms.push_back(molGraph->getAtomIndex(atom));
	globalStereoReferenceAtoms.push_back(molGraph->getAtomIndex(*ref_ligand.first));
	globalStereoReferenceBonds.push_back(molGraph->getBondIndex(*ref_ligand.second));
}

void Chem::HashCodeCalculator::perceiveGlobalStereoReferenceBonds()
{ 
	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
			continue;

		perceiveGlobalStereoReferenceBond(bond);
	}
}

void Chem::HashCodeCalculator::perceiveGlobalStereoReferenceBond(const Bond& bond)
{ 
	const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);

	if (!stereo_desc.isValid(bond))
		return;

	unsigned int config = stereo_desc.getConfiguration();

	if (config != BondConfiguration::CIS && config != BondConfiguration::TRANS)
		return;

	const Atom* const* sto_ref_atoms = stereo_desc.getReferenceAtoms();

	const Atom* ligand_atoms[2][2] = { { 0, 0 }, { 0, 0 } };
	const Bond* ligand_bonds[2][2] = { { 0, 0 }, { 0, 0 } };

	bool eq_ligand_atoms[2] = { false, false };

	for (std::size_t i = 0; i < 2; i++) {
		Atom::ConstAtomIterator atoms_end = sto_ref_atoms[i + 1]->getAtomsEnd();
		Atom::ConstBondIterator b_it = sto_ref_atoms[i + 1]->getBondsBegin();

		for (Atom::ConstAtomIterator a_it = sto_ref_atoms[i + 1]->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
			const Bond* ligand_bond = &*b_it;

			if (ligand_bond == &bond)
				continue;

			const Atom* ligand_atom = &*a_it;

			if (!molGraph->containsAtom(*ligand_atom) || !molGraph->containsBond(*ligand_bond))
				continue;

			if (!ligand_atoms[i][0]) {
				ligand_atoms[i][0] = ligand_atom;
				ligand_bonds[i][0] = ligand_bond;

			} else {
				std::size_t pri1 = getCIPPriority(*ligand_atoms[i][0]);
				std::size_t pri2 = getCIPPriority(*ligand_atom);

				if (pri1 >= pri2) {
					ligand_atoms[i][1] = ligand_atom;
					ligand_bonds[i][1] = ligand_bond;
					eq_ligand_atoms[i] |= (pri1 == pri2);

				} else {
					ligand_atoms[i][1] = ligand_atoms[i][0];
					ligand_atoms[i][0] = ligand_atom;
					ligand_bonds[i][1] = ligand_bonds[i][0];
					ligand_bonds[i][0] = ligand_bond;
				}
			}
		}
	}

	if (eq_ligand_atoms[0] == eq_ligand_atoms[1])
		return;

	int sign = 0;

	switch (config) {
				
		case BondConfiguration::CIS:
			sign = ((ligand_atoms[0][0] == sto_ref_atoms[0]) ^ (ligand_atoms[1][0] == sto_ref_atoms[3]) ? 1 : -1);
			break;

		case BondConfiguration::TRANS:
			sign = ((ligand_atoms[0][0] == sto_ref_atoms[0]) ^ (ligand_atoms[1][0] == sto_ref_atoms[3]) ? -1 : 1);
			break;

		default:
			return;
	}

	const Atom* ref_atom;
	const Bond* ref_bond;

	if (eq_ligand_atoms[0]) {
		ref_atom = (sign > 0 ? ligand_atoms[0][0] : ligand_atoms[0][1]);   
		ref_bond = (sign > 0 ? ligand_bonds[0][0] : ligand_bonds[0][1]);   

	} else {
		ref_atom = (sign > 0 ? ligand_atoms[1][0] : ligand_atoms[1][1]);   
		ref_bond = (sign > 0 ? ligand_bonds[1][0] : ligand_bonds[1][1]);   
	}

	globalStereoBonds.push_back(molGraph->getBondIndex(bond));
	globalStereoReferenceAtoms.push_back(molGraph->getAtomIndex(*ref_atom));
	globalStereoReferenceBonds.push_back(molGraph->getBondIndex(*ref_bond));
}

void Chem::HashCodeCalculator::calcSHAHashCode()
{
	shaInput.clear();

	MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molGraph->getAtomsBegin(); it != atoms_end; ++it) {
		std::size_t atom_idx = molGraph->getAtomIndex(*it);

		shaInput.push_back(atomHashCodes[atom_idx]);
	}

	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
	
		if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(*it);

		shaInput.push_back(bondHashCodes[bond_idx]);
	}

	std::sort(shaInput.begin(), shaInput.end());

	Internal::SHA1 sha;

	sha.input(shaInput.begin(), shaInput.end());
	sha.getResult(&shaHashCode[0]);
}
