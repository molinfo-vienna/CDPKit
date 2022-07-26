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
class AlignmentResult(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AlignmentResult instance.
    # \param self The \e %AlignmentResult instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %AlignmentResult instance.
    # \param self The \e %AlignmentResult instance to initialize.
    # \param res 
    #
    def __init__(self: object, res: AlignmentResult) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AlignmentResult instance this method is called upon.
    #
    # Different Python \e %AlignmentResult instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AlignmentResult instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: AlignmentResult) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AlignmentResult instance \a res.
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param res The \e %AlignmentResult instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AlignmentResult, res: AlignmentResult) -> AlignmentResult: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getTransform(self: AlignmentResult) -> CDPL.Math.Matrix4D: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param xform 
    #
    def setTransform(self: AlignmentResult, xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getScore(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param score 
    #
    def setScore(self: AlignmentResult, score: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getReferenceShapeSetIndex(self: AlignmentResult) -> int: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param idx 
    #
    def setReferenceShapeSetIndex(self: AlignmentResult, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getReferenceShapeIndex(self: AlignmentResult) -> int: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param idx 
    #
    def setReferenceShapeIndex(self: AlignmentResult, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getAlignedShapeIndex(self: AlignmentResult) -> int: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param idx 
    #
    def setAlignedShapeIndex(self: AlignmentResult, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getOverlap(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param overlap 
    #
    def setOverlap(self: AlignmentResult, overlap: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getColorOverlap(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param overlap 
    #
    def setColorOverlap(self: AlignmentResult, overlap: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getReferenceSelfOverlap(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param overlap 
    #
    def setReferenceSelfOverlap(self: AlignmentResult, overlap: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getReferenceColorSelfOverlap(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param overlap 
    #
    def setReferenceColorSelfOverlap(self: AlignmentResult, overlap: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getAlignedSelfOverlap(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param overlap 
    #
    def setAlignedSelfOverlap(self: AlignmentResult, overlap: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \return 
    #
    def getAlignedColorSelfOverlap(self: AlignmentResult) -> float: pass

    ##
    # \brief 
    # \param self The \e %AlignmentResult instance this method is called upon.
    # \param overlap 
    #
    def setAlignedColorSelfOverlap(self: AlignmentResult, overlap: float) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    transform = property(getTransform, setTransform)

    ##
    # \brief 
    #
    score = property(getScore, setScore)

    ##
    # \brief 
    #
    referenceShapeSetIndex = property(getReferenceShapeSetIndex, setReferenceShapeSetIndex)

    ##
    # \brief 
    #
    referenceShapeIndex = property(getReferenceShapeIndex, setReferenceShapeIndex)

    ##
    # \brief 
    #
    alignedShapeIndex = property(getAlignedShapeIndex, setAlignedShapeIndex)

    ##
    # \brief 
    #
    overlap = property(getOverlap, setOverlap)

    ##
    # \brief 
    #
    colorOverlap = property(getColorOverlap, setColorOverlap)

    ##
    # \brief 
    #
    referenceSelfOverlap = property(getReferenceSelfOverlap, setReferenceSelfOverlap)

    ##
    # \brief 
    #
    referenceColorSelfOverlap = property(getReferenceColorSelfOverlap, setReferenceColorSelfOverlap)

    ##
    # \brief 
    #
    alignedSelfOverlap = property(getAlignedSelfOverlap, setAlignedSelfOverlap)

    ##
    # \brief 
    #
    alignedColorSelfOverlap = property(getAlignedColorSelfOverlap, setAlignedColorSelfOverlap)
