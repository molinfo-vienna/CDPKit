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

void Chem::StereoisomerGenerator::enumerateAtomCenters(bool enumerate)
{
    enumAtomCtrs = enumerate;
}

bool Chem::StereoisomerGenerator::atomCentersEnumerated() const
{
    return enumAtomCtrs;
}

void Chem::StereoisomerGenerator::enumerateBondCenters(bool enumerate)
{
    enumBondCtrs = enumerate;
}

bool Chem::StereoisomerGenerator::bondCentersEnumerated() const
{
    return enumBondCtrs;
}

void Chem::StereoisomerGenerator::enumerateSpecifiedCenters(bool enumerate)
{
    enumSpecifiedCtrs = enumerate;
}

bool Chem::StereoisomerGenerator::specifiedCentersEnumerated() const
{
    return enumSpecifiedCtrs;
}

void Chem::StereoisomerGenerator::enumerateSymmetricCenters(bool enumerate)
{
    enumSymmetricCtrs = enumerate;
}

bool Chem::StereoisomerGenerator::symmetricCentersEnumerated() const
{
    return enumSymmetricCtrs;
}

void Chem::StereoisomerGenerator::excludeBridgeheadAtoms(bool exclude)
{
    exclBridgeheads = exclude;
}

bool Chem::StereoisomerGenerator::bridgeheadAtomsExcluded() const
{
    return exclBridgeheads;
}

void Chem::StereoisomerGenerator::excludeNitrogens(bool exclude)
{
    exclNitrogens = exclude;
}

bool Chem::StereoisomerGenerator::nitrogensExcluded() const
{
    return exclNitrogens;
}

void Chem::StereoisomerGenerator::excludeRingBonds(bool exclude)
{
    exclRingBonds = exclude;
}

bool Chem::StereoisomerGenerator::ringBondsExcluded() const
{
    return exclRingBonds;
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
    atomCtrs.clear();
    bondDescrs.clear();
    bondCtrs.clear();

    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
        const Atom& atom = molgraph.getAtom(i);
        const StereoDescriptor& descr = getStereoDescriptor(atom);

        atomDescrs.addElement(descr);

        switch (descr.getConfiguration()) {

            case AtomConfiguration::R:
            case AtomConfiguration::S:
                if (isExcluded(atom, molgraph, true))
                    continue;
                break;

            case AtomConfiguration::UNDEF:
                if (!isExcluded(atom, molgraph, false))
                    break;

            default:
                continue;
        }

        atomDescrs.getLastElement().setConfiguration(AtomConfiguration::R);
        atomCtrs.push_back(i);
    }

    for (std::size_t i = 0, num_bonds = molgraph.getNumBonds(); i < num_bonds; i++) {
        const Bond& bond = molgraph.getBond(i);
        const StereoDescriptor& descr = getStereoDescriptor(bond);

        bondDescrs.addElement(descr);

        switch (descr.getConfiguration()) {

            case BondConfiguration::E:
            case BondConfiguration::Z:
                if (isExcluded(bond, molgraph, true))
                    continue;
                break;

            case BondConfiguration::UNDEF:
                if (!isExcluded(bond, molgraph, false))
                    break;

            default:
                continue;
        }

        bondDescrs.getLastElement().setConfiguration(BondConfiguration::E);
        bondCtrs.push_back(i);
    }
}

bool Chem::StereoisomerGenerator::generate()
{
    // TODO
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

    if (has_config && !enumSpecifiedCtrs)
        return true;

    if (exclNitrogens && getType(atom) == AtomType::N)
        return true;

    if (exclBridgeheads && isBridgehead(atom, molgraph))
        return true;

    if (!enumSymmetricCtrs && !isStereoCenter(atom, molgraph, true, false))
        return true;

    return false;
}

bool Chem::StereoisomerGenerator::isExcluded(const Bond& bond, const MolecularGraph& molgraph, bool has_config) const
{
    if (bondPred)
        return !bondPred(bond);

    if (has_config && !enumSpecifiedCtrs)
        return true;

    if (getRingFlag(bond)) {
        if (exclRingBonds)
            return true;

        if (minRingSize > 0 && getSizeOfSmallestContainingFragment(bond, *getSSSR(molgraph)) < minRingSize)
            return true;
    }

    if (!enumSymmetricCtrs && !isStereoCenter(bond, molgraph, true, 0))
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

    // check for (pure) spiro center

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
    for (const auto& b : ring1)
        if (ring2.containsBond(b))
            return true;

    return false;
}
