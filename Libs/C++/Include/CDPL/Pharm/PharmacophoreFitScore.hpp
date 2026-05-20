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
         * \brief Scoring functor that quantifies how well a candidate set of features fits a reference pharmacophore,
         *        combining feature-match count, per-feature position deviation and geometry-match contributions.
         */
        class CDPL_PHARM_API PharmacophoreFitScore
        {

          public:
            /** \brief Default contribution weight of the matched-feature-count term. */
            static constexpr double DEF_FTR_MATCH_COUNT_WEIGHT = 1.0;
            /** \brief Default contribution weight of the feature-position-deviation term. */
            static constexpr double DEF_FTR_POS_MATCH_WEIGHT   = 0.5;
            /** \brief Default contribution weight of the feature-geometry-match term. */
            static constexpr double DEF_FTR_GEOM_MATCH_WEIGHT  = 0.4;

            /**
             * \brief Constructs the \c %PharmacophoreFitScore instance.
             * \param query_mode Forwarded to the embedded Pharm::SpatialFeatureMapping. If \c true, the reference feature container
             *                   is interpreted as a query pharmacophore so that position matching uses only the reference feature's
             *                   tolerance as the maximum allowed distance; if \c false, the maximum of the two feature tolerances is used.
             * \param match_cnt_weight Weight of the matched-feature-count contribution.
             * \param pos_match_weight Weight of the feature-position-deviation contribution.
             * \param geom_match_weight Weight of the feature-geometry-match contribution.
             */
            PharmacophoreFitScore(bool query_mode = false,
                                  double match_cnt_weight  = DEF_FTR_MATCH_COUNT_WEIGHT,
                                  double pos_match_weight  = DEF_FTR_POS_MATCH_WEIGHT,
                                  double geom_match_weight = DEF_FTR_GEOM_MATCH_WEIGHT);

            /**
             * \brief Returns the currently configured weight of the matched-feature-count contribution.
             * \return The match-count weight.
             */
            double getFeatureMatchCountWeight() const;

            /**
             * \brief Sets the weight of the matched-feature-count contribution.
             * \param weight The new match-count weight.
             */
            void setFeatureMatchCountWeight(double weight);

            /**
             * \brief Returns the currently configured weight of the feature-position-deviation contribution.
             * \return The position-match weight.
             */
            double getFeaturePositionMatchWeight() const;

            /**
             * \brief Sets the weight of the feature-position-deviation contribution.
             * \param weight The new position-match weight.
             */
            void setFeaturePositionMatchWeight(double weight);

            /**
             * \brief Returns the currently configured weight of the feature-geometry-match contribution.
             * \return The geometry-match weight.
             */
            double getFeatureGeometryMatchWeight() const;

            /**
             * \brief Sets the weight of the feature-geometry-match contribution.
             * \param weight The new geometry-match weight.
             */
            void setFeatureGeometryMatchWeight(double weight);

            /**
             * \brief Specifies whether reference features should be grouped before scoring (groups share a common
             *        mandatory/optional status and contribute jointly to the score).
             * \param group \c true to enable reference-feature grouping, and \c false to score every feature individually.
             * \since 1.2
             */
            void groupReferenceFeatures(bool group);

            /**
             * \brief Tells whether reference features are grouped before scoring.
             * \return \c true if reference-feature grouping is enabled, and \c false otherwise.
             * \since 1.2
             */
            bool referenceFeaturesGrouped() const;

            /**
             * \brief Computes the fit score of \a algnd_ftrs against \a ref_ftrs after applying the rigid-body transformation \a xform.
             * \param ref_ftrs The reference pharmacophore features.
             * \param algnd_ftrs The aligned candidate features.
             * \param xform The transformation applied to the aligned features before the comparison.
             * \return The pharmacophore fit score.
             */
            double operator()(const FeatureContainer& ref_ftrs, const FeatureContainer& algnd_ftrs,
                              const Math::Matrix4D& xform);

            /**
             * \brief Computes the fit score from a pre-computed feature mapping.
             * \param ref_ftrs The reference pharmacophore features.
             * \param mapping The spatial feature mapping between reference and aligned features.
             * \return The pharmacophore fit score.
             */
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
