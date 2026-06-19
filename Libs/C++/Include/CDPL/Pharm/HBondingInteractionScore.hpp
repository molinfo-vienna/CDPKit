/* 
 * HBondingInteractionScore.hpp 
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
 * \brief Definition of class CDPL::Pharm::HBondingInteractionScore.
 */

#ifndef CDPL_PHARM_HBONDINGINTERACTIONSCORE_HPP
#define CDPL_PHARM_HBONDINGINTERACTIONSCORE_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief Pharm::FeatureInteractionScore implementation that scores a donor/acceptor feature pair by combining
         *        per-component scores for H-bond length, acceptor-H-donor angle and H-bond direction to
         *        acceptor vector angle.
         */
        class CDPL_PHARM_API HBondingInteractionScore : public FeatureInteractionScore
        {

          public:
            /**
             * \brief Default minimum H-bond length in &Aring;ngstrom.
             */
            static constexpr double DEF_MIN_HB_LENGTH = 1.2;

            /**
             * \brief Default maximum H-bond length in &Aring;ngstrom.
             */
            static constexpr double DEF_MAX_HB_LENGTH = 2.8;

            /**
             * \brief Default minimum acceptor-hydrogen-donor angle in degrees.
             */
            static constexpr double DEF_MIN_AHD_ANGLE = 150.0;

            /**
             * \brief Default maximum H-bond direction to acceptor vector angle in degrees.
             */
            static constexpr double DEF_MAX_ACC_ANGLE = 75.0;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %HBondingInteractionScore instances.
             */
            typedef std::shared_ptr<HBondingInteractionScore> SharedPointer;

            /**
             * \brief Type of the function mapping an H-bond length to its score contribution.
             */
            typedef std::function<double(double)> DistanceScoringFunction;

            /**
             * \brief Type of the function mapping an H-bond geometry angle to its score contribution.
             */
            typedef std::function<double(double)> AngleScoringFunction;

            /**
             * \brief Constructs a \c %HBondingInteractionScore functor with the specified constraints.
             * \param don_acc \c true if the first feature argument represents the donor- and the second one
             *                the acceptor-feature, and \c false otherwise.
             * \param min_len The minimum allowed length of the H-bond (distance between the hydrogen-atom and acceptor-feature).
             * \param max_len The maximum allowed length of the H-bond (distance between the hydrogen-atom and acceptor-feature).
             * \param min_ahd_ang The minimum allowed angle between the acceptor-feature, hydrogen-atom and donor-feature.
             * \param max_acc_ang The maximum allowed angle between the H-bond direction and the acceptor-feature vector.
             */
            HBondingInteractionScore(bool don_acc, double min_len = DEF_MIN_HB_LENGTH, double max_len = DEF_MAX_HB_LENGTH,
                                     double min_ahd_ang = DEF_MIN_AHD_ANGLE, double max_acc_ang = DEF_MAX_ACC_ANGLE);

            /**
             * \brief Returns the currently configured minimum H-bond length.
             * \return The minimum H-bond length.
             */
            double getMinLength() const;

            /**
             * \brief Returns the currently configured maximum H-bond length.
             * \return The maximum H-bond length.
             */
            double getMaxLength() const;

            /**
             * \brief Returns the currently configured minimum acceptor-hydrogen-donor angle.
             * \return The minimum AHD angle in degrees.
             */
            double getMinAHDAngle() const;

            /**
             * \brief Returns the currently configured maximum H-bond direction to acceptor vector angle.
             * \return The maximum acceptor angle in degrees.
             */
            double getMaxAcceptorAngle() const;

            /**
             * \brief Specifies the function that maps the H-bond length to its score contribution.
             * \param func The distance-scoring function.
             */
            void setDistanceScoringFunction(const DistanceScoringFunction& func);

            /**
             * \brief Specifies the function that maps the H-bond direction to acceptor vector angle to its score contribution.
             * \param func The acceptor-angle scoring function.
             */
            void setAcceptorAngleScoringFunction(const AngleScoringFunction& func);

            /**
             * \brief Specifies the function that maps the acceptor-hydrogen-donor angle to its score contribution.
             * \param func The AHD-angle scoring function.
             */
            void setAHDAngleScoringFunction(const AngleScoringFunction& func);

            /**
             * \brief Evaluates the H-bond interaction score between features \a ftr1 and \a ftr2.
             * \param ftr1 The first feature.
             * \param ftr2 The second feature.
             * \return The H-bond interaction score.
             */
            double operator()(const Feature& ftr1, const Feature& ftr2) const;

            /**
             * \brief Evaluates the H-bond interaction score with the first feature represented only by its 3D position \a ftr1_pos.
             * \param ftr1_pos The 3D position of the first feature.
             * \param ftr2 The second feature.
             * \return The H-bond interaction score.
             */
            double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const;

          private:
            bool                    donAccOrder;
            double                  minLength;
            double                  maxLength;
            double                  minAHDAngle;
            double                  maxAccAngle;
            DistanceScoringFunction distScoringFunc;
            AngleScoringFunction    accAngleScoringFunc;
            AngleScoringFunction    ahdAngleScoringFunc;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_HBONDINGINTERACTIONSCORE_HPP
