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


constexpr double Pharm::PharmacophoreFitScore::DEF_FTR_MATCH_COUNT_WEIGHT;
constexpr double Pharm::PharmacophoreFitScore::DEF_FTR_POS_MATCH_WEIGHT;
constexpr double Pharm::PharmacophoreFitScore::DEF_FTR_GEOM_MATCH_WEIGHT;


Pharm::PharmacophoreFitScore::PharmacophoreFitScore(double match_cnt_weight, double pos_match_weight, 
                            double geom_match_weight):
    ftrMatchCntWeight(match_cnt_weight), ftrPosMatchWeight(pos_match_weight), ftrGeomMatchWeight(geom_match_weight),
    grpRefFtrs(true)
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

void Pharm::PharmacophoreFitScore::groupReferenceFeatures(bool group)
{
    grpRefFtrs = true;
}

bool Pharm::PharmacophoreFitScore::referenceFeaturesGrouped() const
{
    return grpRefFtrs;
}
            
double Pharm::PharmacophoreFitScore::operator()(const FeatureContainer& ref_ftrs, const FeatureContainer& algnd_ftrs, 
                                                const Math::Matrix4D& xform)
{
    spatFtrMapping.perceive(ref_ftrs, algnd_ftrs, xform);

    return this->operator()(ref_ftrs, spatFtrMapping);
}

double Pharm::PharmacophoreFitScore::operator()(const FeatureContainer& ref_ftrs, const SpatialFeatureMapping& mapping)
{
    grpdRefFtrs.clear();

    for (auto& ref_ftr : ref_ftrs) {
        if (getDisabledFlag(ref_ftr))
            continue;

        if (getType(ref_ftr) == FeatureType::EXCLUSION_VOLUME)
            continue;

        grpdRefFtrs.push_back(&ref_ftr);
    }

    if (grpdRefFtrs.empty())
        return 0.0;

    maxScore = 0.0;
    maxMpdMandFtrCount = 0;
    maxMpdFtrCount = 0;
    
    assignedAlgdFtrs.clear();
    refFtrGrpBounds.clear();
    mandRefFtrGrps.resize(grpdRefFtrs.size());

    if (grpRefFtrs) {
        std::sort(grpdRefFtrs.begin(), grpdRefFtrs.end(),
                  [](const Feature* ftr1, const Feature* ftr2) {
                      auto type1 = getType(*ftr1);
                      auto type2 = getType(*ftr2);

                      if (type1 == type2) {
                          auto& pos1 = get3DCoordinates(*ftr1);
                          auto& pos2 = get3DCoordinates(*ftr2);

                          if (pos1(0) == pos2(0)) {
                              if (pos1(1) == pos2(1))
                                  return (pos1(2) < pos2(2));

                              return (pos1(1) < pos2(1));
                          }

                          return (pos1(0) < pos2(0));
                      }

                      return (type1 < type2);
                  });

        for (std::size_t i = 0, num_ftrs = grpdRefFtrs.size(); i < num_ftrs; ) {
            auto& ftr = *grpdRefFtrs[i];
            auto ref_type = getType(ftr);
            auto& ref_pos = get3DCoordinates(ftr);
            auto optional = getOptionalFlag(ftr);

            refFtrGrpBounds.push_back(i);
        
            for (i++ ; i < num_ftrs; i++) {
                auto& next_ftr = *grpdRefFtrs[i];
            
                if (ref_type != getType(next_ftr) || ref_pos != get3DCoordinates(next_ftr))
                    break;

                optional &= getOptionalFlag(next_ftr);
            }

            mandRefFtrGrps.set(refFtrGrpBounds.size() / 2, !optional);
            refFtrGrpBounds.push_back(i);
        }

    } else
        for (std::size_t i = 0, num_ftrs = grpdRefFtrs.size(); i < num_ftrs; ) {
            mandRefFtrGrps.set(i, !getOptionalFlag(*grpdRefFtrs[i]));
            refFtrGrpBounds.push_back(i);
            refFtrGrpBounds.push_back(++i);
        }
    
    calcScore(0, mapping, 0, 0, 0.0);

    return maxScore;
}

void Pharm::PharmacophoreFitScore::calcScore(std::size_t idx, const SpatialFeatureMapping& mapping,
                                             std::size_t mat_ftr_cnt, std::size_t mat_mand_ftr_cnt, double tot_fit_score)
{
    if (idx == refFtrGrpBounds.size()) {
        if (mat_mand_ftr_cnt < maxMpdMandFtrCount)
            return;

        auto score = ftrMatchCntWeight * mat_ftr_cnt + tot_fit_score / mat_ftr_cnt;

        if (mat_mand_ftr_cnt == maxMpdMandFtrCount) {
            if (mat_ftr_cnt < maxMpdFtrCount)
                return;

            if (mat_ftr_cnt == maxMpdFtrCount) {
                if (score > maxScore)
                    maxScore = score;

                return;
            }

            maxMpdFtrCount = mat_ftr_cnt;
            maxScore = score;
            return;
        }
        
        maxMpdMandFtrCount = mat_mand_ftr_cnt;
        maxMpdFtrCount = mat_ftr_cnt;
        maxScore = score;
        return;
    }

    auto mand_grp = mandRefFtrGrps.test(idx / 2);
    
    for (auto i = refFtrGrpBounds[idx], j = refFtrGrpBounds[idx + 1]; i < j; i++) {
        auto ftr = grpdRefFtrs[i];
        auto mpd_ftrs = mapping.getEntries(ftr);

        for (auto mf_it = mpd_ftrs.first; mf_it != mpd_ftrs.second; ++mf_it) {
            auto m_ftr = mf_it->second;
            auto pair_pos_score = mapping.getPositionMatchScore(*ftr, *m_ftr);
            auto pair_geom_score = mapping.getGeometryMatchScore(*ftr, *m_ftr);

            if (!assignedAlgdFtrs.insert(m_ftr).second)
                continue;
            
            calcScore(idx + 2, mapping, mat_ftr_cnt + 1, mat_mand_ftr_cnt + mand_grp,
                      tot_fit_score + ftrPosMatchWeight * pair_pos_score + ftrGeomMatchWeight * pair_geom_score);

            assignedAlgdFtrs.erase(m_ftr);
        }
    }

    calcScore(idx + 2, mapping, mat_ftr_cnt, mat_mand_ftr_cnt, tot_fit_score);
}
