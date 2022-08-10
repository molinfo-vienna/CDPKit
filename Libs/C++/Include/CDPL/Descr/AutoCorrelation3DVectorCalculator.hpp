/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AutoCorrelation3DVectorCalculator.hpp 
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
 * \brief Definition of the class CDPL::Descr::AutoCorrelation3DVectorCalculator.
 */

#ifndef CDPL_DESCR_AUTOCORRELATION3DVECTORCALCULATOR_HPP
#define CDPL_DESCR_AUTOCORRELATION3DVECTORCALCULATOR_HPP

#include <cstddef>
#include <iterator>
#include <cmath>

#include <boost/function.hpp>

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

	namespace Descr
	{

		/**
		 * \addtogroup CDPL_DESCR_3D_AUTOCORRELATION
		 * @{
		 */

		/**
		 * \brief AutoCorrelation3DVectorCalculator.
		 */
		template <typename T>
		class AutoCorrelation3DVectorCalculator
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
			 * \brief Constructs the \c %AutoCorrelation3DVectorCalculator instance.
			 */
			AutoCorrelation3DVectorCalculator();
		
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
			 * \brief Sets the radius step size between successive autocorrelation vector elements.
			 * \param radius_inc The radius step size.
			 * \note The default radius step size is <em>0.1</em>&Aring;.
			 */
			void setRadiusIncrement(double radius_inc);

			/**
			 * \brief Returns the radius step size between successive autocorrelation vector elements.
			 * \return The applied radius step size.
			 */
			double getRadiusIncrement() const;

			/**
			 * \brief Sets the number of desired radius incrementation steps.
			 *
			 * The number of performed radius incrementation steps defines the size of the calculated autocorrelation vector
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
			 * \param func A AutoCorrelation3DVectorCalculator::EntityPairWeightFunction instance that wraps the target function.
			 * \note The default entity pair weight function returns the value \e 1.
			 */
			void setEntityPairWeightFunction(const EntityPairWeightFunction& func);

			/**
			 * \brief Allows to specify the entity 3D coordinates function.
			 * \param func A AutoCorrelation3DVectorCalculator::Entity3DCoordinatesFunction instance that wraps the target function.
			 * \note The coordinates function must be specified before calling calculate(), otherwise a zero distance
			 *       for each entity pair will be used for the calculation.
			 */
			void setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func);

			/**
			 * \brief Calculates the RDF code of an entity sequence.
			 *
			 * The elements of the returned vector correspond to the values of the 3D autocorrelation function
			 * for the different interval centers. The total number of calculated vector elements is given by
			 * the specified number of incrementation steps (see setNumSteps()).
			 * 
			 * \param beg An iterator pointing to the beginning of the entity sequence.
			 * \param end An iterator pointing one past the end of the entity sequence.
			 * \param vec The calculated 3D autocorrelation vector.
 			 */
			template <typename Iter, typename Vec>
			void calculate(Iter beg, Iter end, Vec& vec);

		private:
			template <typename Iter>
			void init(Iter beg, Iter end);

			double                      startRadius;
			double                      radiusIncrement;
			std::size_t                 numSteps;
			std::size_t                 numEntities;
			EntityPairWeightFunction    weightFunc;
			Entity3DCoordinatesFunction coordsFunc;
			Math::DMatrix               weightMatrix;
			Math::Vector3DArray         entityPositions;
		}; 

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename T>
CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::AutoCorrelation3DVectorCalculator(): 
	startRadius(0.0), radiusIncrement(0.1), numSteps(99) {}

template <typename T>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::setStartRadius(double start_radius)
{
	startRadius = start_radius;
}

template <typename T>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::setRadiusIncrement(double radius_inc)
{
	radiusIncrement = radius_inc;
}

template <typename T>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::setNumSteps(std::size_t num_steps)
{
	numSteps = num_steps;
}

template <typename T>
double CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::getStartRadius() const
{
	return startRadius;
}

template <typename T>
double CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::getRadiusIncrement() const
{
	return radiusIncrement;
}

template <typename T>
std::size_t CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::getNumSteps() const
{
	return numSteps;
}

template <typename T>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::setEntityPairWeightFunction(const EntityPairWeightFunction& func)
{
	weightFunc = func;
}

template <typename T>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func)
{
	coordsFunc = func;
}

template <typename T>
template <typename Iter, typename Vec>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::calculate(Iter beg, Iter end, Vec& vec)
{
	init(beg, end);

	for (std::size_t i = 0; i <= numSteps; i++)
		vec[i] = 0.0;

	Math::Vector3D tmp;
	const double max_radius = startRadius + (numSteps + 1) * radiusIncrement;

	for (std::size_t i = 0; i < numEntities; i++) {
		for (std::size_t j = i; j < numEntities; j++) {
			double dist = 0.0;

			if (i != j) {
				tmp.assign(entityPositions[i] - entityPositions[j]);
				dist = length(tmp);
			}

			if (dist < startRadius || dist >= max_radius)
				continue;

			std::size_t idx = std::floor((dist - startRadius) / radiusIncrement);

			vec[idx] = weightMatrix(i, j);
		}
	}
}

template <typename T>
template <typename Iter>
void CDPL::Descr::AutoCorrelation3DVectorCalculator<T>::init(Iter beg, Iter end)
{
	numEntities = std::distance(beg, end);

	weightMatrix.resize(numEntities, numEntities, false);
	entityPositions.resize(numEntities);

	for (std::size_t i = 0; beg != end; i++, ++beg) {
		const EntityType& entity1 = *beg;
		
		if (coordsFunc)
			entityPositions[i] = coordsFunc(entity1);
		else
			entityPositions[i].clear(0.0);

		std::size_t j = i;

		for (Iter it = beg; it != end; ++it, j++) {
			const EntityType& entity2 = *it;

			if (!weightFunc)
				weightMatrix(i, j) = 1.0;
			else
				weightMatrix(i, j) = weightFunc(entity1, entity2);
		}
	}
}

#endif // CDPL_DESCR_AUTOCORRELATION3DVECTORCALCULATOR_HPP
