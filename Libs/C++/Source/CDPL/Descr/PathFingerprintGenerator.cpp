/* 
 * PathFingerprintGenerator.cpp 
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

#include <cmath>
#include <algorithm>
#include <iterator>

#include "CDPL/Descr/PathFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/RangeHashCode.hpp"


using namespace CDPL;


constexpr unsigned int Descr::PathFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS;
constexpr unsigned int Descr::PathFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS;

//-----

std::uint64_t Descr::PathFingerprintGenerator::DefAtomDescriptorFunctor::operator()(const Chem::Atom& atom) const
{
    using namespace Chem;

    std::uint64_t descr = 0;

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

std::uint64_t Descr::PathFingerprintGenerator::DefBondDescriptorFunctor::operator()(const Chem::Bond& bond) const
{
    using namespace Chem;

    std::uint64_t descr = 0;

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

Descr::PathFingerprintGenerator::PathFingerprintGenerator():
    molGraph(0), minPathLength(0), maxPathLength(5), incHydrogens(false),
    atomDescriptorFunc(DefAtomDescriptorFunctor()), bondDescriptorFunc(DefBondDescriptorFunctor()) {}

Descr::PathFingerprintGenerator::PathFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp):
    molGraph(0), minPathLength(0), maxPathLength(5), incHydrogens(false), 
    atomDescriptorFunc(DefAtomDescriptorFunctor()), bondDescriptorFunc(DefBondDescriptorFunctor())
{
    generate(molgraph, fp);
}

void Descr::PathFingerprintGenerator::setMinPathLength(std::size_t min_length)
{
    minPathLength = min_length;
}

void Descr::PathFingerprintGenerator::setMaxPathLength(std::size_t max_length)
{
    maxPathLength = max_length;
}

std::size_t Descr::PathFingerprintGenerator::getMinPathLength() const
{
    return minPathLength;
}

std::size_t Descr::PathFingerprintGenerator::getMaxPathLength() const
{
    return maxPathLength;
}

void Descr::PathFingerprintGenerator::includeHydrogens(bool include)
{
    incHydrogens = include;
}

bool Descr::PathFingerprintGenerator::hydrogensIncluded() const
{
    return incHydrogens;
}

void Descr::PathFingerprintGenerator::generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    calcFingerprint(molgraph, fp);    
}

void Descr::PathFingerprintGenerator::setAtomDescriptorFunction(const AtomDescriptorFunction& func)
{
    atomDescriptorFunc = func;
}

void Descr::PathFingerprintGenerator::setBondDescriptorFunction(const BondDescriptorFunction& func)
{
    bondDescriptorFunc = func;
}

void Descr::PathFingerprintGenerator::calcFingerprint(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    using namespace Chem;

    if (fp.size() == 0)
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

    for (auto& atom : molgraph.getAtoms())
        growPath(atom, fp);
}

void Descr::PathFingerprintGenerator::growPath(const Chem::Atom& atom, Util::BitSet& fp)
{
    using namespace Chem;

    if (!incHydrogens && (getType(atom) == Chem::AtomType::H))
        return;
    
    std::size_t atom_idx = molGraph->getAtomIndex(atom);

    atomPath.push_back(atom_idx);

    std::size_t bond_path_len = bondPath.size();

    if (bond_path_len >= minPathLength)
        fp.set(calcBitIndex(fp));

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

std::size_t Descr::PathFingerprintGenerator::calcBitIndex(const Util::BitSet& fp)
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

    std::uint64_t fwd_descr_hash = Internal::calcHashCode<std::uint64_t>(fwdPathDescriptor.begin(), fwdPathDescriptor.end());
    std::uint64_t rev_descr_hash = Internal::calcHashCode<std::uint64_t>(revPathDescriptor.begin(), revPathDescriptor.end());
    boost::uint64_t rand_seed = (fwd_descr_hash < rev_descr_hash ? fwd_descr_hash : rev_descr_hash);

    randGenerator.seed(rand_seed);

    return std::size_t((double(randGenerator()) / randGenerator.max()) * (fp.size() - 1));
}
