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
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeAlignment instance.
    # \param ref_shape 
    # 
    def __init__(ref_shape: GaussianShape) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeAlignment instance.
    # \param ref_shapes 
    # 
    def __init__(ref_shapes: GaussianShapeSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setOverlapFunction(func: GaussianShapeOverlapFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getOverlapFunction() -> GaussianShapeOverlapFunction: pass

    ##
    # \brief 
    # \return 
    #
    def getDefaultOverlapFunction() -> FastGaussianShapeOverlapFunction: pass

    ##
    # \brief 
    # \param gen 
    #
    def setStartGenerator(gen: GaussianShapeAlignmentStartGenerator) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStartGenerator() -> GaussianShapeAlignmentStartGenerator: pass

    ##
    # \brief 
    # \return 
    #
    def getDefaultStartGenerator() -> PrincipalAxesAlignmentStartGenerator: pass

    ##
    # \brief 
    # \param func 
    #
    def setColorMatchFunction(func: Pharm.BoolSizeType2Functor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getColorMatchFunction() -> Pharm.BoolSizeType2Functor: pass

    ##
    # \brief 
    # \param func 
    #
    def setColorFilterFunction(func: BoolSizeTypeFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getColorFilterFunction() -> BoolSizeTypeFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setResultCompareFunction(func: BoolAlignmentResult2Functor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getResultCompareFunction() -> BoolAlignmentResult2Functor: pass

    ##
    # \brief 
    # \param func 
    #
    def setScoringFunction(func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoringFunction() -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief 
    # \param mode 
    #
    def setResultSelectionMode(mode: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getResultSelectionMode() -> int: pass

    ##
    # \brief 
    # \param max_iter 
    #
    def setMaxNumOptimizationIterations(max_iter: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumOptimizationIterations() -> int: pass

    ##
    # \brief 
    # \param grad_norm 
    #
    def setOptimizationStopGradient(grad_norm: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getOptimizationStopGradient() -> float: pass

    ##
    # \brief 
    # \param perf_align 
    #
    def performAlignment(perf_align: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def performAlignment() -> bool: pass

    ##
    # \brief 
    # \param optimize 
    #
    def optimizeOverlap(optimize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def optimizeOverlap() -> bool: pass

    ##
    # \brief 
    # \param greedy 
    #
    def greedyOptimization(greedy: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def greedyOptimization() -> bool: pass

    ##
    # \brief 
    # \param calc 
    #
    def calcColorOverlaps(calc: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def calcColorOverlaps() -> bool: pass

    ##
    # \brief 
    # \param calc 
    #
    def calcSelfOverlaps(calc: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def calcSelfOverlaps() -> bool: pass

    ##
    # \brief 
    # \param calc 
    #
    def calcColorSelfOverlaps(calc: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def calcColorSelfOverlaps() -> bool: pass

    ##
    # \brief 
    # \param max_order 
    #
    def setMaxOrder(max_order: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxOrder() -> int: pass

    ##
    # \brief 
    # \param cutoff 
    #
    def setDistanceCutoff(cutoff: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDistanceCutoff() -> float: pass

    ##
    # \brief 
    #
    def clearReferenceShapes() -> None: pass

    ##
    # \brief 
    # \param shape 
    # \param new_set 
    #
    def addReferenceShape(shape: GaussianShape, new_set: bool = True) -> None: pass

    ##
    # \brief 
    # \param shapes 
    # \param new_set 
    #
    def addReferenceShapes(shapes: GaussianShapeSet, new_set: bool = True) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumReferenceShapes() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getReferenceShape(idx: int) -> GaussianShape: pass

    ##
    # \brief 
    # \param shape 
    # \return 
    #
    def align(shape: GaussianShape) -> bool: pass

    ##
    # \brief 
    # \param shapes 
    # \return 
    #
    def align(shapes: GaussianShapeSet) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getNumResults() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getResult(idx: int) -> AlignmentResult: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> AlignmentResult: pass

    objectID = property(getObjectID)

    numResults = property(getNumResults)

    overlapFunction = property(getOverlapFunction, setOverlapFunction)

    defaultOverlapFunction = property(getDefaultOverlapFunction)

    startGenerator = property(getStartGenerator, setStartGenerator)

    defaultStartGenerator = property(getDefaultStartGenerator)

    colorMatchFunction = property(getColorMatchFunction, setColorMatchFunction)

    colorFilterFunction = property(getColorFilterFunction, setColorFilterFunction)

    resultCompareFunction = property(getResultCompareFunction, setResultCompareFunction)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    resultSelectionMode = property(getResultSelectionMode, setResultSelectionMode)

    maxNumOptIterations = property(getMaxNumOptimizationIterations, setMaxNumOptimizationIterations)

    optStopGradient = property(getOptimizationStopGradient, setOptimizationStopGradient)

    perfAlignment = property(performAlignment, performAlignment)

    optOverlap = property(optimizeOverlap, optimizeOverlap)

    greedyOpt = property(greedyOptimization, greedyOptimization)

    selfOverlaps = property(calcSelfOverlaps, calcSelfOverlaps)

    colorSelfOverlaps = property(calcColorSelfOverlaps, calcColorSelfOverlaps)

    colorOverlaps = property(calcColorOverlaps, calcColorOverlaps)

    maxOrder = property(getMaxOrder, setMaxOrder)

    distCutoff = property(getDistanceCutoff, setDistanceCutoff)

    numReferenceShapes = property(getNumReferenceShapes)
