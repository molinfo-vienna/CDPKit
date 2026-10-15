#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Generic distance-geometry (DG) implementation for the generation of 2D coordinates that fulfill user-provided distance constraints.
# \see [\ref ASPE]
# 
class DG2DCoordinatesGenerator(Boost.Python.instance):

    ##
    # \brief Sequence of configured distance constraints.
    # 
    class DistanceConstraintList(Boost.Python.instance):

        ##
        # \brief Returns the number of constraints.
        # \return The number of constraints.
        # 
        def __len__() -> int: pass

        ##
        # \brief Returns the constraint at index \a idx.
        # \param idx The zero-based constraint index.
        # \return The constraint at index \a idx.
        # \throw Base.IndexError if \a idx is not in the range [0, __len__()).
        # 
        def __getitem__(idx: int) -> DistanceConstraint: pass

        ##
        # \brief Removes the element at index <em>idx</em>.
        # 
        # \param idx The zero-based index of the element to remove.
        # 
        # \throw Base.IndexError if <em>idx</em> is not in the range [0, getSize()).
        # 
        def __delitem__(idx: int) -> None: pass

    ##
    # \brief A constraint that pins the distance between two points to the interval [<em>lb</em>, <em>ub</em>].
    # 
    class DistanceConstraint(Boost.Python.instance):

        ##
        # \brief Constructs a distance constraint for the points with indices <em>pt1_idx</em> and <em>pt2_idx</em> whose Euclidean distance is to be kept in the interval [<em>lb</em>, <em>ub</em>].
        # 
        # \param pt1_idx The index of the first point.
        # \param pt2_idx The index of the second point.
        # \param lb The lower distance bound.
        # \param ub The upper distance bound.
        # 
        def __init__(pt1_idx: int, pt2_idx: int, lb: float, ub: float) -> None: pass

        ##
        # \brief Contructs a copy of the \c DistanceConstraint instance \a constr.
        # \param constr The \c DistanceConstraint instance to copy.
        # 
        def __init__(constr: DistanceConstraint) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c DistanceConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DistanceConstraint instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state with a copy of the state of the \c DistanceConstraint instance \a constr.
        # \param constr The \c DistanceConstraint instance to copy.
        # \return \a self
        # 
        def assign(constr: DistanceConstraint) -> DistanceConstraint: pass

        ##
        # \brief Returns the index of the first constrained point.
        # 
        # \return The first point index.
        # 
        def getPoint1Index() -> int: pass

        ##
        # \brief Returns the index of the second constrained point.
        # 
        # \return The second point index.
        # 
        def getPoint2Index() -> int: pass

        ##
        # \brief Returns the lower distance bound.
        # 
        # \return A reference to the lower distance bound.
        # 
        def getLowerBound() -> float: pass

        ##
        # \brief Returns the upper distance bound.
        # 
        # \return A reference to the upper distance bound.
        # 
        def getUpperBound() -> float: pass

        objectID = property(getObjectID)

        point1Index = property(getPoint1Index)

        point2Index = property(getPoint2Index)

        lowerBound = property(getLowerBound)

        upperBound = property(getUpperBound)

    ##
    # \brief Dimensionality of the coordinate space.
    # 
    COORDS_DIM = 2

    ##
    # \brief Default number of optimization cycles.
    # 
    DEF_NUM_CYCLES = 50

    ##
    # \brief Default per-cycle step-count multiplier (steps per cycle = factor * number of constraints).
    # 
    DEF_CYCLE_STEP_COUNT_FACTOR = 1.0

    ##
    # \brief Default initial learning rate.
    # 
    DEF_START_LEARNING_RATE = 1.0

    ##
    # \brief Default per-cycle decrement subtracted from the learning rate.
    # 
    DEF_LEARNING_RATE_DECREMENT = 0.019

    ##
    # \brief Contructs the \c DG2DCoordinatesGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c DG2DCoordinatesGenerator instance \a gen.
    # \param gen The \c DG2DCoordinatesGenerator instance to copy.
    # 
    def __init__(gen: DG2DCoordinatesGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DG2DCoordinatesGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DG2DCoordinatesGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c DG2DCoordinatesGenerator instance \a gen.
    # \param gen The \c DG2DCoordinatesGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: DG2DCoordinatesGenerator) -> DG2DCoordinatesGenerator: pass

    ##
    # \brief Removes all configured distance constraints.
    # 
    def clearDistanceConstraints() -> None: pass

    ##
    # \brief Returns the number of configured distance constraints.
    # 
    # \return The distance-constraint count.
    # 
    def getNumDistanceConstraints() -> int: pass

    ##
    # \brief Returns the distance constraint at index <em>idx</em>.
    # 
    # \param idx The zero-based constraint index.
    # 
    # \return A reference to the distance constraint. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumDistanceConstraints()).
    # 
    def getDistanceConstraint(idx: int) -> DistanceConstraint: pass

    ##
    # \brief Appends a new distance constraint to the list of configured constraints.
    # 
    # \param pt1_idx The index of the first point.
    # \param pt2_idx The index of the second point.
    # \param lb The lower distance bound.
    # \param ub The upper distance bound.
    # 
    def addDistanceConstraint(pt1_idx: int, pt2_idx: int, lb: float, ub: float) -> None: pass

    ##
    # \brief Removes the distance constraint at index <em>idx</em>.
    # 
    # \param idx The zero-based constraint index.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumDistanceConstraints()).
    # 
    def removeDistanceConstraint(idx: int) -> None: pass

    ##
    # \brief Sets the number of optimization cycles.
    # 
    # \param num_cycles The new cycle count.
    # 
    def setNumCycles(num_cycles: int) -> None: pass

    ##
    # \brief Returns the currently configured number of optimization cycles.
    # 
    # \return The cycle count.
    # 
    def getNumCycles() -> int: pass

    ##
    # \brief Sets the multiplier that determines the per-cycle step count (steps per cycle = factor * number of constraints).
    # 
    # \param fact The new per-cycle step-count factor.
    # 
    def setCycleStepCountFactor(fact: float) -> None: pass

    ##
    # \brief Returns the currently configured per-cycle step-count factor.
    # 
    # \return The step-count factor.
    # 
    def getCycleStepCountFactor() -> float: pass

    ##
    # \brief Sets the initial learning rate used by the first optimization cycle.
    # 
    # \param rate The new initial learning rate.
    # 
    def setStartLearningRate(rate: float) -> None: pass

    ##
    # \brief Returns the currently configured initial learning rate.
    # 
    # \return A reference to the initial learning rate.
    # 
    def getStartLearningRate() -> float: pass

    ##
    # \brief Sets the per-cycle learning rate decrement.
    # 
    # \param decr The new per-cycle learning rate decrement.
    # 
    def setLearningRateDecrement(decr: float) -> None: pass

    ##
    # \brief Returns the currently configured per-cycle learning rate decrement.
    # 
    # \return A reference to the per-cycle learning rate decrement.
    # 
    def getLearningRateDecrement() -> float: pass

    ##
    # \brief Sets the seed of the internal random number generator used to initialize the coordinates.
    # 
    # \param seed The new random seed.
    # 
    def setRandomSeed(seed: int) -> None: pass

    ##
    # \brief Generates <em>num_points</em> coordinate vectors that try to satisfy the configured constraints and stores them in <em>coords</em>.
    # 
    # \param num_points The number of points whose coordinates are to be generated.
    # \param coords The output coordinate array (resized as needed).
    # 
    def generate(num_points: int, coords: Math.Vector2DArray) -> None: pass

    ##
    # \brief Computes the cumulative squared distance error of <em>coords</em> against the configured distance constraints.
    # 
    # \param coords The input coordinate array.
    # 
    # \return The cumulative distance error.
    # 
    def getDistanceError(coords: Math.Vector2DArray) -> float: pass

    ##
    # \brief Returns a list containing the configured distance constraints.
    # \return A list containing the configured distance constraints.
    # 
    def getDistanceConstraints() -> DistanceConstraintList: pass

    objectID = property(getObjectID)

    numCycles = property(getNumCycles, setNumCycles)

    cycleStepCountFactor = property(getCycleStepCountFactor, setCycleStepCountFactor)

    startLearningRate = property(getStartLearningRate, setStartLearningRate)

    learningRateDecrement = property(getLearningRateDecrement, setLearningRateDecrement)

    numDistanceConstraints = property(getNumDistanceConstraints)

    distanceConstraints = property(getDistanceConstraints)
