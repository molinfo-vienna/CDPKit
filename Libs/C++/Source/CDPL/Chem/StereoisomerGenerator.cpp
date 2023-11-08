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

void Chem::StereoisomerGenerator::setup(const MolecularGraph& molgraph)
{
    // TODO
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
