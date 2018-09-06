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
#include <boost/bind.hpp>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
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
		 *        (and volume) constraints [\ref SDGM].
		 */
		template <std::size_t Dim, typename T>
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

			std::size_t getNumPoints() const;

			void setMaxNumPhase1OptimizationSteps(std::size_t num_steps);

			void setMaxNumPhase2OptimizationSteps(std::size_t num_steps);

			void setMaxError(ValueType max_err);

			bool generate();
		
			template <typename CoordsArray>
			void getCoordinates(CoordsArray& coords) const;

		protected:
			typedef Math::CVector<ValueType, Dim + 1> InternalCoordsType;
			typedef std::vector<InternalCoordsType> InternalCoordsArray;

			DGCoordinatesGeneratorBase();

			DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen);

			~DGCoordinatesGeneratorBase() {}

			DGCoordinatesGeneratorBase& operator=(const DGCoordinatesGeneratorBase& gen);

			void needConstraintCheck();

		private:
			void init();
			void checkConstraints();
			void genRandomCoords();
			bool embedCoords();

			bool minimizeError(bool phase1);

			ValueType calcError(const InternalCoordsArray& coords) const;
			ValueType calcDistanceError(const InternalCoordsArray& coords) const;
			ValueType calcDimensionError(const InternalCoordsArray& coords) const;

			ValueType calcErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const;
			ValueType calcDistanceErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const;
			ValueType calcDimensionErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const;

			ValueType calcNumErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const;

			ValueType calcDiffAndSquaredDist(const InternalCoordsType& pt1_pos, const InternalCoordsType& pt2_pos, ValueType diff[]) const;

			typedef std::vector<DistanceConstraint> DistConstraintList;
			typedef Math::BFGSMinimizer<InternalCoordsArray, ValueType> Minimizer;
			typedef boost::random::mt19937 RandNumEngine;
			typedef boost::random::uniform_real_distribution<ValueType> RandNumDist;

			std::size_t         numPoints;
			std::size_t         maxP1OptSteps;
			std::size_t         maxP2OptSteps;
			ValueType           maxError;
			ValueType           boxSize;
			InternalCoordsArray pointCoords;
			InternalCoordsArray errorGrad;
			DistConstraintList  distConstrs;
			bool                inOptPhase1;
			bool                checkConstrs;
			RandNumEngine       randEngine;
			RandNumDist         randDist;
			Minimizer           minimizer;
		};

		/**
		 * \brief Generation of coordinates that fulfill user-provided point distance constraints [\ref SDGM].
		 */
		template <std::size_t Dim, typename T>
		class DGCoordinatesGenerator : public DGCoordinatesGeneratorBase<Dim, T> 
		{

			friend class DGCoordinatesGeneratorBase<Dim, T>;

		public:
			typedef typename DGCoordinatesGeneratorBase<Dim, T>::ValueType ValueType;

		private:
			typedef typename DGCoordinatesGeneratorBase<Dim, T>::InternalCoordsArray InternalCoordsArray;

			void checkConstraints() const {}

			ValueType calcCustomError(const InternalCoordsArray& coords) const { return ValueType(); }

			ValueType calcCustomErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const { return ValueType(); }
		};

		/**
		 * \brief Generation of coordinates that fulfill user-provided point distance and volume constraints [\ref SDGM].
		 */
		template <typename T>
		class DGCoordinatesGenerator<3, T> : public DGCoordinatesGeneratorBase<3, T> 
		{

			friend class DGCoordinatesGeneratorBase<3, T>;

		public:
			typedef T ValueType;

			class VolumeConstraint
			{

			public:
				VolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, std::size_t pt4_idx, const ValueType& vol);

				std::size_t getPoint1Index() const;

				std::size_t getPoint2Index() const;

				std::size_t getPoint3Index() const;

				std::size_t getPoint4Index() const;

				const ValueType& getVolume() const;

			private:
				std::size_t pointInds[4];
				ValueType   volume;
			};

			void clearVolumeConstraints();

			void addVolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, std::size_t pt4_idx, const ValueType& vol);

		private:
			typedef typename DGCoordinatesGeneratorBase<3, T>::InternalCoordsArray InternalCoordsArray;

			void checkConstraints() const;

			ValueType calcCustomError(const InternalCoordsArray& coords) const;
			ValueType calcCustomErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const;

			typedef std::vector<VolumeConstraint> VolConstraintList;

			VolConstraintList volConstrs;
		};

		/**
		 * @}
		 */
    }
}


// DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint implementation

template <std::size_t Dim, typename T>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint::DistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, 
																					   const ValueType& lb, const ValueType& ub):
	point1Idx(pt1_idx), point2Idx(pt2_idx), lowerBound(lb), upperBound(ub) 
{
	if (lb < ValueType() || ub < ValueType())
		throw Base::ValueError("DistanceConstraint: specified distance < 0");
	
	if (lb > ub)
		throw Base::RangeError("DistanceConstraint: lower bound > upper bound");
}

template <std::size_t Dim, typename T>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint::getPoint1Index() const
{
	return point1Idx;
}

template <std::size_t Dim, typename T>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint::getPoint2Index() const
{
	return point2Idx;
}

template <std::size_t Dim, typename T>
const T& CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint::getLowerBound() const
{
	return lowerBound;
}

template <std::size_t Dim, typename T>
const T& CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint::getUpperBound() const
{
	return upperBound;
}

// DGCoordinatesGeneratorBase<Dim, T> implementation

template <std::size_t Dim, typename T>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DGCoordinatesGeneratorBase(): 
	numPoints(0), maxP1OptSteps(1000), maxP2OptSteps(1000), maxError(0.5), boxSize(10), checkConstrs(false), 
	randDist(-0.5, 0.5), minimizer(boost::bind(&DGCoordinatesGeneratorBase::calcError, this, _1),
								   boost::bind(&DGCoordinatesGeneratorBase::calcErrorGradient, this, _1, _2)) 
{}
	
template <std::size_t Dim, typename T>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen): 
	numPoints(gen.numPoints), maxP1OptSteps(gen.maxP1OptSteps), maxP2OptSteps(gen.maxP2OptSteps), maxError(gen.maxError), 
	boxSize(gen.boxSize), checkConstrs(gen.checkConstrs), pointCoords(gen.pointCoords), distConstrs(gen.distConstrs),
	randDist(-0.5, 0.5), minimizer(boost::bind(&DGCoordinatesGeneratorBase::calcError, this, _1),
								   boost::bind(&DGCoordinatesGeneratorBase::calcErrorGradient, this, _1, _2)) 
{}

template <std::size_t Dim, typename T>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>& 
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::operator=(const DGCoordinatesGeneratorBase& gen)
{
	if (&gen == this)
		return *this;

	numPoints = gen.numPoints;
	maxP1OptSteps = gen.maxP1OptSteps;
	maxP2OptSteps = gen.maxP2OptSteps;
	maxError = gen.maxError; 
	boxSize = gen.boxSize;
	checkConstrs = gen.checkConstrs;
	pointCoords = gen.pointCoords;
	distConstrs = gen.distConstrs;

	return *this;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::clearDistanceConstraints()
{
	distConstrs.clear();	
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::addDistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, 
																	   const ValueType& lb, const ValueType& ub)
{
	distConstrs.push_back(DistanceConstraint(pt1_idx, pt2_idx, lb, ub));
	checkConstrs = true;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::setBoxSize(const ValueType& size)
{
	boxSize = size;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::setNumPoints(std::size_t num_points)
{
	numPoints = num_points;
	checkConstrs = true;
}

template <std::size_t Dim, typename T>
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::getNumPoints() const
{
	return numPoints;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::setMaxNumPhase1OptimizationSteps(std::size_t num_steps)
{
	maxP1OptSteps = num_steps;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::setMaxNumPhase2OptimizationSteps(std::size_t num_steps)
{
	maxP2OptSteps = num_steps;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::setMaxError(ValueType max_err)
{
	maxError = max_err;
}

template <std::size_t Dim, typename T>
bool CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::generate()
{
	init();

	checkConstraints();
	genRandomCoords();
	
	return embedCoords();
}

template <std::size_t Dim, typename T>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::getCoordinates(CoordsArray& coords) const
{
	for (std::size_t i = 0, num_pts = pointCoords.size(); i < num_pts; i++) {
		const typename InternalCoordsType::ConstPointer pt_pos_data = pointCoords[i].getData();

		for (std::size_t j = 0; j < Dim; j++)
			coords[i][j] = pt_pos_data[j];
	}
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::needConstraintCheck()
{
	checkConstraints = true;
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::init()
{
	pointCoords.resize(numPoints);
	errorGrad.resize(numPoints);
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::checkConstraints()
{
	if (!checkConstrs)
		return;

	for (typename DistConstraintList::const_iterator it = distConstrs.begin(), end = distConstrs.end(); it != end; ++it) {
		const DistanceConstraint& constr = *it;

		if (constr.getPoint1Index() >= numPoints || constr.getPoint2Index() >= numPoints)
			throw Base::IndexError("DGCoordinatesGeneratorBase: distance constraint point index out of bounds");
	}

	static_cast<const DGCoordinatesGenerator<Dim, T>&>(*this).checkConstraints();

	checkConstrs = false;
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcError(const InternalCoordsArray& coords) const
{
	if (inOptPhase1)
		return (calcDistanceError(coords) + static_cast<const DGCoordinatesGenerator<Dim, T>&>(*this).calcCustomError(coords));

	return (calcDistanceError(coords)  + static_cast<const DGCoordinatesGenerator<Dim, T>&>(*this).calcCustomError(coords) +
			calcDimensionError(coords));
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcDistanceError(const InternalCoordsArray& coords) const
{
	ValueType error = ValueType();
	ValueType pos_diff[Dim + 1];

	for (typename DistConstraintList::const_iterator it = distConstrs.begin(), end = distConstrs.end(); it != end; ++it) {
		const DistanceConstraint& constr = *it;

		ValueType dist_2 = calcDiffAndSquaredDist(coords[constr.getPoint1Index()], coords[constr.getPoint2Index()], pos_diff);

		ValueType ub = constr.getUpperBound();
		ValueType tmp1 = dist_2 / (ub * ub) - 1;
		ValueType ub_err = tmp1 * tmp1;

		if (ub_err > ValueType())
			error += ub_err;

		ValueType lb = constr.getLowerBound();
		ValueType lb_2 = lb * lb;
		ValueType tmp2 = 2 * lb_2 / (lb_2 + dist_2) - 1;
		ValueType lb_err = tmp2 * tmp2;

		if (lb_err > ValueType())
			error += lb_err;
	}

	return error;
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcDimensionError(const InternalCoordsArray& coords) const
{
	ValueType error = ValueType();

	for (typename InternalCoordsArray::const_iterator it = coords.begin(), end = coords.end(); it != end; ++it) {
		ValueType extra_dim = it->getData()[Dim];

		error += extra_dim * extra_dim;
	}

	return error;
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const
{
	for (typename InternalCoordsArray::iterator it = grad.begin(), end = grad.end(); it != end; ++it)
		it->clear();

	if (inOptPhase1)
		return (calcDistanceErrorGradient(coords, grad) + 
				static_cast<const DGCoordinatesGenerator<Dim, T>&>(*this).calcCustomErrorGradient(coords, grad));

	return (calcDistanceErrorGradient(coords, grad) + 
			static_cast<const DGCoordinatesGenerator<Dim, T>&>(*this).calcCustomErrorGradient(coords, grad) +
			calcDimensionErrorGradient(coords, grad));
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcDistanceErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const
{
	ValueType error = ValueType();
	ValueType pos_diff[Dim + 1];

	for (typename DistConstraintList::const_iterator it = distConstrs.begin(), end = distConstrs.end(); it != end; ++it) {
		const DistanceConstraint& constr = *it;
		std::size_t pt1_idx = constr.getPoint1Index();
		std::size_t pt2_idx = constr.getPoint2Index();
		ValueType ub = constr.getUpperBound();
		ValueType lb = constr.getLowerBound();

		typename InternalCoordsType::Pointer pt1_grad_data = grad[pt1_idx].getData();
		typename InternalCoordsType::Pointer pt2_grad_data = grad[pt2_idx].getData();

		ValueType dist_2 = calcDiffAndSquaredDist(coords[pt1_idx], coords[pt2_idx], pos_diff);

		ValueType ub_2 = ub * ub;
		ValueType tmp1 = dist_2 / ub_2 - 1;
		ValueType ub_err = tmp1 * tmp1;
		
		if (ub_err > ValueType()) {
			ValueType grad_fact = 4 * tmp1 / ub_2;

			for (std::size_t i = 0; i < Dim + 1; i++) {
				ValueType dv = pos_diff[i] * grad_fact;

				pt1_grad_data[i] -= dv;
				pt2_grad_data[i] += dv;
			}

			error += ub_err;
		}

		ValueType lb_2 = lb * lb;
		ValueType g = lb_2 + dist_2;
		ValueType tmp2 = 2 * lb_2 / g - 1;
		ValueType lb_err = tmp2 * tmp2;

		if (lb_err > ValueType()) {
			ValueType grad_fact = -8 * tmp2 * lb_2 / (g * g);

			for (std::size_t i = 0; i < Dim + 1; i++) {
				ValueType dv = pos_diff[i] * grad_fact;

				pt1_grad_data[i] -= dv;
				pt2_grad_data[i] += dv;
			}

			error += lb_err;
		}
	}

	return error;
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcDimensionErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const
{
	ValueType error = ValueType();

	typename InternalCoordsArray::iterator g_it = grad.begin();

	for (typename InternalCoordsArray::const_iterator c_it = coords.begin(), c_end = coords.end(); c_it != c_end; ++c_it, ++g_it) {
		ValueType extra_dim = c_it->getData()[Dim];

		error += extra_dim * extra_dim;
		g_it->getData()[Dim] += 2 * extra_dim;
	}

	return error;
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcNumErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const
{
	static const ValueType EPSILON = 0.0000001;

	for (std::size_t i = 0; i < numPoints; i++) {
		InternalCoordsType& pt_pos = const_cast<InternalCoordsType&>(coords[i]);
		InternalCoordsType& pt_grad = grad[i];

		for (std::size_t j = 0; j < Dim + 1; j++) { 
			ValueType tmp = pt_pos[j];
			
			pt_pos[j] = tmp + EPSILON;
			ValueType e1 = calcError(coords);

			pt_pos[j] = tmp - EPSILON;
			ValueType e2 = calcError(coords);

			pt_pos[j] = tmp;
			pt_grad[j] = (e1 - e2) / (2 * EPSILON);
		}
	}

	return calcError(coords);
}

template <std::size_t Dim, typename T>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::genRandomCoords()
{
	for (typename InternalCoordsArray::iterator it = pointCoords.begin(), end = pointCoords.end(); it != end; ++it) {
		InternalCoordsType& pt_pos = *it;

		for (std::size_t i = 0; i < Dim + 1; i++)
			pt_pos[i] = randDist(randEngine) * boxSize;
	}
}

template <std::size_t Dim, typename T>
bool CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::embedCoords()
{
	minimizeError(true);

	return minimizeError(false);
}

template <std::size_t Dim, typename T>
T CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::calcDiffAndSquaredDist(const InternalCoordsType& pt1_pos, const InternalCoordsType& pt2_pos, ValueType diff[]) const
{
	ValueType dist_2 = ValueType();

	typename InternalCoordsType::ConstPointer pt1_pos_data = pt1_pos.getData();
	typename InternalCoordsType::ConstPointer pt2_pos_data = pt2_pos.getData();

	for (std::size_t i = 0; i < Dim + 1; i++) {
		diff[i] = pt2_pos_data[i] - pt1_pos_data[i];
		dist_2 += diff[i] * diff[i];
	}

	return dist_2;
}

template <std::size_t Dim, typename T>
bool CDPL::Util::DGCoordinatesGeneratorBase<Dim, T>::minimizeError(bool phase1)
{
	inOptPhase1 = phase1;

	ValueType error = ValueType();

	minimizer.setup(pointCoords, errorGrad);

	for (std::size_t i = 0, max_num_steps = phase1 ? maxP1OptSteps : maxP2OptSteps; i < max_num_steps; i++) { 
		typename Minimizer::Status status = minimizer.iterate(error, pointCoords, errorGrad);

		if (status != Minimizer::SUCCESS)
			return false;
		
		//std::cerr << "i = " << i << "; error = " << error << std::endl;

		if (error <= maxError)
			return true;
	}

	return false;
}


// DGCoordinatesGenerator<3, T>::VolumeConstraint implementation

template <typename T>
CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::VolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, 
																			 std::size_t pt3_idx, std::size_t pt4_idx, 
																			 const ValueType& vol): volume(vol) 
{
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
const T& CDPL::Util::DGCoordinatesGenerator<3, T>::VolumeConstraint::getVolume() const
{
	return volume;
}


// DGCoordinatesGenerator<3, T> implementation

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::clearVolumeConstraints()
{
	volConstrs.clear();
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::addVolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx, std::size_t pt4_idx, const ValueType& vol)
{
	volConstrs.push_back(VolumeConstraint(pt1_idx, pt2_idx, pt3_idx, pt4_idx, vol));
	this->needConstraintCheck();
}

template <typename T>
void CDPL::Util::DGCoordinatesGenerator<3, T>::checkConstraints() const
{
	std::size_t num_pts = this->getNumPoints();

	for (typename VolConstraintList::const_iterator it = volConstrs.begin(), end = volConstrs.end(); it != end; ++it) {
		const VolumeConstraint& constr = *it;

		if (constr.getPoint1Index() >= num_pts || constr.getPoint2Index() >= num_pts ||
			constr.getPoint3Index() >= num_pts || constr.getPoint4Index() >= num_pts)
			throw Base::IndexError("DGCoordinatesGenerator: volume constraint point index out of bounds");
	}
}

template <typename T>
T CDPL::Util::DGCoordinatesGenerator<3, T>::calcCustomError(const InternalCoordsArray& coords) const
{
	return ValueType(); // TODO
}

template <typename T>
T CDPL::Util::DGCoordinatesGenerator<3, T>::calcCustomErrorGradient(const InternalCoordsArray& coords, InternalCoordsArray& grad) const
{
	return ValueType(); // TODO
}

#endif // CDPL_UTIL_DGCOORDINATESGENERATOR_HPP
