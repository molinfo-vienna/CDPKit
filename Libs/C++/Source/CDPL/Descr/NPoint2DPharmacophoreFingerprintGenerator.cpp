/* 
 * NPoint2DPharmacophoreFingerprintGenerator.cpp 
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

#include "CDPL/Descr/NPoint2DPharmacophoreFingerprintGenerator.hpp"


using namespace CDPL;


constexpr Descr::NPoint2DPharmacophoreFingerprintGenerator::FeatureDistanceType
Descr::NPoint2DPharmacophoreFingerprintGenerator::DEF_FEATURE_DISTANCE_TYPE;


Descr::NPoint2DPharmacophoreFingerprintGenerator::NPoint2DPharmacophoreFingerprintGenerator():
    ftrDistType(DEF_FEATURE_DISTANCE_TYPE)
{}

Descr::NPoint2DPharmacophoreFingerprintGenerator::NPoint2DPharmacophoreFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp):
    NPoint2DPharmacophoreFingerprintGenerator()
{
    generate(molgraph, fp);
}

void Descr::NPoint2DPharmacophoreFingerprintGenerator::setFeatureDistanceType(FeatureDistanceType dist_type)
{
    ftrDistType = dist_type;
}

Descr::NPoint2DPharmacophoreFingerprintGenerator::FeatureDistanceType
Descr::NPoint2DPharmacophoreFingerprintGenerator::getFeatureDistanceType() const
{
    return ftrDistType;
}

void Descr::NPoint2DPharmacophoreFingerprintGenerator::generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    NPoint2DPharmacophoreFingerprintGenerator::generate(molgraph, fp); // TODO
}

double Descr::NPoint2DPharmacophoreFingerprintGenerator::getDistance(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2) const
{
    return 0.0; // TODO
}
