/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGCoordinatesGenerator.hpp 
 *
 * Copyright (C) 2010-2012 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Implementation of a distance geometry based coordinates generator.
 */

#ifndef CDPL_UTIL_DGCOORDINATESGENERATOR_HPP
#define CDPL_UTIL_DGCOORDINATESGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <algorithm>
#include <cmath>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_int.hpp>

#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Util
    {

		/**
		 * \addtogroup CDPL_UTIL_ALGORITHMS
		 * @{
		 */

		/**
		 * \brief Base for classes dedicated to the generation of coordinates that fulfill user-provided point distance
		 *        (and volume) constraints [\ref ASPE].
		 */
		template <std::size_t Dim, typename T, typename Derived>
		class DGCoordinatesGeneratorBase
		{

		public:
			class DistanceConstraint;

		private:
			typedef std::vector<DistanceConstraint> DistanceConstraintList;

		public:
			typedef typename DistanceConstraintList::iterator DistanceConstraintIterator;
			typedef typename DistanceConstraintList::const_iterator ConstDistanceConstraintIterator;
			typedef T ValueType;

			static const std::size_t COORDS_DIM                  = Dim;
			static const std::size_t DEF_NUM_CYCLES              = 50;
			static const std::size_t DEF_CYCLE_STEP_COUNT_FACTOR = 50;

			static const ValueType   DEF_START_LEARNING_RATE;
			static const ValueType   DEF_LEARNING_RATE_DECREMENT;

			class DistanceConstraint
			{

			public:
				DistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, const ValueType& lb, const ValueType& ub);

				std::size_t getPoint1Index() const;

				std::size_t getPoint2Index() const;

				const ValueType& getLowerBound() const;

				const ValueType& getUpperBound() const;

			private:
				std::size_t point1Idx;
				std::size_t point2Idx;
				ValueType   lowerBound;
				ValueType   upperBound;
			};
	
			void clearDistanceConstraints();

			void addDistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, const ValueType& lb, const ValueType& ub);

			std::size_t getNumDistanceConstraints() const;

			const DistanceConstraint& getDistanceConstraint(std::size_t idx) const;

			DistanceConstraint& getDistanceConstraint(std::size_t idx);

			void removeDistanceConstraint(std::size_t idx);

			void removeDistanceConstraint(const DistanceConstraintIterator& it);

			DistanceConstraintIterator getDistanceConstraintsBegin();

			DistanceConstraintIterator getDistanceConstraintsEnd();

			ConstDistanceConstraintIterator getDistanceConstraintsBegin() const;

			ConstDistanceConstraintIterator getDistanceConstraintsEnd() const;

			void setBoxSize(const ValueType& size);

			void setNumCycles(std::size_t num_cycles);

			void setCycleStepCountFactor(std::size_t fact);

			void setStartLearningRate(const ValueType& rate);

			void setLearningRateDecrement(const ValueType& decr);

			const ValueType& getBoxSize() const;

			std::size_t getNumCycles() const;

			std::size_t getCycleStepCountFactor() const;

			const ValueType& getStartLearningRate() const;

			const ValueType& getLearningRateDecrement() const;

			template <typename CoordsArray>
			void generate(std::size_t num_points, CoordsArray& coords);

			template <typename CoordsArray>
			ValueType getDistanceError(const CoordsArray& coords) const;

		protected:
			DGCoordinatesGeneratorBase();

			DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen);

			~DGCoordinatesGeneratorBase() {}

			DGCoordinatesGeneratorBase& operator=(const DGCoordinatesGeneratorBase& gen);

		private:
			std::size_t getNumVolumeConstraints() const;

			template <typename CoordsArray>
			void genRandomCoords(std::size_t num_points, CoordsArray& coords);

			template <typename CoordsArray>
			void embedCoords(std::size_t num_points, CoordsArray& coords);

			template <typename CoordsArray>
			void adjCoordsForDistanceConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx) const;

			template <typename Vec>
			void adjCoordsForConstraint(const DistanceConstraint& constr, Vec& pt1_pos, Vec& pt2_pos, const ValueType& lambda) const;

			template <typename CoordsArray>
			void adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx) const;

			template <typename Vec>
			static ValueType calcDiffVectorAndSquaredDist(const Vec& pt1_pos, const Vec& pt2_pos, ValueType diff[]);

			typedef boost::random::mt19937 RandNumEngine;

			std::size_t            numCycles;
			std::size_t            cycleStepCountFactor;
			ValueType              startLearningRate;
			ValueType              learningRateDecr;
			ValueType              boxSize;
			DistanceConstraintList distConstraints;
			RandNumEngine          randomEngine;
		};

		template <std::size_t Dim, typename T, typename Derived> 
		const std::size_t DGCoordinatesGeneratorBase<Dim, T, Derived>::COORDS_DIM;

		template <std::size_t Dim, typename T, typename Derived> 
		const std::size_t DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_NUM_CYCLES;

		template <std::size_t Dim, typename T, typename Derived> 
		const std::size_t DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_CYCLE_STEP_COUNT_FACTOR;

		template <std::size_t Dim, typename T, typename Derived> 
		const typename DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType
		DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_START_LEARNING_RATE = 1;

		template <std::size_t Dim, typename T, typename Derived> 
		const typename DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType
		DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_LEARNING_RATE_DECREMENT = 0.9 / 50;


		/**
		 * \brief Generic implementation for generation of coordinates that fulfill user-provided point distance constraints [\ref ASPE].
		 */
		template <std::size_t Dim, typename T>
		class DGCoordinatesGenerator : public DGCoordinatesGeneratorBase<Dim, T, DGCoordinatesGenerator<Dim, T> > {};


		/**
		 * \brief Specialized implementation for the generation of 3D coordinates that fulfill user-provided point distance and volume constraints [\ref ASPE].
		 */
		template <typename T>
		class DGCoordinatesGenerator<3, T> : public DGCoordinatesGeneratorBase<3, T, DGCoordinatesGenerator<3, T> > 
		{

			typedef DGCoordinatesGeneratorBase<3, T, DGCoordinatesGenerator<3, T> > BaseType;
			friend class DGCoordinatesGeneratorBase<3, T, DGCoordinatesGenerator<3, T> >;

		public:
			class VolumeConstraint;

		private:
			typedef std::vector<VolumeConstraint> VolumeConstraintList;

		public:
			typedef typename BaseType::ValueType ValueType;
			typedef typename VolumeConstraintList::iterator VolumeConstraintIterator;
			typedef typename VolumeConstraintList::const_iterator ConstVolumeConstraintIterator;

			class VolumeConstraint
			{

			public:
				VolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, 
								 std::size_t pt4_idx, const ValueType& lb, const ValueType& ub);

				std::size_t getPoint1Index() const;

				std::size_t getPoint2Index() const;

				std::size_t getPoint3Index() const;

				std::size_t getPoint4Index() const;

				const ValueType& getLowerBound() const;

				const ValueType& getUpperBound() const;

			private:
				std::size_t point1Idx;
				std::size_t point2Idx;
				std::size_t point3Idx;
				std::size_t point4Idx;
				ValueType   lowerBound;
				ValueType   upperBound;
			};

			void clearVolumeConstraints();

			void addVolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, 
									 std::size_t pt4_idx, const ValueType& lb, const ValueType& ub);

			std::size_t getNumVolumeConstraints() const;

			const VolumeConstraint& getVolumeConstraint(std::size_t idx) const;

			VolumeConstraint& getVolumeConstraint(std::size_t idx);

			void removeVolumeConstraint(std::size_t idx);

			void removeVolumeConstraint(const VolumeConstraintIterator& it);

			VolumeConstraintIterator getVolumeConstraintsBegin();

			VolumeConstraintIterator getVolumeConstraintsEnd();

			ConstVolumeConstraintIterator getVolumeConstraintsBegin() const;

			ConstVolumeConstraintIterator getVolumeConstraintsEnd() const;

			template <typename CoordsArray>
			ValueType getVolumeError(const CoordsArray& coords) const;

		private:
			template <typename CoordsArray>
			void adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx) const;

			template <typename Vec>
			void adjCoordsForConstraint(const VolumeConstraint& constr, Vec& pt1_pos, Vec& pt2_pos, Vec& pt3_pos, 
										Vec& pt4_pos, const ValueType& lambda) const;

			template <typename Vec>
			static void calcDiffVector(const Vec& pt1_pos, const Vec& pt2_pos, ValueType diff[]);

			VolumeConstraintList volConstraints;
		};

		/**
		 * @}
		 */
    }
}


// \cond UNHIDE_DETAILS
// DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint implementation

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::DistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, 
																					   const ValueType& lb, const ValueType& ub):
	point1Idx(pt1_idx), point2Idx(pt2_idx), lowerBound(lb), upperBound(ub) {}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::getPoint1Index() const
{
	return point1Idx;
}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::getPoint2Index() const
{
	return point2Idx;
}

template <std::size_t Dim, typename T, typename Derived>
const T& CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::getLowerBound() const
{
	return lowerBound;
}

template <std::size_t Dim, typename T, typename Derived>
const T& CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::getUpperBound() const
{
	return upperBound;
}

// DGCoordinatesGeneratorBase<Dim, T, Derived> implementation

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DGCoordinatesGeneratorBase(): 
	numCycles(DEF_NUM_CYCLES), cycleStepCountFactor(DEF_CYCLE_STEP_COUNT_FACTOR), startLearningRate(DEF_START_LEARNING_RATE), 
	learningRateDecr(DEF_LEARNING_RATE_DECREMENT), boxSize(10), randomEngine(170375)
{}
	
template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen): 
	numCycles(gen.numCycles), cycleStepCountFactor(gen.cycleStepCountFactor), 
	startLearningRate(gen.startLearningRate), learningRateDecr(gen.learningRateDecr), 
	boxSize(gen.boxSize), distConstraints(gen.distConstraints),
	randomEngine(gen.randomEngine)
{}

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::operator=(const DGCoordinatesGeneratorBase& gen)
{
	if (&gen == this)
		return *this;

	numCycles = gen.numCycles;
	cycleStepCountFactor = gen.cycleStepCountFactor;
	startLearningRate = gen.startLearningRate;
	learningRateDecr = gen.learningRateDecr;
	boxSize = gen.boxSize;
	distConstraints = gen.distConstraints;

	return *this;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::clearDistanceConstraints()
{
	distConstraints.clear();	
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::addDistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, 
																					const ValueType& lb, const ValueType& ub)
{
	distConstraints.push_back(DistanceConstraint(pt1_idx, pt2_idx, lb, ub));
}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getNumDistanceConstraints() const
{
	return distConstraints.size();
}

template <std::size_t Dim, typename T, typename Derived>
const typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceConstraint(std::size_t idx) const
{
	if (idx >= distConstraints.size())
		throw Base::IndexError("DGCoordinatesGeneratorBase: constraint index out of bounds");

	return distConstraints[idx];
}

template <std::size_t Dim, typename T, typename Derived>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceConstraint(std::size_t idx)
{
	if (idx >= distConstraints.size())
		throw Base::IndexError("DGCoordinatesGeneratorBase: constraint index out of bounds");

	return distConstraints[idx];
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::removeDistanceConstraint(std::size_t idx)
{
	if (idx >= distConstraints.size())
		throw Base::IndexError("DGCoordinatesGeneratorBase: constraint index out of bounds");

	distConstraints.erase(distConstraints.begin() + idx);
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::removeDistanceConstraint(const DistanceConstraintIterator& it)
{
	if ((it - distConstraints.begin()) >= distConstraints.size())
		throw Base::IndexError("DGCoordinatesGeneratorBase: constraint iterator out of bounds");

	distConstraints.erase(it);
}

template <std::size_t Dim, typename T, typename Derived>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraintIterator
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceConstraintsBegin()
{
	return distConstraints.begin();
}

template <std::size_t Dim, typename T, typename Derived>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraintIterator
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceConstraintsEnd()
{
	return distConstraints.end();
}

template <std::size_t Dim, typename T, typename Derived>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ConstDistanceConstraintIterator
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceConstraintsBegin() const
{
	return distConstraints.begin();
}

template <std::size_t Dim, typename T, typename Derived>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ConstDistanceConstraintIterator
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceConstraintsEnd() const
{
	return distConstraints.end();
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setBoxSize(const ValueType& size)
{
	boxSize = size;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setNumCycles(std::size_t num_cycles)
{
	numCycles = num_cycles;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setCycleStepCountFactor(std::size_t fact)
{
	cycleStepCountFactor = fact;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setStartLearningRate(const ValueType& rate)
{
	startLearningRate = rate;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setLearningRateDecrement(const ValueType& decr)
{
	learningRateDecr = decr;
}

template <std::size_t Dim, typename T, typename Derived>
const typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getBoxSize() const
{
	return boxSize;
}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getNumCycles() const
{
	return numCycles;
}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getCycleStepCountFactor() const
{
	return cycleStepCountFactor;
}

template <std::size_t Dim, typename T, typename Derived>
const typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getStartLearningRate() const
{
	return startLearningRate;
}

template <std::size_t Dim, typename T, typename Derived>
const typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getLearningRateDecrement() const
{
	return learningRateDecr;
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceError(const CoordsArray& coords) const
{
	ValueType error = ValueType();
	ValueType pos_diff[Dim];

	for (typename DistanceConstraintList::const_iterator it = distConstraints.begin(), end = distConstraints.end(); it != end; ++it) {
		const DistanceConstraint& constr = *it;

		ValueType dist_2 = calcDiffVectorAndSquaredDist(coords[constr.getPoint1Index()], coords[constr.getPoint2Index()], pos_diff);
		ValueType dist = std::sqrt(dist_2);
		ValueType lb = constr.getLowerBound();
		ValueType ub = constr.getUpperBound();

		if (dist >= lb && dist <= ub)
			continue;

		if (dist < lb) {
			ValueType tmp = (lb * lb - dist_2) / (0.000001 + lb * lb);

			error += tmp * tmp;

		} else {
			ValueType tmp = (ub * ub - dist_2) / (0.000001 + ub * ub);
			
			error += tmp * tmp;
		}

	}

	return error;
}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getNumVolumeConstraints() const
{
	return 0;
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::generate(std::size_t num_points, CoordsArray& coords)
{
	genRandomCoords(num_points, coords);
	embedCoords(num_points, coords);
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::genRandomCoords(std::size_t num_points, CoordsArray& coords)
{
	boost::random::uniform_real_distribution<ValueType> rnd_dist(-boxSize / 2, boxSize / 2);

	for (std::size_t i = 0; i < num_points; i++) 
		for (std::size_t j = 0; j < Dim; j++)
			coords[i][j] = rnd_dist(randomEngine);
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::embedCoords(std::size_t num_points, CoordsArray& coords)
{
	std::size_t num_dist_constrs = distConstraints.size();
	std::size_t num_vol_constrs = static_cast<Derived&>(*this).getNumVolumeConstraints();

	if ((num_dist_constrs + num_vol_constrs) == 0)
		return;

	std::size_t num_steps = num_points * cycleStepCountFactor;
	ValueType lambda = startLearningRate;

	if (num_dist_constrs > 0 && num_vol_constrs > 0) {
		boost::random::uniform_int_distribution<std::size_t> dist_constr_sd(0, num_dist_constrs - 1);
		boost::random::uniform_int_distribution<std::size_t> vol_constr_sd(0, num_vol_constrs - 1);
		boost::random::uniform_real_distribution<ValueType> vol_dist_constr_sd(0, 1);

		ValueType vol_constr_prob = std::max(ValueType(0.5), ValueType(num_vol_constrs) / (num_vol_constrs + num_dist_constrs));

		for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) {
			for (std::size_t j = 0; j < num_steps; j++) {
				if (vol_dist_constr_sd(randomEngine) > vol_constr_prob)
					adjCoordsForDistanceConstraint(coords, lambda, dist_constr_sd(randomEngine));
				else
					static_cast<Derived&>(*this).adjCoordsForVolumeConstraint<CoordsArray>(coords, lambda, vol_constr_sd(randomEngine));
			}
		}

		return;
	}
 
	if (num_dist_constrs > 0) {
		boost::random::uniform_int_distribution<std::size_t> dist_constr_sd(0, num_dist_constrs - 1);

		for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) 
			for (std::size_t j = 0; j < num_steps; j++) 
				adjCoordsForDistanceConstraint(coords, lambda, dist_constr_sd(randomEngine));
		
		return;
	}

	boost::random::uniform_int_distribution<std::size_t> vol_constr_sd(0, num_vol_constrs - 1);

	for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) 
		for (std::size_t j = 0; j < num_steps; j++) 
			static_cast<Derived&>(*this).adjCoordsForVolumeConstraint<CoordsArray>(coords, lambda, vol_constr_sd(randomEngine));
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::adjCoordsForDistanceConstraint(CoordsArray& coords, const ValueType& lambda, 
																							 std::size_t constr_idx) const
{
	const DistanceConstraint& constr = distConstraints[constr_idx];

	adjCoordsForConstraint(constr, coords[constr.getPoint1Index()], coords[constr.getPoint2Index()], lambda);
}

template <std::size_t Dim, typename T, typename Derived>
template <typename Vec>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::adjCoordsForConstraint(const DistanceConstraint& constr, Vec& pt1_pos, 
																					 Vec& pt2_pos, const ValueType& lambda) const
{
	ValueType pos_diff[Dim];
	ValueType dist = std::sqrt(calcDiffVectorAndSquaredDist(pt1_pos, pt2_pos, pos_diff));

	ValueType ub = constr.getUpperBound();
	ValueType lb = constr.getLowerBound();

	if (dist >= lb && dist <= ub)
		return;
	
	ValueType bound = (dist > ub ? ub : lb);
	ValueType factor = lambda / 2 * (bound - dist) / (0.000001 + dist);

	for (std::size_t i = 0; i < Dim; i++) {
		ValueType pos_delta = pos_diff[i] * factor;

		pt1_pos[i] -= pos_delta;
		pt2_pos[i] += pos_delta;
	}
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, 
																						   std::size_t constr_idx) const
{}

template <std::size_t Dim, typename T, typename Derived>
template <typename Vec>
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::calcDiffVectorAndSquaredDist(const Vec& pt1_pos, const Vec& pt2_pos, ValueType diff[])
{
	ValueType dist_2 = ValueType();

	for (std::size_t i = 0; i < Dim; i++) {
		diff[i] = pt2_pos[i] - pt1_pos[i];
		dist_2 += diff[i] * diff[i];
	}

	return dist_2;
}


// DGCoordinatesGenerator<3, T>::VolumeConstraint implementation

template <typename T>
CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::VolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, 
																			 std::size_t pt3_idx, std::size_t pt4_idx, 
																			 const ValueType& lb, const ValueType& ub): 
	point1Idx(pt1_idx), point2Idx(pt2_idx), point3Idx(pt3_idx), point4Idx(pt4_idx), lowerBound(lb), upperBound(ub) 
{}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint1Index() const
{
	return point1Idx;
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint2Index() const
{
	return point2Idx;
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint3Index() const
{
	return point3Idx;
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint4Index() const
{
	return point4Idx;
}

template <typename T>
const typename CDPL::Util::DGCoordinatesGenerator<3, T>::ValueType& 
CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getLowerBound() const
{
	return lowerBound;
}

template <typename T>
const typename CDPL::Util::DGCoordinatesGenerator<3, T>::ValueType& 
CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getUpperBound() const
{
	return upperBound;
}


// DGCoordinatesGenerator<3, T> implementation

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::clearVolumeConstraints()
{
	volConstraints.clear();
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::addVolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, 
																   std::size_t pt4_idx, const ValueType& lb, const ValueType& ub)
{
	volConstraints.push_back(VolumeConstraint(pt1_idx, pt2_idx, pt3_idx, pt4_idx, lb, ub));
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::getNumVolumeConstraints() const
{
	return volConstraints.size();
}

template <typename T>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint& 
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeConstraint(std::size_t idx)
{
	if (idx >= volConstraints.size())
		throw Base::IndexError("DGCoordinatesGenerator: constraint index out of bounds");

	return volConstraints[idx];
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::removeVolumeConstraint(std::size_t idx)
{
	if (idx >= volConstraints.size())
		throw Base::IndexError("DGCoordinatesGenerator: constraint index out of bounds");

	volConstraints.erase(volConstraints.begin() + idx);
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::removeVolumeConstraint(const VolumeConstraintIterator& it)
{
	if ((it - volConstraints.begin()) >= volConstraints.size())
		throw Base::IndexError("DGCoordinatesGenerator: constraint iterator out of bounds");

	volConstraints.erase(it);
}

template <typename T>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraintIterator
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeConstraintsBegin()
{
	return volConstraints.begin();
}

template <typename T>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraintIterator
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeConstraintsEnd()
{
	return volConstraints.end();
}

template <typename T>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::ConstVolumeConstraintIterator
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeConstraintsBegin() const
{
	return volConstraints.begin();
}

template <typename T>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::ConstVolumeConstraintIterator
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeConstraintsEnd() const
{
	return volConstraints.end();
}

template <typename T>
template <typename CoordsArray>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::ValueType 
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeError(const CoordsArray& coords) const
{
	ValueType error = ValueType();
	ValueType v_41[3];
	ValueType v_42[3];
	ValueType v_43[3];

	for (typename VolumeConstraintList::const_iterator it = volConstraints.begin(), end = volConstraints.end(); it != end; ++it) {
		const VolumeConstraint& constr = *it;

		calcDiffVector(coords[constr.getPoint4Index()], coords[constr.getPoint1Index()], v_41);
		calcDiffVector(coords[constr.getPoint4Index()], coords[constr.getPoint2Index()], v_42);
		calcDiffVector(coords[constr.getPoint4Index()], coords[constr.getPoint3Index()], v_43);

		ValueType vol = (v_41[0] * (v_42[1] * v_43[2] - v_42[2] * v_43[1]) 
						 - v_41[1] * (v_42[0] * v_43[2] - v_42[2] * v_43[0]) 
						 + v_41[2] * (v_42[0] * v_43[1] - v_42[1] * v_43[0])) / 6;

		ValueType lb = constr.getLowerBound();
		ValueType ub = constr.getUpperBound();

		if (vol >= lb && vol <= ub)
			continue;

		if (vol < lb) {
			ValueType tmp = (lb * lb - vol * vol) / (0.000001 + lb * lb);

			error += tmp * tmp;

		} else {
			ValueType tmp = (ub * ub - vol * vol) / (0.000001 + ub * ub);
			
			error += tmp * tmp;
		}
	}

	return error;
}

template <typename T>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGenerator<3, T>::adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx) const
{
	const VolumeConstraint& constr = volConstraints[constr_idx];

	adjCoordsForConstraint(constr, coords[constr.getPoint1Index()], coords[constr.getPoint2Index()],
						   coords[constr.getPoint3Index()], coords[constr.getPoint4Index()], lambda);
}

template <typename T>
template <typename Vec>
void CDPL::Util::DGCoordinatesGenerator<3, T>::adjCoordsForConstraint(const VolumeConstraint& constr, Vec& pt1_pos, Vec& pt2_pos, Vec& pt3_pos, 
																	  Vec& pt4_pos, const ValueType& lambda) const
{
	Vec* pt_pos[4] = { &pt1_pos,  &pt2_pos,  &pt3_pos, &pt4_pos }; 
	ValueType v_41[3];
	ValueType v_42[3];
	ValueType v_43[3];

	calcDiffVector(*pt_pos[3], *pt_pos[0], v_41);
	calcDiffVector(*pt_pos[3], *pt_pos[1], v_42);
	calcDiffVector(*pt_pos[3], *pt_pos[2], v_43);

	ValueType g[4][3];

	g[0][0] =  (v_42[1] * v_43[2] - v_42[2] * v_43[1]) / 6;
	g[0][1] = -(v_42[0] * v_43[2] - v_42[2] * v_43[0]) / 6;
	g[0][2] =  (v_42[0] * v_43[1] - v_42[1] * v_43[0]) / 6;

	ValueType vol = (v_41[0] * g[0][0] + v_41[1] * g[0][1] + v_41[2] * g[0][2]);
	ValueType ub = constr.getUpperBound();
	ValueType lb = constr.getLowerBound();

	if (vol >= lb && vol <= ub)
		return;

	g[1][0] = (v_41[2] * v_43[1] - v_41[1] * v_43[2]) / 6;
	g[1][1] = (v_41[0] * v_43[2] - v_41[2] * v_43[0]) / 6;
	g[1][2] = (v_41[1] * v_43[0] - v_41[0] * v_43[1]) / 6;

	g[2][0] = (v_41[1] * v_42[2] - v_41[2] * v_42[1]) / 6;
	g[2][1] = (v_41[2] * v_42[0] - v_41[0] * v_42[2]) / 6;
	g[2][2] = (v_41[0] * v_42[1] - v_41[1] * v_42[0]) / 6;

	g[3][0] = -g[0][0] - g[1][0] - g[2][0];
	g[3][1] = -g[0][1] - g[1][1] - g[2][1];
	g[3][2] = -g[0][2] - g[1][2] - g[2][2];

	ValueType g_len2_sum = ValueType();

	for (std::size_t i = 0; i < 4; i++)
		g_len2_sum += g[i][0] * g[i][0] + g[i][1] * g[i][1] + g[i][2] * g[i][2];

	ValueType bound = (vol < lb ? lb : ub);
	ValueType fact = lambda * (bound - vol) / g_len2_sum;

	for (std::size_t i = 0; i < 4; i++) 
		for (std::size_t j = 0; j < 3; j++) 
			(*pt_pos[i])[j] += fact * g[i][j];
}

template <typename T>
template <typename Vec>
void CDPL::Util::DGCoordinatesGenerator<3, T>::calcDiffVector(const Vec& pt1_pos, const Vec& pt2_pos, ValueType diff[])
{
	for (std::size_t i = 0; i < 3; i++)
		diff[i] = pt2_pos[i] - pt1_pos[i];
}

// \endcond

#endif // CDPL_UTIL_DGCOORDINATESGENERATOR_HPP
