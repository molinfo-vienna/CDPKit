/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeaturePairDistanceMatchFunctor.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Pharm::FeaturePairDistanceMatchFunctor.
 */

#ifndef CDPL_PHARM_FEATUREPAIRDISTANCEMATCHFUNCTOR_HPP
#define CDPL_PHARM_FEATUREPAIRDISTANCEMATCHFUNCTOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief FeaturePairDistanceMatchFunctor.
		 */
		class CDPL_PHARM_API FeaturePairDistanceMatchFunctor
		{

		  public:
			/**
			 * \brief Constructs the \c %FeaturePairDistanceMatchFunctor instance.
			 * \param query_mode If \c true, the second pair feature distance must fall in the distance +/- tolerances
			 *                   of the first pair for the compatibility check to succeed. If \c false, it is sufficient
			 *                   that any one of the pairs matches the distance range of the other. 
			 */
			FeaturePairDistanceMatchFunctor(bool query_mode): qryMode(query_mode) {}

			bool queryMode() const;

			/**
			 * \brief Checks if the feature pairs (\a p1_ftr1, \a p1_ftr2) and (\a p2_ftr1, \a p2_ftr2) are matching
			 *        in terms of their feature distance.
			 * \param p1_ftr1 The first feature of the first pair.
			 * \param p1_ftr2 The second feature of the first pair.
			 * \param p2_ftr1 The first feature of the second pair.
			 * \param p2_ftr2 The second feature of the second pair.
			 * \return \c true if the feature pair distance are compatible, and \c false otherwise.
			 * \see FeaturePairDistanceMatchFunctor()
			 */
			bool operator()(const Feature& p1_ftr1, const Feature& p1_ftr2,
							const Feature& p2_ftr1, const Feature& p2_ftr2) const;

		  private:
			bool qryMode;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_FEATUREPAIRDISTANCEMATCHFUNCTOR_HPP
