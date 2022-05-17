/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CircularFingerprintGenerator.cpp 
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

#include <cmath>
#include <algorithm>
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/CircularFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/RangeHashCode.hpp"


using namespace CDPL;


struct Chem::CircularFingerprintGenerator::UInt64PairLessCmpFunc : 
	public std::binary_function<Chem::CircularFingerprintGenerator::UInt64Pair, Chem::CircularFingerprintGenerator::UInt64Pair, bool>
{

	bool operator()(const UInt64Pair& p1, const UInt64Pair& p2) const {
		if (p1.first == p2.first)
			return (p1.second < p2.second);

		return (p1.first < p2.first);
	}
};


const unsigned int Chem::CircularFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::CircularFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS;

//-----

Base::uint64 Chem::CircularFingerprintGenerator::DefAtomIdentifierFunctor::operator()(const Atom& atom, const MolecularGraph& molgraph) const
{
    Base::uint64 id = 0;

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
							   getExplicitAtomCount(atom, molgraph, AtomType::H, true) : std::size_t(0));

	if (flags & AtomPropertyFlag::VALENCE) {
		id <<= 8;
		id += calcExplicitValence(atom, molgraph) - exp_h_count;
    }

	if (flags & AtomPropertyFlag::HEAVY_BOND_COUNT) {
		id <<= 8;
		id += getExplicitBondCount(atom, molgraph) - exp_h_count;
    }

	if (flags & AtomPropertyFlag::H_COUNT) {
		id <<= 8;
		id += exp_h_count + calcImplicitHydrogenCount(atom, molgraph);
    }

	if (flags & AtomPropertyFlag::TOPOLOGY) {
		id <<= 1;
		id += getRingFlag(atom);
    }

	if (flags & AtomPropertyFlag::CIP_CONFIGURATION) {
		id <<= 2;

		unsigned int config = getCIPConfiguration(atom);

		switch (config) {

			case AtomConfiguration::R: 
				id += 1;
				break;
				
			case AtomConfiguration::S: 
				id += 2;

			default:
				break;
		}
    }

    return id;
}

//-----

Base::uint64 Chem::CircularFingerprintGenerator::DefBondIdentifierFunctor::operator()(const Bond& bond) const
{
    Base::uint64 id = 0;

	if (flags & BondPropertyFlag::CIP_CONFIGURATION) {
		unsigned int config = getCIPConfiguration(bond);

		switch (config) {

			case BondConfiguration::E: 
				id = 0x10000;
				break;
				
			case BondConfiguration::Z: 
				id += 0x20000;

			default:
				break;
		}
    }

    if (flags & BondPropertyFlag::TOPOLOGY) {
		if (getRingFlag(bond))
			id += 0x8000;
    }

    if (flags & BondPropertyFlag::AROMATICITY) {
		if (getAromaticityFlag(bond)) {
			id |= 0x4000;
			return id;
		}
    }

    if (flags & BondPropertyFlag::ORDER)
		id += getOrder(bond);
	
    return id;
}

//-----

Chem::CircularFingerprintGenerator::CircularFingerprintGenerator():
    numBits(1024), numIterations(2), remDuplicates(true),
    atomIdentifierFunc(DefAtomIdentifierFunctor()), bondIdentifierFunc(DefBondIdentifierFunctor()) {}

Chem::CircularFingerprintGenerator::CircularFingerprintGenerator(const MolecularGraph& molgraph, Util::BitSet& fp):
    numBits(1024), numIterations(2), remDuplicates(true),
    atomIdentifierFunc(DefAtomIdentifierFunctor()), bondIdentifierFunc(DefBondIdentifierFunctor())
{
    generate(molgraph, fp);
}

void Chem::CircularFingerprintGenerator::setNumBits(std::size_t num_bits)
{
    numBits = num_bits;
}

std::size_t Chem::CircularFingerprintGenerator::getNumBits() const
{
    return numBits;
}

void Chem::CircularFingerprintGenerator::setAtomIdentifierFunction(const AtomIdentifierFunction& func)
{
    atomIdentifierFunc = func;
}

void Chem::CircularFingerprintGenerator::setBondIdentifierFunction(const BondIdentifierFunction& func)
{
    bondIdentifierFunc = func;
}

void Chem::CircularFingerprintGenerator::setNumIterations(std::size_t num_iter)
{
	numIterations = num_iter;
}

std::size_t Chem::CircularFingerprintGenerator::getNumIterations() const
{
	return numIterations;
}

void Chem::CircularFingerprintGenerator::removeDuplicates(bool remove)
{
	remDuplicates = remove;
}

bool Chem::CircularFingerprintGenerator::duplicatesRemoved() const
{
	return remDuplicates;
}

std::size_t Chem::CircularFingerprintGenerator::getNumFeatures() const
{
	return fingerprintSet.size();
}

Base::uint64 Chem::CircularFingerprintGenerator::getFeatureIdentifier(std::size_t idx) const
{
	if (idx >= fingerprintSet.size())
		throw Base::IndexError("CircularFingerprintGenerator: feature index out of bounds");

	return fingerprintSet[idx].first;
}

const Util::BitSet& Chem::CircularFingerprintGenerator::getFeatureSubstructure(std::size_t idx) const
{
	if (idx >= fingerprintSet.size())
		throw Base::IndexError("CircularFingerprintGenerator: feature index out of bounds");

	return fingerprintSet[idx].second;
}

void Chem::CircularFingerprintGenerator::generate(const MolecularGraph& molgraph, Util::BitSet& fp)
{
    generateFingerprintSet(molgraph);	
	setFeatureBits(fp);
}

void Chem::CircularFingerprintGenerator::generate(const MolecularGraph& molgraph)
{
    generateFingerprintSet(molgraph);	
}

void Chem::CircularFingerprintGenerator::generateFingerprintSet(const MolecularGraph& molgraph)
{
	init(molgraph);

	for (std::size_t i = 0; i < numIterations; )
		performIteration(++i);
}

void Chem::CircularFingerprintGenerator::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();

	features.clear();
	features.reserve(num_atoms);

	fingerprintSet.clear();
	fingerprintSet.reserve(num_atoms * (numIterations + 1));

	std::size_t num_bonds = molgraph.getNumBonds();

	if (bondIdentifiers.size() < num_bonds)
		bondIdentifiers.resize(num_bonds);
	
	bondSet.resize(num_bonds);

	FingerprintSetEntry fp_entry;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		fp_entry.first = atomIdentifierFunc(atom, molgraph);

		features.push_back(fp_entry.first);
		fingerprintSet.push_back(fp_entry);
	}

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

		std::size_t atom1_idx = molgraph.getAtomIndex(atom1);
		std::size_t atom2_idx = molgraph.getAtomIndex(atom2);

		features[atom1_idx].addNeighbor(i, atom2_idx);
		features[atom2_idx].addNeighbor(i, atom1_idx);
	}
}

void Chem::CircularFingerprintGenerator::performIteration(std::size_t iter_num)
{
	extendFeatures(iter_num);
	emitFingerprintSetEntries();
}

void Chem::CircularFingerprintGenerator::extendFeatures(std::size_t iter_num)
{
	std::for_each(features.begin(), features.end(), boost::bind(&CircularFingerprintGenerator::extendFeature, this, iter_num, _1));
	std::for_each(features.begin(), features.end(), boost::bind(&Feature::update, _1));
}

void Chem::CircularFingerprintGenerator::extendFeature(std::size_t iter_num, Feature& feature)
{
	const Feature::NeighborList& nbrs = feature.getNeighborList();

	nbrFeatureData.clear();

	if (iter_num > 1)
		bondSet = feature.getBondSet();
	else
		bondSet.reset();	

	for (Feature::NeighborList::const_iterator it = nbrs.begin(), end = nbrs.end(); it != end; ++it) {
		const Feature::NeighborData& nbr_data = *it;
		const Feature& nbr_ftr = features[nbr_data.second];

		if (iter_num > 1)
			bondSet |= nbr_ftr.getBondSet();
		else
			bondSet.set(nbr_data.first);

		nbrFeatureData.push_back(UInt64Pair(bondIdentifiers[nbr_data.first], nbr_ftr.getID()));
	}

	std::sort(nbrFeatureData.begin(), nbrFeatureData.end(), UInt64PairLessCmpFunc());

	idCalculationData.clear();
	idCalculationData.push_back(iter_num);
	idCalculationData.push_back(feature.getID());

	for (UInt64PairArray::const_iterator it = nbrFeatureData.begin(), end = nbrFeatureData.end(); it != end; ++it) {
		idCalculationData.push_back(it->first);
		idCalculationData.push_back(it->second);
	}

	feature.setNextID(Internal::calcHashCode<Base::uint64>(idCalculationData.begin(), idCalculationData.end()));
	feature.setNextBondSet(bondSet);
}

void Chem::CircularFingerprintGenerator::setFeatureBits(Util::BitSet& fp)
{
	fp.resize(numBits);

	if (numBits == 0)
		return;

	fp.reset();

	for (FingerprintSet::const_iterator it = fingerprintSet.begin(), end = fingerprintSet.end(); it != end; ++it)
		fp.set(it->first % numBits);
}

void Chem::CircularFingerprintGenerator::emitFingerprintSetEntries()
{
	if (remDuplicates)
		std::for_each(features.begin(), features.end(), boost::bind(&Feature::setDuplicateFlag, _1, false));

	for (FeatureList::iterator it1 = features.begin(), end = features.end(); it1 != end; ++it1) {
		const Feature& ftr = *it1;

		if (remDuplicates && ftr.isDuplicate())
			continue;

		Base::uint64 ftr_id = ftr.getID();

		if (remDuplicates) {
			const Util::BitSet& bond_set = ftr.getBondSet();

			for (FeatureList::iterator it2 = it1 + 1; it2 != end; ++it2) {
				Feature& ftr2 = *it2;
 
				if (ftr2.getBondSet() == bond_set) {
					ftr2.setDuplicateFlag(true);

					ftr_id = std::min(ftr_id, ftr2.getID());
				}
			}

			if (fingerprintSetContainsSubstruct(bond_set))
				continue;
		}

		fingerprintSet.resize(fingerprintSet.size() + 1);

		fingerprintSet.back().first = ftr_id;

		if (remDuplicates)
			fingerprintSet.back().second = ftr.getBondSet();
	}
}

bool Chem::CircularFingerprintGenerator::fingerprintSetContainsSubstruct(const Util::BitSet& bs) const
{
	return (std::find_if(fingerprintSet.begin(), fingerprintSet.end(), 
						 boost::bind(std::equal_to<Util::BitSet>(), boost::ref(bs),
									 boost::bind(&FingerprintSetEntry::second, _1))) != fingerprintSet.end());
}

//--------

void Chem::CircularFingerprintGenerator::Feature::addNeighbor(std::size_t bond_idx, std::size_t nbr_idx)
{
	nbrList.push_back(NeighborData(bond_idx, nbr_idx));
}

const Chem::CircularFingerprintGenerator::Feature::NeighborList& Chem::CircularFingerprintGenerator::Feature::getNeighborList() const
{
	return nbrList;
}

void Chem::CircularFingerprintGenerator::Feature::update()
{
	currentID = nextID;
	currentBondSet.swap(nextBondSet);
}

Base::uint64 Chem::CircularFingerprintGenerator::Feature::getID() const
{
	return currentID;
}

const Util::BitSet& Chem::CircularFingerprintGenerator::Feature::getBondSet() const
{
	return currentBondSet;
}

void Chem::CircularFingerprintGenerator::Feature::setNextID(Base::uint64 next_id)
{
	nextID = next_id;
}

void Chem::CircularFingerprintGenerator::Feature::setNextBondSet(const Util::BitSet& bond_set)
{
	nextBondSet = bond_set;
}

void Chem::CircularFingerprintGenerator::Feature::setDuplicateFlag(bool flag)
{
	duplicate = flag;
}

bool Chem::CircularFingerprintGenerator::Feature::isDuplicate() const
{
	return duplicate;
}
