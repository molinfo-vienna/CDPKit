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
# \brief Driver for the alignment of one Shape.GaussianShapeFunction (the aligned shape) against a fixed reference Shape.GaussianShapeFunction.
# 
# The alignment iterates over starting transformations produced by a configurable Shape.GaussianShapeAlignmentStartGenerator, optionally refines each start via BFGS minimization of the overlap function, and collects the resulting transformations and overlap values in Result instances.
# 
class GaussianShapeFunctionAlignment(Boost.Python.instance):

    ##
    # \brief A single alignment result: rigid-body transformation plus shape and color overlap values.
    # 
    class Result(Boost.Python.instance):

        ##
        # \brief Initializes the \c %Result instance.
        # \param transform 
        # \param overlap 
        # \param col_overlap 
        # 
        def __init__(transform: Math.Matrix4D, overlap: float, col_overlap: float) -> None: pass

        ##
        # \brief Initializes a copy of the \c %Result instance \a res.
        # \param res The \c %Result instance to copy.
        # 
        def __init__(res: Result) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Result instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Result instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Result instance \a res.
        # \param res The \c %Result instance to copy.
        # \return \a self
        # 
        def assign(res: Result) -> Result: pass

        ##
        # \brief Returns the rigid-body transformation that maps the aligned shape onto the reference shape.
        # 
        def getTransform() -> Math.Matrix4D: pass

        ##
        # \brief Returns the shape overlap value of the alignment.
        # 
        def getOverlap() -> float: pass

        ##
        # \brief Returns the color overlap value of the alignment.
        # 
        def getColorOverlap() -> float: pass

        objectID = property(getObjectID)

        transform = property(getTransform)

        overlap = property(getOverlap)

        colorOverlap = property(getColorOverlap)

    ##
    # \brief Default gradient norm at which the overlap optimization is stopped.
    # 
    DEF_OPTIMIZATION_STOP_GRADIENT = 1.0

    ##
    # \brief Default maximum number of overlap-optimization iterations.
    # 
    DEF_MAX_OPTIMIZATION_ITERATIONS = 20

    ##
    # \brief Constructs the <tt>GaussianShapeFunctionAlignment</tt> instance without a reference shape.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>GaussianShapeFunctionAlignment</tt> instance with the given reference shape function.
    # 
    # \param ref_func The reference shape function.
    # \param sym_class The symmetry class of the reference shape (see namespace Shape.SymmetryClass).
    # 
    def __init__(ref_func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeFunctionAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeFunctionAlignment instances \e a and \e b reference different C++ objects. 
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
    # \brief Returns the built-in default overlap function (Shape.FastGaussianShapeOverlapFunction).
    # 
    def getDefaultOverlapFunction() -> FastGaussianShapeOverlapFunction: pass

    ##
    # \brief Sets the reference shape function used by subsequent align() calls.
    # 
    # \param func The reference shape function.
    # \param sym_class The symmetry class of the reference shape (see namespace Shape.SymmetryClass).
    # 
    def setReference(func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief Returns the current reference shape function (or <tt>nullptr</tt> if none is set).
    # 
    # \return A reference to the reference shape function.
    # 
    def getReference() -> GaussianShapeFunction: pass

    ##
    # \brief Specifies the alignment-start generator used to seed the overlap optimization.
    # 
    def setStartGenerator(gen: GaussianShapeAlignmentStartGenerator) -> None: pass

    ##
    # \brief Returns the currently configured alignment-start generator.
    # 
    def getStartGenerator() -> GaussianShapeAlignmentStartGenerator: pass

    ##
    # \brief Returns the built-in default principal-axes alignment-start generator.
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
    # \brief Specifies whether the actual alignment shall be performed (vs. only evaluating overlaps in the initial pose).
    # 
    def performAlignment(perf_align: bool) -> None: pass

    ##
    # \brief Tells whether the actual alignment is performed.
    # 
    def performAlignment() -> bool: pass

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
    # \brief Delegates the reference-shape preparation to the configured start generator.
    # 
    # \param func The reference shape function (may be modified).
    # \param xform The output transformation that maps the prepared frame back to the original frame.
    # 
    # \return The perceived symmetry class of the reference shape (see namespace Shape.SymmetryClass).
    # 
    def setupReference(func: GaussianShapeFunction, xform: Math.Matrix4D) -> int: pass

    ##
    # \brief Delegates the aligned-shape preparation to the configured start generator.
    # 
    # \param func The aligned shape function (may be modified).
    # \param xform The output transformation that maps the prepared frame back to the original frame.
    # 
    # \return The perceived symmetry class of the aligned shape (see namespace Shape.SymmetryClass).
    # 
    def setupAligned(func: GaussianShapeFunction, xform: Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param calc 
    # \return 
    #
    def calcSelfOverlap(calc: GaussianShapeFunction) -> float: pass

    ##
    # \brief 
    # \param calc 
    # \return 
    #
    def calcColorSelfOverlap(calc: GaussianShapeFunction) -> float: pass

    ##
    # \brief Specifies whether color overlaps shall be evaluated in addition to shape overlaps.
    # 
    def calcColorOverlaps(calc: bool) -> None: pass

    ##
    # \brief Tells whether color overlaps are evaluated.
    # 
    def calcColorOverlaps() -> bool: pass

    ##
    # \brief Aligns the shape function <em>func</em> against the configured reference shape.
    # 
    # \param func The aligned shape function.
    # \param sym_class The symmetry class of the aligned shape (see namespace Shape.SymmetryClass).
    # 
    # \return <tt>True</tt> if at least one alignment result was produced, and <tt>False</tt> otherwise.
    # 
    def align(func: GaussianShapeFunction, sym_class: int) -> bool: pass

    ##
    # \brief Returns the number of alignment results produced by the last align() call.
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
    def getResult(idx: int) -> Result: pass

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
    def __getitem__(idx: int) -> Result: pass

    objectID = property(getObjectID)

    numResults = property(getNumResults)

    overlapFunction = property(getOverlapFunction, setOverlapFunction)

    defaultOverlapFunction = property(getDefaultOverlapFunction)

    reference = property(getReference, setReference)

    startGenerator = property(getStartGenerator, setStartGenerator)

    defaultStartGenerator = property(getDefaultStartGenerator)

    colorMatchFunction = property(getColorMatchFunction, setColorMatchFunction)

    colorFilterFunction = property(getColorFilterFunction, setColorFilterFunction)

    perfAlignment = property(performAlignment, performAlignment)

    maxNumOptIterations = property(getMaxNumOptimizationIterations, setMaxNumOptimizationIterations)

    optStopGradient = property(getOptimizationStopGradient, setOptimizationStopGradient)

    optOverlap = property(optimizeOverlap, optimizeOverlap)

    greedyOpt = property(greedyOptimization, greedyOptimization)

    colorOverlaps = property(calcColorOverlaps, calcColorOverlaps)
