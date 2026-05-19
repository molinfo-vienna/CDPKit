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
# \brief Abstract base for functions evaluating the overlap between two Gaussian shape functions.
# 
# Concrete subclasses (e.g. Shape.ExactGaussianShapeOverlapFunction, Shape.FastGaussianShapeOverlapFunction) implement the overlap evaluation using different trade-offs of accuracy vs. speed.
# 
class GaussianShapeOverlapFunction(Boost.Python.instance):

    ##
    # \brief Initializes the \c %GaussianShapeOverlapFunction instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeOverlapFunction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeOverlapFunction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies the reference or aligned shape function used by the overlap evaluation.
    # 
    # \param func The shape function.
    # \param is_ref If <tt>True</tt>, <em>func</em> is the reference shape function; otherwise the aligned shape function.
    # 
    def setShapeFunction(func: GaussianShapeFunction, is_ref: bool) -> None: pass

    ##
    # \brief Returns the reference or aligned shape function.
    # 
    # \param ref If <tt>True</tt>, the reference shape function is returned; otherwise the aligned shape function.
    # 
    # \return A reference to the requested shape function (or <tt>nullptr</tt> if none is associated).
    # 
    def getShapeFunction(ref: bool) -> GaussianShapeFunction: pass

    ##
    # \brief Specifies the function used to decide whether two color features match.
    # 
    # \param func The color-match function.
    # 
    def setColorMatchFunction(func: Pharm.BoolSizeType2Functor) -> None: pass

    ##
    # \brief Returns the currently configured color-match function.
    # 
    # \return A reference to the color-match function.
    # 
    def getColorMatchFunction() -> Pharm.BoolSizeType2Functor: pass

    ##
    # \brief Specifies the function used to filter color features by type.
    # 
    # \param func The color-filter function.
    # 
    def setColorFilterFunction(func: BoolSizeTypeFunctor) -> None: pass

    ##
    # \brief Returns the currently configured color-filter function.
    # 
    # \return A reference to the color-filter function.
    # 
    def getColorFilterFunction() -> BoolSizeTypeFunctor: pass

    ##
    # \brief Calculates the shape-only self-overlap of the reference or aligned shape function.
    # 
    # \param ref If <tt>True</tt>, the reference self-overlap is returned; otherwise the aligned self-overlap.
    # 
    # \return The self-overlap value.
    # 
    def calcSelfOverlap(ref: bool) -> float: pass

    ##
    # \brief Calculates the color self-overlap of the reference or aligned shape function.
    # 
    # \param ref If <tt>True</tt>, the reference color self-overlap is returned; otherwise the aligned color self-overlap.
    # 
    # \return The color self-overlap value.
    # 
    def calcColorSelfOverlap(ref: bool) -> float: pass

    ##
    # \brief Calculates the shape-only overlap of the reference and aligned shape functions.
    # 
    # \return The shape overlap value.
    # 
    def calcOverlap() -> float: pass

    ##
    # \brief Calculates the shape-only overlap with the aligned shape element positions taken from <em>coords</em>.
    # 
    # \param coords The element 3D positions of the aligned shape.
    # 
    # \return The shape overlap value.
    # 
    def calcOverlap(coords: Math.Vector3DArray) -> float: pass

    ##
    # \brief Calculates the color overlap of the reference and aligned shape functions.
    # 
    # \return The color overlap value.
    # 
    def calcColorOverlap() -> float: pass

    ##
    # \brief Calculates the color overlap with the aligned shape element positions taken from <em>coords</em>.
    # 
    # \param coords The element 3D positions of the aligned shape.
    # 
    # \return The color overlap value.
    # 
    def calcColorOverlap(coords: Math.Vector3DArray) -> float: pass

    ##
    # \brief Calculates the shape overlap with the aligned shape element positions taken from <em>coords</em> and returns the gradient with respect to those positions.
    # 
    # \param coords The element 3D positions of the aligned shape.
    # \param grad The output element-wise gradient of the overlap.
    # 
    # \return The shape overlap value.
    # 
    def calcOverlapGradient(coords: Math.Vector3DArray, grad: Math.Vector3DArray) -> float: pass

    objectID = property(getObjectID)

    colorMatchFunction = property(getColorMatchFunction, setColorMatchFunction)

    colorFilterFunction = property(getColorFilterFunction, setColorFilterFunction)
