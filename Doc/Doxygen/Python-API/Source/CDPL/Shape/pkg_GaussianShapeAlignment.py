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
class GaussianShapeAlignment(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_OPTIMIZATION_STOP_GRADIENT = 1.0

    ##
    # \brief 
    #
    DEF_MAX_OPTIMIZATION_ITERATIONS = 20

    ##
    # \brief 
    #
    DEF_MAX_PRODUCT_ORDER = 1

    ##
    # \brief 
    #
    DEF_DISTANCE_CUTOFF = 0.0

    ##
    # \brief 
    #
    DEF_RESULT_SELECTION_MODE = 3

    ##
    # \brief Initializes the \e %GaussianShapeAlignment instance.
    # \param self The \e %GaussianShapeAlignment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeAlignment instance.
    # \param self The \e %GaussianShapeAlignment instance to initialize.
    # \param ref_shape 
    #
    def __init__(self: object, ref_shape: GaussianShape) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeAlignment instance.
    # \param self The \e %GaussianShapeAlignment instance to initialize.
    # \param ref_shapes 
    #
    def __init__(self: object, ref_shapes: GaussianShapeSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    #
    # Different Python \e %GaussianShapeAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setOverlapFunction(self: GaussianShapeAlignment, func: GaussianShapeOverlapFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getOverlapFunction(self: GaussianShapeAlignment) -> GaussianShapeOverlapFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getDefaultOverlapFunction(self: GaussianShapeAlignment) -> FastGaussianShapeOverlapFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param gen 
    #
    def setStartGenerator(self: GaussianShapeAlignment, gen: GaussianShapeAlignmentStartGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getStartGenerator(self: GaussianShapeAlignment) -> GaussianShapeAlignmentStartGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getDefaultStartGenerator(self: GaussianShapeAlignment) -> PrincipalAxesAlignmentStartGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setColorMatchFunction(self: GaussianShapeAlignment, func: CDPL.Pharm.BoolSizeType2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getColorMatchFunction(self: GaussianShapeAlignment) -> CDPL.Pharm.BoolSizeType2Functor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setColorFilterFunction(self: GaussianShapeAlignment, func: BoolSizeTypeFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getColorFilterFunction(self: GaussianShapeAlignment) -> BoolSizeTypeFunctor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setResultCompareFunction(self: GaussianShapeAlignment, func: BoolAlignmentResult2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getResultCompareFunction(self: GaussianShapeAlignment) -> BoolAlignmentResult2Functor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setScoringFunction(self: GaussianShapeAlignment, func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getScoringFunction(self: GaussianShapeAlignment) -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param mode 
    #
    def setResultSelectionMode(self: GaussianShapeAlignment, mode: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getResultSelectionMode(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param max_iter 
    #
    def setMaxNumOptimizationIterations(self: GaussianShapeAlignment, max_iter: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getMaxNumOptimizationIterations(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param grad_norm 
    #
    def setOptimizationStopGradient(self: GaussianShapeAlignment, grad_norm: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getOptimizationStopGradient(self: GaussianShapeAlignment) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param perf_align 
    #
    def performAlignment(self: GaussianShapeAlignment, perf_align: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def performAlignment(self: GaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param optimize 
    #
    def optimizeOverlap(self: GaussianShapeAlignment, optimize: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def optimizeOverlap(self: GaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param greedy 
    #
    def greedyOptimization(self: GaussianShapeAlignment, greedy: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def greedyOptimization(self: GaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param calc 
    #
    def calcColorOverlaps(self: GaussianShapeAlignment, calc: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def calcColorOverlaps(self: GaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param calc 
    #
    def calcSelfOverlaps(self: GaussianShapeAlignment, calc: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def calcSelfOverlaps(self: GaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param calc 
    #
    def calcColorSelfOverlaps(self: GaussianShapeAlignment, calc: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def calcColorSelfOverlaps(self: GaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param max_order 
    #
    def setMaxOrder(self: GaussianShapeAlignment, max_order: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getMaxOrder(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param cutoff 
    #
    def setDistanceCutoff(self: GaussianShapeAlignment, cutoff: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getDistanceCutoff(self: GaussianShapeAlignment) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    #
    def clearReferenceShapes(self: GaussianShapeAlignment) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param shape 
    # \param new_set 
    #
    def addReferenceShape(self: GaussianShapeAlignment, shape: GaussianShape, new_set: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param shapes 
    # \param new_set 
    #
    def addReferenceShapes(self: GaussianShapeAlignment, shapes: GaussianShapeSet, new_set: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getNumReferenceShapes(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getReferenceShape(self: GaussianShapeAlignment, idx: int) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param shape 
    # \return 
    #
    def align(self: GaussianShapeAlignment, shape: GaussianShape) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param shapes 
    # \return 
    #
    def align(self: GaussianShapeAlignment, shapes: GaussianShapeSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getNumResults(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getResult(self: GaussianShapeAlignment, idx: int) -> AlignmentResult: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def __len__(self: GaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: GaussianShapeAlignment, idx: int) -> AlignmentResult: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numResults = property(getNumResults)

    ##
    # \brief 
    #
    overlapFunction = property(getOverlapFunction, setOverlapFunction)

    ##
    # \brief 
    #
    defaultOverlapFunction = property(getDefaultOverlapFunction)

    ##
    # \brief 
    #
    startGenerator = property(getStartGenerator, setStartGenerator)

    ##
    # \brief 
    #
    defaultStartGenerator = property(getDefaultStartGenerator)

    ##
    # \brief 
    #
    colorMatchFunction = property(getColorMatchFunction, setColorMatchFunction)

    ##
    # \brief 
    #
    colorFilterFunction = property(getColorFilterFunction, setColorFilterFunction)

    ##
    # \brief 
    #
    resultCompareFunction = property(getResultCompareFunction, setResultCompareFunction)

    ##
    # \brief 
    #
    scoringFunction = property(getScoringFunction, setScoringFunction)

    ##
    # \brief 
    #
    resultSelectionMode = property(getResultSelectionMode, setResultSelectionMode)

    ##
    # \brief FIXME!
    #
    maxNumOptIterations = property(getMaxNumOptIterations, setMaxNumOptIterations)

    ##
    # \brief FIXME!
    #
    optStopGradient = property(getOptStopGradient, setOptStopGradient)

    ##
    # \brief FIXME!
    #
    perfAlignment = property(getPerfAlignment, setPerfAlignment)

    ##
    # \brief FIXME!
    #
    optOverlap = property(getOptOverlap, setOptOverlap)

    ##
    # \brief FIXME!
    #
    greedyOpt = property(getGreedyOpt, setGreedyOpt)

    ##
    # \brief FIXME!
    #
    selfOverlaps = property(getSelfOverlaps, setSelfOverlaps)

    ##
    # \brief FIXME!
    #
    colorSelfOverlaps = property(getColorSelfOverlaps, setColorSelfOverlaps)

    ##
    # \brief FIXME!
    #
    colorOverlaps = property(getColorOverlaps, setColorOverlaps)

    ##
    # \brief 
    #
    maxOrder = property(getMaxOrder, setMaxOrder)

    ##
    # \brief FIXME!
    #
    distCutoff = property(getDistCutoff, setDistCutoff)

    ##
    # \brief 
    #
    numReferenceShapes = property(getNumReferenceShapes)
