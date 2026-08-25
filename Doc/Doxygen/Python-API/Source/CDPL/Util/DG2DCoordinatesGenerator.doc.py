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
# \brief 
#
class DG2DCoordinatesGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class DistanceConstraintList(Boost.Python.instance):

        def __len__() -> int: pass

        def __getitem__(idx: int) -> DistanceConstraint: pass

        def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    #
    class DistanceConstraint(Boost.Python.instance):

        ##
        # \brief Initializes the \c %DistanceConstraint instance.
        # \param pt1_idx 
        # \param pt2_idx 
        # \param lb 
        # \param ub 
        # 
        def __init__(pt1_idx: int, pt2_idx: int, lb: float, ub: float) -> None: pass

        ##
        # \brief Initializes a copy of the \c %DistanceConstraint instance \a constr.
        # \param constr The \c %DistanceConstraint instance to copy.
        # 
        def __init__(constr: DistanceConstraint) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %DistanceConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DistanceConstraint instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %DistanceConstraint instance \a constr.
        # \param constr The \c %DistanceConstraint instance to copy.
        # \return \a self
        # 
        def assign(constr: DistanceConstraint) -> DistanceConstraint: pass

        def getPoint1Index() -> int: pass

        def getPoint2Index() -> int: pass

        def getLowerBound() -> float: pass

        def getUpperBound() -> float: pass

        objectID = property(getObjectID)

        point1Index = property(getPoint1Index)

        point2Index = property(getPoint2Index)

        lowerBound = property(getLowerBound)

        upperBound = property(getUpperBound)

    ##
    # \brief 
    #
    COORDS_DIM = 2

    ##
    # \brief 
    #
    DEF_NUM_CYCLES = 50

    ##
    # \brief 
    #
    DEF_CYCLE_STEP_COUNT_FACTOR = 1.0

    ##
    # \brief 
    #
    DEF_START_LEARNING_RATE = 1.0

    ##
    # \brief 
    #
    DEF_LEARNING_RATE_DECREMENT = 0.019

    ##
    # \brief Initializes the \c %DG2DCoordinatesGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %DG2DCoordinatesGenerator instance \a gen.
    # \param gen The \c %DG2DCoordinatesGenerator instance to copy.
    # 
    def __init__(gen: DG2DCoordinatesGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DG2DCoordinatesGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DG2DCoordinatesGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DG2DCoordinatesGenerator instance \a gen.
    # \param gen The \c %DG2DCoordinatesGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: DG2DCoordinatesGenerator) -> DG2DCoordinatesGenerator: pass

    def clearDistanceConstraints() -> None: pass

    def getNumDistanceConstraints() -> int: pass

    def getDistanceConstraint(idx: int) -> DistanceConstraint: pass

    def addDistanceConstraint(pt1_idx: int, pt2_idx: int, lb: float, ub: float) -> None: pass

    def removeDistanceConstraint(idx: int) -> None: pass

    def setNumCycles(num_cycles: int) -> None: pass

    def getNumCycles() -> int: pass

    def setCycleStepCountFactor(fact: float) -> None: pass

    def getCycleStepCountFactor() -> float: pass

    def setStartLearningRate(rate: float) -> None: pass

    def getStartLearningRate() -> float: pass

    def setLearningRateDecrement(decr: float) -> None: pass

    def getLearningRateDecrement() -> float: pass

    def setRandomSeed(seed: int) -> None: pass

    def generate(num_points: int, coords: Math.Vector2DArray) -> None: pass

    def getDistanceError(coords: Math.Vector2DArray) -> float: pass

    def getDistanceConstraints() -> DistanceConstraintList: pass

    objectID = property(getObjectID)

    numCycles = property(getNumCycles, setNumCycles)

    cycleStepCountFactor = property(getCycleStepCountFactor, setCycleStepCountFactor)

    startLearningRate = property(getStartLearningRate, setStartLearningRate)

    learningRateDecrement = property(getLearningRateDecrement, setLearningRateDecrement)

    numDistanceConstraints = property(getNumDistanceConstraints)

    distanceConstraints = property(getDistanceConstraints)
