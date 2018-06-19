/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RDFCodeCalculator.hpp 
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
 * \brief Definition of the class CDPL::Chem::RDFCodeCalculator.
 */

#ifndef CDPL_CHEM_RDFCODECALCULATOR_HPP
#define CDPL_CHEM_RDFCODECALCULATOR_HPP

#include <cstddef>
#include <iterator>
#include <cmath>

#include <boost/function.hpp>
#include <boost/math/special_functions/round.hpp>

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_RDF_CODES
		 * @{
		 */

		/**
		 * \brief RDFCodeCalculator.
		 * \see [\ref CITB, \ref HBMD]
		 */
		template <typename T>
		class RDFCodeCalculator
		{

		public:
			typedef T EntityType;
			
			/**
			 * \brief Type of the generic functor class used to store a user-defined entity pair weight function.
			 *
			 * The specified function (or function object) is required to take the two entitys (as a
			 * \c const reference to \c EntityType) as its arguments and return the weight of the entity pair as
			 * a floating-point value of type \c double. For details refer to the <em>Boost.Function</em>
			 * documentation [\ref BFUN]. 
			 */
			typedef boost::function2<double, const EntityType&, const EntityType&> EntityPairWeightFunction;

			/**
			 * \brief Type of the generic functor class used to store a user-defined entity 3D coordinates function.
			 *
			 * The provided specified function (or function object) is required to take the entity (as a
			 * \c const reference to \c EntityType) as its argument and return the coordinates of the entity as
			 * a \c const reference to Math::Vector3D. For details refer to the <em>Boost.Function</em>
			 * documentation [\ref BFUN]. 
			 */
			typedef boost::function1<const Math::Vector3D&, const EntityType&> Entity3DCoordinatesFunction;

			/**
			 * \brief Constructs the \c %RDFCodeCalculator instance.
			 */
			RDFCodeCalculator();

			/**
			 * \brief Allows to specify the smoothing factor used in the calculation of
			 *        entity pair RDF contributions.
			 * \param factor The smoothing factor.
			 * \note The default value of the smoothing factor is <em>1.0</em>.
			 */
			void setSmoothingFactor(double factor);

			/**
			 * \brief Returns the smoothing factor used in the calculation of
			 *        entity pair RDF contributions.
			 * \return The applied smoothing factor.
			 */
			double getSmoothingFactor() const;

			/**
			 * \brief Allows to specify the scaling factor for the RDF code elements.
			 * \param factor The scaling factor.
			 * \note The default scaling factor is <em>1.0</em>.
			 */
			void setScalingFactor(double factor);

			/**
			 * \brief Returns the scaling factor applied to the RDF code elements.
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
			 * \brief Sets the radius step size between successive RDF code elements.
			 * \param radius_inc The radius step size.
			 * \note The default radius step size is <em>0.1</em>&Aring;.
			 */
			void setRadiusIncrement(double radius_inc);

			/**
			 * \brief Returns the radius step size between successive RDF code elements.
			 * \return The applied radius step size.
			 */
			double getRadiusIncrement() const;

			/**
			 * \brief Sets the number of desired radius incrementation steps.
			 *
			 * The number of performed radius incrementation steps defines the size of the calculated RDF code vector
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
			 * \brief Allows to specify a custom entity pair weight function.
			 * \param func A RDFCodeCalculator::EntityPairWeightFunction instance that wraps the target function.
			 * \note The default entity pair weight function returns the value \e 1.
			 */
			void setEntityPairWeightFunction(const EntityPairWeightFunction& func);

			/**
			 * \brief Allows to specify the entity 3D coordinates function.
			 * \param func A RDFCodeCalculator::Entity3DCoordinatesFunction instance that wraps the target function.
			 * \note The coordinates function must be specified before calling calculate(), otherwise a zero distance
			 *       for each entity pair will be used for the calculation.
			 */
			void setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func);

			/**
			 * \brief Allows to specify whether entity pair distances should be rounded to the nearest radius interval center.
			 * \param enable \c true if pair distances should be rounded, and \c false otherwise.
			 * \note The default setting is not to round the entity pair distances.
			 */
			void enableDistanceToIntervalCenterRounding(bool enable);

			/**
			 * \brief Tells whether entity pair distances get rounded to the nearest radius interval centers.
			 * \return \c true if pair distances get rounded, and \c false otherwise.
			 */
			bool distanceToIntervalsCenterRoundingEnabled() const;

			/**
			 * \brief Calculates the RDF code of an entity sequence.
			 *
			 * The elements of the returned RDF code vector correspond to the values of the radial distribution function
			 * at different radii. The first element provides the RDF value at the start radius (see setStartRadius())
			 * which gets incremented by the radius step size (see setRadiusIncrement()) for each successive
			 * element. The total number of calculated RDF values (corresponds to the RDF code vector's length) is given by
			 * the specified number of incrementation steps (see setNumSteps()) plus \e 1.
			 * 
			 * \param beg An iterator pointing to the beginning of the entity sequence.
			 * \param end An iterator pointing one past the end of the entity sequence.
			 * \param rdf_code The calculated RDF code vector.
 			 */
			template <typename Iter, typename Vec>
			void calculate(Iter beg, Iter end, Vec& rdf_code);

		private:
			template <typename Iter>
			void init(Iter beg, Iter end);

			double                      smoothingFactor;
			double                      scalingFactor;
			double                      startRadius;
			double                      radiusIncrement;
			std::size_t                 numSteps;
			std::size_t                 numEntities;
			EntityPairWeightFunction    weightFunc;
			Entity3DCoordinatesFunction coordsFunc;
			bool                        distToIntervalCenterRounding;
			Math::DMatrix               weightMatrix;
			Math::DMatrix               distMatrix;
		}; 

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename T>
CDPL::Chem::RDFCodeCalculator<T>::RDFCodeCalculator(): 
	smoothingFactor(1.0), scalingFactor(1.0), startRadius(0.0), radiusIncrement(0.1), numSteps(99), 
	distToIntervalCenterRounding(false) 
{}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setSmoothingFactor(double factor)
{
	smoothingFactor = factor;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setScalingFactor(double factor)
{
	scalingFactor = factor;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setStartRadius(double start_radius)
{
	startRadius = start_radius;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setRadiusIncrement(double radius_inc)
{
	radiusIncrement = radius_inc;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setNumSteps(std::size_t num_steps)
{
	numSteps = num_steps;
}

template <typename T>
double CDPL::Chem::RDFCodeCalculator<T>::getSmoothingFactor() const
{
	return smoothingFactor;
}

template <typename T>
double CDPL::Chem::RDFCodeCalculator<T>::getScalingFactor() const
{
	return scalingFactor;
}

template <typename T>
double CDPL::Chem::RDFCodeCalculator<T>::getStartRadius() const
{
	return startRadius;
}

template <typename T>
double CDPL::Chem::RDFCodeCalculator<T>::getRadiusIncrement() const
{
	return radiusIncrement;
}

template <typename T>
std::size_t CDPL::Chem::RDFCodeCalculator<T>::getNumSteps() const
{
	return numSteps;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setEntityPairWeightFunction(const EntityPairWeightFunction& func)
{
	weightFunc = func;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func)
{
	coordsFunc = func;
}

template <typename T>
void CDPL::Chem::RDFCodeCalculator<T>::enableDistanceToIntervalCenterRounding(bool enable)
{
	distToIntervalCenterRounding = enable;
}

template <typename T>
bool CDPL::Chem::RDFCodeCalculator<T>::distanceToIntervalsCenterRoundingEnabled() const
{
	return distToIntervalCenterRounding;
}

template <typename T>
template <typename Iter, typename Vec>
void CDPL::Chem::RDFCodeCalculator<T>::calculate(Iter beg, Iter end, Vec& rdf_code)
{
	init(beg, end);

	double r = startRadius;

	for (std::size_t i = 0; i <= numSteps; i++, r += radiusIncrement) {
		double sum = 0.0;

		for (std::size_t j = 0; j < numEntities; j++) {
			for (std::size_t k = j + 1; k < numEntities; k++) {
				double t = r - distMatrix(j, k);

				sum += weightMatrix(j, k) * std::exp(-smoothingFactor * t * t);
			}
		}

		rdf_code[i] = scalingFactor * sum;
	}
}

template <typename T>
template <typename Iter>
void CDPL::Chem::RDFCodeCalculator<T>::init(Iter beg, Iter end)
{
	numEntities = std::distance(beg, end);

	weightMatrix.resize(numEntities, numEntities, false);
	distMatrix.resize(numEntities, numEntities, false);

	Math::Vector3D entity1_pos;

	for (std::size_t i = 0; beg != end; i++) {
		const EntityType& entity1 = *beg;
		
		if (coordsFunc)
			entity1_pos = coordsFunc(entity1);

		std::size_t j = i + 1;

		for (Iter it = ++beg; it != end; ++it, j++) {
			const EntityType& entity2 = *it;

			if (!weightFunc)
				weightMatrix(i, j) = 1.0;
			else
				weightMatrix(i, j) = weightFunc(entity1, entity2);

			if (coordsFunc) {
				double dist = length(entity1_pos - coordsFunc(entity2));

				if (distToIntervalCenterRounding) 
					dist = boost::math::round((dist - startRadius) / radiusIncrement) * radiusIncrement + startRadius;
				
				distMatrix(i, j) = dist;

			} else
				distMatrix(i, j) = 0.0;
		}
	}
}

#endif // CDPL_CHEM_RDFCODECALCULATOR_HPP
