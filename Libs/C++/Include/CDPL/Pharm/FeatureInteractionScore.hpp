/* 
 * FeatureInteractionScore.hpp 
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
 * \brief Definition of class CDPL::Pharm::FeatureInteractionScore.
 */

#ifndef CDPL_PHARM_FEATUREINTERACTIONSCORE_HPP
#define CDPL_PHARM_FEATUREINTERACTIONSCORE_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief Abstract base class for scoring functors that quantify the strength of a directional pharmacophore-feature
         *        interaction (e.g. H-bond, ionic, &pi;-&pi; stacking) between two Pharm::Feature instances.
         */
        class CDPL_PHARM_API FeatureInteractionScore
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureInteractionScore instances.
             */
            typedef std::shared_ptr<FeatureInteractionScore> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~FeatureInteractionScore() {}

            /**
             * \brief Evaluates the interaction score between features \a ftr1 and \a ftr2.
             * \param ftr1 The first feature.
             * \param ftr2 The second feature.
             * \return The interaction score.
             */
            virtual double operator()(const Feature& ftr1, const Feature& ftr2) const = 0;

            /**
             * \brief Evaluates the interaction score with the first feature represented only by its 3D position \a ftr1_pos.
             * \param ftr1_pos The 3D position of the first feature.
             * \param ftr2 The second feature.
             * \return The interaction score.
             */
            virtual double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const = 0;

          protected:
            FeatureInteractionScore() {}
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREINTERACTIONSCORE_HPP
