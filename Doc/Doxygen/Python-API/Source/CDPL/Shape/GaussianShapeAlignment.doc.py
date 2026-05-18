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
# \brief High-level driver for the alignment of Gaussian shapes against a set of reference shapes.
# 
# The class manages a list of reference Gaussian shapes (organised into reference sets), runs the underlying Shape.GaussianShapeFunctionAlignment for each (reference, aligned) pair, and collects the Shape.AlignmentResult instances filtered according to the configured selection mode and comparator/scoring functions.
# 
class GaussianShapeAlignment(Boost.Python.instance):

    ##
    # \brief Default gradient norm at which the overlap optimization is stopped.
    # 
    DEF_OPTIMIZATION_STOP_GRADIENT = 1.0

    ##
    # \brief Default maximum number of overlap-optimization iterations.
    # 
    DEF_MAX_OPTIMIZATION_ITERATIONS = 20

    ##
    # \brief Default maximum order of the Gaussian-product expansion.
    # 
    DEF_MAX_PRODUCT_ORDER = 1

    ##
    # \brief Default distance cutoff for pruning negligible overlap contributions.
    # 
    DEF_DISTANCE_CUTOFF = 0.0

    ##
    # \brief Default alignment-result selection mode.
    # 
    DEF_RESULT_SELECTION_MODE = 3

    ##
    # \brief Constructs the <tt>GaussianShapeAlignment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>GaussianShapeAlignment</tt> instance with <em>ref_shape</em> as the single reference shape.
    # 
    def __init__(ref_shape: GaussianShape) -> None: pass

    ##
    # \brief Constructs the <tt>GaussianShapeAlignment</tt> instance with the shapes in <em>ref_shapes</em> as the reference set.
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
    # \brief Specifies the Gaussian-shape overlap function used during alignment.
    # 
    def setOverlapFunction(func: GaussianShapeOverlapFunction) -> None: pass

    ##
    # \brief Returns the currently configured overlap function.
    # 
    def getOverlapFunction() -> GaussianShapeOverlapFunction: pass

    ##
    # \brief Returns the built-in default overlap function.
    # 
    def getDefaultOverlapFunction() -> FastGaussianShapeOverlapFunction: pass

    ##
    # \brief Specifies the alignment-start generator used to seed the overlap optimization.
    # 
    def setStartGenerator(gen: GaussianShapeAlignmentStartGenerator) -> None: pass

    ##
    # \brief Returns the currently configured alignment-start generator.
    # 
    def getStartGenerator() -> GaussianShapeAlignmentStartGenerator: pass

    ##
    # \brief Returns the built-in principal-axes alignment-start generator.
    # 
    def getDefaultStartGenerator() -> PrincipalAxesAlignmentStartGenerator: pass

    ##
    # \brief Specifies the function used to decide whether two color features match.
    # 
    def setColorMatchFunction(func: Pharm.BoolSizeType2Functor) -> None: pass

    ##
    # \brief Returns the currently configured color-match function.
    # 
    def getColorMatchFunction() -> Pharm.BoolSizeType2Functor: pass

    ##
    # \brief Specifies the function used to filter color features by type.
    # 
    def setColorFilterFunction(func: BoolSizeTypeFunctor) -> None: pass

    ##
    # \brief Returns the currently configured color-filter function.
    # 
    def getColorFilterFunction() -> BoolSizeTypeFunctor: pass

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
    # \brief Specifies whether the actual alignment shall be performed (vs. only computing overlaps in the initial pose).
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
    # \brief Specifies whether color overlaps shall be computed in addition to shape overlaps.
    # 
    def calcColorOverlaps(calc: bool) -> None: pass

    ##
    # \brief Tells whether color overlaps are computed in addition to shape overlaps.
    # 
    def calcColorOverlaps() -> bool: pass

    ##
    # \brief Specifies whether shape self-overlaps shall be computed for the involved shapes.
    # 
    def calcSelfOverlaps(calc: bool) -> None: pass

    ##
    # \brief Tells whether shape self-overlaps are computed for the involved shapes.
    # 
    def calcSelfOverlaps() -> bool: pass

    ##
    # \brief Specifies whether color self-overlaps shall be computed for the involved shapes.
    # 
    def calcColorSelfOverlaps(calc: bool) -> None: pass

    ##
    # \brief Tells whether color self-overlaps are computed for the involved shapes.
    # 
    def calcColorSelfOverlaps() -> bool: pass

    ##
    # \brief Sets the maximum order of the Gaussian-product expansion used by the overlap function.
    # 
    def setMaxOrder(max_order: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum order of the Gaussian-product expansion.
    # 
    def getMaxOrder() -> int: pass

    ##
    # \brief Sets the distance cutoff for pruning negligible overlap contributions.
    # 
    def setDistanceCutoff(cutoff: float) -> None: pass

    ##
    # \brief Returns the currently configured distance cutoff.
    # 
    def getDistanceCutoff() -> float: pass

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
    # \brief Returns the reference shape at index <em>idx</em>.
    # 
    def getReferenceShape(idx: int) -> GaussianShape: pass

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
