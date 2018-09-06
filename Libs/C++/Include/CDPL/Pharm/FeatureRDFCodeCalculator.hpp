/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureRDFCodeCalculator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FeatureRDFCodeCalculator.
 */

#ifndef CDPL_PHARM_FEATURERDFCODECALCULATOR_HPP
#define CDPL_PHARM_FEATURERDFCODECALCULATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/RDFCodeCalculator.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class Feature;
		class FeatureContainer;

		/**
		 * \addtogroup CDPL_PHARM_RDF_CODES
		 * @{
		 */

		/**
		 * \brief FeatureRDFCodeCalculator.
		 * \see [\ref CITB, \ref HBMD]
		 */
		class CDPL_PHARM_API FeatureRDFCodeCalculator : public Chem::RDFCodeCalculator<Feature>
		{

		public:
			/**
			 * \brief Constructs the \c %FeatureRDFCodeCalculator instance.
			 */
			FeatureRDFCodeCalculator();
			
			FeatureRDFCodeCalculator(const FeatureContainer& cntnr, Math::DVector& rdf_code);

			void calculate(const FeatureContainer& cntnr, Math::DVector& rdf_code);
		}; 

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_FEATURERDFCODECALCULATOR_HPP