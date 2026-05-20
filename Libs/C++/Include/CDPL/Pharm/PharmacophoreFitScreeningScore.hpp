/* 
 * PharmacophoreFitScreeningScore.hpp 
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
 * \brief Definition of class CDPL::Pharm::PharmacophoreFitScreeningScore.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREFITSCREENINGSCORE_HPP
#define CDPL_PHARM_PHARMACOPHOREFITSCREENINGSCORE_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Pharm/PharmacophoreFitScore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief Pharm::PharmacophoreFitScore specialization that scores a Pharm::ScreeningProcessor::SearchHit by
         *        applying the underlying pharmacophore-fit score to its query and hit features.
         */
        class CDPL_PHARM_API PharmacophoreFitScreeningScore : public PharmacophoreFitScore
        {

          public:
            /**
             * \brief Constructs the \c %PharmacophoreFitScreeningScore instance.
             * \param ftr_match_cnt_weight Weight of the matched-feature-count contribution.
             * \param ftr_pos_match_weight Weight of the feature-position-deviation contribution.
             * \param ftr_geom_match_weight Weight of the feature-geometry-match contribution.
             */
            PharmacophoreFitScreeningScore(double ftr_match_cnt_weight  = DEF_FTR_MATCH_COUNT_WEIGHT,
                                           double ftr_pos_match_weight  = DEF_FTR_POS_MATCH_WEIGHT,
                                           double ftr_geom_match_weight = DEF_FTR_GEOM_MATCH_WEIGHT);

            /**
             * \brief Computes the pharmacophore-fit score of the screening search hit \a hit.
             * \param hit The screening search hit.
             * \return The pharmacophore-fit screening score.
             */
            double operator()(const ScreeningProcessor::SearchHit& hit);
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PHARMACOPHOREFITSCREENINGSCORE_HPP
