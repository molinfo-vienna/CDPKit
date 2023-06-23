/* 
 * FeatureInteractionScoreCombiner.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FeatureInteractionScoreCombiner.
 */

#ifndef CDPL_PHARM_FEATUREINTERACTIONSCORECOMBINER_HPP
#define CDPL_PHARM_FEATUREINTERACTIONSCORECOMBINER_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL 
{

    namespace Pharm
    {

        /**
         * \brief FeatureInteractionScoreCombiner.
         */
        class CDPL_PHARM_API FeatureInteractionScoreCombiner : public FeatureInteractionScore
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureInteractionScoreCombiner instances.
             */
            typedef std::shared_ptr<FeatureInteractionScoreCombiner> SharedPointer;

            typedef std::function<double(double, double)> CombinationFunction;

            typedef FeatureInteractionScore::SharedPointer InteractionScore;
            
            /**
             * \brief Constructs a \c %FeatureInteractionScoreCombiner that combines the score values calculated by two feature 
             *        interaction scoring functions.
             * \param score1 The first interaction scoring function.
             * \param score2 The second interaction scoring function.
             * \param comb_func The function calculating the final score value.
             */
            FeatureInteractionScoreCombiner(const InteractionScore& score1, const InteractionScore& score2,
                                     const CombinationFunction& comb_func);

            FeatureInteractionScoreCombiner(const InteractionScore& score1, const InteractionScore& score2);

            double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const;

            double operator()(const Feature& ftr1, const Feature& ftr2) const;

          private:
            InteractionScore    scoringFunc1;
            InteractionScore    scoringFunc2;
            CombinationFunction combFunc;
        };
    }
}

#endif // CDPL_PHARM_FEATUREINTERACTIONSCORECOMBINER_HPP
