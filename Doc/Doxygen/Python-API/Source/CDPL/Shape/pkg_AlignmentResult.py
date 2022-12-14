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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AlignmentResult instance.
    # \param res 
    #
    def __init__(res: AlignmentResult) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %AlignmentResult instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AlignmentResult instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AlignmentResult instance \a res.
    # \param res The \e %AlignmentResult instance to copy.
    # \return \a self
    #
    def assign(res: AlignmentResult) -> AlignmentResult: pass

    ##
    # \brief 
    # \return 
    #
    def getTransform() -> CDPL.Math.Matrix4D: pass

    ##
    # \brief 
    # \param xform 
    #
    def setTransform(xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScore() -> float: pass

    ##
    # \brief 
    # \param score 
    #
    def setScore(score: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceShapeSetIndex() -> int: pass

    ##
    # \brief 
    # \param idx 
    #
    def setReferenceShapeSetIndex(idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceShapeIndex() -> int: pass

    ##
    # \brief 
    # \param idx 
    #
    def setReferenceShapeIndex(idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAlignedShapeIndex() -> int: pass

    ##
    # \brief 
    # \param idx 
    #
    def setAlignedShapeIndex(idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getOverlap() -> float: pass

    ##
    # \brief 
    # \param overlap 
    #
    def setOverlap(overlap: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getColorOverlap() -> float: pass

    ##
    # \brief 
    # \param overlap 
    #
    def setColorOverlap(overlap: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceSelfOverlap() -> float: pass

    ##
    # \brief 
    # \param overlap 
    #
    def setReferenceSelfOverlap(overlap: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceColorSelfOverlap() -> float: pass

    ##
    # \brief 
    # \param overlap 
    #
    def setReferenceColorSelfOverlap(overlap: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAlignedSelfOverlap() -> float: pass

    ##
    # \brief 
    # \param overlap 
    #
    def setAlignedSelfOverlap(overlap: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAlignedColorSelfOverlap() -> float: pass

    ##
    # \brief 
    # \param overlap 
    #
    def setAlignedColorSelfOverlap(overlap: float) -> None: pass

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
