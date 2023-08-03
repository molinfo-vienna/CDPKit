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
class GaussianShapeFunctionAlignment(Boost.Python.instance):

    ##
    # \brief 
    #
    class Result(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Result instance.
        # \param transform 
        # \param overlap 
        # \param col_overlap 
        # 
        def __init__(transform: Math.Matrix4D, overlap: float, col_overlap: float) -> None: pass

        ##
        # \brief Initializes the \e %Result instance with a copy of the state of the \e %Result instance \a res.
        # \param res The \e %Result instance to copy.
        # 
        def __init__(res: Result) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %Result instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Result instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Result instance \a res.
        # \param res The \e %Result instance to copy.
        # \return \a self
        # 
        def assign(res: Result) -> Result: pass

        ##
        # \brief 
        # \return 
        #
        def getTransform() -> Math.Matrix4D: pass

        ##
        # \brief 
        # \return 
        #
        def getOverlap() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getColorOverlap() -> float: pass

        objectID = property(getObjectID)

        transform = property(getTransform)

        overlap = property(getOverlap)

        colorOverlap = property(getColorOverlap)

    ##
    # \brief 
    #
    DEF_OPTIMIZATION_STOP_GRADIENT = 1.0

    ##
    # \brief 
    #
    DEF_MAX_OPTIMIZATION_ITERATIONS = 20

    ##
    # \brief Initializes the \e %GaussianShapeFunctionAlignment instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeFunctionAlignment instance.
    # \param ref_func 
    # \param sym_class 
    # 
    def __init__(ref_func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %GaussianShapeFunctionAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeFunctionAlignment instances \e a and \e b reference different C++ objects. 
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
    # \param func 
    # \param sym_class 
    #
    def setReference(func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReference() -> GaussianShapeFunction: pass

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
    # \param func 
    # \param xform 
    # \return 
    #
    def setupReference(func: GaussianShapeFunction, xform: Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param func 
    # \param xform 
    # \return 
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
    # \param func 
    # \param sym_class 
    # \return 
    #
    def align(func: GaussianShapeFunction, sym_class: int) -> bool: pass

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

    ##
    # \brief FIXME!
    # \brief 
    #
    referenceShapeFunction = property(getReferenceShapeFunction, setReferenceShapeFunction)

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
