/* 
 * StereoisomerGenerator.cpp 
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

#include <random>
#include <algorithm>

#include "CDPL/Chem/StereoisomerGenerator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL;


void Chem::StereoisomerGenerator::setAtomPredicate(const AtomPredicate& pred)
{
    atomPred = pred;
}

const Chem::AtomPredicate& Chem::StereoisomerGenerator::getAtomPredicate() const
{
    return atomPred;
}

void Chem::StereoisomerGenerator::setBondPredicate(const BondPredicate& pred)
{
    bondPred = pred;
}

const Chem::BondPredicate& Chem::StereoisomerGenerator::getBondPredicate() const
{
    return bondPred;
}

void Chem::StereoisomerGenerator::enumerateAtomConfig(bool enumerate)
{
    enumAtomConfig = enumerate;
}

bool Chem::StereoisomerGenerator::atomConfigEnumerated() const
{
    return enumAtomConfig;
}

void Chem::StereoisomerGenerator::enumerateBondConfig(bool enumerate)
{
    enumBondConfig = enumerate;
}

bool Chem::StereoisomerGenerator::bondConfigEnumerated() const
{
    return enumBondConfig;
}

void Chem::StereoisomerGenerator::includeSpecifiedCenters(bool include)
{
    incSpecifiedCtrs = include;
}

bool Chem::StereoisomerGenerator::specifiedCentersIncluded() const
{
    return incSpecifiedCtrs;
}

void Chem::StereoisomerGenerator::includeSymmetricCenters(bool include)
{
    incSymmetricCtrs = include;
}

bool Chem::StereoisomerGenerator::symmetricCentersIncluded() const
{
    return incSymmetricCtrs;
}

void Chem::StereoisomerGenerator::includeBridgeheadAtoms(bool include)
{
    incBridgeheads = include;
}

bool Chem::StereoisomerGenerator::bridgeheadAtomsIncluded() const
{
    return incBridgeheads;
}

void Chem::StereoisomerGenerator::includeInvertibleNitrogens(bool include)
{
    incInvNitrogens = include;
}

bool Chem::StereoisomerGenerator::invertibleNitrogensIncluded() const
{
    return incInvNitrogens;
}

void Chem::StereoisomerGenerator::includeRingBonds(bool include)
{
    incRingBonds = include;
}

bool Chem::StereoisomerGenerator::ringBondsIncluded() const
{
    return incRingBonds;
}

void Chem::StereoisomerGenerator::setMinRingSize(std::size_t min_size)
{
    minRingSize = min_size;
}

std::size_t Chem::StereoisomerGenerator::getMinRingSize() const
{
    return minRingSize;
}

void Chem::StereoisomerGenerator::setup(const MolecularGraph& molgraph)
{
    atomDescrs.clear();
    bondDescrs.clear();
    procCtrs.clear();

    if (!incBridgeheads)
        findBridgeheadAtoms(molgraph);
    
    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
        const Atom& atom = molgraph.getAtom(i);
        const StereoDescriptor& descr = getStereoDescriptor(atom);

        atomDescrs.addElement(descr);

        if (!enumAtomConfig)
            continue;
        
        switch (descr.getConfiguration()) {

            case AtomConfiguration::R:
            case AtomConfiguration::S:
                if (isExcluded(atom, molgraph, true))
                    continue;
                break;

            case AtomConfiguration::UNDEF:
                if (descr.getNumReferenceAtoms() < 3)
                    continue;
 
            case AtomConfiguration::EITHER:
                if (!isExcluded(atom, molgraph, false)) {
                    atomDescrs.getLastElement().setConfiguration(AtomConfiguration::R);
                    break;
                }
                
            default:
                continue;
        }

        procCtrs.emplace_back(true, i);
    }

    for (std::size_t i = 0, num_bonds = molgraph.getNumBonds(); i < num_bonds; i++) {
        const Bond& bond = molgraph.getBond(i);
        const StereoDescriptor& descr = getStereoDescriptor(bond);

        bondDescrs.addElement(descr);

        if (!enumBondConfig)
            continue;
    
        switch (descr.getConfiguration()) {

            case BondConfiguration::E:
            case BondConfiguration::Z:
                if (isExcluded(bond, molgraph, true))
                    continue;
                break;

            case AtomConfiguration::UNDEF:
                if (descr.getNumReferenceAtoms() != 4)
                    continue;
 
            case BondConfiguration::EITHER:
                if (!isExcluded(bond, molgraph, false)) {
                    bondDescrs.getLastElement().setConfiguration(BondConfiguration::E);
                    break;
                }
                
            default:
                continue;
        }

        procCtrs.emplace_back(false, i);
    }

    flipStates.resize(procCtrs.size());
    flipStates.reset();
    
    std::shuffle(procCtrs.begin(), procCtrs.end(), std::mt19937());
}

bool Chem::StereoisomerGenerator::generate()
{
    for (std::size_t i = 0, num_ctrs = procCtrs.size(); i < num_ctrs; i++) {
        flipConfiguration(procCtrs[i]);
        
        if (flipStates.test(i)) {
            flipStates.reset(i);
            continue;
        }

        flipStates.set(i);
        return true;
    }

    return false;
}

const Chem::StereoisomerGenerator::StereoDescriptorArray& Chem::StereoisomerGenerator::getAtomDescriptors()
{
    return atomDescrs;
}

const Chem::StereoisomerGenerator::StereoDescriptorArray& Chem::StereoisomerGenerator::getBondDescriptors()
{
    return bondDescrs;
}

bool Chem::StereoisomerGenerator::isExcluded(const Atom& atom, const MolecularGraph& molgraph, bool has_config)
{
    if (atomPred)
        return !atomPred(atom);

    if (has_config && !incSpecifiedCtrs)
        return true;
  
    if (!isStereoCenter(atom, molgraph, !incSymmetricCtrs, !incInvNitrogens, !incInvNitrogens))
        return true;

    if (!incBridgeheads && bhAtoms.test(molgraph.getAtomIndex(atom)))
        return true;

    return false;
}

bool Chem::StereoisomerGenerator::isExcluded(const Bond& bond, const MolecularGraph& molgraph, bool has_config) const
{
    if (bondPred)
        return !bondPred(bond);

    if (has_config && !incSpecifiedCtrs)
        return true;

    if (!incRingBonds && getRingFlag(bond))
        return true;
        
    if (!isStereoCenter(bond, molgraph, !incSymmetricCtrs, true, true, minRingSize))
        return true;

    return false;
}

void Chem::StereoisomerGenerator::findBridgeheadAtoms(const MolecularGraph& molgraph)
{
    bhAtoms.resize(molgraph.getNumAtoms());
    bhAtoms.reset();

    for (const auto& atom : molgraph.getAtoms()) {
        if (!getRingFlag(atom))
            continue;

        std::size_t ring_bnd_cnt = Internal::getRingBondCount(atom, molgraph);

        if (ring_bnd_cnt <= 2)
            continue;

        if ((ring_bnd_cnt % 2) == 0 && isSpiroCenter(atom, molgraph))
            continue;
        
        bhAtoms.set(molgraph.getAtomIndex(atom));
    }

    // remove all preliminary bridgehead atoms that are members of simple ring fusion bonds
    
    const FragmentList& sssr = *getSSSR(molgraph);
    std::size_t num_rings = sssr.getSize();
    
    for (Util::BitSet::size_type i = bhAtoms.find_first(); i != Util::BitSet::npos; i = bhAtoms.find_next(i)) {
        const Atom& atom = molgraph.getAtom(i);
     
        atomRingSet.clear();

        for (std::size_t j = 0; j < num_rings; j++)
            if (sssr[j].containsAtom(atom))
                atomRingSet.push_back(j);

        bool is_bh_atom = false;
        
        for (Util::BitSet::size_type j = bhAtoms.find_first(); j != Util::BitSet::npos; j = bhAtoms.find_next(j)) {
            if (i == j)
                continue;
            
            const Atom& other_atom = molgraph.getAtom(j);
            std::size_t shrd_ring_cnt = 0;

            for (std::size_t k : atomRingSet)
                if (sssr[k].containsAtom(other_atom))
                    shrd_ring_cnt++;

            if (shrd_ring_cnt >= 2 && !atom.findBondToAtom(other_atom)) {
                is_bh_atom = true;
                break;
            }
        }

        if (!is_bh_atom)
            bhAtoms.reset(i);
    }
}

bool Chem::StereoisomerGenerator::isSpiroCenter(const Atom& atom, const MolecularGraph& molgraph)
{
    const FragmentList& sssr = *getSSSR(molgraph);

    atomRingSet.clear();

    for (std::size_t i = 0, num_rings = sssr.getSize(); i < num_rings; i++)
        if (sssr[i].containsAtom(atom))
            atomRingSet.push_back(i);

    for (std::size_t i = 0, num_rings = atomRingSet.size(); i < num_rings; i++)
        for (std::size_t j = i + 1; j < num_rings; j++)
            if (haveCommonBond(sssr[i], sssr[j]))
                return false;

    return true;
}

bool Chem::StereoisomerGenerator::haveCommonBond(const BondContainer& ring1, const BondContainer& ring2) const
{
    for (const auto& bond : ring1)
        if (ring2.containsBond(bond))
            return true;

    return false;
}

void Chem::StereoisomerGenerator::flipConfiguration(const StereoCenterID& ctr_id)
{
    if (ctr_id.first) {
        StereoDescriptor& descr = atomDescrs[ctr_id.second];

        descr.setConfiguration(descr.getConfiguration() == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R);

    } else {
        StereoDescriptor& descr = bondDescrs[ctr_id.second];

        descr.setConfiguration(descr.getConfiguration() == BondConfiguration::E ? BondConfiguration::Z : BondConfiguration::E);
    }
}
