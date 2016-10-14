/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreFitScore.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Pharm::PharmacophoreFitScore.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREFITSCORE_HPP
#define CDPL_PHARM_PHARMACOPHOREFITSCORE_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief PharmacophoreFitScore.
		 */
		class CDPL_PHARM_API PharmacophoreFitScore
		{

		  public:
			static const double DEF_FTR_MATCH_COUNT_FACTOR   = 0.8;
			static const double DEF_FTR_POS_MATCH_FACTOR     = 0.1;
			static const double DEF_FTR_GEOM_MATCH_FACTOR    = 0.1;
	  
			PharmacophoreFitScore(double match_cnt_factor = DEF_FTR_MATCH_COUNT_FACTOR, 
								  double pos_match_factor = DEF_FTR_POS_MATCH_FACTOR,
								  double geom_match_factor = DEF_FTR_GEOM_MATCH_FACTOR);

			double getFeatureMatchCountFactor() const;

			void setFeatureMatchCountFactor(double factor);

			double getFeaturePositionMatchFactor() const;

			void setFeaturePositionMatchFactor(double factor);

			double getFeatureGeometryMatchFactor() const;

			void setFeatureGeometryMatchFactor(double factor);

			double operator()(const Pharmacophore& ref_pharm, const Pharmacophore& algnd_pharm, 
							  const Math::Matrix4D& xform);

		  private:
			double ftrMatchCntFactor;
			double ftrPosMatchFactor;
			double ftrGeomMatchFactor;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_PHARMACOPHOREFITSCORE_HPP
