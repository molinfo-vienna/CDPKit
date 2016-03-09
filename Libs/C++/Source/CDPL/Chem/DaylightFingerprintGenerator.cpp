/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DaylightFingerprintGenerator.cpp 
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

#include <cmath>
#include <algorithm>
#include <iterator>

#include <boost/bind.hpp>

#include "CDPL/Chem/DaylightFingerprintGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"


using namespace CDPL;


namespace
{

	//  P. J. Weinberger's hashing function

	Base::uint64 calcPathHashCode(const std::vector<Base::uint64>& path_descr)
	{
		Base::uint64 g;
		Base::uint64 h = 0;

		for (std::vector<Base::uint64>::const_iterator end = path_descr.end(), it = path_descr.begin(); it != end; ++it) {
			h = (h << 4) + *it;

			if ((g = h & 0xf0000000)) 
				h = h ^ (g >> 24) ^ g;
		}

		return h;
	}
}


const unsigned int Chem::DaylightFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::DaylightFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS;

//-----

Base::uint64 Chem::DaylightFingerprintGenerator::DefAtomDescriptorFunctor::operator()(const Atom& atom) const
{
	Base::uint64 descr = 0;

	if (flags & AtomPropertyFlag::ISOTOPE)
		descr = getIsotope(atom);

	if (flags & AtomPropertyFlag::TYPE) {
		descr *= 1024;
		descr += getType(atom);
	}

	if (flags & AtomPropertyFlag::FORMAL_CHARGE) {
		descr *= 100;

		long charge = getFormalCharge(atom);

		if (charge < 0)
			descr += 50 - std::size_t(-charge % 50);
		else
			descr += 50 + std::size_t(charge % 50);
	}

	if (flags & AtomPropertyFlag::AROMATICITY) {
		descr *= 2;
		descr += getAromaticityFlag(atom);
	}

	return descr;
}

//-----

Base::uint64 Chem::DaylightFingerprintGenerator::DefBondDescriptorFunctor::operator()(const Bond& bond) const
{
	Base::uint64 descr = 0;

	if (flags & BondPropertyFlag::TOPOLOGY) {
		if (getRingFlag(bond))
			descr = 1;
	}

	if (flags & BondPropertyFlag::AROMATICITY) {
		descr *= 2;

		if (getAromaticityFlag(bond))
			descr += 1;
	}

	if (flags & BondPropertyFlag::ORDER) {
		descr *= 1024;
		descr += getOrder(bond);
	}

	return descr;
}

//-----

Chem::DaylightFingerprintGenerator::DaylightFingerprintGenerator():
	molGraph(0), numBits(256), minPathLength(0), maxPathLength(5),
	atomDescriptorFunc(DefAtomDescriptorFunctor()), bondDescriptorFunc(DefBondDescriptorFunctor()) {}

Chem::DaylightFingerprintGenerator::DaylightFingerprintGenerator(const MolecularGraph& molgraph, Util::BitSet& fprint):
	molGraph(0), numBits(256), minPathLength(0), maxPathLength(5), 
	atomDescriptorFunc(DefAtomDescriptorFunctor()), bondDescriptorFunc(DefBondDescriptorFunctor())
{
	generate(molgraph, fprint);
}

void Chem::DaylightFingerprintGenerator::setMinPathLength(std::size_t min_length)
{
	minPathLength = min_length;
}

void Chem::DaylightFingerprintGenerator::setMaxPathLength(std::size_t max_length)
{
	maxPathLength = max_length;
}

void Chem::DaylightFingerprintGenerator::setNumBits(std::size_t num_bits)
{
	numBits = num_bits;
}

std::size_t Chem::DaylightFingerprintGenerator::getMinPathLength() const
{
	return minPathLength;
}

std::size_t Chem::DaylightFingerprintGenerator::getMaxPathLength() const
{
	return maxPathLength;
}

std::size_t Chem::DaylightFingerprintGenerator::getNumBits() const
{
	return numBits;
}

void Chem::DaylightFingerprintGenerator::generate(const MolecularGraph& molgraph, Util::BitSet& fprint)
{
	calcFingerprint(molgraph, fprint);	
}

void Chem::DaylightFingerprintGenerator::setAtomDescriptorFunction(const AtomDescriptorFunction& func)
{
	atomDescriptorFunc = func;
}

void Chem::DaylightFingerprintGenerator::setBondDescriptorFunction(const BondDescriptorFunction& func)
{
	bondDescriptorFunc = func;
}

void Chem::DaylightFingerprintGenerator::calcFingerprint(const MolecularGraph& molgraph, Util::BitSet& fprint)
{
	molGraph = &molgraph;

	fprint.resize(numBits);
	fprint.reset();

	std::size_t num_atoms = molgraph.getNumAtoms();

	if (atomDescriptors.size() < num_atoms)
		atomDescriptors.resize(num_atoms);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		atomDescriptors[atom_idx] = atomDescriptorFunc(atom);
	}

	std::size_t num_bonds = molgraph.getNumBonds();

	if (bondDescriptors.size() < num_bonds) {
		bondDescriptors.resize(num_bonds);
		visBondMask.resize(num_bonds);
	}

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom1) || !molgraph.containsAtom(atom2))
			continue;

		std::size_t bond_idx = molgraph.getBondIndex(bond);

		bondDescriptors[bond_idx] = bondDescriptorFunc(bond);
	}

	atomPath.clear();
	bondPath.clear();
	visBondMask.reset();

	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
				  boost::bind(&DaylightFingerprintGenerator::growPath, this, _1, boost::ref(fprint)));
}

void Chem::DaylightFingerprintGenerator::growPath(const Atom& atom, Util::BitSet& fprint)
{
	std::size_t atom_idx = molGraph->getAtomIndex(atom);

	atomPath.push_back(atom_idx);

	std::size_t bond_path_len = bondPath.size();

	if (bond_path_len >= minPathLength)
		fprint.set(calcBitIndex());

	if (bond_path_len < maxPathLength) {
		Atom::ConstAtomIterator nbrs_end = atom.getAtomsEnd();
		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbrs_end; ++a_it, ++b_it) {
			if (!molGraph->containsBond(*b_it) || !molGraph->containsAtom(*a_it))
				continue;

			std::size_t bond_idx = molGraph->getBondIndex(*b_it);

			if (visBondMask.test(bond_idx))
				continue;

			visBondMask.set(bond_idx);
			bondPath.push_back(bond_idx);

			growPath(*a_it, fprint);

			bondPath.pop_back();
			visBondMask.reset(bond_idx);
		}
	}

	atomPath.pop_back();
}

std::size_t Chem::DaylightFingerprintGenerator::calcBitIndex()
{
	std::size_t atom_path_len = atomPath.size();
	std::size_t bond_path_len = bondPath.size();

	fwdPathDescriptor.clear();

	for (std::size_t i = 0; i < atom_path_len; i++) {
		fwdPathDescriptor.push_back(atomDescriptors[atomPath[i]]);

		if (i < bond_path_len)
			fwdPathDescriptor.push_back(bondDescriptors[bondPath[i]]);
	}

	revPathDescriptor.clear();

	std::reverse_copy(fwdPathDescriptor.begin(), fwdPathDescriptor.end(), std::back_inserter(revPathDescriptor));

	Base::uint64 fwd_descr_hash = calcPathHashCode(fwdPathDescriptor);
	Base::uint64 rev_descr_hash = calcPathHashCode(revPathDescriptor);
	boost::uint64_t rand_seed = (fwd_descr_hash < rev_descr_hash ? fwd_descr_hash : rev_descr_hash);

	randGenerator.seed(rand_seed);

	return (std::size_t(std::floor(double(randGenerator()) * numBits / randGenerator.max())) % numBits);
}
