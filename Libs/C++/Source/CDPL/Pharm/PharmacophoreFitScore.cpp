/* 
 * PharmacophoreFitScore.cpp 
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

#include <algorithm>

#include "CDPL/Pharm/PharmacophoreFitScore.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL;


namespace
{

    struct FeatureCmpFunc
    {

    public:
        bool operator()(const Pharm::Feature* ftr1, const Pharm::Feature* ftr2) const {
            unsigned int type1 = getType(*ftr1);
            unsigned int type2 = getType(*ftr2);

            if (type1 == type2) {
                const Math::Vector3D& pos1 = get3DCoordinates(*ftr1);
                const Math::Vector3D& pos2 = get3DCoordinates(*ftr2);

                if (pos1(0) == pos2(0)) {
                    if (pos1(1) == pos2(1)) 
                        return (pos1(2) < pos2(2));
                    
                    return (pos1(1) < pos2(1));
                }

                return (pos1(0) < pos2(0));
            }

            return (type1 < type2);
        }
    };
}


constexpr double Pharm::PharmacophoreFitScore::DEF_FTR_MATCH_COUNT_WEIGHT;
constexpr double Pharm::PharmacophoreFitScore::DEF_FTR_POS_MATCH_WEIGHT;
constexpr double Pharm::PharmacophoreFitScore::DEF_FTR_GEOM_MATCH_WEIGHT;


Pharm::PharmacophoreFitScore::PharmacophoreFitScore(double match_cnt_weight, double pos_match_weight, 
                            double geom_match_weight):
    ftrMatchCntWeight(match_cnt_weight), ftrPosMatchWeight(pos_match_weight), ftrGeomMatchWeight(geom_match_weight)
{}

double Pharm::PharmacophoreFitScore::getFeatureMatchCountWeight() const
{
    return ftrMatchCntWeight;
}

void Pharm::PharmacophoreFitScore::setFeatureMatchCountWeight(double weight)
{
    ftrMatchCntWeight = weight;
}

double Pharm::PharmacophoreFitScore::getFeaturePositionMatchWeight() const
{
    return ftrPosMatchWeight;
}

void Pharm::PharmacophoreFitScore::setFeaturePositionMatchWeight(double weight)
{
    ftrPosMatchWeight = weight;
}

double Pharm::PharmacophoreFitScore::getFeatureGeometryMatchWeight() const
{
    return ftrGeomMatchWeight;
}

void Pharm::PharmacophoreFitScore::setFeatureGeometryMatchWeight(double weight)
{
    ftrGeomMatchWeight = weight;
}

double Pharm::PharmacophoreFitScore::operator()(const FeatureContainer& ref_ftrs, const FeatureContainer& algnd_ftrs, 
                                                const Math::Matrix4D& xform)
{
    spatFtrMapping.perceive(ref_ftrs, algnd_ftrs, xform);

    return this->operator()(ref_ftrs, spatFtrMapping);
}

double Pharm::PharmacophoreFitScore::operator()(const FeatureContainer& ref_ftrs, const SpatialFeatureMapping& mapping)
{
    groupedRefFtrs.clear();

    for (FeatureContainer::ConstFeatureIterator it = ref_ftrs.getFeaturesBegin(), end = ref_ftrs.getFeaturesEnd(); it != end; ++it) {
        const Feature& ref_ftr = *it;
 
        if (getDisabledFlag(ref_ftr))
            continue;

        if (getType(ref_ftr) == FeatureType::EXCLUSION_VOLUME)
            continue;

        groupedRefFtrs.push_back(&ref_ftr);
    }

    if (groupedRefFtrs.empty())
        return 0.0;

    std::sort(groupedRefFtrs.begin(), groupedRefFtrs.end(), FeatureCmpFunc());

    std::size_t mat_ftr_cnt = 0;
    double tot_fit_score = 0.0;
    
    for (FeatureList::const_iterator it = groupedRefFtrs.begin(), end = groupedRefFtrs.end(); it != end; ) {
        unsigned int ref_type = 0;
        const Math::Vector3D* ref_pos = 0;
        double best_fit_score = 0.0;
        bool found_mapping = false;

        for ( ; it != end; ++it) {
            const Feature* ref_ftr = *it;

            if (ref_pos == 0) {
                ref_type = getType(*ref_ftr);
                ref_pos = &get3DCoordinates(*ref_ftr);

            } else if (ref_type != getType(*ref_ftr) || *ref_pos != get3DCoordinates(*ref_ftr))
                break;

            FeatureMapping::ConstEntryIteratorRange mpd_ftrs = mapping.getEntries(ref_ftr);

            for (FeatureMapping::ConstEntryIterator mf_it = mpd_ftrs.first; mf_it != mpd_ftrs.second; ++mf_it) {
                const Feature* m_ftr = mf_it->second;
                double pair_pos_score = mapping.getPositionMatchScore(*ref_ftr, *m_ftr);
                double pair_geom_score = mapping.getGeometryMatchScore(*ref_ftr, *m_ftr);
            
                best_fit_score = std::max(best_fit_score, ftrPosMatchWeight * pair_pos_score + ftrGeomMatchWeight * pair_geom_score);
                found_mapping = true;
            }
        }

        if (found_mapping) {
            mat_ftr_cnt++;
            tot_fit_score += best_fit_score;
        }
    }

    if (mat_ftr_cnt == 0)
        return 0.0;
    
    return (ftrMatchCntWeight * mat_ftr_cnt + tot_fit_score / mat_ftr_cnt);
}
