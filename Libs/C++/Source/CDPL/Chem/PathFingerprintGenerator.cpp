/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PathFingerprintGenerator.cpp 
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

#include "CDPL/Chem/PathFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Internal/RangeHashCode.hpp"


using namespace CDPL;


const unsigned int Chem::PathFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::PathFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS;

//-----

Base::uint64 Chem::PathFingerprintGenerator::DefAtomDescriptorFunctor::operator()(const Atom& atom) const
{
	Base::uint64 descr = 0;

	if (flags & AtomPropertyFlag::ISOTOPE)
		descr = getIsotope(atom);

	if (flags & AtomPropertyFlag::TYPE) {
		descr *= 512;
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

Base::uint64 Chem::PathFingerprintGenerator::DefBondDescriptorFunctor::operator()(const Bond& bond) const
{
	Base::uint64 descr = 0;

	if (flags & BondPropertyFlag::TOPOLOGY) {
		if (getRingFlag(bond))
			descr = 0x8000000000000000;
	}

	if (flags & BondPropertyFlag::AROMATICITY) {
		if (getAromaticityFlag(bond)) {
			descr |= 0x4000000000000000;
			return descr;
		}
	}

	if (flags & BondPropertyFlag::ORDER)
		descr += getOrder(bond);
	
	return descr;
}

//-----

Chem::PathFingerprintGenerator::PathFingerprintGenerator():
	molGraph(0), numBits(1024), minPathLength(0), maxPathLength(5),
	atomDescriptorFunc(DefAtomDescriptorFunctor()), bondDescriptorFunc(DefBondDescriptorFunctor()) {}

Chem::PathFingerprintGenerator::PathFingerprintGenerator(const MolecularGraph& molgraph, Util::BitSet& fp):
	molGraph(0), numBits(1024), minPathLength(0), maxPathLength(5), 
	atomDescriptorFunc(DefAtomDescriptorFunctor()), bondDescriptorFunc(DefBondDescriptorFunctor())
{
	generate(molgraph, fp);
}

void Chem::PathFingerprintGenerator::setMinPathLength(std::size_t min_length)
{
	minPathLength = min_length;
}

void Chem::PathFingerprintGenerator::setMaxPathLength(std::size_t max_length)
{
	maxPathLength = max_length;
}

void Chem::PathFingerprintGenerator::setNumBits(std::size_t num_bits)
{
	numBits = num_bits;
}

std::size_t Chem::PathFingerprintGenerator::getMinPathLength() const
{
	return minPathLength;
}

std::size_t Chem::PathFingerprintGenerator::getMaxPathLength() const
{
	return maxPathLength;
}

std::size_t Chem::PathFingerprintGenerator::getNumBits() const
{
	return numBits;
}

void Chem::PathFingerprintGenerator::generate(const MolecularGraph& molgraph, Util::BitSet& fp)
{
	calcFingerprint(molgraph, fp);	
}

void Chem::PathFingerprintGenerator::setAtomDescriptorFunction(const AtomDescriptorFunction& func)
{
	atomDescriptorFunc = func;
}

void Chem::PathFingerprintGenerator::setBondDescriptorFunction(const BondDescriptorFunction& func)
{
	bondDescriptorFunc = func;
}

void Chem::PathFingerprintGenerator::calcFingerprint(const MolecularGraph& molgraph, Util::BitSet& fp)
{
	fp.resize(numBits);

	if (numBits == 0)
		return;

	fp.reset();

	molGraph = &molgraph;

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
				  boost::bind(&PathFingerprintGenerator::growPath, this, _1, boost::ref(fp)));
}

void Chem::PathFingerprintGenerator::growPath(const Atom& atom, Util::BitSet& fp)
{
	std::size_t atom_idx = molGraph->getAtomIndex(atom);

	atomPath.push_back(atom_idx);

	std::size_t bond_path_len = bondPath.size();

	if (bond_path_len >= minPathLength)
		fp.set(calcBitIndex());

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

			growPath(*a_it, fp);

			bondPath.pop_back();
			visBondMask.reset(bond_idx);
		}
	}

	atomPath.pop_back();
}

std::size_t Chem::PathFingerprintGenerator::calcBitIndex()
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

	Base::uint64 fwd_descr_hash = Internal::calcHashCode<Base::uint64>(fwdPathDescriptor.begin(), fwdPathDescriptor.end());
	Base::uint64 rev_descr_hash = Internal::calcHashCode<Base::uint64>(revPathDescriptor.begin(), revPathDescriptor.end());
	boost::uint64_t rand_seed = (fwd_descr_hash < rev_descr_hash ? fwd_descr_hash : rev_descr_hash);

	randGenerator.seed(rand_seed);

	return std::size_t((double(randGenerator()) / randGenerator.max()) * (numBits - 1));
}
