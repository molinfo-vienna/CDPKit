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
class GaussianShapeOverlapFunction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GaussianShapeOverlapFunction instance.
    # \param self The \e %GaussianShapeOverlapFunction instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    #
    # Different Python \e %GaussianShapeOverlapFunction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeOverlapFunction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeOverlapFunction) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param func 
    # \param is_ref 
    #
    def setShapeFunction(self: GaussianShapeOverlapFunction, func: GaussianShapeFunction, is_ref: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param ref 
    # \return 
    #
    def getShapeFunction(self: GaussianShapeOverlapFunction, ref: bool) -> GaussianShapeFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param func 
    #
    def setColorMatchFunction(self: GaussianShapeOverlapFunction, func: CDPL.Pharm.BoolSizeType2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \return 
    #
    def getColorMatchFunction(self: GaussianShapeOverlapFunction) -> CDPL.Pharm.BoolSizeType2Functor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param func 
    #
    def setColorFilterFunction(self: GaussianShapeOverlapFunction, func: BoolSizeTypeFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \return 
    #
    def getColorFilterFunction(self: GaussianShapeOverlapFunction) -> BoolSizeTypeFunctor: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param ref 
    # \return 
    #
    def calcSelfOverlap(self: GaussianShapeOverlapFunction, ref: bool) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param ref 
    # \return 
    #
    def calcColorSelfOverlap(self: GaussianShapeOverlapFunction, ref: bool) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \return 
    #
    def calcOverlap(self: GaussianShapeOverlapFunction) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param coords 
    # \return 
    #
    def calcOverlap(self: GaussianShapeOverlapFunction, coords: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \return 
    #
    def calcColorOverlap(self: GaussianShapeOverlapFunction) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param coords 
    # \return 
    #
    def calcColorOverlap(self: GaussianShapeOverlapFunction, coords: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeOverlapFunction instance this method is called upon.
    # \param coords 
    # \param grad 
    # \return 
    #
    def calcOverlapGradient(self: GaussianShapeOverlapFunction, coords: CDPL.Math.Vector3DArray, grad: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    colorMatchFunction = property(getColorMatchFunction, setColorMatchFunction)

    ##
    # \brief 
    #
    colorFilterFunction = property(getColorFilterFunction, setColorFilterFunction)
