/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::Pharm::HBondingInteractionScore.
 */

#ifndef CDPL_PHARM_HBONDINGINTERACTIONSCORE_HPP
#define CDPL_PHARM_HBONDINGINTERACTIONSCORE_HPP

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \brief HBondingInteractionScore.
		 */
		class CDPL_PHARM_API HBondingInteractionScore : public FeatureInteractionScore
		{

		  public:
			static const double DEF_MIN_HB_LENGTH;
			static const double DEF_MAX_HB_LENGTH;
			static const double DEF_MIN_AHD_ANGLE;
			static const double DEF_MAX_ACC_ANGLE;

			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %HBondingInteractionScore instances.
			 */
			typedef boost::shared_ptr<HBondingInteractionScore> SharedPointer;

			typedef boost::function1<double, double> DistanceScoringFunction;
			typedef boost::function1<double, double> AngleScoringFunction;

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

			double getMinLength() const;

			double getMaxLength() const;

			double getMinAHDAngle() const;

			double getMaxAcceptorAngle() const;

			void setDistanceScoringFunction(const DistanceScoringFunction& func);

			void setAcceptorAngleScoringFunction(const AngleScoringFunction& func);

			void setAHDAngleScoringFunction(const AngleScoringFunction& func);

			double operator()(const Feature& ftr1, const Feature& ftr2) const;

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
    }
}

#endif // CDPL_PHARM_HBONDINGINTERACTIONSCORE_HPP
