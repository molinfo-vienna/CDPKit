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
# \brief High-level driver for the fast alignment of Gaussian shapes against a set of reference shapes.
# 
# Unlike Shape.GaussianShapeAlignment, which delegates the alignment to a separate Shape.GaussianShapeFunctionAlignment instance, <tt>FastGaussianShapeAlignment</tt> integrates the entire pipeline (start-transform generation, BFGS overlap optimization, result selection) into one class and operates on a self-contained Gaussian-product representation. The configuration combines settings exposed by Shape.PrincipalAxesAlignmentStartGenerator (start-transform options) and the iterative overlap optimization.
# 
class FastGaussianShapeAlignment(Boost.Python.instance):

    ##
    # \brief Default gradient norm at which the overlap optimization is stopped.
    # 
    DEF_OPTIMIZATION_STOP_GRADIENT = 1.0

    ##
    # \brief Default maximum number of overlap-optimization iterations.
    # 
    DEF_MAX_OPTIMIZATION_ITERATIONS = 20

    ##
    # \brief Default alignment-result selection mode.
    # 
    DEF_RESULT_SELECTION_MODE = 3

    ##
    # \brief Default relative threshold for treating two principal moments as equal.
    # 
    DEF_SYMMETRY_THRESHOLD = 0.15

    ##
    # \brief Default number of random starting transformations.
    # 
    DEF_NUM_RANDOM_STARTS = 4

    ##
    # \brief Default maximum random translation magnitude applied to random starts.
    # 
    DEF_MAX_RANDOM_TRANSLATION = 2.0

    ##
    # \brief Constructs the <tt>FastGaussianShapeAlignment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>FastGaussianShapeAlignment</tt> instance with <em>ref_shape</em> as the single reference shape.
    # 
    def __init__(ref_shape: GaussianShape) -> None: pass

    ##
    # \brief Constructs the <tt>FastGaussianShapeAlignment</tt> instance with the shapes in <em>ref_shapes</em> as the reference set.
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
    # \brief Specifies the function used to compare two alignment results for sorting and filtering.
    # 
    def setResultCompareFunction(func: BoolAlignmentResult2Functor) -> None: pass

    ##
    # \brief Returns the currently configured result-compare function.
    # 
    def getResultCompareFunction() -> BoolAlignmentResult2Functor: pass

    ##
    # \brief Specifies the function used to score an alignment result.
    # 
    def setScoringFunction(func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief Returns the currently configured scoring function.
    # 
    def getScoringFunction() -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief Sets the alignment-result selection mode (see namespace Shape.AlignmentResultSelectionMode).
    # 
    def setResultSelectionMode(mode: int) -> None: pass

    ##
    # \brief Returns the currently configured alignment-result selection mode.
    # 
    def getResultSelectionMode() -> int: pass

    ##
    # \brief Sets the maximum number of overlap-optimization iterations.
    # 
    def setMaxNumOptimizationIterations(max_iter: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum number of overlap-optimization iterations.
    # 
    def getMaxNumOptimizationIterations() -> int: pass

    ##
    # \brief Sets the gradient norm at which the overlap optimization is stopped.
    # 
    def setOptimizationStopGradient(grad_norm: float) -> None: pass

    ##
    # \brief Returns the currently configured overlap-optimization stop gradient.
    # 
    def getOptimizationStopGradient() -> float: pass

    ##
    # \brief Specifies whether the actual alignment shall be performed (vs. only evaluating overlaps in the initial pose).
    # 
    def performAlignment(perf_align: bool) -> None: pass

    ##
    # \brief Tells whether the actual alignment is performed.
    # 
    def performAlignment() -> bool: pass

    ##
    # \brief Specifies whether the overlap shall be optimized iteratively after the initial alignment.
    # 
    def optimizeOverlap(optimize: bool) -> None: pass

    ##
    # \brief Tells whether the overlap is optimized iteratively.
    # 
    def optimizeOverlap() -> bool: pass

    ##
    # \brief Specifies whether the overlap optimization shall use a greedy strategy that stops at the first local maximum.
    # 
    def greedyOptimization(greedy: bool) -> None: pass

    ##
    # \brief Tells whether the overlap optimization uses a greedy strategy.
    # 
    def greedyOptimization() -> bool: pass

    ##
    # \brief Sets the relative threshold for treating two principal moments as equal.
    # 
    def setSymmetryThreshold(thresh: float) -> None: pass

    ##
    # \brief Returns the currently configured symmetry threshold.
    # 
    def getSymmetryThreshold() -> float: pass

    ##
    # \brief Enables or disables the generation of a starting transformation at the shape centroid.
    # 
    def genShapeCenterStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether a starting transformation at the shape centroid is generated.
    # 
    def genShapeCenterStarts() -> bool: pass

    ##
    # \brief Enables or disables the generation of starting transformations at color (pharmacophore) feature centers.
    # 
    def genColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether starting transformations at color (pharmacophore) feature centers are generated.
    # 
    def genColorCenterStarts() -> bool: pass

    ##
    # \brief Enables or disables the generation of starting transformations at non-color (shape) element centers.
    # 
    def genNonColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether starting transformations at non-color (shape) element centers are generated.
    # 
    def genNonColorCenterStarts() -> bool: pass

    ##
    # \brief Enables or disables the generation of random starting transformations.
    # 
    def genRandomStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether random starting transformations are generated.
    # 
    def genRandomStarts() -> bool: pass

    ##
    # \brief Specifies whether element-/color-center starts shall be generated for centers of the aligned shape.
    # 
    def genForAlignedShapeCenters(generate: bool) -> None: pass

    ##
    # \brief Tells whether element-/color-center starts are generated for centers of the aligned shape.
    # 
    def genForAlignedShapeCenters() -> bool: pass

    ##
    # \brief Specifies whether element-/color-center starts shall be generated for centers of the reference shape.
    # 
    def genForReferenceShapeCenters(generate: bool) -> None: pass

    ##
    # \brief Tells whether element-/color-center starts are generated for centers of the reference shape.
    # 
    def genForReferenceShapeCenters() -> bool: pass

    ##
    # \brief Specifies whether element-/color-center starts shall be generated for centers of the shape with more elements (instead of both shapes).
    # 
    def genForLargerShapeCenters(generate: bool) -> None: pass

    ##
    # \brief Tells whether element-/color-center starts are generated for centers of the shape with more elements (instead of both shapes).
    # 
    def genForLargerShapeCenters() -> bool: pass

    ##
    # \brief Sets the maximum random translation magnitude applied to random starts.
    # 
    def setMaxRandomTranslation(max_trans: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum random translation.
    # 
    def getMaxRandomTranslation() -> float: pass

    ##
    # \brief Sets the number of random starting transformations.
    # 
    def setNumRandomStarts(num_starts: int) -> None: pass

    ##
    # \brief Returns the currently configured number of random starts.
    # 
    def getNumRandomStarts() -> int: pass

    ##
    # \brief Sets the seed used by the random number generator that produces the random starts.
    # 
    def setRandomSeed(seed: int) -> None: pass

    ##
    # \brief Removes all reference shapes and reference shape sets.
    # 
    def clearReferenceShapes() -> None: pass

    ##
    # \brief Adds <em>shape</em> to the reference shapes.
    # 
    # \param shape The reference shape.
    # \param new_set If <tt>True</tt>, <em>shape</em> is added to a new reference set; otherwise it is appended to the most recent reference set.
    # 
    def addReferenceShape(shape: GaussianShape, new_set: bool = True) -> None: pass

    ##
    # \brief Adds the shapes in <em>shapes</em> to the reference shapes.
    # 
    # \param shapes The reference shapes.
    # \param new_set If <tt>True</tt>, the shapes are added to a new reference set; otherwise they are appended to the most recent reference set.
    # 
    def addReferenceShapes(shapes: GaussianShapeSet, new_set: bool = True) -> None: pass

    ##
    # \brief Returns the total number of reference shapes.
    # 
    def getNumReferenceShapes() -> int: pass

    ##
    # \brief Aligns <em>shape</em> against all reference shapes.
    # 
    # \param shape The shape to align.
    # 
    # \return <tt>True</tt> if at least one alignment result was produced, and <tt>False</tt> otherwise.
    # 
    def align(shape: GaussianShape) -> bool: pass

    ##
    # \brief Aligns each shape in <em>shapes</em> against all reference shapes.
    # 
    # \param shapes The shapes to align.
    # 
    # \return <tt>True</tt> if at least one alignment result was produced, and <tt>False</tt> otherwise.
    # 
    def align(shapes: GaussianShapeSet) -> bool: pass

    ##
    # \brief Returns the number of stored alignment results.
    # 
    def getNumResults() -> int: pass

    ##
    # \brief Returns the alignment result at index <em>idx</em>.
    # 
    # \param idx The zero-based result index.
    # 
    # \return A reference to the result. 
    # 
    # \throw Base.IndexError if the number of results is zero or <em>idx</em> is not in the range [0, getNumResults() - 1].
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
