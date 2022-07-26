#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
class DG3DCoordinatesGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class VolumeConstraintList(Boost.Python.instance):

        ##
        # \brief 
        # \param self The \e %VolumeConstraintList instance this method is called upon.
        # \return 
        #
        def __len__(self: VolumeConstraintList) -> int: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraintList instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: VolumeConstraintList, idx: int) -> VolumeConstraint: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraintList instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: VolumeConstraintList, idx: int) -> None: pass

    ##
    # \brief 
    #
    class VolumeConstraint(Boost.Python.instance):

        ##
        # \brief Initializes the \e %VolumeConstraint instance.
        # \param self The \e %VolumeConstraint instance to initialize.
        # \param pt1_idx 
        # \param pt2_idx 
        # \param pt3_idx 
        # \param pt4_idx 
        # \param lb 
        # \param ub 
        #
        def __init__(self: object, pt1_idx: int, pt2_idx: int, pt3_idx: int, pt4_idx: int, lb: float, ub: float) -> None: pass

        ##
        # \brief Initializes the \e %VolumeConstraint instance.
        # \param self The \e %VolumeConstraint instance to initialize.
        # \param constr 
        #
        def __init__(self: object, constr: VolumeConstraint) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %VolumeConstraint instance this method is called upon.
        #
        # Different Python \e %VolumeConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %VolumeConstraint instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: VolumeConstraint) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %VolumeConstraint instance \a constr.
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \param constr The \e %VolumeConstraint instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: VolumeConstraint, constr: VolumeConstraint) -> VolumeConstraint: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \return 
        #
        def getPoint1Index(self: VolumeConstraint) -> int: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \return 
        #
        def getPoint2Index(self: VolumeConstraint) -> int: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \return 
        #
        def getPoint3Index(self: VolumeConstraint) -> int: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \return 
        #
        def getPoint4Index(self: VolumeConstraint) -> int: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \return 
        #
        def getLowerBound(self: VolumeConstraint) -> float: pass

        ##
        # \brief 
        # \param self The \e %VolumeConstraint instance this method is called upon.
        # \return 
        #
        def getUpperBound(self: VolumeConstraint) -> float: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        point1Index = property(getPoint1Index)

        ##
        # \brief 
        #
        point2Index = property(getPoint2Index)

        ##
        # \brief 
        #
        point3Index = property(getPoint3Index)

        ##
        # \brief 
        #
        point4Index = property(getPoint4Index)

        ##
        # \brief 
        #
        lowerBound = property(getLowerBound)

        ##
        # \brief 
        #
        upperBound = property(getUpperBound)

    ##
    # \brief 
    #
    class DistanceConstraintList(Boost.Python.instance):

        ##
        # \brief 
        # \param self The \e %DistanceConstraintList instance this method is called upon.
        # \return 
        #
        def __len__(self: DistanceConstraintList) -> int: pass

        ##
        # \brief 
        # \param self The \e %DistanceConstraintList instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: DistanceConstraintList, idx: int) -> DistanceConstraint: pass

        ##
        # \brief 
        # \param self The \e %DistanceConstraintList instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: DistanceConstraintList, idx: int) -> None: pass

    ##
    # \brief 
    #
    class DistanceConstraint(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DistanceConstraint instance.
        # \param self The \e %DistanceConstraint instance to initialize.
        # \param pt1_idx 
        # \param pt2_idx 
        # \param lb 
        # \param ub 
        #
        def __init__(self: object, pt1_idx: int, pt2_idx: int, lb: float, ub: float) -> None: pass

        ##
        # \brief Initializes the \e %DistanceConstraint instance.
        # \param self The \e %DistanceConstraint instance to initialize.
        # \param constr 
        #
        def __init__(self: object, constr: DistanceConstraint) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %DistanceConstraint instance this method is called upon.
        #
        # Different Python \e %DistanceConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DistanceConstraint instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: DistanceConstraint) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %DistanceConstraint instance \a constr.
        # \param self The \e %DistanceConstraint instance this method is called upon.
        # \param constr The \e %DistanceConstraint instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: DistanceConstraint, constr: DistanceConstraint) -> DistanceConstraint: pass

        ##
        # \brief 
        # \param self The \e %DistanceConstraint instance this method is called upon.
        # \return 
        #
        def getPoint1Index(self: DistanceConstraint) -> int: pass

        ##
        # \brief 
        # \param self The \e %DistanceConstraint instance this method is called upon.
        # \return 
        #
        def getPoint2Index(self: DistanceConstraint) -> int: pass

        ##
        # \brief 
        # \param self The \e %DistanceConstraint instance this method is called upon.
        # \return 
        #
        def getLowerBound(self: DistanceConstraint) -> float: pass

        ##
        # \brief 
        # \param self The \e %DistanceConstraint instance this method is called upon.
        # \return 
        #
        def getUpperBound(self: DistanceConstraint) -> float: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        point1Index = property(getPoint1Index)

        ##
        # \brief 
        #
        point2Index = property(getPoint2Index)

        ##
        # \brief 
        #
        lowerBound = property(getLowerBound)

        ##
        # \brief 
        #
        upperBound = property(getUpperBound)

    ##
    # \brief 
    #
    COORDS_DIM = 3

    ##
    # \brief 
    #
    DEF_NUM_CYCLES = 50

    ##
    # \brief 
    #
    DEF_CYCLE_STEP_COUNT_FACTOR = 1

    ##
    # \brief 
    #
    DEF_START_LEARNING_RATE = 1.0

    ##
    # \brief 
    #
    DEF_LEARNING_RATE_DECREMENT = 0.019

    ##
    # \brief Initializes the \e %DG3DCoordinatesGenerator instance.
    # \param self The \e %DG3DCoordinatesGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DG3DCoordinatesGenerator instance.
    # \param self The \e %DG3DCoordinatesGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    #
    # Different Python \e %DG3DCoordinatesGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DG3DCoordinatesGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DG3DCoordinatesGenerator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DG3DCoordinatesGenerator instance \a gen.
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param gen The \e %DG3DCoordinatesGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DG3DCoordinatesGenerator, gen: DG3DCoordinatesGenerator) -> DG3DCoordinatesGenerator: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    #
    def clearDistanceConstraints(self: DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getNumDistanceConstraints(self: DG3DCoordinatesGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getDistanceConstraint(self: DG3DCoordinatesGenerator, idx: int) -> DistanceConstraint: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param pt1_idx 
    # \param pt2_idx 
    # \param lb 
    # \param ub 
    #
    def addDistanceConstraint(self: DG3DCoordinatesGenerator, pt1_idx: int, pt2_idx: int, lb: float, ub: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param idx 
    #
    def removeDistanceConstraint(self: DG3DCoordinatesGenerator, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param num_cycles 
    #
    def setNumCycles(self: DG3DCoordinatesGenerator, num_cycles: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getNumCycles(self: DG3DCoordinatesGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param fact 
    #
    def setCycleStepCountFactor(self: DG3DCoordinatesGenerator, fact: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getCycleStepCountFactor(self: DG3DCoordinatesGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param rate 
    #
    def setStartLearningRate(self: DG3DCoordinatesGenerator, rate: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getStartLearningRate(self: DG3DCoordinatesGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param decr 
    #
    def setLearningRateDecrement(self: DG3DCoordinatesGenerator, decr: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getLearningRateDecrement(self: DG3DCoordinatesGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param seed 
    #
    def setRandomSeed(self: DG3DCoordinatesGenerator, seed: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param num_points 
    # \param coords 
    #
    def generate(self: DG3DCoordinatesGenerator, num_points: int, coords: CDPL.Math.Vector3DArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param coords 
    # \return 
    #
    def getDistanceError(self: DG3DCoordinatesGenerator, coords: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    #
    def clearVolumeConstraints(self: DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getNumVolumeConstraints(self: DG3DCoordinatesGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getVolumeConstraint(self: DG3DCoordinatesGenerator, idx: int) -> VolumeConstraint: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param pt1_idx 
    # \param pt2_idx 
    # \param pt3_idx 
    # \param pt4_idx 
    # \param lb 
    # \param ub 
    #
    def addVolumeConstraint(self: DG3DCoordinatesGenerator, pt1_idx: int, pt2_idx: int, pt3_idx: int, pt4_idx: int, lb: float, ub: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param idx 
    #
    def removeVolumeConstraint(self: DG3DCoordinatesGenerator, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DG3DCoordinatesGenerator instance this method is called upon.
    # \param coords 
    # \return 
    #
    def getVolumeError(self: DG3DCoordinatesGenerator, coords: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numCycles = property(getNumCycles, setNumCycles)

    ##
    # \brief 
    #
    cycleStepCountFactor = property(getCycleStepCountFactor, setCycleStepCountFactor)

    ##
    # \brief 
    #
    startLearningRate = property(getStartLearningRate, setStartLearningRate)

    ##
    # \brief 
    #
    learningRateDecrement = property(getLearningRateDecrement, setLearningRateDecrement)

    ##
    # \brief 
    #
    numDistanceConstraints = property(getNumDistanceConstraints)

    ##
    # \brief FIXME!
    #
    distanceConstraints = property(getDistanceConstraints)

    ##
    # \brief 
    #
    numVolumeConstraints = property(getNumVolumeConstraints)

    ##
    # \brief FIXME!
    #
    volumeConstraints = property(getVolumeConstraints)
