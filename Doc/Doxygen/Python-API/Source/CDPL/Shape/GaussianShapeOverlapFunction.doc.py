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
class GaussianShapeOverlapFunction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GaussianShapeOverlapFunction instance.
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
    # \brief 
    # \param func 
    # \param is_ref 
    #
    def setShapeFunction(func: GaussianShapeFunction, is_ref: bool) -> None: pass

    ##
    # \brief 
    # \param ref 
    # \return 
    #
    def getShapeFunction(ref: bool) -> GaussianShapeFunction: pass

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
    # \param ref 
    # \return 
    #
    def calcSelfOverlap(ref: bool) -> float: pass

    ##
    # \brief 
    # \param ref 
    # \return 
    #
    def calcColorSelfOverlap(ref: bool) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def calcOverlap() -> float: pass

    ##
    # \brief 
    # \param coords 
    # \return 
    #
    def calcOverlap(coords: Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def calcColorOverlap() -> float: pass

    ##
    # \brief 
    # \param coords 
    # \return 
    #
    def calcColorOverlap(coords: Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \param coords 
    # \param grad 
    # \return 
    #
    def calcOverlapGradient(coords: Math.Vector3DArray, grad: Math.Vector3DArray) -> float: pass

    objectID = property(getObjectID)

    colorMatchFunction = property(getColorMatchFunction, setColorMatchFunction)

    colorFilterFunction = property(getColorFilterFunction, setColorFilterFunction)
