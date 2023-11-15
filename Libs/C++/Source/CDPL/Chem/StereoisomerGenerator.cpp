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
#include "CDPL/Chem/AtomType.hpp"
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

void Chem::StereoisomerGenerator::includeNitrogens(bool include)
{
    incNitrogens = include;
}

bool Chem::StereoisomerGenerator::nitrogensIncluded() const
{
    return incNitrogens;
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
            case AtomConfiguration::EITHER:
                if (!isExcluded(atom, molgraph, false))
                    break;

            default:
                continue;
        }

        atomDescrs.getLastElement().setConfiguration(AtomConfiguration::R);
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

            case BondConfiguration::UNDEF:
            case BondConfiguration::EITHER:
                if (!isExcluded(bond, molgraph, false))
                    break;

            default:
                continue;
        }

        bondDescrs.getLastElement().setConfiguration(BondConfiguration::E);
        procCtrs.emplace_back(false, i);
    }

    std::shuffle(procCtrs.begin(), procCtrs.end(), std::mt19937());
}

bool Chem::StereoisomerGenerator::generate()
{
    for (const auto& ctr_id : procCtrs) {
        if (ctr_id.first) {
            StereoDescriptor& descr = atomDescrs[ctr_id.second];

            if (descr.getConfiguration() == AtomConfiguration::R) {
                descr.setConfiguration(AtomConfiguration::S);
                return true;
            }

            descr.setConfiguration(AtomConfiguration::R);
            
        } else {
            StereoDescriptor& descr = bondDescrs[ctr_id.second];

            if (descr.getConfiguration() == BondConfiguration::E) {
                descr.setConfiguration(BondConfiguration::Z);
                return true;
            }

            descr.setConfiguration(BondConfiguration::E);
        }
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

    if (!incNitrogens && getType(atom) == AtomType::N)
        return true;

    if (!incBridgeheads && isBridgehead(atom, molgraph))
        return true;

    if (!incSymmetricCtrs && !isStereoCenter(atom, molgraph, true, false))
        return true;

    return false;
}

bool Chem::StereoisomerGenerator::isExcluded(const Bond& bond, const MolecularGraph& molgraph, bool has_config)
{
    if (bondPred)
        return !bondPred(bond);

    if (has_config && !incSpecifiedCtrs)
        return true;

    if (getRingFlag(bond)) {
        if (!incRingBonds)
            return true;

        if (minRingSize > 0 && getSizeOfSmallestContainingFragment(bond, *getSSSR(molgraph)) < minRingSize)
            return true;

        if (!incBridgeheads && (isBridgehead(bond.getBegin(), molgraph) || isBridgehead(bond.getEnd(), molgraph)))
            return true;
    }

    if (!incSymmetricCtrs && !isStereoCenter(bond, molgraph, true, 0))
        return true;

    return false;
}

bool Chem::StereoisomerGenerator::isBridgehead(const Atom& atom, const MolecularGraph& molgraph)
{
    if (!getRingFlag(atom))
        return false;
    
    std::size_t ring_bnd_cnt = Internal::getRingBondCount(atom, molgraph);

    if (ring_bnd_cnt <= 2)
        return false;

    if (ring_bnd_cnt % 2)
        return true;

    // check for spiro center

    const FragmentList& sssr = *getSSSR(molgraph);

    atomRingSet.clear();

    for (std::size_t i = 0, num_rings = sssr.getSize(); i < num_rings; i++)
        if (sssr[i].containsAtom(atom))
            atomRingSet.push_back(i);

    for (std::size_t i = 0, num_rings = atomRingSet.size(); i < num_rings; i++)
        for (std::size_t j = i + 1; j < num_rings; j++)
            if (haveCommonBond(sssr[i], sssr[j]))
                return true;

    return false;
}

bool Chem::StereoisomerGenerator::haveCommonBond(const BondContainer& ring1, const BondContainer& ring2) const
{
    for (const auto& bond : ring1)
        if (ring2.containsBond(bond))
            return true;

    return false;
}
