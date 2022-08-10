/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureAutoCorrelation3DVectorCalculator.hpp 
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
 * \brief Definition of the class CDPL::Descr::FeatureAutoCorrelation3DVectorCalculator.
 */

#ifndef CDPL_DESCR_AUTOCORRELATION3DVECTORCODECALCULATOR_HPP
#define CDPL_DESCR_AUTOCORRELATION3DVECTORCODECALCULATOR_HPP

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Descr/AutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class Feature;
		class FeatureContainer;
	}

	namespace Descr
	{

		/**
		 * \addtogroup CDPL_DESCR_3D_AUTOCORRELATION
		 * @{
		 */

		/**
		 * \brief FeatureAutoCorrelation3DVectorCalculator.
		 * \see [\ref CITB, \ref HBMD]
		 */
		class CDPL_DESCR_API FeatureAutoCorrelation3DVectorCalculator : public AutoCorrelation3DVectorCalculator<Pharm::Feature>
		{

		public:
			/**
			 * \brief Constructs the \c %FeatureAutoCorrelation3DVectorCalculator instance.
			 */
			FeatureAutoCorrelation3DVectorCalculator();
			
			FeatureAutoCorrelation3DVectorCalculator(const Pharm::FeatureContainer& cntnr, Math::DVector& vec);

			void calculate(const Pharm::FeatureContainer& cntnr, Math::DVector& vec);
		}; 

		/**
		 * @}
		 */
	}
}

#endif // CDPL_DESCR_AUTOCORRELATION3DVECTORCODECALCULATOR_HPP
