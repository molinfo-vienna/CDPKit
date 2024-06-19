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

#include <cmath>

#include "CDPL/Descr/NPoint2DPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


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
    molGraph = &molgraph;

    if (hasTopologicalDistanceMatrix(molgraph))
        activeTopDistMatrix = getTopologicalDistanceMatrix(molgraph).get();

    else {
        calcTopologicalDistanceMatrix(molgraph, topDistMatrix);

        activeTopDistMatrix = &topDistMatrix;
    }
            
    NPointPharmacophoreFingerprintGenerator::generate(molgraph, fp);
}

double Descr::NPoint2DPharmacophoreFingerprintGenerator::getDistance(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2) const
{
    auto& substr1 = *getSubstructure(ftr1);
    auto& substr2 = *getSubstructure(ftr2);

    switch (ftrDistType) {

        case MIN_PATH_LENGTH: {
            unsigned long dist = ~static_cast<unsigned long>(0);

            for (auto& atom1 : substr1.getAtoms()) {
                auto atom1_idx = molGraph->getAtomIndex(atom1);

                for (auto& atom2 : substr2.getAtoms()) {
                    auto atom2_idx = molGraph->getAtomIndex(atom2);

                    dist = std::min(dist, (*activeTopDistMatrix)(atom1_idx, atom2_idx));
                }
            }

            return dist;
        }
            
        case MAX_PATH_LENGTH: {
            unsigned long dist = 0;

            for (auto& atom1 : substr1.getAtoms()) {
                auto atom1_idx = molGraph->getAtomIndex(atom1);

                for (auto& atom2 : substr2.getAtoms()) {
                    auto atom2_idx = molGraph->getAtomIndex(atom2);

                    dist = std::max(dist, (*activeTopDistMatrix)(atom1_idx, atom2_idx));
                }
            }

            return dist;
        }
            
        case AVG_PATH_LENGTH: {
            double dist = 0.0;
            std::size_t num_dist = 0;
            
            for (auto& atom1 : substr1.getAtoms()) {
                auto atom1_idx = molGraph->getAtomIndex(atom1);

                for (auto& atom2 : substr2.getAtoms()) {
                    auto atom2_idx = molGraph->getAtomIndex(atom2);

                    dist += (*activeTopDistMatrix)(atom1_idx, atom2_idx);
                    num_dist++;
                }
            }

            return (dist / num_dist);
        }

        default:
            throw Base::OperationFailed("NPoint2DPharmacophoreFingerprintGenerator: invalid feature distance type");
    }

    return 0.0;
}
