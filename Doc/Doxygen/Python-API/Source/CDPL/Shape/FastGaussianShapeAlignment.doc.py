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
class FastGaussianShapeAlignment(Boost.Python.instance):

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
    DEF_RESULT_SELECTION_MODE = 3

    ##
    # \brief 
    #
    DEF_SYMMETRY_THRESHOLD = 0.15

    ##
    # \brief 
    #
    DEF_NUM_RANDOM_STARTS = 4

    ##
    # \brief 
    #
    DEF_MAX_RANDOM_TRANSLATION = 2.0

    ##
    # \brief Initializes the \e %FastGaussianShapeAlignment instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FastGaussianShapeAlignment instance.
    # \param ref_shape 
    # 
    def __init__(ref_shape: GaussianShape) -> None: pass

    ##
    # \brief Initializes the \e %FastGaussianShapeAlignment instance.
    # \param ref_shapes 
    # 
    def __init__(ref_shapes: GaussianShapeSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FastGaussianShapeAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FastGaussianShapeAlignment instances \e a and \e b reference different C++ objects. 
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
    # \param thresh 
    #
    def setSymmetryThreshold(thresh: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSymmetryThreshold() -> float: pass

    ##
    # \brief 
    # \param generate 
    #
    def genShapeCenterStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genShapeCenterStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genColorCenterStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genNonColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genNonColorCenterStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genRandomStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genRandomStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genForAlignedShapeCenters(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genForAlignedShapeCenters() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genForReferenceShapeCenters(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genForReferenceShapeCenters() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genForLargerShapeCenters(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genForLargerShapeCenters() -> bool: pass

    ##
    # \brief 
    # \param max_trans 
    #
    def setMaxRandomTranslation(max_trans: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxRandomTranslation() -> float: pass

    ##
    # \brief 
    # \param num_starts 
    #
    def setNumRandomStarts(num_starts: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumRandomStarts() -> int: pass

    ##
    # \brief 
    # \param seed 
    #
    def setRandomSeed(seed: int) -> None: pass

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

    resultCompareFunction = property(getResultCompareFunction, setResultCompareFunction)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    resultSelectionMode = property(getResultSelectionMode, setResultSelectionMode)

    maxNumOptIterations = property(getMaxNumOptimizationIterations, setMaxNumOptimizationIterations)

    optStopGradient = property(getOptimizationStopGradient, setOptimizationStopGradient)

    perfAlignment = property(performAlignment, performAlignment)

    optOverlap = property(optimizeOverlap, optimizeOverlap)

    greedyOpt = property(greedyOptimization, greedyOptimization)

    numReferenceShapes = property(getNumReferenceShapes)

    symmetryThreshold = property(getSymmetryThreshold, setSymmetryThreshold)

    maxRandomTranslation = property(getMaxRandomTranslation, setMaxRandomTranslation)

    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    shapeCenterStarts = property(genShapeCenterStarts, genShapeCenterStarts)

    colorCenterStarts = property(genColorCenterStarts, genColorCenterStarts)

    nonColorCenterStarts = property(genNonColorCenterStarts, genNonColorCenterStarts)

    randomStarts = property(getNumRandomStarts, setNumRandomStarts)

    genForAlignedShapeCtrs = property(genForAlignedShapeCenters, genForAlignedShapeCenters)

    genForReferenceShapeCrs = property(genForReferenceShapeCenters, genForReferenceShapeCenters)

    genForLargerShapeCtrs = property(genForLargerShapeCenters, genForLargerShapeCenters)
