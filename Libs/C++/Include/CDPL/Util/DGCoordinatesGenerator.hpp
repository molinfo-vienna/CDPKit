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

#include "CDPL/Math/Vector.hpp"
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
			typedef T ValueType;

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

			void setBoxSize(const ValueType& size);

			void setNumPoints(std::size_t num_points);

			void setNumCycles(std::size_t num_cycles);

			void setCycleStepCountFactor(std::size_t fact);

			void setStartLearningRate(const ValueType& rate);

			void setLearningRateDecrement(const ValueType& decr);

			const ValueType& getBoxSize() const;

			std::size_t getNumCycles() const;

			std::size_t getCycleStepCountFactor() const;

			const ValueType& getStartLearningRate() const;

			const ValueType& getLearningRateDecrement() const;

			std::size_t getNumPoints() const;

			void generate();
		
			template <typename OutputCoordsArray>
			void getCoordinates(OutputCoordsArray& coords) const;

			ValueType getDistanceError() const;

		protected:
			typedef Math::CVector<ValueType, Dim> CoordsType;
			typedef typename CoordsType::ConstPointer ConstCoordsDataPtr;
			typedef typename CoordsType::Pointer CoordsDataPtr;
			typedef std::vector<CoordsType> CoordsArray;

			DGCoordinatesGeneratorBase();

			DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen);

			~DGCoordinatesGeneratorBase() {}

			DGCoordinatesGeneratorBase& operator=(const DGCoordinatesGeneratorBase& gen);

			const CoordsArray& getCoordinates() const;

		private:
			void init();

			void checkConstraints();
			void checkVolumeConstraints();

			std::size_t getNumVolumeConstraints() const;

			void genRandomCoords();
			void embedCoords();

			void adjCoordsForDistanceConstraint(const ValueType& lambda, std::size_t constr_idx);
			void adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx);

			void numPointsChanged();

			ValueType calcDiffVectorAndSquaredDist(ConstCoordsDataPtr pt1_pos, ConstCoordsDataPtr pt2_pos, ValueType diff[]) const;

			typedef std::vector<DistanceConstraint> DistConstraintList;
			typedef boost::random::mt19937 RandNumEngine;

			std::size_t         numPoints;
			std::size_t         numCycles;
			std::size_t         cycleStepCountFactor;
			ValueType           startLearningRate;
			ValueType           learningRateDecr;
			ValueType           boxSize;
			CoordsArray         coordinates;
			DistConstraintList  distConstraints;
			bool                verifyConstraints;
			RandNumEngine       randomEngine;
		};

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
			typedef typename BaseType::ValueType ValueType;

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
				std::size_t pointInds[4];
				ValueType   lowerBound;
				ValueType   upperBound;
			};

			DGCoordinatesGenerator();

			void clearVolumeConstraints();

			void addVolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, 
									 std::size_t pt4_idx, const ValueType& lb, const ValueType& ub);

			std::size_t getNumVolumeConstraints() const;

			ValueType getVolumeError() const;

		private:
			typedef typename BaseType::CoordsArray CoordsArray;
			typedef typename BaseType::CoordsType CoordsType;
			typedef typename BaseType::ConstCoordsDataPtr ConstCoordsDataPtr;
			typedef typename BaseType::CoordsDataPtr CoordsDataPtr;

			void numPointsChanged();
			void checkVolumeConstraints();

			void adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx);
	
			void calcDiffVector(ConstCoordsDataPtr pt1_pos, ConstCoordsDataPtr pt2_pos, ValueType diff[]) const;

			typedef std::vector<VolumeConstraint> VolConstraintList;

			VolConstraintList volConstraints;
			bool              verifyConstraints;
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
	point1Idx(pt1_idx), point2Idx(pt2_idx), lowerBound(lb), upperBound(ub) 
{
	if (lb < ValueType() || ub < ValueType())
		throw Base::ValueError("DistanceConstraint: specified distance < 0");
	
	if (lb > ub)
		throw Base::RangeError("DistanceConstraint: lower bound > upper bound");
}

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
	numPoints(0), numCycles(100), cycleStepCountFactor(50), startLearningRate(1), learningRateDecr(0.009),
	boxSize(10), verifyConstraints(false), 
	randomEngine(170375)
{}
	
template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen): 
	numPoints(gen.numPoints), numCycles(gen.numCycles), cycleStepCountFactor(gen.cycleStepCountFactor), 
	startLearningRate(gen.startLearningRate), learningRateDecr(gen.learningRateDecr), 
	boxSize(gen.boxSize), verifyConstraints(gen.verifyConstraints), coordinates(gen.coordinates), distConstraints(gen.distConstraints),
	randomEngine(gen.randomEngine)
{}

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::operator=(const DGCoordinatesGeneratorBase& gen)
{
	if (&gen == this)
		return *this;

	numPoints = gen.numPoints;
	numCycles = gen.numCycles;
	cycleStepCountFactor = gen.cycleStepCountFactor;
	startLearningRate = gen.startLearningRate;
	learningRateDecr = gen.learningRateDecr;
	boxSize = gen.boxSize;
	verifyConstraints = gen.verifyConstraints;
	coordinates = gen.coordinates;
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
	verifyConstraints = true;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setBoxSize(const ValueType& size)
{
	boxSize = size;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setNumPoints(std::size_t num_points)
{
	numPoints = num_points;
	verifyConstraints = true;

	static_cast<Derived&>(*this).numPointsChanged();
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
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getNumPoints() const
{
	return numPoints;
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
typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getDistanceError() const
{
	ValueType error = ValueType();
	ValueType pos_diff[Dim];

	for (typename DistConstraintList::const_iterator it = distConstraints.begin(), end = distConstraints.end(); it != end; ++it) {
		const DistanceConstraint& constr = *it;

		ValueType dist_2 = calcDiffVectorAndSquaredDist(coordinates[constr.getPoint1Index()].getData(), coordinates[constr.getPoint2Index()].getData(), pos_diff);
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
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::generate()
{
	init();

	checkConstraints();

	genRandomCoords();
	embedCoords();
}

template <std::size_t Dim, typename T, typename Derived>
template <typename OutputCoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getCoordinates(OutputCoordsArray& out_coords) const
{
	for (std::size_t i = 0, num_pts = coordinates.size(); i < num_pts; i++) {
		ConstCoordsDataPtr pt_pos = coordinates[i].getData();

		for (std::size_t j = 0; j < Dim; j++)
			out_coords[i][j] = pt_pos[j];
	}
}

template <std::size_t Dim, typename T, typename Derived>
const typename CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::CoordsArray&
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getCoordinates() const
{
	return coordinates;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::init()
{
	coordinates.resize(numPoints);
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::checkConstraints()
{
	if (verifyConstraints) {
		for (typename DistConstraintList::const_iterator it = distConstraints.begin(), end = distConstraints.end(); it != end; ++it) {
			const DistanceConstraint& constr = *it;

			if (constr.getPoint1Index() >= numPoints || constr.getPoint2Index() >= numPoints)
				throw Base::IndexError("DGCoordinatesGeneratorBase: distance constraint point index out of bounds");
		}

		verifyConstraints = false;
	}

	static_cast<Derived&>(*this).checkVolumeConstraints();
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::checkVolumeConstraints()
{}

template <std::size_t Dim, typename T, typename Derived>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getNumVolumeConstraints() const
{
	return 0;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::numPointsChanged()
{}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::genRandomCoords()
{
	boost::random::uniform_real_distribution<ValueType> rnd_dist(-boxSize / 2, boxSize / 2);

	for (typename CoordsArray::iterator it = coordinates.begin(), end = coordinates.end(); it != end; ++it) {
		CoordsDataPtr pt_pos = it->getData();

		for (std::size_t i = 0; i < Dim; i++)
			pt_pos[i] = rnd_dist(randomEngine);

		pt_pos[Dim] = ValueType();
	}
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::embedCoords()
{
	std::size_t num_dist_constrs = distConstraints.size();
	std::size_t num_vol_constrs = static_cast<Derived&>(*this).getNumVolumeConstraints();

	if ((num_dist_constrs + num_vol_constrs) == 0)
		return;

	std::size_t num_steps = numPoints * cycleStepCountFactor;
	ValueType lambda = startLearningRate;

	if (num_dist_constrs > 0 && num_vol_constrs > 0) {
		boost::random::uniform_int_distribution<std::size_t> dist_constr_sd(0, num_dist_constrs - 1);
		boost::random::uniform_int_distribution<std::size_t> vol_constr_sd(0, num_vol_constrs - 1);
		boost::random::uniform_real_distribution<ValueType> vol_dist_constr_sd(0, 1);

		ValueType vol_constr_prob = std::max(ValueType(0.5), ValueType(num_vol_constrs) / (num_vol_constrs + num_dist_constrs));

		for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) {
			for (std::size_t j = 0; j < num_steps; j++) {
				if (vol_dist_constr_sd(randomEngine) > vol_constr_prob)
					adjCoordsForDistanceConstraint(lambda, dist_constr_sd(randomEngine));
				else
					static_cast<Derived&>(*this).adjCoordsForVolumeConstraint(coordinates, lambda, vol_constr_sd(randomEngine));
			}
		}

		return;
	}
 
	if (num_dist_constrs > 0) {
		boost::random::uniform_int_distribution<std::size_t> dist_constr_sd(0, num_dist_constrs - 1);

		for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) 
			for (std::size_t j = 0; j < num_steps; j++) 
				adjCoordsForDistanceConstraint(lambda, dist_constr_sd(randomEngine));
		
		return;
	}

	boost::random::uniform_int_distribution<std::size_t> vol_constr_sd(0, num_vol_constrs - 1);

	for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) 
		for (std::size_t j = 0; j < num_steps; j++) 
			static_cast<Derived&>(*this).adjCoordsForVolumeConstraint(coordinates, lambda, vol_constr_sd(randomEngine));
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::adjCoordsForDistanceConstraint(const ValueType& lambda, std::size_t constr_idx)
{
	const DistanceConstraint& constr = distConstraints[constr_idx];

	CoordsDataPtr pt1_pos = coordinates[constr.getPoint1Index()].getData();
	CoordsDataPtr pt2_pos = coordinates[constr.getPoint2Index()].getData();

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
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx)
{}

template <std::size_t Dim, typename T, typename Derived>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::calcDiffVectorAndSquaredDist(ConstCoordsDataPtr pt1_pos, ConstCoordsDataPtr pt2_pos,
																						ValueType diff[]) const
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
	lowerBound(lb), upperBound(ub) 
{
	if (lb > ub)
		throw Base::RangeError("VolumeConstraint: lower bound > upper bound");

	pointInds[0] = pt1_idx;
	pointInds[1] = pt2_idx;
	pointInds[2] = pt3_idx;
	pointInds[3] = pt4_idx;
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint1Index() const
{
	return pointInds[0];
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint2Index() const
{
	return pointInds[1];
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint3Index() const
{
	return pointInds[2];
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getPoint4Index() const
{
	return pointInds[3];
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
CDPL::Util::DGCoordinatesGenerator<3, T>::DGCoordinatesGenerator(): verifyConstraints(false)
{}

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
	verifyConstraints = true;
}

template <typename T>
typename CDPL::Util::DGCoordinatesGenerator<3, T>::ValueType 
CDPL::Util::DGCoordinatesGenerator<3, T>::getVolumeError() const
{
	const CoordsArray& coords = this->getCoordinates();

	ValueType error = ValueType();
	ValueType v_41[3];
	ValueType v_42[3];
	ValueType v_43[3];

	for (typename VolConstraintList::const_iterator it = volConstraints.begin(), end = volConstraints.end(); it != end; ++it) {
		const VolumeConstraint& constr = *it;
		ConstCoordsDataPtr pt4_pos = coords[constr.getPoint4Index()].getData();

		calcDiffVector(pt4_pos, coords[constr.getPoint1Index()].getData(), v_41);
		calcDiffVector(pt4_pos, coords[constr.getPoint2Index()].getData(), v_42);
		calcDiffVector(pt4_pos, coords[constr.getPoint3Index()].getData(), v_43);

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
void CDPL::Util::DGCoordinatesGenerator<3, T>::numPointsChanged()
{
	verifyConstraints = true;
}

template <typename T>
std::size_t CDPL::Util::DGCoordinatesGenerator<3, T>::getNumVolumeConstraints() const
{
	return volConstraints.size();
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::checkVolumeConstraints()
{
	if (!verifyConstraints)
		return;

	std::size_t num_pts = this->getNumPoints();

	for (typename VolConstraintList::const_iterator it = volConstraints.begin(), end = volConstraints.end(); it != end; ++it) {
		const VolumeConstraint& constr = *it;

		if (constr.getPoint1Index() >= num_pts || constr.getPoint2Index() >= num_pts ||
			constr.getPoint3Index() >= num_pts || constr.getPoint4Index() >= num_pts)
			throw Base::IndexError("DGCoordinatesGenerator: volume constraint point index out of bounds");
	}

	verifyConstraints = false;
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::adjCoordsForVolumeConstraint(CoordsArray& coords, const ValueType& lambda, std::size_t constr_idx)
{
	const VolumeConstraint& constr = volConstraints[constr_idx];

	CoordsDataPtr pt_pos[4] = {
	    coords[constr.getPoint1Index()].getData(),
		coords[constr.getPoint2Index()].getData(),
		coords[constr.getPoint3Index()].getData(),
		coords[constr.getPoint4Index()].getData() 
	};

	ValueType v_41[3];
	ValueType v_42[3];
	ValueType v_43[3];

	calcDiffVector(pt_pos[3], pt_pos[0], v_41);
	calcDiffVector(pt_pos[3], pt_pos[1], v_42);
	calcDiffVector(pt_pos[3], pt_pos[2], v_43);

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
			pt_pos[i][j] += fact * g[i][j];
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::calcDiffVector(ConstCoordsDataPtr pt1_pos, ConstCoordsDataPtr pt2_pos, ValueType diff[]) const
{
	for (std::size_t i = 0; i < 3; i++)
		diff[i] = pt2_pos[i] - pt1_pos[i];
}

// \endcond

#endif // CDPL_UTIL_DGCOORDINATESGENERATOR_HPP
