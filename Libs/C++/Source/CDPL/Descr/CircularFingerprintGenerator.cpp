/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CircularFingerprintGenerator.cpp 
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

#include "CDPL/Descr/CircularFingerprintGenerator.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/RangeHashCode.hpp"


using namespace CDPL;


const unsigned int Descr::CircularFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Descr::CircularFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS;

//-----

std::uint64_t Descr::CircularFingerprintGenerator::DefAtomIdentifierFunctor::operator()(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const
{
	using namespace Chem;

    std::uint64_t id = 0;

	if (flags & AtomPropertyFlag::ISOTOPE) {
		id = getIsotope(atom);
	}

    if (flags & AtomPropertyFlag::TYPE) {
		id <<= 10;
		id += getType(atom);
    }

    if (flags & AtomPropertyFlag::FORMAL_CHARGE) {
		id <<= 8;

		long charge = getFormalCharge(atom);

		if (charge < 0)
			id += 128 - std::size_t(-charge % 128);
		else
			id += 128 + std::size_t(charge % 128);
    }
 
	std::size_t exp_h_count = ((flags & AtomPropertyFlag::VALENCE) || (flags & AtomPropertyFlag::HEAVY_BOND_COUNT) || (flags & AtomPropertyFlag::H_COUNT) ?
							   MolProp::getExplicitBondCount(atom, molgraph, 1, AtomType::H) : std::size_t(0));

	if (flags & AtomPropertyFlag::VALENCE) {
		id <<= 8;
		id += MolProp::calcExplicitValence(atom, molgraph) - exp_h_count;
    }

	if (flags & AtomPropertyFlag::HEAVY_BOND_COUNT) {
		id <<= 8;
		id += MolProp::getExplicitBondCount(atom, molgraph) - exp_h_count;
    }

	if (flags & AtomPropertyFlag::H_COUNT) {
		id <<= 8;
		id += exp_h_count + calcImplicitHydrogenCount(atom, molgraph);
    }

	if (flags & AtomPropertyFlag::TOPOLOGY) {
		id <<= 1;
		id += getRingFlag(atom);
    }

	if (flags & AtomPropertyFlag::AROMATICITY) {
		id <<= 1;
		id += getAromaticityFlag(atom);
    }

	if (id == 0)
		return ~id;
	
    return id;
}

//-----

std::uint64_t Descr::CircularFingerprintGenerator::DefBondIdentifierFunctor::operator()(const Chem::Bond& bond) const
{
	using namespace Chem;

    std::uint64_t id = 0;

    if (flags & BondPropertyFlag::TOPOLOGY) {
		if (getRingFlag(bond))
			id |= 0x8000;
    }

    if (flags & BondPropertyFlag::AROMATICITY) {
		if (getAromaticityFlag(bond)) {
			id |= 0x4000;
			return id;
		}
    }
	
	if (flags & BondPropertyFlag::ORDER)
		id += getOrder(bond);

	if (id == 0)
		return ~id;
	
    return id;
}

//-----

Descr::CircularFingerprintGenerator::CircularFingerprintGenerator():
    numIterations(2), atomIdentifierFunc(DefAtomIdentifierFunctor()),
	bondIdentifierFunc(DefBondIdentifierFunctor()), incHydrogens(false),
	incChirality(false) {}

Descr::CircularFingerprintGenerator::CircularFingerprintGenerator(const Chem::MolecularGraph& molgraph):
    numIterations(2), atomIdentifierFunc(DefAtomIdentifierFunctor()),
	bondIdentifierFunc(DefBondIdentifierFunctor()), incHydrogens(false),
	incChirality(false)
{
    generate(molgraph);
}

void Descr::CircularFingerprintGenerator::setAtomIdentifierFunction(const AtomIdentifierFunction& func)
{
    atomIdentifierFunc = func;
}

void Descr::CircularFingerprintGenerator::setBondIdentifierFunction(const BondIdentifierFunction& func)
{
    bondIdentifierFunc = func;
}

void Descr::CircularFingerprintGenerator::setNumIterations(std::size_t num_iter)
{
	numIterations = num_iter;
}

std::size_t Descr::CircularFingerprintGenerator::getNumIterations() const
{
	return numIterations;
}

void Descr::CircularFingerprintGenerator::includeHydrogens(bool include)
{
	incHydrogens = include;
}

bool Descr::CircularFingerprintGenerator::hydrogensIncluded() const
{
	return incHydrogens;
}

void Descr::CircularFingerprintGenerator::includeChirality(bool include)
{
	incChirality = include;
}

bool Descr::CircularFingerprintGenerator::chiralityIncluded() const
{
	return incChirality;
}

void Descr::CircularFingerprintGenerator::generate(const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	for (std::size_t i = 0; i < numIterations; )
		performIteration(++i);
}

void Descr::CircularFingerprintGenerator::setFeatureBits(Util::BitSet& bs, bool reset) const
{
	std::size_t bs_size = bs.size();
	
	if (bs_size == 0)
		return;

	if (reset)
		bs.reset();
	
	for (FeaturePtrList::const_iterator it = outputFeatures.begin(), end = outputFeatures.end(); it != end; ++it)
		bs.set((*it)->first % bs_size);
}

void Descr::CircularFingerprintGenerator::setFeatureBits(std::size_t atom_idx, Util::BitSet& bs, bool reset) const
{
	std::size_t bs_size = bs.size();
	
	if (bs_size == 0)
		return;

	if (reset)
		bs.reset();

	if (atom_idx >= (features.size() / (numIterations + 1)))
		throw Base::IndexError("CircularFingerprintGenerator: atom index out of bounds");
	
	for (FeaturePtrList::const_iterator it = outputFeatures.begin(), end = outputFeatures.end(); it != end; ++it)
		if ((*it)->second.test(atom_idx))
			bs.set((*it)->first % bs_size);
}

std::size_t Descr::CircularFingerprintGenerator::getNumFeatures() const
{
	return outputFeatures.size();
}

std::uint64_t Descr::CircularFingerprintGenerator::getFeatureIdentifier(std::size_t ftr_idx) const
{
	if (ftr_idx >= outputFeatures.size())
		throw Base::IndexError("CircularFingerprintGenerator: feature index out of bounds");

	return outputFeatures[ftr_idx]->first;
}

const Util::BitSet& Descr::CircularFingerprintGenerator::getFeatureSubstructure(std::size_t ftr_idx) const
{
	if (ftr_idx >= outputFeatures.size())
		throw Base::IndexError("CircularFingerprintGenerator: feature index out of bounds");

	return outputFeatures[ftr_idx]->second;
}

void Descr::CircularFingerprintGenerator::getFeatureSubstructure(std::size_t ftr_idx, Chem::Fragment& frag, bool clear) const
{
	if (ftr_idx >= outputFeatures.size())
		throw Base::IndexError("CircularFingerprintGenerator: feature index out of bounds");

	if (clear)
		frag.clear();

	bitSetToFragment(outputFeatures[ftr_idx]->second, frag);
}

void Descr::CircularFingerprintGenerator::getFeatureSubstructures(std::size_t bit_idx, std::size_t bs_size, Chem::FragmentList& frags, bool clear) const
{
	using namespace Chem;
	
	if (clear)
		frags.clear();
	
	for (FeaturePtrList::const_iterator it = outputFeatures.begin(), end = outputFeatures.end(); it != end; ++it) {
		const Feature* ftr = *it;

		if ((ftr->first % bs_size) != bit_idx)
			continue;

		Fragment::SharedPointer frag_ptr(new Fragment());

		bitSetToFragment(ftr->second, *frag_ptr);
		frags.addElement(frag_ptr);
	}
}

void Descr::CircularFingerprintGenerator::init(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();
	std::size_t num_bonds = molgraph.getNumBonds();

	features.resize(num_atoms * (numIterations + 1));
	
	outputFeatures.clear();
	outputFeatures.reserve(features.size());

	duplicateMask.resize(num_atoms);
	
	for (std::size_t i = 0; i < num_atoms; i++) {
		Feature& ftr = features[i];
		std::uint64_t id = atomIdentifierFunc(molgraph.getAtom(i), molgraph);

		if (id == 0 || (!incHydrogens && getType(molgraph.getAtom(i)) == AtomType::H)) {
			ftr.first = 0;
			ftr.second.clear();
			continue;
		}

		randGenerator.seed(id);

		ftr.first = randGenerator();
		
		ftr.second.resize(num_bonds + num_atoms);
		ftr.second.reset();
		ftr.second.set(i);

		outputFeatures.push_back(&ftr);
	}

	if (bondIdentifiers.size() < num_bonds)
		bondIdentifiers.resize(num_bonds);

	std::size_t i = 0;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it, i++) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();

		if (!molgraph.containsAtom(atom1))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom2))
			continue;

		bondIdentifiers[i] = bondIdentifierFunc(bond);
	}
}

void Descr::CircularFingerprintGenerator::performIteration(std::size_t iter_num)
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();
		
	for (std::size_t i = 0; i < num_atoms; i++) {
		std::size_t ftr_idx = num_atoms * (iter_num - 1) + i;
		std::size_t ext_ftr_idx = ftr_idx + num_atoms;

		features[ext_ftr_idx].second = features[ftr_idx].second;
				
		if (features[ext_ftr_idx].second.empty())  // to be ignored?
			continue;
		
		neighborData.clear();

		const Atom& ctr_atom = molGraph->getAtom(i);
		Atom::ConstBondIterator b_it = ctr_atom.getBondsBegin();
		
		for (Atom::ConstAtomIterator a_it = ctr_atom.getAtomsBegin(), a_end = ctr_atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Bond& nbr_bond = *b_it;

			if (!molGraph->containsBond(nbr_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molGraph->containsAtom(nbr_atom))
				continue;

			std::size_t nbr_bond_idx = molGraph->getBondIndex(nbr_bond);

			if (bondIdentifiers[nbr_bond_idx] == 0) // to be ignored?
				continue;
			
			const Feature& nbr_ftr = features[num_atoms * (iter_num - 1) + molGraph->getAtomIndex(nbr_atom)];

			if (nbr_ftr.second.empty())  // to be ignored?
				continue;
			
			features[ext_ftr_idx].second |= nbr_ftr.second;

			if (iter_num == 1)
				features[ext_ftr_idx].second.set(num_atoms + nbr_bond_idx);

			neighborData.push_back(NeighborData({ { bondIdentifiers[nbr_bond_idx], nbr_ftr.first }, &nbr_atom }));
		}

		std::sort(neighborData.begin(), neighborData.end(), &compareNeighborData);

		idCalculationData.clear();
		idCalculationData.push_back(iter_num);
		idCalculationData.push_back(features[ftr_idx].first);

		unsigned int stereo_flag = getStereoFlag(ctr_atom);

		if (stereo_flag)
			idCalculationData.push_back(stereo_flag);
		
		for (NeighborDataList::const_iterator it = neighborData.begin(), end = neighborData.end(); it != end; ++it) {
			idCalculationData.push_back(it->first.first);
			idCalculationData.push_back(it->first.second);
		}
		
		features[ext_ftr_idx].first = Internal::calcHashCode<std::uint64_t>(idCalculationData.begin(), idCalculationData.end());
	}

	duplicateMask.reset();
	
	FeaturePtrList::const_iterator prev_of_end = outputFeatures.end();
		
	for (std::size_t i = 0, ftr_offs = num_atoms * iter_num; i < num_atoms; i++) {
		if (duplicateMask.test(i))
			continue;
		
		const Feature* output_ftr = &features[ftr_offs + i];

		if (output_ftr->second.empty())
			continue;
		
		for (std::size_t j = i + 1; j < num_atoms; j++) {
			Feature& ftr = features[ftr_offs + j];
 
			if (ftr.second == output_ftr->second) {
				duplicateMask.set(j);

				if (output_ftr->first > ftr.first)
					output_ftr = &ftr;
			}
		}

		bool duplicate = false;

		for (FeaturePtrList::const_iterator it = outputFeatures.begin(); it != prev_of_end; ++it) {
			if ((*it)->second == output_ftr->second) {
				duplicate = true;
				break;
			}
		}

		if (duplicate)
			continue;
		
		outputFeatures.push_back(output_ftr);
	}
}

unsigned int Descr::CircularFingerprintGenerator::getStereoFlag(const Chem::Atom& ctr_atom) const
{
	using namespace Chem;
	
	if (!incChirality)
		return 0;
	
	std::size_t num_nbrs = neighborData.size();
		
	if (num_nbrs != 3 && num_nbrs != 4)
		return 0;

	const StereoDescriptor& sto_descr = getStereoDescriptor(ctr_atom);
	unsigned int config = sto_descr.getConfiguration();
	
	if (config != AtomConfiguration::R && config != AtomConfiguration::S)
		return 0;

	if (!sto_descr.isValid(ctr_atom))
		return 0;

	if (neighborData[0].first == neighborData[1].first || neighborData[1].first == neighborData[2].first)
		return 0;

	if (num_nbrs == 4 && neighborData[2].first == neighborData[3].first)
		return 0;

	unsigned int parity = 0;

	if (num_nbrs == 4)
		parity = sto_descr.getPermutationParity(*neighborData[0].second, *neighborData[1].second,
												*neighborData[2].second, *neighborData[3].second);
	else
		parity = sto_descr.getPermutationParity(*neighborData[0].second, *neighborData[1].second,
												*neighborData[2].second);
	if (parity == 0)
		return 0;

	if (parity == 1)
		return (config == AtomConfiguration::R ? 1 : 2);

	return (config == AtomConfiguration::R ? 2 : 1);
}
	
void Descr::CircularFingerprintGenerator::bitSetToFragment(const Util::BitSet& ab_mask, Chem::Fragment& frag) const
{
	std::size_t num_atoms = molGraph->getNumAtoms();
	
	for (Util::BitSet::size_type i = ab_mask.find_first(); i != Util::BitSet::npos; i = ab_mask.find_next(i)) {
		if (i < num_atoms)
			frag.addAtom(molGraph->getAtom(i));
		else
			frag.addBond(molGraph->getBond(i - num_atoms));
	}
}

bool Descr::CircularFingerprintGenerator::compareNeighborData(const NeighborData& nbr1, const NeighborData& nbr2)
{
	return (nbr1.first < nbr2.first);
}
