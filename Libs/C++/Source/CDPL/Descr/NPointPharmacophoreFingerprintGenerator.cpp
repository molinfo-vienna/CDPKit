/* 
 * NPointPharmacophoreFingerprintGenerator.cpp 
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

#include "CDPL/Descr/NPointPharmacophoreFingerprintGenerator.hpp"


using namespace CDPL;


constexpr std::size_t Descr::NPointPharmacophoreFingerprintGenerator::DEF_MIN_FEATURE_TUPLE_SIZE;
constexpr std::size_t Descr::NPointPharmacophoreFingerprintGenerator::DEF_MAX_FEATURE_TUPLE_SIZE;
constexpr double      Descr::NPointPharmacophoreFingerprintGenerator::DEF_BIN_SIZE;


Descr::NPointPharmacophoreFingerprintGenerator::NPointPharmacophoreFingerprintGenerator():
    minFtrTupleSize(DEF_MIN_FEATURE_TUPLE_SIZE), maxFtrTupleSize(DEF_MAX_FEATURE_TUPLE_SIZE),
    binSize(DEF_BIN_SIZE)
{}

void Descr::NPointPharmacophoreFingerprintGenerator::setMinFeatureTupleSize(std::size_t min_size)
{
    minFtrTupleSize = min_size;
}

std::size_t Descr::NPointPharmacophoreFingerprintGenerator::getMinFeatureTupleSize() const
{
    return minFtrTupleSize;
}
            
void Descr::NPointPharmacophoreFingerprintGenerator::setMaxFeatureTupleSize(std::size_t max_size)
{
    maxFtrTupleSize = max_size;
}

std::size_t Descr::NPointPharmacophoreFingerprintGenerator::getMaxFeatureTupleSize() const
{
    return maxFtrTupleSize;
}

void Descr::NPointPharmacophoreFingerprintGenerator::setBinSize(double bin_size)
{
    binSize = binSize;
}

double Descr::NPointPharmacophoreFingerprintGenerator::getBinSize() const
{
    return binSize;
}
            
void Descr::NPointPharmacophoreFingerprintGenerator::generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    pharmGen.generate(molgraph, pharm);

    generate(pharm, fp);
}

void Descr::NPointPharmacophoreFingerprintGenerator::generate(const Pharm::FeatureContainer& cntnr, Util::BitSet& fp)
{
    // TODO
}

Pharm::PharmacophoreGenerator& Descr::NPointPharmacophoreFingerprintGenerator::getPharmacophoreGenerator()
{
    return pharmGen;
}

const Pharm::PharmacophoreGenerator& Descr::NPointPharmacophoreFingerprintGenerator::getPharmacophoreGenerator() const
{
    return pharmGen;
}
