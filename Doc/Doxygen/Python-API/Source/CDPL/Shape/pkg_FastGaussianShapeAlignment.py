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
    # \param self The \e %FastGaussianShapeAlignment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FastGaussianShapeAlignment instance.
    # \param self The \e %FastGaussianShapeAlignment instance to initialize.
    # \param ref_shape 
    #
    def __init__(self: object, ref_shape: GaussianShape) -> None: pass

    ##
    # \brief Initializes the \e %FastGaussianShapeAlignment instance.
    # \param self The \e %FastGaussianShapeAlignment instance to initialize.
    # \param ref_shapes 
    #
    def __init__(self: object, ref_shapes: GaussianShapeSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    #
    # Different Python \e %FastGaussianShapeAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FastGaussianShapeAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setResultCompareFunction(self: FastGaussianShapeAlignment, func: BoolAlignmentResult2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getResultCompareFunction(self: FastGaussianShapeAlignment) -> BoolAlignmentResult2Functor: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param func 
    #
    def setScoringFunction(self: FastGaussianShapeAlignment, func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getScoringFunction(self: FastGaussianShapeAlignment) -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param mode 
    #
    def setResultSelectionMode(self: FastGaussianShapeAlignment, mode: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getResultSelectionMode(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param max_iter 
    #
    def setMaxNumOptimizationIterations(self: FastGaussianShapeAlignment, max_iter: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getMaxNumOptimizationIterations(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param grad_norm 
    #
    def setOptimizationStopGradient(self: FastGaussianShapeAlignment, grad_norm: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getOptimizationStopGradient(self: FastGaussianShapeAlignment) -> float: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param perf_align 
    #
    def performAlignment(self: FastGaussianShapeAlignment, perf_align: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def performAlignment(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param optimize 
    #
    def optimizeOverlap(self: FastGaussianShapeAlignment, optimize: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def optimizeOverlap(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param greedy 
    #
    def greedyOptimization(self: FastGaussianShapeAlignment, greedy: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def greedyOptimization(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param thresh 
    #
    def setSymmetryThreshold(self: FastGaussianShapeAlignment, thresh: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getSymmetryThreshold(self: FastGaussianShapeAlignment) -> float: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genShapeCenterStarts(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genShapeCenterStarts(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genColorCenterStarts(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genColorCenterStarts(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genNonColorCenterStarts(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genNonColorCenterStarts(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genRandomStarts(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genRandomStarts(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genForAlignedShapeCenters(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genForAlignedShapeCenters(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genForReferenceShapeCenters(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genForReferenceShapeCenters(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param generate 
    #
    def genForLargerShapeCenters(self: FastGaussianShapeAlignment, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def genForLargerShapeCenters(self: FastGaussianShapeAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param max_trans 
    #
    def setMaxRandomTranslation(self: FastGaussianShapeAlignment, max_trans: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getMaxRandomTranslation(self: FastGaussianShapeAlignment) -> float: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param num_starts 
    #
    def setNumRandomStarts(self: FastGaussianShapeAlignment, num_starts: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getNumRandomStarts(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param seed 
    #
    def setRandomSeed(self: FastGaussianShapeAlignment, seed: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    #
    def clearReferenceShapes(self: FastGaussianShapeAlignment) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param shape 
    # \param new_set 
    #
    def addReferenceShape(self: FastGaussianShapeAlignment, shape: GaussianShape, new_set: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param shapes 
    # \param new_set 
    #
    def addReferenceShapes(self: FastGaussianShapeAlignment, shapes: GaussianShapeSet, new_set: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getNumReferenceShapes(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param shape 
    # \return 
    #
    def align(self: FastGaussianShapeAlignment, shape: GaussianShape) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param shapes 
    # \return 
    #
    def align(self: FastGaussianShapeAlignment, shapes: GaussianShapeSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def getNumResults(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getResult(self: FastGaussianShapeAlignment, idx: int) -> AlignmentResult: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \return 
    #
    def __len__(self: FastGaussianShapeAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %FastGaussianShapeAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: FastGaussianShapeAlignment, idx: int) -> AlignmentResult: pass

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
    # \brief 
    #
    numReferenceShapes = property(getNumReferenceShapes)

    ##
    # \brief 
    #
    symmetryThreshold = property(getSymmetryThreshold, setSymmetryThreshold)

    ##
    # \brief 
    #
    maxRandomTranslation = property(getMaxRandomTranslation, setMaxRandomTranslation)

    ##
    # \brief 
    #
    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    ##
    # \brief FIXME!
    #
    shapeCenterStarts = property(getShapeCenterStarts, setShapeCenterStarts)

    ##
    # \brief FIXME!
    #
    colorCenterStarts = property(getColorCenterStarts, setColorCenterStarts)

    ##
    # \brief FIXME!
    #
    nonColorCenterStarts = property(getNonColorCenterStarts, setNonColorCenterStarts)

    ##
    # \brief FIXME!
    #
    randomStarts = property(getRandomStarts, setRandomStarts)

    ##
    # \brief FIXME!
    #
    genForAlignedShapeCtrs = property(getGenForAlignedShapeCtrs, setGenForAlignedShapeCtrs)

    ##
    # \brief FIXME!
    #
    genForReferenceShapeCrs = property(getGenForReferenceShapeCrs, setGenForReferenceShapeCrs)

    ##
    # \brief FIXME!
    #
    genForLargerShapeCtrs = property(getGenForLargerShapeCtrs, setGenForLargerShapeCtrs)
