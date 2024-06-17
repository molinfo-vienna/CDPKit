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

#include <cmath>
#include <algorithm>

#include "CDPL/Descr/NPointPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Internal/Permutation.hpp"
#include "CDPL/Internal/SHA1.hpp"


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
    auto num_bits = fp.size();

    if (num_bits == 0)
        return;

    fp.reset();
    
    init(cntnr);
    enumFeatureTuples(0, cntnr, fp);
}

Pharm::PharmacophoreGenerator& Descr::NPointPharmacophoreFingerprintGenerator::getPharmacophoreGenerator()
{
    return pharmGen;
}

const Pharm::PharmacophoreGenerator& Descr::NPointPharmacophoreFingerprintGenerator::getPharmacophoreGenerator() const
{
    return pharmGen;
}

void Descr::NPointPharmacophoreFingerprintGenerator::init(const Pharm::FeatureContainer& cntnr)
{
    auto num_ftrs = cntnr.getNumFeatures();

    ftrDistMatrix.resize(num_ftrs, num_ftrs, false);

    for (std::size_t i = 0; i < num_ftrs; i++) {
        auto& ftr1 = cntnr.getFeature(i);
        
        ftrDistMatrix(i, i) = getDistanceBinNumber(0);
        
        for (std::size_t j = i + 1; j < num_ftrs; j++) {
            auto dist = getDistanceBinNumber(getDistance(ftr1, cntnr.getFeature(j)));

            ftrDistMatrix(i, j) = dist;
            ftrDistMatrix(j, i) = dist;
        }
    }

    ftrTuple.clear();
}

void Descr::NPointPharmacophoreFingerprintGenerator::enumFeatureTuples(std::size_t curr_ftr_idx, const Pharm::FeatureContainer& cntnr, Util::BitSet& fp)
{
    if (ftrTuple.size() >= maxFtrTupleSize)
        return;
     
    for (auto i = curr_ftr_idx, num_ftrs = cntnr.getNumFeatures(); i < num_ftrs; i++) {
        ftrTuple.emplace_back(getType(cntnr.getFeature(i)), i);

        if (ftrTuple.size() >= minFtrTupleSize)
            emitFeatureTupleBit(fp);

        enumFeatureTuples(i + 1, cntnr, fp);

        ftrTuple.pop_back();
    }
}

void Descr::NPointPharmacophoreFingerprintGenerator::emitFeatureTupleBit(Util::BitSet& fp)
{
    ftrTupleData.clear();
    tmpFtrTuple = ftrTuple;

    std::sort(tmpFtrTuple.begin(), tmpFtrTuple.end(),
              [](const FeatureID& ftr1, const FeatureID& ftr2) {
                  return (ftr1.first < ftr2.first);
              });
        
    switch (tmpFtrTuple.size()) {

        case 2:
            ftrTupleData.push_back(ftrDistMatrix(tmpFtrTuple[0].second, tmpFtrTuple[1].second));

        case 0:
        case 1:
            break;
            
        default:
            canonFeatureTupleData(0);
    }

    for (auto& ftr_id : tmpFtrTuple)
        ftrTupleData.push_back(ftr_id.first);

    Internal::SHA1 sha;
    std::uint8_t sha_hash[Internal::SHA1::HASH_SIZE];

    sha.input(ftrTupleData.begin(), ftrTupleData.end());
    sha.getResult(sha_hash);

    std::uint64_t hash_code = 0;

    for (std::size_t i = 0; i < Internal::SHA1::HASH_SIZE; i++) 
        hash_code = hash_code ^ (std::uint64_t(sha_hash[i]) << ((i % 8) * 8));

    fp.set(hash_code % fp.size());
}

void Descr::NPointPharmacophoreFingerprintGenerator::canonFeatureTupleData(std::size_t curr_ftr_idx)
{
    auto num_ftrs = tmpFtrTuple.size();
    
    if (curr_ftr_idx == num_ftrs) {
        tmpFtrTupleData.clear();
        
        for (std::size_t i = 0; i < num_ftrs; i++)
            for (std::size_t j = 0; j < num_ftrs; j++)
                tmpFtrTupleData.push_back(ftrDistMatrix(tmpFtrTuple[i].second, tmpFtrTuple[j].second));

        if (std::lexicographical_compare(ftrTupleData.begin(), ftrTupleData.end(), tmpFtrTupleData.begin(), tmpFtrTupleData.end()))
            tmpFtrTupleData.swap(ftrTupleData);
        
        return;
    }
    
    auto eq_type_range_end = curr_ftr_idx + 1;

    for ( ; eq_type_range_end < tmpFtrTuple.size() && (tmpFtrTuple[curr_ftr_idx].first == tmpFtrTuple[eq_type_range_end].first); eq_type_range_end++);

    canonFeatureTupleData(eq_type_range_end);
 
    for (std::size_t i = 0, num_perms = Math::factorial<std::size_t>(eq_type_range_end - curr_ftr_idx) - 1; i < num_perms; i++) {
        Internal::nextPermutation(&tmpFtrTuple[curr_ftr_idx], &tmpFtrTuple[eq_type_range_end]);

        canonFeatureTupleData(eq_type_range_end);
    }
}

inline unsigned long Descr::NPointPharmacophoreFingerprintGenerator::getDistanceBinNumber(double dist) const
{
    return std::floor(dist / binSize);
}
