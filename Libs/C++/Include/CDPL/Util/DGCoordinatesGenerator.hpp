/* 
 * DGCoordinatesGenerator.hpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
         * \brief Serves as foundation for subclasses that perform coordinates generation based on distance-geometry.
         * \tparam Dim The dimension of the coordinates to generate.
         * \tparam T The scalar value type to use for coordinates and constraint bounds.
         * \tparam Derived The type of the subclass.
         * \see [\ref ASPE]
         */
        template <std::size_t Dim, typename T, typename Derived>
        class DGCoordinatesGeneratorBase
        {

          public:
            class DistanceConstraint;

          private:
            typedef std::vector<DistanceConstraint> DistanceConstraintList;

          public:
            /**
             * \brief A mutable iterator over the configured distance constraints.
             */
            typedef typename DistanceConstraintList::iterator       DistanceConstraintIterator;

            /**
             * \brief A constant iterator over the configured distance constraints.
             */
            typedef typename DistanceConstraintList::const_iterator ConstDistanceConstraintIterator;

            /**
             * \brief The scalar value type used for coordinates and constraint bounds.
             */
            typedef T                                               ValueType;

            /**
             * \brief Dimensionality of the coordinate space.
             */
            static constexpr std::size_t COORDS_DIM                  = Dim;

            /**
             * \brief Default number of optimization cycles.
             */
            static constexpr std::size_t DEF_NUM_CYCLES              = 50;

            /**
             * \brief Default per-cycle step-count multiplier (steps per cycle = factor * number of constraints).
             */
            static constexpr double      DEF_CYCLE_STEP_COUNT_FACTOR = 1.0;

            /**
             * \brief Default initial learning rate.
             */
            static constexpr ValueType   DEF_START_LEARNING_RATE     = 1;

            /**
             * \brief Default per-cycle decrement subtracted from the learning rate.
             */
            static constexpr ValueType   DEF_LEARNING_RATE_DECREMENT = 0.95 / 50;

            /**
             * \brief A constraint that pins the distance between two points to the interval [\a lb, \a ub].
             */
            class DistanceConstraint
            {

              public:
                /**
                 * \brief Constructs a distance constraint for the points with indices \a pt1_idx and \a pt2_idx
                 *        whose Euclidean distance is to be kept in the interval [\a lb, \a ub].
                 * \param pt1_idx The index of the first point.
                 * \param pt2_idx The index of the second point.
                 * \param lb The lower distance bound.
                 * \param ub The upper distance bound.
                 */
                DistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, const ValueType& lb, const ValueType& ub);

                /**
                 * \brief Returns the index of the first constrained point.
                 * \return The first point index.
                 */
                std::size_t getPoint1Index() const;

                /**
                 * \brief Returns the index of the second constrained point.
                 * \return The second point index.
                 */
                std::size_t getPoint2Index() const;

                /**
                 * \brief Returns the lower distance bound.
                 * \return A \c const reference to the lower distance bound.
                 */
                const ValueType& getLowerBound() const;

                /**
                 * \brief Returns the upper distance bound.
                 * \return A \c const reference to the upper distance bound.
                 */
                const ValueType& getUpperBound() const;

                /**
                 * \brief Lexicographic less-than comparison on (point1Idx, point2Idx).
                 * \param constr The constraint to compare against.
                 * \return \c true if this constraint precedes \a constr in lexicographic order, and \c false otherwise.
                 */
                bool operator<(const DistanceConstraint& constr) const;

              private:
                std::size_t point1Idx;
                std::size_t point2Idx;
                ValueType   lowerBound;
                ValueType   upperBound;
            };

            /**
             * \brief Removes all configured distance constraints.
             */
            void clearDistanceConstraints();

            /**
             * \brief Appends a new distance constraint to the list of configured constraints.
             * \param pt1_idx The index of the first point.
             * \param pt2_idx The index of the second point.
             * \param lb The lower distance bound.
             * \param ub The upper distance bound.
             */
            void addDistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx, const ValueType& lb, const ValueType& ub);

            /**
             * \brief Returns the number of configured distance constraints.
             * \return The distance-constraint count.
             */
            std::size_t getNumDistanceConstraints() const;

            /**
             * \brief Returns the distance constraint at index \a idx.
             * \param idx The zero-based constraint index.
             * \return A \c const reference to the distance constraint.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDistanceConstraints()).
             */
            const DistanceConstraint& getDistanceConstraint(std::size_t idx) const;

            /**
             * \brief Returns the distance constraint at index \a idx.
             * \param idx The zero-based constraint index.
             * \return A reference to the distance constraint.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDistanceConstraints()).
             */
            DistanceConstraint& getDistanceConstraint(std::size_t idx);

            /**
             * \brief Removes the distance constraint at index \a idx.
             * \param idx The zero-based constraint index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDistanceConstraints()).
             */
            void removeDistanceConstraint(std::size_t idx);

            /**
             * \brief Removes the distance constraint referenced by iterator \a it.
             * \param it The iterator pointing to the distance constraint.
             * \throw Base::IndexError if \a it is not in the range [getDistanceConstraintsBegin(), getDistanceConstraintsEnd()).
             */
            void removeDistanceConstraint(const DistanceConstraintIterator& it);

            /**
             * \brief Returns a mutable iterator pointing to the first distance constraint.
             * \return A mutable iterator pointing to the first distance constraint.
             */
            DistanceConstraintIterator getDistanceConstraintsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last distance constraint.
             * \return A mutable iterator pointing one past the last distance constraint.
             */
            DistanceConstraintIterator getDistanceConstraintsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first distance constraint.
             * \return A constant iterator pointing to the first distance constraint.
             */
            ConstDistanceConstraintIterator getDistanceConstraintsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last distance constraint.
             * \return A constant iterator pointing one past the last distance constraint.
             */
            ConstDistanceConstraintIterator getDistanceConstraintsEnd() const;

            /**
             * \brief Sets the number of optimization cycles.
             * \param num_cycles The new cycle count.
             */
            void setNumCycles(std::size_t num_cycles);

            /**
             * \brief Sets the multiplier that determines the per-cycle step count (steps per cycle = factor * number of constraints).
             * \param fact The new per-cycle step-count factor.
             */
            void setCycleStepCountFactor(double fact);

            /**
             * \brief Sets the initial learning rate used by the first optimization cycle.
             * \param rate The new initial learning rate.
             */
            void setStartLearningRate(const ValueType& rate);

            /**
             * \brief Sets the per-cycle learning-rate decrement.
             * \param decr The new per-cycle learning-rate decrement.
             */
            void setLearningRateDecrement(const ValueType& decr);

            /**
             * \brief Returns the currently configured number of optimization cycles.
             * \return The cycle count.
             */
            std::size_t getNumCycles() const;

            /**
             * \brief Returns the currently configured per-cycle step-count factor.
             * \return The step-count factor.
             */
            double getCycleStepCountFactor() const;

            /**
             * \brief Returns the currently configured initial learning rate.
             * \return A \c const reference to the initial learning rate.
             */
            const ValueType& getStartLearningRate() const;

            /**
             * \brief Returns the currently configured per-cycle learning-rate decrement.
             * \return A \c const reference to the per-cycle learning-rate decrement.
             */
            const ValueType& getLearningRateDecrement() const;

            /**
             * \brief Sets the seed of the internal random number generator used to initialize the coordinates.
             * \param seed The new random seed.
             */
            void setRandomSeed(unsigned int seed);

            /**
             * \brief Generates \a num_points coordinate vectors that try to satisfy the configured constraints and stores them in \a coords.
             * \tparam CoordsArray The output coordinate-array type (must be index-accessible and writable).
             * \param num_points The number of points whose coordinates are to be generated.
             * \param coords The output coordinate array (resized as needed).
             */
            template <typename CoordsArray>
            void generate(std::size_t num_points, CoordsArray& coords);

            /**
             * \brief Computes the cumulative squared distance error of \a coords against the configured distance constraints.
             * \tparam CoordsArray The input coordinate-array type.
             * \param coords The input coordinate array.
             * \return The cumulative distance error.
             */
            template <typename CoordsArray>
            ValueType getDistanceError(const CoordsArray& coords) const;

            /**
             * \brief Sorts the configured distance constraints in lexicographic order.
             */
            void orderDistanceConstraints();

          protected:
            DGCoordinatesGeneratorBase();

            DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen);

            ~DGCoordinatesGeneratorBase() {}

            DGCoordinatesGeneratorBase& operator=(const DGCoordinatesGeneratorBase& gen);

          private:
            std::size_t getNumVolumeConstraints() const;

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

            typedef boost::random::mt11213b RandNumEngine;

            std::size_t            numCycles;
            double                 cycleStepCountFactor;
            ValueType              startLearningRate;
            ValueType              learningRateDecr;
            DistanceConstraintList distConstraints;
            RandNumEngine          randomEngine;
        };

        template <std::size_t Dim, typename T, typename Derived>
        constexpr std::size_t DGCoordinatesGeneratorBase<Dim, T, Derived>::COORDS_DIM;

        template <std::size_t Dim, typename T, typename Derived>
        constexpr std::size_t DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_NUM_CYCLES;

        template <std::size_t Dim, typename T, typename Derived>
        constexpr double DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_CYCLE_STEP_COUNT_FACTOR;

        template <std::size_t Dim, typename T, typename Derived>
        constexpr typename DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType
            DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_START_LEARNING_RATE;

        template <std::size_t Dim, typename T, typename Derived>
        constexpr typename DGCoordinatesGeneratorBase<Dim, T, Derived>::ValueType
            DGCoordinatesGeneratorBase<Dim, T, Derived>::DEF_LEARNING_RATE_DECREMENT;


        /**
         * \brief Generic distance-geometry implementation for the generation of coordinates that fulfill user-provided distance constraints.
         * \tparam Dim The dimension of the coordinates to generate.
         * \tparam T The scalar value type to use for coordinates and constraint bounds.
         * \see [\ref ASPE]
         */
        template <std::size_t Dim, typename T>
        class DGCoordinatesGenerator : public DGCoordinatesGeneratorBase<Dim, T, DGCoordinatesGenerator<Dim, T> >
        {};


        /**
         * \brief Specialized distance-geometry implementation for the generation of 3D coordinates that fulfill user-provided distance and volume constraints.
         * \tparam T The scalar value type to use for coordinates and constraint bounds.
         * \see [\ref ASPE]
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
            /**
             * \brief The scalar value type used for coordinates and constraint bounds.
             */
            typedef typename BaseType::ValueType                  ValueType;

            /**
             * \brief A mutable iterator over the configured volume constraints.
             */
            typedef typename VolumeConstraintList::iterator       VolumeConstraintIterator;

            /**
             * \brief A constant iterator over the configured volume constraints.
             */
            typedef typename VolumeConstraintList::const_iterator ConstVolumeConstraintIterator;

            /**
             * \brief A constraint that pins the signed tetrahedral volume spanned by four points to the interval [\a lb, \a ub].
             */
            class VolumeConstraint
            {

              public:
                /**
                 * \brief Constructs a volume constraint for the tetrahedron spanned by the four points with the given indices.
                 * \param pt1_idx The index of the first point.
                 * \param pt2_idx The index of the second point.
                 * \param pt3_idx The index of the third point.
                 * \param pt4_idx The index of the fourth point.
                 * \param lb The lower volume bound.
                 * \param ub The upper volume bound.
                 */
                VolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx,
                                 std::size_t pt4_idx, const ValueType& lb, const ValueType& ub);

                /**
                 * \brief Returns the index of the first constrained point.
                 * \return The first point index.
                 */
                std::size_t getPoint1Index() const;

                /**
                 * \brief Returns the index of the second constrained point.
                 * \return The second point index.
                 */
                std::size_t getPoint2Index() const;

                /**
                 * \brief Returns the index of the third constrained point.
                 * \return The third point index.
                 */
                std::size_t getPoint3Index() const;

                /**
                 * \brief Returns the index of the fourth constrained point.
                 * \return The fourth point index.
                 */
                std::size_t getPoint4Index() const;

                /**
                 * \brief Returns the lower volume bound.
                 * \return A \c const reference to the lower volume bound.
                 */
                const ValueType& getLowerBound() const;

                /**
                 * \brief Returns the upper volume bound.
                 * \return A \c const reference to the upper volume bound.
                 */
                const ValueType& getUpperBound() const;

              private:
                std::size_t point1Idx;
                std::size_t point2Idx;
                std::size_t point3Idx;
                std::size_t point4Idx;
                ValueType   lowerBound;
                ValueType   upperBound;
            };

            /**
             * \brief Removes all configured volume constraints.
             */
            void clearVolumeConstraints();

            /**
             * \brief Appends a new volume constraint to the list of configured constraints.
             * \param pt1_idx The index of the first point.
             * \param pt2_idx The index of the second point.
             * \param pt3_idx The index of the third point.
             * \param pt4_idx The index of the fourth point.
             * \param lb The lower volume bound.
             * \param ub The upper volume bound.
             */
            void addVolumeConstraint(std::size_t pt1_idx, std::size_t pt2_idx, std::size_t pt3_idx,
                                     std::size_t pt4_idx, const ValueType& lb, const ValueType& ub);

            /**
             * \brief Returns the number of configured volume constraints.
             * \return The volume-constraint count.
             */
            std::size_t getNumVolumeConstraints() const;

            /**
             * \brief Returns the volume constraint at index \a idx.
             * \param idx The zero-based constraint index.
             * \return A \c const reference to the volume constraint.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumVolumeConstraints()).
             */
            const VolumeConstraint& getVolumeConstraint(std::size_t idx) const;

            /**
             * \brief Returns the volume constraint at index \a idx.
             * \param idx The zero-based constraint index.
             * \return A reference to the volume constraint.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumVolumeConstraints()).
             */
            VolumeConstraint& getVolumeConstraint(std::size_t idx);

            /**
             * \brief Removes the volume constraint at index \a idx.
             * \param idx The zero-based constraint index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumVolumeConstraints()).
             */
            void removeVolumeConstraint(std::size_t idx);

            /**
             * \brief Removes the volume constraint referenced by iterator \a it.
             * \param it The iterator pointing to the volume constraint.
             * \throw Base::IndexError if \a it is not in the range [getVolumeConstraintsBegin(), getVolumeConstraintsEnd()).
             */
            void removeVolumeConstraint(const VolumeConstraintIterator& it);

            /**
             * \brief Returns a mutable iterator pointing to the first volume constraint.
             * \return A mutable iterator pointing to the first volume constraint.
             */
            VolumeConstraintIterator getVolumeConstraintsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last volume constraint.
             * \return A mutable iterator pointing one past the last volume constraint.
             */
            VolumeConstraintIterator getVolumeConstraintsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first volume constraint.
             * \return A constant iterator pointing to the first volume constraint.
             */
            ConstVolumeConstraintIterator getVolumeConstraintsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last volume constraint.
             * \return A constant iterator pointing one past the last volume constraint.
             */
            ConstVolumeConstraintIterator getVolumeConstraintsEnd() const;

            /**
             * \brief Computes the cumulative volume error of \a coords against the configured volume constraints.
             * \tparam CoordsArray The input coordinate-array type.
             * \param coords The input coordinate array.
             * \return The cumulative volume error.
             */
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
         * \brief Convenience alias for the 3D coordinates generator with double-precision values.
         */
        typedef DGCoordinatesGenerator<3, double> DG3DCoordinatesGenerator;
    } // namespace Util
} // namespace CDPL


// \cond DOC_IMPL_DETAILS
// DGCoordinatesGeneratorBase<Dim, T>::DistanceConstraint implementation

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::DistanceConstraint(std::size_t pt1_idx, std::size_t pt2_idx,
                                                                                                const ValueType& lb, const ValueType& ub):
    point1Idx(pt1_idx),
    point2Idx(pt2_idx), lowerBound(lb), upperBound(ub)
{}

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

template <std::size_t Dim, typename T, typename Derived>
bool CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DistanceConstraint::operator<(const DistanceConstraint& constr) const
{
    if (point1Idx < constr.point1Idx)
        return true;

    if (point1Idx == constr.point1Idx)
        return (point2Idx < constr.point2Idx);

    return false;
}


// DGCoordinatesGeneratorBase<Dim, T, Derived> implementation

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DGCoordinatesGeneratorBase():
    numCycles(DEF_NUM_CYCLES), cycleStepCountFactor(DEF_CYCLE_STEP_COUNT_FACTOR), startLearningRate(DEF_START_LEARNING_RATE),
    learningRateDecr(DEF_LEARNING_RATE_DECREMENT), randomEngine(170375)
{}

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::DGCoordinatesGeneratorBase(const DGCoordinatesGeneratorBase& gen):
    numCycles(gen.numCycles), cycleStepCountFactor(gen.cycleStepCountFactor),
    startLearningRate(gen.startLearningRate), learningRateDecr(gen.learningRateDecr),
    distConstraints(gen.distConstraints),
    randomEngine(gen.randomEngine)
{}

template <std::size_t Dim, typename T, typename Derived>
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>&
CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::operator=(const DGCoordinatesGeneratorBase& gen)
{
    if (&gen == this)
        return *this;

    numCycles            = gen.numCycles;
    cycleStepCountFactor = gen.cycleStepCountFactor;
    startLearningRate    = gen.startLearningRate;
    learningRateDecr     = gen.learningRateDecr;
    distConstraints      = gen.distConstraints;
    randomEngine         = gen.randomEngine;

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
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setNumCycles(std::size_t num_cycles)
{
    numCycles = num_cycles;
}

template <std::size_t Dim, typename T, typename Derived>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setCycleStepCountFactor(double fact)
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
std::size_t CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getNumCycles() const
{
    return numCycles;
}

template <std::size_t Dim, typename T, typename Derived>
double CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::getCycleStepCountFactor() const
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
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::setRandomSeed(unsigned int seed)
{
    randomEngine.seed(seed);
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
        ValueType dist   = std::sqrt(dist_2);
        ValueType lb     = constr.getLowerBound();
        ValueType ub     = constr.getUpperBound();

        if (dist >= lb && dist <= ub)
            continue;

        if (dist < lb) {
            ValueType tmp = (dist_2 - lb * lb) / (0.000001 + lb * lb);

            error += tmp * tmp;

        } else {
            ValueType tmp = (dist_2 - ub * ub) / (0.000001 + ub * ub);

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
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::orderDistanceConstraints()
{
    std::sort(distConstraints.begin(), distConstraints.end());
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::generate(std::size_t num_points, CoordsArray& coords)
{
    embedCoords(num_points, coords);
}

template <std::size_t Dim, typename T, typename Derived>
template <typename CoordsArray>
void CDPL::Util::DGCoordinatesGeneratorBase<Dim, T, Derived>::embedCoords(std::size_t num_points, CoordsArray& coords)
{
    std::size_t num_dist_constrs = distConstraints.size();
    std::size_t num_vol_constrs  = static_cast<Derived&>(*this).getNumVolumeConstraints();

    if ((num_dist_constrs + num_vol_constrs) == 0)
        return;

    std::size_t num_steps = std::size_t((num_dist_constrs + num_vol_constrs) * cycleStepCountFactor);
    ValueType lambda    = startLearningRate;

    if (num_dist_constrs > 0 && num_vol_constrs > 0) {
        boost::random::uniform_int_distribution<std::size_t> constr_sd(0, num_dist_constrs + num_vol_constrs - 1);

        for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr) {
            for (std::size_t j = 0; j < num_steps; j++) {
                std::size_t constr_idx = constr_sd(randomEngine);

                if (constr_idx < num_dist_constrs)
                    adjCoordsForDistanceConstraint(coords, lambda, constr_idx);
                else
                    static_cast<Derived&>(*this).template adjCoordsForVolumeConstraint<CoordsArray>(coords, lambda, constr_idx - num_dist_constrs);
            }
        }

        return;
    }

    if (num_dist_constrs > 0) {
        boost::random::uniform_int_distribution<std::size_t> constr_sd(0, num_dist_constrs - 1);

        for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr)
            for (std::size_t j = 0; j < num_steps; j++)
                adjCoordsForDistanceConstraint(coords, lambda, constr_sd(randomEngine));

        return;
    }

    boost::random::uniform_int_distribution<std::size_t> constr_sd(0, num_vol_constrs - 1);

    for (std::size_t i = 0; i < numCycles; i++, lambda -= learningRateDecr)
        for (std::size_t j = 0; j < num_steps; j++)
            static_cast<Derived&>(*this).template adjCoordsForVolumeConstraint<CoordsArray>(coords, lambda, constr_sd(randomEngine));
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

    ValueType bound  = (dist > ub ? ub : lb);
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
    point1Idx(pt1_idx),
    point2Idx(pt2_idx), point3Idx(pt3_idx), point4Idx(pt4_idx), lowerBound(lb), upperBound(ub)
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

        ValueType vol = (v_41[0] * (v_42[1] * v_43[2] - v_42[2] * v_43[1]) - v_41[1] * (v_42[0] * v_43[2] - v_42[2] * v_43[0]) + v_41[2] * (v_42[0] * v_43[1] - v_42[1] * v_43[0])) / 6;

        ValueType lb = constr.getLowerBound();
        ValueType ub = constr.getUpperBound();

        if (vol >= lb && vol <= ub)
            continue;

        if (vol < lb) {
            ValueType tmp = (vol - lb);

            error += tmp * tmp;

        } else {
            ValueType tmp = (vol - ub);

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
    Vec*      pt_pos[4] = {&pt1_pos, &pt2_pos, &pt3_pos, &pt4_pos};
    ValueType v_41[3];
    ValueType v_42[3];
    ValueType v_43[3];

    calcDiffVector(*pt_pos[3], *pt_pos[0], v_41);
    calcDiffVector(*pt_pos[3], *pt_pos[1], v_42);
    calcDiffVector(*pt_pos[3], *pt_pos[2], v_43);

    ValueType g[4][3];

    g[0][0] = (v_42[1] * v_43[2] - v_42[2] * v_43[1]) / 6;
    g[0][1] = -(v_42[0] * v_43[2] - v_42[2] * v_43[0]) / 6;
    g[0][2] = (v_42[0] * v_43[1] - v_42[1] * v_43[0]) / 6;

    ValueType vol = (v_41[0] * g[0][0] + v_41[1] * g[0][1] + v_41[2] * g[0][2]);
    ValueType ub  = constr.getUpperBound();
    ValueType lb  = constr.getLowerBound();

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
    ValueType fact  = lambda * (bound - vol) / g_len2_sum;

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
