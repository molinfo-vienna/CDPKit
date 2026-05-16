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
# \brief Result of a Gaussian-shape alignment between a reference and an aligned shape.
# 
# Bundles the rigid-body transformation that brings the aligned shape onto the reference shape together with the resulting overlap-based score values, source/destination shape indices, and the self-overlap values used for normalization.
# 
class AlignmentResult(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>AlignmentResult</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %AlignmentResult instance \a res.
    # \param res The \c %AlignmentResult instance to copy.
    # 
    def __init__(res: AlignmentResult) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %AlignmentResult instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %AlignmentResult instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %AlignmentResult instance \a res.
    # \param res The \c %AlignmentResult instance to copy.
    # \return \a self
    # 
    def assign(res: AlignmentResult) -> AlignmentResult: pass

    ##
    # \brief Returns the rigid-body transformation matrix that maps the aligned shape onto the reference shape.
    # 
    # \return The transformation matrix.
    # 
    def getTransform() -> Math.Matrix4D: pass

    ##
    # \brief Sets the rigid-body transformation matrix.
    # 
    # \param xform The transformation matrix.
    # 
    def setTransform(xform: Math.Matrix4D) -> None: pass

    ##
    # \brief Returns the score of the alignment.
    # 
    # \return The alignment score.
    # 
    def getScore() -> float: pass

    ##
    # \brief Sets the score of the alignment.
    # 
    # \param score The alignment score.
    # 
    def setScore(score: float) -> None: pass

    ##
    # \brief Returns the index of the reference shape set the aligned shape was matched against.
    # 
    # \return The reference shape set index.
    # 
    def getReferenceShapeSetIndex() -> int: pass

    ##
    # \brief Sets the index of the reference shape set.
    # 
    # \param idx The reference shape set index.
    # 
    def setReferenceShapeSetIndex(idx: int) -> None: pass

    ##
    # \brief Returns the index of the reference shape within its shape set.
    # 
    # \return The reference shape index.
    # 
    def getReferenceShapeIndex() -> int: pass

    ##
    # \brief Sets the index of the reference shape within its shape set.
    # 
    # \param idx The reference shape index.
    # 
    def setReferenceShapeIndex(idx: int) -> None: pass

    ##
    # \brief Returns the index of the aligned shape.
    # 
    # \return The aligned shape index.
    # 
    def getAlignedShapeIndex() -> int: pass

    ##
    # \brief Sets the index of the aligned shape.
    # 
    # \param idx The aligned shape index.
    # 
    def setAlignedShapeIndex(idx: int) -> None: pass

    ##
    # \brief Returns the calculated overlap between the reference and the aligned shape (shape-only contribution).
    # 
    # \return The shape overlap value.
    # 
    def getOverlap() -> float: pass

    ##
    # \brief Sets the overlap between the reference and the aligned shape (shape-only contribution).
    # 
    # \param overlap The shape overlap value.
    # 
    def setOverlap(overlap: float) -> None: pass

    ##
    # \brief Returns the calculated overlap between the reference and the aligned shape (color/pharmacophore contribution).
    # 
    # \return The color overlap value.
    # 
    def getColorOverlap() -> float: pass

    ##
    # \brief Sets the overlap between the reference and the aligned shape (color/pharmacophore contribution).
    # 
    # \param overlap The color overlap value.
    # 
    def setColorOverlap(overlap: float) -> None: pass

    ##
    # \brief Returns the self-overlap of the reference shape (shape-only contribution).
    # 
    # \return The reference shape self-overlap value.
    # 
    def getReferenceSelfOverlap() -> float: pass

    ##
    # \brief Sets the self-overlap of the reference shape (shape-only contribution).
    # 
    # \param overlap The reference shape self-overlap value.
    # 
    def setReferenceSelfOverlap(overlap: float) -> None: pass

    ##
    # \brief Returns the self-overlap of the reference shape (color/pharmacophore contribution).
    # 
    # \return The reference shape color self-overlap value.
    # 
    def getReferenceColorSelfOverlap() -> float: pass

    ##
    # \brief Sets the self-overlap of the reference shape (color/pharmacophore contribution).
    # 
    # \param overlap The reference shape color self-overlap value.
    # 
    def setReferenceColorSelfOverlap(overlap: float) -> None: pass

    ##
    # \brief Returns the self-overlap of the aligned shape (shape-only contribution).
    # 
    # \return The aligned shape self-overlap value.
    # 
    def getAlignedSelfOverlap() -> float: pass

    ##
    # \brief Sets the self-overlap of the aligned shape (shape-only contribution).
    # 
    # \param overlap The aligned shape self-overlap value.
    # 
    def setAlignedSelfOverlap(overlap: float) -> None: pass

    ##
    # \brief Returns the self-overlap of the aligned shape (color/pharmacophore contribution).
    # 
    # \return The aligned shape color self-overlap value.
    # 
    def getAlignedColorSelfOverlap() -> float: pass

    ##
    # \brief Sets the self-overlap of the aligned shape (color/pharmacophore contribution).
    # 
    # \param overlap The aligned shape color self-overlap value.
    # 
    def setAlignedColorSelfOverlap(overlap: float) -> None: pass

    objectID = property(getObjectID)

    transform = property(getTransform, setTransform)

    score = property(getScore, setScore)

    referenceShapeSetIndex = property(getReferenceShapeSetIndex, setReferenceShapeSetIndex)

    referenceShapeIndex = property(getReferenceShapeIndex, setReferenceShapeIndex)

    alignedShapeIndex = property(getAlignedShapeIndex, setAlignedShapeIndex)

    overlap = property(getOverlap, setOverlap)

    colorOverlap = property(getColorOverlap, setColorOverlap)

    referenceSelfOverlap = property(getReferenceSelfOverlap, setReferenceSelfOverlap)

    referenceColorSelfOverlap = property(getReferenceColorSelfOverlap, setReferenceColorSelfOverlap)

    alignedSelfOverlap = property(getAlignedSelfOverlap, setAlignedSelfOverlap)

    alignedColorSelfOverlap = property(getAlignedColorSelfOverlap, setAlignedColorSelfOverlap)
