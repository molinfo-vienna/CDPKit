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
class GaussianShapeFunctionAlignment(Boost.Python.instance):

    ##
    # \brief 
    #
    class Result(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Result instance.
        # \param self The \e %Result instance to initialize.
        # \param transform 
        # \param overlap 
        # \param col_overlap 
        #
        def __init__(self: object, transform: CDPL.Math.Matrix4D, overlap: float, col_overlap: float) -> None: pass

        ##
        # \brief Initializes the \e %Result instance.
        # \param self The \e %Result instance to initialize.
        # \param res 
        #
        def __init__(self: object, res: Result) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Result instance this method is called upon.
        #
        # Different Python \e %Result instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Result instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: Result) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Result instance \a res.
        # \param self The \e %Result instance this method is called upon.
        # \param res The \e %Result instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Result, res: Result) -> Result: pass

        ##
        # \brief 
        # \param self The \e %Result instance this method is called upon.
        # \return 
        #
        def getTransform(self: Result) -> CDPL.Math.Matrix4D: pass

        ##
        # \brief 
        # \param self The \e %Result instance this method is called upon.
        # \return 
        #
        def getOverlap(self: Result) -> float: pass

        ##
        # \brief 
        # \param self The \e %Result instance this method is called upon.
        # \return 
        #
        def getColorOverlap(self: Result) -> float: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        transform = property(getTransform)

        ##
        # \brief 
        #
        overlap = property(getOverlap)

        ##
        # \brief 
        #
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
    # \param self The \e %GaussianShapeFunctionAlignment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeFunctionAlignment instance.
    # \param self The \e %GaussianShapeFunctionAlignment instance to initialize.
    # \param ref_func 
    # \param sym_class 
    #
    def __init__(self: object, ref_func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    #
    # Different Python \e %GaussianShapeFunctionAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeFunctionAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeFunctionAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    #
    def setOverlapFunction(self: GaussianShapeFunctionAlignment, func: GaussianShapeOverlapFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getOverlapFunction(self: GaussianShapeFunctionAlignment) -> GaussianShapeOverlapFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getDefaultOverlapFunction(self: GaussianShapeFunctionAlignment) -> FastGaussianShapeOverlapFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    # \param sym_class 
    #
    def setReference(self: GaussianShapeFunctionAlignment, func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getReference(self: GaussianShapeFunctionAlignment) -> GaussianShapeFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param gen 
    #
    def setStartGenerator(self: GaussianShapeFunctionAlignment, gen: GaussianShapeAlignmentStartGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getStartGenerator(self: GaussianShapeFunctionAlignment) -> GaussianShapeAlignmentStartGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getDefaultStartGenerator(self: GaussianShapeFunctionAlignment) -> PrincipalAxesAlignmentStartGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    #
    def setColorMatchFunction(self: GaussianShapeFunctionAlignment, func: CDPL.Pharm.BoolSizeType2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getColorMatchFunction(self: GaussianShapeFunctionAlignment) -> CDPL.Pharm.BoolSizeType2Functor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    #
    def setColorFilterFunction(self: GaussianShapeFunctionAlignment, func: BoolSizeTypeFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getColorFilterFunction(self: GaussianShapeFunctionAlignment) -> BoolSizeTypeFunctor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param perf_align 
    #
    def performAlignment(self: GaussianShapeFunctionAlignment, perf_align: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def performAlignment(self: GaussianShapeFunctionAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param max_iter 
    #
    def setMaxNumOptimizationIterations(self: GaussianShapeFunctionAlignment, max_iter: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getMaxNumOptimizationIterations(self: GaussianShapeFunctionAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param grad_norm 
    #
    def setOptimizationStopGradient(self: GaussianShapeFunctionAlignment, grad_norm: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getOptimizationStopGradient(self: GaussianShapeFunctionAlignment) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param optimize 
    #
    def optimizeOverlap(self: GaussianShapeFunctionAlignment, optimize: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def optimizeOverlap(self: GaussianShapeFunctionAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param greedy 
    #
    def greedyOptimization(self: GaussianShapeFunctionAlignment, greedy: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def greedyOptimization(self: GaussianShapeFunctionAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    # \param xform 
    # \return 
    #
    def setupReference(self: GaussianShapeFunctionAlignment, func: GaussianShapeFunction, xform: CDPL.Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    # \param xform 
    # \return 
    #
    def setupAligned(self: GaussianShapeFunctionAlignment, func: GaussianShapeFunction, xform: CDPL.Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param calc 
    # \return 
    #
    def calcSelfOverlap(self: GaussianShapeFunctionAlignment, calc: GaussianShapeFunction) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param calc 
    # \return 
    #
    def calcColorSelfOverlap(self: GaussianShapeFunctionAlignment, calc: GaussianShapeFunction) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param calc 
    #
    def calcColorOverlaps(self: GaussianShapeFunctionAlignment, calc: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def calcColorOverlaps(self: GaussianShapeFunctionAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param func 
    # \param sym_class 
    # \return 
    #
    def align(self: GaussianShapeFunctionAlignment, func: GaussianShapeFunction, sym_class: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def getNumResults(self: GaussianShapeFunctionAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getResult(self: GaussianShapeFunctionAlignment, idx: int) -> Result: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \return 
    #
    def __len__(self: GaussianShapeFunctionAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunctionAlignment instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: GaussianShapeFunctionAlignment, idx: int) -> Result: pass

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
    # \brief FIXME!
    #
    referenceShapeFunction = property(getReferenceShapeFunction, setReferenceShapeFunction)

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
    # \brief FIXME!
    #
    perfAlignment = property(getPerfAlignment, setPerfAlignment)

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
    optOverlap = property(getOptOverlap, setOptOverlap)

    ##
    # \brief FIXME!
    #
    greedyOpt = property(getGreedyOpt, setGreedyOpt)

    ##
    # \brief FIXME!
    #
    colorOverlaps = property(getColorOverlaps, setColorOverlaps)
