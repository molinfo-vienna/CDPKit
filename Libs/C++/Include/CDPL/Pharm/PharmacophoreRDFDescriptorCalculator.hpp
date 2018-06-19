/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreRDFDescriptorCalculator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PharmacophoreRDFDescriptorCalculator.
 */

#ifndef CDPL_PHARM_PHARMACOPHORERDFDESCRIPTORCALCULATOR_HPP
#define CDPL_PHARM_PHARMACOPHORERDFDESCRIPTORCALCULATOR_HPP

#include <boost/function.hpp>

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
		 * \addtogroup CDPL_PHARM_DESCRIPTORS
		 * @{
		 */

		/**
		 * \brief PharmacophoreRDFDescriptorCalculator.
		 * \see [\ref CITB, \ref HBMD]
		 */
		class CDPL_PHARM_API PharmacophoreRDFDescriptorCalculator
		{

			typedef Chem::RDFCodeCalculator<Feature> RDFCodeCalculator;

		public:
			typedef RDFCodeCalculator::Entity3DCoordinatesFunction Feature3DCoordinatesFunction;
			typedef boost::function3<double, const Feature&, const Feature&, unsigned int> FeaturePairWeightFunction;
				
			/**
			 * \brief Constructs the \c %PharmacophoreRDFDescriptorCalculator instance.
			 */
			PharmacophoreRDFDescriptorCalculator();
			
			PharmacophoreRDFDescriptorCalculator(const FeatureContainer& cntnr, Math::DVector& descr);

			/**
			 * \brief Allows to specify the smoothing factor used in the calculation of
			 *        feature pair \e RDF contributions.
			 * \param factor The smoothing factor.
			 * \note The default value of the smoothing factor is <em>1.0</em>.
			 */
			void setSmoothingFactor(double factor);

			/**
			 * \brief Returns the smoothing factor used in the calculation of
			 *        feature pair \e RDF contributions.
			 * \return The applied smoothing factor.
			 */
			double getSmoothingFactor() const;

			/**
			 * \brief Allows to specify the scaling factor for the \e RDF code elements.
			 * \param factor The scaling factor.
			 * \note The default scaling factor is <em>100.0</em>.
			 */
			void setScalingFactor(double factor);

			/**
			 * \brief Returns the scaling factor applied to the \e RDF code elements.
			 * \return The applied scaling factor.
			 */
			double getScalingFactor() const;

			/**
			 * \brief Sets the starting value of the radius.
			 * \param start_radius The starting value of the radius.
			 * \note The default starting radius is <em>0.0</em>&Aring;.
			 */
			void setStartRadius(double start_radius);

			/**
			 * \brief Returns the starting value of the radius.
			 * \return The current radius starting value.
			 */
			double getStartRadius() const;

			/**
			 * \brief Sets the radius step size between successive \e RDF code elements.
			 * \param radius_inc The radius step size.
			 * \note The default radius step size is <em>0.1</em>&Aring;.
			 */
			void setRadiusIncrement(double radius_inc);

			/**
			 * \brief Returns the radius step size between successive \e RDF code elements.
			 * \return The applied radius step size.
			 */
			double getRadiusIncrement() const;

			/**
			 * \brief Sets the number of desired radius incrementation steps.
			 *
			 * The number of performed radius incrementation steps defines the size of the calculated \e RDF code vector
			 * which is equal to the number of steps plus \e 1.
			 *
			 * \param num_steps The number of radius incrementation steps.
			 * \note The default number of steps is \e 99.
			 */
			void setNumSteps(std::size_t num_steps);

			/**
			 * \brief Returns the number of performed radius incrementation steps.
			 * \return The number of performed radius incrementation steps.
			 */
			std::size_t getNumSteps() const;

			/**
			 * \brief Allows to specify the feature coordinates function.
			 * \param func A Feature3DCoordinatesFunction instance that wraps the target function.
			 * \note The coordinates function must be specified before calling calculate(), otherwise a zero distance
			 *       for each feature pair will be used for the calculation.
			 */
			void setFeature3DCoordinatesFunction(const Feature3DCoordinatesFunction& func);

			/**
			 * \brief Allows to specify a custom feature pair weight function.
			 * \param func A FeaturePairWeightFunction instance that wraps the target function.
			 */
			void setFeaturePairWeightFunction(const FeaturePairWeightFunction& func);

			/**
			 * \brief Allows to specify whether feature pair distances should be rounded to the nearest radius interval center.
			 * \param enable \c true if pair distances should be rounded, and \c false otherwise.
			 * \note The default setting is not to round the feature pair distances.
			 */
			void enableDistanceToIntervalCenterRounding(bool enable);

			/**
			 * \brief Tells whether feature pair distances get rounded to the nearest radius interval centers.
			 * \return \c true if pair distances get rounded, and \c false otherwise.
			 */
			bool distanceToIntervalsCenterRoundingEnabled() const;

			void calculate(const FeatureContainer& cntnr, Math::DVector& descr);

		  private:
			RDFCodeCalculator         rdfCalculator;
			FeaturePairWeightFunction weightFunc;
		}; 

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_PHARMACOPHORERDFDESCRIPTORCALCULATOR_HPP
