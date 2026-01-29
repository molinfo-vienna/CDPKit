/* 
 * PharmacophoreFitScore.hpp 
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

/**
 * \file
 * \brief Definition of class CDPL::Pharm::PharmacophoreFitScore.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREFITSCORE_HPP
#define CDPL_PHARM_PHARMACOPHOREFITSCORE_HPP

#include <vector>
#include <unordered_set>
#include <cstddef>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Pharm/SpatialFeatureMapping.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class FeatureContainer;

        /**
         * \brief PharmacophoreFitScore.
         */
        class CDPL_PHARM_API PharmacophoreFitScore
        {

          public:
            static constexpr double DEF_FTR_MATCH_COUNT_WEIGHT = 1.0;
            static constexpr double DEF_FTR_POS_MATCH_WEIGHT   = 0.5;
            static constexpr double DEF_FTR_GEOM_MATCH_WEIGHT  = 0.4;

            PharmacophoreFitScore(bool query_mode = false,
                                  double match_cnt_weight  = DEF_FTR_MATCH_COUNT_WEIGHT,
                                  double pos_match_weight  = DEF_FTR_POS_MATCH_WEIGHT,
                                  double geom_match_weight = DEF_FTR_GEOM_MATCH_WEIGHT);

            double getFeatureMatchCountWeight() const;

            void setFeatureMatchCountWeight(double weight);

            double getFeaturePositionMatchWeight() const;

            void setFeaturePositionMatchWeight(double weight);

            double getFeatureGeometryMatchWeight() const;

            void setFeatureGeometryMatchWeight(double weight);

            /**
             * \since 1.2
             */
            void groupReferenceFeatures(bool group);

            /**
             * \since 1.2
             */
            bool referenceFeaturesGrouped() const;
            
            double operator()(const FeatureContainer& ref_ftrs, const FeatureContainer& algnd_ftrs,
                              const Math::Matrix4D& xform);

            double operator()(const FeatureContainer& ref_ftrs, const SpatialFeatureMapping& mapping);

          private:
            typedef std::vector<const Feature*>        FeatureList;
            typedef std::vector<std::size_t>           IndexList;
            typedef std::unordered_set<const Feature*> FeatureSet;

            void calcScore(std::size_t idx, const SpatialFeatureMapping& mapping,
                           std::size_t mat_ftr_cnt, std::size_t mat_mand_ftr_cnt, double tot_fit_score);
            
            SpatialFeatureMapping spatFtrMapping;
            double                ftrMatchCntWeight;
            double                ftrPosMatchWeight;
            double                ftrGeomMatchWeight;
            bool                  grpRefFtrs;
            FeatureList           grpdRefFtrs;
            IndexList             refFtrGrpBounds;
            Util::BitSet          mandRefFtrGrps;
            FeatureSet            assignedAlgdFtrs;
            double                maxScore;
            std::size_t           maxMpdMandFtrCount;
            std::size_t           maxMpdFtrCount;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PHARMACOPHOREFITSCORE_HPP
