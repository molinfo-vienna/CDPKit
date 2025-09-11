/* 
 * FeaturePositionMatchFunctor.hpp 
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
 * \brief Definition of class CDPL::Pharm::FeaturePositionMatchFunctor.
 */

#ifndef CDPL_PHARM_FEATUREPOSITIONMATCHFUNCTOR_HPP
#define CDPL_PHARM_FEATUREPOSITIONMATCHFUNCTOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"

#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief FeaturePositionMatchFunctor.
         */
        class CDPL_PHARM_API FeaturePositionMatchFunctor
        {

          public:
            FeaturePositionMatchFunctor(bool query_mode):
                qryMode(query_mode) {}

            bool queryMode() const;

            /**
             * \brief Checks if the distance between \a ftr1 and \a ftr2 is below the allowed maximum and calculates a score reflecting their proximity.
             *
             * If in 'query mode', the tolerance of \a ftr1 specifies the allowed maximum distance. Otherwise, the maximum tolerance of the features
             * takes effect.
             *
             * \param ftr1 The first feature.
             * \param ftr2 The second feature.
             * \return A score from \e 0 (=outside effective tolerance) and \e 1 (exact position match) that specifies the
             *         proximity of the features.
             * \see Pharm::getPosition(const Feature&), Pharm::getTolerance(const Feature&)
             */
            double operator()(const Feature& ftr1, const Feature& ftr2) const;

            /**
             * \brief Checks if the distance between \a ftr1 and \a ftr2 is below the allowed maximum and calculates a score reflecting their proximity.
             *
             * If in 'query mode', the tolerance of \a ftr1 specifies the allowed maximum distance. Otherwise, the maximum tolerance of the features
             * takes effect.
             *
             * \param ftr1 The first feature.
             * \param ftr2 The second feature.
             * \param xform The transformation to apply to the position of the second feature.
             * \return A score from \e 0 (=outside effective tolerance) and \e 1 (exact position match) that specifies the
             *         proximity of the features.
             * \see Pharm::getPosition(const Feature&), Pharm::getTolerance(const Feature&)
             */
            double operator()(const Feature& ftr1, const Feature& ftr2, const Math::Matrix4D& xform) const;

          private:
            bool qryMode;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREPOSITIONMATCHFUNCTOR_HPP
