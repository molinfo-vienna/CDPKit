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
 * \brief Definition of the class CDPL::Pharm::PharmacophoreFitScreeningScore.
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
         * \brief PharmacophoreFitScreeningScore.
         */
        class CDPL_PHARM_API PharmacophoreFitScreeningScore : public PharmacophoreFitScore
        {

          public:
            PharmacophoreFitScreeningScore(double ftr_match_cnt_weight = DEF_FTR_MATCH_COUNT_WEIGHT, 
                                           double ftr_pos_match_weight = DEF_FTR_POS_MATCH_WEIGHT,
                                           double ftr_geom_match_weight = DEF_FTR_GEOM_MATCH_WEIGHT);

            double operator()(const ScreeningProcessor::SearchHit& hit);
        };
    }
}

#endif // CDPL_PHARM_PHARMACOPHOREFITSCREENINGSCORE_HPP
